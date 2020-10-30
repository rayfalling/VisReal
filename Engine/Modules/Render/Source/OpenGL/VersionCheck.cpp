/**
 * Created by rayfalling on 2020/10/12.
 * */

#include "OpenGL/VersionCheck.h"
#include "OpenGL/GLConstant.h"

[[maybe_unused]] bool Engine::Render::OPENGL::CheckGLVersion(GLVersion& version) {
	return version.major >= CMinGLVersion.major && version.minor >= CMinGLVersion.minor;
}
