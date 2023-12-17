lessThan(QT_MAJOR_VERSION, 5): message("Project requires Qt 5 as a minimum")

QT += core gui widgets

CONFIG += c++17

INCLUDEPATH  += include \
                ../common/include

SOURCES      += $$PWD/src/main.cpp \
                $$PWD/src/spectrum_viewer.cpp

HEADERS      += $$PWD/include/spectrum_viewer.h     

FORMS        += $$PWD/forms/spectrum_viewer.ui

BUILDDIR = $$PWD/build

OBJECTS_DIR = $${BUILDDIR}
MOC_DIR = $${BUILDDIR}
RCC_DIR = $${BUILDDIR}
UI_DIR = $${BUILDDIR}

#------------------------------------------------------------------------------
# get the PLATFORM_ environment variable from the system
PM = $$(PLATFORM_)

if(isEmpty(PM)){
    message("!--- The PLATFORM_ Environment Variable is not set")

    # this is the default configuration
    CONFIG(debug, debug|release) { 
            LIBS += $$PWD/../../liquid-dsp/libliquid.lib \ 
                    $$PWD/../../rapidyaml/build/Debug/ryml.lib
    }
    CONFIG(release, debug|release) { 
            LIBS += $$PWD/../../liquid-dsp/libliquid.lib \ 
                    $$PWD/../../rapidyaml/build/Release/ryml.lib
    }
    
    INCLUDEPATH += $$PWD/../../Common/include \ 
                   $$PWD/../../liquid-dsp/libliquid \
                   $$PWD/../../rapidyaml/include 
                   
} else {
    message("Platform:" $${PM})
}

#------------------------------------------------------------------------------
# check the PLATFORM_ env variable and assign the correct paths
contains(PM, "LaptopN") {

    # this sections check the build type Debog or Release and sets variables accordingly (needed to specifiy debug or release versions of a lib)
    CONFIG(debug, debug|release) { 
        LIBS += C:/opencv-4.5.0/build/x64/vc15/lib/opencv_world450d.lib \ 
                C:/Projects/rapidyaml/build/Debug/ryml.lib
    }
    CONFIG(release, debug|release) { 
        LIBS += C:/opencv-4.5.0/build/x64/vc15/lib/opencv_world450.lib \ 
                C:/Projects/rapidyaml/build/Release/ryml.lib
    }

    INCLUDEPATH += C:/Projects/Common/include \ 
                   C:/opencv-4.5.0/build/include \ 
                   C:/Projects/rapidyaml/include 

}

contains(PM, "Laptop") {

    # this sections check the build type Debog or Release and sets variables accordingly (needed to specifiy debug or release versions of a lib)
    CONFIG(debug, debug|release) { 
        LIBS += D:/Projects/liquid-dsp/libliquid.lib \ 
                D:/Projects/rapidyaml/build/Debug/ryml.lib
    }
    CONFIG(release, debug|release) { 
        LIBS += D:/Projects/liquid-dsp/libliquid.lib \ 
                D:/Projects/rapidyaml/build/Release/ryml.lib
    }

    INCLUDEPATH += D:/Common/include \ 
                   D:/Projects/liquid-dsp/liquid \ 
                   D:/Projects/rapidyaml/include 
}

# Add aditional platforms here and adjust the paths accordingly

#------------------------------------------------------------------------------
message("------------------------------------------------------------------------------")
message("SOURCES")
for(a, SOURCES):message("    "$${a})
message(" ")

message("------------------------------------------------------------------------------")
message("INCLUDEPATH")
for(a, INCLUDEPATH):message("    "$${a})
message(" ")

message("------------------------------------------------------------------------------")
message("LIBS")
for(a, LIBS):message("    "$${a})
message(" ")

message("------------------------------------------------------------------------------")


# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/windowflags
#target.path = C:\Projects\Repos\widgets\windowflags2
#INSTALLS += target

