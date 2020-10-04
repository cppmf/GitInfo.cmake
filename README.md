<p align="center">
  <img src="https://github.com/cppmf/artwork/raw/master/banner/GetInfo.cmake/GetInfo.png" height="100" />
</p>

<p align="center">
  CMake module to easily retrieve git information of your project
</p>

---

## Usage
The easiest way to use [GitInfo.cmake](https://github.com/cppmf/GitInfo.cmake) is by adding [GetCPM.cmake](https://github.com/cppmf/GetCPM.cmake) to your project.

First add GetCPM.cmake module :

```bash
mkdir cmake
wget -O cmake/CPM.cmake https://raw.githubusercontent.com/cppmf/GetCPM.cmake/master/GetCPM.cmake
```

Then add the following lines to the project's `CMakeLists.txt`.


```bash
# include GetCPM.cmake module
include(cmake/CPM.cmake)

# add GitInfo.cmake and tell where to find the root project
# by specifying the GIT_INFO_SOURCE_DIR variable.
CPMAddPackage(
  NAME GitInfo.cmake
  GITHUB_REPOSITORY cppmf/GitInfo.cmake
  VERSION 1.0.0
)

# then call GitInfo function
GitInfo(${CMAKE_CURRENT_SOURCE_DIR})
```

## Available variables

After calling GitInfo function, the following variables will be set

variable | description
---------|------------
GIT_DIR | path to the project .git directory
GIT_IS_DIRTY | whether or not the working tree is dirty
GIT_HEAD_BRANCH | name of the brack associated te HEAD
GIT_REVISION_HASH | current HEAD sha hash
GIT_REVISION | shorten version of GIT_REVISION_HASH
GIT_REVISION_NAME | name associated to GIT_REVISION_HASH
GIT_AUTHOR_NAME | author name
GIT_AUTHOR_EMAIL | author email
GIT_AUTHOR_DATE | author date
GIT_AUTHOR_DATE_ISO | author date, strict ISO 8601 format
GIT_COMMITTER_NAME | committer name
GIT_COMMITTER_EMAIL | committer email
GIT_COMMITTER_DATE | committer date
GIT_COMMITTER_DATE_ISO | committer date, strict ISO 8601 format
GIT_REMOTE_ORIGIN_URL | origin remote url
GIT_LATEST_TAG_LONG | most recent tag of the current branch
GIT_LATEST_TAG | most recent tagname of the current branch
