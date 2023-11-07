#include <strings.h>

#include <iostream>

#include "hyprmag.hpp"

static void help(void) {
    std::cout << "Hyprmag usage: hyprmag [arg [...]].\n\nArguments:\n"
              << " -h | --help              | Show this help message\n"
              << " -i | --render-inactive   | Render (freeze) inactive displays\n"
              << " -r | --radius            | Define lens radius\n"
              << " -s | --scale             | Define lens scale\n";
}

int main(int argc, char** argv, char** envp) {
    g_pHyprmag = std::make_unique<CHyprmag>();

    while (true) {
        static struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                               {"render-inactive", no_argument, NULL, 'i'},
                                               {"radius", required_argument, NULL, 'r'},
                                               {"scale", required_argument, NULL, 's'},
                                               {NULL, 0, NULL, 0}};

        int                  c = getopt_long(argc, argv, "hir:s:", long_options, NULL);

        if (c == -1)
            break;

        switch (c) {
            case 'h': help(); exit(0);
            case 'i': g_pHyprmag->m_bRenderInactive = true; break;
            case 'r': g_pHyprmag->m_iRadius         = atoi(optarg); break;
            case 's': g_pHyprmag->m_fScale          = atof(optarg); break;

            default: help(); exit(1);
        }
    }

    if (g_pHyprmag->m_iRadius <= 0 || g_pHyprmag->m_iRadius == INT32_MAX) {
        std::cerr << "Radius must be between 1 and " << INT32_MAX << "!\n";
        exit(1);
    }
    if (g_pHyprmag->m_fScale < 0.5f || g_pHyprmag->m_fScale > 10.0f) {
        std::cerr << "Scale must be between 0.5 and 10!\n";
        exit(1);
    }

    g_pHyprmag->init();

    return 0;
}
