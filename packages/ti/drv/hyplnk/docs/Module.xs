/******************************************************************************
 * FILE PURPOSE: HYPLNK LLD DOCS Module specification file.
 ******************************************************************************
 * FILE NAME: module.xs
 *
 * DESCRIPTION: 
 *  This file contains the module specification for the HYPLNK LLD Documentation.
 *
 * Copyright (C) 2009-2016, Texas Instruments, Inc.
 *****************************************************************************/

/* Load the library utility. */
var libUtility = xdc.loadCapsule ("../build/buildlib.xs");

/**************************************************************************
 * FUNCTION NAME : modBuild
 **************************************************************************
 * DESCRIPTION   :
 *  The function is used to build all the components of the documentation
 **************************************************************************/
function modBuild() 
{
    /* Create the actual PROLOGUE Section for the Documentation.*/
    Pkg.makePrologue += "release: HYPLNK_LLD_document_generation\n";
    Pkg.makePrologue += "HYPLNK_LLD_document_generation:\n";
    Pkg.makePrologue += "\t @echo -------------------------------------------------------\n";
    Pkg.makePrologue += "\t @echo Generating HYPLNK LLD Documentation\n";
    Pkg.makePrologue += "\t doxygen docs/Doxyfile\n";
    Pkg.makePrologue += "\t @echo HYPLNK LLD Documentation Generated \n";
    Pkg.makePrologue += "\t @echo -------------------------------------------------------\n";

    /* Add the documentation file to the package. */
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/tifooter.htm";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/tiheader.htm";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/tilogo.gif";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/titagline.gif";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/ReleaseNotes_HYPLNK_LLD.pdf"
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/KEYSTONE_HYPERLINK_LLD_2.x_manifest.html"
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/address_translation.jpg";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/address_translation_RX.jpg";
    /* Add the HTML documentation to the package */
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/doxygen";

    /* Generate the ECLIPSE Plugin Generation: Only for SETUP Releases. */
    if (hyplnklldInstallType == "SETUP")
    {
        Pkg.makePrologue += "all: eclipse_plugin_generation\n";
        Pkg.makePrologue += "eclipse_plugin_generation:\n";
        Pkg.makePrologue += "\t @echo ----------------------------\n";
        Pkg.makePrologue += "\t @echo HYPLNK LLD Eclipse Plugin Generation\n";
        Pkg.makePrologue += "\t xs xdc.tools.eclipsePluginGen -o . -x ./eclipseDocs/sample.xml -c ./eclipseDocs/toc_cdoc_sample.xml\n";
        Pkg.makePrologue += "\t @echo HYPLNK LLD Eclipse Plugin Generated \n";
        Pkg.makePrologue += "\t @echo ----------------------------\n";
    }
}

