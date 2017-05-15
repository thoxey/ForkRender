**GLSL Cook-Torrance BRDF**
=======
Rendering a UE4/Cook-Torrance BRDF in GLSL
------------
For my principles of rendering unit I had to create a GLSL shader for a simple object. I chose to do a basic fork and give it a BRDF using the Unreal Engine style Cook-Torrance shader.


----------


Running Instructions
------------------------

The demo was made to run on the university machines at the NCCA, but they should run on any properly configured Linux/OSX system (might work on Windows, let me know if you get it running). 

I used Qt as my editor and to power the GL context and GUI, I used version 4.0.2 of Qt Creator with Qt 5.7. The shaders are written for GLSL 4.1 so they would run on Mac, but they should work on earlier versions.

The main dependency is [NGL](https://github.com/NCCA/NGL) which is the graphics library that we use at the NCCA, there are build instructions on there on how to use it, but if it is built and in your home directory it should work fine.

----------

Credits
------------------------
This was based on the contents of a few academic papers and some stuff from online, the citations are in the code itself but also here for your convenience.

 - [Cook-Torrance Paper](http://inst.cs.berkeley.edu/~cs294-13/fa09/lectures/cookpaper.pdf)
 - [UE4 Shading Paper](https://de45xmedrsdbp.cloudfront.net/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf)
 - [Holger Dammertz's Hammersly Function](http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html)
 - [The Book of Shaders (Great Resource)](https://thebookofshaders.com/10/)
 - [NCCA Github](https://github.com/NCCA)
