# wxvtk-UpdatedOnNov27_2020

Modified version of the original source-code of wxvtk(https://github.com/vadz/wxVTK) and CMakeLists.txt in order to make it work with WxWidgets-3.0.5 and VTK-8. Modifications were required since a lot has changed in VTK source code during last five years or so. It builds wxVTKRenderWindowInteractor.(dll,lib) as well as compiles a minimal working example (SAMPLE.cpp) with dynamic linking to the wxVTKRenderWindowInteractor.dll leading to MAIN.exe. A screenshot of the output window (MAIN.exe) is shown below:

![screenshot](https://github.com/harshn05/wxvtk-UpdatedOnJan27_2020/blob/master/Capture.PNG)
