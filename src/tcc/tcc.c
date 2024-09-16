/*
 *  TCC - Tiny C Compiler
 * 
 *  Copyright (c) 2001-2004 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "tcc.h"
// #if ONE_SOURCE
#include "fs.h"
# include "libtcc.c"
// #endif
#include "tcctools.c"


#if defined (__BENCH_TEST__)
static Finfo file_table[] = {
  {"/share/test.c", 336, 0, NULL, NULL},
  {"/share/test", 752, 336, NULL, NULL},
  {"/share/trm.c", 273, 1088, NULL, NULL},
};
int tcc_argc1 = 10;
char *tcc_argv1[]={
    "./tcc",
    "/share/trm.c",
    "/share/test.c",
    "-ffreestanding",
    "-nostdlib",
    "-o",
    "/share/test",
    "-Wl,-Ttext=0x80000000",
    "-O2",
    "-static"
};
#elif defined (__BENCH_TRAIN__)
static Finfo file_table[] = {
  {"/share/trm.c", 273, 0, NULL, NULL},
  {"/share/trap.h", 106, 273, NULL, NULL},
  {"/share/train.c", 1521, 379, NULL, NULL},
  {"/share/train", 106, 1900, NULL, NULL},
};
int tcc_argc1 = 10;
char *tcc_argv1[]={
    "./tcc",
    "/share/trm.c",
    "/share/train.c",
    "-ffreestanding",
    "-nostdlib",
    "-o",
    "/share/train",
    "-Wl,-Ttext=0x80000000",
    "-O2",
    "-static"
};
#elif defined (__BENCH_HUGE__)
#else //default to ref
#endif

static void set_environment(TCCState *s)
{
    char * path;

    // path = getenv("C_INCLUDE_PATH");
    path = "/";
    if(path != NULL) {
        tcc_add_sysinclude_path(s, path);
    }
    // path = getenv("CPATH");
    path = "/";
    if(path != NULL) {
        tcc_add_include_path(s, path);
    }
    // path = getenv("LIBRARY_PATH");
    path = "/";
    if(path != NULL) {
        tcc_add_library_path(s, path);
    }
}

static char *default_outputfile(TCCState *s, const char *first_file)
{
    char buf[1024];
    char *ext;
    const char *name = "a";

    if (first_file && strcmp(first_file, "-"))
        name = tcc_basename(first_file);
    snprintf(buf, sizeof(buf), "%s", name);
    ext = tcc_fileextension(buf);
#ifdef TCC_TARGET_PE
    if (s->output_type == TCC_OUTPUT_DLL)
        strcpy(ext, ".dll");
    else
    if (s->output_type == TCC_OUTPUT_EXE)
        strcpy(ext, ".exe");
    else
#endif
    if ((s->just_deps || s->output_type == TCC_OUTPUT_OBJ) && !s->option_r && *ext)
        strcpy(ext, ".o");
    else
        strcpy(buf, "a.out");
    return tcc_strdup(buf);
}


int main(int argc0, char **argv0)
{

  fs_init(file_table, 4);
  bench_malloc_init();
    TCCState *s, *s1;
    int ret, opt, n = 0, t = 0, done;
    uint64_t start_time = 0, end_time = 0;
    const char *first_file;
    int argc; char **argv;
    int ppfp = FD_STDOUT;


    start_time = uptime();
redo:
    // argc = argc0, argv = argv0;
    argc = tcc_argc1, argv = tcc_argv1;
    s = s1 = tcc_new();
#ifdef CONFIG_TCC_SWITCHES /* predefined options */
    tcc_set_options(s, CONFIG_TCC_SWITCHES);
#endif
    opt = tcc_parse_args(s, &argc, &argv, 1);

    if (n == 0) {
        if (opt == OPT_M32 || opt == OPT_M64)
            tcc_tool_cross(s, argv, opt); /* never returns */
        if (opt == OPT_AR)
            return tcc_tool_ar(s, argc, argv);
        if (opt == OPT_V)
            return 0;

        if (s->nb_files == 0)
            tcc_error("no input files");

        if (s->output_type == TCC_OUTPUT_PREPROCESS) {
            // if (s->outfile && 0!=strcmp("-",s->outfile)) {
            //     ppfp = fopen(s->outfile, "w");
            //     if (!ppfp)
            //         tcc_error("could not write '%s'", s->outfile);
            // }
        } else if (s->output_type == TCC_OUTPUT_OBJ && !s->option_r) {
            if (s->nb_libraries)
                tcc_error("cannot specify libraries with -c");
            if (s->nb_files > 1 && s->outfile)
                tcc_error("cannot specify output file with -c many files");
        }

    }

    set_environment(s);
    if (s->output_type == 0)
        s->output_type = TCC_OUTPUT_EXE;
    tcc_set_output_type(s, s->output_type);
    s->ppfp = ppfp;

    if ((s->output_type == TCC_OUTPUT_MEMORY
      || s->output_type == TCC_OUTPUT_PREPROCESS)
        && (s->dflag & 16)) { /* -dt option */
        if (t)
            s->dflag |= 32;
        s->run_test = ++t;
        if (n)
            --n;
    }

    /* compile or add each files or library */
    first_file = NULL, ret = 0;
    do {
        struct filespec *f = s->files[n];
        s->filetype = f->type;
        if (f->type & AFF_TYPE_LIB) {
            if (tcc_add_library_err(s, f->name) < 0)
                ret = 1;
        } else {
            if (1 == s->verbose)
                bench_printf("-> %s\n", f->name);
            if (!first_file)
                first_file = f->name;
            if (tcc_add_file(s, f->name) < 0)
                ret = 1;
        }
        done = ret || ++n >= s->nb_files;
    } while (!done && (s->output_type != TCC_OUTPUT_OBJ || s->option_r));

      end_time = uptime();

    if (s->run_test) {
        t = 0;
    } else if (s->output_type == TCC_OUTPUT_PREPROCESS) {
        ;
    } else if (0 == ret) {
        if (s->output_type == TCC_OUTPUT_MEMORY) {
#ifdef TCC_IS_NATIVE
            ret = tcc_run(s, argc, argv);
#endif
        } else {
            if (!s->outfile)
                s->outfile = default_outputfile(s, first_file);
            if (!s->just_deps && tcc_output_file(s, s->outfile))
                ret = 1;
            // else if (s->gen_deps)
            //     gen_makedeps(s, s->outfile, s->deps_outfile);
        }
    }

    if (done && 0 == t && 0 == ret && s->do_bench)
        tcc_print_stats(s, end_time - start_time);

    tcc_delete(s);
    if (!done)
        goto redo; /* compile more files with -c */
    if (t)
        goto redo; /* run more tests with -dt -run */

    // if (ppfp && ppfp != stdout)
    //     fclose(ppfp);
    bench_printf("time: %s ms\n", format_time(end_time - start_time));
    return ret;
}
