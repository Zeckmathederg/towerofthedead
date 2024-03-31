AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = towerofthedead
towerofthedead_SOURCES = src/main.c \
			 src/dragoness/dragonessEssentialVars.c \
			 src/dragoness/dragonessTestModels.c \
			 src/dragoness/dragonessShaderCode.c \
			 src/dragoness/dragonessFunctions.c \
			 src/scripts/scriptAll.c
towerofthedead_LDADD =
if MINGW_W64
towerofthedead_RCFLAGS =
towerofthedead_SOURCES += src/totd-pubinfo.rc
towerofthedead_LDADD += src/totd-pubinfo.o
src/totd-pubinfo.o: src/totd-pubinfo.rc
	$(WINDRES) $(towerofthedead_RCFLAGS) -o $@ src/totd-pubinfo.rc
DLL_FILEDIR = vendor/windows/$(WINARCH)/lib
DLL_FILES = $(DLL_FILEDIR)/glew32.dll \
	    $(DLL_FILEDIR)/glfw3.dll \
	    $(DLL_FILEDIR)/libgcc_s_seh-1.dll \
	    $(DLL_FILEDIR)/libstdc++-6.dll \
	    $(DLL_FILEDIR)/libwinpthread-1.dll \
	    $(DLL_FILEDIR)/opengl32.dll
endif
install-exec-hook:
	$(MKDIR_P) $(DESTDIR)$(bindir)
	$(INSTALL_PROGRAM) $(bin_PROGRAMS) $(DESTDIR)$(bindir)
	@if test "$(MINGW_W64)" = "true"; then \
		for dll in $(DLL_FILES); do \
			$(INSTALL_DATA) $$dll $(DESTDIR)$(bindir); \
		done \
	fi
