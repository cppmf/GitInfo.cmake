
// system includes
#include <iostream>


int main()
{
#if defined (GIT_REVISION) && defined (GIT_REVISION_NAME)
    std::cout << "Found git revision: " << GIT_REVISION_NAME << " (" << GIT_REVISION << ")" << std::endl;
    return 0;
#else
    std::cout << "Git revision not found" << std::endl;
    return 1;
#endif
}
