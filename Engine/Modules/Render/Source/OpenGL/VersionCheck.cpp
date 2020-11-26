/**
 * Created by rayfalling on 2020/10/12.
 * */

#include "OpenGL/VersionCheck.h"
#include "OpenGL/GLConstant.h"

[[maybe_unused]] bool Engine::Render::OpenGL::CheckGLVersion(GLVersion& version) {
	return version.major >= C_MIN_GL_VERSION.major && version.minor >= C_MIN_GL_VERSION.minor;
}
