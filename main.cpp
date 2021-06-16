// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "model.h"
#include "pidRocket.h"

char        *progname;
unsigned int debug = 0;
unsigned int flag  = 0;


// --------------------------------------------------------------------
void
application (char *filename)  {
    FILE  *fp;
    char   s[BUFSIZ];

    printf ("%s: %s\n", progname, filename);

    if ( (fp = fopen (filename, "rb")) == NULL)  {
        perror ("app - fopen input");
        exit (1);
    }

    int  arg1;
    while (fgets (s, BUFSIZ, fp) != NULL)  {
        printf ("%s", s);

        if (strstr (s, "step"))  {
            sscanf (s, "%*s %d", & arg1);

            while (arg1--)
                model (1);
        }
    }
}

// --------------------------------------------------------------------
void help (void)  {
    printf (" Usage: %s \n", progname);
}

// --------------------------------------------------------------------
int main (int argc, char **argv)  {
    int   c;

    progname = *argv;

    while ((c = getopt(argc, argv, "D:o")) != -1)  {
        switch (c)  {
        case 'D':
            debug = atoi (optarg);
            break;

        case 'o':
            break;

        default:
            printf ("Error: unknown option '%c'\n", optopt);
                        help();
            break;
        };

    }

    if (optind == argc)
        help();
    else
        for ( ; optind < argc; optind++)
            application (argv[optind]);

    return 0;
}
