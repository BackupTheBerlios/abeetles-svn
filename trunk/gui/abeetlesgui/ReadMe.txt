========================================================================
    CONSOLE APPLICATION : Abeetles Project Overview
========================================================================

AppWizard has created this Abeetles application for you.  

This file contains a summary of what you will find in each of the files that
make up your Abeetles application.


Abeetles.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Abeetles.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Abeetles.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////


CppDoc Guidelines:

My rules:
Method comment:

/**
* Protected method <br>
* Description:<br>
* System dependence:<br>
* Usage comments:<br>
* @return (Return values - meaning) 
* @param name [ descrip](Parameters - meaning)
* @throws name [descrip](Exceptions - meaning)
* @see reference : adds reference to the "See Also" section. The reference can be any of the following:
*          o HTML tag/text, which is added unmodified
*          o a quoted string (e.g., "Foo Bar"), the contents of which are added unmodified
*          o [project].[ class-name][#member] [text ], which adds a link to the given member in class class-name in project project . If project is omitted, the current entity's project is assumed. If class-name is omitted, the current class is assumed. If member is omitted, the link is to the class-file. If text is omitted, default display text is added, based on the actual link.
* {@link reference } replaced with a reference that is built using the exact same syntax as the @see tag (above). For example:
*/

Class comment:

/**
* Desc:
* System dependence:
* Usage comments:
* Relations to other classes:
*/

 Documentation Comments

Basic format
Documentation comments begin with "/**" and end with "*/". Preceding a class, struct, 
typedef, enum, variable, or function with a documentation comment will cause the 
contents of the comment to be attached to that entity. Comments can include HTML 
formatting. For example, the following comment is valid:

    /**
    * This is a <B>test</B> of:
    * <UL>
    * <LI>documentation comments
    * <LI>HTML formatting
    * </UL>
    */
    void foo()
    {
    }

It will attach this documentation to foo():

    This is a test of:

        * documentation comments
        * HTML formatting


Special tags for the cppdoc-standard module
The cppdoc-standard module processes a number of special tags when they are found at the beginning of a line within a documentation comment. These tags should be used below normal documentation text.

    * @author name : adds name to the list of authors under a section titled "Author". Enable this tag in the Module Options dialog or with the -enable-author option.
    * @deprecated text : adds a Deprecated flag at the beginning of the documentation, followed by text. Also adds the current entity to the master deprecated list.
    * @exception: same as @throw.
    * @param name [ descrip]: adds name to the list in the "Parameters" section. The description will be added if it is supplied.
    * @return descrip : adds a section titled "Returns", with the given description.
    * @see reference : adds reference to the "See Also" section. The reference can be any of the following:
          o HTML tag/text, which is added unmodified
          o a quoted string (e.g., "Foo Bar"), the contents of which are added unmodified
          o [project].[ class-name][#member] [text ], which adds a link to the given member in class class-name in project project . If project is omitted, the current entity's project is assumed. If class-name is omitted, the current class is assumed. If member is omitted, the link is to the class-file. If text is omitted, default display text is added, based on the actual link.

        Examples:

            @see <a href="http://www.cppdoc.com">CppDoc website</a>
            @see "The Reference Manual"
            @see parser.ParserExpression#eval(int)
            @see ParserExpression#eval the illustrious eval function
            @see ParserExpression
            @see #eval the one-and-only eval (this is display text)

    * @since descrip: adds descrip to the "Since" section.
    * @throw: same as @throws.
    * @throws name [descrip]: adds name to the list of exceptions in the "Throws" section. If descrip is given, it is added next to name .
    * @version text : sets the text in the "Version" section. Enable this tag in the Module Options dialog or with the -enable-version option.

The following "floating tags" may be used anywhere in the documentation comment, unlike the others which must appear at the beginning of a line.

    * {@docroot} replaced with the path to the document root (where the main HTML file is located).
    * {@files} replaced with a list (<UL>) of links to the associated source files for this entity.
    * {@file1} replaced with a link to the first source file (usually the ".h" file) for this entity.
    * {@file2} replaced with a link to the second source file (usually the ".cpp" file) for this entity.
    * {@link reference } replaced with a reference that is built using the exact same syntax as the @see tag (above). For example:

    /**
    * Click {@link ParserExpression#eval here} to go
    * to the eval() function in the ParserExpression
    * class.
    */


Excluding files from processing
If you include the special comment

    /**NODOCUMENT**/

at the beginning of a file, it will not be included in processing.


Excluding parts of files from processing
To exclude parts of a file from processing, put the following comment at the beginning of the section to be excluded: 

    /* CPPDOC_BEGIN_EXCLUDE */

Put the following comment at the end of the section to be excluded: 

    /* CPPDOC_END_EXCLUDE */


Including project-level and overview-level documentation
The cppdoc-standard module allows you to include documentation for each project, and overview documentation.  To create project-level documentation, create a file called "project.html" at the root for that project's source code.  For overview documentation, create a file called "overview.html" at the overall root directory to be processed.  These filenames may be changed in the Module Options dialog, or as command-line flags for the cppdoc-standard module.




