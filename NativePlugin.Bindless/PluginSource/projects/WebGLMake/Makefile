SRCDIR = ../../source
SRCS = $(SRCDIR)/RenderingPlugin.cpp \
$(SRCDIR)/RenderAPI.cpp \
$(SRCDIR)/RenderAPI_OpenGLCoreES.cpp \
OBJS = ${SRCS:.cpp=.o}
UNITY_DEFINES = -DSUPPORT_OPENGL_ES=1 -DSUPPORT_VULKAN=0 -DUNITY_WEBG=1
CXXFLAGS = $(UNITY_DEFINES) -O2 -fPIC
LDFLAGS = -static -rdynamic
LIBS = 
PLUGIN_STATIC = libRenderingPlugin.a

CXX ?= em++

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: static

clean:
	rm -f $(OBJS) $(PLUGIN_STATIC)

static: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PLUGIN_STATIC) $(OBJS) $(LIBS)
