
// system includes
#include <iostream>


int main(int argc, char* argv[])
{
#if defined (GIT_REVISION) && defined (GIT_REVISION_NAME)
    std::cout << "Found git revision: " << GIT_REVISION_NAME << " (" << GIT_REVISION << ")" << std::endl;
#else
    std::cout << "Git revision not found" << std::endl;
#endif

    return 0;
}
