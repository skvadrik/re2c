#include <stdio.h> /* fprintf() */
#include <string>

#include "config.h"
#include "src/conf/ver_to_vernum.h"

namespace re2c {

std::string ver_to_vernum(const std::string & ver)
{
    std::string parts[3];
    unsigned p = 0;

    for (unsigned i = 0; p < 3 && i < ver.length (); i++)
    {
        if (ver[i] == '.')
            p++;
        else
            parts[p].push_back (ver[i]);
    }

    for (p = 0; p < 3; p++)
        while (parts[p].length () < 2)
            parts[p].insert (0, 1, '0');

    return parts[0] + parts[1] + parts[2];
}

} // namespace re2c
