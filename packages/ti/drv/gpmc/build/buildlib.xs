/******************************************************************************
 * FILE PURPOSE: Build Library Utilities
 ******************************************************************************
 * FILE NAME: buildlib.xs
 *
 * DESCRIPTION:
 *  This file contains common routines that are used by the various LLD
 *  components.
 *
 * Copyright (C) 2014-2015, Texas Instruments, Inc.
 *****************************************************************************/

/**************************************************************************
 * FUNCTION NAME : listAllFiles
 **************************************************************************
 * DESCRIPTION   :
 *  Utility function which lists all files with a specific extension
 *  present in a directory and any directory inside it.
 **************************************************************************/
function listAllFiles(ext, dir, recurse)
{
    var srcFile = [];
    var d;

    /* If recurse parameter is not specified we default to recursive search. */
    if (recurse == null)
        recurse = true;

    if (dir == undefined)
          d = ".";
    else
      d = dir;

    /* Get access to the current directory. */
    var file = new java.io.File(d);

    /* Check if the file exists and it is a directory. */
    if (file.exists() && file.isDirectory())
    {
        /* Get a list of all files in the specific directory. */
        var fileList = file.listFiles();
        for (var i = 0; i < fileList.length; i++)
        {
            /* Dont add the generated directory 'package' and any of its files
             * to the list here. */
            if (fileList[i].getName().matches("package") == false)
            {
                /* Check if the detected file is a directory */
                if (fileList[i].isDirectory())
                {
                    /* We will recurse into the subdirectory only if required to do so. */
                    if (recurse == true)
                    {
                        /* Generate the directory Name in which we will recurse. */
                        var directoryName = d + "/" + fileList[i].getName();

                        /* Get a list of all files in this directory */
                        var fileListing = listAllFiles (ext, directoryName, recurse);
                        if (fileListing != null)
                        {
                            /* Return a list of all file names in the directory. */
                            for (var j = 0 ; j < fileListing.length; j++)
                                srcFile[srcFile.length++] = fileListing[j];
                        }
                    }
                }
                else
                {
                    /* This was a file. Check if the file name matches the extension */
                    if (fileList[i].getName().endsWith(ext) == true)
                        srcFile[srcFile.length++] = d + "/" + fileList[i].getName();
                }
            }
        }

        return srcFile;
    }
    return null;
}


function createMake(makefile)
{
    /* Create the main make file */
    var fileModule = xdc.module('xdc.services.io.File');
    if(makefile==undefined)
    {
      try{
          makefile = fileModule.open("makefile", "w");
         } catch (ex)
         {
           print("makefile cannot be written to. Please check Writing Permissions.");
           java.lang.System.exit(1);
         }

      Pkg.makePrologue += "\ninclude makefile\n";

      Pkg.makeEpilogue += "\nclean::\n\t-$(RM)  makefile\n";
      makefile.writeLine("#*******************************************************************************");
      makefile.writeLine("#* FILE PURPOSE: Top level makefile for Creating Component Libraries");
      makefile.writeLine("#*******************************************************************************");
      makefile.writeLine("#* FILE NAME: makefile");
      makefile.writeLine("#*");
      makefile.writeLine("#* DESCRIPTION: Defines Compiler tools paths, libraries , Build Options ");
      makefile.writeLine("#*");
      makefile.writeLine("#*");
      makefile.writeLine("#*******************************************************************************");
      makefile.writeLine("#*");
      makefile.writeLine("# (Mandatory) Specify where various tools are installed.");

      var file = xdc.module('xdc.services.io.File');


      makefile.writeLine("\n# Output for prebuilt generated libraries");
      makefile.writeLine("export LIBDIR ?= ./lib");
      /* use sectti from path */
      makefile.writeLine("export SECTTI ?= sectti");

      /* Create INCDIR from XDCPATH */

      /* copy the environment array from the current environment */
      var env   = java.lang.System.getenv();
      var getxdcpath=String(java.lang.System.getenv("XDCPATH"));
      getxdcpath= getxdcpath.replace(/\\/g,"/");
      var keys  = env.keySet().toArray();
      var key;
      var stat={};
      var env_j=[];
      var listxdcpath = new Array();
      for (var i = 0; i < keys.length; i++) {
           key = String(keys[i]);
           if((key.match("INSTALL_PATH")) || (key.match("INSTALLDIR")))
           {
             var keyPath=String(env.get(key));
             keyPath=keyPath.replace(/\\/g,"/");
             var file = xdc.module('xdc.services.io.File');
             keyPath=file.getDOSPath(keyPath);
             if(getxdcpath.toString().match(keyPath))
             {
                 listxdcpath.push({keyname: key,keypath: keyPath});
                 while(getxdcpath.toString().match(keyPath))
                 {
                   getxdcpath=getxdcpath.toString().replace(keyPath,"$("+key+")");
                 }
             }
           }

     }
       var pkgroot="..";
       for (var i = Pkg.name.split('.').length; i > 1; i--) {
              pkgroot+="/..";
          }

      makefile.writeLine("\n# ROOT Directory");
      makefile.writeLine("export ROOTDIR := "+pkgroot);

      makefile.writeLine("\n# INCLUDE Directory");
      makefile.writeLine("export INCDIR := "+getxdcpath+";$(ROOTDIR)");

      makefile.writeLine("\n# Common Macros used in make");
      makefile.writeLine("\nifndef RM");
      makefile.writeLine("export RM = rm -f");
      makefile.writeLine("endif");

      makefile.writeLine("\nifndef CP");
      makefile.writeLine("export CP = cp -p");
      makefile.writeLine("endif");

      makefile.writeLine("\nexport MKDIR = mkdir -p");

      makefile.writeLine("\nifndef RMDIR");
      makefile.writeLine("export RMDIR = rm -rf");
      makefile.writeLine("endif");

      makefile.writeLine("\nifndef SED");
      makefile.writeLine("export SED = sed");
      makefile.writeLine("endif");

      makefile.writeLine("\nifndef MAKE");
      makefile.writeLine("export MAKE = make");
      makefile.writeLine("endif");

      makefile.writeLine("\n# PHONY Targets");
      makefile.writeLine(".PHONY: all clean cleanall ");

      makefile.writeLine("\n# FORCE Targets");
      makefile.writeLine("FORCE: ");

      makefile.writeLine("\n# all rule");
      makefile.writeLine("all: .executables");
      makefile.writeLine(".executables: .libraries");
      makefile.writeLine(".libraries:");

      makefile.writeLine("\n# Clean Rule");
      makefile.writeLine("clean:: clean_package");
      makefile.writeLine("# Clean Top Level Object Directory ");
      makefile.writeLine("clean_package :\n\t$(RMDIR) $(LIBDIR)/*/");
      makefile.writeLine("\t$(RMDIR) package/cfg");
   }
   else
   {
     try{
          makefile = fileModule.open("makefile", "a");
         } catch (ex)
         {
           print("makefile cannot be written to. Please check Writing Permissions.");
           java.lang.System.exit(1);
         }

    }

 return makefile;
}

function createLibMake(device, objExtDir, makelibname,targetname, objectPath, useProfiling)
{
   var tooldir;
   var cmdprefix;
   var targetDir;
   var stringname=String(targetname).replace("(xdc.bld.ITarget.Module)","");
   var benchSuffix = "";

   if (useProfiling == true) {
     benchSuffix = "_bench";
   }

   switch(stringname)
   {
    case String(C66LE):
      tooldir="C6X_GEN_INSTALL_PATH";
      cmdprefix="";
      targetDir="c66/release";
      targetname=C66LE;
      break;
    case String(C66BE):
      tooldir="C6X_GEN_INSTALL_PATH";
      cmdprefix="";
      targetDir="c66/release";
      targetname=C66BE;
      break;
    case String(A15LE):
      tooldir="TOOLCHAIN_PATH_A15";
      cmdprefix="CROSS_TOOL_PRFX";
      targetDir="a15/release";
      targetname=A15LE;
      break;
    case String(A9LE):
      tooldir="TOOLCHAIN_PATH_A9";
      cmdprefix="CROSS_TOOL_PRFX";
      targetDir="a9/release";
      targetname=A9LE;
      break;
    case String(A8LE):
      tooldir="TOOLCHAIN_PATH_A8";
      cmdprefix="CROSS_TOOL_PRFX";
      targetDir="a8/release";
      targetname=A8LE;
      break;
    case String(M4LE):
      tooldir="TOOLCHAIN_PATH_M4";
      cmdprefix="";
      targetDir="m4/release";
      targetname=M4LE;
      break;
   }

    var fileModule = xdc.module('xdc.services.io.File');
    try{
     var dstFile = new java.io.File(makelibname);
     dstFile.getParentFile().mkdirs();
     libmakefile = fileModule.open(makelibname, "w");
     /* Add to Archive list */
    } catch (ex)
    {
     print(makelibname+" cannot be written to. Please check Writing Permissions.");
     java.lang.System.exit(1);
    }
    libmakefile.writeLine("#*******************************************************************************");
    libmakefile.writeLine("#* FILE PURPOSE: Lower level makefile for Creating Component Libraries");
    libmakefile.writeLine("#*******************************************************************************");
    libmakefile.writeLine("#* FILE NAME: "+makelibname);
    libmakefile.writeLine("#*");
    libmakefile.writeLine("#* DESCRIPTION: Defines Source Files, Compilers flags and build rules");
    libmakefile.writeLine("#*");
    libmakefile.writeLine("#*");
    libmakefile.writeLine("#*******************************************************************************");
    libmakefile.writeLine("#");
    libmakefile.writeLine("");
    libmakefile.writeLine("#");
    libmakefile.writeLine("# Macro definitions referenced below");
    libmakefile.writeLine("#");
    libmakefile.writeLine("empty =");
    libmakefile.writeLine("space =$(empty) $(empty)");

    if ((targetname.name == "A15F") || (targetname.name == "A9F") || (targetname.name == "A8F"))
    {

        if(stringname.match("gnu.targets"))
        {
            libmakefile.writeLine("CC = $("+tooldir+")/bin/$("+cmdprefix+")gcc");
            libmakefile.writeLine("AC = $("+tooldir+")/bin/$("+cmdprefix+")as");
            libmakefile.writeLine("ARIN = $("+tooldir+")/bin/$("+cmdprefix+")ar");
            libmakefile.writeLine("LD = $("+tooldir+")/bin/$("+cmdprefix+")gcc");
        }
        else
        {
            print("Error: Non-GNU targets are not currently supported ");
            java.lang.System.exit(1);

        }

        libmakefile.writeLine("INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\\$(space),$(INCDIR)))) -I$("+tooldir+")/include");
        libmakefile.writeLine("OBJEXT = o"+targetname.suffix);
        libmakefile.writeLine("AOBJEXT = s"+targetname.suffix);
        if (useProfiling == true){
            libmakefile.writeLine("CFLAGS_INTERNAL = " +targetname.ccOpts.prefix+" "+targetname.cc.opts+" -finstrument-functions -gdwarf-3 -g -D_ENABLE_BM");
        }else{
            libmakefile.writeLine("CFLAGS_INTERNAL = " +targetname.ccOpts.prefix+" "+targetname.cc.opts);
        }
        libmakefile.writeLine("ASFLAGS_INTERNAL = " +targetname.asmOpts.prefix+" "+targetname.asm.opts);
        libmakefile.writeLine("ARFLAGS_INTERNAL = " +targetname.ar.opts);
        libmakefile.writeLine("LNKFLAGS_INTERNAL = " +targetname.lnk.opts);
        libmakefile.writeLine("INTERNALDEFS = -MD -MF $@.dep");
        libmakefile.writeLine("INTERNALLINKDEFS = -o $@ -m $@.map");  /* TBD */
        libmakefile.writeLine("OBJDIR =  ./obj/obj_" +targetname.suffix +"/" + device.toString() + "/" + targetDir +"/obj" + "/" + objExtDir + benchSuffix); 

    }
    else
    {

        if(stringname.match("ti.targets"))
        {

            var rtslibtemp = targetname.lnkOpts.suffix.toString().split("/");
            var rtslib;
            for(n=0;n<rtslibtemp.length;n++)
            {
                if(rtslibtemp[n].match(".lib"))
                {
                    rtslib=rtslibtemp[n];
                }
            }

            libmakefile.writeLine("CC = $("+tooldir+")/bin/"+targetname.cc.cmd);
            libmakefile.writeLine("AC = $("+tooldir+")/bin/"+targetname.asm.cmd);
            libmakefile.writeLine("ARIN = $("+tooldir+")/bin/"+targetname.ar.cmd);
            libmakefile.writeLine("LD = $("+tooldir+")/bin/"+targetname.lnk.cmd);
            libmakefile.writeLine("RTSLIB = -l $("+tooldir+")/lib/"+rtslib);
        }
        else
        {
            print("Error: Non-TI targets are not currently supported ");
            java.lang.System.exit(1);

        }

        libmakefile.writeLine("INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\\$(space),$(INCDIR)))) -I$("+tooldir+")/include");
        libmakefile.writeLine("OBJEXT = o"+targetname.suffix);
        libmakefile.writeLine("AOBJEXT = s"+targetname.suffix);
        if (useProfiling == true){
            libmakefile.writeLine("CFLAGS_INTERNAL = " +targetname.ccOpts.prefix+" "+targetname.cc.opts+" --entry_parm=address --exit_hook=ti_utils_exit --exit_parm=address --entry_hook=ti_utils_entry -g -D_ENABLE_BM");
        }else{
            libmakefile.writeLine("CFLAGS_INTERNAL = " +targetname.ccOpts.prefix+" "+targetname.cc.opts);
        }
        libmakefile.writeLine("ASFLAGS_INTERNAL = " +targetname.asmOpts.prefix+" "+targetname.asm.opts);
        libmakefile.writeLine("ARFLAGS_INTERNAL = " +targetname.ar.opts);
        libmakefile.writeLine("LNKFLAGS_INTERNAL = " +targetname.lnk.opts);
        /* libmakefile.writeLine("INTERNALDEFS = -D"+stringname.replace(/\./g,"_")+" -Dxdc_target_types__=ti/targets/std.h -DMAKEFILE_BUILD -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep");*/
        libmakefile.writeLine("INTERNALDEFS = -D"+stringname.replace(/\./g,"_")+"  -DMAKEFILE_BUILD -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep");
        libmakefile.writeLine("INTERNALLINKDEFS = -o $@ -m $@.map");
        libmakefile.writeLine("OBJDIR =  ./obj/obj_" +targetname.suffix +"/" + device.toString() + "/" + targetDir +"/obj" + "/" + objExtDir + benchSuffix); 
    }

 return libmakefile;

}

function makeAddObjects(srcString, makefilename, srcfiles, flags,fileExt, targetName, objDir)
{
  var  sourcestring = (srcString + fileExt).toString().toUpperCase();
  var  compileflagstring = sourcestring + "FLAGS";
  var  objectliststring = sourcestring + "OBJS";
  /* List all the source files */
  makefilename.writeLine("\n#List the "+srcString+" Files");
  makefilename.writeLine(sourcestring + "= \\");
  for(var i=0;i<srcfiles.length-1;i++)
  {
    makefilename.writeLine("    "+srcfiles[i]+"\\");
  }
    makefilename.writeLine("    "+srcfiles[i]+"\n");

 /* Flags for the source files */
 makefilename.writeLine("# FLAGS for the "+srcString+" Files");
 var compileflags="";
 if(fileExt == "asm" && flags.aopts != undefined)
 {
   compileflags+=" "+flags.aopts;
 }
 else if((fileExt == "c" || fileExt == "sa")&& flags.copts != undefined)
 {
   compileflags+=" "+flags.copts;
 }

 if(flags.incs != undefined)
 {
   compileflags+=" "+flags.incs;
 }


 makefilename.writeLine(compileflagstring+" = "+compileflags +" \n");
 makefilename.writeLine("# Make Rule for the "+srcString+" Files");

 makefilename.writeLine(objectliststring +" = $(patsubst %."+fileExt+", "+objDir+"/%.$(OBJEXT), $(" + sourcestring + "))");
 makefilename.writeLine("\n$("+objectliststring+"): "+objDir+"/%.$(OBJEXT): %."+fileExt);
 if(fileExt == "c")
 {
   makefilename.writeLine("\t-@echo cl"+targetName.suffix +" $< ...");
 }
 else
 {
   makefilename.writeLine("\t-@echo asm"+targetName.suffix +" $< ...");
 }
 makefilename.writeLine("\tif [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;");

 if(fileExt == "c")
 {
   if ((targetName.name == "A15F") || (targetName.name == "A9F") || (targetName.name == "A8F"))
   {
    makefilename.writeLine("\t$(RM) $@.dep");
    makefilename.writeLine("\t$(CC) $(CFLAGS_INTERNAL) $("+compileflagstring+") $(INTERNALDEFS) $(INCS) $< -o $@");
   /*
    TBD
   */
   }
   else
   {
    makefilename.writeLine("\t$(RM) $@.dep");
    makefilename.writeLine("\t$(CC) $(CFLAGS_INTERNAL) $("+compileflagstring+") $(INTERNALDEFS) $(INCS) -fc $< ");
    makefilename.writeLine("\t-@$(CP) $@.dep $@.pp; \\");
    makefilename.writeLine("         $(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\\\$$//' \\");
    makefilename.writeLine("             -e '/^$$/ d' -e 's/$$/ :/' < $@.pp >> $@.dep; \\");
    makefilename.writeLine("         $(RM) $@.pp ");
   }
 }
 else if(fileExt == "asm")
 {
   makefilename.writeLine("\t$(AC) $(ASFLAGS_INTERNAL) $("+compileflagstring+") $(INTERNALDEFS) $(INCS) -fa $< ");
 }
 else if(fileExt == "sa")
 {
   makefilename.writeLine("\t$(AC) $(ASFLAGS_INTERNAL) $("+compileflagstring+") $(INTERNALDEFS) $(INCS) $< ");
 }

 makefilename.writeLine("\n#Create Empty rule for dependency");
 makefilename.writeLine("$("+objectliststring+"):"+makefilename.$private.fd);
 makefilename.writeLine(makefilename.$private.fd+":");
 makefilename.writeLine("\n#Include Depedency for "+srcString+" Files");
 makefilename.writeLine("ifneq (clean,$(MAKECMDGOALS))");
 makefilename.writeLine(" -include $("+objectliststring+":%.$(OBJEXT)=%.$(OBJEXT).dep)");
 makefilename.writeLine("endif");

}

/**************************************************************************
 * FUNCTION NAME : buildLibrary
 **************************************************************************
 * DESCRIPTION   :
 *  Utility function which will build a specific library
 **************************************************************************/
var makefilelocal;
function buildLibrary (socName, isDmaSoc, isSoc, libOptions, libName, target, libFiles, useProfiling)
{
    var targetDir;
    var objExtDir;

    if (useProfiling == true)
    {
        libName += ".profiling"
    }

    if (target.name == "A15F")
    {
        targetDir = "a15/release";
    }
    else if (target.name == "A9F")
    {
        targetDir = "a9/release";
    }
    else if (target.name == "A8F")
    {
        targetDir = "a8/release";
    }
    else if (target.name == "M4")
    {
        targetDir = "m4/release";
    }
    else
    {
        targetDir = "c66/release";
    }

    /* Derive the operating system and soc names */
    if (isSoc == "true") {
        var libNameExp = libName;
        targetDir = socName+"/"+targetDir;
        objExtDir = "soc";
    }
    else  {
        var libNameExp = libName;
        objExtDir = "all";
    }

    var lldFullLibraryPath = "./lib/" + targetDir +"/" + libNameExp;
    var lldFullBuildPath = "./build/" + targetDir +"/" + libNameExp;
    var lldFullLibraryPathMake = "$(LIBDIR)/" + targetDir +"/" + libNameExp;

    /* Create Main make file in the root of package folder */
    makefilelocal = createMake(makefilelocal);

    /* Write the rule to make library in main makefile */
    lib = lldFullBuildPath+".a"+target.suffix;
    libMake = lldFullLibraryPathMake+".a"+target.suffix;
    var objectPath= "./package/"+lldFullBuildPath;

    makefilelocal.writeLine("\n\n# Make rule to create "+libMake+" library");
    makefilelocal.writeLine(".libraries: "+ libMake);
    makefilelocal.writeLine(libMake+": FORCE\n\t$(MAKE) -f "+lib+".mk $@");

    /* Create Library make file in the lib folder */
    var makefilelib= createLibMake(socName, objExtDir, lib+".mk",target,objectPath,useProfiling);

    /* Rule to clean library in main makefile */
    makefilelocal.writeLine("# Rule to clean "+libMake+" library");
    makefilelocal.writeLine("clean ::\n\t$(RM) "+ libMake);
    librule="\n\n"+libMake+" :";

    /* Add files to be compiled */
    /* Separate out the C and assembly files */
    var cfiles= new Array();
    var afiles= new Array();
    var safiles= new Array();
    for each(var srcFile in libFiles)
    {
        var srcFile=String(srcFile);
        var dot = srcFile.lastIndexOf(".");
        var extension = srcFile.substr(dot,srcFile.length);
        if(extension == ".c")
        {
            cfiles.push(srcFile);
        }
        else if(extension == ".sa")
        {
            safiles.push(srcFile);
        }
        else if(extension == ".asm")
        {
            afiles.push(srcFile);
        }
        else
        {
            print("ERROR: Unsupported file extension");
            java.lang.System.exit(1);
        }
    }
    if(cfiles.length > 0)
    {
      makeAddObjects("COMMONSRC",makefilelib,cfiles,libOptions,"c",target, "$(OBJDIR)");
      librule += " $(COMMONSRCCOBJS)";
    }
    if(afiles.length > 0)
    {
      makeAddObjects("COMMONSRC",makefilelib,afiles,libOptions,"asm",target, "$(OBJDIR)");
      librule += " $(COMMONSRCASMOBJS)";
    }
    if(safiles.length > 0)
    {
      makeAddObjects("COMMONSRC",makefilelib,safiles,libOptions,"sa",target, "$(OBJDIR)");
      librule += " $(COMMONSRCSAOBJS)";
    }

    makefilelib.writeLine(librule);
    makefilelib.writeLine("\t@echo archiving $? into $@ ...");
    makefilelib.writeLine("\tif [ ! -d $(LIBDIR)/"+targetDir+" ]; then $(MKDIR) $(LIBDIR)/"+targetDir+" ; fi;");
    makefilelib.writeLine("\t$(ARIN) $(ARFLAGS_INTERNAL) $@ $?");
    makefilelib.close();

    /* Create the Epilogue; which executes after all the builds are completed.
     * This is used to generate the benchmark information for the built library.
     * Also add the benchmarking information file to the package. */
    /* Put the temp file in object directory since javascript doesn't have a built in tmpname,
     * and don't want --jobs=# with # > 1 to result in collisions */
    var libFullName = lldFullLibraryPath + ".a" + target.suffix;
    var tempFile = libFullName + ".xml";
    Pkg.makeEpilogue += ".libraries: " + libFullName +  "_size.txt\n";
    Pkg.makeEpilogue += libFullName +  "_size.txt: " + libFullName + "\n";
    if ( java.lang.String(target.name).contains('66') )
    {
        Pkg.makeEpilogue += "\n\t $(C6X_GEN_INSTALL_PATH)/bin/ofd6x -x " + libFullName + " > " + tempFile;
        Pkg.makeEpilogue += "\n\t $(SECTTI) " + tempFile + " > " + libFullName +  "_size.txt";
        Pkg.makeEpilogue += "\n\t $(RM) " + tempFile + "\n\n";
    }
    else if (target.name == "M4")
    {
        Pkg.makeEpilogue += "\n\t $(TOOLCHAIN_PATH_M4)/bin/armofd -x " + libFullName + " > " + tempFile;
        Pkg.makeEpilogue += "\n\t $(SECTTI) " + tempFile + " > " + libFullName +  "_size.txt";
        Pkg.makeEpilogue += "\n\t $(RM) " + tempFile + "\n\n";
    }
    else
    {
        Pkg.makeEpilogue += "\n\t $(TOOLCHAIN_PATH_A15)/bin/$(CROSS_TOOL_PRFX)size " + libFullName + " > " + libFullName + "_size.txt";
    }
    Pkg.otherFiles[Pkg.otherFiles.length++] = lldFullLibraryPath + ".a" + target.suffix + "_size.txt";
    Pkg.otherFiles[Pkg.otherFiles.length++] = lldFullBuildPath + ".a" + target.suffix + ".mk";
    Pkg.otherFiles[Pkg.otherFiles.length++] = lldFullLibraryPath + ".a" + target.suffix;

    /* We need to clean after ourselves; extend the 'clean' target to take care of this. */
    Pkg.makeEpilogue += "\nclean::\n";
    Pkg.makeEpilogue += "\t$(RM) " + lldFullBuildPath + ".a" + target.suffix + "_size.txt\n";
    Pkg.makeEpilogue += "\t$(RMDIR) " + "$(LIBDIR)/" + targetDir + "/ \n\n";

    return lib;
}



