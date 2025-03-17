#include <strings.h>

#include <iostream>

#include "hyprmag.hpp"

static void help(void) {
    std::cout << "Hyprmag usage: hyprmag [arg [...]].\n\nArguments:\n"
              << " -h | --help              | Show this help message\n"
              << " -r | --radius            | Define lens radius\n"
              << " -l | --lowercase-hex       | Outputs the hexcode in lowercase\n"
              << " -f | --format=fmt          | Specifies the output format (cmyk, hex, rgb, hsl, hsv)\n";
}

int main(int argc, char** argv, char** envp) {
    g_pHyprmag = std::make_unique<CHyprmag>();

    while (true) {
        static struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                               {"radius", required_argument, NULL, 'r'},
                                               {"lowercase-hex", no_argument, nullptr, 'l'},
                                               {"format", required_argument, nullptr, 'f'},
                                               {NULL, 0, NULL, 0}};

        int c = getopt_long(argc, argv, "hir:s:f:l", long_options, NULL);

        if (c == -1)
            break;

        switch (c) {
            case 'h': help(); exit(0);
            case 'r': g_pHyprmag->m_iRadius         = atoi(optarg); break;
            case 'l': g_pHyprmag->m_bUseLowerCase = true; break;
            case 'f':
                if (strcasecmp(optarg, "cmyk") == 0)
                    g_pHyprmag->m_bSelectedOutputMode = OUTPUT_CMYK;
                else if (strcasecmp(optarg, "hex") == 0)
                    g_pHyprmag->m_bSelectedOutputMode = OUTPUT_HEX;
                else if (strcasecmp(optarg, "rgb") == 0)
                    g_pHyprmag->m_bSelectedOutputMode = OUTPUT_RGB;
                else if (strcasecmp(optarg, "hsl") == 0)
                    g_pHyprmag->m_bSelectedOutputMode = OUTPUT_HSL;
                else if (strcasecmp(optarg, "hsv") == 0)
                    g_pHyprmag->m_bSelectedOutputMode = OUTPUT_HSV;
                else {
                    Debug::log(NONE, "Unrecognized format %s", optarg);
                    exit(1);
                }
                break;
            default: help(); exit(1);
        }
    }

    if (g_pHyprmag->m_iRadius <= 0 || g_pHyprmag->m_iRadius == INT32_MAX) {
        std::cerr << "Radius must be between 0 and " << INT32_MAX << "!\n";
        exit(1);
    }

    g_pHyprmag->init();

    return 0;
}
