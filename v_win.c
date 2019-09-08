#define V_COMMIT_HASH "2644b9a"

#include <inttypes.h> // int64_t etc
#include <signal.h>
#include <stdarg.h> // for va_list
#include <stdio.h> // TODO remove all these includes, define all function signatures and types manually
#include <stdlib.h>
#include <string.h> // memcpy

#ifndef _WIN32
#include <ctype.h>
#include <locale.h> // tolower
#include <sys/time.h>
#include <unistd.h> // sleep
#endif

#ifdef __APPLE__
#include <execinfo.h> // backtrace and backtrace_symbols_fd
#include <libproc.h>  // proc_pidpath
#endif

#ifdef __linux__
#include <execinfo.h> // backtrace and backtrace_symbols_fd
#pragma weak backtrace
#pragma weak backtrace_symbols_fd
#endif

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h> // os__wait uses wait on nix
#endif

#define EMPTY_STRUCT_DECLARATION
#define OPTION_CAST(x) (x)

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// must be included after <windows.h>
#ifndef __TINYC__
#include <shellapi.h>
#endif

#include <direct.h> // _wgetcwd
#include <fcntl.h>  // _O_U8TEXT
#include <io.h>     // _waccess
//#include <WinSock2.h>
#ifdef _MSC_VER
// On MSVC these are the same (as long as /volatile:ms is passed)
#define _Atomic volatile

// MSVC cannot parse some things properly
//#undef EMPTY_STRUCT_DECLARATION
//#define EMPTY_STRUCT_DECLARATION void *____dummy_variable
#undef OPTION_CAST
#define OPTION_CAST(x)
#endif

void pthread_mutex_lock(HANDLE *m) { WaitForSingleObject(*m, INFINITE); }

void pthread_mutex_unlock(HANDLE *m) { ReleaseMutex(*m); }
#else
#include <pthread.h>
#endif

//================================== TYPEDEFS ================================*/

typedef int64_t i64;
typedef int16_t i16;
typedef int8_t i8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t byte;
typedef uint32_t rune;
typedef float f32;
typedef double f64;
typedef unsigned char *byteptr;
typedef int *intptr;
typedef void *voidptr;
typedef struct array array;
typedef struct map map;
typedef array array_string;
typedef array array_int;
typedef array array_byte;
typedef array array_f32;
typedef array array_f64;
typedef map map_int;
typedef map map_string;
#ifndef bool
typedef int bool;
#define true 1
#define false 0
#endif

//============================== HELPER C MACROS =============================*/

#define _PUSH(arr, val, tmp, tmp_typ)                                          \
  {                                                                            \
    tmp_typ tmp = (val);                                                       \
    array__push(arr, &tmp);                                                    \
  }
#define _PUSH_MANY(arr, val, tmp, tmp_typ)                                     \
  {                                                                            \
    tmp_typ tmp = (val);                                                       \
    array__push_many(arr, tmp.data, tmp.len);                                  \
  }
#define _IN(typ, val, arr) array_##typ##_contains(arr, val)
#define _IN_MAP(val, m) map__exists(m, val)
//#define ALLOC_INIT(type, ...) (type *)memdup((type[]){ __VA_ARGS__ },
//sizeof(type))

//================================== GLOBALS =================================*/
byteptr g_str_buf;
int load_so(byteptr);
void reload_so();
void init_consts();

int g_test_ok = 1;
/*================================== FNS =================================*/
#include <errno.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <math.h>
#include <time.h>
typedef struct array array;
typedef array array_string;
typedef array array_byte;
typedef array array_int;
typedef struct string string;
typedef struct ustring ustring;
typedef struct map map;
typedef struct mapnode mapnode;
typedef struct Option Option;
typedef struct strings__Builder strings__Builder;
typedef struct os__File os__File;
typedef struct os__FileInfo os__FileInfo;
typedef Option Option_string;
typedef array array_ustring;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef struct os__Result os__Result;
typedef Option Option_os__Result;
typedef voidptr HANDLE; // type alias name="HANDLE" parent=`voidptr`
typedef struct os__filetime os__filetime;
typedef struct os__win32finddata os__win32finddata;
typedef Option Option_string;
typedef struct time__Time time__Time;
typedef Option Option_int;
typedef struct CFlag CFlag;
typedef array array_CFlag;
typedef struct CGen CGen;
typedef array array_Type;
typedef struct DepGraphNode DepGraphNode;
typedef struct DepGraph DepGraph;
typedef array array_DepGraphNode;
typedef struct DepSet DepSet;
typedef struct Fn Fn;
typedef array array_Var;
typedef struct V V;
typedef struct Preferences Preferences;
typedef array array_FileImportTable;
typedef struct MsvcResult MsvcResult;
typedef voidptr RegKey; // type alias name="RegKey" parent=`voidptr`
typedef Option Option_string;
typedef struct WindowsKit WindowsKit;
typedef Option Option_WindowsKit;
typedef struct VsInstallation VsInstallation;
typedef Option Option_VsInstallation;
typedef Option Option_MsvcResult;
typedef struct Parser Parser;
typedef struct Repl Repl;
typedef struct Scanner Scanner;
typedef struct ScanRes ScanRes;
typedef struct Table Table;
typedef map map_Type;
typedef map map_Fn;
typedef array array_GenTable;
typedef struct GenTable GenTable;
typedef struct FileImportTable FileImportTable;
typedef struct Var Var;
typedef struct Type Type;
typedef array array_Fn;
typedef struct TypeNode TypeNode;
typedef array array_Token;
typedef Option Option_string;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__Result;
typedef Option Option_string;
typedef Option Option_int;
typedef map map_DepGraphNode;
typedef map map_DepSet;
typedef int BuildMode;
typedef int OS;
typedef int Pass;
typedef Option Option_string;
typedef Option Option_WindowsKit;
typedef Option Option_VsInstallation;
typedef Option Option_MsvcResult;
typedef int AccessMod;
typedef int TypeCategory;
typedef int Token;
struct string {
  byte *str;
  int len;
};

struct array {
  void *data;
  int len;
  int cap;
  int element_size;
};

struct map {
  int element_size;
  mapnode *root;
  int size;
};

struct Option {
  byte data[255];
  string error;
  bool ok;
};

//----
struct CFlag {
  string os;
  string name;
  string value;
};

struct MsvcResult {
  string full_cl_exe_path;
  string exe_path;
  string um_lib_path;
  string ucrt_lib_path;
  string vs_lib_path;
  string um_include_path;
  string ucrt_include_path;
  string vs_include_path;
  string shared_include_path;
};

struct WindowsKit {
  string um_lib_path;
  string ucrt_lib_path;
  string um_include_path;
  string ucrt_include_path;
  string shared_include_path;
};

struct VsInstallation {
  string include_path;
  string lib_path;
  string exe_path;
};

struct os__File {
  FILE *cfile;
};

struct CGen {
  os__File out;
  string out_path;
  array_string thread_fns;
  bool is_user;
  array_string lines;
  array_string typedefs;
  array_string type_aliases;
  array_string includes;
  array_string thread_args;
  array_string consts;
  array_string fns;
  array_string so_fns;
  array_string consts_init;
  Pass pass;
  bool nogen;
  string tmp_line;
  string cur_line;
  string prev_line;
  bool is_tmp;
  string fn_main;
  string stash;
  string file;
  int line;
  bool line_directives;
  int cut_pos;
};

struct DepGraphNode {
  string name;
  array_string deps;
  string last_cycle;
};

struct DepGraph {
  bool acyclic;
  array_DepGraphNode nodes;
};

struct DepSet {
  array_string items;
};

struct Fn {
  string name;
  string mod;
  array_Var local_vars;
  int var_idx;
  array_Var args;
  bool is_interface;
  int scope_level;
  string typ;
  bool is_c;
  string receiver_typ;
  bool is_public;
  bool is_method;
  bool returns_error;
  bool is_decl;
  array_string defer_text;
};

struct FileImportTable {
  string module_name;
  string file_path;
  map_string imports;
};

struct GenTable {
  string fn_name;
  array_string types;
};

struct Preferences {
  BuildMode build_mode;
  bool nofmt;
  bool is_test;
  bool is_script;
  bool is_live;
  bool is_so;
  bool is_prof;
  bool translated;
  bool is_prod;
  bool is_verbose;
  bool obfuscate;
  bool is_repl;
  bool is_run;
  bool show_c_cmd;
  bool sanitize;
  bool is_debuggable;
  bool is_debug;
  bool no_auto_free;
  string cflags;
  string ccompiler;
};

struct Repl {
  int indent;
  bool in_func;
  array_string lines;
  array_string temp_lines;
  array_string functions_name;
  array_string functions;
};

struct ScanRes {
  Token tok;
  string lit;
};

struct V {
  OS os;
  string out_name_c;
  array_string files;
  string dir;
  Table *table;
  CGen *cgen;
  Preferences *pref;
  string lang_dir;
  string out_name;
  string vroot;
  string mod;
};

struct Table {
  map_Type typesmap;
  array_Var consts;
  map_Fn fns;
  array_GenTable generic_fns;
  map_int obf_ids;
  array_string modules;
  array_string imports;
  array_FileImportTable file_imports;
  array_CFlag cflags;
  int fn_cnt;
  bool obfuscate;
};

struct Var {
  string typ;
  string name;
  bool is_arg;
  bool is_const;
  array_Var args;
  string attr;
  bool is_mut;
  bool is_alloc;
  bool ptr;
  bool ref;
  string parent_fn;
  string mod;
  int line_nr;
  AccessMod access_mod;
  bool is_global;
  bool is_used;
  bool is_changed;
  int scope_level;
};

struct mapnode {
  mapnode *left;
  mapnode *right;
  bool is_empty;
  string key;
  void *val;
};

struct os__FileInfo {
  string name;
  int size;
};

struct os__Result {
  int exit_code;
  string output;
};

struct os__filetime {
  u32 dwLowDateTime;
  u32 dwHighDateTime;
};

struct strings__Builder {
  array_byte buf;
  int len;
};

struct time__Time {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int uni;
};

struct ustring {
  string s;
  array_int runes;
  int len;
};

struct Parser {
  string file_path;
  string file_name;
  string file_platform;
  string file_pcguard;
  V *v;
  Scanner *scanner;
  int token_idx;
  Token tok;
  Token prev_tok;
  Token prev_tok2;
  string lit;
  CGen *cgen;
  Table *table;
  FileImportTable *import_table;
  Pass pass;
  OS os;
  string mod;
  bool inside_const;
  Var expr_var;
  bool has_immutable_field;
  Var first_immutable_field;
  string assigned_type;
  string expected_type;
  int tmp_cnt;
  bool is_script;
  Preferences *pref;
  bool builtin_mod;
  array_string vh_lines;
  bool inside_if_expr;
  bool inside_unwrapping_match_statement;
  bool is_struct_init;
  int if_expr_cnt;
  int for_expr_cnt;
  bool ptr_cast;
  bool calling_c;
  Fn *cur_fn;
  bool returns;
  string vroot;
  bool is_c_struct_init;
  bool is_empty_c_struct_init;
  bool is_c_fn_call;
  bool can_chash;
  string attr;
  bool v_script;
  string var_decl_name;
  bool building_v;
  bool is_alloc;
  string cur_gen_type;
  bool is_vweb;
  bool is_sql;
  int sql_i;
  array_string sql_params;
  array_string sql_types;
};

struct Scanner {
  string file_path;
  string text;
  int pos;
  int line_nr;
  bool inside_string;
  bool dollar_start;
  bool dollar_end;
  bool debug;
  string line_comment;
  bool started;
  strings__Builder fmt_out;
  int fmt_indent;
  bool fmt_line_empty;
  Token prev_tok;
  string fn_name;
};

struct Type {
  string mod;
  string name;
  TypeCategory cat;
  array_Var fields;
  array_Fn methods;
  string parent;
  Fn func;
  bool is_c;
  array_string enum_vals;
  array_string gen_types;
  bool is_placeholder;
  bool gen_str;
};

struct os__win32finddata {
  u32 dwFileAttributes;
  os__filetime ftCreationTime;
  os__filetime ftLastAccessTime;
  os__filetime ftLastWriteTime;
  u32 nFileSizeHigh;
  u32 nFileSizeLow;
  u32 dwReserved0;
  u32 dwReserved1;
  u16 cFileName[260];
  u16 cAlternateFileName[14];
  u32 dwFileType;
  u32 dwCreatorType;
  u16 wFinderFlags;
};

struct TypeNode {
  TypeNode *next;
  Type typ;
};

string _STR(const char *, ...);

string _STR_TMP(const char *, ...);

array new_array(int mylen, int cap, int elm_size);
array _make(int len, int cap, int elm_size);
array new_array_from_c_array(int len, int cap, int elm_size, void *c_array);
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size,
                                      void *c_array);
array array_repeat(void *val, int nr_repeats, int elm_size);
void array_sort_with_compare(array *a, void *compare);
void array_insert(array *a, int i, void *val);
void array_prepend(array *a, void *val);
void array_delete(array *a, int idx);
void *array__get(array a, int i);
void *array_first(array a);
void *array_last(array a);
array array_left(array s, int n);
array array_right(array s, int n);
array array_slice(array s, int start, int _end);
void array_set(array *a, int idx, void *val);
void array__push(array *arr, void *val);
void array__push_many(array *arr, void *val, int size);
array array_reverse(array a);
array array_clone(array a);
void v_array_free(array a);
string array_string_str(array_string a);
string array_byte_hex(array_byte b);
int copy(array_byte dst, array_byte src);
int compare_ints(int *a, int *b);
void array_int_sort(array_int *a);
void todo();
string tos(byte *s, int len);
string tos_clone(byte *s);
string tos2(byte *s);
string string_clone(string a);
string string_replace(string s, string rep, string with);
int v_string_int(string s);
i64 string_i64(string s);
f32 string_f32(string s);
f64 string_f64(string s);
u32 string_u32(string s);
u64 string_u64(string s);
bool string_eq(string s, string a);
bool string_ne(string s, string a);
bool string_lt(string s, string a);
bool string_le(string s, string a);
bool string_gt(string s, string a);
bool string_ge(string s, string a);
string string_add(string s, string a);
array_string string_split(string s, string delim);
array_string string_split_single(string s, byte delim);
array_string string_split_into_lines(string s);
string string_left(string s, int n);
string string_right(string s, int n);
string string_substr(string s, int start, int end);
int string_index(string s, string p);
int string_index_any(string s, string chars);
int string_last_index(string s, string p);
int string_index_after(string s, string p, int start);
int string_count(string s, string substr);
bool string_contains(string s, string p);
bool string_starts_with(string s, string p);
bool string_ends_with(string s, string p);
string string_to_lower(string s);
string string_to_upper(string s);
string string_capitalize(string s);
string string_title(string s);
string string_find_between(string s, string start, string end);
bool array_string_contains(array_string ar, string val);
bool array_int_contains(array_int ar, int val);
bool is_space(byte c);
bool byte_is_space(byte c);
string string_trim_space(string s);
string string_trim(string s, string cutset);
string string_trim_left(string s, string cutset);
string string_trim_right(string s, string cutset);
int compare_strings(string *a, string *b);
int compare_strings_by_len(string *a, string *b);
int compare_lower_strings(string *a, string *b);
void array_string_sort(array_string *s);
void array_string_sort_ignore_case(array_string *s);
void array_string_sort_by_len(array_string *s);
ustring string_ustring(string s);
ustring string_ustring_tmp(string s);
string ustring_substr(ustring u, int _start, int _end);
string ustring_left(ustring u, int pos);
string ustring_right(ustring u, int pos);
byte string_at(string s, int idx);
string ustring_at(ustring u, int idx);
void v_ustring_free(ustring u);
bool byte_is_digit(byte c);
bool byte_is_hex_digit(byte c);
bool byte_is_oct_digit(byte c);
bool byte_is_letter(byte c);
void v_string_free(string s);
string string_all_before(string s, string dot);
string string_all_before_last(string s, string dot);
string string_all_after(string s, string dot);
string array_string_join(array_string a, string del);
string array_string_join_lines(array_string s);
string string_reverse(string s);
string string_limit(string s, int max);
bool byte_is_white(byte c);
int string_hash(string s);
array_byte string_bytes(string s);
void v_exit(int code);
bool isnil(void *v);
void on_panic(int (*f)(int /*FFF*/));
void print_backtrace_skipping_top_frames(int skipframes);
void print_backtrace();
void _panic_debug(int line_no, string file, string mod, string fn_name,
                  string s);
void v_panic(string s);
void println(string s);
void eprintln(string s);
void print(string s);
byte *v_malloc(int n);
byte *v_calloc(int n);
void v_free(void *ptr);
void *memdup(void *src, int sz);
string f64_str(f64 d);
string f32_str(f32 d);
string ptr_str(void *ptr);
bool f64_eq(f64 a, f64 b);
string int_str(int nn);
string u32_str(u32 nn);
string i64_str(i64 nn);
string u64_str(u64 nn);
string bool_str(bool b);
string int_hex(int n);
string i64_hex(i64 n);
bool array_byte_contains(array_byte a, byte val);
string rune_str(rune c);
string byte_str(byte c);
bool byte_is_capital(byte c);
array_byte array_byte_clone(array_byte b);
int utf8_char_len(byte b);
string utf32_to_str(u32 code);
string utf32_to_str_no_malloc(u32 code, void *buf);
int string_utf32_code(string _rune);
u16 *string_to_wide(string _str);
string string_from_wide(u16 *_wstr);
string string_from_wide2(u16 *_wstr, int len);
map new_map(int cap, int elm_size);
map new_map_init(int cap, int elm_size, string *keys, void *vals);
mapnode *new_node(string key, void *val, int element_size);
void map_insert(map *m, mapnode *n, string key, void *val);
bool mapnode_find(mapnode *n, string key, void *out, int element_size);
bool mapnode_find2(mapnode *n, string key, int element_size);
void map__set(map *m, string key, void *val);
int preorder_keys(mapnode *node, array_string *keys, int key_i);
array_string map_keys(map *m);
bool map_get(map m, string key, void *out);
void mapnode_delete(mapnode *n, string key, int element_size);
void map_delete(map *m, string key);
bool map_exists(map m, string key);
bool map__exists(map m, string key);
void map_print(map m);
void v_map_free(map m);
string map_string_str(map_string m);
Option opt_ok(void *data, int size);
Option v_error(string s);
strings__Builder strings__new_builder(int initial_size);
void strings__Builder_write(strings__Builder *b, string s);
void strings__Builder_writeln(strings__Builder *b, string s);
string strings__Builder_str(strings__Builder b);
void strings__Builder_cut(strings__Builder *b, int n);
void strings__Builder_free(strings__Builder *b);
string strings__repeat(byte c, int n);
array_string os__init_os_args(int argc, byteptr *argv);
array_string os__parse_windows_cmd_line(byte *cmd);
Option_string os__read_file(string path);
int os__file_size(string path);
void os__mv(string old, string new);
array_string os__read_lines(string path);
array_ustring os__read_ulines(string path);
Option_os__File os__open(string path);
Option_os__File os__create(string path);
Option_os__File os__open_append(string path);
void os__File_write(os__File f, string s);
void os__File_write_bytes(os__File f, void *data, int size);
void os__File_write_bytes_at(os__File f, void *data, int size, int pos);
void os__File_writeln(os__File f, string s);
void os__File_flush(os__File f);
void os__File_close(os__File f);
FILE *os__popen(string path);
int os__pclose(FILE *f);
Option_os__Result os__exec(string cmd);
int os__system(string cmd);
string os__getenv(string key);
int os__setenv(string name, string value, bool overwrite);
int os__unsetenv(string name);
bool os__file_exists(string _path);
void os__rm(string path);
void os__rmdir(string path);
void os__print_c_errno();
string os__ext(string path);
string os__dir(string path);
string os__path_sans_ext(string path);
string os__basedir(string path);
string os__filename(string path);
string os__get_line();
string os__get_raw_line();
array_string os__get_lines();
string os__get_lines_joined();
string os__user_os();
string os__home_dir();
void os__write_file(string path, string text);
void os__clear();
void os__on_segfault(void *f);
string os__executable();
bool os__is_dir(string path);
void os__chdir(string path);
string os__getwd();
string os__realpath(string fpath);
array_string os__walk_ext(string path, string ext);
void os__signal(int signum, void *handler);
int os__fork();
int os__wait();
int os__file_last_mod_unix(string path);
void os__log(string s);
void os__flush_stdout();
void os__print_backtrace();
array_string os__ls(string path);
bool os__dir_exists(string path);
void os__mkdir(string path);
HANDLE os__get_file_handle(string path);
Option_string os__get_module_filename(HANDLE handle);
void *os__ptr_win_get_error_msg(u32 code);
string os__get_error_msg(int code);
f64 math__abs(f64 a);
f64 math__acos(f64 a);
f64 math__asin(f64 a);
f64 math__atan(f64 a);
f64 math__atan2(f64 a, f64 b);
f64 math__cbrt(f64 a);
int math__ceil(f64 a);
f64 math__cos(f64 a);
f64 math__cosh(f64 a);
f64 math__degrees(f64 radians);
f64 math__exp(f64 a);
array_int math__digits(int _n, int base);
f64 math__erf(f64 a);
f64 math__erfc(f64 a);
f64 math__exp2(f64 a);
f64 math__floor(f64 a);
f64 math__fmod(f64 a, f64 b);
f64 math__gamma(f64 a);
i64 math__gcd(i64 a_, i64 b_);
f64 math__hypot(f64 a, f64 b);
i64 math__lcm(i64 a, i64 b);
f64 math__log(f64 a);
f64 math__log2(f64 a);
f64 math__log10(f64 a);
f64 math__log_gamma(f64 a);
f64 math__log_n(f64 a, f64 b);
f64 math__max(f64 a, f64 b);
f64 math__min(f64 a, f64 b);
f64 math__pow(f64 a, f64 b);
f64 math__radians(f64 degrees);
f64 math__round(f64 f);
f64 math__sin(f64 a);
f64 math__sinh(f64 a);
f64 math__sqrt(f64 a);
f64 math__tan(f64 a);
f64 math__tanh(f64 a);
f64 math__trunc(f64 a);
void rand__seed(int s);
int rand__next(int max);
string term___format(string msg, string open, string close);
string term___format_rgb(int r, int g, int b, string msg, string open,
                         string close);
string term__rgb(int r, int g, int b, string msg);
string term__bg_rgb(int r, int g, int b, string msg);
string term__hex(int hex, string msg);
string term__bg_hex(int hex, string msg);
string term__bg_black(string msg);
string term__bright_bg_black(string msg);
string term__bg_blue(string msg);
string term__bright_bg_blue(string msg);
string term__bg_cyan(string msg);
string term__bright_bg_cyan(string msg);
string term__bg_green(string msg);
string term__bright_bg_green(string msg);
string term__bg_magenta(string msg);
string term__bright_bg_magenta(string msg);
string term__bg_red(string msg);
string term__bright_bg_red(string msg);
string term__bg_white(string msg);
string term__bright_bg_white(string msg);
string term__bg_yellow(string msg);
string term__bright_bg_yellow(string msg);
string term__black(string msg);
string term__bright_black(string msg);
string term__blue(string msg);
string term__bright_blue(string msg);
string term__bold(string msg);
string term__cyan(string msg);
string term__bright_cyan(string msg);
string term__dim(string msg);
string term__green(string msg);
string term__bright_green(string msg);
string term__gray(string msg);
string term__hidden(string msg);
string term__italic(string msg);
string term__inverse(string msg);
string term__magenta(string msg);
string term__bright_magenta(string msg);
string term__reset(string msg);
string term__red(string msg);
string term__bright_red(string msg);
string term__strikethrough(string msg);
string term__underline(string msg);
string term__white(string msg);
string term__bright_white(string msg);
string term__yellow(string msg);
string term__bright_yellow(string msg);
string term__format(string msg, string open, string close);
string term__format_rgb(int r, int g, int b, string msg, string open,
                        string close);
void term__set_cursor_position(int x, int y);
void term__move(int n, string direction);
void term__cursor_up(int n);
void term__cursor_down(int n);
void term__cursor_forward(int n);
void term__cursor_back(int n);
void term__erase_display(string t);
void term__erase_toend();
void term__erase_tobeg();
void term__erase_clear();
void term__erase_del_clear();
void term__erase_line(string t);
void term__erase_line_toend();
void term__erase_line_tobeg();
void term__erase_line_clear();
void term__show_cursor();
void term__hide_cursor();
void time__remove_me_when_c_bug_is_fixed();
time__Time time__now();
time__Time time__random();
time__Time time__unix(int abs);
time__Time time__convert_ctime(struct /*TM*/ tm t);
string time__Time_format_ss(time__Time t);
string time__Time_format(time__Time t);
string time__Time_smonth(time__Time t);
string time__Time_hhmm(time__Time t);
string time__Time_hhmm12(time__Time t);
string time__Time_hhmmss(time__Time t);
string time__Time_ymmdd(time__Time t);
string time__Time_md(time__Time t);
string time__Time_clean(time__Time t);
string time__Time_clean12(time__Time t);
time__Time time__parse(string s);
time__Time time__new_time(time__Time t);
int time__Time_calc_unix(time__Time *t);
time__Time time__Time_add_seconds(time__Time t, int seconds);
int time__since(time__Time t);
string time__Time_relative(time__Time t);
int time__day_of_week(int y, int m, int d);
int time__Time_day_of_week(time__Time t);
string time__Time_weekday_str(time__Time t);
i64 time__ticks();
void time__sleep(int seconds);
void time__usleep(int n);
void time__sleep_ms(int n);
bool time__is_leap_year(int year);
Option_int time__days_in_month(int month, int year);
string vweb_dot_tmpl__compile_template(string path);
void V_cc(V *v);
void V_cc_windows_cross(V *c);
void V_build_thirdparty_obj_files(V c);
string find_c_compiler();
string find_c_compiler_default();
string find_c_compiler_thirdparty_options();
array_CFlag V_get_os_cflags(V v);
string CFlag_format(CFlag *cf);
bool Table_has_cflag(Table *table, CFlag cflag);
void Table_parse_cflag(Table *table, string cflag);
CGen *new_cgen(string out_name_c);
void CGen_genln(CGen *g, string s);
void CGen_gen(CGen *g, string s);
void CGen_resetln(CGen *g, string s);
void CGen_save(CGen *g);
void CGen_start_tmp(CGen *g);
string CGen_end_tmp(CGen *g);
int CGen_add_placeholder(CGen *g);
void CGen_start_cut(CGen *g);
string CGen_cut(CGen *g);
void CGen_set_placeholder(CGen *g, int pos, string val);
void CGen_insert_before(CGen *g, string val);
void CGen_register_thread_fn(CGen *g, string wrapper_name, string wrapper_text,
                             string struct_text);
string V_prof_counters(V *c);
string Parser_print_prof_counters(Parser *p);
void Parser_gen_typedef(Parser *p, string s);
void Parser_gen_type_alias(Parser *p, string s);
void CGen_add_to_main(CGen *g, string s);
void build_thirdparty_obj_file(string path);
string os_name_to_ifdef(string name);
string platform_postfix_to_ifdefguard(string name);
string V_c_type_definitions(V *v);
string types_to_c(array_Type types, Table *table);
array_Type sort_structs(array_Type types);
void Parser_comp_time(Parser *p);
void Parser_chash(Parser *p);
void Parser_comptime_method_call(Parser *p, Type typ);
void Parser_gen_array_str(Parser *p, Type typ);
void Parser_parse_t(Parser *p);
void DepSet_add(DepSet *dset, string item);
DepSet DepSet_diff(DepSet *dset, DepSet otherset);
int DepSet_size(DepSet *dset);
DepGraph *new_dep_graph();
void DepGraph_add(DepGraph *graph, string mod, array_string deps);
DepGraph *DepGraph_resolve(DepGraph *graph);
DepGraphNode DepGraph_last_node(DepGraph *graph);
string DepGraph_last_cycle(DepGraph *graph);
void DepGraph_display(DepGraph *graph);
Var Fn_find_var(Fn *f, string name);
void Fn_open_scope(Fn *f);
void Fn_close_scope(Fn *f);
void Fn_mark_var_used(Fn *f, Var v);
void Fn_mark_var_changed(Fn *f, Var v);
bool Fn_known_var(Fn *f, string name);
void Fn_register_var(Fn *f, Var v);
void Fn_clear_vars(Fn *f);
bool Parser_is_sig(Parser *p);
Fn *new_fn(string mod, bool is_public);
void Parser_fn_decl(Parser *p);
void Parser_check_unused_variables(Parser *p);
void Parser_async_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                          string receiver_type);
void Parser_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                    string receiver_type);
void Parser_fn_args(Parser *p, Fn *f);
Fn *Parser_fn_call_args(Parser *p, Fn *f);
string Fn_typ_str(Fn f);
string Fn_str_args(Fn *f, Table *table);
void Parser_gen_json_for_type(Parser *p, Type typ);
bool is_js_prim(string typ);
string Parser_decode_array(Parser *p, string array_type);
string js_enc_name(string typ);
string js_dec_name(string typ);
string Parser_encode_array(Parser *p, string array_type);
array_string V_generate_hotcode_reloading_compiler_flags(V *v);
void V_generate_hotcode_reloading_declarations(V *v);
void V_generate_hotcode_reloading_code(V *v);
void V_compile(V *v);
void V_generate_main(V *v);
string final_target_out_name(string out_name);
void V_run_compiled_executable_and_exit(V v);
array_string V_v_files_from_dir(V *v, string dir);
void V_add_v_files_to_compile(V *v);
string get_arg(string joined_args, string arg, string def);
string get_all_after(string joined_args, string arg, string def);
string V_module_path(V *v, string mod);
void V_log(V *v, string s);
V *new_v(array_string args);
array_string env_vflags_and_os_args();
void update_v();
void test_v();
void create_symlink();
void cerror(string s);
void DepGraph_from_import_tables(DepGraph *graph,
                                 array_FileImportTable import_tables);
array_string DepGraph_imports(DepGraph *graph);
string V_find_module_path(V *v, string mod);
Option_string find_windows_kit_internal(RegKey key, array_string versions);
Option_WindowsKit find_windows_kit_root();
Option_VsInstallation find_vs();
Option_MsvcResult find_msvc();
void V_cc_msvc(V *v);
void build_thirdparty_obj_file_with_msvc(string path);
Parser V_new_parser(V *v, string path);
void Parser_set_current_fn(Parser *p, Fn *f);
void Parser_next(Parser *p);
void Parser_log(Parser *p, string s);
void Parser_parse(Parser *p, Pass pass);
void Parser_imports(Parser *p);
void Parser_import_statement(Parser *p);
void Parser_const_decl(Parser *p);
void Parser_type_decl(Parser *p);
Fn *Parser_interface_method(Parser *p, string field_name, string receiver);
TypeCategory key_to_type_cat(Token tok);
void Parser_struct_decl(Parser *p);
void Parser_enum_decl(Parser *p, string _enum_name);
string Parser_check_name(Parser *p);
string Parser_check_string(Parser *p);
string Parser_strtok(Parser *p);
void Parser_check_space(Parser *p, Token expected);
void Parser_check(Parser *p, Token expected);
void Parser_warn(Parser *p, string s);
void Parser_error(Parser *p, string s);
bool Parser_first_pass(Parser *p);
string Parser_get_type(Parser *p);
void Parser_print_tok(Parser *p);
string Parser_statements(Parser *p);
string Parser_statements_no_rcbr(Parser *p);
void Parser_close_scope(Parser *p);
void Parser_genln(Parser *p, string s);
void Parser_gen(Parser *p, string s);
void Parser_vh_genln(Parser *p, string s);
string Parser_statement(Parser *p, bool add_semi);
void Parser_assign_statement(Parser *p, Var v, int ph, bool is_map);
void Parser_var_decl(Parser *p);
string Parser_bool_expression(Parser *p);
string Parser_bterm(Parser *p);
string Parser_name_expr(Parser *p);
string Parser_var_expr(Parser *p, Var v);
bool Parser_fileis(Parser *p, string s);
string Parser_dot(Parser *p, string str_typ, int method_ph);
string Parser_index_expr(Parser *p, string typ_, int fn_ph);
string Parser_expression(Parser *p);
string Parser_term(Parser *p);
string Parser_unary(Parser *p);
string Parser_factor(Parser *p);
string Parser_assoc(Parser *p);
void Parser_char_expr(Parser *p);
string format_str(string _str);
void Parser_string_expr(Parser *p);
string Parser_map_init(Parser *p);
string Parser_array_init(Parser *p);
string Parser_struct_init(Parser *p, string typ, bool is_c_struct_init);
string Parser_cast(Parser *p, string typ);
string Parser_get_tmp(Parser *p);
int Parser_get_tmp_counter(Parser *p);
string Parser_if_st(Parser *p, bool is_expr, int elif_depth);
void Parser_for_st(Parser *p);
void Parser_switch_statement(Parser *p);
string Parser_match_statement(Parser *p, bool is_expr);
void Parser_assert_statement(Parser *p);
void Parser_return_st(Parser *p);
string prepend_mod(string mod, string name);
string Parser_prepend_mod(Parser *p, string name);
void Parser_go_statement(Parser *p);
void Parser_register_var(Parser *p, Var v);
string Parser_js_decode(Parser *p);
void Parser_attribute(Parser *p);
void Parser_defer_st(Parser *p);
Type Parser_get_type2(Parser *p);
string sql_params2params_gen(array_string sql_params, array_string sql_types,
                             string qprefix);
string Parser_select_query(Parser *p, int fn_ph);
void Parser_insert_query(Parser *p, int fn_ph);
bool Repl_checks(Repl *r, string line);
bool Repl_function_call(Repl *r, string line);
void repl_help();
array_string run_repl();
Scanner *new_scanner(string file_path);
ScanRes scan_res(Token tok, string lit);
string Scanner_ident_name(Scanner *s);
string Scanner_ident_hex_number(Scanner *s);
string Scanner_ident_oct_number(Scanner *s);
string Scanner_ident_dec_number(Scanner *s);
string Scanner_ident_number(Scanner *s);
bool Scanner_has_gone_over_line_end(Scanner s);
void Scanner_skip_whitespace(Scanner *s);
ScanRes Scanner_scan(Scanner *s);
int Scanner_find_current_line_start_position(Scanner *s);
int Scanner_current_column(Scanner *s);
void Scanner_error(Scanner *s, string msg);
int Scanner_count_symbol_before(Scanner s, int p, byte sym);
string Scanner_ident_string(Scanner *s);
string Scanner_ident_char(Scanner *s);
Token Scanner_peek(Scanner *s);
bool Scanner_expect(Scanner *s, string want, int start_pos);
void Scanner_debug_tokens(Scanner *s);
bool is_name_char(byte c);
bool is_nl(byte c);
int Scanner_get_opening_bracket(Scanner *s);
void Scanner_create_type_string(Scanner *s, Type T, string name);
bool contains_capital(string s);
bool good_type_name(string s);
string Type_str(Type t);
string Fn_str(Fn f);
string Table_debug_fns(Table *t);
bool is_number_type(string typ);
bool is_float_type(string typ);
bool is_primitive_type(string typ);
Table *new_table(bool obfuscate);
string Table_var_cgen_name(Table *t, string name);
void Table_register_module(Table *t, string mod);
void Parser_register_array(Parser *p, string typ);
void Parser_register_map(Parser *p, string typ);
bool Table_known_mod(Table *table, string mod);
void Table_register_const(Table *t, string name, string typ, string mod);
void Parser_register_global(Parser *p, string name, string typ);
void Table_register_fn(Table *t, Fn new_fn);
bool Table_known_type(Table *table, string typ_);
bool Table_known_type_fast(Table *table, Type *t);
Fn Table_find_fn(Table *t, string name);
bool Table_known_fn(Table *t, string name);
bool Table_known_const(Table *t, string name);
void Table_register_type(Table *t, string typ);
void Parser_register_type_with_parent(Parser *p, string strtyp, string parent);
void Table_register_type_with_parent(Table *t, string typ, string parent);
void Table_register_type2(Table *t, Type typ);
void Table_rewrite_type(Table *t, Type typ);
void Table_add_field(Table *table, string type_name, string field_name,
                     string field_type, bool is_mut, string attr,
                     AccessMod access_mod);
bool Type_has_field(Type *t, string name);
bool Type_has_enum_val(Type *t, string name);
Var Type_find_field(Type *t, string name);
bool Table_type_has_field(Table *table, Type *typ, string name);
Var Table_find_field(Table *table, Type *typ, string name);
void Table_add_method(Table *table, string type_name, Fn f);
bool Type_has_method(Type *t, string name);
bool Table_type_has_method(Table *table, Type *typ, string name);
Fn Table_find_method(Table *table, Type *typ, string name);
Fn Type_find_method(Type *t, string name);
Type Parser_find_type(Parser *p, string name);
Type Table_find_type(Table *t, string name_);
bool Parser__check_types(Parser *p, string got_, string expected_, bool throw);
bool Parser_check_types(Parser *p, string got, string expected);
bool Parser_check_types_no_throw(Parser *p, string got, string expected);
bool Parser_satisfies_interface(Parser *p, string interface_name, string _typ,
                                bool throw);
string type_default(string typ);
bool Table_is_interface(Table *table, string name);
bool Table_main_exists(Table *t);
Var Table_find_const(Table *t, string name);
string Table_cgen_name(Table *table, Fn *f);
string Table_cgen_name_type_pair(Table *table, string name, string typ);
bool is_valid_int_const(string val, string typ);
void Table_register_generic_fn(Table *t, string fn_name);
array_string Table_fn_gen_types(Table *t, string fn_name);
void Table_register_generic_fn_type(Table *t, string fn_name, string typ);
string Parser_typ_to_fmt(Parser *p, string typ, int level);
bool is_compile_time_const(string s_);
string Table_qualify_module(Table *table, string mod, string file_path);
FileImportTable *new_file_import_table(string file_path);
bool FileImportTable_known_import(FileImportTable *fit, string mod);
void FileImportTable_register_import(FileImportTable *fit, string mod);
void FileImportTable_register_alias(FileImportTable *fit, string alias,
                                    string mod);
bool FileImportTable_known_alias(FileImportTable *fit, string alias);
bool FileImportTable_is_aliased(FileImportTable *fit, string mod);
string FileImportTable_resolve_alias(FileImportTable *fit, string alias);
bool Type_contains_field_type(Type *t, string typ);
map_int build_keys();
array_string build_token_str();
Token key_to_token(string key);
bool is_key(string key);
string Token_str(Token t);
bool Token_is_decl(Token t);
bool Token_is_assign(Token t);
bool array_Token_contains(array_Token t, Token val);
void Scanner_fgen(Scanner *scanner, string s_);
void Scanner_fgenln(Scanner *scanner, string s_);
void Parser_fgen(Parser *p, string s);
void Parser_fspace(Parser *p);
void Parser_fgenln(Parser *p, string s);
Token Parser_peek(Parser *p);
void Parser_fmt_inc(Parser *p);
void Parser_fmt_dec(Parser *p);
array_int g_ustring_runes; // global
i64 total_m = 0;           // global
#define builtin__CP_UTF8 65001
#define os__SUCCESS 0
#define os__ERROR_INSUFFICIENT_BUFFER 130
#define os__FILE_SHARE_READ 1
#define os__FILE_SHARE_WRITE 2
#define os__FILE_SHARE_DELETE 4
#define os__FILE_NOTIFY_CHANGE_FILE_NAME 1
#define os__FILE_NOTIFY_CHANGE_DIR_NAME 2
#define os__FILE_NOTIFY_CHANGE_ATTRIBUTES 4
#define os__FILE_NOTIFY_CHANGE_SIZE 8
#define os__FILE_NOTIFY_CHANGE_LAST_WRITE 16
#define os__FILE_NOTIFY_CHANGE_LAST_ACCESS 32
#define os__FILE_NOTIFY_CHANGE_CREATION 64
#define os__FILE_NOTIFY_CHANGE_SECURITY 128
#define os__FILE_ACTION_ADDED 1
#define os__FILE_ACTION_REMOVED 2
#define os__FILE_ACTION_MODIFIED 3
#define os__FILE_ACTION_RENAMED_OLD_NAME 4
#define os__FILE_ACTION_RENAMED_NEW_NAME 5
int os__FILE_ATTR_READONLY;
int os__FILE_ATTR_HIDDEN;
int os__FILE_ATTR_SYSTEM;
int os__FILE_ATTR_DIRECTORY;
int os__FILE_ATTR_ARCHIVE;
int os__FILE_ATTR_DEVICE;
int os__FILE_ATTR_NORMAL;
int os__FILE_ATTR_TEMPORARY;
int os__FILE_ATTR_SPARSE_FILE;
int os__FILE_ATTR_REPARSE_POINT;
int os__FILE_ATTR_COMPRESSED;
int os__FILE_ATTR_OFFLINE;
int os__FILE_ATTR_NOT_CONTENT_INDEXED;
int os__FILE_ATTR_ENCRYPTED;
int os__FILE_ATTR_INTEGRITY_STREAM;
int os__FILE_ATTR_VIRTUAL;
int os__FILE_ATTR_NO_SCRUB_DATA;
int os__FILE_TYPE_DISK;
int os__FILE_TYPE_CHAR;
int os__FILE_TYPE_PIPE;
int os__FILE_TYPE_UNKNOWN;
int os__FILE_INVALID_FILE_ID;
#define os__O_RDONLY 1
#define os__O_WRONLY 2
#define os__O_RDWR 3
#define os__O_APPEND 8
#define os__O_CREATE 16
#define os__O_EXCL 32
#define os__O_SYNC 64
#define os__O_TRUNC 128
int os__S_IFMT;
int os__S_IFDIR;
int os__INVALID_HANDLE_VALUE;
int os__STD_INPUT_HANDLE;
int os__STD_OUTPUT_HANDLE;
int os__STD_ERROR_HANDLE;
int os__ENABLE_ECHO_INPUT;
int os__ENABLE_EXTENDED_FLAGS;
int os__ENABLE_INSERT_MODE;
int os__ENABLE_LINE_INPUT;
int os__ENABLE_MOUSE_INPUT;
int os__ENABLE_PROCESSED_INPUT;
int os__ENABLE_QUICK_EDIT_MODE;
int os__ENABLE_WINDOW_INPUT;
int os__ENABLE_VIRTUAL_TERMINAL_INPUT;
int os__ENABLE_PROCESSED_OUTPUT;
int os__ENABLE_WRAP_AT_EOL_OUTPUT;
int os__ENABLE_VIRTUAL_TERMINAL_PROCESSING;
int os__DISABLE_NEWLINE_AUTO_RETURN;
int os__ENABLE_LVB_GRID_WORLDWIDE;
array_string os__args;
#define os__MAX_PATH 4096
string os__PathSeparator;
int os__FORMAT_MESSAGE_ALLOCATE_BUFFER;
int os__FORMAT_MESSAGE_ARGUMENT_ARRAY;
int os__FORMAT_MESSAGE_FROM_HMODULE;
int os__FORMAT_MESSAGE_FROM_STRING;
int os__FORMAT_MESSAGE_FROM_SYSTEM;
int os__FORMAT_MESSAGE_IGNORE_INSERTS;
int os__SUBLANG_NEUTRAL;
int os__SUBLANG_DEFAULT;
int os__LANG_NEUTRAL;
#define os__MAX_ERROR_CODE 15841
#define math__E 2.71828182845904523536028747135266249775724709369995957496696763
#define math__Pi                                                               \
  3.14159265358979323846264338327950288419716939937510582097494459
#define math__Phi                                                              \
  1.61803398874989484820458683436563811772030917980576286213544862
#define math__Tau                                                              \
  6.28318530717958647692528676655900576839433879875021164194988918
#define math__Sqrt2                                                            \
  1.41421356237309504880168872420969807856967187537694807317667974
#define math__SqrtE                                                            \
  1.64872127070012814684865078781416357165377610071014801157507931
#define math__SqrtPi                                                           \
  1.77245385090551602729816748334114518279754945612238712821380779
#define math__SqrtTau                                                          \
  2.50662827463100050241576528481104525300698674060993831662992357
#define math__SqrtPhi                                                          \
  1.27201964951406896425242246173749149171560804184009624861664038
#define math__Ln2                                                              \
  0.693147180559945309417232121458176568075500134360255254120680009
f32 math__Log2E;
#define math__Ln10                                                             \
  2.30258509299404568401799145468436420760110148862877297603332790
f32 math__Log10E;
int math__MaxI8;
int math__MinI8;
int math__MaxI16;
int math__MinI16;
int math__MaxI32;
int math__MinI32;
int math__MaxU8;
int math__MaxU16;
int math__MaxU32;
int math__MaxU64;
array_int time__MonthDays;
i64 time__absoluteZeroYear;
#define time__secondsPerMinute 60
int time__secondsPerHour;
int time__secondsPerDay;
int time__secondsPerWeek;
int time__daysPer400Years;
int time__daysPer100Years;
int time__daysPer4Years;
array_int time__daysBefore;
string time__Months;
string time__Days;
#define vweb_dot_tmpl__STR_START tos2((byte *)"sb.write(\'")
#define vweb_dot_tmpl__STR_END tos2((byte *)"\' ) ")
string main__CommonCHeaders;
#define main__MaxLocalVars 50
string main__Version;
#define main__BuildMode_default_mode 0
#define main__BuildMode_embed_vlib 1
#define main__BuildMode_build 2
array_string main__SupportedPlatforms;
string main__ModPath;
#define main__OS_mac 0
#define main__OS_linux 1
#define main__OS_windows 2
#define main__OS_freebsd 3
#define main__OS_openbsd 4
#define main__OS_netbsd 5
#define main__OS_dragonfly 6
#define main__OS_msvc 7
#define main__Pass_imports 0
#define main__Pass_decl 1
#define main__Pass_main 2
string main__HelpText;
RegKey main__HKEY_LOCAL_MACHINE;
int main__KEY_QUERY_VALUE;
int main__KEY_WOW64_32KEY;
int main__KEY_ENUMERATE_SUB_KEYS;
Fn *main__EmptyFn;
Fn *main__MainFn;
#define main__MaxModuleDepth 4
string main__and_or_error;
#define main__AccessMod_private 0
#define main__AccessMod_private_mut 1
#define main__AccessMod_public 2
#define main__AccessMod_public_mut 3
#define main__AccessMod_public_mut_mut 4
#define main__TypeCategory_builtin 0
#define main__TypeCategory_struct_ 1
#define main__TypeCategory_func 2
#define main__TypeCategory_interface_ 3
#define main__TypeCategory_enum_ 4
#define main__TypeCategory_union_ 5
#define main__TypeCategory_c_struct 6
#define main__TypeCategory_c_typedef 7
#define main__TypeCategory_array 8
array_string main__CReserved;
array_string main__number_types;
array_string main__float_types;
#define main__Token_eof 0
#define main__Token_name 1
#define main__Token_number 2
#define main__Token_str 3
#define main__Token_str_inter 4
#define main__Token_chartoken 5
#define main__Token_plus 6
#define main__Token_minus 7
#define main__Token_mul 8
#define main__Token_div 9
#define main__Token_mod 10
#define main__Token_xor 11
#define main__Token_pipe 12
#define main__Token_inc 13
#define main__Token_dec 14
#define main__Token_and 15
#define main__Token_logical_or 16
#define main__Token_not 17
#define main__Token_bit_not 18
#define main__Token_question 19
#define main__Token_comma 20
#define main__Token_semicolon 21
#define main__Token_colon 22
#define main__Token_arrow 23
#define main__Token_amp 24
#define main__Token_hash 25
#define main__Token_dollar 26
#define main__Token_left_shift 27
#define main__Token_righ_shift 28
#define main__Token_assign 29
#define main__Token_decl_assign 30
#define main__Token_plus_assign 31
#define main__Token_minus_assign 32
#define main__Token_div_assign 33
#define main__Token_mult_assign 34
#define main__Token_xor_assign 35
#define main__Token_mod_assign 36
#define main__Token_or_assign 37
#define main__Token_and_assign 38
#define main__Token_righ_shift_assign 39
#define main__Token_left_shift_assign 40
#define main__Token_lcbr 41
#define main__Token_rcbr 42
#define main__Token_lpar 43
#define main__Token_rpar 44
#define main__Token_lsbr 45
#define main__Token_rsbr 46
#define main__Token_eq 47
#define main__Token_ne 48
#define main__Token_gt 49
#define main__Token_lt 50
#define main__Token_ge 51
#define main__Token_le 52
#define main__Token_nl 53
#define main__Token_dot 54
#define main__Token_dotdot 55
#define main__Token_keyword_beg 56
#define main__Token_key_as 57
#define main__Token_key_assert 58
#define main__Token_key_atomic 59
#define main__Token_key_break 60
#define main__Token_key_case 61
#define main__Token_key_const 62
#define main__Token_key_continue 63
#define main__Token_key_default 64
#define main__Token_key_defer 65
#define main__Token_key_else 66
#define main__Token_key_embed 67
#define main__Token_key_enum 68
#define main__Token_key_false 69
#define main__Token_key_for 70
#define main__Token_func 71
#define main__Token_key_global 72
#define main__Token_key_go 73
#define main__Token_key_goto 74
#define main__Token_key_if 75
#define main__Token_key_import 76
#define main__Token_key_import_const 77
#define main__Token_key_in 78
#define main__Token_key_interface 79
#define main__Token_key_match 80
#define main__Token_key_module 81
#define main__Token_key_mut 82
#define main__Token_key_return 83
#define main__Token_key_select 84
#define main__Token_key_sizeof 85
#define main__Token_key_struct 86
#define main__Token_key_switch 87
#define main__Token_key_true 88
#define main__Token_key_type 89
#define main__Token_key_orelse 90
#define main__Token_key_union 91
#define main__Token_key_pub 92
#define main__Token_key_static 93
#define main__Token_keyword_end 94
#define main__NrTokens 140
array_string main__TokenStr;
map_int main__KEYWORDS;
array_Token main__AssignTokens;

array new_array(int mylen, int cap, int elm_size) {

  array arr = (array){.len = mylen,
                      .cap = cap,
                      .element_size = elm_size,
                      .data = v_calloc(cap * elm_size)};

  return arr;
}
array _make(int len, int cap, int elm_size) {

  return new_array(len, cap, elm_size);
}
array new_array_from_c_array(int len, int cap, int elm_size, void *c_array) {

  array arr = (array){.len = len,
                      .cap = cap,
                      .element_size = elm_size,
                      .data = v_malloc(cap * elm_size)};

  memcpy(arr.data, c_array, len * elm_size);

  return arr;
}
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size,
                                      void *c_array) {

  array arr = (array){
      .len = len, .cap = cap, .element_size = elm_size, .data = c_array};

  return arr;
}
array array_repeat(void *val, int nr_repeats, int elm_size) {

  array arr = (array){.len = nr_repeats,
                      .cap = nr_repeats,
                      .element_size = elm_size,
                      .data = v_malloc(nr_repeats * elm_size)};

  for (int i = 0; i < nr_repeats; i++) {

    memcpy((byte *)arr.data + i * elm_size, val, elm_size);
  };

  return arr;
}
void array_sort_with_compare(array *a, void *compare) {

  qsort(a->data, a->len, a->element_size, compare);
}
void array_insert(array *a, int i, void *val) {

  if (i >= a->len) {

    v_panic(tos2((byte *)"array.insert: index larger than length"));
  };

  array__push(a, val);

  int size = a->element_size;

  memmove((byte *)a->data + (i + 1) * size, (byte *)a->data + i * size,
          (a->len - i) * size);

  array_set(a, i, val);
}
void array_prepend(array *a, void *val) { array_insert(a, 0, val); }
void array_delete(array *a, int idx) {

  int size = a->element_size;

  memmove((byte *)a->data + idx * size, (byte *)a->data + (idx + 1) * size,
          (a->len - idx) * size);

  a->len--;

  a->cap--;
}
void *array__get(array a, int i) {

  if (i < 0 || i >= a.len) {

    v_panic(_STR("array index out of range: %d/%d", i, a.len));
  };

  return (byte *)a.data + i * a.element_size;
}
void *array_first(array a) {

  if (a.len == 0) {

    v_panic(tos2((byte *)"array.first: empty array"));
  };

  return (byte *)a.data + 0;
}
void *array_last(array a) {

  if (a.len == 0) {

    v_panic(tos2((byte *)"array.last: empty array"));
  };

  return (byte *)a.data + (a.len - 1) * a.element_size;
}
array array_left(array s, int n) {

  if (n >= s.len) {

    return s;
  };

  return array_slice(s, 0, n);
}
array array_right(array s, int n) {

  if (n >= s.len) {

    return s;
  };

  return array_slice(s, n, s.len);
}
array array_slice(array s, int start, int _end) {

  int end = _end;

  if (start > end) {

    v_panic(_STR("invalid slice index: %d > %d", start, end));
  };

  if (end > s.len) {

    v_panic(_STR("runtime error: slice bounds out of range (%d >= %d)", end,
                 s.len));
  };

  if (start < 0) {

    v_panic(_STR("runtime error: slice bounds out of range (%d < 0)", start));
  };

  int l = end - start;

  array res = (array){.element_size = s.element_size,
                      .data = (byte *)s.data + start * s.element_size,
                      .len = l,
                      .cap = l};

  return res;
}
void array_set(array *a, int idx, void *val) {

  if (idx < 0 || idx >= a->len) {

    v_panic(_STR("array index out of range: %d / %d", idx, a->len));
  };

  memcpy((byte *)a->data + a->element_size * idx, val, a->element_size);
}
void array__push(array *arr, void *val) {

  if (arr->len >= arr->cap - 1) {

    int cap = (arr->len + 1) * 2;

    if (arr->cap == 0) {

      arr->data = v_malloc(cap * arr->element_size);

    } else {

      arr->data = realloc(arr->data, cap * arr->element_size);
    };

    arr->cap = cap;
  };

  memcpy((byte *)arr->data + arr->element_size * arr->len, val,
         arr->element_size);

  arr->len++;
}
void array__push_many(array *arr, void *val, int size) {

  if (arr->len >= arr->cap - size) {

    int cap = (arr->len + size) * 2;

    if (arr->cap == 0) {

      arr->data = v_malloc(cap * arr->element_size);

    } else {

      arr->data = realloc(arr->data, cap * arr->element_size);
    };

    arr->cap = cap;
  };

  memcpy((byte *)arr->data + arr->element_size * arr->len, val,
         arr->element_size * size);

  arr->len += size;
}
array array_reverse(array a) {

  array arr = (array){.len = a.len,
                      .cap = a.cap,
                      .element_size = a.element_size,
                      .data = v_malloc(a.cap * a.element_size)};

  for (int i = 0; i < a.len; i++) {

    memcpy((byte *)arr.data + i * arr.element_size,
           &/*vvar*/ (*(void **)array__get(a, a.len - 1 - i)),
           arr.element_size);
  };

  return arr;
}
array array_clone(array a) {

  array arr = (array){.len = a.len,
                      .cap = a.cap,
                      .element_size = a.element_size,
                      .data = v_malloc(a.cap * a.element_size)};

  memcpy(arr.data, a.data, a.cap * a.element_size);

  return arr;
}
void v_array_free(array a) { free(a.data); }
string array_string_str(array_string a) {

  strings__Builder sb = strings__new_builder(a.len * 3);

  strings__Builder_write(&/* ? */ sb, tos2((byte *)"["));

  for (int i = 0; i < a.len; i++) {

    string val = (*(string *)array__get(a, i));

    strings__Builder_write(&/* ? */ sb, _STR("\"%.*s\"", val.len, val.str));

    if (i < a.len - 1) {

      strings__Builder_write(&/* ? */ sb, tos2((byte *)", "));
    };
  };

  strings__Builder_write(&/* ? */ sb, tos2((byte *)"]"));

  return strings__Builder_str(sb);
}
string array_byte_hex(array_byte b) {

  byte *hex = v_malloc(b.len * 2 + 1);

  byte *ptr = &/*vvar*/ hex[/*ptr*/ 0] /*rbyte 1*/;

  for (int i = 0; i < b.len; i++) {

    ptr += sprintf(ptr, "%02x", (*(byte *)array__get(b, i)));
  };

  return (tos2((byte *)hex));
}
int copy(array_byte dst, array_byte src) {

  if (dst.len > 0 && src.len > 0) {

    int min = (dst.len < src.len) ? (dst.len) : (src.len);

    memcpy(dst.data, array_left(src, min).data, dst.element_size * min);

    return min;
  };

  return 0;
}
int compare_ints(int *a, int *b) {

  if (a < b) {

    return -1;
  };

  if (a > b) {

    return 1;
  };

  return 0;
}
void array_int_sort(array_int *a) { array_sort_with_compare(a, compare_ints); }
void todo() {}
string tos(byte *s, int len) {

  if (isnil(s)) {

    v_panic(tos2((byte *)"tos(): nil string"));
  };

  return (string){.str = s, .len = len};
}
string tos_clone(byte *s) {

  if (isnil(s)) {

    v_panic(tos2((byte *)"tos: nil string"));
  };

  return string_clone(tos2(s));
}
string tos2(byte *s) {

  if (isnil(s)) {

    v_panic(tos2((byte *)"tos2: nil string"));
  };

  int len = strlen(s);

  string res = tos(s, len);

  return res;
}
string string_clone(string a) {

  string b = (string){.len = a.len, .str = v_malloc(a.len + 1)};

  for (int i = 0; i < a.len; i++) {

    b.str[i] /*rbyte 1*/ = a.str[i] /*rbyte 0*/;
  };

  b.str[a.len] /*rbyte 1*/ = '\0';

  return b;
}
string string_replace(string s, string rep, string with) {

  if (s.len == 0 || rep.len == 0) {

    return s;
  };

  array_int idxs = new_array_from_c_array(0, 0, sizeof(int), (int[]){0});

  {}

  string rem = s;

  int rstart = 0;

  while (1) {

    int i = string_index(rem, rep);

    if (i < 0) {

      break;
    };

    _PUSH(&idxs, (rstart + i), tmp9, int);

    i += rep.len;

    rstart += i;

    rem = string_substr(rem, i, rem.len);
  };

  if (idxs.len == 0) {

    return s;
  };

  int new_len = s.len + idxs.len * (with.len - rep.len);

  byte *b = v_malloc(new_len + 1);

  int idx_pos = 0;

  int cur_idx = (*(int *)array__get(idxs, idx_pos));

  int b_i = 0;

  for (int i = 0; i < s.len; i++) {

    if (i == cur_idx) {

      for (int j = 0; j < with.len; j++) {

        b[/*ptr*/ b_i] /*rbyte 1*/ = with.str[j] /*rbyte 0*/;

        b_i++;
      };

      i += rep.len - 1;

      idx_pos++;

      if (idx_pos < idxs.len) {

        cur_idx = (*(int *)array__get(idxs, idx_pos));
      };

    } else {

      b[/*ptr*/ b_i] /*rbyte 1*/ = s.str[i] /*rbyte 0*/;

      b_i++;
    };
  };

  b[/*ptr*/ new_len] /*rbyte 1*/ = '\0';

  return tos(b, new_len);

  v_array_free(idxs); // close_scope free
}
int v_string_int(string s) { return atoi(s.str); }
i64 string_i64(string s) { return atoll(s.str); }
f32 string_f32(string s) { return atof(s.str); }
f64 string_f64(string s) { return atof(s.str); }
u32 string_u32(string s) { return strtoul(s.str, 0, 0); }
u64 string_u64(string s) { return strtoull(s.str, 0, 0); }
bool string_eq(string s, string a) {

  if (isnil(s.str)) {

    v_panic(tos2((byte *)"string.eq(): nil string"));
  };

  if (s.len != a.len) {

    return 0;
  };

  for (int i = 0; i < s.len; i++) {

    if (s.str[i] /*rbyte 0*/ != a.str[i] /*rbyte 0*/) {

      return 0;
    };
  };

  return 1;
}
bool string_ne(string s, string a) { return !string_eq(s, a); }
bool string_lt(string s, string a) {

  for (int i = 0; i < s.len; i++) {

    if (i >= a.len || s.str[i] /*rbyte 0*/ > a.str[i] /*rbyte 0*/) {

      return 0;

    } else if (s.str[i] /*rbyte 0*/ < a.str[i] /*rbyte 0*/) {

      return 1;
    };
  };

  if (s.len < a.len) {

    return 1;
  };

  return 0;
}
bool string_le(string s, string a) {

  return string_lt(s, a) || string_eq(s, a);
}
bool string_gt(string s, string a) { return !string_le(s, a); }
bool string_ge(string s, string a) { return !string_lt(s, a); }
string string_add(string s, string a) {

  int new_len = a.len + s.len;

  string res = (string){.len = new_len, .str = v_malloc(new_len + 1)};

  for (int j = 0; j < s.len; j++) {

    res.str[j] /*rbyte 1*/ = s.str[j] /*rbyte 0*/;
  };

  for (int j = 0; j < a.len; j++) {

    res.str[s.len + j] /*rbyte 1*/ = a.str[j] /*rbyte 0*/;
  };

  res.str[new_len] /*rbyte 1*/ = '\0';

  return res;
}
array_string string_split(string s, string delim) {

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (delim.len == 0) {

    _PUSH(&res, (s), tmp28, string);

    return res;
  };

  if (delim.len == 1) {

    return string_split_single(s, delim.str[0] /*rbyte 0*/);
  };

  int i = 0;

  int start = 0;

  while (i < s.len) {

    bool a = s.str[i] /*rbyte 0*/ == delim.str[0] /*rbyte 0*/;

    int j = 1;

    while (j < delim.len && a) {

      a = a && s.str[i + j] /*rbyte 0*/ == delim.str[j] /*rbyte 0*/;

      j++;
    };

    bool last = i == s.len - 1;

    if (a || last) {

      if (last) {

        i++;
      };

      string val = string_substr(s, start, i);

      if (val.len > 0) {

        if (string_starts_with(val, delim)) {

          val = string_right(val, delim.len);
        };

        _PUSH(&res, (string_trim_space(val)), tmp35, string);
      };

      start = i;
    };

    i++;
  };

  return res;

  v_array_free(res); // close_scope free
}
array_string string_split_single(string s, byte delim) {

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (((int)(delim)) == 0) {

    _PUSH(&res, (s), tmp37, string);

    return res;
  };

  int i = 0;

  int start = 0;

  while (i < s.len) {

    bool is_delim = s.str[i] /*rbyte 0*/ == delim;

    bool last = i == s.len - 1;

    if (is_delim || last) {

      if (!is_delim && i == s.len - 1) {

        i++;
      };

      string val = string_substr(s, start, i);

      if (val.len > 0) {

        _PUSH(&res, (val), tmp43, string);
      };

      start = i + 1;
    };

    i++;
  };

  return res;

  v_array_free(res); // close_scope free
}
array_string string_split_into_lines(string s) {

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (s.len == 0) {

    return res;
  };

  int start = 0;

  for (int i = 0; i < s.len; i++) {

    bool last = i == s.len - 1;

    if (((int)(s.str[i] /*rbyte 0*/)) == 10 || last) {

      if (last) {

        i++;
      };

      string line = string_substr(s, start, i);

      _PUSH(&res, (line), tmp49, string);

      start = i + 1;
    };
  };

  return res;

  v_array_free(res); // close_scope free
}
string string_left(string s, int n) {

  if (n >= s.len) {

    return s;
  };

  return string_substr(s, 0, n);
}
string string_right(string s, int n) {

  if (n >= s.len) {

    return tos2((byte *)"");
  };

  return string_substr(s, n, s.len);
}
string string_substr(string s, int start, int end) {

  if (start > end || start > s.len || end > s.len || start < 0 || end < 0) {

    v_panic(_STR("substr(%d, %d) out of bounds (len=%d)", start, end, s.len));
  };

  int len = end - start;

  string res = (string){.len = len, .str = v_malloc(len + 1)};

  for (int i = 0; i < len; i++) {

    res.str[/*ptr*/ i] /*rbyte 1*/ = s.str[/*ptr*/ start + i] /*rbyte 0*/;
  };

  res.str[/*ptr*/ len] /*rbyte 1*/ = '\0';

  return res;
}
int string_index(string s, string p) {

  if (p.len > s.len) {

    return -1;
  };

  array_int prefix = array_repeat(&(int[]){0}, p.len, sizeof(int));

  int j = 0;

  for (int i = 1; i < p.len; i++) {

    while (p.str[j] /*rbyte 0*/ != p.str[i] /*rbyte 0*/ && j > 0) {

      j = (*(int *)array__get(prefix, j - 1));
    };

    if (p.str[j] /*rbyte 0*/ == p.str[i] /*rbyte 0*/) {

      j++;
    };

    array_set(&/*q*/ prefix, i, &(int[]){j});
  };

  j = 0;

  for (int i = 0; i < s.len; i++) {

    while (p.str[j] /*rbyte 0*/ != s.str[i] /*rbyte 0*/ && j > 0) {

      j = (*(int *)array__get(prefix, j - 1));
    };

    if (p.str[j] /*rbyte 0*/ == s.str[i] /*rbyte 0*/) {

      j++;
    };

    if (j == p.len) {

      v_array_free(prefix);

      return i - p.len + 1;
    };
  };

  v_array_free(prefix);

  return -1;

  v_array_free(prefix); // close_scope free
}
int string_index_any(string s, string chars) {

  string tmp61 = chars;
  ;
  for (int tmp62 = 0; tmp62 < tmp61.len; tmp62++) {
    byte c = ((byte *)tmp61.str)[tmp62];

    int index = string_index(s, byte_str(c));

    if (index != -1) {

      return index;
    };
  };

  return -1;
}
int string_last_index(string s, string p) {

  if (p.len > s.len) {

    return -1;
  };

  int i = s.len - p.len;

  while (i >= 0) {

    int j = 0;

    while (j < p.len && s.str[i + j] /*rbyte 0*/ == p.str[j] /*rbyte 0*/) {

      j++;
    };

    if (j == p.len) {

      return i;
    };

    i--;
  };

  return -1;
}
int string_index_after(string s, string p, int start) {

  if (p.len > s.len) {

    return -1;
  };

  int strt = start;

  if (start < 0) {

    strt = 0;
  };

  if (start >= s.len) {

    return -1;
  };

  int i = strt;

  while (i < s.len) {

    int j = 0;

    int ii = i;

    while (j < p.len && s.str[ii] /*rbyte 0*/ == p.str[j] /*rbyte 0*/) {

      j++;

      ii++;
    };

    if (j == p.len) {

      return i;
    };

    i++;
  };

  return -1;
}
int string_count(string s, string substr) {

  if (s.len == 0 || substr.len == 0) {

    return 0;
  };

  if (substr.len > s.len) {

    return 0;
  };

  int n = 0;

  int i = 0;

  while (1) {

    i = string_index_after(s, substr, i);

    if (i == -1) {

      return n;
    };

    i += substr.len;

    n++;
  };

  return 0;
}
bool string_contains(string s, string p) {

  bool res = string_index(s, p) > 0 - 1;

  return res;
}
bool string_starts_with(string s, string p) {

  bool res = string_index(s, p) == 0;

  return res;
}
bool string_ends_with(string s, string p) {

  if (p.len > s.len) {

    return 0;
  };

  bool res = string_last_index(s, p) == s.len - p.len;

  return res;
}
string string_to_lower(string s) {

  byte *b = v_malloc(s.len + 1);

  for (int i = 0; i < s.len; i++) {

    b[/*ptr*/ i] /*rbyte 1*/ = tolower(s.str[/*ptr*/ i] /*rbyte 0*/);
  };

  return tos(b, s.len);
}
string string_to_upper(string s) {

  byte *b = v_malloc(s.len + 1);

  for (int i = 0; i < s.len; i++) {

    b[/*ptr*/ i] /*rbyte 1*/ = toupper(s.str[/*ptr*/ i] /*rbyte 0*/);
  };

  return tos(b, s.len);
}
string string_capitalize(string s) {

  string sl = string_to_lower(s);

  string cap = string_add(string_to_upper(byte_str(sl.str[0] /*rbyte 0*/)),
                          string_right(sl, 1));

  return cap;
}
string string_title(string s) {

  array_string words = string_split(s, tos2((byte *)" "));

  array_string tit =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  array_string tmp83 = words;
  ;
  for (int tmp84 = 0; tmp84 < tmp83.len; tmp84++) {
    string word = ((string *)tmp83.data)[tmp84];

    _PUSH(&tit, (string_capitalize(word)), tmp85, string);
  };

  string title = array_string_join(tit, tos2((byte *)" "));

  return title;

  v_array_free(tit); // close_scope free
}
string string_find_between(string s, string start, string end) {

  int start_pos = string_index(s, start);

  if (start_pos == -1) {

    return tos2((byte *)"");
  };

  string val = string_right(s, start_pos + start.len);

  int end_pos = string_index(val, end);

  if (end_pos == -1) {

    return val;
  };

  return string_left(val, end_pos);
}
bool array_string_contains(array_string ar, string val) {

  array_string tmp90 = ar;
  ;
  for (int tmp91 = 0; tmp91 < tmp90.len; tmp91++) {
    string s = ((string *)tmp90.data)[tmp91];

    if (string_eq(s, val)) {

      return 1;
    };
  };

  return 0;
}
bool array_int_contains(array_int ar, int val) {

  array_int tmp92 = ar;
  ;
  for (int i = 0; i < tmp92.len; i++) {
    int s = ((int *)tmp92.data)[i];

    if (s == val) {

      return 1;
    };
  };

  return 0;
}
bool is_space(byte c) {

  return _IN(
      byte, c,
      new_array_from_c_array(6, 6, sizeof(byte),
                             (byte[]){' ', '\n', '\t', '\v', '\f', '\r'}));
}
bool byte_is_space(byte c) { return is_space(c); }
string string_trim_space(string s) {

  return string_trim(s, tos2((byte *)" \n\t\v\f\r"));
}
string string_trim(string s, string cutset) {

  if (s.len < 1 || cutset.len < 1) {

    return s;
  };

  array_byte cs_arr = string_bytes(cutset);

  int pos_left = 0;

  int pos_right = s.len - 1;

  bool cs_match = 1;

  while (pos_left <= s.len && pos_right >= -1 && cs_match) {

    cs_match = 0;

    if (_IN(byte, s.str[pos_left] /*rbyte 0*/, cs_arr)) {

      pos_left++;

      cs_match = 1;
    };

    if (_IN(byte, s.str[pos_right] /*rbyte 0*/, cs_arr)) {

      pos_right--;

      cs_match = 1;
    };

    if (pos_left > pos_right) {

      return tos2((byte *)"");
    };
  };

  return string_substr(s, pos_left, pos_right + 1);
}
string string_trim_left(string s, string cutset) {

  if (s.len < 1 || cutset.len < 1) {

    return s;
  };

  array_byte cs_arr = string_bytes(cutset);

  int pos = 0;

  while (pos <= s.len && _IN(byte, s.str[pos] /*rbyte 0*/, cs_arr)) {

    pos++;
  };

  return string_right(s, pos);
}
string string_trim_right(string s, string cutset) {

  if (s.len < 1 || cutset.len < 1) {

    return s;
  };

  array_byte cs_arr = string_bytes(cutset);

  int pos = s.len - 1;

  while (pos >= -1 && _IN(byte, s.str[pos] /*rbyte 0*/, cs_arr)) {

    pos--;
  };

  return string_left(s, pos + 1);
}
int compare_strings(string *a, string *b) {

  if (string_lt(*a, *b)) {

    return -1;
  };

  if (string_gt(*a, *b)) {

    return 1;
  };

  return 0;
}
int compare_strings_by_len(string *a, string *b) {

  if (a->len < b->len) {

    return -1;
  };

  if (a->len > b->len) {

    return 1;
  };

  return 0;
}
int compare_lower_strings(string *a, string *b) {

  string aa = string_to_lower(*a);

  string bb = string_to_lower(*b);

  return compare_strings(&/*112 EXP:"string*" GOT:"string" */ aa,
                         &/*112 EXP:"string*" GOT:"string" */ bb);
}
void array_string_sort(array_string *s) {

  array_sort_with_compare(s, compare_strings);
}
void array_string_sort_ignore_case(array_string *s) {

  array_sort_with_compare(s, compare_lower_strings);
}
void array_string_sort_by_len(array_string *s) {

  array_sort_with_compare(s, compare_strings_by_len);
}
ustring string_ustring(string s) {

  ustring res =
      (ustring){.s = s, .runes = new_array(0, s.len, sizeof(int)), .len = 0};

  for (int i = 0; i < s.len; i++) {

    int char_len = utf8_char_len(s.str[/*ptr*/ i] /*rbyte 0*/);

    _PUSH(&res.runes, (i), tmp106, int);

    i += char_len - 1;

    res.len++;
  };

  return res;
}
ustring string_ustring_tmp(string s) {

  if (g_ustring_runes.len == 0) {

    g_ustring_runes = new_array(0, 128, sizeof(int));
  };

  ustring res =
      (ustring){.s = s, .runes = new_array(0, 1, sizeof(int)), .len = 0};

  res.runes = g_ustring_runes;

  res.runes.len = s.len;

  int j = 0;

  for (int i = 0; i < s.len; i++) {

    int char_len = utf8_char_len(s.str[/*ptr*/ i] /*rbyte 0*/);

    array_set(&/*q*/ res.runes, j, &(int[]){i});

    j++;

    i += char_len - 1;

    res.len++;
  };

  return res;
}
string ustring_substr(ustring u, int _start, int _end) {

  int start = (*(int *)array__get(u.runes, _start));

  int end =
      (_end >= u.runes.len) ? (u.s.len) : ((*(int *)array__get(u.runes, _end)));

  return string_substr(u.s, start, end);
}
string ustring_left(ustring u, int pos) { return ustring_substr(u, 0, pos); }
string ustring_right(ustring u, int pos) {

  return ustring_substr(u, pos, u.len);
}
byte string_at(string s, int idx) {

  if (idx < 0 || idx >= s.len) {

    v_panic(_STR("string index out of range: %d / %d", idx, s.len));
  };

  return s.str[/*ptr*/ idx] /*rbyte 0*/;
}
string ustring_at(ustring u, int idx) {

  return ustring_substr(u, idx, idx + 1);
}
void v_ustring_free(ustring u) { v_array_free(u.runes); }
bool byte_is_digit(byte c) { return c >= '0' && c <= '9'; }
bool byte_is_hex_digit(byte c) {

  return byte_is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
bool byte_is_oct_digit(byte c) { return c >= '0' && c <= '7'; }
bool byte_is_letter(byte c) {

  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
void v_string_free(string s) { v_free(s.str); }
string string_all_before(string s, string dot) {

  int pos = string_index(s, dot);

  if (pos == -1) {

    return s;
  };

  return string_left(s, pos);
}
string string_all_before_last(string s, string dot) {

  int pos = string_last_index(s, dot);

  if (pos == -1) {

    return s;
  };

  return string_left(s, pos);
}
string string_all_after(string s, string dot) {

  int pos = string_last_index(s, dot);

  if (pos == -1) {

    return s;
  };

  return string_right(s, pos + dot.len);
}
string array_string_join(array_string a, string del) {

  if (a.len == 0) {

    return tos2((byte *)"");
  };

  int len = 0;

  array_string tmp121 = a;
  ;
  for (int i = 0; i < tmp121.len; i++) {
    string val = ((string *)tmp121.data)[i];

    len += val.len + del.len;
  };

  len -= del.len;

  string res = tos2((byte *)"");

  res.len = len;

  res.str = v_malloc(res.len + 1);

  int idx = 0;

  array_string tmp124 = a;
  ;
  for (int i = 0; i < tmp124.len; i++) {
    string val = ((string *)tmp124.data)[i];

    for (int j = 0; j < val.len; j++) {

      byte c = val.str[j] /*rbyte 0*/;

      res.str[/*ptr*/ idx] /*rbyte 1*/ = val.str[/*ptr*/ j] /*rbyte 0*/;

      idx++;
    };

    if (i != a.len - 1) {

      for (int k = 0; k < del.len; k++) {

        res.str[/*ptr*/ idx] /*rbyte 1*/ = del.str[/*ptr*/ k] /*rbyte 0*/;

        idx++;
      };
    };
  };

  res.str[/*ptr*/ res.len] /*rbyte 1*/ = '\0';

  return res;
}
string array_string_join_lines(array_string s) {

  return array_string_join(s, tos2((byte *)"\n"));
}
string string_reverse(string s) {

  string res = (string){.len = s.len, .str = v_malloc(s.len)};

  for (int i = s.len - 1; i >= 0; i--) {

    res.str[s.len - i - 1] /*rbyte 1*/ = s.str[i] /*rbyte 0*/;
  };

  return res;
}
string string_limit(string s, int max) {

  ustring u = string_ustring(s);

  if (u.len <= max) {

    return s;
  };

  return ustring_substr(u, 0, max);
}
bool byte_is_white(byte c) {

  int i = ((int)(c));

  return i == 10 || i == 32 || i == 9 || i == 13 || c == '\r';
}
int string_hash(string s) {

  int h = 0;

  if (h == 0 && s.len > 0) {

    string tmp133 = s;
    ;
    for (int tmp134 = 0; tmp134 < tmp133.len; tmp134++) {
      byte c = ((byte *)tmp133.str)[tmp134];

      h = h * 31 + ((int)(c));
    };
  };

  return h;
}
array_byte string_bytes(string s) {

  if (s.len == 0) {

    return new_array_from_c_array(0, 0, sizeof(byte), (byte[]){0});
  };

  array_byte buf = array_repeat(&(byte[]){((byte)(0))}, s.len, sizeof(byte));

  memcpy(buf.data, s.str, s.len);

  return buf;

  v_array_free(buf); // close_scope free
}
void v_exit(int code) { exit(code); }
bool isnil(void *v) { return v == 0; }
void on_panic(int (*f)(int /*FFF*/)) {}
void print_backtrace_skipping_top_frames(int skipframes) {

#ifdef __APPLE__

  byte *buffer[100] = {0};

  void *nr_ptrs = backtrace(buffer, 100);

  backtrace_symbols_fd(&/*vvar*/ buffer[skipframes] /*rbyte* 0*/,
                       (byte *)nr_ptrs - skipframes, 1);

  return;

#endif
  ;

#ifdef __linux__

  if (backtrace_symbols_fd != 0) {

    byte *buffer[100] = {0};

    void *nr_ptrs = backtrace(buffer, 100);

    backtrace_symbols_fd(&/*vvar*/ buffer[skipframes] /*rbyte* 0*/,
                         (byte *)nr_ptrs - skipframes, 1);

    return;

  } else {

    printf("backtrace_symbols_fd is missing, so printing backtraces is not "
           "available.\n");

    printf("Some libc implementations like musl simply do not provide it.\n");
  };

#endif
  ;

  println(tos2((byte *)"print_backtrace_skipping_top_frames is not implemented "
                       "on this platform for now...\n"));
}
void print_backtrace() { print_backtrace_skipping_top_frames(2); }
void _panic_debug(int line_no, string file, string mod, string fn_name,
                  string s) {

  println(tos2((byte *)"================ V panic ================"));

  printf("   module: %.*s\n", mod.len, mod.str);

  printf(" function: %.*s()\n", fn_name.len, fn_name.str);

  printf("     file: %.*s\n", file.len, file.str);

  println(string_add(tos2((byte *)"     line: "), int_str(line_no)));

  printf("  message: %.*s\n", s.len, s.str);

  println(tos2((byte *)"========================================="));

  print_backtrace_skipping_top_frames(1);

  exit(1);
}
void v_panic(string s) {

  printf("V panic: %.*s\n", s.len, s.str);

  print_backtrace();

  exit(1);
}
void println(string s) {

  if (isnil(s.str)) {

    v_panic(tos2((byte *)"println(NIL)"));
  };

#ifdef _WIN32

  _putws(string_to_wide(s));

#else

  printf("%.*s\n", s.len, s.str);

#endif
  ;
}
void eprintln(string s) {

  if (isnil(s.str)) {

    v_panic(tos2((byte *)"eprintln(NIL)"));
  };

#ifdef __APPLE__

  fprintf(stderr, "%.*s\n", s.len, s.str);

#else

  println(s);

#endif
  ;
}
void print(string s) {

#ifdef _WIN32

  wprintf(string_to_wide(s));

#else

  printf("%.*s", s.len, s.str);

#endif
  ;
}
byte *v_malloc(int n) {

  if (n < 0) {

    v_panic(tos2((byte *)"malloc(<0)"));
  };

  byte *ptr = malloc(n);

  if (isnil(ptr)) {

    v_panic(_STR("malloc(%d) failed", n));
  };

  return ptr;
}
byte *v_calloc(int n) {

  if (n < 0) {

    v_panic(tos2((byte *)"calloc(<0)"));
  };

  return calloc(n, 1);
}
void v_free(void *ptr) { free(ptr); }
void *memdup(void *src, int sz) {

  byte *mem = v_malloc(sz);

  return memcpy(mem, src, sz);
}
string f64_str(f64 d) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(buf, "%f", d);

  return tos(buf, strlen(buf));
}
string f32_str(f32 d) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(buf, "%f", d);

  return tos(buf, strlen(buf));
}
string ptr_str(void *ptr) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(buf, "%p", ptr);

  return tos(buf, strlen(buf));
}
bool f64_eq(f64 a, f64 b) { return (a - b) <= DBL_EPSILON; }
string int_str(int nn) {

  int n = nn;

  if (n == 0) {

    return tos2((byte *)"0");
  };

  int max = 16;

  byte *buf = v_calloc(max);

  int len = 0;

  bool is_neg = 0;

  if (n < 0) {

    n = -n;

    is_neg = 1;
  };

  while (n > 0) {

    int d = n % 10;

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = d + ((int)('0'));

    len++;

    n = n / 10;
  };

  if (is_neg) {

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = '-';

    len++;
  };

  return tos(buf + max - len, len);
}
string u32_str(u32 nn) {

  u32 n = nn;

  if (n == ((u32)(0))) {

    return tos2((byte *)"0");
  };

  int max = 16;

  byte *buf = v_malloc(max);

  int len = 0;

  while (n > ((u32)(0))) {

    u32 d = n % ((u32)(10));

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = d + ((u32)('0'));

    len++;

    n = n / ((u32)(10));
  };

  return tos(buf + max - len, len);
}
string i64_str(i64 nn) {

  i64 n = nn;

  if (n == ((i64)(0))) {

    return tos2((byte *)"0");
  };

  int max = 32;

  byte *buf = v_malloc(max);

  int len = 0;

  bool is_neg = 0;

  if (n < ((i64)(0))) {

    n = -n;

    is_neg = 1;
  };

  while (n > ((i64)(0))) {

    int d = ((int)(n % ((i64)(10))));

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = d + ((int)('0'));

    len++;

    n = n / ((i64)(10));
  };

  if (is_neg) {

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = '-';

    len++;
  };

  return tos(buf + max - len, len);
}
string u64_str(u64 nn) {

  u64 n = nn;

  if (n == ((u64)(0))) {

    return tos2((byte *)"0");
  };

  int max = 32;

  byte *buf = v_malloc(max);

  int len = 0;

  while (n > ((u64)(0))) {

    u64 d = n % ((u64)(10));

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = d + ((u64)('0'));

    len++;

    n = n / ((u64)(10));
  };

  return tos(buf + max - len, len);
}
string bool_str(bool b) {

  if (b) {

    return tos2((byte *)"true");
  };

  return tos2((byte *)"false");
}
string int_hex(int n) {

  int len = (n >= 0) ? (int_str(n).len + 3) : (11);

  byte *hex = v_malloc(len);

  int count = ((int)(sprintf(hex, "0x%x", n)));

  return tos(hex, count);
}
string i64_hex(i64 n) {

  int len = (n >= ((i64)(0))) ? (i64_str(n).len + 3) : (19);

  byte *hex = v_malloc(len);

  int count = ((int)(sprintf(hex, "0x%x", n)));

  return tos(hex, count);
}
bool array_byte_contains(array_byte a, byte val) {

  array_byte tmp32 = a;
  ;
  for (int tmp33 = 0; tmp33 < tmp32.len; tmp33++) {
    byte aa = ((byte *)tmp32.data)[tmp33];

    if (aa == val) {

      return 1;
    };
  };

  return 0;
}
string rune_str(rune c) {

  int fst_byte = ((int)(c)) >> 8 * 3 & 0xff;

  int len = utf8_char_len(fst_byte);

  string str = (string){.len = len, .str = v_malloc(len + 1)};

  for (int i = 0; i < len; i++) {

    str.str[/*ptr*/ i] /*rbyte 1*/ = ((int)(c)) >> 8 * (3 - i) & 0xff;
  };

  str.str[len] /*rbyte 1*/ = '\0';

  return str;
}
string byte_str(byte c) {

  string str = (string){.len = 1, .str = v_malloc(2)};

  str.str[/*ptr*/ 0] /*rbyte 1*/ = c;

  str.str[/*ptr*/ 1] /*rbyte 1*/ = '\0';

  return str;
}
bool byte_is_capital(byte c) { return c >= 'A' && c <= 'Z'; }
array_byte array_byte_clone(array_byte b) {

  array_byte res = array_repeat(&(byte[]){((byte)(0))}, b.len, sizeof(byte));

  for (int i = 0; i < b.len; i++) {

    array_set(&/*q*/ res, i, &(byte[]){(*(byte *)array__get(b, i))});
  };

  return res;

  v_array_free(res); // close_scope free
}
int utf8_char_len(byte b) {

  return ((0xe5000000 >> ((b >> 3) & 0x1e)) & 3) + 1;
}
string utf32_to_str(u32 code) {

  int icode = ((int)(code));

  byte *buffer = v_malloc(5);

  if (icode <= 127) {

    buffer[/*ptr*/ 0] /*rbyte 1*/ = icode;

    return tos(buffer, 1);
  };

  if ((icode <= 2047)) {

    buffer[/*ptr*/ 0] /*rbyte 1*/ = 192 | (icode >> 6);

    buffer[/*ptr*/ 1] /*rbyte 1*/ = 128 | (icode & 63);

    return tos(buffer, 2);
  };

  if ((icode <= 65535)) {

    buffer[/*ptr*/ 0] /*rbyte 1*/ = 224 | (icode >> 12);

    buffer[/*ptr*/ 1] /*rbyte 1*/ = 128 | ((icode >> 6) & 63);

    buffer[/*ptr*/ 2] /*rbyte 1*/ = 128 | (icode & 63);

    return tos(buffer, 3);
  };

  if ((icode <= 1114111)) {

    buffer[/*ptr*/ 0] /*rbyte 1*/ = 240 | (icode >> 18);

    buffer[/*ptr*/ 1] /*rbyte 1*/ = 128 | ((icode >> 12) & 63);

    buffer[/*ptr*/ 2] /*rbyte 1*/ = 128 | ((icode >> 6) & 63);

    buffer[/*ptr*/ 3] /*rbyte 1*/ = 128 | (icode & 63);

    return tos(buffer, 4);
  };

  return tos2((byte *)"");
}
string utf32_to_str_no_malloc(u32 code, void *buf) {

  int icode = ((int)(code));

  byteptr buffer = ((byteptr)(buf));

  if (icode <= 127) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = icode;

    return tos(buffer, 1);
  };

  if ((icode <= 2047)) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = 192 | (icode >> 6);

    buffer[/*ptr*/ 1] /*rbyteptr 1*/ = 128 | (icode & 63);

    return tos(buffer, 2);
  };

  if ((icode <= 65535)) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = 224 | (icode >> 12);

    buffer[/*ptr*/ 1] /*rbyteptr 1*/ = 128 | ((icode >> 6) & 63);

    buffer[/*ptr*/ 2] /*rbyteptr 1*/ = 128 | (icode & 63);

    return tos(buffer, 3);
  };

  if ((icode <= 1114111)) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = 240 | (icode >> 18);

    buffer[/*ptr*/ 1] /*rbyteptr 1*/ = 128 | ((icode >> 12) & 63);

    buffer[/*ptr*/ 2] /*rbyteptr 1*/ = 128 | ((icode >> 6) & 63);

    buffer[/*ptr*/ 3] /*rbyteptr 1*/ = 128 | (icode & 63);

    return tos(buffer, 4);
  };

  return tos2((byte *)"");
}
int string_utf32_code(string _rune) {

  if (_rune.len == 0) {

    return 0;
  };

  if (_rune.len == 1) {

    return ((int)(_rune.str[0] /*rbyte 0*/));
  };

  byte b = ((byte)(((int)(_rune.str[0] /*rbyte 0*/))));

  b = b << _rune.len;

  int res = ((int)(b));

  int shift = 6 - _rune.len;

  for (int i = 1; i < _rune.len; i++) {

    int c = ((int)(_rune.str[i] /*rbyte 0*/));

    res = res << shift;

    res |= c & 63;

    shift = 6;
  };

  return res;
}
u16 *string_to_wide(string _str) {

#ifdef _WIN32

  int num_chars = ((
      int)(MultiByteToWideChar(builtin__CP_UTF8, 0, _str.str, _str.len, 0, 0)));

  u16 *wstr = ((u16 *)(v_malloc((num_chars + 1) * 2)));

  if (wstr > 0) {

    MultiByteToWideChar(builtin__CP_UTF8, 0, _str.str, _str.len, wstr,
                        num_chars);

    memset(((byte *)(wstr)) + num_chars * 2, 0, 2);
  };

  return wstr;

#else

  return 0;

#endif
  ;
}
string string_from_wide(u16 *_wstr) {

#ifdef _WIN32

  int wstr_len = ((int)(wcslen(_wstr)));

  return string_from_wide2(_wstr, wstr_len);

#else

  return tos2((byte *)"");

#endif
  ;
}
string string_from_wide2(u16 *_wstr, int len) {

#ifdef _WIN32

  int num_chars =
      ((int)(WideCharToMultiByte(builtin__CP_UTF8, 0, _wstr, len, 0, 0, 0, 0)));

  byte *str_to = ((byte *)(v_malloc(num_chars + 1)));

  if (str_to > 0) {

    WideCharToMultiByte(builtin__CP_UTF8, 0, _wstr, len, str_to, num_chars, 0,
                        0);

    memset(((byte *)(str_to)) + num_chars, 0, 1);
  };

  return tos2(str_to);

#else

  return tos2((byte *)"");

#endif
  ;
}
map new_map(int cap, int elm_size) {

  map res = (map){.element_size = elm_size, .root = 0, .size = 0};

  return res;
}
map new_map_init(int cap, int elm_size, string *keys, void *vals) {

  map res = (map){.element_size = elm_size, .root = 0, .size = 0};

  int tmp3 = 0;
  ;
  for (int tmp4 = tmp3; tmp4 < cap; tmp4++) {
    int i = tmp4;

    map__set(&/* ? */ res, keys[/*ptr*/ i] /*rstring 0*/,
             (byte *)vals + i * elm_size);
  };

  return res;
}
mapnode *new_node(string key, void *val, int element_size) {

  mapnode *new_e = (mapnode *)memdup(
      &(mapnode){
          .key = key,
          .val = v_malloc(element_size),
          .left = 0,
          .right = 0,
          .is_empty = 0,
      },
      sizeof(mapnode));

  memcpy(new_e->val, val, element_size);

  return new_e;
}
void map_insert(map *m, mapnode *n, string key, void *val) {

  if (string_eq(n->key, key)) {

    memcpy(n->val, val, m->element_size);

    return;
  };

  if (string_gt(n->key, key)) {

    if (n->left == 0) {

      n->left = new_node(key, val, m->element_size);

      m->size++;

    } else {

      map_insert(m, n->left, key, val);
    };

    return;
  };

  if (n->right == 0) {

    n->right = new_node(key, val, m->element_size);

    m->size++;

  } else {

    map_insert(m, n->right, key, val);
  };
}
bool mapnode_find(mapnode *n, string key, void *out, int element_size) {

  if (string_eq(n->key, key)) {

    memcpy(out, n->val, element_size);

    return 1;

  } else if (string_gt(n->key, key)) {

    if (n->left == 0) {

      return 0;

    } else {

      return mapnode_find(&/* ? */ *n->left, key, out, element_size);
    };

  } else {

    if (n->right == 0) {

      return 0;

    } else {

      return mapnode_find(&/* ? */ *n->right, key, out, element_size);
    };
  };
}
bool mapnode_find2(mapnode *n, string key, int element_size) {

  if (string_eq(n->key, key)) {

    return 1;

  } else if (string_gt(n->key, key)) {

    if (isnil(n->left)) {

      return 0;

    } else {

      return mapnode_find2(&/* ? */ *n->left, key, element_size);
    };

  } else {

    if (isnil(n->right)) {

      return 0;

    } else {

      return mapnode_find2(&/* ? */ *n->right, key, element_size);
    };
  };
}
void map__set(map *m, string key, void *val) {

  if (isnil(m->root)) {

    m->root = new_node(key, val, m->element_size);

    m->size++;

    return;
  };

  map_insert(m, m->root, key, val);
}
int preorder_keys(mapnode *node, array_string *keys, int key_i) {

  int i = key_i;

  if (!node->is_empty) {

    array_string a = *keys;

    array_set(&/*q*/ a, i, &(string[]){node->key});

    i++;
  };

  if (!isnil(node->left)) {

    i = preorder_keys(node->left, keys, i);
  };

  if (!isnil(node->right)) {

    i = preorder_keys(node->right, keys, i);
  };

  return i;
}
array_string map_keys(map *m) {

  array_string keys =
      array_repeat(&(string[]){tos2((byte *)"")}, m->size, sizeof(string));

  if (isnil(m->root)) {

    return keys;
  };

  preorder_keys(m->root, &/*111*/ (array[]){keys}[0], 0);

  return keys;

  v_array_free(keys); // close_scope free
}
bool map_get(map m, string key, void *out) {

  if (m.root == 0) {

    return 0;
  };

  return mapnode_find(&/* ? */ *m.root, key, out, m.element_size);
}
void mapnode_delete(mapnode *n, string key, int element_size) {

  if (string_eq(n->key, key)) {

    memset(n->val, 0, element_size);

    n->is_empty = 1;

    return;

  } else if (string_gt(n->key, key)) {

    if (isnil(n->left)) {

      return;

    } else {

      mapnode_delete(n->left, key, element_size);
    };

  } else {

    if (isnil(n->right)) {

      return;

    } else {

      mapnode_delete(n->right, key, element_size);
    };
  };
}
void map_delete(map *m, string key) {

  mapnode_delete(m->root, key, m->element_size);

  m->size--;
}
bool map_exists(map m, string key) {

  v_panic(tos2((byte *)"map.exists(key) was removed from the language. Use "
                       "`key in map` instead."));
}
bool map__exists(map m, string key) {

  return !isnil(m.root) && mapnode_find2(&/* ? */ *m.root, key, m.element_size);
}
void map_print(map m) {

  println(tos2((byte *)"<<<<<<<<"));

  println(tos2((byte *)">>>>>>>>>>"));
}
void v_map_free(map m) {}
string map_string_str(map_string m) {

  if (m.size == 0) {

    return tos2((byte *)"{}");
  };

  strings__Builder sb = strings__new_builder(50);

  strings__Builder_writeln(&/* ? */ sb, tos2((byte *)"{"));

  map_string tmp10 = m;
  array_string keys_tmp10 = map_keys(&tmp10);
  for (int l = 0; l < keys_tmp10.len; l++) {
    string key = ((string *)keys_tmp10.data)[l];
    string val = {0};
    map_get(tmp10, key, &val);

    strings__Builder_writeln(
        &/* ? */ sb,
        _STR("  \"%.*s\" => \"%.*s\"", key.len, key.str, val.len, val.str));
  };

  strings__Builder_writeln(&/* ? */ sb, tos2((byte *)"}"));

  return strings__Builder_str(sb);
}
Option opt_ok(void *data, int size) {

  if (size >= 255) {

    v_panic(
        _STR("option size too big: %d (max is 255), this is a temporary limit",
             size));
  };

  Option res = (Option){
      .ok = 1,
      .error = tos((byte *)"", 0),
  };

  memcpy(res.data, data, size);

  return res;
}
Option v_error(string s) { return (Option){.error = s, .ok = 0}; }
strings__Builder strings__new_builder(int initial_size) {

  return (strings__Builder){.buf = _make(0, initial_size, sizeof(byte)),
                            .len = 0};
}
void strings__Builder_write(strings__Builder *b, string s) {

  array__push_many(&/* ? */ b->buf, s.str, s.len);

  b->len += s.len;
}
void strings__Builder_writeln(strings__Builder *b, string s) {

  array__push_many(&/* ? */ b->buf, s.str, s.len);

  _PUSH(&b->buf, ('\n'), tmp1, byte);

  b->len += s.len + 1;
}
string strings__Builder_str(strings__Builder b) {

  return (tos((byte *)b.buf.data, b.len));
}
void strings__Builder_cut(strings__Builder *b, int n) { b->len -= n; }
void strings__Builder_free(strings__Builder *b) { v_free(b->buf.data); }
string strings__repeat(byte c, int n) {

  if (n <= 0) {

    return tos2((byte *)"");
  };

  byte *arr = v_malloc(n + 1);

  for (int i = 0; i < n; i++) {

    arr[/*ptr*/ i] /*rbyte 1*/ = c;
  };

  arr[/*ptr*/ n] /*rbyte 1*/ = '\0';

  return (tos((byte *)arr, n));
}
array_string os__init_os_args(int argc, byteptr *argv) {

  array_string args =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

#ifdef _WIN32

  voidptr *args_list = ((voidptr *)(0));

  int args_count = 0;

  args_list = CommandLineToArgvW(GetCommandLine(), &/*vvar*/ args_count);

  for (int i = 0; i < args_count; i++) {

    _PUSH(&args,
          (string_from_wide(((u16 *)(args_list[/*ptr*/ i] /*rvoidptr 1*/)))),
          tmp5, string);
  };

  LocalFree(args_list);

#else

  for (int i = 0; i < argc; i++) {

    _PUSH(&args, ((tos2((byte *)argv[/*ptr*/ i] /*rbyteptr 0*/))), tmp7,
          string);
  };

#endif
  ;

  return args;

  v_array_free(args); // close_scope free
}
array_string os__parse_windows_cmd_line(byte *cmd) {

  string s = (tos2((byte *)cmd));

  return string_split(s, tos2((byte *)" "));
}
Option_string os__read_file(string path) {

  string mode = tos2((byte *)"rb");

  struct /*c struct init*/

      FILE *fp = 0;

#ifdef _WIN32

  fp = _wfopen(string_to_wide(path), string_to_wide(mode));

#else

  byte *cpath = path.str;

  fp = fopen(cpath, mode.str);

#endif
  ;

  if (isnil(fp)) {

    return v_error(_STR("failed to open file \"%.*s\"", path.len, path.str));
  };

  fseek(fp, 0, SEEK_END);

  int fsize = ftell(fp);

  rewind(fp);

  byte *str = v_malloc(fsize + 1);

  fread(str, fsize, 1, fp);

  fclose(fp);

  str[/*ptr*/ fsize] /*rbyte 1*/ = 0;

  string tmp14 = OPTION_CAST(string)((tos((byte *)str, fsize)));
  return opt_ok(&tmp14, sizeof(string));
}
int os__file_size(string path) {

  struct /*c struct init*/

      stat s;

#ifdef _WIN32

  _wstat(string_to_wide(path), &/*vvar*/ s);

#else

  stat(path.str, &/*vvar*/ s);

#endif
  ;

  return s.st_size;
}
void os__mv(string old, string new) {

#ifdef _WIN32

  _wrename(string_to_wide(old), string_to_wide(new));

#else

  rename(old.str, new.str);

#endif
  ;
}
array_string os__read_lines(string path) {

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  int buf_len = 1024;

  byte *buf = v_malloc(buf_len);

  string mode = tos2((byte *)"rb");

  struct /*c struct init*/

      FILE *fp = 0;

#ifdef _WIN32

  fp = _wfopen(string_to_wide(path), string_to_wide(mode));

#else

  fp = fopen(path.str, mode.str);

#endif
  ;

  if (isnil(fp)) {

    return res;
  };

  int buf_index = 0;

  while (fgets(buf + buf_index, buf_len - buf_index, fp) != 0) {

    int len = strlen(buf);

    if (len == buf_len - 1 && buf[/*ptr*/ len - 1] /*rbyte 1*/ != 10) {

      buf_len *= 2;

      buf = realloc(buf, buf_len);

      if (isnil(buf)) {

        v_panic(tos2((byte *)"Could not reallocate the read buffer"));
      };

      buf_index = len;

      continue;
    };

    if (buf[/*ptr*/ len - 1] /*rbyte 1*/ == 10 ||
        buf[/*ptr*/ len - 1] /*rbyte 1*/ == 13) {

      buf[/*ptr*/ len - 1] /*rbyte 1*/ = '\0';
    };

    if (len > 1 && buf[/*ptr*/ len - 2] /*rbyte 1*/ == 13) {

      buf[/*ptr*/ len - 2] /*rbyte 1*/ = '\0';
    };

    _PUSH(&res, (tos_clone(buf)), tmp23, string);

    buf_index = 0;
  };

  fclose(fp);

  return res;

  v_array_free(res); // close_scope free
}
array_ustring os__read_ulines(string path) {

  array_string lines = os__read_lines(path);

  array_ustring ulines =
      new_array_from_c_array(0, 0, sizeof(ustring), (ustring[]){0});

  array_string tmp26 = lines;
  ;
  for (int tmp27 = 0; tmp27 < tmp26.len; tmp27++) {
    string myline = ((string *)tmp26.data)[tmp27];

    _PUSH(&ulines, (string_ustring(myline)), tmp28, ustring);
  };

  return ulines;

  v_array_free(ulines); // close_scope free
}
Option_os__File os__open(string path) {

  os__File file;

#ifdef _WIN32

  u16 *wpath = string_to_wide(path);

  string mode = tos2((byte *)"rb");

  file = (struct os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(cpath, "rb")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(_STR("failed to open file \"%.*s\"", path.len, path.str));
  };

  os__File tmp33 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp33, sizeof(os__File));
}
Option_os__File os__create(string path) {

  os__File file = (os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(
      string_replace(path, tos2((byte *)"/"), tos2((byte *)"\\")));

  string mode = tos2((byte *)"wb");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(cpath, "wb")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(_STR("failed to create file \"%.*s\"", path.len, path.str));
  };

  os__File tmp38 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp38, sizeof(os__File));
}
Option_os__File os__open_append(string path) {

  os__File file = (os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(
      string_replace(path, tos2((byte *)"/"), tos2((byte *)"\\")));

  string mode = tos2((byte *)"ab");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(cpath, "ab")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(
        _STR("failed to create(append) file \"%.*s\"", path.len, path.str));
  };

  os__File tmp43 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp43, sizeof(os__File));
}
void os__File_write(os__File f, string s) { fputs(s.str, f.cfile); }
void os__File_write_bytes(os__File f, void *data, int size) {

  fwrite(data, 1, size, f.cfile);
}
void os__File_write_bytes_at(os__File f, void *data, int size, int pos) {

  fseek(f.cfile, pos, SEEK_SET);

  fwrite(data, 1, size, f.cfile);

  fseek(f.cfile, 0, SEEK_END);
}
void os__File_writeln(os__File f, string s) {

  fputs(s.str, f.cfile);

  fputs("\n", f.cfile);
}
void os__File_flush(os__File f) { fflush(f.cfile); }
void os__File_close(os__File f) { fclose(f.cfile); }
FILE *os__popen(string path) {

#ifdef _WIN32

  string mode = tos2((byte *)"rb");

  u16 *wpath = string_to_wide(path);

  return _wpopen(wpath, string_to_wide(mode));

#else

  byte *cpath = path.str;

  return popen(cpath, "r");

#endif
  ;
}
int os__pclose(FILE *f) {

#ifdef _WIN32

  return _pclose(f);

#else

  return pclose(f) / 256;

#endif
  ;
}
Option_os__Result os__exec(string cmd) {

  string pcmd = _STR("%.*s 2>&1", cmd.len, cmd.str);

  FILE *f = os__popen(pcmd);

  if (isnil(f)) {

    return v_error(_STR("exec(\"%.*s\") failed", cmd.len, cmd.str));
  };

  byte buf[1000] = {0};

  string res = tos2((byte *)"");

  while (fgets(buf, 1000, f) != 0) {

    res = string_add(res, tos(buf, strlen(buf)));
  };

  res = string_trim_space(res);

  int exit_code = os__pclose(f);

  os__Result tmp52 = OPTION_CAST(os__Result)(
      (os__Result){.output = res, .exit_code = exit_code});
  return opt_ok(&tmp52, sizeof(os__Result));
}
int os__system(string cmd) {

  int ret = ((int)(0));

#ifdef _WIN32

  ret = _wsystem(string_to_wide(cmd));

#else

  ret = system(cmd.str);

#endif
  ;

  if (ret == -1) {

    os__print_c_errno();
  };

  return ret;
}
string os__getenv(string key) {

#ifdef _WIN32

  void *s = _wgetenv(string_to_wide(key));

  if (isnil(s)) {

    return tos2((byte *)"");
  };

  return string_from_wide(s);

#else

  byte *s = getenv(key.str);

  if (isnil(s)) {

    return tos2((byte *)"");
  };

  return (tos2((byte *)s));

#endif
  ;
}
int os__setenv(string name, string value, bool overwrite) {

#ifdef _WIN32

  string format = _STR("%.*s=%.*s", name.len, name.str, value.len, value.str);

  if (overwrite) {

    return _putenv(format.str);
  };

  return -1;

#else

  return setenv(name.str, value.str, overwrite);

#endif
  ;
}
int os__unsetenv(string name) {

#ifdef _WIN32

  string format = _STR("%.*s=", name.len, name.str);

  return _putenv(format.str);

#else

  return unsetenv(name.str);

#endif
  ;
}
bool os__file_exists(string _path) {

#ifdef _WIN32

  string path = string_replace(_path, tos2((byte *)"/"), tos2((byte *)"\\"));

  return _waccess(string_to_wide(path), 0) != -1;

#else

  return access(_path.str, 0) != -1;

#endif
  ;
}
void os__rm(string path) {

#ifdef _WIN32

  _wremove(string_to_wide(path));

#else

  remove(path.str);

#endif
  ;
}
void os__rmdir(string path) {

#ifndef _WIN32

  rmdir(path.str);

#else

  RemoveDirectory(string_to_wide(path));

#endif
  ;
}
void os__print_c_errno() {}
string os__ext(string path) {

  int pos = string_last_index(path, tos2((byte *)"."));

  if (pos == -1) {

    return tos2((byte *)"");
  };

  return string_right(path, pos);
}
string os__dir(string path) {

  if (string_eq(path, tos2((byte *)"."))) {

    return os__getwd();
  };

  int pos = string_last_index(path, os__PathSeparator);

  if (pos == -1) {

    return tos2((byte *)".");
  };

  return string_left(path, pos);
}
string os__path_sans_ext(string path) {

  int pos = string_last_index(path, tos2((byte *)"."));

  if (pos == -1) {

    return path;
  };

  return string_left(path, pos);
}
string os__basedir(string path) {

  int pos = string_last_index(path, tos2((byte *)"/"));

  if (pos == -1) {

    return path;
  };

  return string_left(path, pos + 1);
}
string os__filename(string path) {

  return string_all_after(path, tos2((byte *)"/"));
}
string os__get_line() {

  string str = os__get_raw_line();

#ifdef _WIN32

  return string_trim_right(str, tos2((byte *)"\r\n"));

#else

  return string_trim_right(str, tos2((byte *)"\n"));

#endif
  ;
}
string os__get_raw_line() {

#ifdef _WIN32

  int maxlinechars = 256;

  u16 *buf = ((u16 *)(v_malloc(maxlinechars * 2)));

  int res = ((int)(fgetws(buf, maxlinechars, stdin)));

  int len = ((int)(wcslen(buf)));

  if (0 != res) {

    return string_from_wide2(buf, len);
  };

  return tos2((byte *)"");

#else

  u64 max = ((u64)(256));

  byte *buf = v_malloc(((int)(max)));

  int nr_chars = getline(&/*vvar*/ buf, &/*vvar*/ max, stdin);

  if (nr_chars == 0) {

    return tos2((byte *)"");
  };

  return (tos((byte *)buf, nr_chars));

#endif
  ;
}
array_string os__get_lines() {

  string line = tos2((byte *)"");

  array_string inputstr =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  while (1) {

    line = os__get_line();

    if ((line.len <= 0)) {

      break;
    };

    line = string_trim_space(line);

    _PUSH(&inputstr, (line), tmp73, string);
  };

  return inputstr;

  v_array_free(inputstr); // close_scope free
}
string os__get_lines_joined() {

  string line = tos2((byte *)"");

  string inputstr = tos2((byte *)"");

  while (1) {

    line = os__get_line();

    if ((line.len <= 0)) {

      break;
    };

    line = string_trim_space(line);

    inputstr = string_add(inputstr, line);
  };

  return inputstr;
}
string os__user_os() {

#ifdef __linux__

  return tos2((byte *)"linux");

#endif
  ;

#ifdef __APPLE__

  return tos2((byte *)"mac");

#endif
  ;

#ifdef _WIN32

  return tos2((byte *)"windows");

#endif
  ;

#ifdef __FreeBSD__

  return tos2((byte *)"freebsd");

#endif
  ;

#ifdef __OpenBSD__

  return tos2((byte *)"openbsd");

#endif
  ;

#ifdef __NetBSD__

  return tos2((byte *)"netbsd");

#endif
  ;

#ifdef __DragonFly__

  return tos2((byte *)"dragonfly");

#endif
  ;

#ifdef _MSC_VER

  return tos2((byte *)"windows");

#endif
  ;

  return tos2((byte *)"unknown");
}
string os__home_dir() {

  string home = os__getenv(tos2((byte *)"HOME"));

#ifdef _WIN32

  home = os__getenv(tos2((byte *)"HOMEDRIVE"));

  if (home.len == 0) {

    home = os__getenv(tos2((byte *)"SYSTEMDRIVE"));
  };

  string homepath = os__getenv(tos2((byte *)"HOMEPATH"));

  if (homepath.len == 0) {

    homepath = string_add(tos2((byte *)"\\Users\\"),
                          os__getenv(tos2((byte *)"USERNAME")));
  };

  home = string_add(home, homepath);

#endif
  ;

  home = string_add(home, tos2((byte *)"/"));

  return home;
}
void os__write_file(string path, string text) {

  Option_os__File tmp78 = os__create(path);
  if (!tmp78.ok) {
    string err = tmp78.error;

    return;
  }
  os__File f = *(os__File *)tmp78.data;
  ;

  os__File_write(f, text);

  os__File_close(f);
}
void os__clear() {

  printf("\x1b[2J");

  printf("\x1b[H");
}
void os__on_segfault(void *f) {

#ifdef _WIN32

  return;

#endif
  ;

#ifdef __APPLE__

  struct /*c struct init*/

      sigaction sa;

  memset(&/*vvar*/ sa, 0, sizeof(sigaction));

  sigemptyset(&/*vvar*/ sa.sa_mask);

  sa.sa_sigaction = f;

  sa.sa_flags = SA_SIGINFO;

  sigaction(SIGSEGV, &/*vvar*/ sa, 0);

#endif
  ;
}
string os__executable() {

#ifdef __linux__

  byte *result = v_malloc(os__MAX_PATH);

  int count = ((int)(readlink("/proc/self/exe", result, os__MAX_PATH)));

  if (count < 0) {

    v_panic(tos2((byte *)"error reading /proc/self/exe to get exe path"));
  };

  return (tos((byte *)result, count));

#endif
  ;

#ifdef _WIN32

  int max = 512;

  u16 *result = ((u16 *)(v_malloc(max * 2)));

  int len = ((int)(GetModuleFileName(0, result, max)));

  return string_from_wide2(result, len);

#endif
  ;

#ifdef __APPLE__

  byte *result = v_malloc(os__MAX_PATH);

  void *pid = getpid();

  void *ret = proc_pidpath(pid, result, os__MAX_PATH);

  if (ret <= 0) {

    println(tos2((byte *)"os.executable() failed"));

    return tos2((byte *)".");
  };

  return (tos2((byte *)result));

#endif
  ;

#ifdef __FreeBSD__

  byte *result = v_malloc(os__MAX_PATH);

  array_int mib =
      new_array_from_c_array(4, 4, sizeof(int), (int[]){1, 14, 12, -1});

  int size = os__MAX_PATH;

  sysctl(mib.data, 4, result, &/*vvar*/ size, 0, 0);

  return (tos2((byte *)result));

  v_array_free(mib); // close_scope free
#endif
  ;

#ifdef __OpenBSD__

  return (*(string *)array__get(os__args, 0));

#endif
  ;

#ifdef __NetBSD__

  byte *result = v_malloc(os__MAX_PATH);

  int count = ((int)(readlink("/proc/curproc/exe", result, os__MAX_PATH)));

  if (count < 0) {

    v_panic(tos2((byte *)"error reading /proc/curproc/exe to get exe path"));
  };

  return (tos((byte *)result, count));

#endif
  ;

#ifdef __DragonFly__

  byte *result = v_malloc(os__MAX_PATH);

  int count = ((int)(readlink("/proc/curproc/file", result, os__MAX_PATH)));

  if (count < 0) {

    v_panic(tos2((byte *)"error reading /proc/curproc/file to get exe path"));
  };

  return (tos((byte *)result, count));

#endif
  ;

  return tos2((byte *)".");
}
bool os__is_dir(string path) {

#ifdef _WIN32

  return os__dir_exists(path);

#else

  struct /*c struct init*/

      stat statbuf;

  byte *cstr = path.str;

  if (stat(cstr, &/*vvar*/ statbuf) != 0) {

    return 0;
  };

  return (statbuf.st_mode & os__S_IFMT) == os__S_IFDIR;

#endif
  ;
}
void os__chdir(string path) {

#ifdef _WIN32

  _wchdir(string_to_wide(path));

#else

  chdir(path.str);

#endif
  ;
}
string os__getwd() {

#ifdef _WIN32

  int max = 512;

  u16 *buf = ((u16 *)(v_malloc(max * 2)));

  if (_wgetcwd(buf, max) == 0) {

    return tos2((byte *)"");
  };

  return string_from_wide(buf);

#else

  byte *buf = v_malloc(512);

  if (getcwd(buf, 512) == 0) {

    return tos2((byte *)"");
  };

  return (tos2((byte *)buf));

#endif
  ;
}
string os__realpath(string fpath) {

  byte *fullpath = v_malloc(os__MAX_PATH);

  int res = 0;

#ifdef _WIN32

  res = ((int)(_fullpath(fullpath, fpath.str, os__MAX_PATH)));

#else

  res = ((int)(realpath(fpath.str, fullpath)));

#endif
  ;

  if (res != 0) {

    return (tos((byte *)fullpath, strlen(fullpath)));
  };

  return fpath;
}
array_string os__walk_ext(string path, string ext) {

  if (!os__is_dir(path)) {

    return new_array_from_c_array(0, 0, sizeof(string), (string[]){0});
  };

  array_string files = os__ls(path);

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  array_string tmp106 = files;
  ;
  for (int i = 0; i < tmp106.len; i++) {
    string file = ((string *)tmp106.data)[i];

    if (string_starts_with(file, tos2((byte *)"."))) {

      continue;
    };

    string p = string_add(string_add(path, tos2((byte *)"/")), file);

    if (os__is_dir(p)) {

      _PUSH_MANY(&res, (os__walk_ext(p, ext)), tmp108, array_string);

    } else if (string_ends_with(file, ext)) {

      _PUSH(&res, (p), tmp109, string);
    };
  };

  return res;

  v_array_free(res); // close_scope free
}
void os__signal(int signum, void *handler) { signal(signum, handler); }
int os__fork() {

#ifndef _WIN32

  void *pid = fork();

  return pid;

#endif
  ;

  v_panic(tos2((byte *)"os.fork not supported in windows"));
}
int os__wait() {

#ifndef _WIN32

  void *pid = wait(0);

  return pid;

#endif
  ;

  v_panic(tos2((byte *)"os.wait not supported in windows"));
}
int os__file_last_mod_unix(string path) {

  struct /*c struct init*/

      stat attr;

  stat(path.str, &/*vvar*/ attr);

  return attr.st_mtime;
}
void os__log(string s) {}
void os__flush_stdout() { fflush(stdout); }
void os__print_backtrace() {}
array_string os__ls(string path) {

  os__win32finddata find_file_data = (os__win32finddata){.dwFileAttributes = 0,
                                                         .nFileSizeHigh = 0,
                                                         .nFileSizeLow = 0,
                                                         .dwReserved0 = 0,
                                                         .dwReserved1 = 0,
                                                         .dwFileType = 0,
                                                         .dwCreatorType = 0,
                                                         .wFinderFlags = 0};

  array_string dir_files =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (!os__dir_exists(path)) {

    printf("ls() couldnt open dir \"%.*s\" (does not exist).\n", path.len,
           path.str);

    return dir_files;
  };

  string path_files = _STR("%.*s\\*", path.len, path.str);

  void *h_find_files =
      FindFirstFile(string_to_wide(path_files), &/*vvar*/ find_file_data);

  string first_filename = string_from_wide(((u16 *)(find_file_data.cFileName)));

  if (string_ne(first_filename, tos2((byte *)".")) &&
      string_ne(first_filename, tos2((byte *)".."))) {

    _PUSH(&dir_files, (first_filename), tmp6, string);
  };

  while (FindNextFile(h_find_files, &/*vvar*/ find_file_data)) {

    string filename = string_from_wide(((u16 *)(find_file_data.cFileName)));

    if (string_ne(filename, tos2((byte *)".")) &&
        string_ne(filename, tos2((byte *)".."))) {

      _PUSH(&dir_files, (string_clone(filename)), tmp8, string);
    };
  };

  FindClose(h_find_files);

  return dir_files;

  v_array_free(dir_files); // close_scope free
}
bool os__dir_exists(string path) {

  string _path = string_replace(path, tos2((byte *)"/"), tos2((byte *)"\\"));

  int attr = ((int)(GetFileAttributes(string_to_wide(_path))));

  if (attr == INVALID_FILE_ATTRIBUTES) {

    return 0;
  };

  if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0) {

    return 1;
  };

  return 0;
}
void os__mkdir(string path) {

  string _path = string_replace(path, tos2((byte *)"/"), tos2((byte *)"\\"));

  if (string_last_index(_path, tos2((byte *)"\\")) != -1) {

    os__mkdir(string_all_before_last(_path, tos2((byte *)"\\")));
  };

  CreateDirectory(string_to_wide(_path), 0);
}
HANDLE os__get_file_handle(string path) {

  string mode = tos2((byte *)"rb");

  void *_fd = _wfopen(string_to_wide(path), string_to_wide(mode));

  if (_fd == 0) {

    return ((HANDLE)(os__INVALID_HANDLE_VALUE));
  };

  void *_handle = _get_osfhandle(_fileno(_fd));

  return _handle;
}
Option_string os__get_module_filename(HANDLE handle) {

  int sz = ((int)(4096));

  u16 *buf = ((u16 *)(v_malloc(4096)));

  while (1) {

    void *status = GetModuleFileName(handle, &/*vvar*/ buf, sz);

    if ((status == os__SUCCESS)) { /* case */

      string _filename = string_from_wide2(buf, sz);

      string tmp19 = OPTION_CAST(string)(_filename);
      return opt_ok(&tmp19, sizeof(string));

    } else { // default:

      return v_error(tos2((byte *)"Cannot get file name from handle."));
    };
  };

  v_panic(tos2((byte *)"this should be unreachable"));
}
void *os__ptr_win_get_error_msg(u32 code) {

  voidptr buf = ((voidptr)(0));

  if (code > ((u32)(os__MAX_ERROR_CODE))) {

    return buf;
  };

  FormatMessage(os__FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    os__FORMAT_MESSAGE_FROM_SYSTEM |
                    os__FORMAT_MESSAGE_IGNORE_INSERTS,
                0, code, MAKELANGID(os__LANG_NEUTRAL, os__SUBLANG_DEFAULT),
                &/*vvar*/ buf, 0, 0);

  return buf;
}
string os__get_error_msg(int code) {

  if (code < 0) {

    return tos2((byte *)"");
  };

  void *_ptr_text = os__ptr_win_get_error_msg(((u32)(code)));

  if (_ptr_text == 0) {

    return tos2((byte *)"");
  };

  return tos(_ptr_text, strlen(_ptr_text));
}
f64 math__abs(f64 a) {

  if (a < 0) {

    return -a;
  };

  return a;
}
f64 math__acos(f64 a) { return acos(a); }
f64 math__asin(f64 a) { return asin(a); }
f64 math__atan(f64 a) { return atan(a); }
f64 math__atan2(f64 a, f64 b) { return atan2(a, b); }
f64 math__cbrt(f64 a) { return cbrt(a); }
int math__ceil(f64 a) { return ceil(a); }
f64 math__cos(f64 a) { return cos(a); }
f64 math__cosh(f64 a) { return cosh(a); }
f64 math__degrees(f64 radians) { return radians * (180.0 / math__Pi); }
f64 math__exp(f64 a) { return exp(a); }
array_int math__digits(int _n, int base) {

  int n = _n;

  int sign = 1;

  if (n < 0) {

    sign = -1;

    n = -n;
  };

  array_int res = new_array_from_c_array(0, 0, sizeof(int), (int[]){0});

  while (n != 0) {

    _PUSH(&res, ((n % base) * sign), tmp4, int);

    n /= base;
  };

  return res;

  v_array_free(res); // close_scope free
}
f64 math__erf(f64 a) { return erf(a); }
f64 math__erfc(f64 a) { return erfc(a); }
f64 math__exp2(f64 a) { return exp2(a); }
f64 math__floor(f64 a) { return floor(a); }
f64 math__fmod(f64 a, f64 b) { return fmod(a, b); }
f64 math__gamma(f64 a) { return tgamma(a); }
i64 math__gcd(i64 a_, i64 b_) {

  i64 a = a_;

  i64 b = b_;

  if (a < 0) {

    a = -a;
  };

  if (b < 0) {

    b = -b;
  };

  while (b != 0) {

    a %= b;

    if (a == 0) {

      return b;
    };

    b %= a;
  };

  return a;
}
f64 math__hypot(f64 a, f64 b) { return hypot(a, b); }
i64 math__lcm(i64 a, i64 b) {

  if (a == 0) {

    return a;
  };

  i64 res = a * (b / math__gcd(b, a));

  if (res < 0) {

    return -res;
  };

  return res;
}
f64 math__log(f64 a) { return log(a); }
f64 math__log2(f64 a) { return log2(a); }
f64 math__log10(f64 a) { return log10(a); }
f64 math__log_gamma(f64 a) { return lgamma(a); }
f64 math__log_n(f64 a, f64 b) { return log(a) / log(b); }
f64 math__max(f64 a, f64 b) {

  if (a > b) {

    return a;
  };

  return b;
}
f64 math__min(f64 a, f64 b) {

  if (a < b) {

    return a;
  };

  return b;
}
f64 math__pow(f64 a, f64 b) { return pow(a, b); }
f64 math__radians(f64 degrees) { return degrees * (math__Pi / 180.0); }
f64 math__round(f64 f) { return round(f); }
f64 math__sin(f64 a) { return sin(a); }
f64 math__sinh(f64 a) { return sinh(a); }
f64 math__sqrt(f64 a) { return sqrt(a); }
f64 math__tan(f64 a) { return tan(a); }
f64 math__tanh(f64 a) { return tanh(a); }
f64 math__trunc(f64 a) { return trunc(a); }
void rand__seed(int s) { srand(s); }
int rand__next(int max) { return rand() % max; }
string term___format(string msg, string open, string close) {

  return string_add(
      string_add(
          string_add(
              string_add(string_add(string_add(tos2((byte *)"\x1b["), open),
                                    tos2((byte *)"m")),
                         msg),
              tos2((byte *)"\x1b[")),
          close),
      tos2((byte *)"m"));
}
string term___format_rgb(int r, int g, int b, string msg, string open,
                         string close) {

  return string_add(
      string_add(
          string_add(
              string_add(
                  string_add(
                      string_add(
                          string_add(
                              string_add(
                                  string_add(
                                      string_add(
                                          string_add(
                                              string_add(tos2((byte *)"\x1b["),
                                                         open),
                                              tos2((byte *)";2;")),
                                          int_str(r)),
                                      tos2((byte *)";")),
                                  int_str(g)),
                              tos2((byte *)";")),
                          int_str(b)),
                      tos2((byte *)"m")),
                  msg),
              tos2((byte *)"\x1b[")),
          close),
      tos2((byte *)"m"));
}
string term__rgb(int r, int g, int b, string msg) {

  return term__format_rgb(r, g, b, msg, tos2((byte *)"38"), tos2((byte *)"39"));
}
string term__bg_rgb(int r, int g, int b, string msg) {

  return term__format_rgb(r, g, b, msg, tos2((byte *)"48"), tos2((byte *)"49"));
}
string term__hex(int hex, string msg) {

  return term__format_rgb(hex >> 16, hex >> 8 & 0xFF, hex & 0xFF, msg,
                          tos2((byte *)"38"), tos2((byte *)"39"));
}
string term__bg_hex(int hex, string msg) {

  return term__format_rgb(hex >> 16, hex >> 8 & 0xFF, hex & 0xFF, msg,
                          tos2((byte *)"48"), tos2((byte *)"49"));
}
string term__bg_black(string msg) {

  return term__format(msg, tos2((byte *)"40"), tos2((byte *)"49"));
}
string term__bright_bg_black(string msg) {

  return term__format(msg, tos2((byte *)"100"), tos2((byte *)"49"));
}
string term__bg_blue(string msg) {

  return term__format(msg, tos2((byte *)"44"), tos2((byte *)"49"));
}
string term__bright_bg_blue(string msg) {

  return term__format(msg, tos2((byte *)"104"), tos2((byte *)"49"));
}
string term__bg_cyan(string msg) {

  return term__format(msg, tos2((byte *)"46"), tos2((byte *)"49"));
}
string term__bright_bg_cyan(string msg) {

  return term__format(msg, tos2((byte *)"106"), tos2((byte *)"49"));
}
string term__bg_green(string msg) {

  return term__format(msg, tos2((byte *)"42"), tos2((byte *)"49"));
}
string term__bright_bg_green(string msg) {

  return term__format(msg, tos2((byte *)"102"), tos2((byte *)"49"));
}
string term__bg_magenta(string msg) {

  return term__format(msg, tos2((byte *)"45"), tos2((byte *)"49"));
}
string term__bright_bg_magenta(string msg) {

  return term__format(msg, tos2((byte *)"105"), tos2((byte *)"49"));
}
string term__bg_red(string msg) {

  return term__format(msg, tos2((byte *)"41"), tos2((byte *)"49"));
}
string term__bright_bg_red(string msg) {

  return term__format(msg, tos2((byte *)"101"), tos2((byte *)"49"));
}
string term__bg_white(string msg) {

  return term__format(msg, tos2((byte *)"47"), tos2((byte *)"49"));
}
string term__bright_bg_white(string msg) {

  return term__format(msg, tos2((byte *)"107"), tos2((byte *)"49"));
}
string term__bg_yellow(string msg) {

  return term__format(msg, tos2((byte *)"43"), tos2((byte *)"49"));
}
string term__bright_bg_yellow(string msg) {

  return term__format(msg, tos2((byte *)"103"), tos2((byte *)"49"));
}
string term__black(string msg) {

  return term__format(msg, tos2((byte *)"30"), tos2((byte *)"39"));
}
string term__bright_black(string msg) {

  return term__format(msg, tos2((byte *)"90"), tos2((byte *)"39"));
}
string term__blue(string msg) {

  return term__format(msg, tos2((byte *)"34"), tos2((byte *)"39"));
}
string term__bright_blue(string msg) {

  return term__format(msg, tos2((byte *)"94"), tos2((byte *)"39"));
}
string term__bold(string msg) {

  return term__format(msg, tos2((byte *)"1"), tos2((byte *)"22"));
}
string term__cyan(string msg) {

  return term__format(msg, tos2((byte *)"36"), tos2((byte *)"39"));
}
string term__bright_cyan(string msg) {

  return term__format(msg, tos2((byte *)"96"), tos2((byte *)"39"));
}
string term__dim(string msg) {

  return term__format(msg, tos2((byte *)"2"), tos2((byte *)"22"));
}
string term__green(string msg) {

  return term__format(msg, tos2((byte *)"32"), tos2((byte *)"39"));
}
string term__bright_green(string msg) {

  return term__format(msg, tos2((byte *)"92"), tos2((byte *)"39"));
}
string term__gray(string msg) { return term__bright_black(msg); }
string term__hidden(string msg) {

  return term__format(msg, tos2((byte *)"8"), tos2((byte *)"28"));
}
string term__italic(string msg) {

  return term__format(msg, tos2((byte *)"3"), tos2((byte *)"23"));
}
string term__inverse(string msg) {

  return term__format(msg, tos2((byte *)"7"), tos2((byte *)"27"));
}
string term__magenta(string msg) {

  return term__format(msg, tos2((byte *)"35"), tos2((byte *)"39"));
}
string term__bright_magenta(string msg) {

  return term__format(msg, tos2((byte *)"95"), tos2((byte *)"39"));
}
string term__reset(string msg) {

  return term__format(msg, tos2((byte *)"0"), tos2((byte *)"0"));
}
string term__red(string msg) {

  return term__format(msg, tos2((byte *)"31"), tos2((byte *)"39"));
}
string term__bright_red(string msg) {

  return term__format(msg, tos2((byte *)"91"), tos2((byte *)"39"));
}
string term__strikethrough(string msg) {

  return term__format(msg, tos2((byte *)"9"), tos2((byte *)"29"));
}
string term__underline(string msg) {

  return term__format(msg, tos2((byte *)"4"), tos2((byte *)"24"));
}
string term__white(string msg) {

  return term__format(msg, tos2((byte *)"37"), tos2((byte *)"39"));
}
string term__bright_white(string msg) {

  return term__format(msg, tos2((byte *)"97"), tos2((byte *)"39"));
}
string term__yellow(string msg) {

  return term__format(msg, tos2((byte *)"33"), tos2((byte *)"39"));
}
string term__bright_yellow(string msg) {

  return term__format(msg, tos2((byte *)"93"), tos2((byte *)"39"));
}
string term__format(string msg, string open, string close) {

  return term___format(msg, open, close);
}
string term__format_rgb(int r, int g, int b, string msg, string open,
                        string close) {

  return term___format_rgb(r, g, b, msg, open, close);
}
void term__set_cursor_position(int x, int y) {

  print(string_add(_STR("\x1b[%d;%d", y, x), tos2((byte *)"H")));
}
void term__move(int n, string direction) {

  print(_STR("\x1b[%d%.*s", n, direction.len, direction.str));
}
void term__cursor_up(int n) { term__move(n, tos2((byte *)"A")); }
void term__cursor_down(int n) { term__move(n, tos2((byte *)"B")); }
void term__cursor_forward(int n) { term__move(n, tos2((byte *)"C")); }
void term__cursor_back(int n) { term__move(n, tos2((byte *)"D")); }
void term__erase_display(string t) {

  print(string_add(string_add(tos2((byte *)"\x1b["), t), tos2((byte *)"J")));
}
void term__erase_toend() { term__erase_display(tos2((byte *)"0")); }
void term__erase_tobeg() { term__erase_display(tos2((byte *)"1")); }
void term__erase_clear() { term__erase_display(tos2((byte *)"2")); }
void term__erase_del_clear() { term__erase_display(tos2((byte *)"3")); }
void term__erase_line(string t) {

  print(string_add(string_add(tos2((byte *)"\x1b["), t), tos2((byte *)"K")));
}
void term__erase_line_toend() { term__erase_line(tos2((byte *)"0")); }
void term__erase_line_tobeg() { term__erase_line(tos2((byte *)"1")); }
void term__erase_line_clear() { term__erase_line(tos2((byte *)"2")); }
void term__show_cursor() { print(tos2((byte *)"\x1b[?25h")); }
void term__hide_cursor() { print(tos2((byte *)"\x1b[?25l")); }
void time__remove_me_when_c_bug_is_fixed() {}
time__Time time__now() {

  void *t = time(0);

  struct /*c struct init*/

      tm *now = 0;

  now = localtime(&/*vvar*/ t);

  return time__convert_ctime(*now);
}
time__Time time__random() {

  int now_unix = time__now().uni;

  int rand_unix = rand__next(now_unix);

  return time__unix(rand_unix);
}
time__Time time__unix(int abs) {

  int d = abs / time__secondsPerDay;

  int n = d / time__daysPer400Years;

  int y = 400 * n;

  d -= time__daysPer400Years * n;

  n = d / time__daysPer100Years;

  n -= n >> 2;

  y += 100 * n;

  d -= time__daysPer100Years * n;

  n = d / time__daysPer4Years;

  y += 4 * n;

  d -= time__daysPer4Years * n;

  n = d / 365;

  n -= n >> 2;

  y += n;

  d -= 365 * n;

  int yday = ((int)(d));

  int day = yday;

  int year = abs / ((int)(3.154e+7)) + 1970;

  int hour = ((int)(abs % time__secondsPerDay)) / time__secondsPerHour;

  int minute = ((int)(abs % time__secondsPerHour)) / time__secondsPerMinute;

  int second = ((int)(abs % time__secondsPerMinute));

  if (time__is_leap_year(year)) {

    if (day > 31 + 29 - 1) {

      day--;

    } else if (day == 31 + 29 - 1) {

      day = 29;

      return (struct time__Time){.year = year,
                                 .month = 2,
                                 .day = day,
                                 .hour = hour,
                                 .minute = minute,
                                 .second = second,
                                 .uni = 0};
    };
  };

  int month = day / 31;

  int begin = 0;

  int end = ((int)((*(int *)array__get(time__daysBefore, month + 1))));

  if (day >= end) {

    month++;

    begin = end;

  } else {

    begin = ((int)((*(int *)array__get(time__daysBefore, month))));
  };

  month++;

  day = day - begin + 1;

  return (time__Time){.year = year,
                      .month = month,
                      .day = day,
                      .hour = hour,
                      .minute = minute,
                      .second = second,
                      .uni = 0};
}
time__Time time__convert_ctime(struct /*TM*/ tm t) {

  return (time__Time){.year = t.tm_year + 1900,
                      .month = t.tm_mon + 1,
                      .day = t.tm_mday,
                      .hour = t.tm_hour,
                      .minute = t.tm_min,
                      .second = t.tm_sec,
                      .uni = mktime(&/*vvar*/ t)};
}
string time__Time_format_ss(time__Time t) {

  return _STR("%d-%02d-%02d %02d:%02d:%02d", t.year, t.month, t.day, t.hour,
              t.minute, t.second);
}
string time__Time_format(time__Time t) {

  return _STR("%d-%02d-%02d %02d:%02d", t.year, t.month, t.day, t.hour,
              t.minute);
}
string time__Time_smonth(time__Time t) {

  int i = t.month - 1;

  return string_substr(time__Months, i * 3, (i + 1) * 3);
}
string time__Time_hhmm(time__Time t) {

  return _STR("%02d:%02d", t.hour, t.minute);
}
string time__Time_hhmm12(time__Time t) {

  string am = tos2((byte *)"am");

  int hour = t.hour;

  if (t.hour > 11) {

    am = tos2((byte *)"pm");
  };

  if (t.hour > 12) {

    hour = hour - 12;
  };

  if (t.hour == 0) {

    hour = 12;
  };

  return _STR("%d:%02d %.*s", hour, t.minute, am.len, am.str);
}
string time__Time_hhmmss(time__Time t) {

  return _STR("%02d:%02d:%02d", t.hour, t.minute, t.second);
}
string time__Time_ymmdd(time__Time t) {

  return _STR("%d-%02d-%02d", t.year, t.month, t.day);
}
string time__Time_md(time__Time t) {

  string s = _STR("%.*s %d", time__Time_smonth(t).len, time__Time_smonth(t).str,
                  t.day);

  return s;
}
string time__Time_clean(time__Time t) {

  time__Time nowe = time__now();

  if (t.month == nowe.month && t.year == nowe.year && t.day == nowe.day) {

    return time__Time_hhmm(t);
  };

  if (t.year == nowe.year) {

    return _STR("%.*s %d %.*s", time__Time_smonth(t).len,
                time__Time_smonth(t).str, t.day, time__Time_hhmm(t).len,
                time__Time_hhmm(t).str);
  };

  return time__Time_format(t);
}
string time__Time_clean12(time__Time t) {

  time__Time nowe = time__now();

  if (t.month == nowe.month && t.year == nowe.year && t.day == nowe.day) {

    return time__Time_hhmm12(t);
  };

  if (t.year == nowe.year) {

    return _STR("%.*s %d %.*s", time__Time_smonth(t).len,
                time__Time_smonth(t).str, t.day, time__Time_hhmm12(t).len,
                time__Time_hhmm12(t).str);
  };

  return time__Time_format(t);
}
time__Time time__parse(string s) {

  int pos = string_index(s, tos2((byte *)" "));

  if (pos <= 0) {

    println(tos2((byte *)"bad time format"));

    return time__now();
  };

  string symd = string_left(s, pos);

  array_string ymd = string_split(symd, tos2((byte *)"-"));

  if (ymd.len != 3) {

    println(tos2((byte *)"bad time format"));

    return time__now();
  };

  string shms = string_right(s, pos);

  array_string hms = string_split(shms, tos2((byte *)":"));

  string hour = (*(string *)array__get(hms, 0));

  string minute = (*(string *)array__get(hms, 1));

  string second = (*(string *)array__get(hms, 2));

  return time__new_time(
      (time__Time){.year = v_string_int((*(string *)array__get(ymd, 0))),
                   .month = v_string_int((*(string *)array__get(ymd, 1))),
                   .day = v_string_int((*(string *)array__get(ymd, 2))),
                   .hour = v_string_int(hour),
                   .minute = v_string_int(minute),
                   .second = v_string_int(second),
                   .uni = 0});
}
time__Time time__new_time(time__Time t) {

  return (time__Time){
      .uni = time__Time_calc_unix(&/* ? */ t),
      .year = t.year,
      .month = t.month,
      .day = t.day,
      .hour = t.hour,
      .minute = t.minute,
      .second = t.second,
  };
}
int time__Time_calc_unix(time__Time *t) {

  if (t->uni != 0) {

    return t->uni;
  };

  struct /*TM*/ tm tt = (struct tm){.tm_sec = t->second,
                                    .tm_min = t->minute,
                                    .tm_hour = t->hour,
                                    .tm_mday = t->day,
                                    .tm_mon = t->month - 1,
                                    .tm_year = t->year - 1900};

  return mktime(&/*vvar*/ tt);
}
time__Time time__Time_add_seconds(time__Time t, int seconds) {

  return time__unix(t.uni + seconds);
}
int time__since(time__Time t) { return 0; }
string time__Time_relative(time__Time t) {

  time__Time now = time__now();

  int secs = now.uni - t.uni;

  if (secs <= 30) {

    return tos2((byte *)"now");
  };

  if (secs < 60) {

    return tos2((byte *)"1m");
  };

  if (secs < 3600) {

    return _STR("%dm", secs / 60);
  };

  if (secs < 3600 * 24) {

    return _STR("%dh", secs / 3600);
  };

  if (secs < 3600 * 24 * 5) {

    return _STR("%dd", secs / 3600 / 24);
  };

  if (secs > 3600 * 24 * 10000) {

    return tos2((byte *)"");
  };

  return time__Time_md(t);
}
int time__day_of_week(int y, int m, int d) {

  array_int t = new_array_from_c_array(
      12, 12, sizeof(int), (int[]){0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4});

  int sy = y;

  if ((m < 3)) {

    sy = sy - 1;
  };

  return (sy + sy / 4 - sy / 100 + sy / 400 + (*(int *)array__get(t, m - 1)) +
          d - 1) %
             7 +
         1;

  v_array_free(t); // close_scope free
}
int time__Time_day_of_week(time__Time t) {

  return time__day_of_week(t.year, t.month, t.day);
}
string time__Time_weekday_str(time__Time t) {

  int i = time__Time_day_of_week(t) - 1;

  return string_substr(time__Days, i * 3, (i + 1) * 3);
}
i64 time__ticks() {

#ifdef _WIN32

  return GetTickCount();

#else

  struct /*c struct init*/

      timeval ts;

  gettimeofday(&/*vvar*/ ts, 0);

  return ts.tv_sec * 1000 + (ts.tv_usec / 1000);

#endif
  ;
}
void time__sleep(int seconds) {

#ifdef _WIN32

  _sleep(seconds * 1000);

#else

  sleep(seconds);

#endif
  ;
}
void time__usleep(int n) {

#ifdef _WIN32

#else

  usleep(n);

#endif
  ;
}
void time__sleep_ms(int n) {

#ifdef _WIN32

  Sleep(n);

#else

  usleep(n * 1000);

#endif
  ;
}
bool time__is_leap_year(int year) {

  return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}
Option_int time__days_in_month(int month, int year) {

  if (month > 12 || month < 1) {

    return v_error(_STR("Invalid month: %d", month));
  };

  int extra = (month == 2 && time__is_leap_year(year)) ? (1) : (0);

  int res = (*(int *)array__get(time__MonthDays, month - 1)) + extra;

  int tmp60 = OPTION_CAST(int)(res);
  return opt_ok(&tmp60, sizeof(int));
}
string vweb_dot_tmpl__compile_template(string path) {

  Option_string tmp1 = os__read_file(path);
  if (!tmp1.ok) {
    string err = tmp1.error;

    v_panic(tos2((byte *)"html failed"));
  }
  string html = *(string *)tmp1.data;
  ;

  string header = tos2((byte *)"");

  if (os__file_exists(tos2((byte *)"header.html"))) {

    Option_string tmp3 = os__read_file(tos2((byte *)"header.html"));
    if (!tmp3.ok) {
      string err = tmp3.error;

      v_panic(tos2((byte *)"html failed"));
    }
    string h = *(string *)tmp3.data;
    ;

    header = string_replace(h, tos2((byte *)"\'"), tos2((byte *)"\""));
  };

  array_string lines = string_split_into_lines(html);

  strings__Builder s = strings__new_builder(1000);

  string base = string_replace(string_all_after(path, tos2((byte *)"/")),
                               tos2((byte *)".html"), tos2((byte *)""));

  strings__Builder_writeln(
      &/* ? */ s,
      _STR("module main import strings fn %.*s_view() string {   // this line "
           "will get removed becase only function body is embedded \nmut sb := "
           "strings.new_builder(%d)\nheader := \'%.*s\' \n_ := header "
           "\n//footer := \'footer\' \n",
           base.len, base.str, lines.len * 30, header.len, header.str));

  strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

  bool in_css = 1;

  array_string tmp8 = lines;
  ;
  for (int tmp9 = 0; tmp9 < tmp8.len; tmp9++) {
    string _line = ((string *)tmp8.data)[tmp9];

    string line = string_trim_space(_line);

    if (string_eq(line, tos2((byte *)"<style>"))) {

      in_css = 1;

    } else if (string_eq(line, tos2((byte *)"</style>"))) {
    };

    if (string_contains(line, tos2((byte *)"@if "))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      int pos = string_index(line, tos2((byte *)"@if"));

      strings__Builder_writeln(
          &/* ? */ s, string_add(string_add(tos2((byte *)"if "),
                                            string_right(line, pos + 4)),
                                 tos2((byte *)"{")));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (string_contains(line, tos2((byte *)"@end"))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      strings__Builder_writeln(&/* ? */ s, tos2((byte *)"}"));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (string_contains(line, tos2((byte *)"@else"))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      strings__Builder_writeln(&/* ? */ s, tos2((byte *)" } else { "));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (string_contains(line, tos2((byte *)"@for"))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      int pos = string_index(line, tos2((byte *)"@for"));

      strings__Builder_writeln(
          &/* ? */ s, string_add(string_add(tos2((byte *)"for "),
                                            string_right(line, pos + 4)),
                                 tos2((byte *)"{")));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (!in_css && string_contains(line, tos2((byte *)".")) &&
               string_ends_with(line, tos2((byte *)"{"))) {

      string class =
          string_find_between(line, tos2((byte *)"."), tos2((byte *)"{"));

      strings__Builder_writeln(
          &/* ? */ s, _STR("<div class=\"%.*s\">", class.len, class.str));

    } else if (!in_css && string_eq(line, tos2((byte *)"}"))) {

      strings__Builder_writeln(&/* ? */ s, tos2((byte *)"</div>"));

    } else {

      strings__Builder_writeln(
          &/* ? */ s, string_replace(string_replace(line, tos2((byte *)"@"),
                                                    tos2((byte *)"\x24")),
                                     tos2((byte *)"\'"), tos2((byte *)"\"")));
    };
  };

  strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

  strings__Builder_writeln(&/* ? */ s, tos2((byte *)"tmpl_res := sb.str() "));

  strings__Builder_writeln(&/* ? */ s, tos2((byte *)"return tmpl_res }"));

  return strings__Builder_str(s);
}
void V_cc(V *v) {

  V_build_thirdparty_obj_files(*v);

  if (string_ends_with(v->out_name, tos2((byte *)".c"))) {

    os__mv(v->out_name_c, v->out_name);

    v_exit(0);
  };

  if (v->os == main__OS_windows) {

#ifndef _WIN32

    V_cc_windows_cross(v);

    return;

#endif
    ;
  };

#ifdef _WIN32

  if (v->os == main__OS_msvc) {

    V_cc_msvc(v);

    return;
  };

#endif
  ;

  V_log(&/* ? */ *v, _STR("cc() isprod=%d outname=%.*s", v->pref->is_prod,
                          v->out_name.len, v->out_name.str));

  array_string a = new_array_from_c_array(3, 3, sizeof(string),
                                          (string[]){v->pref->cflags,
                                                     tos2((byte *)"-std=gnu11"),
                                                     tos2((byte *)"-w")});

  if (v->pref->is_so) {

    _PUSH(&a, (tos2((byte *)"-shared -fPIC ")), tmp2, string);

    v->out_name = string_add(v->out_name, tos2((byte *)".so"));
  };

  if (v->pref->build_mode == main__BuildMode_build) {

    v->out_name =
        string_add(string_add(main__ModPath, v->dir), tos2((byte *)".o"));

    printf("Building %.*s...\n", v->out_name.len, v->out_name.str);
  };

  if (v->pref->is_prod) {

    _PUSH(&a, (tos2((byte *)"-O2")), tmp3, string);

  } else {

    _PUSH(&a, (tos2((byte *)"-g")), tmp4, string);
  };

  if (v->pref->is_debug && string_ne(os__user_os(), tos2((byte *)"windows"))) {

    _PUSH(&a, (tos2((byte *)" -rdynamic ")), tmp5, string);
  };

  if (v->os != main__OS_msvc && v->os != main__OS_freebsd) {

    _PUSH(&a, (tos2((byte *)"-Werror=implicit-function-declaration")), tmp6,
          string);
  };

  array_string tmp7 = V_generate_hotcode_reloading_compiler_flags(v);
  ;
  for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
    string f = ((string *)tmp7.data)[tmp8];

    _PUSH(&a, (f), tmp9, string);
  };

  string libs = tos2((byte *)"");

  if (v->pref->build_mode == main__BuildMode_build) {

    _PUSH(&a, (tos2((byte *)"-c")), tmp11, string);

  } else if (v->pref->build_mode == main__BuildMode_embed_vlib) {

  } else if (v->pref->build_mode == main__BuildMode_default_mode) {

    libs = _STR("%.*s/vlib/builtin.o", main__ModPath.len, main__ModPath.str);

    if (!os__file_exists(libs)) {

      printf("object file `%.*s` not found\n", libs.len, libs.str);

      v_exit(1);
    };

    array_string tmp12 = v->table->imports;
    ;
    for (int tmp13 = 0; tmp13 < tmp12.len; tmp13++) {
      string imp = ((string *)tmp12.data)[tmp13];

      if (string_eq(imp, tos2((byte *)"webview"))) {

        continue;
      };

      libs = string_add(libs, _STR(" \"%.*s/vlib/%.*s.o\"", main__ModPath.len,
                                   main__ModPath.str, imp.len, imp.str));
    };
  };

  if (v->pref->sanitize) {

    _PUSH(&a, (tos2((byte *)"-fsanitize=leak")), tmp14, string);
  };

  _PUSH(&a, (_STR("-o \"%.*s\"", v->out_name.len, v->out_name.str)), tmp15,
        string);

  if (os__dir_exists(v->out_name)) {

    cerror(_STR("\'%.*s\' is a directory", v->out_name.len, v->out_name.str));
  };

  if (v->os == main__OS_mac) {

    _PUSH(&a, (tos2((byte *)"-x objective-c")), tmp16, string);
  };

  _PUSH(&a, (_STR("\"%.*s\"", v->out_name_c.len, v->out_name_c.str)), tmp17,
        string);

  if (v->os == main__OS_mac) {

    _PUSH(&a, (tos2((byte *)"-x none")), tmp18, string);
  };

  if (v->os == main__OS_mac) {

    _PUSH(&a, (tos2((byte *)"-mmacosx-version-min=10.7")), tmp19, string);
  };

  array_CFlag cflags = V_get_os_cflags(*v);

  array_CFlag tmp21 = cflags;
  ;
  for (int tmp22 = 0; tmp22 < tmp21.len; tmp22++) {
    CFlag flag = ((CFlag *)tmp21.data)[tmp22];

    if (string_ends_with(flag.value, tos2((byte *)".o"))) {

      continue;
    };

    _PUSH(&a, (CFlag_format(&/* ? */ flag)), tmp23, string);
  };

  array_CFlag tmp24 = cflags;
  ;
  for (int tmp25 = 0; tmp25 < tmp24.len; tmp25++) {
    CFlag flag = ((CFlag *)tmp24.data)[tmp25];

    if (!string_ends_with(flag.value, tos2((byte *)".o"))) {

      continue;
    };

    _PUSH(&a, (CFlag_format(&/* ? */ flag)), tmp26, string);
  };

  _PUSH(&a, (libs), tmp27, string);

  if (v->pref->build_mode != main__BuildMode_build &&
      (v->os == main__OS_linux || v->os == main__OS_freebsd ||
       v->os == main__OS_openbsd || v->os == main__OS_netbsd ||
       v->os == main__OS_dragonfly)) {

    _PUSH(&a, (tos2((byte *)"-lm -lpthread ")), tmp28, string);

    if (v->os == main__OS_linux) {

      _PUSH(&a, (tos2((byte *)" -ldl ")), tmp29, string);
    };
  };

  if (v->os == main__OS_windows) {

    _PUSH(&a, (tos2((byte *)"-DUNICODE -D_UNICODE")), tmp30, string);
  };

  string args = array_string_join(a, tos2((byte *)" "));

  string cmd = _STR("%.*s %.*s", v->pref->ccompiler.len, v->pref->ccompiler.str,
                    args.len, args.str);

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    println(tos2((byte *)"\n=========="));

    println(cmd);
  };

  i64 ticks = time__ticks();

  Option_os__Result tmp34 = os__exec(cmd);
  if (!tmp34.ok) {
    string err = tmp34.error;

    cerror(err);

    return;
  }
  os__Result res = *(os__Result *)tmp34.data;
  ;

  if (res.exit_code != 0) {

    if (res.exit_code == 127) {

      cerror(string_add(
          string_add(
              string_add(
                  string_add(
                      string_add(tos2((byte *)"C compiler error, while "
                                              "attempting to run: \n"),
                                 tos2((byte *)"--------------------------------"
                                              "---------------------------\n")),
                      _STR("%.*s\n", cmd.len, cmd.str)),
                  tos2((byte *)"-----------------------------------------------"
                               "------------\n")),
              tos2((byte *)"Probably your C compiler is missing. \n")),
          tos2((byte *)"Please reinstall it, or make it available in your "
                       "PATH.")));
    };

    if (v->pref->is_debug) {

      println(res.output);

    } else {

      string partial_output = string_trim_right(string_limit(res.output, 200),
                                                tos2((byte *)"\r\n"));

      print(partial_output);

      if (res.output.len > partial_output.len) {

        println(tos2((
            byte
                *)"...\n(Use `v -debug` to print the entire error message)\n"));

      } else {

        println(tos2((byte *)""));
      };
    };

    cerror(string_add(
        tos2((byte *)"C error. This should never happen. "),
        tos2((byte *)"Please create a GitHub issue: "
                     "https://github.com/vlang/v/issues/new/choose")));
  };

  i64 diff = time__ticks() - ticks;

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    printf("%.*s took %lld ms\n", v->pref->ccompiler.len,
           v->pref->ccompiler.str, diff);

    println(tos2((byte *)"=========\n"));
  };

  if (!v->pref->is_debug && string_ne(v->out_name_c, tos2((byte *)"v.c")) &&
      string_ne(v->out_name_c, tos2((byte *)"v_macos.c"))) {

    os__rm(v->out_name_c);
  };

  v_array_free(a); // close_scope free
}
void V_cc_windows_cross(V *c) {

  if (!string_ends_with(c->out_name, tos2((byte *)".exe"))) {

    c->out_name = string_add(c->out_name, tos2((byte *)".exe"));
  };

  string args = _STR("-o %.*s -w -L. ", c->out_name.len, c->out_name.str);

  array_CFlag cflags = V_get_os_cflags(*c);

  array_CFlag tmp39 = cflags;
  ;
  for (int tmp40 = 0; tmp40 < tmp39.len; tmp40++) {
    CFlag flag = ((CFlag *)tmp39.data)[tmp40];

    if (string_ne(flag.name, tos2((byte *)"-l"))) {

      args = string_add(args, CFlag_format(&/* ? */ flag));

      args = string_add(args, tos2((byte *)" "));
    };
  };

  string libs = tos2((byte *)"");

  if (c->pref->build_mode == main__BuildMode_default_mode) {

    libs =
        _STR("\"%.*s/vlib/builtin.o\"", main__ModPath.len, main__ModPath.str);

    if (!os__file_exists(libs)) {

      printf("`%.*s` not found\n", libs.len, libs.str);

      v_exit(1);
    };

    array_string tmp42 = c->table->imports;
    ;
    for (int tmp43 = 0; tmp43 < tmp42.len; tmp43++) {
      string imp = ((string *)tmp42.data)[tmp43];

      libs = string_add(libs, _STR(" \"%.*s/vlib/%.*s.o\"", main__ModPath.len,
                                   main__ModPath.str, imp.len, imp.str));
    };
  };

  args = string_add(args, _STR(" %.*s ", c->out_name_c.len, c->out_name_c.str));

  array_CFlag tmp44 = cflags;
  ;
  for (int tmp45 = 0; tmp45 < tmp44.len; tmp45++) {
    CFlag flag = ((CFlag *)tmp44.data)[tmp45];

    if (string_eq(flag.name, tos2((byte *)"-l"))) {

      args = string_add(args, CFlag_format(&/* ? */ flag));

      args = string_add(args, tos2((byte *)" "));
    };
  };

  println(tos2((byte *)"Cross compiling for Windows..."));

  string winroot = _STR("%.*s/winroot", main__ModPath.len, main__ModPath.str);

  if (!os__dir_exists(winroot)) {

    string winroot_url = tos2((byte *)"https://github.com/vlang/v/releases/"
                                      "download/v0.1.10/winroot.zip");

    printf("\"%.*s\" not found.\n", winroot.len, winroot.str);

    printf("Download it from %.*s and save it in %.*s\n", winroot_url.len,
           winroot_url.str, main__ModPath.len, main__ModPath.str);

    println(tos2((byte *)"Unzip it afterwards.\n"));

    println(string_add(
        tos2((
            byte *)"winroot.zip contains all library and header files needed "),
        tos2((byte *)"to cross-compile for Windows.")));

    v_exit(1);
  };

  string obj_name = c->out_name;

  obj_name = string_replace(obj_name, tos2((byte *)".exe"), tos2((byte *)""));

  obj_name = string_replace(obj_name, tos2((byte *)".o.o"), tos2((byte *)".o"));

  string include = _STR("-I %.*s/include ", winroot.len, winroot.str);

  string cmd = _STR("clang -o %.*s -w %.*s -DUNICODE -D_UNICODE -m32 -c "
                    "-target x86_64-win32 %.*s/%.*s",
                    obj_name.len, obj_name.str, include.len, include.str,
                    main__ModPath.len, main__ModPath.str, c->out_name_c.len,
                    c->out_name_c.str);

  if (c->pref->show_c_cmd) {

    println(cmd);
  };

  if (os__system(cmd) != 0) {

    println(tos2((byte *)"Cross compilation for Windows failed. Make sure you "
                         "have clang installed."));

    v_exit(1);
  };

  if (c->pref->build_mode != main__BuildMode_build) {

    string link_cmd = string_add(
        string_add(_STR("lld-link %.*s %.*s/lib/libcmt.lib ", obj_name.len,
                        obj_name.str, winroot.len, winroot.str),
                   _STR("%.*s/lib/libucrt.lib %.*s/lib/kernel32.lib "
                        "%.*s/lib/libvcruntime.lib ",
                        winroot.len, winroot.str, winroot.len, winroot.str,
                        winroot.len, winroot.str)),
        _STR("%.*s/lib/uuid.lib", winroot.len, winroot.str));

    if (c->pref->show_c_cmd) {

      println(link_cmd);
    };

    if (os__system(link_cmd) != 0) {

      println(tos2((byte *)"Cross compilation for Windows failed. Make sure "
                           "you have lld linker installed."));

      v_exit(1);
    };
  };

  println(tos2((byte *)"Done!"));
}
void V_build_thirdparty_obj_files(V c) {

  array_CFlag tmp52 = V_get_os_cflags(c);
  ;
  for (int tmp53 = 0; tmp53 < tmp52.len; tmp53++) {
    CFlag flag = ((CFlag *)tmp52.data)[tmp53];

    if (string_ends_with(flag.value, tos2((byte *)".o"))) {

      if (c.os == main__OS_msvc) {

        build_thirdparty_obj_file_with_msvc(flag.value);

      } else {

        build_thirdparty_obj_file(flag.value);
      };
    };
  };
}
string find_c_compiler() {

  string args = array_string_join(env_vflags_and_os_args(), tos2((byte *)" "));

  string defaultcc = find_c_compiler_default();

  return get_arg(args, tos2((byte *)"cc"), defaultcc);
}
string find_c_compiler_default() {

#ifdef _WIN32

  return tos2((byte *)"gcc");

#endif
  ;

  return tos2((byte *)"cc");
}
string find_c_compiler_thirdparty_options() {

#ifdef _WIN32

  return tos2((byte *)"");

#endif
  ;

  return tos2((byte *)"-fPIC");
}
array_CFlag V_get_os_cflags(V v) {

  array_CFlag flags = new_array_from_c_array(0, 0, sizeof(CFlag), (CFlag[]){0});

  array_CFlag tmp2 = v.table->cflags;
  ;
  for (int tmp3 = 0; tmp3 < tmp2.len; tmp3++) {
    CFlag flag = ((CFlag *)tmp2.data)[tmp3];

    if (string_eq(flag.os, tos2((byte *)"")) ||
        (string_eq(flag.os, tos2((byte *)"linux")) && v.os == main__OS_linux) ||
        (string_eq(flag.os, tos2((byte *)"darwin")) && v.os == main__OS_mac) ||
        (string_eq(flag.os, tos2((byte *)"windows")) &&
         (v.os == main__OS_windows || v.os == main__OS_msvc))) {

      _PUSH(&flags, (flag), tmp4, CFlag);
    };
  };

  return flags;

  v_array_free(flags); // close_scope free
}
string CFlag_format(CFlag *cf) {

  string value = cf->value;

  if (string_eq(cf->name, tos2((byte *)"-I")) ||
      string_eq(cf->name, tos2((byte *)"-L")) ||
      string_ends_with(value, tos2((byte *)".o"))) {

    value = string_add(string_add(tos2((byte *)"\""), os__realpath(value)),
                       tos2((byte *)"\""));
  };

  return string_trim_space(
      _STR("%.*s %.*s", cf->name.len, cf->name.str, value.len, value.str));
}
bool Table_has_cflag(Table *table, CFlag cflag) {

  array_CFlag tmp6 = table->cflags;
  ;
  for (int tmp7 = 0; tmp7 < tmp6.len; tmp7++) {
    CFlag cf = ((CFlag *)tmp6.data)[tmp7];

    if (string_eq(cf.os, cflag.os) && string_eq(cf.name, cflag.name) &&
        string_eq(cf.value, cflag.value)) {

      return 1;
    };
  };

  return 0;
}
void Table_parse_cflag(Table *table, string cflag) {

  array_string allowed_flags =
      new_array_from_c_array(5, 5, sizeof(string),
                             (string[]){
                                 tos2((byte *)"framework"),
                                 tos2((byte *)"library"),
                                 tos2((byte *)"I"),
                                 tos2((byte *)"l"),
                                 tos2((byte *)"L"),
                             });

  string flag = string_trim_space(cflag);

  if (string_eq(flag, tos2((byte *)""))) {

    return;
  };

  string fos = tos2((byte *)"");

  string name = tos2((byte *)"");

  if (string_starts_with(flag, tos2((byte *)"linux")) ||
      string_starts_with(flag, tos2((byte *)"darwin")) ||
      string_starts_with(flag, tos2((byte *)"windows"))) {

    int pos = string_index(flag, tos2((byte *)" "));

    fos = string_trim_space(string_left(flag, pos));

    flag = string_trim_space(string_right(flag, pos));
  };

  while (1) {

    int index = -1;

    string value = tos2((byte *)"");

    if (string_at(flag, 0) == '-') {

      array_string tmp17 = allowed_flags;
      ;
      for (int tmp18 = 0; tmp18 < tmp17.len; tmp18++) {
        string f = ((string *)tmp17.data)[tmp18];

        int i = 1 + f.len;

        if (i < flag.len && string_eq(f, string_substr(flag, 1, i))) {

          name = string_trim_space(string_left(flag, i));

          flag = string_trim_space(string_right(flag, i));

          break;
        };
      };
    };

    array_int tmp20 =
        new_array_from_c_array(2, 2, sizeof(int),
                               (int[]){string_index(flag, tos2((byte *)" ")),
                                       string_index(flag, tos2((byte *)","))});
    ;
    for (int tmp21 = 0; tmp21 < tmp20.len; tmp21++) {
      int i = ((int *)tmp20.data)[tmp21];

      if (index == -1 || (i != -1 && i < index)) {

        index = i;
      };
    };

    if (index != -1 && string_at(flag, index) == ' ' &&
        string_at(flag, index + 1) == '-') {

      array_string tmp26 = allowed_flags;
      ;
      for (int tmp27 = 0; tmp27 < tmp26.len; tmp27++) {
        string f = ((string *)tmp26.data)[tmp27];

        int i = index + f.len;

        if (i < flag.len && string_eq(f, string_substr(flag, index, i))) {

          index = i;

          break;
        };
      };

      value = string_trim_space(string_left(flag, index));

      flag = string_trim_space(string_right(flag, index));

    } else if (index != -1 && index < flag.len - 2 &&
               string_at(flag, index) == ',') {

      value = string_trim_space(string_left(flag, index));

      flag = string_trim_space(string_right(flag, index + 1));

    } else {

      value = string_trim_space(flag);

      index = -1;
    };

    CFlag cf = (CFlag){.os = fos, .name = name, .value = value};

    if (!Table_has_cflag(&/* ? */ *table, cf)) {

      _PUSH(&table->cflags, (cf), tmp32, CFlag);
    };

    if (index == -1) {

      break;
    };
  };

  v_array_free(allowed_flags); // close_scope free
}
CGen *new_cgen(string out_name_c) {

  string path = out_name_c;

  Option_os__File tmp2 = os__create(path);
  if (!tmp2.ok) {
    string err = tmp2.error;

    printf("failed to create %.*s\n", path.len, path.str);

    return (CGen *)memdup(
        &(CGen){.out_path = tos((byte *)"", 0),
                .thread_fns = new_array(0, 1, sizeof(string)),
                .is_user = 0,
                .lines = new_array(0, 1, sizeof(string)),
                .typedefs = new_array(0, 1, sizeof(string)),
                .type_aliases = new_array(0, 1, sizeof(string)),
                .includes = new_array(0, 1, sizeof(string)),
                .thread_args = new_array(0, 1, sizeof(string)),
                .consts = new_array(0, 1, sizeof(string)),
                .fns = new_array(0, 1, sizeof(string)),
                .so_fns = new_array(0, 1, sizeof(string)),
                .consts_init = new_array(0, 1, sizeof(string)),
                .nogen = 0,
                .tmp_line = tos((byte *)"", 0),
                .cur_line = tos((byte *)"", 0),
                .prev_line = tos((byte *)"", 0),
                .is_tmp = 0,
                .fn_main = tos((byte *)"", 0),
                .stash = tos((byte *)"", 0),
                .file = tos((byte *)"", 0),
                .line = 0,
                .line_directives = 0,
                .cut_pos = 0},
        sizeof(CGen));
  }
  os__File out = *(os__File *)tmp2.data;
  ;

  CGen *gen =
      (CGen *)memdup(&(CGen){.out_path = path,
                             .out = out,
                             .lines = _make(0, 1000, sizeof(string)),
                             .thread_fns = new_array(0, 1, sizeof(string)),
                             .is_user = 0,
                             .typedefs = new_array(0, 1, sizeof(string)),
                             .type_aliases = new_array(0, 1, sizeof(string)),
                             .includes = new_array(0, 1, sizeof(string)),
                             .thread_args = new_array(0, 1, sizeof(string)),
                             .consts = new_array(0, 1, sizeof(string)),
                             .fns = new_array(0, 1, sizeof(string)),
                             .so_fns = new_array(0, 1, sizeof(string)),
                             .consts_init = new_array(0, 1, sizeof(string)),
                             .nogen = 0,
                             .tmp_line = tos((byte *)"", 0),
                             .cur_line = tos((byte *)"", 0),
                             .prev_line = tos((byte *)"", 0),
                             .is_tmp = 0,
                             .fn_main = tos((byte *)"", 0),
                             .stash = tos((byte *)"", 0),
                             .file = tos((byte *)"", 0),
                             .line = 0,
                             .line_directives = 0,
                             .cut_pos = 0},
                     sizeof(CGen));

  return gen;
}
void CGen_genln(CGen *g, string s) {

  if (g->nogen || g->pass != main__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    g->tmp_line =
        _STR("%.*s %.*s\n", g->tmp_line.len, g->tmp_line.str, s.len, s.str);

    return;
  };

  g->cur_line =
      _STR("%.*s %.*s", g->cur_line.len, g->cur_line.str, s.len, s.str);

  if (string_ne(g->cur_line, tos2((byte *)""))) {

    if (g->line_directives &&
        string_ne(string_trim_space(g->cur_line), tos2((byte *)""))) {

      _PUSH(&g->lines,
            (_STR("#line %d \"%.*s\"", g->line, g->file.len, g->file.str)),
            tmp4, string);
    };

    _PUSH(&g->lines, (g->cur_line), tmp5, string);

    g->prev_line = g->cur_line;

    g->cur_line = tos2((byte *)"");
  };
}
void CGen_gen(CGen *g, string s) {

  if (g->nogen || g->pass != main__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    g->tmp_line =
        _STR("%.*s %.*s", g->tmp_line.len, g->tmp_line.str, s.len, s.str);

  } else {

    g->cur_line =
        _STR("%.*s %.*s", g->cur_line.len, g->cur_line.str, s.len, s.str);
  };
}
void CGen_resetln(CGen *g, string s) {

  if (g->nogen || g->pass != main__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    g->tmp_line = s;

  } else {

    g->cur_line = s;
  };
}
void CGen_save(CGen *g) {

  string s = array_string_join(g->lines, tos2((byte *)"\n"));

  os__File_writeln(g->out, s);

  os__File_close(g->out);
}
void CGen_start_tmp(CGen *g) {

  if (g->is_tmp) {

    println(g->tmp_line);

    printf("start_tmp() already started. cur_line=\"%.*s\"\n", g->cur_line.len,
           g->cur_line.str);

    v_exit(1);
  };

  g->tmp_line = tos2((byte *)"");

  g->is_tmp = 1;
}
string CGen_end_tmp(CGen *g) {

  g->is_tmp = 0;

  string res = g->tmp_line;

  g->tmp_line = tos2((byte *)"");

  return res;
}
int CGen_add_placeholder(CGen *g) {

  if (g->is_tmp) {

    return g->tmp_line.len;
  };

  return g->cur_line.len;
}
void CGen_start_cut(CGen *g) { g->cut_pos = CGen_add_placeholder(g); }
string CGen_cut(CGen *g) {

  int pos = g->cut_pos;

  g->cut_pos = 0;

  if (g->is_tmp) {

    string res = string_right(g->tmp_line, pos);

    g->tmp_line = string_left(g->tmp_line, pos);

    return res;
  };

  string res = string_right(g->cur_line, pos);

  g->cur_line = string_left(g->cur_line, pos);

  return res;
}
void CGen_set_placeholder(CGen *g, int pos, string val) {

  if (g->nogen || g->pass != main__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    string left = string_left(g->tmp_line, pos);

    string right = string_right(g->tmp_line, pos);

    g->tmp_line = _STR("%.*s%.*s%.*s", left.len, left.str, val.len, val.str,
                       right.len, right.str);

    return;
  };

  string left = string_left(g->cur_line, pos);

  string right = string_right(g->cur_line, pos);

  g->cur_line = _STR("%.*s%.*s%.*s", left.len, left.str, val.len, val.str,
                     right.len, right.str);
}
void CGen_insert_before(CGen *g, string val) {

  string prev = (*(string *)array__get(g->lines, g->lines.len - 1));

  array_set(&/*q*/ g->lines, g->lines.len - 1,
            &(string[]){
                _STR("%.*s \n %.*s \n", prev.len, prev.str, val.len, val.str)});
}
void CGen_register_thread_fn(CGen *g, string wrapper_name, string wrapper_text,
                             string struct_text) {

  array_string tmp18 = g->thread_args;
  ;
  for (int tmp19 = 0; tmp19 < tmp18.len; tmp19++) {
    string arg = ((string *)tmp18.data)[tmp19];

    if (string_contains(arg, wrapper_name)) {

      return;
    };
  };

  _PUSH(&g->thread_args, (struct_text), tmp20, string);

  _PUSH(&g->thread_args, (wrapper_text), tmp21, string);
}
string V_prof_counters(V *c) {

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  return array_string_join(res, tos2((byte *)";\n"));

  v_array_free(res); // close_scope free
}
string Parser_print_prof_counters(Parser *p) {

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  return array_string_join(res, tos2((byte *)";\n"));

  v_array_free(res); // close_scope free
}
void Parser_gen_typedef(Parser *p, string s) {

  if (!Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->typedefs, (s), tmp24, string);
}
void Parser_gen_type_alias(Parser *p, string s) {

  if (!Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->type_aliases, (s), tmp25, string);
}
void CGen_add_to_main(CGen *g, string s) {

  g->fn_main = string_add(g->fn_main, s);
}
void build_thirdparty_obj_file(string path) {

  string obj_path = os__realpath(path);

  if (os__file_exists(obj_path)) {

    return;
  };

  printf("%.*s not found, building it...\n", obj_path.len, obj_path.str);

  string parent = os__dir(obj_path);

  array_string files = os__ls(parent);

  string cfiles = tos2((byte *)"");

  array_string tmp30 = files;
  ;
  for (int tmp31 = 0; tmp31 < tmp30.len; tmp31++) {
    string file = ((string *)tmp30.data)[tmp31];

    if (string_ends_with(file, tos2((byte *)".c"))) {

      cfiles = string_add(
          cfiles,
          string_add(
              string_add(tos2((byte *)"\""),
                         os__realpath(string_add(
                             string_add(parent, os__PathSeparator), file))),
              tos2((byte *)"\" ")));
    };
  };

  string cc = find_c_compiler();

  string cc_thirdparty_options = find_c_compiler_thirdparty_options();

  string cmd = _STR("%.*s %.*s -c -o \"%.*s\" %.*s", cc.len, cc.str,
                    cc_thirdparty_options.len, cc_thirdparty_options.str,
                    obj_path.len, obj_path.str, cfiles.len, cfiles.str);

  Option_os__Result tmp35 = os__exec(cmd);
  if (!tmp35.ok) {
    string err = tmp35.error;

    printf("failed thirdparty object build cmd: %.*s\n", cmd.len, cmd.str);

    cerror(err);

    return;
  }
  os__Result res = *(os__Result *)tmp35.data;
  ;

  println(res.output);
}
string os_name_to_ifdef(string name) {

  if (string_eq(name, tos2((byte *)"windows"))) { /* case */

    return tos2((byte *)"_WIN32");

  } else if (string_eq(name, tos2((byte *)"mac"))) { /* case */

    return tos2((byte *)"__APPLE__");

  } else if (string_eq(name, tos2((byte *)"linux"))) { /* case */

    return tos2((byte *)"__linux__");

  } else if (string_eq(name, tos2((byte *)"freebsd"))) { /* case */

    return tos2((byte *)"__FreeBSD__");

  } else if (string_eq(name, tos2((byte *)"openbsd"))) { /* case */

    return tos2((byte *)"__OpenBSD__");

  } else if (string_eq(name, tos2((byte *)"netbsd"))) { /* case */

    return tos2((byte *)"__NetBSD__");

  } else if (string_eq(name, tos2((byte *)"dragonfly"))) { /* case */

    return tos2((byte *)"__DragonFly__");

  } else if (string_eq(name, tos2((byte *)"msvc"))) { /* case */

    return tos2((byte *)"_MSC_VER");
  };

  cerror(_STR("bad os ifdef name \"%.*s\"", name.len, name.str));

  return tos2((byte *)"");
}
string platform_postfix_to_ifdefguard(string name) {

  if (string_eq(name, tos2((byte *)".v"))) { /* case */

    return tos2((byte *)"");

  } else if (string_eq(name, tos2((byte *)"_win.v"))) { /* case */

    return tos2((byte *)"#ifdef _WIN32");

  } else if (string_eq(name, tos2((byte *)"_nix.v"))) { /* case */

    return tos2((byte *)"#ifndef _WIN32");

  } else if (string_eq(name, tos2((byte *)"_lin.v"))) { /* case */

    return tos2((byte *)"#ifdef __linux__");

  } else if (string_eq(name, tos2((byte *)"_mac.v"))) { /* case */

    return tos2((byte *)"#ifdef __APPLE__");
  };

  cerror(_STR("bad platform_postfix \"%.*s\"", name.len, name.str));

  return tos2((byte *)"");
}
string V_c_type_definitions(V *v) {

  array_Type types = new_array_from_c_array(0, 0, sizeof(Type), (Type[]){0});

  array_Type builtin_types =
      new_array_from_c_array(0, 0, sizeof(Type), (Type[]){0});

  array_string builtins = new_array_from_c_array(
      4, 4, sizeof(string),
      (string[]){tos2((byte *)"string"), tos2((byte *)"array"),
                 tos2((byte *)"map"), tos2((byte *)"Option")});

  array_string tmp39 = builtins;
  ;
  for (int tmp40 = 0; tmp40 < tmp39.len; tmp40++) {
    string builtin = ((string *)tmp39.data)[tmp40];

    Type tmp41 = {0};
    bool tmp42 = map_get(v->table->typesmap, builtin, &tmp41);

    Type typ = tmp41;

    _PUSH(&builtin_types, (typ), tmp44, Type);
  };

  map_Type tmp45 = v->table->typesmap;
  array_string keys_tmp45 = map_keys(&tmp45);
  for (int l = 0; l < keys_tmp45.len; l++) {
    string t_name = ((string *)keys_tmp45.data)[l];
    Type t = {0};
    map_get(tmp45, t_name, &t);

    if (_IN(string, t_name, builtins)) {

      continue;
    };

    _PUSH(&types, (t), tmp46, Type);
  };

  array_Type types_sorted = sort_structs(types);

  return string_add(string_add(types_to_c(builtin_types, v->table),
                               tos2((byte *)"\n//----\n")),
                    types_to_c(types_sorted, v->table));

  v_array_free(builtins);      // close_scope free
  v_array_free(builtin_types); // close_scope free
  v_array_free(types);         // close_scope free
}
string types_to_c(array_Type types, Table *table) {

  strings__Builder sb = strings__new_builder(10);

  array_Type tmp49 = types;
  ;
  for (int tmp50 = 0; tmp50 < tmp49.len; tmp50++) {
    Type t = ((Type *)tmp49.data)[tmp50];

    if (t.cat != main__TypeCategory_union_ &&
        t.cat != main__TypeCategory_struct_) {

      continue;
    };

    string kind = (t.cat == main__TypeCategory_union_)
                      ? (tos2((byte *)"union"))
                      : (tos2((byte *)"struct"));

    strings__Builder_writeln(
        &/* ? */ sb,
        _STR("%.*s %.*s {", kind.len, kind.str, t.name.len, t.name.str));

    array_Var tmp52 = t.fields;
    ;
    for (int tmp53 = 0; tmp53 < tmp52.len; tmp53++) {
      Var field = ((Var *)tmp52.data)[tmp53];

      strings__Builder_writeln(
          &/* ? */ sb, string_add(Table_cgen_name_type_pair(
                                      &/* ? */ *table, field.name, field.typ),
                                  tos2((byte *)";")));
    };

    strings__Builder_writeln(&/* ? */ sb, tos2((byte *)"};\n"));
  };

  return strings__Builder_str(sb);
}
array_Type sort_structs(array_Type types) {

  DepGraph *dep_graph = new_dep_graph();

  array_string type_names =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  array_Type tmp56 = types;
  ;
  for (int tmp57 = 0; tmp57 < tmp56.len; tmp57++) {
    Type t = ((Type *)tmp56.data)[tmp57];

    _PUSH(&type_names, (t.name), tmp58, string);
  };

  array_Type tmp59 = types;
  ;
  for (int tmp60 = 0; tmp60 < tmp59.len; tmp60++) {
    Type t = ((Type *)tmp59.data)[tmp60];

    array_string field_deps =
        new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

    array_Var tmp62 = t.fields;
    ;
    for (int tmp63 = 0; tmp63 < tmp62.len; tmp63++) {
      Var field = ((Var *)tmp62.data)[tmp63];

      if (!(_IN(string, field.typ, type_names)) ||
          _IN(string, field.typ, field_deps)) {

        continue;
      };

      _PUSH(&field_deps, (field.typ), tmp64, string);
    };

    DepGraph_add(dep_graph, t.name, field_deps);

    v_array_free(field_deps); // close_scope free
  };

  DepGraph *dep_graph_sorted = DepGraph_resolve(&/* ? */ *dep_graph);

  if (!dep_graph_sorted->acyclic) {

    cerror(tos2((byte *)"error: cgen.sort_structs() DGNAC.\nplease create a "
                        "new issue here: https://github.com/vlang/v/issues and "
                        "tag @joe-conigliaro"));
  };

  array_Type types_sorted =
      new_array_from_c_array(0, 0, sizeof(Type), (Type[]){0});

  array_DepGraphNode tmp67 = dep_graph_sorted->nodes;
  ;
  for (int tmp68 = 0; tmp68 < tmp67.len; tmp68++) {
    DepGraphNode node = ((DepGraphNode *)tmp67.data)[tmp68];

    array_Type tmp69 = types;
    ;
    for (int tmp70 = 0; tmp70 < tmp69.len; tmp70++) {
      Type t = ((Type *)tmp69.data)[tmp70];

      if (string_eq(t.name, node.name)) {

        _PUSH(&types_sorted, (t), tmp71, Type);

        continue;
      };
    };
  };

  return types_sorted;

  v_array_free(types_sorted); // close_scope free
  v_array_free(type_names);   // close_scope free
}
void Parser_comp_time(Parser *p) {

  Parser_check(p, main__Token_dollar);

  if (p->tok == main__Token_key_if) {

    Parser_check(p, main__Token_key_if);

    Parser_fspace(p);

    bool not = p->tok == main__Token_not;

    if (not) {

      Parser_check(p, main__Token_not);
    };

    string name = Parser_check_name(p);

    Parser_fspace(p);

    if (_IN(string, name, main__SupportedPlatforms)) {

      string ifdef_name = os_name_to_ifdef(name);

      if (not) {

        Parser_genln(p, _STR("#ifndef %.*s", ifdef_name.len, ifdef_name.str));

      } else {

        Parser_genln(p, _STR("#ifdef %.*s", ifdef_name.len, ifdef_name.str));
      };

      Parser_check(p, main__Token_lcbr);

      Parser_statements_no_rcbr(p);

      if (!(p->tok == main__Token_dollar &&
            Parser_peek(p) == main__Token_key_else)) {

        Parser_genln(p, tos2((byte *)"#endif"));
      };

    } else if (string_eq(name, tos2((byte *)"debug"))) {

      Parser_genln(p, tos2((byte *)"#ifdef VDEBUG"));

      Parser_check(p, main__Token_lcbr);

      Parser_statements_no_rcbr(p);

      Parser_genln(p, tos2((byte *)"#endif"));

    } else {

      println(tos2((byte *)"Supported platforms:"));

      println(array_string_str(main__SupportedPlatforms));

      Parser_error(p, _STR("unknown platform `%.*s`", name.len, name.str));
    };

    bool if_returns = p->returns;

    p->returns = 0;

    if (p->tok == main__Token_dollar &&
        Parser_peek(p) == main__Token_key_else) {

      Parser_next(p);

      Parser_next(p);

      Parser_check(p, main__Token_lcbr);

      Parser_genln(p, tos2((byte *)"#else"));

      Parser_statements_no_rcbr(p);

      Parser_genln(p, tos2((byte *)"#endif"));

      bool else_returns = p->returns;

      p->returns = if_returns && else_returns;
    };

  } else if (p->tok == main__Token_key_for) {

    Parser_next(p);

    string name = Parser_check_name(p);

    if (string_ne(name, tos2((byte *)"field"))) {

      Parser_error(p, tos2((byte *)"for field only"));
    };

    Parser_check(p, main__Token_key_in);

    Parser_check_name(p);

    Parser_check(p, main__Token_dot);

    Parser_check_name(p);

    Parser_check(p, main__Token_lcbr);

    string res_name = Parser_check_name(p);

    println(res_name);

    Parser_check(p, main__Token_dot);

    Parser_check(p, main__Token_dollar);

    Parser_check(p, main__Token_name);

    Parser_check(p, main__Token_assign);

    CGen_start_tmp(p->cgen);

    Parser_bool_expression(p);

    string val = CGen_end_tmp(p->cgen);

    println(val);

    Parser_check(p, main__Token_rcbr);

  } else if (p->tok == main__Token_name &&
             string_eq(p->lit, tos2((byte *)"vweb"))) {

    string path = string_add(p->cur_fn->name, tos2((byte *)".html"));

    if (p->pref->is_debug) {

      printf("compiling tmpl %.*s\n", path.len, path.str);
    };

    if (!os__file_exists(path)) {

      Parser_error(
          p, _STR("vweb HTML template \"%.*s\" not found", path.len, path.str));
    };

    Parser_check(p, main__Token_name);

    Parser_check(p, main__Token_dot);

    Parser_check(p, main__Token_name);

    Parser_check(p, main__Token_lpar);

    Parser_check(p, main__Token_rpar);

    string v_code = vweb_dot_tmpl__compile_template(path);

    if (os__file_exists(tos2((byte *)".vwebtmpl.v"))) {

      os__rm(tos2((byte *)".vwebtmpl.v"));
    };

    os__write_file(tos2((byte *)".vwebtmpl.v"), string_clone(v_code));

    Parser_genln(p, tos2((byte *)""));

    int pos = p->cgen->lines.len - 1;

    Parser pp = V_new_parser(p->v, tos2((byte *)".vwebtmpl.v"));

    if (!p->pref->is_debug) {

      os__rm(tos2((byte *)".vwebtmpl.v"));
    };

    pp.is_vweb = 1;

    Parser_set_current_fn(&/* ? */ pp, p->cur_fn);

    Parser_parse(&/* ? */ pp, main__Pass_main);

    string tmpl_fn_body = string_clone(array_string_join(
        array_slice(p->cgen->lines, pos + 2, p->cgen->lines.len),
        tos2((byte *)"\n")));

    int end_pos =
        string_last_index(tmpl_fn_body, tos2((byte *)"Builder_str( sb )")) + 19;

    p->cgen->lines = array_left(p->cgen->lines, pos);

    Parser_genln(p, tos2((byte *)"/////////////////// tmpl start"));

    Parser_genln(p, string_left(tmpl_fn_body, end_pos));

    Parser_genln(p, tos2((byte *)"/////////////////// tmpl end"));

    Var receiver = (*(Var *)array__get(p->cur_fn->args, 0));

    string dot = (receiver.is_mut) ? (tos2((byte *)"->")) : (tos2((byte *)"."));

    Parser_genln(p,
                 _STR("vweb__Context_html(%.*s %.*s vweb, tmpl_res)",
                      receiver.name.len, receiver.name.str, dot.len, dot.str));

  } else {

    Parser_error(p, tos2((byte *)"bad comptime expr"));
  };
}
void Parser_chash(Parser *p) {

  string hash = string_trim_space(p->lit);

  Parser_next(p);

  bool is_sig = Parser_is_sig(p);

  if (string_starts_with(hash, tos2((byte *)"flag "))) {

    string flag = string_right(hash, 5);

    flag = string_replace(flag, tos2((byte *)"@VROOT"), p->vroot);

    flag = string_replace(flag, tos2((byte *)"@VMOD"), main__ModPath);

    Parser_log(&/* ? */ *p, _STR("adding flag \"%.*s\"", flag.len, flag.str));

    Table_parse_cflag(p->table, flag);

    return;
  };

  if (string_starts_with(hash, tos2((byte *)"include"))) {

    if (Parser_first_pass(&/* ? */ *p) && !is_sig) {

      if (p->file_pcguard.len != 0) {

        _PUSH(&p->cgen->includes,
              (_STR("%.*s\n#%.*s\n#endif", p->file_pcguard.len,
                    p->file_pcguard.str, hash.len, hash.str)),
              tmp22, string);

        return;
      };

      _PUSH(&p->cgen->includes, (_STR("#%.*s", hash.len, hash.str)), tmp23,
            string);

      return;
    };

  } else if (string_contains(hash, tos2((byte *)"embed"))) {

    int pos = string_index(hash, tos2((byte *)"embed")) + 5;

    string file = string_right(hash, pos);

    if (p->pref->build_mode != main__BuildMode_default_mode) {

      Parser_genln(p, _STR("#include %.*s", file.len, file.str));
    };

  } else if (string_contains(hash, tos2((byte *)"define"))) {

    _PUSH(&p->cgen->includes, (_STR("#%.*s", hash.len, hash.str)), tmp26,
          string);

  } else if (string_eq(hash, tos2((byte *)"v"))) {

    println(tos2((byte *)"v script"));

  } else {

    if (!p->can_chash) {

      Parser_error(
          p,
          tos2((
              byte
                  *)"bad token `#` (embedding C code is no longer supported)"));
    };

    Parser_genln(p, hash);
  };
}
void Parser_comptime_method_call(Parser *p, Type typ) {

  p->cgen->cur_line = tos2((byte *)"");

  Parser_check(p, main__Token_dollar);

  string var = Parser_check_name(p);

  array_Fn tmp28 = typ.methods;
  ;
  for (int i = 0; i < tmp28.len; i++) {
    Fn method = ((Fn *)tmp28.data)[i];

    if (string_ne(method.typ, tos2((byte *)"void"))) {

      continue;
    };

    Var receiver = (*(Var *)array__get(method.args, 0));

    string amp = (receiver.is_mut) ? (tos2((byte *)"&")) : (tos2((byte *)""));

    if (i > 0) {

      Parser_gen(p, tos2((byte *)" else "));
    };

    Parser_gen(
        p, _STR("if ( string_eq(%.*s, _STR(\"%.*s\")) ) %.*s_%.*s(%.*s %.*s);",
                var.len, var.str, method.name.len, method.name.str,
                typ.name.len, typ.name.str, method.name.len, method.name.str,
                amp.len, amp.str, p->expr_var.name.len, p->expr_var.name.str));
  };

  Parser_check(p, main__Token_lpar);

  Parser_check(p, main__Token_rpar);

  if (p->tok == main__Token_key_orelse) {

    Parser_check(p, main__Token_key_orelse);

    Parser_genln(p, tos2((byte *)"else {"));

    Parser_check(p, main__Token_lcbr);

    Parser_statements(p);
  };
}
void Parser_gen_array_str(Parser *p, Type typ) {

  Table_add_method(p->table, typ.name,
                   (Fn){.name = tos2((byte *)"str"),
                        .typ = tos2((byte *)"string"),
                        .args = new_array_from_c_array(
                            1, 1, sizeof(Var),
                            (Var[]){(Var){.typ = typ.name,
                                          .is_arg = 1,
                                          .name = tos((byte *)"", 0),
                                          .is_const = 0,
                                          .args = new_array(0, 1, sizeof(Var)),
                                          .attr = tos((byte *)"", 0),
                                          .is_mut = 0,
                                          .is_alloc = 0,
                                          .ptr = 0,
                                          .ref = 0,
                                          .parent_fn = tos((byte *)"", 0),
                                          .mod = tos((byte *)"", 0),
                                          .line_nr = 0,
                                          .is_global = 0,
                                          .is_used = 0,
                                          .is_changed = 0,
                                          .scope_level = 0}}),
                        .is_method = 1,
                        .is_public = 1,
                        .receiver_typ = typ.name,
                        .mod = tos((byte *)"", 0),
                        .local_vars = new_array(0, 1, sizeof(Var)),
                        .var_idx = 0,
                        .is_interface = 0,
                        .scope_level = 0,
                        .is_c = 0,
                        .returns_error = 0,
                        .is_decl = 0,
                        .defer_text = new_array(0, 1, sizeof(string))});

  string t = typ.name;

  string elm_type = string_right(t, 6);

  Type elm_type2 = Table_find_type(&/* ? */ *p->table, elm_type);

  if (string_eq(Parser_typ_to_fmt(p, elm_type, 0), tos2((byte *)"")) &&
      !Table_type_has_method(&/* ? */ *p->table,
                             &/*112 EXP:"Type*" GOT:"Type" */ elm_type2,
                             tos2((byte *)"str"))) {

    Parser_error(p,
                 _STR("cant print %.*s[], unhandled print of %.*s",
                      elm_type.len, elm_type.str, elm_type.len, elm_type.str));
  };

  _PUSH(&p->cgen->fns,
        (_STR("\nstring %.*s_str(%.*s a) {\n	strings__Builder sb = "
              "strings__new_builder(a.len * 3);\n	"
              "strings__Builder_write(&sb, tos2(\"[\")) ;\n	for (int i = "
              "0; i < a.len; i++) {\n		strings__Builder_write(&sb, "
              "%.*s_str( ((%.*s *) a.data)[i]));\n\n	if (i < a.len - 1) "
              "{\n		strings__Builder_write(&sb, tos2(\", \")) "
              ";\n		\n	}\n}\nstrings__Builder_write(&sb, "
              "tos2(\"]\")) ;\nreturn strings__Builder_str(sb);\n} ",
              t.len, t.str, t.len, t.str, elm_type.len, elm_type.str,
              elm_type.len, elm_type.str)),
        tmp36, string);
}
void Parser_parse_t(Parser *p) {}
void DepSet_add(DepSet *dset, string item) {

  _PUSH(&dset->items, (item), tmp1, string);
}
DepSet DepSet_diff(DepSet *dset, DepSet otherset) {

  DepSet diff = (DepSet){.items = new_array(0, 1, sizeof(string))};

  array_string tmp3 = dset->items;
  ;
  for (int tmp4 = 0; tmp4 < tmp3.len; tmp4++) {
    string item = ((string *)tmp3.data)[tmp4];

    if (!_IN(string, item, otherset.items)) {

      _PUSH(&diff.items, (item), tmp5, string);
    };
  };

  return diff;
}
int DepSet_size(DepSet *dset) { return dset->items.len; }
DepGraph *new_dep_graph() {

  return (DepGraph *)memdup(
      &(DepGraph){.acyclic = 1, .nodes = new_array(0, 1, sizeof(DepGraphNode))},
      sizeof(DepGraph));
}
void DepGraph_add(DepGraph *graph, string mod, array_string deps) {

  _PUSH(&graph->nodes,
        ((DepGraphNode){.name = mod,
                        .deps = array_clone(deps),
                        .last_cycle = tos((byte *)"", 0)}),
        tmp6, DepGraphNode);
}
DepGraph *DepGraph_resolve(DepGraph *graph) {

  map_DepGraphNode node_names = new_map(1, sizeof(DepGraphNode));

  map_DepSet node_deps = new_map(1, sizeof(DepSet));

  array_DepGraphNode tmp9 = graph->nodes;
  ;
  for (int _ = 0; _ < tmp9.len; _++) {
    DepGraphNode node = ((DepGraphNode *)tmp9.data)[_];

    map__set(&node_names, node.name, &(DepGraphNode[]){node});

    DepSet dep_set = (DepSet){.items = new_array(0, 1, sizeof(string))};

    array_string tmp11 = node.deps;
    ;
    for (int _ = 0; _ < tmp11.len; _++) {
      string dep = ((string *)tmp11.data)[_];

      DepSet_add(&/* ? */ dep_set, dep);
    };

    map__set(&node_deps, node.name, &(DepSet[]){dep_set});
  };

  DepGraph *resolved = new_dep_graph();

  while (node_deps.size != 0) {

    DepSet ready_set = (DepSet){.items = new_array(0, 1, sizeof(string))};

    map_DepSet tmp14 = node_deps;
    array_string keys_tmp14 = map_keys(&tmp14);
    for (int l = 0; l < keys_tmp14.len; l++) {
      string name = ((string *)keys_tmp14.data)[l];
      DepSet deps = {0};
      map_get(tmp14, name, &deps);

      if (DepSet_size(&/* ? */ deps) == 0) {

        DepSet_add(&/* ? */ ready_set, name);
      };
    };

    if (DepSet_size(&/* ? */ ready_set) == 0) {

      DepGraph *g = new_dep_graph();

      g->acyclic = 0;

      array_string ndk = map_keys(&/* ? */ node_deps);

      map_DepSet tmp17 = node_deps;
      array_string keys_tmp17 = map_keys(&tmp17);
      for (int l = 0; l < keys_tmp17.len; l++) {
        string name = ((string *)keys_tmp17.data)[l];
        DepSet _ = {0};
        map_get(tmp17, name, &_);

        DepGraphNode tmp18 = {0};
        bool tmp19 = map_get(node_names, name, &tmp18);

        DepGraphNode node = tmp18;

        if (string_eq(name, (*(string *)array__get(ndk, node_deps.size - 1)))) {

          DepSet tmp23 = {0};
          bool tmp24 = map_get(node_deps, name, &tmp23);

          DepSet tmp25 = {0};
          bool tmp26 = map_get(node_deps, name, &tmp25);

          node.last_cycle =
              (*(string *)array__get(tmp23.items, tmp25.items.len - 1));
        };

        _PUSH(&g->nodes, (node), tmp29, DepGraphNode);
      };

      return g;
    };

    array_string tmp30 = ready_set.items;
    ;
    for (int tmp31 = 0; tmp31 < tmp30.len; tmp31++) {
      string name = ((string *)tmp30.data)[tmp31];

      map_delete(&/* ? */ node_deps, name);

      DepGraphNode tmp33 = {0};
      bool tmp34 = map_get(node_names, name, &tmp33);

      _PUSH(&resolved->nodes, (tmp33), tmp32, DepGraphNode);
    };

    map_DepSet tmp35 = node_deps;
    array_string keys_tmp35 = map_keys(&tmp35);
    for (int l = 0; l < keys_tmp35.len; l++) {
      string name = ((string *)keys_tmp35.data)[l];
      DepSet deps = {0};
      map_get(tmp35, name, &deps);

      map__set(&node_deps, name,
               &(DepSet[]){DepSet_diff(&/* ? */ deps, ready_set)});
    };
  };

  return resolved;
}
DepGraphNode DepGraph_last_node(DepGraph *graph) {

  return (*(DepGraphNode *)array__get(graph->nodes, graph->nodes.len - 1));
}
string DepGraph_last_cycle(DepGraph *graph) {

  return DepGraph_last_node(&/* ? */ *graph).last_cycle;
}
void DepGraph_display(DepGraph *graph) {

  for (int i = 0; i < graph->nodes.len; i++) {

    DepGraphNode node = (*(DepGraphNode *)array__get(graph->nodes, i));

    array_string tmp42 = node.deps;
    ;
    for (int tmp43 = 0; tmp43 < tmp42.len; tmp43++) {
      string dep = ((string *)tmp42.data)[tmp43];

      string out = _STR(" * %.*s -> %.*s", node.name.len, node.name.str,
                        dep.len, dep.str);

      if (!graph->acyclic && i == graph->nodes.len - 1 &&
          string_eq(dep, node.last_cycle)) {

        out = string_add(out, tos2((byte *)" <-- last cycle"));
      };

      println(out);
    };
  };
}
Var Fn_find_var(Fn *f, string name) {

  int tmp1 = 0;
  ;
  for (int tmp2 = tmp1; tmp2 < f->var_idx; tmp2++) {
    int i = tmp2;

    if (string_eq((*(Var *)array__get(f->local_vars, i)).name, name)) {

      return (*(Var *)array__get(f->local_vars, i));
    };
  };

  return (Var){.typ = tos((byte *)"", 0),
               .name = tos((byte *)"", 0),
               .is_arg = 0,
               .is_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos((byte *)"", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos((byte *)"", 0),
               .mod = tos((byte *)"", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .is_changed = 0,
               .scope_level = 0};
}
void Fn_open_scope(Fn *f) {

  _PUSH(&f->defer_text, (tos2((byte *)"")), tmp7, string);

  f->scope_level++;
}
void Fn_close_scope(Fn *f) {

  f->scope_level--;

  f->defer_text = array_left(f->defer_text, f->scope_level + 1);
}
void Fn_mark_var_used(Fn *f, Var v) {

  array_Var tmp8 = f->local_vars;
  ;
  for (int i = 0; i < tmp8.len; i++) {
    Var vv = ((Var *)tmp8.data)[i];

    if (string_eq(vv.name, v.name)) {

      (*(Var *)array__get(f->local_vars, i)).is_used = 1;

      return;
    };
  };
}
void Fn_mark_var_changed(Fn *f, Var v) {

  array_Var tmp11 = f->local_vars;
  ;
  for (int i = 0; i < tmp11.len; i++) {
    Var vv = ((Var *)tmp11.data)[i];

    if (string_eq(vv.name, v.name)) {

      (*(Var *)array__get(f->local_vars, i)).is_changed = 1;
    };
  };
}
bool Fn_known_var(Fn *f, string name) {

  Var v = Fn_find_var(&/* ? */ *f, name);

  return v.name.len > 0;
}
void Fn_register_var(Fn *f, Var v) {

  Var new_var = (Var){
      .scope_level = f->scope_level,
      .typ = v.typ,
      .name = v.name,
      .is_arg = v.is_arg,
      .is_const = v.is_const,
      .args = v.args,
      .attr = v.attr,
      .is_mut = v.is_mut,
      .is_alloc = v.is_alloc,
      .ptr = v.ptr,
      .ref = v.ref,
      .parent_fn = v.parent_fn,
      .mod = v.mod,
      .line_nr = v.line_nr,
      .access_mod = v.access_mod,
      .is_global = v.is_global,
      .is_used = v.is_used,
      .is_changed = v.is_changed,
  };

  if (f->var_idx >= f->local_vars.len) {

    _PUSH(&f->local_vars, (new_var), tmp16, Var);

  } else {

    array_set(&/*q*/ f->local_vars, f->var_idx, &(Var[]){new_var});
  };

  f->var_idx++;
}
void Fn_clear_vars(Fn *f) {

  f->var_idx = 0;

  f->local_vars = new_array_from_c_array(0, 0, sizeof(Var), (Var[]){0});
}
bool Parser_is_sig(Parser *p) {

  return (p->pref->build_mode == main__BuildMode_default_mode ||
          p->pref->build_mode == main__BuildMode_build) &&
         (string_contains(p->file_path, main__ModPath));
}
Fn *new_fn(string mod, bool is_public) {

  return (Fn *)memdup(
      &(Fn){.mod = mod,
            .local_vars = array_repeat(
                &(Var[]){(Var){.typ = tos((byte *)"", 0),
                               .name = tos((byte *)"", 0),
                               .is_arg = 0,
                               .is_const = 0,
                               .args = new_array(0, 1, sizeof(Var)),
                               .attr = tos((byte *)"", 0),
                               .is_mut = 0,
                               .is_alloc = 0,
                               .ptr = 0,
                               .ref = 0,
                               .parent_fn = tos((byte *)"", 0),
                               .mod = tos((byte *)"", 0),
                               .line_nr = 0,
                               .is_global = 0,
                               .is_used = 0,
                               .is_changed = 0,
                               .scope_level = 0}},
                main__MaxLocalVars, sizeof(Var)),
            .is_public = is_public,
            .name = tos((byte *)"", 0),
            .var_idx = 0,
            .args = new_array(0, 1, sizeof(Var)),
            .is_interface = 0,
            .scope_level = 0,
            .typ = tos((byte *)"", 0),
            .is_c = 0,
            .receiver_typ = tos((byte *)"", 0),
            .is_method = 0,
            .returns_error = 0,
            .is_decl = 0,
            .defer_text = new_array(0, 1, sizeof(string))},
      sizeof(Fn));
}
void Parser_fn_decl(Parser *p) {

  Parser_fgen(p, tos2((byte *)"fn "));

  bool is_pub = p->tok == main__Token_key_pub;

  bool is_live = string_eq(p->attr, tos2((byte *)"live")) && !p->pref->is_so &&
                 p->pref->is_live;

  if (string_eq(p->attr, tos2((byte *)"live")) &&
      Parser_first_pass(&/* ? */ *p) && !p->pref->is_live && !p->pref->is_so) {

    println(tos2((byte *)"INFO: run `v -live program.v` if you want to use "
                         "[live] functions"));
  };

  if (is_pub) {

    Parser_next(p);
  };

  p->returns = 0;

  Parser_next(p);

  Fn *f = new_fn(p->mod, is_pub);

  string receiver_typ = tos2((byte *)"");

  if (p->tok == main__Token_lpar) {

    f->is_method = 1;

    Parser_check(p, main__Token_lpar);

    string receiver_name = Parser_check_name(p);

    bool is_mut = p->tok == main__Token_key_mut;

    bool is_amp = p->tok == main__Token_amp;

    if (is_mut || is_amp) {

      Parser_check_space(p, p->tok);
    };

    receiver_typ = Parser_get_type(p);

    Type T = Table_find_type(&/* ? */ *p->table, receiver_typ);

    if (T.cat == main__TypeCategory_interface_) {

      Parser_error(p,
                   _STR("invalid receiver type `%.*s` (`%.*s` is an interface)",
                        receiver_typ.len, receiver_typ.str, receiver_typ.len,
                        receiver_typ.str));
    };

    if (!Parser_first_pass(&/* ? */ *p) && !p->builtin_mod &&
        string_ne(T.mod, p->mod)) {

      printf("T.mod=%.*s\n", T.mod.len, T.mod.str);

      printf("p.mod=%.*s\n", p->mod.len, p->mod.str);

      Parser_error(p, _STR("cannot define new methods on non-local type `%.*s`",
                           receiver_typ.len, receiver_typ.str));
    };

    if (!p->builtin_mod && string_contains(receiver_typ, tos2((byte *)"*"))) {

      string t =
          string_replace(receiver_typ, tos2((byte *)"*"), tos2((byte *)""));

      Parser_error(p, _STR("use `(%.*s mut %.*s)` instead of `(%.*s *%.*s)`",
                           receiver_name.len, receiver_name.str, t.len, t.str,
                           receiver_name.len, receiver_name.str, t.len, t.str));
    };

    f->receiver_typ = receiver_typ;

    if (is_mut || is_amp) {

      receiver_typ = string_add(receiver_typ, tos2((byte *)"*"));
    };

    Parser_check(p, main__Token_rpar);

    Parser_fspace(p);

    Var receiver = (Var){.name = receiver_name,
                         .is_arg = 1,
                         .typ = receiver_typ,
                         .is_mut = is_mut,
                         .ref = is_amp,
                         .ptr = is_mut,
                         .line_nr = p->scanner->line_nr,
                         .is_const = 0,
                         .args = new_array(0, 1, sizeof(Var)),
                         .attr = tos((byte *)"", 0),
                         .is_alloc = 0,
                         .parent_fn = tos((byte *)"", 0),
                         .mod = tos((byte *)"", 0),
                         .is_global = 0,
                         .is_used = 0,
                         .is_changed = 0,
                         .scope_level = 0};

    _PUSH(&f->args, (receiver), tmp27, Var);

    Fn_register_var(f, receiver);
  };

  if (p->tok == main__Token_plus || p->tok == main__Token_minus ||
      p->tok == main__Token_mul) {

    f->name = Token_str(p->tok);

    Parser_next(p);

  } else {

    f->name = Parser_check_name(p);
  };

  bool is_c =
      string_eq(f->name, tos2((byte *)"C")) && p->tok == main__Token_dot;

  bool is_sig = Parser_is_sig(p);

  if (is_c) {

    Parser_check(p, main__Token_dot);

    f->name = Parser_check_name(p);

    f->is_c = 1;

  } else if (!p->pref->translated &&
             !string_contains(p->file_path, tos2((byte *)"view.v"))) {

    if (contains_capital(f->name)) {

      Parser_error(p, tos2((byte *)"function names cannot contain uppercase "
                                   "letters, use snake_case instead"));
    };

    if (string_contains(f->name, tos2((byte *)"__"))) {

      Parser_error(p,
                   tos2((byte *)"function names cannot contain double "
                                "underscores, use single underscores instead"));
    };
  };

  bool has_receiver = receiver_typ.len > 0;

  if (string_ne(receiver_typ, tos2((byte *)""))) {
  };

  if (!is_c && !p->builtin_mod && string_ne(p->mod, tos2((byte *)"main")) &&
      receiver_typ.len == 0) {

    f->name = Parser_prepend_mod(&/* ? */ *p, f->name);
  };

  if (Parser_first_pass(&/* ? */ *p) &&
      Table_known_fn(&/* ? */ *p->table, f->name) && receiver_typ.len == 0) {

    Fn existing_fn = Table_find_fn(&/* ? */ *p->table, f->name);

    if (!existing_fn.is_decl) {

      Parser_error(p, _STR("redefinition of `%.*s`", f->name.len, f->name.str));
    };
  };

  bool is_generic = 0;

  if (p->tok == main__Token_lt) {

    is_generic = 1;

    Parser_next(p);

    string gen_type = Parser_check_name(p);

    if (string_ne(gen_type, tos2((byte *)"T"))) {

      Parser_error(
          p, tos2((byte *)"only `T` is allowed as a generic type for now"));
    };

    Parser_check(p, main__Token_gt);

    if (Parser_first_pass(&/* ? */ *p)) {

      Table_register_generic_fn(p->table, f->name);

    } else {
    };
  };

  Parser_fn_args(p, f);

  if (p->tok == main__Token_not) {

    Parser_next(p);

    f->returns_error = 1;
  };

  string typ = tos2((byte *)"void");

  if (p->tok == main__Token_name || p->tok == main__Token_mul ||
      p->tok == main__Token_amp || p->tok == main__Token_lsbr ||
      p->tok == main__Token_question) {

    Parser_fgen(p, tos2((byte *)" "));

    typ = Parser_get_type(p);
  };

  bool is_fn_header = !is_c && !is_sig &&
                      (p->pref->translated || p->pref->is_test) &&
                      p->tok != main__Token_lcbr;

  if (is_fn_header) {

    f->is_decl = 1;
  };

  if (!is_c && !is_sig && !is_fn_header) {

    Parser_fgen(p, tos2((byte *)" "));

    Parser_check(p, main__Token_lcbr);
  };

  if (string_starts_with(typ, tos2((byte *)"Option_"))) {

    _PUSH(&p->cgen->typedefs, (_STR("typedef Option %.*s;", typ.len, typ.str)),
          tmp36, string);
  };

  f->typ = typ;

  string str_args = Fn_str_args(&/* ? */ *f, p->table);

  if (string_eq(f->name, tos2((byte *)"main")) && !has_receiver) {

    if (string_ne(str_args, tos2((byte *)"")) ||
        string_ne(typ, tos2((byte *)"void"))) {

      Parser_error(
          p,
          tos2((byte *)"fn main must have no arguments and no return values"));
    };

    typ = tos2((byte *)"int");

    str_args = tos2((byte *)"int argc, char** argv");
  };

  string dll_export_linkage =
      (p->os == main__OS_msvc && string_eq(p->attr, tos2((byte *)"live")) &&
       p->pref->is_so)
          ? (tos2((byte *)"__declspec(dllexport) "))
          : ((string_eq(p->attr, tos2((byte *)"inline")))
                 ? (tos2((byte *)"static inline "))
                 : (tos2((byte *)"")));

  if (!p->is_vweb) {

    Parser_set_current_fn(p, f);
  };

  string fn_name_cgen = Table_cgen_name(p->table, f);

  bool skip_main_in_test =
      string_eq(f->name, tos2((byte *)"main")) && p->pref->is_test;

  if (!is_c && !is_live && !is_sig && !is_fn_header && !skip_main_in_test) {

    if (p->pref->obfuscate) {

      Parser_genln(p, _STR("; // %.*s", f->name.len, f->name.str));
    };

    if (is_generic) {

      array_string gen_types = Table_fn_gen_types(p->table, f->name);

      int cur_pos = p->scanner->pos;

      Token cur_tok = p->tok;

      string cur_lit = p->lit;

      array_string tmp45 = gen_types;
      ;
      for (int tmp46 = 0; tmp46 < tmp45.len; tmp46++) {
        string gen_type = ((string *)tmp45.data)[tmp46];

        Parser_genln(p,
                     _STR("%.*s%.*s %.*s_%.*s(%.*s) {", dll_export_linkage.len,
                          dll_export_linkage.str, typ.len, typ.str,
                          fn_name_cgen.len, fn_name_cgen.str, gen_type.len,
                          gen_type.str, str_args.len, str_args.str));

        Parser_genln(p, _STR("// T start %d %.*s", p->pass,
                             Parser_strtok(&/* ? */ *p).len,
                             Parser_strtok(&/* ? */ *p).str));

        p->cur_gen_type = gen_type;

        Parser_statements(p);

        p->scanner->pos = cur_pos;

        p->tok = cur_tok;

        p->lit = cur_lit;
      };

    } else {

      Parser_genln(p, _STR("%.*s%.*s %.*s(%.*s) {", dll_export_linkage.len,
                           dll_export_linkage.str, typ.len, typ.str,
                           fn_name_cgen.len, fn_name_cgen.str, str_args.len,
                           str_args.str));
    };
  };

  if (is_fn_header) {

    Parser_genln(p, _STR("%.*s %.*s(%.*s);", typ.len, typ.str, fn_name_cgen.len,
                         fn_name_cgen.str, str_args.len, str_args.str));

    Parser_fgenln(p, tos2((byte *)""));
  };

  if (is_c) {

    Parser_fgenln(p, tos2((byte *)"\n"));
  };

  if (string_ne(receiver_typ, tos2((byte *)""))) {

    Type receiver_t = Table_find_type(&/* ? */ *p->table, receiver_typ);

    if (Parser_first_pass(&/* ? */ *p) &&
        string_eq(receiver_t.name, tos2((byte *)""))) {

      receiver_t =
          (Type){.name = string_replace(receiver_typ, tos2((byte *)"*"),
                                        tos2((byte *)"")),
                 .mod = p->mod,
                 .is_placeholder = 1,
                 .fields = new_array(0, 1, sizeof(Var)),
                 .methods = new_array(0, 1, sizeof(Fn)),
                 .parent = tos((byte *)"", 0),
                 .is_c = 0,
                 .enum_vals = new_array(0, 1, sizeof(string)),
                 .gen_types = new_array(0, 1, sizeof(string)),
                 .gen_str = 0};

      Table_register_type2(p->table, receiver_t);
    };

    Table_add_method(p->table, receiver_t.name, *f);

  } else {

    Table_register_fn(p->table, *f);
  };

  if (is_sig || Parser_first_pass(&/* ? */ *p) || is_live || is_fn_header ||
      skip_main_in_test) {

    if (!is_sig && !is_fn_header) {

      int opened_scopes = 0;

      int closed_scopes = 0;

      int temp_scanner_pos = 0;

      while (1) {

        if (p->tok == main__Token_lcbr) {

          opened_scopes++;
        };

        if (p->tok == main__Token_rcbr) {

          closed_scopes++;
        };

        if (p->tok == main__Token_gt && p->prev_tok == main__Token_name &&
            p->prev_tok2 == main__Token_lt &&
            string_at(p->scanner->text, p->scanner->pos - 1) != 'T') {

          temp_scanner_pos = p->scanner->pos;

          p->scanner->pos -= 3;

          while (p->scanner->pos > 0 &&
                 (is_name_char(string_at(p->scanner->text, p->scanner->pos)) ||
                  string_at(p->scanner->text, p->scanner->pos) == '.' ||
                  string_at(p->scanner->text, p->scanner->pos) == '<')) {

            p->scanner->pos--;
          };

          p->scanner->pos--;

          Parser_next(p);

          Parser_name_expr(p);

          p->scanner->pos = temp_scanner_pos;
        };

        if (Token_is_decl(p->tok)) {

          break;
        };

        if (closed_scopes > opened_scopes && p->prev_tok == main__Token_rcbr) {

          if (p->tok == main__Token_lsbr) {

            break;
          };
        };

        Parser_next(p);
      };
    };

    if (is_live && Parser_first_pass(&/* ? */ *p) &&
        string_eq(p->mod, tos2((byte *)"main"))) {

      _PUSH(&p->cgen->so_fns, (fn_name_cgen), tmp59, string);

      fn_name_cgen = _STR("(* %.*s )", fn_name_cgen.len, fn_name_cgen.str);
    };

    string fn_decl =
        _STR("%.*s%.*s %.*s(%.*s)", dll_export_linkage.len,
             dll_export_linkage.str, typ.len, typ.str, fn_name_cgen.len,
             fn_name_cgen.str, str_args.len, str_args.str);

    if (p->pref->obfuscate) {

      fn_decl =
          string_add(fn_decl, _STR("; // %.*s", f->name.len, f->name.str));
    };

    if (!is_c && string_ne(f->name, tos2((byte *)"main")) &&
        Parser_first_pass(&/* ? */ *p)) {

      if (string_eq(f->name, tos2((byte *)"darwin__nsstring")) &&
          p->pref->build_mode == main__BuildMode_default_mode) {

        return;
      };

      _PUSH(&p->cgen->fns, (string_add(fn_decl, tos2((byte *)";"))), tmp61,
            string);
    };

    return;
  };

  if (string_eq(p->attr, tos2((byte *)"live")) && p->pref->is_so) {

    Parser_genln(p, tos2((byte *)"pthread_mutex_lock(&live_fn_mutex);"));
  };

  if (string_eq(f->name, tos2((byte *)"main")) ||
      string_eq(f->name, tos2((byte *)"WinMain"))) {

    Parser_genln(p, tos2((byte *)"init_consts();"));

    if (array_string_contains(p->table->imports, tos2((byte *)"os"))) {

      if (string_eq(f->name, tos2((byte *)"main"))) {

        Parser_genln(p,
                     tos2((byte *)"os__args = os__init_os_args(argc, argv);"));

      } else if (string_eq(f->name, tos2((byte *)"WinMain"))) {

        Parser_genln(
            p,
            tos2((byte *)"os__args = os__parse_windows_cmd_line(pCmdLine);"));
      };
    };

    if (p->pref->is_live) {

      string file_base =
          string_replace(p->file_path, tos2((byte *)".v"), tos2((byte *)""));

      if (p->os != main__OS_windows && p->os != main__OS_msvc) {

        string so_name = string_add(file_base, tos2((byte *)".so"));

        Parser_genln(p, _STR("\nload_so(\"%.*s\");\npthread_t "
                             "_thread_so;\npthread_create(&_thread_so , NULL, "
                             "&reload_so, NULL); ",
                             so_name.len, so_name.str));

      } else {

        string so_name = string_add(file_base, (p->os == main__OS_msvc)
                                                   ? (tos2((byte *)".dll"))
                                                   : (tos2((byte *)".so")));

        Parser_genln(p, _STR("\nlive_fn_mutex = CreateMutexA(0, 0, "
                             "0);\nload_so(\"%.*s\");\nunsigned long "
                             "_thread_so;\n_thread_so = CreateThread(0, 0, "
                             "(LPTHREAD_START_ROUTINE)&reload_so, 0, 0, "
                             "0);\n				",
                             so_name.len, so_name.str));
      };
    };

    if (p->pref->is_test &&
        !string_contains(p->scanner->file_path, tos2((byte *)"/volt"))) {

      Parser_error(p, tos2((byte *)"tests cannot have function `main`"));
    };
  };

  if (is_c || is_sig || is_fn_header) {

    return;
  };

  if (p->pref->is_prof && string_ne(f->name, tos2((byte *)"main")) &&
      string_ne(f->name, tos2((byte *)"time__ticks"))) {

    Parser_genln(p, _STR("double _PROF_START = time__ticks();//%.*s",
                         f->name.len, f->name.str));

    string cgen_name = Table_cgen_name(p->table, f);

    array_set(&/*q*/ f->defer_text, f->scope_level,
              &(string[]){_STR("  %.*s_time += time__ticks() - _PROF_START;",
                               cgen_name.len, cgen_name.str)});
  };

  if (is_generic) {

    p->cgen->nogen = 1;
  };

  Parser_statements_no_rcbr(p);

  p->cgen->nogen = 0;

  if (p->pref->is_prof && string_eq(f->name, tos2((byte *)"main"))) {

    Parser_genln(p, Parser_print_prof_counters(p));
  };

  if (!p->is_vweb) {

    Parser_genln(p, (*(string *)array__get(f->defer_text, f->scope_level)));
  };

  if (string_ne(typ, tos2((byte *)"void")) && !p->returns &&
      string_ne(f->name, tos2((byte *)"main")) &&
      string_ne(f->name, tos2((byte *)"WinMain"))) {

    Parser_error(p, _STR("%.*s must return \"%.*s\"", f->name.len, f->name.str,
                         typ.len, typ.str));
  };

  if (string_eq(p->attr, tos2((byte *)"live")) && p->pref->is_so) {

    Parser_genln(p, tos2((byte *)"pthread_mutex_unlock(&live_fn_mutex);"));
  };

  if (string_eq(p->mod, tos2((byte *)"main"))) {
  };

  if (p->cur_fn->scope_level > 2) {
  };

  if (string_ne(p->mod, tos2((byte *)"main"))) {

    if (!is_generic) {

      Parser_genln(p, tos2((byte *)"}"));
    };

    return;
  };

  Parser_check_unused_variables(p);

  Parser_set_current_fn(p, main__EmptyFn);

  p->returns = 0;

  if (!is_generic) {

    Parser_genln(p, tos2((byte *)"}"));
  };
}
void Parser_check_unused_variables(Parser *p) {

  array_Var tmp68 = p->cur_fn->local_vars;
  ;
  for (int tmp69 = 0; tmp69 < tmp68.len; tmp69++) {
    Var var = ((Var *)tmp68.data)[tmp69];

    if (string_eq(var.name, tos2((byte *)""))) {

      break;
    };

    if (!var.is_used && !p->pref->is_repl && !var.is_arg &&
        !p->pref->translated && string_ne(var.name, tos2((byte *)"_"))) {

      p->scanner->line_nr = var.line_nr - 1;

      Parser_error(
          p, _STR("`%.*s` declared and not used", var.name.len, var.name.str));
    };

    if (!var.is_changed && var.is_mut && !p->pref->is_repl && !var.is_arg &&
        !p->pref->translated && string_ne(var.name, tos2((byte *)"_"))) {

      p->scanner->line_nr = var.line_nr - 1;

      Parser_error(
          p, _STR("`%.*s` is declared as mutable, but it was never changed",
                  var.name.len, var.name.str));
    };
  };
}
void Parser_async_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                          string receiver_type) {

  string thread_name = tos2((byte *)"");

  string fn_name = f.name;

  if (f.is_method) {

    fn_name =
        string_add(string_add(string_replace(receiver_type, tos2((byte *)"*"),
                                             tos2((byte *)"")),
                              tos2((byte *)"_")),
                   f.name);
  };

  string arg_struct_name = _STR("thread_arg_%.*s", fn_name.len, fn_name.str);

  string tmp_struct = Parser_get_tmp(p);

  Parser_genln(p,
               _STR("%.*s * %.*s = malloc(sizeof(%.*s));", arg_struct_name.len,
                    arg_struct_name.str, tmp_struct.len, tmp_struct.str,
                    arg_struct_name.len, arg_struct_name.str));

  string arg_struct = _STR("typedef struct  %.*s   { ", arg_struct_name.len,
                           arg_struct_name.str);

  Parser_next(p);

  Parser_check(p, main__Token_lpar);

  string str_args = tos2((byte *)"");

  bool did_gen_something = 0;

  array_Var tmp77 = f.args;
  ;
  for (int i = 0; i < tmp77.len; i++) {
    Var arg = ((Var *)tmp77.data)[i];

    arg_struct =
        string_add(arg_struct, _STR("%.*s %.*s ;", arg.typ.len, arg.typ.str,
                                    arg.name.len, arg.name.str));

    str_args =
        string_add(str_args, _STR("arg->%.*s", arg.name.len, arg.name.str));

    if (i == 0 && f.is_method) {

      Parser_genln(p, _STR("%.*s -> %.*s =  %.*s ;", tmp_struct.len,
                           tmp_struct.str, arg.name.len, arg.name.str,
                           receiver_var.len, receiver_var.str));

      if (i < f.args.len - 1) {

        str_args = string_add(str_args, tos2((byte *)","));
      };

      continue;
    };

    Parser_genln(p, _STR("%.*s -> %.*s =  ", tmp_struct.len, tmp_struct.str,
                         arg.name.len, arg.name.str));

    Parser_expression(p);

    Parser_genln(p, tos2((byte *)";"));

    if (i < f.args.len - 1) {

      Parser_check(p, main__Token_comma);

      str_args = string_add(str_args, tos2((byte *)","));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    arg_struct =
        string_add(arg_struct, tos2((byte *)"EMPTY_STRUCT_DECLARATION"));
  };

  arg_struct = string_add(
      arg_struct, _STR("} %.*s ;", arg_struct_name.len, arg_struct_name.str));

  fn_name = Table_cgen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  string wrapper_name = _STR("%.*s_thread_wrapper", fn_name.len, fn_name.str);

  string wrapper_text =
      _STR("void* %.*s(%.*s * arg) {%.*s( /*f*/%.*s );  }", wrapper_name.len,
           wrapper_name.str, arg_struct_name.len, arg_struct_name.str,
           fn_name.len, fn_name.str, str_args.len, str_args.str);

  CGen_register_thread_fn(p->cgen, wrapper_name, wrapper_text, arg_struct);

  int tmp_nr = Parser_get_tmp_counter(p);

  thread_name = _STR("_thread%d", tmp_nr);

  if (p->os != main__OS_windows && p->os != main__OS_msvc) {

    Parser_genln(p, _STR("pthread_t %.*s;", thread_name.len, thread_name.str));
  };

  string tmp2 = Parser_get_tmp(p);

  string parg = tos2((byte *)"NULL");

  if (f.args.len > 0) {

    parg = _STR(" %.*s", tmp_struct.len, tmp_struct.str);
  };

  if (p->os == main__OS_windows || p->os == main__OS_msvc) {

    Parser_genln(p,
                 _STR(" CreateThread(0,0, %.*s, %.*s, 0,0);", wrapper_name.len,
                      wrapper_name.str, parg.len, parg.str));

  } else {

    Parser_genln(p,
                 _STR("int %.*s = pthread_create(& %.*s, NULL, %.*s, %.*s);",
                      tmp2.len, tmp2.str, thread_name.len, thread_name.str,
                      wrapper_name.len, wrapper_name.str, parg.len, parg.str));
  };

  Parser_check(p, main__Token_rpar);
}
void Parser_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                    string receiver_type) {

  if (!f.is_public && !f.is_c && !p->pref->is_test && !f.is_interface &&
      string_ne(f.mod, p->mod)) {

    Parser_error(p, _STR("function `%.*s` is private", f.name.len, f.name.str));
  };

  p->calling_c = f.is_c;

  if (f.is_c && !p->builtin_mod) {

    if (string_eq(f.name, tos2((byte *)"free"))) {

      Parser_error(p, tos2((byte *)"use `free()` instead of `C.free()`"));

    } else if (string_eq(f.name, tos2((byte *)"malloc"))) {

      Parser_error(p, tos2((byte *)"use `malloc()` instead of `C.malloc()`"));
    };
  };

  string cgen_name = Table_cgen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  Parser_next(p);

  string gen_type = tos2((byte *)"");

  if (p->tok == main__Token_lt) {

    Parser_check(p, main__Token_lt);

    gen_type = Parser_check_name(p);

    if (string_eq(gen_type, tos2((byte *)"T")) &&
        string_ne(p->cur_gen_type, tos2((byte *)""))) {

      gen_type = p->cur_gen_type;
    };

    if (Parser_first_pass(&/* ? */ *p)) {

      printf("registering %.*s in %.*s fname=%.*s\n", gen_type.len,
             gen_type.str, f.name.len, f.name.str, f.name.len, f.name.str);

      Table_register_generic_fn_type(p->table, f.name, gen_type);

      return;
    };

    cgen_name = string_add(cgen_name, string_add(tos2((byte *)"_"), gen_type));

    Parser_check(p, main__Token_gt);
  };

  if (!f.is_method) {

    Parser_gen(p, cgen_name);

    Parser_gen(p, tos2((byte *)"("));

  } else {

    string method_call = _STR("%.*s(", cgen_name.len, cgen_name.str);

    Var receiver = *(Var *)array_first(f.args);

    if (receiver.is_mut && !p->expr_var.is_mut) {

      printf("%.*s  recv=%.*s recv_mut=%d\n", method_call.len, method_call.str,
             receiver.name.len, receiver.name.str, receiver.is_mut);

      Parser_error(p, _STR("`%.*s` is immutable, declare it with `mut`",
                           p->expr_var.name.len, p->expr_var.name.str));
    };

    if (!p->expr_var.is_changed) {

      Fn_mark_var_changed(p->cur_fn, p->expr_var);
    };

    if (receiver.ref || (receiver.is_mut &&
                         !string_contains(receiver_type, tos2((byte *)"*")))) {

      method_call = string_add(method_call, tos2((byte *)"& /* ? */"));
    };

    if (!receiver.is_mut && string_contains(receiver_type, tos2((byte *)"*"))) {

      method_call = string_add(method_call, tos2((byte *)"*"));
    };

    string cast = tos2((byte *)"");

    if (string_eq(f.typ, tos2((byte *)"void*"))) {

      cast = string_all_after(receiver_type, tos2((byte *)"_"));

      cast = _STR("*(%.*s*) ", cast.len, cast.str);
    };

    CGen_set_placeholder(p->cgen, method_ph,
                         _STR("%.*s %.*s", cast.len, cast.str, method_call.len,
                              method_call.str));
  };

  Parser_fn_call_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  Parser_gen(p, tos2((byte *)")"));

  p->calling_c = 0;
}
void Parser_fn_args(Parser *p, Fn *f) {

  Parser_check(p, main__Token_lpar);

  if (f->is_interface) {

    Var int_arg = (Var){.typ = f->receiver_typ,
                        .name = tos((byte *)"", 0),
                        .is_arg = 0,
                        .is_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos((byte *)"", 0),
                        .is_mut = 0,
                        .is_alloc = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos((byte *)"", 0),
                        .mod = tos((byte *)"", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .is_changed = 0,
                        .scope_level = 0};

    _PUSH(&f->args, (int_arg), tmp89, Var);
  };

  bool types_only = p->tok == main__Token_mul || p->tok == main__Token_amp ||
                    (Parser_peek(p) == main__Token_comma &&
                     Table_known_type(&/* ? */ *p->table, p->lit)) ||
                    Parser_peek(p) == main__Token_rpar;

  if (types_only) {

    while (p->tok != main__Token_rpar) {

      string typ = Parser_get_type(p);

      Var v = (Var){.typ = typ,
                    .is_arg = 1,
                    .line_nr = p->scanner->line_nr,
                    .name = tos((byte *)"", 0),
                    .is_const = 0,
                    .args = new_array(0, 1, sizeof(Var)),
                    .attr = tos((byte *)"", 0),
                    .is_mut = 0,
                    .is_alloc = 0,
                    .ptr = 0,
                    .ref = 0,
                    .parent_fn = tos((byte *)"", 0),
                    .mod = tos((byte *)"", 0),
                    .is_global = 0,
                    .is_used = 0,
                    .is_changed = 0,
                    .scope_level = 0};

      _PUSH(&f->args, (v), tmp93, Var);

      if (p->tok == main__Token_comma) {

        Parser_next(p);
      };
    };
  };

  while (p->tok != main__Token_rpar) {

    array_string names = new_array_from_c_array(
        1, 1, sizeof(string), (string[]){Parser_check_name(p)});

    while (p->tok == main__Token_comma) {

      Parser_check(p, main__Token_comma);

      Parser_fspace(p);

      _PUSH(&names, (Parser_check_name(p)), tmp95, string);
    };

    Parser_fspace(p);

    bool is_mut = p->tok == main__Token_key_mut;

    if (is_mut) {

      Parser_next(p);
    };

    string typ = Parser_get_type(p);

    if (is_mut && is_primitive_type(typ)) {

      Parser_error(p,
                   string_add(tos2((byte *)"mutable arguments are only allowed "
                                           "for arrays, maps, and structs."),
                              tos2((byte *)"\nreturn values instead: `foo(n "
                                           "mut int)` => `foo(n int) int`")));
    };

    array_string tmp98 = names;
    ;
    for (int tmp99 = 0; tmp99 < tmp98.len; tmp99++) {
      string name = ((string *)tmp98.data)[tmp99];

      if (!Parser_first_pass(&/* ? */ *p) &&
          !Table_known_type(&/* ? */ *p->table, typ)) {

        Parser_error(p, _STR("fn_args: unknown type %.*s", typ.len, typ.str));
      };

      if (is_mut) {

        typ = string_add(typ, tos2((byte *)"*"));
      };

      Var v = (Var){.name = name,
                    .typ = typ,
                    .is_arg = 1,
                    .is_mut = is_mut,
                    .ptr = is_mut,
                    .line_nr = p->scanner->line_nr,
                    .is_const = 0,
                    .args = new_array(0, 1, sizeof(Var)),
                    .attr = tos((byte *)"", 0),
                    .is_alloc = 0,
                    .ref = 0,
                    .parent_fn = tos((byte *)"", 0),
                    .mod = tos((byte *)"", 0),
                    .is_global = 0,
                    .is_used = 0,
                    .is_changed = 0,
                    .scope_level = 0};

      Fn_register_var(f, v);

      _PUSH(&f->args, (v), tmp101, Var);
    };

    if (p->tok == main__Token_comma) {

      Parser_next(p);
    };

    if (p->tok == main__Token_dotdot) {

      _PUSH(&f->args,
            ((Var){.name = tos2((byte *)".."),
                   .typ = tos((byte *)"", 0),
                   .is_arg = 0,
                   .is_const = 0,
                   .args = new_array(0, 1, sizeof(Var)),
                   .attr = tos((byte *)"", 0),
                   .is_mut = 0,
                   .is_alloc = 0,
                   .ptr = 0,
                   .ref = 0,
                   .parent_fn = tos((byte *)"", 0),
                   .mod = tos((byte *)"", 0),
                   .line_nr = 0,
                   .is_global = 0,
                   .is_used = 0,
                   .is_changed = 0,
                   .scope_level = 0}),
            tmp102, Var);

      Parser_next(p);
    };

    v_array_free(names); // close_scope free
  };

  { Parser_check(p, main__Token_rpar); }
}
Fn *Parser_fn_call_args(Parser *p, Fn *f) {

  Parser_check(p, main__Token_lpar);

  if (f->is_c) {

    while (p->tok != main__Token_rpar) {

      Parser_bool_expression(p);

      if (p->tok == main__Token_comma) {

        Parser_gen(p, tos2((byte *)", "));

        Parser_check(p, main__Token_comma);
      };
    };

    Parser_check(p, main__Token_rpar);

    return f;
  };

  if (p->v->pref->is_debug && string_eq(f->name, tos2((byte *)"panic"))) {

    string mod_name =
        string_replace(p->mod, tos2((byte *)"_dot_"), tos2((byte *)"."));

    string fn_name =
        string_replace(p->cur_fn->name, _STR("%.*s__", p->mod.len, p->mod.str),
                       tos2((byte *)""));

    string file_path =
        string_replace(p->file_path, tos2((byte *)"\\"), tos2((byte *)"\\\\"));

    CGen_resetln(
        p->cgen,
        string_replace(p->cgen->cur_line, tos2((byte *)"v_panic ("),
                       _STR("_panic_debug (%d, tos2((byte *)\"%.*s\"), "
                            "tos2((byte *)\"%.*s\"), tos2((byte *)\"%.*s\"), ",
                            p->scanner->line_nr, file_path.len, file_path.str,
                            mod_name.len, mod_name.str, fn_name.len,
                            fn_name.str)));
  };

  array_Var tmp106 = f->args;
  ;
  for (int i = 0; i < tmp106.len; i++) {
    Var arg = ((Var *)tmp106.data)[i];

    if (i == 0 && f->is_method) {

      if (f->args.len > 1) {

        Parser_gen(p, tos2((byte *)","));
      };

      continue;
    };

    if (i == f->args.len - 1 && string_eq(arg.name, tos2((byte *)".."))) {

      break;
    };

    int ph = CGen_add_placeholder(p->cgen);

    if (p->tok == main__Token_rpar) {

      string str_args = Fn_str_args(&/* ? */ *f, p->table);

      Parser_error(p,
                   _STR("not enough arguments in call to `%.*s (%.*s)`",
                        f->name.len, f->name.str, str_args.len, str_args.str));
    };

    if (arg.is_mut) {

      if (p->tok != main__Token_key_mut && p->tok == main__Token_name) {

        string dots_example = _STR("mut %.*s", p->lit.len, p->lit.str);

        if (i > 0) {

          dots_example = string_add(tos2((byte *)".., "), dots_example);
        };

        if (i < f->args.len - 1) {

          dots_example = string_add(dots_example, tos2((byte *)",.."));
        };

        Parser_error(p, _STR("`%.*s` is a mutable argument, you need to "
                             "provide `mut`: `%.*s(%.*s)`",
                             arg.name.len, arg.name.str, f->name.len,
                             f->name.str, dots_example.len, dots_example.str));
      };

      if (Parser_peek(p) != main__Token_name) {

        Parser_error(
            p, _STR("`%.*s` is a mutable argument, you need to provide a "
                    "variable to modify: `%.*s(... mut a...)`",
                    arg.name.len, arg.name.str, f->name.len, f->name.str));
      };

      Parser_check(p, main__Token_key_mut);

      string var_name = p->lit;

      Var v = Fn_find_var(&/* ? */ *p->cur_fn, var_name);

      if (string_eq(v.name, tos2((byte *)""))) {

        Parser_error(
            p, _STR("`%.*s` is a mutable argument, you need to provide a "
                    "variable to modify: `%.*s(... mut a...)`",
                    arg.name.len, arg.name.str, f->name.len, f->name.str));
      };

      if (!v.is_changed) {

        Fn_mark_var_changed(p->cur_fn, v);
      };
    };

    p->expected_type = arg.typ;

    string typ = Parser_bool_expression(p);

    if (i == 0 &&
        (string_eq(f->name, tos2((byte *)"println")) ||
         string_eq(f->name, tos2((byte *)"print"))) &&
        string_ne(typ, tos2((byte *)"string")) &&
        string_ne(typ, tos2((byte *)"void"))) {

      Type T = Table_find_type(&/* ? */ *p->table, typ);

#ifndef _WIN32

      string fmt = Parser_typ_to_fmt(p, typ, 0);

      if (string_ne(fmt, tos2((byte *)""))) {

        CGen_resetln(
            p->cgen,
            string_replace(
                p->cgen->cur_line, string_add(f->name, tos2((byte *)" (")),
                string_add(string_add(tos2((byte *)"/*opt*/printf (\""), fmt),
                           tos2((byte *)"\\n\", "))));

        continue;
      };

#endif
      ;

      if (string_ends_with(typ, tos2((byte *)"*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"ptr_str("));

        Parser_gen(p, tos2((byte *)")"));

        continue;
      };

      if (!Type_has_method(&/* ? */ T, tos2((byte *)"str"))) {

        if (string_starts_with(T.name, tos2((byte *)"array_"))) {

          Parser_gen_array_str(p, T);

          CGen_set_placeholder(p->cgen, ph,
                               _STR("%.*s_str(", typ.len, typ.str));

          Parser_gen(p, tos2((byte *)")"));

          continue;
        };

        string error_msg =
            (_STR("`%.*s` needs to have method `str() string` to be printable",
                  typ.len, typ.str));

        if (T.fields.len > 0) {

          int index = p->cgen->cur_line.len - 1;

          while (index > 0 && string_at(p->cgen->cur_line, index - 1) != '(') {

            index--;
          };

          string name = string_right(p->cgen->cur_line, index + 1);

          if (string_eq(name, tos2((byte *)"}"))) {

            Parser_error(p, error_msg);
          };

          CGen_resetln(p->cgen, string_left(p->cgen->cur_line, index));

          Scanner_create_type_string(p->scanner, T, name);

          string_replace(p->cgen->cur_line, typ, tos2((byte *)""));

          Parser_next(p);

          return Parser_fn_call_args(p, f);
        };

        Parser_error(p, error_msg);
      };

      CGen_set_placeholder(p->cgen, ph, _STR("%.*s_str(", typ.len, typ.str));

      Parser_gen(p, tos2((byte *)")"));

      continue;
    };

    string got = typ;

    string expected = arg.typ;

    if (!Parser_check_types_no_throw(p, got, expected)) {

      string err =
          _STR("Fn \"%.*s\" wrong arg #%d. ", f->name.len, f->name.str, i + 1);

      err = string_add(err, _STR("Expected \"%.*s\" (%.*s)  but got \"%.*s\"",
                                 arg.typ.len, arg.typ.str, arg.name.len,
                                 arg.name.str, typ.len, typ.str));

      Parser_error(p, err);
    };

    bool is_interface = Table_is_interface(&/* ? */ *p->table, arg.typ);

    if (!is_interface) {

      if (string_contains(got, tos2((byte *)"*")) &&
          !string_contains(expected, tos2((byte *)"*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"*"));
      };

      if (!string_contains(got, tos2((byte *)"*")) &&
          string_contains(expected, tos2((byte *)"*")) &&
          string_ne(got, tos2((byte *)"voidptr"))) {

        if (string_starts_with(expected, tos2((byte *)"array_")) &&
            string_ends_with(expected, tos2((byte *)"*"))) {

          CGen_set_placeholder(p->cgen, ph,
                               tos2((byte *)"& /*111*/ (array[]){"));

          Parser_gen(p, tos2((byte *)"}[0] "));

        } else if (!(string_eq(expected, tos2((byte *)"void*")) &&
                     string_eq(got, tos2((byte *)"int"))) &&
                   !(string_eq(expected, tos2((byte *)"byte*")) &&
                     string_contains(got, tos2((byte *)"]byte"))) &&
                   !(string_eq(expected, tos2((byte *)"byte*")) &&
                     string_eq(got, tos2((byte *)"string"))) &&
                   !(string_eq(expected, tos2((byte *)"byte*")) &&
                     string_eq(got, tos2((byte *)"byteptr")))) {

          CGen_set_placeholder(p->cgen, ph,
                               _STR("& /*112 EXP:\"%.*s\" GOT:\"%.*s\" */",
                                    expected.len, expected.str, got.len,
                                    got.str));
        };
      };
    };

    if (is_interface) {

      if (!string_contains(got, tos2((byte *)"*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"&"));
      };

      Type interface_type = Table_find_type(&/* ? */ *p->table, arg.typ);

      array_Fn tmp125 = interface_type.methods;
      ;
      for (int tmp126 = 0; tmp126 < tmp125.len; tmp126++) {
        Fn method = ((Fn *)tmp125.data)[tmp126];

        Parser_gen(p, _STR(", %.*s_%.*s ", typ.len, typ.str, method.name.len,
                           method.name.str));
      };
    };

    if (i < f->args.len - 1) {

      bool is_vararg = i == f->args.len - 2 &&
                       string_eq((*(Var *)array__get(f->args, i + 1)).name,
                                 tos2((byte *)".."));

      if (p->tok != main__Token_comma && !is_vararg) {

        Parser_error(p, _STR("wrong number of arguments for %d,%.*s fn `%.*s`: "
                             "expected %d, but got less",
                             i, arg.name.len, arg.name.str, f->name.len,
                             f->name.str, f->args.len));
      };

      if (p->tok == main__Token_comma) {

        Parser_fgen(p, tos2((byte *)", "));
      };

      if (!is_vararg) {

        Parser_next(p);

        Parser_gen(p, tos2((byte *)","));
      };
    };
  };

  if (f->args.len > 0) {

    Var last_arg = *(Var *)array_last(f->args);

    if (string_eq(last_arg.name, tos2((byte *)".."))) {

      while (p->tok != main__Token_rpar) {

        if (p->tok == main__Token_comma) {

          Parser_gen(p, tos2((byte *)","));

          Parser_check(p, main__Token_comma);
        };

        Parser_bool_expression(p);
      };
    };
  };

  if (p->tok == main__Token_comma) {

    Parser_error(p, _STR("wrong number of arguments for fn `%.*s`: expected "
                         "%d, but got more",
                         f->name.len, f->name.str, f->args.len));
  };

  Parser_check(p, main__Token_rpar);

  return f;
}
string Fn_typ_str(Fn f) {

  strings__Builder sb = strings__new_builder(50);

  strings__Builder_write(&/* ? */ sb, tos2((byte *)"fn ("));

  array_Var tmp132 = f.args;
  ;
  for (int i = 0; i < tmp132.len; i++) {
    Var arg = ((Var *)tmp132.data)[i];

    strings__Builder_write(&/* ? */ sb, arg.typ);

    if (i < f.args.len - 1) {

      strings__Builder_write(&/* ? */ sb, tos2((byte *)","));
    };
  };

  strings__Builder_write(&/* ? */ sb, tos2((byte *)")"));

  if (string_ne(f.typ, tos2((byte *)"void"))) {

    strings__Builder_write(&/* ? */ sb, _STR(" %.*s", f.typ.len, f.typ.str));
  };

  return strings__Builder_str(sb);
}
string Fn_str_args(Fn *f, Table *table) {

  string s = tos2((byte *)"");

  array_Var tmp134 = f->args;
  ;
  for (int i = 0; i < tmp134.len; i++) {
    Var arg = ((Var *)tmp134.data)[i];

    if (Table_is_interface(&/* ? */ *table, arg.typ)) {

      s = string_add(s, _STR(" void* %.*s", arg.name.len, arg.name.str));

      Type interface_type = Table_find_type(&/* ? */ *table, arg.typ);

      array_Fn tmp136 = interface_type.methods;
      ;
      for (int tmp137 = 0; tmp137 < tmp136.len; tmp137++) {
        Fn method = ((Fn *)tmp136.data)[tmp137];

        s = string_add(s, _STR(", %.*s (*%.*s_%.*s)(void*", method.typ.len,
                               method.typ.str, arg.typ.len, arg.typ.str,
                               method.name.len, method.name.str));

        if (method.args.len > 1) {

          array_Var tmp138 = array_right(method.args, 1);
          ;
          for (int tmp139 = 0; tmp139 < tmp138.len; tmp139++) {
            Var a = ((Var *)tmp138.data)[tmp139];

            s = string_add(s, _STR(", %.*s", a.typ.len, a.typ.str));
          };
        };

        s = string_add(s, tos2((byte *)")"));
      };

    } else if (string_eq(arg.name, tos2((byte *)".."))) {

      s = string_add(s, tos2((byte *)"..."));

    } else {

      s = string_add(
          s, Table_cgen_name_type_pair(&/* ? */ *table, arg.name, arg.typ));
    };

    if (i < f->args.len - 1) {

      s = string_add(s, tos2((byte *)", "));
    };
  };

  return s;
}
void Parser_gen_json_for_type(Parser *p, Type typ) {

  string dec = tos2((byte *)"");

  string enc = tos2((byte *)"");

  string t = typ.name;

  if (string_eq(t, tos2((byte *)"int")) ||
      string_eq(t, tos2((byte *)"string")) ||
      string_eq(t, tos2((byte *)"bool"))) {

    return;
  };

  if (Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  Fn dec_fn = (Fn){.mod = p->mod,
                   .typ = _STR("Option_%.*s", typ.name.len, typ.name.str),
                   .name = js_dec_name(t),
                   .local_vars = new_array(0, 1, sizeof(Var)),
                   .var_idx = 0,
                   .args = new_array(0, 1, sizeof(Var)),
                   .is_interface = 0,
                   .scope_level = 0,
                   .is_c = 0,
                   .receiver_typ = tos((byte *)"", 0),
                   .is_public = 0,
                   .is_method = 0,
                   .returns_error = 0,
                   .is_decl = 0,
                   .defer_text = new_array(0, 1, sizeof(string))};

  if (Table_known_fn(&/* ? */ *p->table, dec_fn.name)) {

    return;
  };

  Var arg = (Var){.typ = tos2((byte *)"cJSON*"),
                  .name = tos((byte *)"", 0),
                  .is_arg = 0,
                  .is_const = 0,
                  .args = new_array(0, 1, sizeof(Var)),
                  .attr = tos((byte *)"", 0),
                  .is_mut = 0,
                  .is_alloc = 0,
                  .ptr = 0,
                  .ref = 0,
                  .parent_fn = tos((byte *)"", 0),
                  .mod = tos((byte *)"", 0),
                  .line_nr = 0,
                  .is_global = 0,
                  .is_used = 0,
                  .is_changed = 0,
                  .scope_level = 0};

  _PUSH(&dec_fn.args, (arg), tmp6, Var);

  Table_register_fn(p->table, dec_fn);

  Fn enc_fn = (Fn){.mod = p->mod,
                   .typ = tos2((byte *)"cJSON*"),
                   .name = js_enc_name(t),
                   .local_vars = new_array(0, 1, sizeof(Var)),
                   .var_idx = 0,
                   .args = new_array(0, 1, sizeof(Var)),
                   .is_interface = 0,
                   .scope_level = 0,
                   .is_c = 0,
                   .receiver_typ = tos((byte *)"", 0),
                   .is_public = 0,
                   .is_method = 0,
                   .returns_error = 0,
                   .is_decl = 0,
                   .defer_text = new_array(0, 1, sizeof(string))};

  Var enc_arg = (Var){.typ = t,
                      .name = tos((byte *)"", 0),
                      .is_arg = 0,
                      .is_const = 0,
                      .args = new_array(0, 1, sizeof(Var)),
                      .attr = tos((byte *)"", 0),
                      .is_mut = 0,
                      .is_alloc = 0,
                      .ptr = 0,
                      .ref = 0,
                      .parent_fn = tos((byte *)"", 0),
                      .mod = tos((byte *)"", 0),
                      .line_nr = 0,
                      .is_global = 0,
                      .is_used = 0,
                      .is_changed = 0,
                      .scope_level = 0};

  _PUSH(&enc_fn.args, (enc_arg), tmp9, Var);

  Table_register_fn(p->table, enc_fn);

  dec = string_add(
      dec,
      _STR("\n//%.*s %.*s(cJSON* root) {\nOption %.*s(cJSON* root, %.*s* res) "
           "{\n//  %.*s res;\n  if (!root) {\n    const char *error_ptr = "
           "cJSON_GetErrorPtr();\n    if (error_ptr != NULL)	{\n      "
           "fprintf(stderr, \"Error in decode() for %.*s error_ptr=: "
           "%%%%s\\n\", error_ptr);\n//      printf(\"\\nbad js=%%%%s\\n\", "
           "js.str);\n      return v_error(tos2(error_ptr));\n    }\n  }\n",
           t.len, t.str, dec_fn.name.len, dec_fn.name.str, dec_fn.name.len,
           dec_fn.name.str, t.len, t.str, t.len, t.str, t.len, t.str));

  enc =
      string_add(enc, _STR("\ncJSON* %.*s(%.*s val) {\ncJSON *o = "
                           "cJSON_CreateObject();\nstring res = tos2(\"\");\n",
                           enc_fn.name.len, enc_fn.name.str, t.len, t.str));

  if (string_starts_with(t, tos2((byte *)"array_"))) {

    dec = string_add(dec, Parser_decode_array(p, t));

    enc = string_add(enc, Parser_encode_array(&/* ? */ *p, t));
  };

  array_Var tmp10 = typ.fields;
  ;
  for (int tmp11 = 0; tmp11 < tmp10.len; tmp11++) {
    Var field = ((Var *)tmp10.data)[tmp11];

    if (string_eq(field.attr, tos2((byte *)"skip"))) {

      continue;
    };

    string name = (string_starts_with(field.attr, tos2((byte *)"json:")))
                      ? (string_right(field.attr, 5))
                      : (field.name);

    Type field_type = Table_find_type(&/* ? */ *p->table, field.typ);

    string _typ =
        string_replace(field.typ, tos2((byte *)"*"), tos2((byte *)""));

    string enc_name = js_enc_name(_typ);

    if (string_eq(field.attr, tos2((byte *)"raw"))) {

      dec = string_add(
          dec,
          string_add(_STR(" res->%.*s = tos2(cJSON_PrintUnformatted(",
                          field.name.len, field.name.str),
                     _STR("js_get(root, \"%.*s\")));\n", name.len, name.str)));

    } else {

      Parser_gen_json_for_type(p, field_type);

      string dec_name = js_dec_name(_typ);

      if (is_js_prim(_typ)) {

        dec = string_add(
            dec, string_add(_STR(" res->%.*s = %.*s(js_get(", field.name.len,
                                 field.name.str, dec_name.len, dec_name.str),
                            _STR("root, \"%.*s\"))", name.len, name.str)));

      } else {

        dec =
            string_add(dec, _STR(" %.*s(js_get(root, \"%.*s\"), & (res->%.*s))",
                                 dec_name.len, dec_name.str, name.len, name.str,
                                 field.name.len, field.name.str));
      };

      dec = string_add(dec, tos2((byte *)";\n"));
    };

    enc = string_add(
        enc, _STR("  cJSON_AddItemToObject(o,  \"%.*s\",%.*s(val.%.*s)); \n",
                  name.len, name.str, enc_name.len, enc_name.str,
                  field.name.len, field.name.str));
  };

  _PUSH(&p->cgen->fns,
        (_STR("%.*s return opt_ok(res, sizeof(*res)); \n}", dec.len, dec.str)),
        tmp17, string);

  _PUSH(&p->cgen->fns,
        (_STR("/*enc start*/ %.*s return o;}", enc.len, enc.str)), tmp18,
        string);
}
bool is_js_prim(string typ) {

  return string_eq(typ, tos2((byte *)"int")) ||
         string_eq(typ, tos2((byte *)"string")) ||
         string_eq(typ, tos2((byte *)"bool")) ||
         string_eq(typ, tos2((byte *)"f32")) ||
         string_eq(typ, tos2((byte *)"f64")) ||
         string_eq(typ, tos2((byte *)"i8")) ||
         string_eq(typ, tos2((byte *)"i16")) ||
         string_eq(typ, tos2((byte *)"i64")) ||
         string_eq(typ, tos2((byte *)"u16")) ||
         string_eq(typ, tos2((byte *)"u32")) ||
         string_eq(typ, tos2((byte *)"u64"));
}
string Parser_decode_array(Parser *p, string array_type) {

  string typ =
      string_replace(array_type, tos2((byte *)"array_"), tos2((byte *)""));

  Type t = Table_find_type(&/* ? */ *p->table, typ);

  string fn_name = js_dec_name(typ);

  Parser_gen_json_for_type(p, t);

  string s = tos2((byte *)"");

  if (is_js_prim(typ)) {

    s = _STR("%.*s val= %.*s(jsval); ", typ.len, typ.str, fn_name.len,
             fn_name.str);

  } else {

    s = _STR("  %.*s val; %.*s(jsval, &val); ", typ.len, typ.str, fn_name.len,
             fn_name.str);
  };

  return _STR("\n*res = new_array(0, 0, sizeof(%.*s));\nconst cJSON *jsval = "
              "NULL;\ncJSON_ArrayForEach(jsval, root)\n{\n%.*s\n  "
              "array__push(res, &val);\n}\n",
              typ.len, typ.str, s.len, s.str);
}
string js_enc_name(string typ) {

  string name = _STR("json__jsencode_%.*s", typ.len, typ.str);

  return name;
}
string js_dec_name(string typ) {

  string name = _STR("json__jsdecode_%.*s", typ.len, typ.str);

  return name;
}
string Parser_encode_array(Parser *p, string array_type) {

  string typ =
      string_replace(array_type, tos2((byte *)"array_"), tos2((byte *)""));

  string fn_name = js_enc_name(typ);

  return _STR(
      "\no = cJSON_CreateArray();\nfor (int i = 0; i < val.len; i++){\n  "
      "cJSON_AddItemToArray(o, %.*s(  ((%.*s*)val.data)[i]  ));\n}\n",
      fn_name.len, fn_name.str, typ.len, typ.str);
}
array_string V_generate_hotcode_reloading_compiler_flags(V *v) {

  array_string a = new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (v->pref->is_live || v->pref->is_so) {

    if ((v->os == main__OS_linux ||
         string_eq(os__user_os(), tos2((byte *)"linux")))) {

      _PUSH(&a, (tos2((byte *)"-rdynamic")), tmp2, string);
    };

    if ((v->os == main__OS_mac ||
         string_eq(os__user_os(), tos2((byte *)"mac")))) {

      _PUSH(&a, (tos2((byte *)"-flat_namespace")), tmp3, string);
    };
  };

  return a;

  v_array_free(a); // close_scope free
}
void V_generate_hotcode_reloading_declarations(V *v) {

  CGen *cgen = v->cgen;

  if (v->os != main__OS_windows && v->os != main__OS_msvc) {

    if (v->pref->is_so) {

      CGen_genln(cgen, tos2((byte *)"pthread_mutex_t live_fn_mutex;"));
    };

    if (v->pref->is_live) {

      CGen_genln(cgen, tos2((byte *)"pthread_mutex_t live_fn_mutex = "
                                    "PTHREAD_MUTEX_INITIALIZER;"));
    };

  } else {

    if (v->pref->is_so) {

      CGen_genln(cgen, tos2((byte *)"HANDLE live_fn_mutex;"));
    };

    if (v->pref->is_live) {

      CGen_genln(cgen, tos2((byte *)"HANDLE live_fn_mutex = 0;"));
    };
  };
}
void V_generate_hotcode_reloading_code(V *v) {

  CGen *cgen = v->cgen;

  if (v->pref->is_live) {

    string file = v->dir;

    string file_base =
        string_replace(v->dir, tos2((byte *)".v"), tos2((byte *)""));

    string so_name = string_add(file_base, tos2((byte *)".so"));

    string vexe = (*(string *)array__get(os__args, 0));

    if (string_eq(os__user_os(), tos2((byte *)"windows"))) {

      vexe = string_replace(vexe, tos2((byte *)"\\"), tos2((byte *)"\\\\"));
    };

    string msvc = tos2((byte *)"");

    if (v->os == main__OS_msvc) {

      msvc = tos2((byte *)"-os msvc");
    };

    string debug = tos2((byte *)"");

    if (v->pref->is_debug) {

      debug = tos2((byte *)"-debug");
    };

    os__system(_STR("%.*s %.*s %.*s -o %.*s -shared %.*s", vexe.len, vexe.str,
                    msvc.len, msvc.str, debug.len, debug.str, file_base.len,
                    file_base.str, file.len, file.str));

    CGen_genln(
        cgen,
        tos2((
            byte *)"\n\nvoid lfnmutex_print(char *s){\n	if(0){\n	"
                   "	fflush(stderr);\n		fprintf(stderr,\">> "
                   "live_fn_mutex: %p | %s\\n\", &live_fn_mutex, s);\n	"
                   "	fflush(stderr);\n	}\n}\n"));

    if (v->os != main__OS_windows && v->os != main__OS_msvc) {

      CGen_genln(
          cgen,
          tos2(
              (byte *)"\n#include <dlfcn.h>\nvoid* live_lib=0;\nint "
                      "load_so(byteptr path) {\n	char "
                      "cpath[1024];\n	sprintf(cpath,\"./%s\", "
                      "path);\n	//printf(\"load_so %s\\n\", cpath);\n	if "
                      "(live_lib) dlclose(live_lib);\n	live_lib = "
                      "dlopen(cpath, RTLD_LAZY);\n	if (!live_lib) "
                      "{\n		puts(\"open failed\");\n	"
                      "	exit(1);\n		return 0;\n	}\n"));

      array_string tmp14 = cgen->so_fns;
      ;
      for (int tmp15 = 0; tmp15 < tmp14.len; tmp15++) {
        string so_fn = ((string *)tmp14.data)[tmp15];

        CGen_genln(cgen, _STR("%.*s = dlsym(live_lib, \"%.*s\");  ", so_fn.len,
                              so_fn.str, so_fn.len, so_fn.str));
      };

    } else {

      CGen_genln(
          cgen,
          tos2((
              byte
                  *)"\nvoid* live_lib=0;\nint load_so(byteptr path) {\n	char "
                    "cpath[1024];\n	sprintf(cpath, \"./%s\", "
                    "path);\n	if (live_lib) FreeLibrary(live_lib);\n	"
                    "live_lib = LoadLibraryA(cpath);\n	if (!live_lib) "
                    "{\n		puts(\"open failed\");\n	"
                    "	exit(1);\n		return 0;\n	}\n"));

      array_string tmp16 = cgen->so_fns;
      ;
      for (int tmp17 = 0; tmp17 < tmp16.len; tmp17++) {
        string so_fn = ((string *)tmp16.data)[tmp17];

        CGen_genln(cgen,
                   _STR("%.*s = (void *)GetProcAddress(live_lib, \"%.*s\");  ",
                        so_fn.len, so_fn.str, so_fn.len, so_fn.str));
      };
    };

    CGen_genln(
        cgen,
        _STR("return 1;\n}\n\nint _live_reloads = 0;\nvoid reload_so() "
             "{\n	char new_so_base[1024];\n	char "
             "new_so_name[1024];\n	char compile_cmd[1024];\n	int "
             "last = os__file_last_mod_unix(tos2(\"%.*s\"));\n	while (1) "
             "{\n		// TODO use inotify\n		int now = "
             "os__file_last_mod_unix(tos2(\"%.*s\"));\n		if (now != "
             "last) {\n			last = now;\n			"
             "_live_reloads++;\n\n			//v -o bounce -shared "
             "bounce.v\n			sprintf(new_so_base, "
             "\".tmp.%%d.%.*s\", _live_reloads);\n			#ifdef "
             "_WIN32\n			// We have to make this directory "
             "becuase windows WILL NOT\n			// do it for "
             "us\n			"
             "os__mkdir(string_all_before_last(tos2(new_so_base), "
             "tos2(\"/\")));\n			#endif\n		"
             "	#ifdef _MSC_VER\n			sprintf(new_so_name, "
             "\"%%s.dll\", new_so_base);\n			#else\n	"
             "		sprintf(new_so_name, \"%%s.so\", "
             "new_so_base);\n			#endif\n		"
             "	sprintf(compile_cmd, \"%.*s %.*s -o %%s -shared %.*s\", "
             "new_so_base);\n			"
             "os__system(tos2(compile_cmd));\n\n			if( "
             "!os__file_exists(tos2(new_so_name)) ) {\n			"
             "	fprintf(stderr, \"Errors while compiling %.*s\\n\");\n	"
             "			continue;\n			}\n\n	"
             "		lfnmutex_print(\"reload_so locking...\");\n	"
             "		pthread_mutex_lock(&live_fn_mutex);\n		"
             "	lfnmutex_print(\"reload_so locked\");\n\n		"
             "	live_lib = 0; // hack: force skipping dlclose/1, the code may "
             "be still used...\n			"
             "load_so(new_so_name);\n			#ifndef "
             "_WIN32\n			unlink(new_so_name); // removing the "
             ".so file from the filesystem after dlopen-ing it is safe, since "
             "it will still be mapped in memory.\n			"
             "#else\n			_unlink(new_so_name);\n		"
             "	#endif\n			//if(0 == rename(new_so_name, "
             "\"%.*s\")){\n			//	"
             "load_so(\"%.*s\");\n			//}\n\n		"
             "	lfnmutex_print(\"reload_so unlocking...\");\n		"
             "	pthread_mutex_unlock(&live_fn_mutex);\n			"
             "lfnmutex_print(\"reload_so unlocked\");\n\n		"
             "}\n		time__sleep_ms(100);\n	}\n}\n",
             file.len, file.str, file.len, file.str, file_base.len,
             file_base.str, vexe.len, vexe.str, msvc.len, msvc.str, file.len,
             file.str, file.len, file.str, so_name.len, so_name.str,
             so_name.len, so_name.str));
  };

  if (v->pref->is_so) {

    CGen_genln(cgen, tos2((byte *)" int load_so(byteptr path) { return 0; }"));
  };
}
int main(int argc, char **argv) {
  init_consts();
  os__args = os__init_os_args(argc, argv);

  array_string args = env_vflags_and_os_args();

  if (_IN(string, tos2((byte *)"-v"), args) ||
      _IN(string, tos2((byte *)"--version"), args) ||
      _IN(string, tos2((byte *)"version"), args)) {

    printf("V %.*s\n", main__Version.len, main__Version.str);

    return 0;
  };

  if (_IN(string, tos2((byte *)"-h"), args) ||
      _IN(string, tos2((byte *)"--help"), args) ||
      _IN(string, tos2((byte *)"help"), args)) {

    println(main__HelpText);

    return 0;
  };

  if (_IN(string, tos2((byte *)"translate"), args)) {

    println(tos2((byte *)"Translating C to V will be available in V 0.3"));

    return 0;
  };

  if (_IN(string, tos2((byte *)"up"), args)) {

    update_v();

    return 0;
  };

  if (_IN(string, tos2((byte *)"get"), args)) {

    println(
        tos2((byte *)"use `v install` to install modules from vpm.vlang.io"));

    return 0;
  };

  if (_IN(string, tos2((byte *)"symlink"), args)) {

    create_symlink();

    return 0;
  };

  if (string_contains(array_string_join(args, tos2((byte *)" ")),
                      tos2((byte *)" test v"))) {

    test_v();

    return 0;
  };

  if (_IN(string, tos2((byte *)"install"), args)) {

    if (args.len < 3) {

      println(tos2((byte *)"usage: v install [module] [module] [...]"));

      return 0;
    };

    array_string names = array_slice(args, 2, args.len);

    string vexec = os__executable();

    string vroot = os__dir(vexec);

    string vget = _STR("%.*s/tools/vget", vroot.len, vroot.str);

    if (1) {

      os__chdir(string_add(vroot, tos2((byte *)"/tools")));

      Option_os__Result tmp6 = os__exec(_STR("%.*s -o %.*s vget.v", vexec.len,
                                             vexec.str, vget.len, vget.str));
      if (!tmp6.ok) {
        string err = tmp6.error;

        cerror(err);

        return 0;
      }
      os__Result vgetcompilation = *(os__Result *)tmp6.data;
      ;

      if (vgetcompilation.exit_code != 0) {

        cerror(vgetcompilation.output);

        return 0;
      };
    };

    Option_os__Result tmp7 =
        os__exec(string_add(_STR("%.*s ", vget.len, vget.str),
                            array_string_join(names, tos2((byte *)" "))));
    if (!tmp7.ok) {
      string err = tmp7.error;

      cerror(err);

      return 0;
    }
    os__Result vgetresult = *(os__Result *)tmp7.data;
    ;

    if (vgetresult.exit_code != 0) {

      cerror(vgetresult.output);

      return 0;
    };

    return 0;
  };

  if (_IN(string, tos2((byte *)"fmt"), args)) {

    string file = *(string *)array_last(args);

    if (!os__file_exists(file)) {

      printf("\"%.*s\" does not exist\n", file.len, file.str);

      v_exit(1);
    };

    if (!string_ends_with(file, tos2((byte *)".v"))) {

      println(tos2((byte *)"v fmt can only be used on .v files"));

      v_exit(1);
    };

    println(tos2((byte *)"vfmt is temporarily disabled"));

    return 0;
  };

  if (_IN(string, tos2((byte *)"get"), args)) {

    if (!os__file_exists(main__ModPath)) {

      os__mkdir(main__ModPath);
    };
  };

  V *v = new_v(args);

  if (v->pref->is_verbose) {

    println(array_string_str(args));
  };

  if (_IN(string, tos2((byte *)"doc"), args)) {

    v_exit(0);
  };

  if (_IN(string, tos2((byte *)"run"), args)) {

    V_compile(v);

    V_run_compiled_executable_and_exit(*v);
  };

  if (args.len < 2 ||
      (args.len == 2 &&
       string_eq((*(string *)array__get(args, 1)), tos2((byte *)"-"))) ||
      _IN(string, tos2((byte *)"runrepl"), args)) {

    run_repl();

    return 0;
  };

  V_compile(v);

  if (v->pref->is_test) {

    V_run_compiled_executable_and_exit(*v);
  };
}
void V_compile(V *v) {

  if (string_ne(os__user_os(), tos2((byte *)"windows")) &&
      v->os == main__OS_msvc) {

    cerror(_STR("Cannot build with msvc on %.*s", os__user_os().len,
                os__user_os().str));
  };

  CGen *cgen = v->cgen;

  CGen_genln(cgen, tos2((byte *)"// Generated by V"));

  array_string tmp13 = v->files;
  ;
  for (int i = 0; i < tmp13.len; i++) {
    string file = ((string *)tmp13.data)[i];
  };

  if (v->pref->is_verbose) {

    println(tos2((byte *)"all .v files before:"));

    println(array_string_str(v->files));
  };

  V_add_v_files_to_compile(v);

  if (v->pref->is_verbose) {

    println(tos2((byte *)"all .v files:"));

    println(array_string_str(v->files));
  };

  array_string tmp14 = v->files;
  ;
  for (int tmp15 = 0; tmp15 < tmp14.len; tmp15++) {
    string file = ((string *)tmp14.data)[tmp15];

    Parser p = V_new_parser(v, file);

    Parser_parse(&/* ? */ p, main__Pass_decl);
  };

  cgen->pass = main__Pass_main;

  if (v->pref->is_debug) {

    CGen_genln(cgen, tos2((byte *)"#define VDEBUG (1) "));
  };

  CGen_genln(cgen, main__CommonCHeaders);

  V_generate_hotcode_reloading_declarations(v);

  bool imports_json =
      array_string_contains(v->table->imports, tos2((byte *)"json"));

  if (v->os == main__OS_mac &&
      ((v->pref->build_mode == main__BuildMode_embed_vlib &&
        array_string_contains(v->table->imports, tos2((byte *)"ui"))) ||
       (v->pref->build_mode == main__BuildMode_build &&
        string_contains(v->dir, tos2((byte *)"/ui"))))) {

    CGen_genln(cgen, tos2((byte *)"id defaultFont = 0; // main.v"));
  };

  if (v->pref->build_mode == main__BuildMode_default_mode) {

    if (imports_json) {

      CGen_genln(cgen, tos2((byte *)"#include \"cJSON.h\""));
    };
  };

  if (v->pref->build_mode == main__BuildMode_embed_vlib ||
      v->pref->build_mode == main__BuildMode_default_mode) {

    CGen_genln(cgen, tos2((byte *)"int g_test_ok = 1; "));

    if (array_string_contains(v->table->imports, tos2((byte *)"json"))) {

      CGen_genln(
          cgen,
          tos2((byte *)"\n#define js_get(object, key) "
                       "cJSON_GetObjectItemCaseSensitive((object), (key))\n"));
    };
  };

  if (array_string_contains(os__args, tos2((byte *)"-debug_alloc"))) {

    CGen_genln(cgen, tos2((byte *)"#define DEBUG_ALLOC 1"));
  };

  CGen_genln(cgen, tos2((byte *)"/*================================== FNS "
                                "=================================*/"));

  CGen_genln(cgen, tos2((byte *)"this line will be replaced with definitions"));

  int defs_pos = cgen->lines.len - 1;

  array_string tmp19 = v->files;
  ;
  for (int tmp20 = 0; tmp20 < tmp19.len; tmp20++) {
    string file = ((string *)tmp19.data)[tmp20];

    Parser p = V_new_parser(v, file);

    Parser_parse(&/* ? */ p, main__Pass_main);

    if (!v->pref->nofmt && !string_contains(file, tos2((byte *)"/vlib/"))) {
    };
  };

  V_log(&/* ? */ *v, tos2((byte *)"Done parsing."));

  strings__Builder d = strings__new_builder(10000);

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->includes));

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->typedefs));

  strings__Builder_writeln(&/* ? */ d, V_c_type_definitions(v));

  strings__Builder_writeln(&/* ? */ d,
                           tos2((byte *)"\nstring _STR(const char*, ...);\n"));

  strings__Builder_writeln(
      &/* ? */ d, tos2((byte *)"\nstring _STR_TMP(const char*, ...);\n"));

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->fns));

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->consts));

  strings__Builder_writeln(&/* ? */ d,
                           array_string_join_lines(cgen->thread_args));

  if (v->pref->is_prof) {

    strings__Builder_writeln(&/* ? */ d, tos2((byte *)"; // Prof counters:"));

    strings__Builder_writeln(&/* ? */ d, V_prof_counters(v));
  };

  string dd = strings__Builder_str(d);

  array_set(&/*q*/ cgen->lines, defs_pos, &(string[]){dd});

  V_generate_main(v);

  V_generate_hotcode_reloading_code(v);

  CGen_save(cgen);

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos2((byte *)"flags="));

    array_CFlag tmp24 = V_get_os_cflags(*v);
    ;
    for (int tmp25 = 0; tmp25 < tmp24.len; tmp25++) {
      CFlag flag = ((CFlag *)tmp24.data)[tmp25];

      println(string_add(tos2((byte *)" * "), CFlag_format(&/* ? */ flag)));
    };
  };

  V_cc(v);
}
void V_generate_main(V *v) {

  CGen *cgen = v->cgen;

  if (v->pref->build_mode == main__BuildMode_default_mode ||
      v->pref->build_mode == main__BuildMode_embed_vlib) {

    string consts_init_body = array_string_join_lines(cgen->consts_init);

    array_string tmp28 = v->table->imports;
    ;
    for (int tmp29 = 0; tmp29 < tmp28.len; tmp29++) {
      string imp = ((string *)tmp28.data)[tmp29];

      if (string_eq(imp, tos2((byte *)"http"))) {

        consts_init_body = string_add(consts_init_body,
                                      tos2((byte *)"\n http__init_module();"));
      };
    };

    CGen_genln(cgen,
               _STR("void init_consts() {\n#ifdef _WIN32\n#ifndef "
                    "_BOOTSTRAP_NO_UNICODE_STREAM\n_setmode(_fileno(stdout), "
                    "_O_U8TEXT);\nSetConsoleMode(GetStdHandle(STD_OUTPUT_"
                    "HANDLE), ENABLE_PROCESSED_OUTPUT | 0x0004);\n// "
                    "ENABLE_VIRTUAL_TERMINAL_PROCESSING\n#endif\n#endif\ng_str_"
                    "buf=malloc(1000);\n%.*s\n}",
                    consts_init_body.len, consts_init_body.str));

    CGen_genln(
        cgen,
        tos2(
            (byte *)"\nstring _STR(const char *fmt, ...) {\n	va_list "
                    "argptr;\n	va_start(argptr, fmt);\n	size_t len = "
                    "vsnprintf(0, 0, fmt, argptr) + 1;\n	"
                    "va_end(argptr);\n	byte* buf = malloc(len);\n	"
                    "va_start(argptr, fmt);\n	vsprintf((char *)buf, fmt, "
                    "argptr);\n	va_end(argptr);\n#ifdef DEBUG_ALLOC\n	"
                    "puts(\"_STR:\");\n	puts(buf);\n#endif\n	return "
                    "tos2(buf);\n}\n\nstring _STR_TMP(const char *fmt, ...) "
                    "{\n	va_list argptr;\n	va_start(argptr, "
                    "fmt);\n	//size_t len = vsnprintf(0, 0, fmt, argptr) + "
                    "1;\n	va_end(argptr);\n	va_start(argptr, "
                    "fmt);\n	vsprintf((char *)g_str_buf, fmt, "
                    "argptr);\n	va_end(argptr);\n#ifdef DEBUG_ALLOC\n	"
                    "//puts(\"_STR_TMP:\");\n	"
                    "//puts(g_str_buf);\n#endif\n	return "
                    "tos2(g_str_buf);\n}\n\n"));
  };

  if (v->pref->build_mode != main__BuildMode_build) {

    if (!Table_main_exists(&/* ? */ *v->table) && !v->pref->is_test) {

      if (v->pref->is_script) {

        CGen_genln(cgen, tos2((byte *)"int main() { init_consts();"));

        CGen_genln(cgen, _STR("%.*s;", cgen->fn_main.len, cgen->fn_main.str));

        CGen_genln(cgen, tos2((byte *)"return 0; }"));

      } else {

        println(tos2(
            (byte *)"panic: function `main` is undeclared in the main module"));

        v_exit(1);
      };

    } else if (v->pref->is_test) {

      CGen_genln(cgen, tos2((byte *)"int main() { init_consts();"));

      map_Fn tmp30 = v->table->fns;
      array_string keys_tmp30 = map_keys(&tmp30);
      for (int l = 0; l < keys_tmp30.len; l++) {
        string _ = ((string *)keys_tmp30.data)[l];
        Fn f = {0};
        map_get(tmp30, _, &f);

        if (string_starts_with(f.name, tos2((byte *)"test_"))) {

          CGen_genln(cgen, _STR("%.*s();", f.name.len, f.name.str));
        };
      };

      CGen_genln(cgen, tos2((byte *)"return g_test_ok == 0; }"));
    };
  };
}
string final_target_out_name(string out_name) {

  string cmd = (string_starts_with(out_name, tos2((byte *)"/")))
                   ? (out_name)
                   : (string_add(tos2((byte *)"./"), out_name));

#ifdef _WIN32

  cmd = out_name;

  cmd = string_replace(cmd, tos2((byte *)"/"), tos2((byte *)"\\"));

  cmd = string_add(cmd, tos2((byte *)".exe"));

#endif
  ;

  return cmd;
}
void V_run_compiled_executable_and_exit(V v) {

  if (v.pref->is_verbose) {

    printf("============ running %.*s ============\n", v.out_name.len,
           v.out_name.str);
  };

  string cmd = string_add(
      string_add(tos2((byte *)"\""),
                 string_replace(final_target_out_name(v.out_name),
                                tos2((byte *)".exe"), tos2((byte *)""))),
      tos2((byte *)"\""));

  if (os__args.len > 3) {

    cmd = string_add(cmd, string_add(tos2((byte *)" "),
                                     array_string_join(array_right(os__args, 3),
                                                       tos2((byte *)" "))));
  };

  if (v.pref->is_test) {

    int ret = os__system(cmd);

    if (ret != 0) {

      v_exit(1);
    };
  };

  if (v.pref->is_run) {

    int ret = os__system(cmd);

    v_exit(ret >> 8);
  };

  v_exit(0);
}
array_string V_v_files_from_dir(V *v, string dir) {

  array_string res =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (!os__file_exists(dir)) {

    cerror(_STR("%.*s doesn\'t exist", dir.len, dir.str));

  } else if (!os__dir_exists(dir)) {

    cerror(_STR("%.*s isn\'t a directory", dir.len, dir.str));
  };

  array_string files = os__ls(dir);

  if (v->pref->is_verbose) {

    printf("v_files_from_dir (\"%.*s\")\n", dir.len, dir.str);
  };

  array_string_sort(&/* ? */ files);

  array_string tmp37 = files;
  ;
  for (int tmp38 = 0; tmp38 < tmp37.len; tmp38++) {
    string file = ((string *)tmp37.data)[tmp38];

    if (!string_ends_with(file, tos2((byte *)".v")) &&
        !string_ends_with(file, tos2((byte *)".vh"))) {

      continue;
    };

    if (string_ends_with(file, tos2((byte *)"_test.v"))) {

      continue;
    };

    if (string_ends_with(file, tos2((byte *)"_win.v")) &&
        (v->os != main__OS_windows && v->os != main__OS_msvc)) {

      continue;
    };

    if (string_ends_with(file, tos2((byte *)"_lin.v")) &&
        v->os != main__OS_linux) {

      continue;
    };

    if (string_ends_with(file, tos2((byte *)"_mac.v")) &&
        v->os != main__OS_mac) {

      continue;
    };

    if (string_ends_with(file, tos2((byte *)"_nix.v")) &&
        (v->os == main__OS_windows || v->os == main__OS_msvc)) {

      continue;
    };

    _PUSH(&res, (_STR("%.*s/%.*s", dir.len, dir.str, file.len, file.str)),
          tmp39, string);
  };

  return res;

  v_array_free(res); // close_scope free
}
void V_add_v_files_to_compile(V *v) {

  string dir = v->dir;

  V_log(&/* ? */ *v, _STR("add_v_files(%.*s)", dir.len, dir.str));

  array_string user_files =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  bool is_test_with_imports = string_ends_with(dir, tos2((byte *)"_test.v")) &&
                              (string_contains(dir, tos2((byte *)"/volt")) ||
                               string_contains(dir, tos2((byte *)"/c2volt")));

  if (is_test_with_imports) {

    _PUSH(&user_files, (dir), tmp43, string);

    int pos = string_last_index(dir, tos2((byte *)"/"));

    dir = string_add(string_left(dir, pos), tos2((byte *)"/"));
  };

  if (string_ends_with(dir, tos2((byte *)".v"))) {

    _PUSH(&user_files, (dir), tmp45, string);

    dir = string_all_before(dir, tos2((byte *)"/"));

  } else {

    array_string files = V_v_files_from_dir(&/* ? */ *v, dir);

    array_string tmp47 = files;
    ;
    for (int tmp48 = 0; tmp48 < tmp47.len; tmp48++) {
      string file = ((string *)tmp47.data)[tmp48];

      _PUSH(&user_files, (file), tmp49, string);
    };
  };

  if (user_files.len == 0) {

    println(tos2((byte *)"No input .v files"));

    v_exit(1);
  };

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos2((byte *)"user_files:"));

    println(array_string_str(user_files));
  };

  array_string tmp50 = v->files;
  ;
  for (int tmp51 = 0; tmp51 < tmp50.len; tmp51++) {
    string file = ((string *)tmp50.data)[tmp51];

    Parser p = V_new_parser(v, file);

    Parser_parse(&/* ? */ p, main__Pass_imports);
  };

  array_string tmp53 = user_files;
  ;
  for (int tmp54 = 0; tmp54 < tmp53.len; tmp54++) {
    string file = ((string *)tmp53.data)[tmp54];

    Parser p = V_new_parser(v, file);

    Parser_parse(&/* ? */ p, main__Pass_imports);
  };

  for (int i = 0; i < v->table->imports.len; i++) {

    string mod = (*(string *)array__get(v->table->imports, i));

    string import_path = V_find_module_path(&/* ? */ *v, mod);

    array_string vfiles = V_v_files_from_dir(&/* ? */ *v, import_path);

    if (vfiles.len == 0) {

      cerror(_STR("cannot import module %.*s (no .v files in \"%.*s\").",
                  mod.len, mod.str, import_path.len, import_path.str));
    };

    array_string tmp62 = vfiles;
    ;
    for (int tmp63 = 0; tmp63 < tmp62.len; tmp63++) {
      string file = ((string *)tmp62.data)[tmp63];

      Parser p = V_new_parser(v, file);

      Parser_parse(&/* ? */ p, main__Pass_imports);
    };
  };

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos2((byte *)"imports:"));

    println(array_string_str(v->table->imports));
  };

  DepGraph *dep_graph = new_dep_graph();

  DepGraph_from_import_tables(dep_graph, v->table->file_imports);

  DepGraph *deps_resolved = DepGraph_resolve(&/* ? */ *dep_graph);

  if (!deps_resolved->acyclic) {

    DepGraph_display(&/* ? */ *deps_resolved);

    cerror(tos2((byte *)"Import cycle detected."));
  };

  array_string tmp67 = DepGraph_imports(&/* ? */ *deps_resolved);
  ;
  for (int tmp68 = 0; tmp68 < tmp67.len; tmp68++) {
    string mod = ((string *)tmp67.data)[tmp68];

    if (string_eq(mod, v->mod)) {

      continue;
    };

    string mod_path = V_find_module_path(&/* ? */ *v, mod);

    array_string vfiles = V_v_files_from_dir(&/* ? */ *v, mod_path);

    array_string tmp71 = vfiles;
    ;
    for (int tmp72 = 0; tmp72 < tmp71.len; tmp72++) {
      string file = ((string *)tmp71.data)[tmp72];

      if (!(_IN(string, file, v->files))) {

        _PUSH(&v->files, (file), tmp73, string);
      };
    };
  };

  int j = 0;

  int len = -1;

  array_FileImportTable tmp76 = v->table->file_imports;
  ;
  for (int i = 0; i < tmp76.len; i++) {
    FileImportTable fit = ((FileImportTable *)tmp76.data)[i];

    if (_IN(string, fit.file_path, v->files) ||
        string_eq(fit.module_name, tos2((byte *)"builtin"))) {

      continue;
    };

    if (len == -1) {

      len = i;
    };

    j++;

    if (v->pref->build_mode == main__BuildMode_build && j >= len / 2) {

      break;
    };

    _PUSH(&v->files, (fit.file_path), tmp77, string);
  };

  v_array_free(user_files); // close_scope free
}
string get_arg(string joined_args, string arg, string def) {

  return get_all_after(joined_args, _STR("-%.*s", arg.len, arg.str), def);
}
string get_all_after(string joined_args, string arg, string def) {

  string key = _STR("%.*s ", arg.len, arg.str);

  int pos = string_index(joined_args, key);

  if (pos == -1) {

    return def;
  };

  pos += key.len;

  int space = string_index_after(joined_args, tos2((byte *)" "), pos);

  if (space == -1) {

    space = joined_args.len;
  };

  string res = string_substr(joined_args, pos, space);

  return res;
}
string V_module_path(V *v, string mod) {

  if (string_contains(mod, tos2((byte *)"."))) {

    return string_replace(mod, tos2((byte *)"."), tos2((byte *)"/"));
  };

  return mod;
}
void V_log(V *v, string s) {

  if (!v->pref->is_verbose) {

    return;
  };

  println(s);
}
V *new_v(array_string args) {

  string joined_args = array_string_join(args, tos2((byte *)" "));

  string target_os = get_arg(joined_args, tos2((byte *)"os"), tos2((byte *)""));

  string out_name =
      get_arg(joined_args, tos2((byte *)"o"), tos2((byte *)"a.out"));

  string dir = *(string *)array_last(args);

  if (array_string_contains(args, tos2((byte *)"run"))) {

    dir = get_all_after(joined_args, tos2((byte *)"run"), tos2((byte *)""));
  };

  if (string_ends_with(dir, tos2((byte *)"/"))) {

    dir = string_all_before_last(dir, tos2((byte *)"/"));
  };

  if (args.len < 2) {

    dir = tos2((byte *)"");
  };

  BuildMode build_mode = main__BuildMode_default_mode;

  string mod = tos2((byte *)"");

  if (string_contains(joined_args, tos2((byte *)"build module "))) {

    build_mode = main__BuildMode_build;

    mod = (string_contains(dir, tos2((byte *)"/")))
              ? (string_all_after(dir, tos2((byte *)"/")))
              : (dir);

    printf("Building module \"%.*s\" (dir=\"%.*s\")...\n", mod.len, mod.str,
           dir.len, dir.str);

    out_name = string_add(mod, tos2((byte *)".o"));

  } else if (!array_string_contains(args, tos2((byte *)"-embed_vlib"))) {

    build_mode = main__BuildMode_embed_vlib;
  };

  bool is_test = string_ends_with(dir, tos2((byte *)"_test.v"));

  bool is_script = string_ends_with(dir, tos2((byte *)".v"));

  if (is_script && !os__file_exists(dir)) {

    printf("`%.*s` does not exist\n", dir.len, dir.str);

    v_exit(1);
  };

  if (string_eq(out_name, tos2((byte *)"a.out")) &&
      string_ends_with(dir, tos2((byte *)".v"))) {

    out_name = string_left(dir, dir.len - 2);
  };

  if (string_eq(dir, tos2((byte *)".")) &&
      string_eq(out_name, tos2((byte *)"a.out"))) {

    string base = string_all_after(os__getwd(), tos2((byte *)"/"));

    out_name = string_trim_space(base);
  };

  OS _os = main__OS_mac;

  if (string_eq(target_os, tos2((byte *)""))) {

#ifdef __linux__

    _os = main__OS_linux;

#endif
    ;

#ifdef __APPLE__

    _os = main__OS_mac;

#endif
    ;

#ifdef _WIN32

    _os = main__OS_windows;

#endif
    ;

#ifdef __FreeBSD__

    _os = main__OS_freebsd;

#endif
    ;

#ifdef __OpenBSD__

    _os = main__OS_openbsd;

#endif
    ;

#ifdef __NetBSD__

    _os = main__OS_netbsd;

#endif
    ;

#ifdef __DragonFly__

    _os = main__OS_dragonfly;

#endif
    ;

  } else {

    if (string_eq(target_os, tos2((byte *)"linux"))) { /* case */

      _os = main__OS_linux;

    } else if (string_eq(target_os, tos2((byte *)"windows"))) { /* case */

      _os = main__OS_windows;

    } else if (string_eq(target_os, tos2((byte *)"mac"))) { /* case */

      _os = main__OS_mac;

    } else if (string_eq(target_os, tos2((byte *)"freebsd"))) { /* case */

      _os = main__OS_freebsd;

    } else if (string_eq(target_os, tos2((byte *)"openbsd"))) { /* case */

      _os = main__OS_openbsd;

    } else if (string_eq(target_os, tos2((byte *)"netbsd"))) { /* case */

      _os = main__OS_netbsd;

    } else if (string_eq(target_os, tos2((byte *)"dragonfly"))) { /* case */

      _os = main__OS_dragonfly;

    } else if (string_eq(target_os, tos2((byte *)"msvc"))) { /* case */

      _os = main__OS_msvc;
    };
  };

  array_string builtins = new_array_from_c_array(7, 7, sizeof(string),
                                                 (string[]){
                                                     tos2((byte *)"array.v"),
                                                     tos2((byte *)"string.v"),
                                                     tos2((byte *)"builtin.v"),
                                                     tos2((byte *)"int.v"),
                                                     tos2((byte *)"utf8.v"),
                                                     tos2((byte *)"map.v"),
                                                     tos2((byte *)"option.v"),
                                                 });

  string vroot = os__dir(os__executable());

  if (!os__dir_exists(vroot) ||
      !os__dir_exists(string_add(vroot, tos2((byte *)"/vlib/builtin")))) {

    println(tos2(
        (byte *)"vlib not found. It should be next to the V executable. "));

    println(tos2((byte *)"Go to https://vlang.io to install V."));

    v_exit(1);
  };

  string out_name_c =
      string_add(os__realpath(out_name), tos2((byte *)".tmp.c"));

  array_string files =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  array_string tmp96 = builtins;
  ;
  for (int tmp97 = 0; tmp97 < tmp96.len; tmp97++) {
    string builtin = ((string *)tmp96.data)[tmp97];

    string f = _STR("%.*s/vlib/builtin/%.*s", vroot.len, vroot.str, builtin.len,
                    builtin.str);

    if (build_mode == main__BuildMode_default_mode ||
        build_mode == main__BuildMode_build) {
    };

    _PUSH(&files, (f), tmp99, string);
  };

  string cflags = tos2((byte *)"");

  array_string tmp101 = args;
  ;
  for (int ci = 0; ci < tmp101.len; ci++) {
    string cv = ((string *)tmp101.data)[ci];

    if (string_eq(cv, tos2((byte *)"-cflags"))) {

      cflags =
          string_add(cflags, string_add((*(string *)array__get(args, ci + 1)),
                                        tos2((byte *)" ")));
    };
  };

  bool obfuscate = array_string_contains(args, tos2((byte *)"-obf"));

  Preferences *pref = (Preferences *)memdup(
      &(Preferences){
          .is_test = is_test,
          .is_script = is_script,
          .is_so = array_string_contains(args, tos2((byte *)"-shared")),
          .is_prod = array_string_contains(args, tos2((byte *)"-prod")),
          .is_verbose = array_string_contains(args, tos2((byte *)"-verbose")),
          .is_debuggable = array_string_contains(args, tos2((byte *)"-g")),
          .is_debug = array_string_contains(args, tos2((byte *)"-debug")) ||
                      array_string_contains(args, tos2((byte *)"-g")),
          .obfuscate = obfuscate,
          .is_prof = array_string_contains(args, tos2((byte *)"-prof")),
          .is_live = array_string_contains(args, tos2((byte *)"-live")),
          .sanitize = array_string_contains(args, tos2((byte *)"-sanitize")),
          .nofmt = array_string_contains(args, tos2((byte *)"-nofmt")),
          .show_c_cmd =
              array_string_contains(args, tos2((byte *)"-show_c_cmd")),
          .translated = array_string_contains(args, tos2((byte *)"translated")),
          .is_run = array_string_contains(args, tos2((byte *)"run")),
          .is_repl = array_string_contains(args, tos2((byte *)"-repl")),
          .build_mode = build_mode,
          .cflags = cflags,
          .ccompiler = find_c_compiler(),
          .no_auto_free = 0,
      },
      sizeof(Preferences));

  if (pref->is_verbose || pref->is_debug) {

    printf("C compiler=%.*s\n", pref->ccompiler.len, pref->ccompiler.str);
  };

  if (pref->is_so) {

    out_name_c = string_add(string_all_after(out_name, tos2((byte *)"/")),
                            tos2((byte *)"_shared_lib.c"));
  };

  return (V *)memdup(&(V){.os = _os,
                          .out_name = out_name,
                          .files = files,
                          .dir = dir,
                          .lang_dir = vroot,
                          .table = new_table(obfuscate),
                          .out_name_c = out_name_c,
                          .cgen = new_cgen(out_name_c),
                          .vroot = vroot,
                          .pref = pref,
                          .mod = mod},
                     sizeof(V));

  v_array_free(files);    // close_scope free
  v_array_free(builtins); // close_scope free
}
array_string env_vflags_and_os_args() {

  array_string args =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  string vflags = os__getenv(tos2((byte *)"VFLAGS"));

  if (string_ne(tos2((byte *)""), vflags)) {

    _PUSH(&args, ((*(string *)array__get(os__args, 0))), tmp108, string);

    _PUSH_MANY(&args, (string_split(vflags, tos2((byte *)" "))), tmp111,
               array_string);

    if (os__args.len > 1) {

      _PUSH_MANY(&args, (array_right(os__args, 1)), tmp112, array_string);
    };

  } else {

    _PUSH_MANY(&args, (os__args), tmp113, array_string);
  };

  return args;

  v_array_free(args); // close_scope free
}
void update_v() {

  println(tos2((byte *)"Updating V..."));

  string vroot = os__dir(os__executable());

  Option_os__Result tmp115 = os__exec(_STR(
      "git -C \"%.*s\" pull --rebase origin master", vroot.len, vroot.str));
  if (!tmp115.ok) {
    string err = tmp115.error;

    cerror(err);

    return;
  }
  os__Result s = *(os__Result *)tmp115.data;
  ;

  println(s.output);

#ifdef _WIN32

  os__mv(_STR("%.*s/v.exe", vroot.len, vroot.str),
         _STR("%.*s/v_old.exe", vroot.len, vroot.str));

  Option_os__Result tmp116 =
      os__exec(_STR("%.*s/make.bat", vroot.len, vroot.str));
  if (!tmp116.ok) {
    string err = tmp116.error;

    cerror(err);

    return;
  }
  os__Result s2 = *(os__Result *)tmp116.data;
  ;

  println(s2.output);

#else

  Option_os__Result tmp117 =
      os__exec(_STR("make -C \"%.*s\"", vroot.len, vroot.str));
  if (!tmp117.ok) {
    string err = tmp117.error;

    cerror(err);

    return;
  }
  os__Result s2 = *(os__Result *)tmp117.data;
  ;

  println(s2.output);

#endif
  ;
}
void test_v() {

  array_string args = env_vflags_and_os_args();

  string vexe = (*(string *)array__get(args, 0));

  string joined_args = array_string_join(
      array_right(env_vflags_and_os_args(), 1), tos2((byte *)" "));

  joined_args = string_left(
      joined_args, string_last_index(joined_args, tos2((byte *)"test")));

  printf("%.*s\n", joined_args.len, joined_args.str);

  bool failed = 0;

  array_string test_files =
      os__walk_ext(tos2((byte *)"."), tos2((byte *)"_test.v"));

  array_string tmp125 = test_files;
  ;
  for (int tmp126 = 0; tmp126 < tmp125.len; tmp126++) {
    string dot_relative_file = ((string *)tmp125.data)[tmp126];

    string relative_file =
        string_replace(dot_relative_file, tos2((byte *)"./"), tos2((byte *)""));

    string file = os__realpath(relative_file);

    string tmpcfilepath = string_replace(file, tos2((byte *)"_test.v"),
                                         tos2((byte *)"_test.tmp.c"));

    print(string_add(relative_file, tos2((byte *)" ")));

    string cmd = _STR("\"%.*s\" %.*s -debug \"%.*s\"", vexe.len, vexe.str,
                      joined_args.len, joined_args.str, file.len, file.str);

    if (string_eq(os__user_os(), tos2((byte *)"windows"))) {

      cmd = _STR("\"%.*s\"", cmd.len, cmd.str);
    };

    Option_os__Result tmp131 = os__exec(cmd);
    if (!tmp131.ok) {
      string err = tmp131.error;

      failed = 1;

      println(tos2((byte *)"FAIL"));

      continue;
    }
    os__Result r = *(os__Result *)tmp131.data;
    ;

    if (r.exit_code != 0) {

      printf("FAIL `%.*s` (\n%.*s\n)\n", file.len, file.str, r.output.len,
             r.output.str);

      failed = 1;

    } else {

      println(tos2((byte *)"OK"));
    };

    os__rm(tmpcfilepath);
  };

  println(tos2((byte *)"\nBuilding examples..."));

  array_string examples =
      os__walk_ext(tos2((byte *)"examples"), tos2((byte *)".v"));

  array_string tmp133 = examples;
  ;
  for (int tmp134 = 0; tmp134 < tmp133.len; tmp134++) {
    string relative_file = ((string *)tmp133.data)[tmp134];

    string file = os__realpath(relative_file);

    string tmpcfilepath =
        string_replace(file, tos2((byte *)".v"), tos2((byte *)".tmp.c"));

    print(string_add(relative_file, tos2((byte *)" ")));

    string cmd = _STR("\"%.*s\" %.*s -debug \"%.*s\"", vexe.len, vexe.str,
                      joined_args.len, joined_args.str, file.len, file.str);

    if (string_eq(os__user_os(), tos2((byte *)"windows"))) {

      cmd = _STR("\"%.*s\"", cmd.len, cmd.str);
    };

    Option_os__Result tmp138 = os__exec(cmd);
    if (!tmp138.ok) {
      string err = tmp138.error;

      failed = 1;

      println(tos2((byte *)"FAIL"));

      continue;
    }
    os__Result r = *(os__Result *)tmp138.data;
    ;

    if (r.exit_code != 0) {

      printf("FAIL `%.*s` (\n%.*s\n)\n", file.len, file.str, r.output.len,
             r.output.str);

      failed = 1;

    } else {

      println(tos2((byte *)"OK"));
    };

    os__rm(tmpcfilepath);
  };

  if (failed) {

    v_exit(1);
  };
}
void create_symlink() {

  string vexe = os__executable();

  string link_path = tos2((byte *)"/usr/local/bin/v");

  int ret = os__system(_STR("ln -sf %.*s %.*s", vexe.len, vexe.str,
                            link_path.len, link_path.str));

  if (ret == 0) {

    printf("symlink \"%.*s\" has been created\n", link_path.len, link_path.str);

  } else {

    println(string_add(_STR("failed to create symlink \"%.*s\", ",
                            link_path.len, link_path.str),
                       tos2((byte *)"make sure you run with sudo")));
  };
}
void cerror(string s) {

  printf("V error: %.*s\n", s.len, s.str);

  os__flush_stdout();

  v_exit(1);
}
void DepGraph_from_import_tables(DepGraph *graph,
                                 array_FileImportTable import_tables) {

  array_FileImportTable tmp1 = import_tables;
  ;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    FileImportTable fit = ((FileImportTable *)tmp1.data)[tmp2];

    array_string deps =
        new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

    map_string tmp4 = fit.imports;
    array_string keys_tmp4 = map_keys(&tmp4);
    for (int l = 0; l < keys_tmp4.len; l++) {
      string _ = ((string *)keys_tmp4.data)[l];
      string m = {0};
      map_get(tmp4, _, &m);

      _PUSH(&deps, (m), tmp5, string);
    };

    DepGraph_add(graph, fit.module_name, deps);

    v_array_free(deps); // close_scope free
  };
}
array_string DepGraph_imports(DepGraph *graph) {

  array_string mods =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  array_DepGraphNode tmp7 = graph->nodes;
  ;
  for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
    DepGraphNode node = ((DepGraphNode *)tmp7.data)[tmp8];

    if (string_eq(node.name, tos2((byte *)"main"))) {

      continue;
    };

    _PUSH(&mods, (node.name), tmp9, string);
  };

  return mods;

  v_array_free(mods); // close_scope free
}
string V_find_module_path(V *v, string mod) {

  string mod_path = V_module_path(&/* ? */ *v, mod);

  string import_path =
      string_add(os__getwd(), _STR("/%.*s", mod_path.len, mod_path.str));

  if (!os__dir_exists(import_path)) {

    import_path = _STR("%.*s/vlib/%.*s", v->lang_dir.len, v->lang_dir.str,
                       mod_path.len, mod_path.str);
  };

  if (!os__dir_exists(import_path)) {

    import_path = _STR("%.*s/%.*s", main__ModPath.len, main__ModPath.str,
                       mod_path.len, mod_path.str);

    if (!os__dir_exists(import_path)) {

      cerror(_STR("module \"%.*s\" not found", mod.len, mod.str));
    };
  };

  return import_path;
}
Option_string find_windows_kit_internal(RegKey key, array_string versions) {

#ifdef _WIN32

  array_string tmp1 = versions;
  ;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    string version = ((string *)tmp1.data)[tmp2];

    int required_bytes = 0;

    void *result = RegQueryValueExW(key, string_to_wide(version), 0, 0, 0,
                                    &/*vvar*/ required_bytes);

    int length = required_bytes / 2;

    if (result != 0) {

      continue;
    };

    int alloc_length = (required_bytes + 2);

    u16 *value = ((u16 *)(v_malloc(alloc_length)));

    if (!value) {

      continue;
    };

    void *result2 = RegQueryValueExW(key, string_to_wide(version), 0, 0, value,
                                     &/*vvar*/ alloc_length);

    if (result2 != 0) {

      continue;
    };

    if ((value[/*ptr*/ length - 1] /*ru16 1*/ != ((u16)(0)))) {

      value[/*ptr*/ length] /*ru16 1*/ = ((u16)(0));
    };

    string tmp9 = OPTION_CAST(string)(string_from_wide(value));
    return opt_ok(&tmp9, sizeof(string));
  };

#endif
  ;

  return v_error(tos2((byte *)"windows kit not found"));
}
Option_WindowsKit find_windows_kit_root() {

#ifdef _WIN32

  RegKey root_key = ((RegKey)(0));

  void *rc =
      RegOpenKeyExA(main__HKEY_LOCAL_MACHINE,
                    "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots", 0,
                    main__KEY_QUERY_VALUE | main__KEY_WOW64_32KEY |
                        main__KEY_ENUMERATE_SUB_KEYS,
                    &/*vvar*/ root_key);

  if (rc != 0) {

    Option tmp12 = v_error(tos2((byte *)"Unable to open root key"));
    { RegCloseKey(root_key); }
    return tmp12;
    ;
  };

  Option_string tmp13 = find_windows_kit_internal(
      root_key, new_array_from_c_array(2, 2, sizeof(string),
                                       (string[]){tos2((byte *)"KitsRoot10"),
                                                  tos2((byte *)"KitsRoot81")}));
  if (!tmp13.ok) {
    string err = tmp13.error;

    Option tmp14 = v_error(tos2((byte *)"Unable to find a windows kit"));
    { RegCloseKey(root_key); }
    return tmp14;
    ;
  }
  string kit_root = *(string *)tmp13.data;
  ;

  string kit_lib = string_add(kit_root, tos2((byte *)"Lib"));

  array_string files = os__ls(kit_lib);

  string highest_path = tos2((byte *)"");

  int highest_int = 0;

  array_string tmp19 = files;
  ;
  for (int tmp20 = 0; tmp20 < tmp19.len; tmp20++) {
    string f = ((string *)tmp19.data)[tmp20];

    string no_dot = string_replace(f, tos2((byte *)"."), tos2((byte *)""));

    int v_int = v_string_int(no_dot);

    if (v_int > highest_int) {

      highest_int = v_int;

      highest_path = f;
    };
  };

  string kit_lib_highest =
      string_add(kit_lib, _STR("\\%.*s", highest_path.len, highest_path.str));

  string kit_include_highest = string_replace(
      kit_lib_highest, tos2((byte *)"Lib"), tos2((byte *)"Include"));

  WindowsKit tmp25 = OPTION_CAST(WindowsKit)((WindowsKit){
      .um_lib_path = string_add(kit_lib_highest, tos2((byte *)"\\um\\x64")),
      .ucrt_lib_path = string_add(kit_lib_highest, tos2((byte *)"\\ucrt\\x64")),
      .um_include_path = string_add(kit_include_highest, tos2((byte *)"\\um")),
      .ucrt_include_path =
          string_add(kit_include_highest, tos2((byte *)"\\ucrt")),
      .shared_include_path =
          string_add(kit_include_highest, tos2((byte *)"\\shared"))});
  return opt_ok(&tmp25, sizeof(WindowsKit));

  {

    RegCloseKey(root_key);
  }
#endif
  ;

  return v_error(
      tos2((byte *)"Host OS does not support funding a windows kit"));
}
Option_VsInstallation find_vs() {

#ifndef _WIN32

  return v_error(
      tos2((byte *)"Host OS does not support finding a Vs installation"));

#endif
  ;

  Option_os__Result tmp26 = os__exec(tos2(
      (byte *)"\"\"%ProgramFiles(x86)%\\Microsoft Visual "
              "Studio\\Installer\\vswhere.exe\" -latest -products * -requires "
              "Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property "
              "installationPath\""));
  if (!tmp26.ok) {
    string err = tmp26.error;

    return v_error(err);
  }
  os__Result res = *(os__Result *)tmp26.data;
  ;

  Option_string tmp27 = os__read_file(
      _STR("%.*s\\VC\\Auxiliary\\Build\\Microsoft.VCToolsVersion.default.txt",
           res.output.len, res.output.str));
  if (!tmp27.ok) {
    string err = tmp27.error;

    println(tos2((byte *)"Unable to find msvc version"));

    return v_error(tos2((byte *)"Unable to find vs installation"));
  }
  string version = *(string *)tmp27.data;
  ;

  string v = (string_ends_with(version, tos2((byte *)"\n")))
                 ? (string_left(version, version.len - 2))
                 : (version);

  string lib_path = _STR("%.*s\\VC\\Tools\\MSVC\\%.*s\\lib\\x64",
                         res.output.len, res.output.str, v.len, v.str);

  string include_path = _STR("%.*s\\VC\\Tools\\MSVC\\%.*s\\include",
                             res.output.len, res.output.str, v.len, v.str);

  if (os__file_exists(
          _STR("%.*s\\vcruntime.lib", lib_path.len, lib_path.str))) {

    string p = _STR("%.*s\\VC\\Tools\\MSVC\\%.*s\\bin\\Hostx64\\x64",
                    res.output.len, res.output.str, v.len, v.str);

    VsInstallation tmp32 = OPTION_CAST(VsInstallation)((VsInstallation){
        .exe_path = p, .lib_path = lib_path, .include_path = include_path});
    return opt_ok(&tmp32, sizeof(VsInstallation));
  };

  printf(
      "Unable to find vs installation (attempted to use lib path \"%.*s\")\n",
      lib_path.len, lib_path.str);

  return v_error(tos2((byte *)"Unable to find vs exe folder"));
}
Option_MsvcResult find_msvc() {

#ifdef _WIN32

  Option_WindowsKit tmp33 = find_windows_kit_root();
  if (!tmp33.ok) {
    string err = tmp33.error;

    return v_error(tos2((byte *)"Unable to find windows sdk"));
  }
  WindowsKit wk = *(WindowsKit *)tmp33.data;
  ;

  Option_VsInstallation tmp34 = find_vs();
  if (!tmp34.ok) {
    string err = tmp34.error;

    return v_error(tos2((byte *)"Unable to find visual studio"));
  }
  VsInstallation vs = *(VsInstallation *)tmp34.data;
  ;

  MsvcResult tmp35 = OPTION_CAST(MsvcResult)((MsvcResult){
      .full_cl_exe_path = os__realpath(string_add(
          string_add(vs.exe_path, os__PathSeparator), tos2((byte *)"cl.exe"))),
      .exe_path = vs.exe_path,
      .um_lib_path = wk.um_lib_path,
      .ucrt_lib_path = wk.ucrt_lib_path,
      .vs_lib_path = vs.lib_path,
      .um_include_path = wk.um_include_path,
      .ucrt_include_path = wk.ucrt_include_path,
      .vs_include_path = vs.include_path,
      .shared_include_path = wk.shared_include_path});
  return opt_ok(&tmp35, sizeof(MsvcResult));

#else

  cerror(tos2((byte *)"Cannot find msvc on this OS"));

  return v_error(tos2((byte *)"msvc not found"));

#endif
  ;
}
void V_cc_msvc(V *v) {

  Option_MsvcResult tmp36 = find_msvc();
  if (!tmp36.ok) {
    string err = tmp36.error;

    if (!v->pref->is_debug && string_ne(v->out_name_c, tos2((byte *)"v.c")) &&
        string_ne(v->out_name_c, tos2((byte *)"v_macos.c"))) {

      os__rm(v->out_name_c);
    };

    cerror(tos2((byte *)"Cannot find MSVC on this OS."));

    return;
  }
  MsvcResult r = *(MsvcResult *)tmp36.data;
  ;

  string out_name_obj =
      os__realpath(string_add(v->out_name_c, tos2((byte *)".obj")));

  array_string a = new_array_from_c_array(
      6, 6, sizeof(string),
      (string[]){tos2((byte *)"-w"), tos2((byte *)"/we4013"),
                 tos2((byte *)"/volatile:ms"), tos2((byte *)"/D_UNICODE"),
                 tos2((byte *)"/DUNICODE"),
                 _STR("/Fo\"%.*s\"", out_name_obj.len, out_name_obj.str)});

  if (v->pref->is_prod) {

    _PUSH(&a, (tos2((byte *)"/O2")), tmp39, string);

    _PUSH(&a, (tos2((byte *)"/MD")), tmp40, string);

  } else {

    _PUSH(&a, (tos2((byte *)"/Z7")), tmp41, string);

    _PUSH(&a, (tos2((byte *)"/MDd")), tmp42, string);
  };

  if (v->pref->is_so) {

    if (!string_ends_with(v->out_name, tos2((byte *)".dll"))) {

      v->out_name = string_add(v->out_name, tos2((byte *)".dll"));
    };

    _PUSH(&a, (tos2((byte *)"/LD")), tmp43, string);

  } else if (!string_ends_with(v->out_name, tos2((byte *)".exe"))) {

    v->out_name = string_add(v->out_name, tos2((byte *)".exe"));
  };

  v->out_name = os__realpath(v->out_name);

  array_string alibs =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (v->pref->build_mode == main__BuildMode_build) {

  } else if (v->pref->build_mode == main__BuildMode_embed_vlib) {

  } else if (v->pref->build_mode == main__BuildMode_default_mode) {

    string b = os__realpath(
        _STR("%.*s/vlib/builtin.obj", main__ModPath.len, main__ModPath.str));

    _PUSH(&alibs, (_STR("\"%.*s\"", b.len, b.str)), tmp46, string);

    if (!os__file_exists(b)) {

      println(tos2((byte *)"`builtin.obj` not found"));

      v_exit(1);
    };

    array_string tmp47 = v->table->imports;
    ;
    for (int tmp48 = 0; tmp48 < tmp47.len; tmp48++) {
      string imp = ((string *)tmp47.data)[tmp48];

      if (string_eq(imp, tos2((byte *)"webview"))) {

        continue;
      };

      _PUSH(&alibs,
            (string_add(string_add(tos2((byte *)"\""),
                                   os__realpath(_STR(
                                       "%.*s/vlib/%.*s.obj", main__ModPath.len,
                                       main__ModPath.str, imp.len, imp.str))),
                        tos2((byte *)"\""))),
            tmp49, string);
    };
  };

  if (v->pref->sanitize) {

    println(tos2((byte *)"Sanitize not supported on msvc."));
  };

  _PUSH(&a,
        (string_add(string_add(tos2((byte *)"\""), os__realpath(v->out_name_c)),
                    tos2((byte *)"\""))),
        tmp50, string);

  array_string real_libs =
      new_array_from_c_array(13, 13, sizeof(string),
                             (string[]){
                                 tos2((byte *)"kernel32.lib"),
                                 tos2((byte *)"user32.lib"),
                                 tos2((byte *)"gdi32.lib"),
                                 tos2((byte *)"winspool.lib"),
                                 tos2((byte *)"comdlg32.lib"),
                                 tos2((byte *)"advapi32.lib"),
                                 tos2((byte *)"shell32.lib"),
                                 tos2((byte *)"ole32.lib"),
                                 tos2((byte *)"oleaut32.lib"),
                                 tos2((byte *)"uuid.lib"),
                                 tos2((byte *)"odbc32.lib"),
                                 tos2((byte *)"odbccp32.lib"),
                                 tos2((byte *)"vcruntime.lib"),
                             });

  array_string inc_paths =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  {}

  array_string lib_paths =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  {}

  array_string other_flags =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  {}

  array_CFlag tmp55 = V_get_os_cflags(*v);
  ;
  for (int tmp56 = 0; tmp56 < tmp55.len; tmp56++) {
    CFlag flag = ((CFlag *)tmp55.data)[tmp56];

    if (string_eq(flag.name, tos2((byte *)"-l"))) {

      if (string_ends_with(flag.value, tos2((byte *)".dll"))) {

        cerror(_STR("MSVC cannot link against a dll (`#flag -l %.*s`)",
                    flag.value.len, flag.value.str));
      };

      string lib_lib = string_add(flag.value, tos2((byte *)".lib"));

      _PUSH(&real_libs, (lib_lib), tmp58, string);

    } else if (string_eq(flag.name, tos2((byte *)"-I"))) {

      _PUSH(&inc_paths, (CFlag_format(&/* ? */ flag)), tmp59, string);

    } else if (string_eq(flag.name, tos2((byte *)"-L"))) {

      _PUSH(&lib_paths, (flag.value), tmp60, string);

      _PUSH(&lib_paths,
            (string_add(string_add(flag.value, os__PathSeparator),
                        tos2((byte *)"msvc"))),
            tmp61, string);

    } else if (string_ends_with(flag.value, tos2((byte *)".o"))) {

      _PUSH(&other_flags, (_STR("\"%.*sbj\"", flag.value.len, flag.value.str)),
            tmp62, string);

    } else {

      _PUSH(&other_flags, (flag.value), tmp63, string);
    };
  };

  _PUSH(&a,
        (_STR("-I \"%.*s\"", r.ucrt_include_path.len, r.ucrt_include_path.str)),
        tmp64, string);

  _PUSH(&a, (_STR("-I \"%.*s\"", r.vs_include_path.len, r.vs_include_path.str)),
        tmp65, string);

  _PUSH(&a, (_STR("-I \"%.*s\"", r.um_include_path.len, r.um_include_path.str)),
        tmp66, string);

  _PUSH(&a,
        (_STR("-I \"%.*s\"", r.shared_include_path.len,
              r.shared_include_path.str)),
        tmp67, string);

  _PUSH_MANY(&a, (inc_paths), tmp68, array_string);

  _PUSH_MANY(&a, (other_flags), tmp69, array_string);

  _PUSH(&a, (array_string_join(real_libs, tos2((byte *)" "))), tmp70, string);

  _PUSH(&a, (tos2((byte *)"/link")), tmp71, string);

  _PUSH(&a, (tos2((byte *)"/NOLOGO")), tmp72, string);

  _PUSH(&a, (_STR("/OUT:\"%.*s\"", v->out_name.len, v->out_name.str)), tmp73,
        string);

  _PUSH(&a,
        (_STR("/LIBPATH:\"%.*s\"", r.ucrt_lib_path.len, r.ucrt_lib_path.str)),
        tmp74, string);

  _PUSH(&a, (_STR("/LIBPATH:\"%.*s\"", r.um_lib_path.len, r.um_lib_path.str)),
        tmp75, string);

  _PUSH(&a, (_STR("/LIBPATH:\"%.*s\"", r.vs_lib_path.len, r.vs_lib_path.str)),
        tmp76, string);

  _PUSH(&a, (tos2((byte *)"/INCREMENTAL:NO")), tmp77, string);

  array_string tmp78 = lib_paths;
  ;
  for (int tmp79 = 0; tmp79 < tmp78.len; tmp79++) {
    string l = ((string *)tmp78.data)[tmp79];

    _PUSH(&a,
          (string_add(string_add(tos2((byte *)"/LIBPATH:\""), os__realpath(l)),
                      tos2((byte *)"\""))),
          tmp80, string);
  };

  if (!v->pref->is_prod) {

    _PUSH(&a, (tos2((byte *)"/DEBUG:FULL")), tmp81, string);

  } else {

    _PUSH(&a, (tos2((byte *)"/DEBUG:NONE")), tmp82, string);
  };

  string args = array_string_join(a, tos2((byte *)" "));

  string cmd = _STR("\"\"%.*s\" %.*s\"", r.full_cl_exe_path.len,
                    r.full_cl_exe_path.str, args.len, args.str);

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    println(tos2((byte *)"\n========== cl cmd line:"));

    println(cmd);

    println(tos2((byte *)"==========\n"));
  };

  Option_os__Result tmp85 = os__exec(cmd);
  if (!tmp85.ok) {
    string err = tmp85.error;

    println(err);

    cerror(tos2((byte *)"msvc error"));

    return;
  }
  os__Result res = *(os__Result *)tmp85.data;
  ;

  if (res.exit_code != 0) {

    cerror(res.output);
  };

  if (!v->pref->is_debug && string_ne(v->out_name_c, tos2((byte *)"v.c")) &&
      string_ne(v->out_name_c, tos2((byte *)"v_macos.c"))) {

    os__rm(v->out_name_c);
  };

  os__rm(out_name_obj);

  v_array_free(other_flags); // close_scope free
  v_array_free(lib_paths);   // close_scope free
  v_array_free(inc_paths);   // close_scope free
  v_array_free(real_libs);   // close_scope free
  v_array_free(alibs);       // close_scope free
  v_array_free(a);           // close_scope free
}
void build_thirdparty_obj_file_with_msvc(string path) {

  Option_MsvcResult tmp86 = find_msvc();
  if (!tmp86.ok) {
    string err = tmp86.error;

    println(tos2((byte *)"Could not find visual studio"));

    return;
  }
  MsvcResult msvc = *(MsvcResult *)tmp86.data;
  ;

  string obj_path = _STR("%.*sbj", path.len, path.str);

  obj_path = os__realpath(obj_path);

  if (os__file_exists(obj_path)) {

    printf("%.*s already build.\n", obj_path.len, obj_path.str);

    return;
  };

  printf("%.*s not found, building it (with msvc)...\n", obj_path.len,
         obj_path.str);

  string parent = os__dir(obj_path);

  array_string files = os__ls(parent);

  string cfiles = tos2((byte *)"");

  array_string tmp91 = files;
  ;
  for (int tmp92 = 0; tmp92 < tmp91.len; tmp92++) {
    string file = ((string *)tmp91.data)[tmp92];

    if (string_ends_with(file, tos2((byte *)".c"))) {

      cfiles = string_add(
          cfiles,
          string_add(
              string_add(tos2((byte *)"\""),
                         os__realpath(string_add(
                             string_add(parent, os__PathSeparator), file))),
              tos2((byte *)"\" ")));
    };
  };

  string include_string =
      _STR("-I \"%.*s\" -I \"%.*s\" -I \"%.*s\" -I \"%.*s\"",
           msvc.ucrt_include_path.len, msvc.ucrt_include_path.str,
           msvc.vs_include_path.len, msvc.vs_include_path.str,
           msvc.um_include_path.len, msvc.um_include_path.str,
           msvc.shared_include_path.len, msvc.shared_include_path.str);

  string cmd = _STR("\"\"%.*s\" /volatile:ms /Z7 %.*s /c %.*s /Fo\"%.*s\" "
                    "/D_UNICODE /DUNICODE\"",
                    msvc.full_cl_exe_path.len, msvc.full_cl_exe_path.str,
                    include_string.len, include_string.str, cfiles.len,
                    cfiles.str, obj_path.len, obj_path.str);

  printf("thirdparty cmd line: %.*s\n", cmd.len, cmd.str);

  Option_os__Result tmp95 = os__exec(cmd);
  if (!tmp95.ok) {
    string err = tmp95.error;

    cerror(err);

    return;
  }
  os__Result res = *(os__Result *)tmp95.data;
  ;

  println(res.output);
}
Parser V_new_parser(V *v, string path) {

  string path_pcguard = tos2((byte *)"");

  string path_platform = tos2((byte *)".v");

  array_string tmp3 = new_array_from_c_array(
      4, 4, sizeof(string),
      (string[]){tos2((byte *)"_lin.v"), tos2((byte *)"_mac.v"),
                 tos2((byte *)"_win.v"), tos2((byte *)"_nix.v")});
  ;
  for (int tmp4 = 0; tmp4 < tmp3.len; tmp4++) {
    string path_ending = ((string *)tmp3.data)[tmp4];

    if (string_ends_with(path, path_ending)) {

      path_platform = path_ending;

      path_pcguard = platform_postfix_to_ifdefguard(path_ending);

      break;
    };
  };

  Parser p = (Parser){
      .v = v,
      .file_path = path,
      .file_name = string_all_after(path, tos2((byte *)"/")),
      .file_platform = path_platform,
      .file_pcguard = path_pcguard,
      .scanner = new_scanner(path),
      .table = v->table,
      .import_table = new_file_import_table(path),
      .cur_fn = main__EmptyFn,
      .cgen = v->cgen,
      .is_script = (v->pref->is_script && string_eq(path, v->dir)),
      .pref = v->pref,
      .os = v->os,
      .vroot = v->vroot,
      .building_v = !v->pref->is_repl &&
                    (string_contains(path, tos2((byte *)"compiler/")) ||
                     string_contains(path, tos2((byte *)"v/vlib"))),
      .token_idx = 0,
      .lit = tos((byte *)"", 0),
      .mod = tos((byte *)"", 0),
      .inside_const = 0,
      .has_immutable_field = 0,
      .assigned_type = tos((byte *)"", 0),
      .expected_type = tos((byte *)"", 0),
      .tmp_cnt = 0,
      .builtin_mod = 0,
      .vh_lines = new_array(0, 1, sizeof(string)),
      .inside_if_expr = 0,
      .inside_unwrapping_match_statement = 0,
      .is_struct_init = 0,
      .if_expr_cnt = 0,
      .for_expr_cnt = 0,
      .ptr_cast = 0,
      .calling_c = 0,
      .returns = 0,
      .is_c_struct_init = 0,
      .is_empty_c_struct_init = 0,
      .is_c_fn_call = 0,
      .can_chash = 0,
      .attr = tos((byte *)"", 0),
      .v_script = 0,
      .var_decl_name = tos((byte *)"", 0),
      .is_alloc = 0,
      .cur_gen_type = tos((byte *)"", 0),
      .is_vweb = 0,
      .is_sql = 0,
      .sql_i = 0,
      .sql_params = new_array(0, 1, sizeof(string)),
      .sql_types = new_array(0, 1, sizeof(string))};

  v->cgen->line_directives = v->pref->is_debuggable;

  v->cgen->file = path;

  Parser_next(&/* ? */ p);

  return p;
}
void Parser_set_current_fn(Parser *p, Fn *f) {

  p->cur_fn = f;

  p->scanner->fn_name =
      _STR("%.*s.%.*s", f->mod.len, f->mod.str, f->name.len, f->name.str);
}
void Parser_next(Parser *p) {

  p->prev_tok2 = p->prev_tok;

  p->prev_tok = p->tok;

  p->scanner->prev_tok = p->tok;

  ScanRes res = Scanner_scan(p->scanner);

  p->tok = res.tok;

  p->lit = res.lit;
}
void Parser_log(Parser *p, string s) {}
void Parser_parse(Parser *p, Pass pass) {

  p->pass = pass;

  Parser_log(&/* ? */ *p, _STR("\nparse() run=%d file=%.*s tok=%.*s", p->pass,
                               p->file_name.len, p->file_name.str,
                               Parser_strtok(&/* ? */ *p).len,
                               Parser_strtok(&/* ? */ *p).str));

  if (p->is_script || p->pref->is_test) {

    p->mod = tos2((byte *)"main");

    if (p->tok == main__Token_key_module) {

      Parser_next(p);

      Parser_fgen(p, tos2((byte *)"module "));

      p->mod = Parser_check_name(p);
    };

  } else {

    Parser_check(p, main__Token_key_module);

    Parser_fspace(p);

    p->mod = Parser_check_name(p);
  };

  Parser_fgenln(p, tos2((byte *)"\n"));

  p->builtin_mod = string_eq(p->mod, tos2((byte *)"builtin"));

  p->can_chash = string_eq(p->mod, tos2((byte *)"ui")) ||
                 string_eq(p->mod, tos2((byte *)"darwin"));

  string fq_mod =
      Table_qualify_module(&/* ? */ *p->table, p->mod, p->file_path);

  p->import_table->module_name = fq_mod;

  Table_register_module(p->table, fq_mod);

  p->mod = string_replace(fq_mod, tos2((byte *)"."), tos2((byte *)"_dot_"));

  if (p->pass == main__Pass_imports) {

    while (p->tok == main__Token_key_import &&
           Parser_peek(p) != main__Token_key_const) {

      Parser_imports(p);
    };

    if (array_string_contains(p->table->imports, tos2((byte *)"builtin"))) {

      Parser_error(p, tos2((byte *)"module `builtin` cannot be imported"));
    };

    _PUSH(&p->table->file_imports, (*p->import_table), tmp8, FileImportTable);

    return;
  };

  while (1) {

    if ((p->tok == main__Token_key_import)) { /* case */

      if (Parser_peek(p) == main__Token_key_const) {

        Parser_const_decl(p);

      } else {

        Parser_imports(p);

        if (p->tok != main__Token_key_import) {

          Parser_fgenln(p, tos2((byte *)""));
        };
      };

    } else if ((p->tok == main__Token_key_enum)) { /* case */

      Parser_next(p);

      if (p->tok == main__Token_name) {

        Parser_fgen(p, tos2((byte *)"enum "));

        string name = Parser_check_name(p);

        Parser_fgen(p, tos2((byte *)" "));

        Parser_enum_decl(p, name);

      } else if (p->pref->translated) {

        Parser_enum_decl(p, tos2((byte *)"int"));

      } else {

        Parser_check(p, main__Token_name);
      };

    } else if ((p->tok == main__Token_key_pub)) { /* case */

      if (Parser_peek(p) == main__Token_func) {

        Parser_fn_decl(p);

      } else if (Parser_peek(p) == main__Token_key_struct) {

        Parser_error(p,
                     tos2((byte *)"structs can\'t be declared public *yet*"));

      } else {

        Parser_error(p, tos2((byte *)"wrong pub keyword usage"));
      };

    } else if ((p->tok == main__Token_func)) { /* case */

      Parser_fn_decl(p);

    } else if ((p->tok == main__Token_key_type)) { /* case */

      Parser_type_decl(p);

    } else if ((p->tok == main__Token_lsbr)) { /* case */

      Parser_attribute(p);

    } else if ((p->tok == main__Token_key_struct) ||
               (p->tok == main__Token_key_interface) ||
               (p->tok == main__Token_key_union) ||
               (p->tok == main__Token_lsbr)) { /* case */

      Parser_struct_decl(p);

    } else if ((p->tok == main__Token_key_const)) { /* case */

      Parser_const_decl(p);

    } else if ((p->tok == main__Token_hash)) { /* case */

      Parser_chash(p);

    } else if ((p->tok == main__Token_dollar)) { /* case */

      Parser_comp_time(p);

    } else if ((p->tok == main__Token_key_global)) { /* case */

      if (!p->pref->translated && !p->pref->is_live && !p->builtin_mod &&
          !p->building_v &&
          !string_contains(os__getwd(), tos2((byte *)"/volt"))) {

        Parser_error(
            p, tos2((byte *)"__global is only allowed in translated code"));
      };

      Parser_next(p);

      string name = Parser_check_name(p);

      string typ = Parser_get_type(p);

      Parser_register_global(p, name, typ);

      string g = Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ);

      if (p->tok == main__Token_assign) {

        Parser_next(p);

        g = string_add(g, tos2((byte *)" = "));

        CGen_start_tmp(p->cgen);

        Parser_bool_expression(p);

        g = string_add(g, CGen_end_tmp(p->cgen));
      };

      g = string_add(g, tos2((byte *)"; // global"));

      _PUSH(&p->cgen->consts, (g), tmp13, string);

    } else if ((p->tok == main__Token_eof)) { /* case */

      Parser_log(&/* ? */ *p, tos2((byte *)"end of parse()"));

      if (p->is_script && !p->pref->is_test) {

        Parser_set_current_fn(p, main__MainFn);

        Parser_check_unused_variables(p);
      };

      if (0 && !Parser_first_pass(&/* ? */ *p) &&
          Parser_fileis(&/* ? */ *p, tos2((byte *)"main.v"))) {

        Option_os__File tmp14 = os__create(tos2((byte *)"/var/tmp/fmt.v"));
        if (!tmp14.ok) {
          string err = tmp14.error;

          cerror(tos2((byte *)"failed to create fmt.v"));

          return;
        }
        os__File out = *(os__File *)tmp14.data;
        ;

        os__File_writeln(out, strings__Builder_str(p->scanner->fmt_out));

        os__File_close(out);
      };

      return;

    } else { // default:

      if (p->is_script && !p->pref->is_test) {

        if (Parser_first_pass(&/* ? */ *p)) {

          if (string_eq(p->cur_fn->name, tos2((byte *)""))) {

            Parser_set_current_fn(p, main__MainFn);
          };

          return;
        };

        if (string_eq(p->cur_fn->name, tos2((byte *)""))) {

          Parser_set_current_fn(p, main__MainFn);

          if (p->pref->is_repl) {

            Fn_clear_vars(p->cur_fn);
          };
        };

        int start = p->cgen->lines.len;

        Parser_statement(p, 1);

        if (string_ne((*(string *)array__get(p->cgen->lines, start - 1)),
                      tos2((byte *)"")) &&
            string_ne(p->cgen->fn_main, tos2((byte *)""))) {

          start--;
        };

        Parser_genln(p, tos2((byte *)""));

        int end = p->cgen->lines.len;

        array_string lines = array_slice(p->cgen->lines, start, end);

        p->cgen->fn_main = string_add(
            p->cgen->fn_main, array_string_join(lines, tos2((byte *)"\n")));

        CGen_resetln(p->cgen, tos2((byte *)""));

        for (int i = start; i < end; i++) {

          array_set(&/*q*/ p->cgen->lines, i, &(string[]){tos2((byte *)"")});
        };

      } else {

        Parser_error(p, _STR("unexpected token `%.*s`",
                             Parser_strtok(&/* ? */ *p).len,
                             Parser_strtok(&/* ? */ *p).str));
      };
    };
  };
}
void Parser_imports(Parser *p) {

  Parser_check(p, main__Token_key_import);

  if (p->tok == main__Token_lpar) {

    Parser_check(p, main__Token_lpar);

    while (p->tok != main__Token_rpar && p->tok != main__Token_eof) {

      Parser_import_statement(p);
    };

    Parser_check(p, main__Token_rpar);

    return;
  };

  Parser_import_statement(p);
}
void Parser_import_statement(Parser *p) {

  if (p->tok != main__Token_name) {

    Parser_error(p, tos2((byte *)"bad import format"));
  };

  if (Parser_peek(p) == main__Token_number &&
      string_at(p->scanner->text, p->scanner->pos + 1) == '.') {

    Parser_error(p, tos2((byte *)"bad import format. module/submodule names "
                                 "cannot begin with a number."));
  };

  string mod = string_trim_space(Parser_check_name(p));

  string mod_alias = mod;

  int depth = 1;

  while (p->tok == main__Token_dot) {

    Parser_check(p, main__Token_dot);

    string submodule = Parser_check_name(p);

    mod_alias = submodule;

    mod = string_add(mod, string_add(tos2((byte *)"."), submodule));

    depth++;

    if (depth > main__MaxModuleDepth) {

      Parser_error(p, _STR("module depth of %d exceeded: %.*s",
                           main__MaxModuleDepth, mod.len, mod.str));
    };
  };

  if (p->tok == main__Token_key_as && Parser_peek(p) == main__Token_name) {

    Parser_check(p, main__Token_key_as);

    mod_alias = Parser_check_name(p);
  };

  FileImportTable_register_alias(p->import_table, mod_alias, mod);

  if (array_string_contains(p->table->imports, mod)) {

    return;
  };

  Parser_log(&/* ? */ *p, _STR("adding import %.*s", mod.len, mod.str));

  _PUSH(&p->table->imports, (mod), tmp27, string);

  Table_register_module(p->table, mod);

  Parser_fgenln(p, string_add(tos2((byte *)" "), mod));
}
void Parser_const_decl(Parser *p) {

  if (p->tok == main__Token_key_import) {

    Parser_error(
        p, string_add(
               tos2((byte *)"`import const` was removed from the language, "),
               tos2((byte *)"use `foo(C.CONST_NAME)` instead")));
  };

  p->inside_const = 1;

  Parser_check(p, main__Token_key_const);

  Parser_fspace(p);

  Parser_check(p, main__Token_lpar);

  Parser_fgenln(p, tos2((byte *)""));

  Parser_fmt_inc(p);

  while (p->tok == main__Token_name) {

    string name = Parser_check_name(p);

    name = Parser_prepend_mod(&/* ? */ *p, name);

    Parser_check_space(p, main__Token_assign);

    string typ = Parser_expression(p);

    if (Parser_first_pass(&/* ? */ *p) &&
        Table_known_const(&/* ? */ *p->table, name)) {

      Parser_error(p, _STR("redefinition of `%.*s`", name.len, name.str));
    };

    Table_register_const(p->table, name, typ, p->mod);

    if (p->pass == main__Pass_main) {

      if (is_compile_time_const(p->cgen->cur_line)) {

        _PUSH(&p->cgen->consts,
              (_STR("#define %.*s %.*s", name.len, name.str,
                    p->cgen->cur_line.len, p->cgen->cur_line.str)),
              tmp30, string);

        CGen_resetln(p->cgen, tos2((byte *)""));

        Parser_fgenln(p, tos2((byte *)""));

        continue;
      };

      if (string_starts_with(typ, tos2((byte *)"["))) {

        _PUSH(&p->cgen->consts,
              (string_add(
                  Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ),
                  _STR(" = %.*s;", p->cgen->cur_line.len,
                       p->cgen->cur_line.str))),
              tmp31, string);

      } else {

        _PUSH(&p->cgen->consts,
              (string_add(
                  Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ),
                  tos2((byte *)";"))),
              tmp32, string);

        _PUSH(&p->cgen->consts_init,
              (_STR("%.*s = %.*s;", name.len, name.str, p->cgen->cur_line.len,
                    p->cgen->cur_line.str)),
              tmp33, string);
      };

      CGen_resetln(p->cgen, tos2((byte *)""));
    };

    Parser_fgenln(p, tos2((byte *)""));
  };

  Parser_fmt_dec(p);

  Parser_check(p, main__Token_rpar);

  Parser_fgenln(p, tos2((byte *)"\n"));

  p->inside_const = 0;
}
void Parser_type_decl(Parser *p) {

  Parser_check(p, main__Token_key_type);

  string name = Parser_check_name(p);

  if (p->tok == main__Token_key_struct) {

    Parser_error(p, _STR("use `struct %.*s {` instead of `type %.*s struct {`",
                         name.len, name.str, name.len, name.str));
  };

  Type parent = Parser_get_type2(p);

  string nt_pair =
      Table_cgen_name_type_pair(&/* ? */ *p->table, name, parent.name);

  string _struct = (parent.cat != main__TypeCategory_array &&
                    parent.cat != main__TypeCategory_func &&
                    !Table_known_type(&/* ? */ *p->table, parent.name))
                       ? (tos2((byte *)"struct"))
                       : (tos2((byte *)""));

  Parser_gen_typedef(
      p, _STR("typedef %.*s %.*s; //type alias name=\"%.*s\" parent=`%.*s`",
              _struct.len, _struct.str, nt_pair.len, nt_pair.str, name.len,
              name.str, parent.name.len, parent.name.str));

  Parser_register_type_with_parent(p, name, parent.name);
}
Fn *Parser_interface_method(Parser *p, string field_name, string receiver) {

  Fn *method =
      (Fn *)memdup(&(Fn){.name = field_name,
                         .is_interface = 1,
                         .is_method = 1,
                         .receiver_typ = receiver,
                         .mod = tos((byte *)"", 0),
                         .local_vars = new_array(0, 1, sizeof(Var)),
                         .var_idx = 0,
                         .args = new_array(0, 1, sizeof(Var)),
                         .scope_level = 0,
                         .typ = tos((byte *)"", 0),
                         .is_c = 0,
                         .is_public = 0,
                         .returns_error = 0,
                         .is_decl = 0,
                         .defer_text = new_array(0, 1, sizeof(string))},
                   sizeof(Fn));

  Parser_log(&/* ? */ *p, _STR("is interface. field=%.*s run=%d",
                               field_name.len, field_name.str, p->pass));

  Parser_fn_args(p, method);

  if (Scanner_has_gone_over_line_end(*p->scanner)) {

    method->typ = tos2((byte *)"void");

  } else {

    method->typ = Parser_get_type(p);

    Parser_fspace(p);

    Parser_fgenln(p, tos2((byte *)""));
  };

  return method;
}
TypeCategory key_to_type_cat(Token tok) {

  if ((tok == main__Token_key_interface)) { /* case */

    return main__TypeCategory_interface_;

  } else if ((tok == main__Token_key_struct)) { /* case */

    return main__TypeCategory_struct_;

  } else if ((tok == main__Token_key_union)) { /* case */

    return main__TypeCategory_union_;
  };

  cerror(_STR("Unknown token: %d", tok));

  return main__TypeCategory_builtin;
}
void Parser_struct_decl(Parser *p) {

  bool is_interface = p->tok == main__Token_key_interface;

  bool is_union = p->tok == main__Token_key_union;

  bool is_struct = p->tok == main__Token_key_struct;

  TypeCategory cat = key_to_type_cat(p->tok);

  Parser_fgen(p, string_add(Token_str(p->tok), tos2((byte *)" ")));

  Parser_next(p);

  string name = Parser_check_name(p);

  if (string_contains(name, tos2((byte *)"_")) && !p->pref->translated) {

    Parser_error(p, tos2((byte *)"type names cannot contain `_`"));
  };

  if (is_interface && !string_ends_with(name, tos2((byte *)"er"))) {

    Parser_error(p, tos2((byte *)"interface names temporarily have to end with "
                                 "`er` (e.g. `Speaker`, `Reader`)"));
  };

  bool is_c = string_eq(name, tos2((byte *)"C")) && p->tok == main__Token_dot;

  if (is_c) {

    Parser_check(p, main__Token_dot);

    name = Parser_check_name(p);

    cat = main__TypeCategory_c_struct;

    if (string_eq(p->attr, tos2((byte *)"typedef"))) {

      cat = main__TypeCategory_c_typedef;
    };
  };

  if (!is_c && !good_type_name(name)) {

    Parser_error(p, tos2((byte *)"bad struct name, e.g. use `HttpRequest` "
                                 "instead of `HTTPRequest`"));
  };

  if (!is_c && !p->builtin_mod && string_ne(p->mod, tos2((byte *)"main"))) {

    name = Parser_prepend_mod(&/* ? */ *p, name);
  };

  Type typ = Table_find_type(&/* ? */ *p->table, name);

  if (p->pass == main__Pass_decl &&
      Table_known_type_fast(&/* ? */ *p->table,
                            &/*112 EXP:"Type*" GOT:"Type" */ typ)) {

    Parser_error(p, _STR("`%.*s` redeclared", name.len, name.str));
  };

  if (!is_c) {

    string kind =
        (is_union) ? (tos2((byte *)"union")) : (tos2((byte *)"struct"));

    Parser_gen_typedef(p, _STR("typedef %.*s %.*s %.*s;", kind.len, kind.str,
                               name.len, name.str, name.len, name.str));
  };

  bool is_ph = 0;

  if (typ.is_placeholder) {

    is_ph = 1;

    typ.name = name;

    typ.mod = p->mod;

    typ.is_c = is_c;

    typ.is_placeholder = 0;

    typ.cat = cat;

    Table_rewrite_type(p->table, typ);

  } else {

    typ = (Type){.name = name,
                 .mod = p->mod,
                 .is_c = is_c,
                 .cat = cat,
                 .fields = new_array(0, 1, sizeof(Var)),
                 .methods = new_array(0, 1, sizeof(Fn)),
                 .parent = tos((byte *)"", 0),
                 .enum_vals = new_array(0, 1, sizeof(string)),
                 .gen_types = new_array(0, 1, sizeof(string)),
                 .is_placeholder = 0,
                 .gen_str = 0};
  };

  if (is_c && is_struct && p->tok != main__Token_lcbr) {

    Table_register_type2(p->table, typ);

    return;
  };

  Parser_fgen(p, tos2((byte *)" "));

  Parser_check(p, main__Token_lcbr);

  bool is_pub = 0;

  bool is_mut = 0;

  array_string names =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  if (!is_ph && Parser_first_pass(&/* ? */ *p)) {

    Table_register_type2(p->table, typ);
  };

  bool did_gen_something = 0;

  while (p->tok != main__Token_rcbr) {

    if (p->tok == main__Token_key_pub) {

      if (is_pub) {

        Parser_error(p, tos2((byte *)"structs can only have one `pub:`, all "
                                     "public fields have to be grouped"));
      };

      is_pub = 1;

      Parser_fmt_dec(p);

      Parser_check(p, main__Token_key_pub);

      if (p->tok != main__Token_key_mut) {

        Parser_check(p, main__Token_colon);
      };

      Parser_fmt_inc(p);

      Parser_fgenln(p, tos2((byte *)""));
    };

    if (p->tok == main__Token_key_mut) {

      if (is_mut) {

        Parser_error(p,
                     tos2((byte *)"structs can only have one `mut:`, all "
                                  "private key_mut fields have to be grouped"));
      };

      is_mut = 1;

      Parser_fmt_dec(p);

      Parser_check(p, main__Token_key_mut);

      if (p->tok != main__Token_key_mut) {

        Parser_check(p, main__Token_colon);
      };

      Parser_fmt_inc(p);

      Parser_fgenln(p, tos2((byte *)""));
    };

    string field_name =
        (string_ne(name, tos2((byte *)"Option")))
            ? (Table_var_cgen_name(p->table, Parser_check_name(p)))
            : (Parser_check_name(p));

    if (_IN(string, field_name, names)) {

      Parser_error(
          p, _STR("duplicate field `%.*s`", field_name.len, field_name.str));
    };

    if (!is_c && string_ne(p->mod, tos2((byte *)"os")) &&
        contains_capital(field_name)) {

      Parser_error(p, tos2((byte *)"struct fields cannot contain uppercase "
                                   "letters, use snake_case instead"));
    };

    _PUSH(&names, (field_name), tmp53, string);

    if (is_interface) {

      Fn *f = Parser_interface_method(p, field_name, name);

      if (Parser_first_pass(&/* ? */ *p)) {

        Table_add_method(p->table, typ.name, *f);
      };

      continue;
    };

    AccessMod access_mod =
        (is_pub) ? (main__AccessMod_public) : (main__AccessMod_private);

    Parser_fgen(p, tos2((byte *)" "));

    string field_type = Parser_get_type(p);

    bool is_atomic = p->tok == main__Token_key_atomic;

    if (is_atomic) {

      Parser_next(p);
    };

    string attr = tos2((byte *)"");

    if (p->tok == main__Token_lsbr) {

      Parser_next(p);

      attr = Parser_check_name(p);

      if (p->tok == main__Token_colon) {

        Parser_check(p, main__Token_colon);

        attr = string_add(attr,
                          string_add(tos2((byte *)":"), Parser_check_name(p)));
      };

      Parser_check(p, main__Token_rsbr);
    };

    if (string_eq(attr, tos2((byte *)"raw")) &&
        string_ne(field_type, tos2((byte *)"string"))) {

      Parser_error(p, _STR("struct field with attribute \"raw\" should be of "
                           "type \"string\" but got \"%.*s\"",
                           field_type.len, field_type.str));
    };

    did_gen_something = 1;

    if (Parser_first_pass(&/* ? */ *p)) {

      Table_add_field(p->table, typ.name, field_name, field_type, is_mut, attr,
                      access_mod);
    };

    Parser_fgenln(p, tos2((byte *)""));
  };

  Parser_check(p, main__Token_rcbr);

  if (!is_c) {

    if (!did_gen_something) {

      if (Parser_first_pass(&/* ? */ *p)) {

        Table_add_field(p->table, typ.name, tos2((byte *)""),
                        tos2((byte *)"EMPTY_STRUCT_DECLARATION"), 0,
                        tos2((byte *)""), main__AccessMod_private);
      };
    };
  };

  Parser_fgenln(p, tos2((byte *)"\n"));

  v_array_free(names); // close_scope free
}
void Parser_enum_decl(Parser *p, string _enum_name) {

  string enum_name = _enum_name;

  if (!p->builtin_mod && string_ne(p->mod, tos2((byte *)"main"))) {

    enum_name = Parser_prepend_mod(&/* ? */ *p, enum_name);
  };

  if (string_ne(enum_name, tos2((byte *)"int")) &&
      !Parser_first_pass(&/* ? */ *p)) {

    _PUSH(&p->cgen->typedefs,
          (_STR("typedef int %.*s;", enum_name.len, enum_name.str)), tmp60,
          string);
  };

  Parser_check(p, main__Token_lcbr);

  int val = 0;

  array_string fields =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  while (p->tok == main__Token_name) {

    string field = Parser_check_name(p);

    _PUSH(&fields, (field), tmp64, string);

    Parser_fgenln(p, tos2((byte *)""));

    string name = _STR("%.*s__%.*s_%.*s", p->mod.len, p->mod.str, enum_name.len,
                       enum_name.str, field.len, field.str);

    if (p->pass == main__Pass_main) {

      _PUSH(&p->cgen->consts,
            (_STR("#define %.*s %d", name.len, name.str, val)), tmp66, string);
    };

    if (p->tok == main__Token_comma) {

      Parser_next(p);
    };

    Table_register_const(p->table, name, enum_name, p->mod);

    val++;
  };

  Table_register_type2(p->table,
                       (Type){.name = enum_name,
                              .mod = p->mod,
                              .parent = tos2((byte *)"int"),
                              .cat = main__TypeCategory_enum_,
                              .enum_vals = array_clone(fields),
                              .fields = new_array(0, 1, sizeof(Var)),
                              .methods = new_array(0, 1, sizeof(Fn)),
                              .is_c = 0,
                              .gen_types = new_array(0, 1, sizeof(string)),
                              .is_placeholder = 0,
                              .gen_str = 0});

  Parser_check(p, main__Token_rcbr);

  Parser_fgenln(p, tos2((byte *)"\n"));

  v_array_free(fields); // close_scope free
}
string Parser_check_name(Parser *p) {

  string name = p->lit;

  Parser_check(p, main__Token_name);

  return name;
}
string Parser_check_string(Parser *p) {

  string s = p->lit;

  Parser_check(p, main__Token_str);

  return s;
}
string Parser_strtok(Parser *p) {

  if (p->tok == main__Token_name) {

    return p->lit;
  };

  if (p->tok == main__Token_str) {

    return _STR("\"%.*s\"", p->lit.len, p->lit.str);
  };

  string res = Token_str(p->tok);

  if (string_eq(res, tos2((byte *)""))) {

    int n = ((int)(p->tok));

    return int_str(n);
  };

  return res;
}
void Parser_check_space(Parser *p, Token expected) {

  Parser_fspace(p);

  Parser_check(p, expected);

  Parser_fspace(p);
}
void Parser_check(Parser *p, Token expected) {

  if (p->tok != expected) {

    println(tos2((byte *)"check()"));

    string s = _STR("expected `%.*s` but got `%.*s`", Token_str(expected).len,
                    Token_str(expected).str, Parser_strtok(&/* ? */ *p).len,
                    Parser_strtok(&/* ? */ *p).str);

    Parser_next(p);

    printf("next token = `%.*s`\n", Parser_strtok(&/* ? */ *p).len,
           Parser_strtok(&/* ? */ *p).str);

    print_backtrace();

    Parser_error(p, s);
  };

  if (expected == main__Token_rcbr) {

    Parser_fmt_dec(p);
  };

  Parser_fgen(p, Parser_strtok(&/* ? */ *p));

  if (expected == main__Token_lcbr &&
      p->scanner->pos + 1 < p->scanner->text.len &&
      string_at(p->scanner->text, p->scanner->pos + 1) != '}') {

    Parser_fgenln(p, tos2((byte *)""));

    Parser_fmt_inc(p);
  };

  Parser_next(p);

  if (string_ne(p->scanner->line_comment, tos2((byte *)""))) {
  };
}
void Parser_warn(Parser *p, string s) {

  printf("warning: %.*s:%d: %.*s\n", p->scanner->file_path.len,
         p->scanner->file_path.str, p->scanner->line_nr + 1, s.len, s.str);
}
void Parser_error(Parser *p, string s) {

  if (p->pref->is_debug) {

    os__write_file(tos2((byte *)"fns.txt"),
                   Table_debug_fns(&/* ? */ *p->table));
  };

  if (p->pref->is_verbose || p->pref->is_debug) {

    printf("pass=%d fn=`%.*s`\n\n", p->pass, p->cur_fn->name.len,
           p->cur_fn->name.str);
  };

  CGen_save(p->cgen);

  string cur_path = os__getwd();

  if (!p->pref->is_repl && !p->pref->is_test &&
      (string_contains(p->file_path, tos2((byte *)"v/compiler")) ||
       string_contains(cur_path, tos2((byte *)"v/compiler")))) {

    println(tos2((byte *)"\n========================="));

    println(tos2((byte *)"It looks like you are building V. It is being "
                         "frequently updated every day."));

    println(tos2((byte *)"If you didn\'t modify V\'s code, most likely there "
                         "was a change that "));

    println(tos2((byte *)"lead to this error."));

    println(tos2((byte *)"\nRun `v up`, that will most likely fix it."));

    println(
        tos2((byte *)"\nIf this doesn\'t help, please create a GitHub issue."));

    println(tos2((byte *)"=========================\n"));
  };

  if (p->pref->is_debug) {

    print_backtrace();
  };

  Scanner_error(
      &/* ? */ *p->scanner,
      string_replace(string_replace(string_replace(s, tos2((byte *)"array_"),
                                                   tos2((byte *)"[]")),
                                    tos2((byte *)"__"), tos2((byte *)".")),
                     tos2((byte *)"Option_"), tos2((byte *)"?")));
}
bool Parser_first_pass(Parser *p) { return p->pass == main__Pass_decl; }
string Parser_get_type(Parser *p) {

  bool mul = 0;

  int nr_muls = 0;

  string typ = tos2((byte *)"");

  if (p->tok == main__Token_func) {

    Fn f = (Fn){.name = tos2((byte *)"_"),
                .mod = p->mod,
                .local_vars = new_array(0, 1, sizeof(Var)),
                .var_idx = 0,
                .args = new_array(0, 1, sizeof(Var)),
                .is_interface = 0,
                .scope_level = 0,
                .typ = tos((byte *)"", 0),
                .is_c = 0,
                .receiver_typ = tos((byte *)"", 0),
                .is_public = 0,
                .is_method = 0,
                .returns_error = 0,
                .is_decl = 0,
                .defer_text = new_array(0, 1, sizeof(string))};

    Parser_next(p);

    int line_nr = p->scanner->line_nr;

    Parser_fn_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

    if (p->scanner->line_nr == line_nr) {

      if (p->tok == main__Token_name) {

        f.typ = Parser_get_type(p);

      } else {

        f.typ = tos2((byte *)"void");
      };

    } else {

      f.typ = tos2((byte *)"void");
    };

    Type fn_typ = (Type){.name = Fn_typ_str(f),
                         .mod = p->mod,
                         .func = f,
                         .fields = new_array(0, 1, sizeof(Var)),
                         .methods = new_array(0, 1, sizeof(Fn)),
                         .parent = tos((byte *)"", 0),
                         .is_c = 0,
                         .enum_vals = new_array(0, 1, sizeof(string)),
                         .gen_types = new_array(0, 1, sizeof(string)),
                         .is_placeholder = 0,
                         .gen_str = 0};

    Table_register_type2(p->table, fn_typ);

    return Fn_typ_str(f);
  };

  bool is_arr = 0;

  bool is_arr2 = 0;

  bool is_question = p->tok == main__Token_question;

  if (is_question) {

    Parser_check(p, main__Token_question);
  };

  if (p->tok == main__Token_lsbr) {

    Parser_check(p, main__Token_lsbr);

    if (p->tok == main__Token_number) {

      typ = _STR("[%.*s]", p->lit.len, p->lit.str);

      Parser_next(p);

    } else {

      is_arr = 1;
    };

    Parser_check(p, main__Token_rsbr);

    if (p->tok == main__Token_lsbr) {

      Parser_next(p);

      if (p->tok == main__Token_number) {

        typ = string_add(typ, _STR("[%.*s]", p->lit.len, p->lit.str));

        Parser_check(p, main__Token_number);

      } else {

        is_arr2 = 1;
      };

      Parser_check(p, main__Token_rsbr);
    };
  };

  if (!p->builtin_mod && p->tok == main__Token_name &&
      string_eq(p->lit, tos2((byte *)"map"))) {

    Parser_next(p);

    Parser_check(p, main__Token_lsbr);

    string key_type = Parser_check_name(p);

    if (string_ne(key_type, tos2((byte *)"string"))) {

      Parser_error(p, tos2((byte *)"maps only support string keys for now"));
    };

    Parser_check(p, main__Token_rsbr);

    string val_type = Parser_get_type(p);

    typ = _STR("map_%.*s", val_type.len, val_type.str);

    Parser_register_map(p, typ);

    return typ;
  };

  while (p->tok == main__Token_mul) {

    if (Parser_first_pass(&/* ? */ *p)) {

      Parser_warn(p, tos2((byte *)"use `&Foo` instead of `*Foo`"));
    };

    mul = 1;

    nr_muls++;

    Parser_check(p, main__Token_mul);
  };

  if (p->tok == main__Token_amp) {

    mul = 1;

    nr_muls++;

    Parser_check(p, main__Token_amp);
  };

  typ = string_add(typ, p->lit);

  if (!p->is_struct_init) {

    Parser_fgen(p, p->lit);
  };

  if (string_eq(p->lit, tos2((byte *)"C")) &&
      Parser_peek(p) == main__Token_dot) {

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    typ = p->lit;

  } else {

    if (Parser_peek(p) == main__Token_dot) {

      if (!p->builtin_mod &&
          FileImportTable_known_alias(&/* ? */ *p->import_table, typ)) {

        string mod =
            FileImportTable_resolve_alias(&/* ? */ *p->import_table, typ);

        if (string_contains(mod, tos2((byte *)"."))) {

          typ = string_replace(mod, tos2((byte *)"."), tos2((byte *)"_dot_"));
        };
      };

      Parser_next(p);

      Parser_check(p, main__Token_dot);

      typ = string_add(typ, _STR("__%.*s", p->lit.len, p->lit.str));
    };

    Type t = Table_find_type(&/* ? */ *p->table, typ);

    if (string_eq(typ, tos2((byte *)"V"))) {
    };

    if (string_eq(t.name, tos2((byte *)"")) && !p->builtin_mod) {

      if (!string_contains(typ, tos2((byte *)"array_")) &&
          string_ne(p->mod, tos2((byte *)"main")) &&
          !string_contains(typ, tos2((byte *)"__")) &&
          !string_starts_with(typ, tos2((byte *)"["))) {

        typ = Parser_prepend_mod(&/* ? */ *p, typ);
      };

      t = Table_find_type(&/* ? */ *p->table, typ);

      if (string_eq(t.name, tos2((byte *)"")) && !p->pref->translated &&
          !Parser_first_pass(&/* ? */ *p) &&
          !string_starts_with(typ, tos2((byte *)"["))) {

        println(tos2((byte *)"get_type() bad type"));

        Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
      };
    };
  };

  if (string_eq(typ, tos2((byte *)"void"))) {

    Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
  };

  if (mul) {

    typ = string_add(typ, strings__repeat('*', nr_muls));
  };

  if (is_arr2) {

    typ = _STR("array_array_%.*s", typ.len, typ.str);

    Parser_register_array(p, typ);

  } else if (is_arr) {

    typ = _STR("array_%.*s", typ.len, typ.str);

    Parser_register_array(p, typ);
  };

  Parser_next(p);

  if (p->tok == main__Token_question || is_question) {

    typ = _STR("Option_%.*s", typ.len, typ.str);

    Table_register_type_with_parent(p->table, typ, tos2((byte *)"Option"));

    if (p->tok == main__Token_question) {

      Parser_next(p);
    };
  };

  if (string_eq(typ, tos2((byte *)"byteptr"))) {

    return tos2((byte *)"byte*");
  };

  if (string_eq(typ, tos2((byte *)"voidptr"))) {

    return tos2((byte *)"void*");
  };

  if (string_last_index(typ, tos2((byte *)"__")) >
      string_index(typ, tos2((byte *)"__"))) {

    Parser_error(p, _STR("2 __ in gettype(): typ=\"%.*s\"", typ.len, typ.str));
  };

  return typ;
}
void Parser_print_tok(Parser *p) {

  if (p->tok == main__Token_name) {

    println(p->lit);

    return;
  };

  if (p->tok == main__Token_str) {

    printf("\"%.*s\"\n", p->lit.len, p->lit.str);

    return;
  };

  println(Token_str(p->tok));
}
string Parser_statements(Parser *p) {

  Parser_log(&/* ? */ *p, tos2((byte *)"statements()"));

  string typ = Parser_statements_no_rcbr(p);

  if (!p->inside_if_expr) {

    Parser_genln(p, tos2((byte *)"}"));
  };

  return typ;
}
string Parser_statements_no_rcbr(Parser *p) {

  Fn_open_scope(p->cur_fn);

  if (!p->inside_if_expr) {

    Parser_genln(p, tos2((byte *)""));
  };

  int i = 0;

  string last_st_typ = tos2((byte *)"");

  while (p->tok != main__Token_rcbr && p->tok != main__Token_eof &&
         p->tok != main__Token_key_case && p->tok != main__Token_key_default &&
         Parser_peek(p) != main__Token_arrow) {

    last_st_typ = Parser_statement(p, 1);

    if (!p->inside_if_expr) {

      Parser_genln(p, tos2((byte *)""));

      Parser_fgenln(p, tos2((byte *)""));
    };

    i++;

    if (i > 50000) {

      CGen_save(p->cgen);

      Parser_error(p, _STR("more than 50 000 statements in function `%.*s`",
                           p->cur_fn->name.len, p->cur_fn->name.str));
    };
  };

  if (p->tok != main__Token_key_case && p->tok != main__Token_key_default &&
      Parser_peek(p) != main__Token_arrow) {

    Parser_check(p, main__Token_rcbr);

  } else {
  };

  Parser_close_scope(p);

  return last_st_typ;
}
void Parser_close_scope(Parser *p) {

  int i = p->cur_fn->var_idx - 1;

  for (; i >= 0; i--) {

    Var v = (*(Var *)array__get(p->cur_fn->local_vars, i));

    if (v.scope_level != p->cur_fn->scope_level) {

      break;
    };

    if (p->building_v && v.is_alloc) {

      if (string_starts_with(v.typ, tos2((byte *)"array_"))) {

        Parser_genln(p, _STR("v_array_free(%.*s); // close_scope free",
                             v.name.len, v.name.str));

      } else if (string_eq(v.typ, tos2((byte *)"string"))) {

      } else if (v.ptr) {
      };
    };
  };

  if (string_ne(*(string *)array_last(p->cur_fn->defer_text),
                tos2((byte *)""))) {

    Parser_genln(p, *(string *)array_last(p->cur_fn->defer_text));
  };

  Fn_close_scope(p->cur_fn);

  p->cur_fn->var_idx = i + 1;
}
void Parser_genln(Parser *p, string s) { CGen_genln(p->cgen, s); }
void Parser_gen(Parser *p, string s) { CGen_gen(p->cgen, s); }
void Parser_vh_genln(Parser *p, string s) {

  _PUSH(&p->vh_lines, (s), tmp95, string);
}
string Parser_statement(Parser *p, bool add_semi) {

  if (p->returns && !p->is_vweb) {

    Parser_error(p, tos2((byte *)"unreachable code"));
  };

  p->cgen->is_tmp = 0;

  Token tok = p->tok;

  string q = tos2((byte *)"");

  if ((tok == main__Token_name)) { /* case */

    Token next = Parser_peek(p);

    if (p->pref->is_verbose) {

      println(Token_str(next));
    };

    if (Parser_peek(p) == main__Token_colon) {

      Parser_fmt_dec(p);

      string label = Parser_check_name(p);

      Parser_fmt_inc(p);

      Parser_genln(p, string_add(label, tos2((byte *)":")));

      Parser_check(p, main__Token_colon);

      return tos2((byte *)"");

    } else if (Parser_peek(p) == main__Token_decl_assign) {

      Parser_var_decl(p);

    } else {

      if (string_eq(p->lit, tos2((byte *)"panic")) ||
          string_eq(p->lit, tos2((byte *)"exit"))) {

        p->returns = 1;
      };

      q = Parser_bool_expression(p);
    };

  } else if ((tok == main__Token_key_goto)) { /* case */

    Parser_check(p, main__Token_key_goto);

    Parser_fgen(p, tos2((byte *)" "));

    string label = Parser_check_name(p);

    Parser_genln(p, _STR("goto %.*s;", label.len, label.str));

    return tos2((byte *)"");

  } else if ((tok == main__Token_key_defer)) { /* case */

    Parser_defer_st(p);

    return tos2((byte *)"");

  } else if ((tok == main__Token_hash)) { /* case */

    Parser_chash(p);

    return tos2((byte *)"");

  } else if ((tok == main__Token_dollar)) { /* case */

    Parser_comp_time(p);

  } else if ((tok == main__Token_key_if)) { /* case */

    Parser_if_st(p, 0, 0);

  } else if ((tok == main__Token_key_for)) { /* case */

    Parser_for_st(p);

  } else if ((tok == main__Token_key_switch)) { /* case */

    Parser_switch_statement(p);

  } else if ((tok == main__Token_key_match)) { /* case */

    Parser_match_statement(p, 0);

  } else if ((tok == main__Token_key_mut) ||
             (tok == main__Token_key_static)) { /* case */

    Parser_var_decl(p);

  } else if ((tok == main__Token_key_return)) { /* case */

    Parser_return_st(p);

  } else if ((tok == main__Token_lcbr)) { /* case */

    Parser_check(p, main__Token_lcbr);

    Parser_genln(p, tos2((byte *)"{"));

    Parser_statements(p);

    return tos2((byte *)"");

  } else if ((tok == main__Token_key_continue)) { /* case */

    if (p->for_expr_cnt == 0) {

      Parser_error(p, tos2((byte *)"`continue` statement outside `for`"));
    };

    Parser_genln(p, tos2((byte *)"continue"));

    Parser_check(p, main__Token_key_continue);

  } else if ((tok == main__Token_key_break)) { /* case */

    if (p->for_expr_cnt == 0) {

      Parser_error(p, tos2((byte *)"`break` statement outside `for`"));
    };

    Parser_genln(p, tos2((byte *)"break"));

    Parser_check(p, main__Token_key_break);

  } else if ((tok == main__Token_key_go)) { /* case */

    Parser_go_statement(p);

  } else if ((tok == main__Token_key_assert)) { /* case */

    Parser_assert_statement(p);

  } else { // default:

    string typ = Parser_expression(p);

    if (p->inside_if_expr) {

    } else {

      Parser_genln(p, tos2((byte *)"; "));
    };

    return typ;
  };

  if (p->inside_if_expr && p->tok != main__Token_rcbr) {

    Parser_gen(p, tos2((byte *)", "));
  };

  if (add_semi && !p->inside_if_expr) {

    Parser_genln(p, tos2((byte *)";"));
  };

  return q;
}
void Parser_assign_statement(Parser *p, Var v, int ph, bool is_map) {

  Parser_log(&/* ? */ *p,
             _STR("assign_statement() name=%.*s tok=", v.name.len, v.name.str));

  bool is_vid = Parser_fileis(&/* ? */ *p, tos2((byte *)"vid"));

  Token tok = p->tok;

  if (!v.is_mut && !p->pref->translated && !v.is_global && !is_vid) {

    if (v.is_arg) {

      if (p->cur_fn->args.len > 0 &&
          string_eq((*(Var *)array__get(p->cur_fn->args, 0)).name, v.name)) {

        printf("make the receiver `%.*s` mutable:\nfn (%.*s mut %.*s) %.*s "
               "(...) {\n\n",
               v.name.len, v.name.str, v.name.len, v.name.str, v.typ.len,
               v.typ.str, p->cur_fn->name.len, p->cur_fn->name.str);
      };
    };

    Parser_error(p, _STR("`%.*s` is immutable.", v.name.len, v.name.str));
  };

  if (!v.is_changed) {

    Fn_mark_var_changed(p->cur_fn, v);
  };

  bool is_str = string_eq(v.typ, tos2((byte *)"string"));

  if ((tok == main__Token_assign)) { /* case */

    if (!is_map && !p->is_empty_c_struct_init) {

      Parser_gen(p, tos2((byte *)" = "));
    };

  } else if ((tok == main__Token_plus_assign)) { /* case */

    if (is_str) {

      Parser_gen(p, _STR("= string_add(%.*s, ", v.name.len, v.name.str));

    } else {

      Parser_gen(p, tos2((byte *)" += "));
    };

  } else { // default:

    Parser_gen(p, string_add(string_add(tos2((byte *)" "), Token_str(p->tok)),
                             tos2((byte *)" ")));
  };

  Parser_fspace(p);

  Parser_fgen(p, Token_str(tok));

  Parser_fspace(p);

  Parser_next(p);

  int pos = p->cgen->cur_line.len;

  string expr_type = Parser_bool_expression(p);

  if (string_starts_with(p->assigned_type, tos2((byte *)"Option_")) &&
      string_eq(expr_type,
                string_right(p->assigned_type, tos2((byte *)"Option_").len))) {

    println(tos2((byte *)"allowing option asss"));

    string expr = string_right(p->cgen->cur_line, pos);

    string left = string_left(p->cgen->cur_line, pos);

    string typ =
        string_replace(expr_type, tos2((byte *)"Option_"), tos2((byte *)""));

    CGen_resetln(p->cgen,
                 string_add(left, _STR("opt_ok(%.*s, sizeof(%.*s))", expr.len,
                                       expr.str, typ.len, typ.str)));

  } else if (!p->builtin_mod &&
             !Parser_check_types_no_throw(p, expr_type, p->assigned_type)) {

    p->scanner->line_nr--;

    Parser_error(p, _STR("cannot use type `%.*s` as type `%.*s` in assignment",
                         expr_type.len, expr_type.str, p->assigned_type.len,
                         p->assigned_type.str));
  };

  if (is_str && tok == main__Token_plus_assign) {

    Parser_gen(p, tos2((byte *)")"));
  };

  p->assigned_type = tos2((byte *)"");

  if (!v.is_used) {

    Fn_mark_var_used(p->cur_fn, v);
  };
}
void Parser_var_decl(Parser *p) {

  p->is_alloc = 0;

  bool is_mut =
      p->tok == main__Token_key_mut || p->prev_tok == main__Token_key_for;

  bool is_static = p->tok == main__Token_key_static;

  if (p->tok == main__Token_key_mut) {

    Parser_check(p, main__Token_key_mut);

    Parser_fspace(p);
  };

  if (p->tok == main__Token_key_static) {

    Parser_check(p, main__Token_key_static);

    Parser_fspace(p);
  };

  string name = Parser_check_name(p);

  p->var_decl_name = name;

  if (!p->builtin_mod && Fn_known_var(p->cur_fn, name)) {

    Var v = Fn_find_var(&/* ? */ *p->cur_fn, name);

    Parser_error(p, _STR("redefinition of `%.*s`", name.len, name.str));
  };

  if (name.len > 1 && contains_capital(name)) {

    Parser_error(p, tos2((byte *)"variable names cannot contain uppercase "
                                 "letters, use snake_case instead"));
  };

  Parser_check_space(p, main__Token_decl_assign);

  int pos = CGen_add_placeholder(p->cgen);

  string typ = Parser_bool_expression(p);

  bool or_else = p->tok == main__Token_key_orelse;

  string tmp = Parser_get_tmp(p);

  if (or_else) {

    CGen_set_placeholder(
        p->cgen, pos, _STR("%.*s %.*s = ", typ.len, typ.str, tmp.len, tmp.str));

    Parser_genln(p, tos2((byte *)";"));

    typ = string_replace(typ, tos2((byte *)"Option_"), tos2((byte *)""));

    Parser_next(p);

    Parser_check(p, main__Token_lcbr);

    Parser_genln(p, _STR("if (!%.*s .ok) {", tmp.len, tmp.str));

    Parser_register_var(p, (Var){.name = tos2((byte *)"err"),
                                 .typ = tos2((byte *)"string"),
                                 .is_mut = 0,
                                 .is_used = 1,
                                 .is_arg = 0,
                                 .is_const = 0,
                                 .args = new_array(0, 1, sizeof(Var)),
                                 .attr = tos((byte *)"", 0),
                                 .is_alloc = 0,
                                 .ptr = 0,
                                 .ref = 0,
                                 .parent_fn = tos((byte *)"", 0),
                                 .mod = tos((byte *)"", 0),
                                 .line_nr = 0,
                                 .is_global = 0,
                                 .is_changed = 0,
                                 .scope_level = 0});

    Parser_genln(p, _STR("string err = %.*s . error;", tmp.len, tmp.str));

    Parser_statements(p);

    Parser_genln(p,
                 _STR("%.*s %.*s = *(%.*s*) %.*s . data;", typ.len, typ.str,
                      name.len, name.str, typ.len, typ.str, tmp.len, tmp.str));

    if (!p->returns && p->prev_tok2 != main__Token_key_continue &&
        p->prev_tok2 != main__Token_key_break) {

      Parser_error(p,
                   tos2((byte *)"`or` block must return/continue/break/panic"));
    };

    p->returns = 0;
  };

  Parser_register_var(p, (Var){.name = name,
                               .typ = typ,
                               .is_mut = is_mut,
                               .is_alloc = p->is_alloc,
                               .is_arg = 0,
                               .is_const = 0,
                               .args = new_array(0, 1, sizeof(Var)),
                               .attr = tos((byte *)"", 0),
                               .ptr = 0,
                               .ref = 0,
                               .parent_fn = tos((byte *)"", 0),
                               .mod = tos((byte *)"", 0),
                               .line_nr = 0,
                               .is_global = 0,
                               .is_used = 0,
                               .is_changed = 0,
                               .scope_level = 0});

  if (!or_else) {

    string gen_name = Table_var_cgen_name(p->table, name);

    string nt_gen =
        Table_cgen_name_type_pair(&/* ? */ *p->table, gen_name, typ);

    if (!p->is_empty_c_struct_init) {

      nt_gen = string_add(nt_gen, tos2((byte *)"="));
    };

    if (is_static) {

      nt_gen = _STR("static %.*s", nt_gen.len, nt_gen.str);
    };

    CGen_set_placeholder(p->cgen, pos, nt_gen);
  };

  p->var_decl_name = tos2((byte *)"");

  p->is_empty_c_struct_init = 0;
}
string Parser_bool_expression(Parser *p) {

  Token tok = p->tok;

  string typ = Parser_bterm(p);

  bool got_and = 0;

  bool got_or = 0;

  while (p->tok == main__Token_and || p->tok == main__Token_logical_or) {

    if (p->tok == main__Token_and) {

      got_and = 1;

      if (got_or) {

        Parser_error(p, main__and_or_error);
      };
    };

    if (p->tok == main__Token_logical_or) {

      got_or = 1;

      if (got_and) {

        Parser_error(p, main__and_or_error);
      };
    };

    if (p->is_sql) {

      if (p->tok == main__Token_and) {

        Parser_gen(p, tos2((byte *)" and "));

      } else if (p->tok == main__Token_logical_or) {

        Parser_gen(p, tos2((byte *)" or "));
      };

    } else {

      Parser_gen(p,
                 _STR(" %.*s ", Token_str(p->tok).len, Token_str(p->tok).str));
    };

    Parser_check_space(p, p->tok);

    Parser_check_types(p, Parser_bterm(p), typ);
  };

  if (string_eq(typ, tos2((byte *)""))) {

    println(tos2((byte *)"curline:"));

    println(p->cgen->cur_line);

    println(Token_str(tok));

    Parser_error(p, tos2((byte *)"expr() returns empty type"));
  };

  return typ;
}
string Parser_bterm(Parser *p) {

  int ph = CGen_add_placeholder(p->cgen);

  string typ = Parser_expression(p);

  p->expected_type = typ;

  bool is_str = string_eq(typ, tos2((byte *)"string")) && !p->is_sql;

  Token tok = p->tok;

  if (tok == main__Token_eq || tok == main__Token_gt || tok == main__Token_lt ||
      tok == main__Token_le || tok == main__Token_ge || tok == main__Token_ne) {

    Parser_fgen(p,
                _STR(" %.*s ", Token_str(p->tok).len, Token_str(p->tok).str));

    if (is_str) {

      Parser_gen(p, tos2((byte *)","));

    } else if (p->is_sql && tok == main__Token_eq) {

      Parser_gen(p, tos2((byte *)"="));

    } else {

      Parser_gen(p, Token_str(tok));
    };

    Parser_next(p);

    if (p->is_sql) {

      p->sql_i++;

      Parser_gen(p, string_add(tos2((byte *)"$"), int_str(p->sql_i)));

      CGen_start_cut(p->cgen);

      Parser_check_types(p, Parser_expression(p), typ);

      string sql_param = CGen_cut(p->cgen);

      _PUSH(&p->sql_params, (sql_param), tmp131, string);

      _PUSH(&p->sql_types, (typ), tmp132, string);

    } else {

      Parser_check_types(p, Parser_expression(p), typ);
    };

    typ = tos2((byte *)"bool");

    if (is_str) {

      Parser_gen(p, tos2((byte *)")"));

      if ((tok == main__Token_eq)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"string_eq("));

      } else if ((tok == main__Token_ne)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"string_ne("));

      } else if ((tok == main__Token_le)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"string_le("));

      } else if ((tok == main__Token_ge)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"string_ge("));

      } else if ((tok == main__Token_gt)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"string_gt("));

      } else if ((tok == main__Token_lt)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"string_lt("));
      };
    };
  };

  return typ;
}
string Parser_name_expr(Parser *p) {

  p->has_immutable_field = 0;

  int ph = CGen_add_placeholder(p->cgen);

  bool ptr = p->tok == main__Token_amp;

  bool deref = p->tok == main__Token_mul;

  if (ptr || deref) {

    Parser_next(p);
  };

  string name = p->lit;

  Parser_fgen(p, name);

  string orig_name = name;

  bool is_c =
      string_eq(name, tos2((byte *)"C")) && Parser_peek(p) == main__Token_dot;

  bool is_c_struct_init = is_c && ptr;

  if (is_c) {

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    name = p->lit;

    Parser_fgen(p, name);

    if (!is_c_struct_init && Parser_peek(p) == main__Token_lcbr) {

      is_c_struct_init = 1;
    };
  };

  if (p->tok == main__Token_dot) {

    Type T = Parser_find_type(&/* ? */ *p, p->expected_type);

    if (T.cat == main__TypeCategory_enum_) {

      Parser_check(p, main__Token_dot);

      string val = Parser_check_name(p);

      if (!Type_has_enum_val(&/* ? */ T, val)) {

        Parser_error(p, _STR("enum `%.*s` does not have value `%.*s`",
                             T.name.len, T.name.str, val.len, val.str));
      };

      Parser_gen(
          p, string_add(
                 string_add(string_add(string_add(T.mod, tos2((byte *)"__")),
                                       p->expected_type),
                            tos2((byte *)"_")),
                 val));
    };

    return p->expected_type;
  };

  if (Parser_peek(p) == main__Token_dot &&
      ((string_eq(name, p->mod) && Table_known_mod(&/* ? */ *p->table, name)) ||
       FileImportTable_known_alias(&/* ? */ *p->import_table, name)) &&
      !Fn_known_var(p->cur_fn, name) && !is_c) {

    string mod = name;

    if (string_ne(name, p->mod) &&
        FileImportTable_known_alias(&/* ? */ *p->import_table, name)) {

      mod = string_replace(
          FileImportTable_resolve_alias(&/* ? */ *p->import_table, name),
          tos2((byte *)"."), tos2((byte *)"_dot_"));
    };

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    name = p->lit;

    Parser_fgen(p, name);

    name = prepend_mod(mod, name);

  } else if (!Table_known_type(&/* ? */ *p->table, name) &&
             !Fn_known_var(p->cur_fn, name) &&
             !Table_known_fn(&/* ? */ *p->table, name) &&
             !Table_known_const(&/* ? */ *p->table, name) && !is_c) {

    name = Parser_prepend_mod(&/* ? */ *p, name);
  };

  Var v = Fn_find_var(&/* ? */ *p->cur_fn, name);

  if (string_eq(name, string_add(tos2((byte *)"main__"), p->var_decl_name))) {

    v.name = p->var_decl_name;

    v.typ = tos2((byte *)"voidptr");

    v.is_mut = 1;
  };

  if (v.name.len != 0) {

    if (ptr) {

      Parser_gen(p, tos2((byte *)"& /*vvar*/ "));

    } else if (deref) {

      Parser_gen(p, tos2((byte *)"*"));
    };

    string typ = Parser_var_expr(p, v);

    if (deref) {

      if (!string_contains(typ, tos2((byte *)"*")) &&
          !string_ends_with(typ, tos2((byte *)"ptr"))) {

        printf("name=\"%.*s\", t=%.*s\n", name.len, name.str, v.typ.len,
               v.typ.str);

        Parser_error(p, _STR("dereferencing requires a pointer, but got `%.*s`",
                             typ.len, typ.str));
      };

      typ = string_replace(typ, tos2((byte *)"ptr"), tos2((byte *)""));

      typ = string_replace(typ, tos2((byte *)"*"), tos2((byte *)""));

    } else if (ptr) {

      typ = string_add(typ, tos2((byte *)"*"));
    };

    return typ;
  };

  if (Table_known_type(&/* ? */ *p->table, name)) {

    if (!is_c && (Parser_peek(p) == main__Token_lpar ||
                  (deref && Parser_peek(p) == main__Token_rpar))) {

      if (deref) {

        name = string_add(name, tos2((byte *)"*"));

      } else if (ptr) {

        name = string_add(name, tos2((byte *)"*"));
      };

      Parser_gen(p, tos2((byte *)"("));

      string typ = Parser_cast(p, name);

      Parser_gen(p, tos2((byte *)")"));

      while (p->tok == main__Token_dot) {

        typ = Parser_dot(p, typ, ph);
      };

      return typ;

    } else if (Parser_peek(p) == main__Token_dot) {

      Type enum_type = Table_find_type(&/* ? */ *p->table, name);

      if (enum_type.cat != main__TypeCategory_enum_) {

        Parser_error(p, _STR("`%.*s` is not an enum", name.len, name.str));
      };

      Parser_next(p);

      Parser_check(p, main__Token_dot);

      string val = p->lit;

      Parser_gen(
          p, string_add(string_add(string_add(string_add(enum_type.mod,
                                                         tos2((byte *)"__")),
                                              enum_type.name),
                                   tos2((byte *)"_")),
                        val));

      Parser_next(p);

      return enum_type.name;

    } else if (Parser_peek(p) == main__Token_lcbr) {

      if (ptr) {

        name = string_add(name, tos2((byte *)"*"));
      };

      if (string_eq(name, tos2((byte *)"T"))) {

        name = p->cur_gen_type;
      };

      return Parser_struct_init(p, name, is_c_struct_init);
    };
  };

  if (is_c) {

    if (Parser_peek(p) != main__Token_lpar) {

      Parser_gen(p, name);

      Parser_next(p);

      return tos2((byte *)"int");
    };

    Fn f = (Fn){.name = name,
                .is_c = 1,
                .mod = tos((byte *)"", 0),
                .local_vars = new_array(0, 1, sizeof(Var)),
                .var_idx = 0,
                .args = new_array(0, 1, sizeof(Var)),
                .is_interface = 0,
                .scope_level = 0,
                .typ = tos((byte *)"", 0),
                .receiver_typ = tos((byte *)"", 0),
                .is_public = 0,
                .is_method = 0,
                .returns_error = 0,
                .is_decl = 0,
                .defer_text = new_array(0, 1, sizeof(string))};

    p->is_c_fn_call = 1;

    Parser_fn_call(p, f, 0, tos2((byte *)""), tos2((byte *)""));

    p->is_c_fn_call = 0;

    Fn cfn = Table_find_fn(&/* ? */ *p->table, name);

    if (string_eq(cfn.name, tos2((byte *)""))) {

      return tos2((byte *)"void*");
    };

    return cfn.typ;
  };

  Var c = Table_find_const(&/* ? */ *p->table, name);

  if (string_ne(c.name, tos2((byte *)"")) && ptr && !c.is_global) {

    Parser_error(p, _STR("cannot take the address of constant `%.*s`",
                         c.name.len, c.name.str));
  };

  if (c.name.len != 0) {

    if (ptr) {

      Parser_gen(p, tos2((byte *)"& /*const*/ "));
    };

    Parser_log(&/* ? */ *p, tos2((byte *)"calling var expr"));

    string typ = Parser_var_expr(p, c);

    if (ptr) {

      typ = string_add(typ, tos2((byte *)"*"));
    };

    return typ;
  };

  Fn f = Table_find_fn(&/* ? */ *p->table, name);

  if (string_eq(f.name, tos2((byte *)""))) {

    if (!Parser_first_pass(&/* ? */ *p)) {

      if (p->v_script) {

        name =
            string_replace(name, tos2((byte *)"main__"), tos2((byte *)"os__"));

        f = Table_find_fn(&/* ? */ *p->table, name);
      };

      if (string_eq(f.name, tos2((byte *)""))) {

        if (Table_known_mod(&/* ? */ *p->table, orig_name) ||
            FileImportTable_known_alias(&/* ? */ *p->import_table, orig_name)) {

          name = string_replace(
              string_replace(name, tos2((byte *)"__"), tos2((byte *)".")),
              tos2((byte *)"_dot_"), tos2((byte *)"."));

          Parser_error(p, _STR("undefined: `%.*s`", name.len, name.str));

        } else {

          if (string_eq(orig_name, tos2((byte *)"i32"))) {

            println(tos2((byte *)"`i32` alias was removed, use `int` instead"));
          };

          if (string_eq(orig_name, tos2((byte *)"u8"))) {

            println(tos2((byte *)"`u8` alias was removed, use `byte` instead"));
          };

          Parser_error(p,
                       _STR("undefined: `%.*s`", orig_name.len, orig_name.str));
        };
      };

    } else {

      Parser_next(p);

      return tos2((byte *)"void");
    };
  };

  Token peek = Parser_peek(p);

  if (peek != main__Token_lpar && peek != main__Token_lt) {

    Type fn_typ = (Type){.name = Fn_typ_str(f),
                         .mod = p->mod,
                         .func = f,
                         .fields = new_array(0, 1, sizeof(Var)),
                         .methods = new_array(0, 1, sizeof(Fn)),
                         .parent = tos((byte *)"", 0),
                         .is_c = 0,
                         .enum_vals = new_array(0, 1, sizeof(string)),
                         .gen_types = new_array(0, 1, sizeof(string)),
                         .is_placeholder = 0,
                         .gen_str = 0};

    Table_register_type2(p->table, fn_typ);

    Parser_gen(p, Table_cgen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f));

    Parser_next(p);

    return Fn_typ_str(f);
  };

  if (string_eq(f.typ, tos2((byte *)"void")) && !p->inside_if_expr) {
  };

  Parser_log(&/* ? */ *p, tos2((byte *)"calling function"));

  Parser_fn_call(p, f, 0, tos2((byte *)""), tos2((byte *)""));

  if (p->tok == main__Token_dot) {

    string typ = tos2((byte *)"");

    while (p->tok == main__Token_dot) {

      typ = Parser_dot(p, f.typ, ph);
    };

    return typ;
  };

  Parser_log(&/* ? */ *p, tos2((byte *)"end of name_expr"));

  return f.typ;
}
string Parser_var_expr(Parser *p, Var v) {

  Parser_log(&/* ? */ *p, _STR("\nvar_expr() v.name=\"%.*s\" v.typ=\"%.*s\"",
                               v.name.len, v.name.str, v.typ.len, v.typ.str));

  Fn_mark_var_used(p->cur_fn, v);

  int fn_ph = CGen_add_placeholder(p->cgen);

  p->expr_var = v;

  Parser_gen(p, Table_var_cgen_name(p->table, v.name));

  Parser_next(p);

  string typ = v.typ;

  if (string_starts_with(typ, tos2((byte *)"fn ")) &&
      p->tok == main__Token_lpar) {

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    Parser_gen(p, tos2((byte *)"("));

    Parser_fn_call_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ T.func);

    Parser_gen(p, tos2((byte *)")"));

    typ = T.func.typ;
  };

  if (p->tok == main__Token_lsbr) {

    typ = Parser_index_expr(p, typ, fn_ph);
  };

  while (p->tok == main__Token_dot) {

    if (Parser_peek(p) == main__Token_key_select) {

      Parser_next(p);

      return Parser_select_query(p, fn_ph);
    };

    if (string_eq(typ, tos2((byte *)"pg__DB")) &&
        !Parser_fileis(&/* ? */ *p, tos2((byte *)"pg.v")) &&
        Parser_peek(p) == main__Token_name) {

      Parser_next(p);

      Parser_insert_query(p, fn_ph);

      return tos2((byte *)"void");
    };

    typ = Parser_dot(p, typ, fn_ph);

    Parser_log(&/* ? */ *p, _STR("typ after dot=%.*s", typ.len, typ.str));

    if (p->tok == main__Token_lsbr) {
    };
  };

  if (p->tok == main__Token_inc || p->tok == main__Token_dec) {

    if (!v.is_mut && !v.is_arg && !p->pref->translated) {

      Parser_error(p, _STR("`%.*s` is immutable", v.name.len, v.name.str));
    };

    if (!v.is_changed) {

      Fn_mark_var_changed(p->cur_fn, v);
    };

    if (string_ne(typ, tos2((byte *)"int"))) {

      if (!p->pref->translated && !is_number_type(typ)) {

        Parser_error(
            p, _STR("cannot ++/-- value of type `%.*s`", typ.len, typ.str));
      };
    };

    Parser_gen(p, Token_str(p->tok));

    Parser_fgen(p, Token_str(p->tok));

    Parser_next(p);

    if (p->pref->translated) {

    } else {

      return tos2((byte *)"void");
    };
  };

  typ = Parser_index_expr(p, typ, fn_ph);

  if (p->tok == main__Token_dot) {

    while (p->tok == main__Token_dot) {

      typ = Parser_dot(p, typ, fn_ph);
    };

    typ = Parser_index_expr(p, typ, fn_ph);
  };

  return typ;
}
bool Parser_fileis(Parser *p, string s) {

  return string_contains(p->scanner->file_path, s);
}
string Parser_dot(Parser *p, string str_typ, int method_ph) {

  Parser_check(p, main__Token_dot);

  Type typ = Parser_find_type(&/* ? */ *p, str_typ);

  if (typ.name.len == 0) {

    Parser_error(
        p, _STR("dot(): cannot find type `%.*s`", str_typ.len, str_typ.str));
  };

  if (p->tok == main__Token_dollar) {

    Parser_comptime_method_call(p, typ);

    return tos2((byte *)"void");
  };

  string field_name = p->lit;

  Parser_fgen(p, field_name);

  Parser_log(&/* ? */ *p, _STR("dot() field_name=%.*s typ=%.*s", field_name.len,
                               field_name.str, str_typ.len, str_typ.str));

  bool has_field = Table_type_has_field(
      &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ,
      Table_var_cgen_name(p->table, field_name));

  bool has_method = Table_type_has_method(
      &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ, field_name);

  if (!has_method && string_eq(field_name, tos2((byte *)"str")) &&
      string_starts_with(typ.name, tos2((byte *)"array_"))) {

    Parser_gen_array_str(p, typ);

    has_method = 1;
  };

  if (!typ.is_c && !p->is_c_fn_call && !has_field && !has_method &&
      !Parser_first_pass(&/* ? */ *p)) {

    if (string_starts_with(typ.name, tos2((byte *)"Option_"))) {

      string opt_type = string_right(typ.name, 7);

      Parser_error(
          p, _STR("unhandled option type: %.*s?", opt_type.len, opt_type.str));
    };

    Parser_error(p,
                 _STR("type `%.*s` has no field or method `%.*s`", typ.name.len,
                      typ.name.str, field_name.len, field_name.str));
  };

  string dot = tos2((byte *)".");

  if (string_ends_with(str_typ, tos2((byte *)"*")) ||
      string_eq(str_typ, tos2((byte *)"FT_Face"))) {

    dot = tos2((byte *)"->");
  };

  if (has_field) {

    string struct_field = (string_ne(typ.name, tos2((byte *)"Option")))
                              ? (Table_var_cgen_name(p->table, field_name))
                              : (field_name);

    Var field = Table_find_field(
        &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ, struct_field);

    if (!field.is_mut && !p->has_immutable_field) {

      p->has_immutable_field = 1;

      p->first_immutable_field = field;
    };

    Token next = Parser_peek(p);

    bool modifying = Token_is_assign(next) || next == main__Token_inc ||
                     next == main__Token_dec ||
                     (string_starts_with(field.typ, tos2((byte *)"array_")) &&
                      next == main__Token_left_shift);

    bool is_vi = Parser_fileis(&/* ? */ *p, tos2((byte *)"vid"));

    if (!p->builtin_mod && !p->pref->translated && modifying && !is_vi &&
        p->has_immutable_field) {

      Var f = p->first_immutable_field;

      Parser_error(
          p, string_add(
                 _STR("cannot modify immutable field `%.*s` (type `%.*s`)\n",
                      f.name.len, f.name.str, f.parent_fn.len, f.parent_fn.str),
                 _STR("declare the field with `mut:`\nstruct %.*s {\n  "
                      "mut:\n	%.*s %.*s\n}\n",
                      f.parent_fn.len, f.parent_fn.str, f.name.len, f.name.str,
                      f.typ.len, f.typ.str)));
    };

    if (!p->builtin_mod && string_ne(p->mod, typ.mod)) {
    };

    if (field.access_mod == main__AccessMod_private && !p->builtin_mod &&
        !p->pref->translated && string_ne(p->mod, typ.mod)) {

      Parser_error(p,
                   _STR("cannot refer to unexported field `%.*s` (type `%.*s`)",
                        struct_field.len, struct_field.str, typ.name.len,
                        typ.name.str));
    };

    Parser_gen(p, string_add(dot, struct_field));

    Parser_next(p);

    return field.typ;
  };

  Fn method = Table_find_method(
      &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ, field_name);

  Parser_fn_call(p, method, method_ph, tos2((byte *)""), str_typ);

  if (string_eq(method.typ, tos2((byte *)"array")) &&
      string_starts_with(typ.name, tos2((byte *)"array_"))) {

    return typ.name;
  };

  if (string_eq(method.typ, tos2((byte *)"void*")) &&
      string_starts_with(typ.name, tos2((byte *)"array_"))) {

    return string_right(typ.name, 6);
  };

  return method.typ;
}
string Parser_index_expr(Parser *p, string typ_, int fn_ph) {

  string typ = typ_;

  Var v = p->expr_var;

  bool is_map = string_starts_with(typ, tos2((byte *)"map_"));

  bool is_str = string_eq(typ, tos2((byte *)"string"));

  bool is_arr0 = string_starts_with(typ, tos2((byte *)"array_"));

  bool is_arr = is_arr0 || string_eq(typ, tos2((byte *)"array"));

  bool is_ptr = string_eq(typ, tos2((byte *)"byte*")) ||
                string_eq(typ, tos2((byte *)"byteptr")) ||
                string_contains(typ, tos2((byte *)"*"));

  bool is_indexer = p->tok == main__Token_lsbr;

  bool close_bracket = 0;

  if (is_indexer) {

    bool is_fixed_arr = string_at(typ, 0) == '[';

    if (!is_str && !is_arr && !is_map && !is_ptr && !is_fixed_arr) {

      Parser_error(p, _STR("Cant [] non-array/string/map. Got type \"%.*s\"",
                           typ.len, typ.str));
    };

    Parser_check(p, main__Token_lsbr);

    if (is_str) {

      typ = tos2((byte *)"byte");

      Parser_fgen(p, tos2((byte *)"["));

      if (p->builtin_mod) {

        Parser_gen(p, tos2((byte *)".str["));

        close_bracket = 1;

      } else {

        Parser_gen(p, tos2((byte *)","));
      };
    };

    if (is_fixed_arr) {

      if (string_contains(typ, tos2((byte *)"]["))) {

        int pos = string_index_after(typ, tos2((byte *)"["), 1);

        typ = string_right(typ, pos);

      } else {

        typ = string_all_after(typ, tos2((byte *)"]"));
      };

      Parser_gen(p, tos2((byte *)"["));

      close_bracket = 1;

    } else if (is_ptr) {

      typ = string_replace(typ, tos2((byte *)"*"), tos2((byte *)""));

      if (!is_arr) {

        Parser_gen(p, tos2((byte *)"[/*ptr*/"));

        close_bracket = 1;
      };
    };

    if (is_arr) {

      if (is_arr0) {

        if (Parser_fileis(&/* ? */ *p, tos2((byte *)"int_test"))) {

          printf("\nRRRR0 %.*s\n", typ.len, typ.str);
        };

        typ = string_right(typ, 6);

        if (Parser_fileis(&/* ? */ *p, tos2((byte *)"int_test"))) {

          printf("RRRR %.*s\n", typ.len, typ.str);
        };
      };

      if (string_eq(typ, tos2((byte *)"array"))) {

        typ = tos2((byte *)"void*");
      };

      if (p->pref->translated && !p->builtin_mod) {

        CGen_set_placeholder(p->cgen, fn_ph,
                             _STR("((%.*s*)(", typ.len, typ.str));

        Parser_gen(p, tos2((byte *)".data))["));

      } else {

        Parser_gen(p, tos2((byte *)","));
      };
    };

    if (is_map) {

      typ = string_replace(typ, tos2((byte *)"map_"), tos2((byte *)""));

      if (string_eq(typ, tos2((byte *)"map"))) {

        typ = tos2((byte *)"void*");
      };

      Parser_gen(p, tos2((byte *)","));
    };

    if (is_arr) {

      int index_pos = p->cgen->cur_line.len;

      Type T = Table_find_type(&/* ? */ *p->table, Parser_expression(p));

      if (string_ne(T.parent, tos2((byte *)"int")) &&
          string_ne(T.parent, tos2((byte *)"u32"))) {

        Parser_check_types(p, T.name, tos2((byte *)"int"));
      };

      if (v_string_int(
              string_replace(string_right(p->cgen->cur_line, index_pos),
                             tos2((byte *)" "), tos2((byte *)""))) < 0) {

        Parser_error(p, tos2((byte *)"cannot access negative array index"));
      };

    } else {

      Type T = Table_find_type(&/* ? */ *p->table, Parser_expression(p));

      if (is_map && string_ne(T.parent, tos2((byte *)"string"))) {

        Parser_check_types(p, T.name, tos2((byte *)"string"));
      };
    };

    Parser_check(p, main__Token_rsbr);

    if (close_bracket) {

      Parser_gen(p, _STR("]/*r%.*s %d*/", typ.len, typ.str, v.is_mut));
    };

    p->expr_var = v;
  };

  if ((p->tok == main__Token_assign && !p->is_sql) ||
      p->tok == main__Token_plus_assign || p->tok == main__Token_minus_assign ||
      p->tok == main__Token_mult_assign || p->tok == main__Token_div_assign ||
      p->tok == main__Token_xor_assign || p->tok == main__Token_mod_assign ||
      p->tok == main__Token_or_assign || p->tok == main__Token_and_assign ||
      p->tok == main__Token_righ_shift_assign ||
      p->tok == main__Token_left_shift_assign) {

    if (is_indexer && is_str && !p->builtin_mod) {

      Parser_error(p, tos2((byte *)"strings are immutable"));
    };

    int assign_pos = p->cgen->cur_line.len;

    bool is_cao = p->tok != main__Token_assign;

    p->assigned_type = typ;

    p->expected_type = typ;

    Parser_assign_statement(p, v, fn_ph, is_indexer && (is_map || is_arr));

    if (is_indexer && (is_map || is_arr)) {

      string val = string_right(p->cgen->cur_line, assign_pos);

      CGen_resetln(p->cgen, string_left(p->cgen->cur_line, assign_pos));

      string cao_tmp = p->cgen->cur_line;

      string func = tos2((byte *)"");

      if (is_map) {

        func = tos2((byte *)"map__set(&");

      } else {

        if (is_ptr) {

          func = tos2((byte *)"array_set(");

          if (is_cao) {

            cao_tmp = _STR("*(%.*s *) array__get(*%.*s)", p->expected_type.len,
                           p->expected_type.str, cao_tmp.len, cao_tmp.str);
          };

        } else {

          func = tos2((byte *)"array_set(&/*q*/");

          if (is_cao) {

            cao_tmp = _STR("*(%.*s *) array__get(%.*s)", p->expected_type.len,
                           p->expected_type.str, cao_tmp.len, cao_tmp.str);
          };
        };
      };

      CGen_set_placeholder(p->cgen, fn_ph, func);

      if (is_cao) {

        val = string_add(
            string_add(cao_tmp, string_all_before(val, tos2((byte *)"="))),
            string_all_after(val, tos2((byte *)"=")));
      };

      Parser_gen(p, _STR(", & (%.*s []) { %.*s })", typ.len, typ.str, val.len,
                         val.str));
    };

    return typ;

  } else if ((is_map || is_arr || (is_str && !p->builtin_mod)) && is_indexer) {

    string index_expr = tos2((byte *)"");

    if (p->cgen->is_tmp) {

      index_expr = string_right(p->cgen->tmp_line, fn_ph);

      CGen_resetln(p->cgen, string_left(p->cgen->tmp_line, fn_ph));

    } else {

      index_expr = string_right(p->cgen->cur_line, fn_ph);

      CGen_resetln(p->cgen, string_left(p->cgen->cur_line, fn_ph));
    };

    string tmp = Parser_get_tmp(p);

    string tmp_ok = Parser_get_tmp(p);

    if (is_map) {

      Parser_gen(p, _STR("%.*s", tmp.len, tmp.str));

      string def = type_default(typ);

      CGen_insert_before(
          p->cgen,
          _STR("%.*s %.*s = %.*s; bool %.*s = map_get(%.*s, & %.*s);", typ.len,
               typ.str, tmp.len, tmp.str, def.len, def.str, tmp_ok.len,
               tmp_ok.str, index_expr.len, index_expr.str, tmp.len, tmp.str));

    } else if (is_arr) {

      if (p->pref->translated && !p->builtin_mod) {

        Parser_gen(p, _STR("%.*s ]", index_expr.len, index_expr.str));

      } else {

        if (is_ptr) {

          Parser_gen(p, _STR("( *(%.*s*) array__get(* %.*s) )", typ.len,
                             typ.str, index_expr.len, index_expr.str));

        } else {

          Parser_gen(p, _STR("( *(%.*s*) array__get(%.*s) )", typ.len, typ.str,
                             index_expr.len, index_expr.str));
        };
      };

    } else if (is_str && !p->builtin_mod) {

      Parser_gen(p, _STR("string_at(%.*s)", index_expr.len, index_expr.str));
    };

    if (is_map && string_eq(typ, tos2((byte *)"string"))) {

      CGen_insert_before(p->cgen,
                         _STR("if (!%.*s) %.*s = tos((byte *)\"\", 0);",
                              tmp_ok.len, tmp_ok.str, tmp.len, tmp.str));
    };
  };

  return typ;
}
string Parser_expression(Parser *p) {

  if (string_contains(p->scanner->file_path, tos2((byte *)"test_test"))) {

    printf("expression() pass=%d tok=\n", p->pass);

    Parser_print_tok(&/* ? */ *p);
  };

  p->cgen;

  (tos2((byte *)"/* expr start*/"));

  int ph = CGen_add_placeholder(p->cgen);

  string typ = Parser_term(p);

  bool is_str = string_eq(typ, tos2((byte *)"string"));

  if (p->tok == main__Token_left_shift) {

    if (string_contains(typ, tos2((byte *)"array_"))) {

      string tmp = Parser_get_tmp(p);

      string tmp_typ = string_right(typ, 6);

      Parser_check_space(p, main__Token_left_shift);

      Parser_gen(p, tos2((byte *)", ("));

      if (!p->expr_var.is_mut && !p->pref->translated) {

        Parser_error(p, _STR("`%.*s` is immutable (can\'t <<)",
                             p->expr_var.name.len, p->expr_var.name.str));
      };

      if (!p->expr_var.is_changed) {

        Fn_mark_var_changed(p->cur_fn, p->expr_var);
      };

      string expr_type = Parser_expression(p);

      bool push_array = string_eq(typ, expr_type);

      if (push_array) {

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"_PUSH_MANY(&"));

        Parser_gen(p,
                   _STR("), %.*s, %.*s)", tmp.len, tmp.str, typ.len, typ.str));

      } else {

        Parser_check_types(p, expr_type, tmp_typ);

        string push_call = (string_contains(typ, tos2((byte *)"*")))
                               ? (tos2((byte *)"_PUSH("))
                               : (tos2((byte *)"_PUSH(&"));

        CGen_set_placeholder(p->cgen, ph, push_call);

        Parser_gen(p, _STR("), %.*s, %.*s)", tmp.len, tmp.str, tmp_typ.len,
                           tmp_typ.str));
      };

      return tos2((byte *)"void");

    } else {

      Parser_next(p);

      Parser_gen(p, tos2((byte *)" << "));

      Parser_check_types(p, Parser_expression(p), typ);

      return tos2((byte *)"int");
    };
  };

  if (p->tok == main__Token_key_in) {

    Parser_fgen(p, tos2((byte *)" "));

    Parser_check(p, main__Token_key_in);

    Parser_fgen(p, tos2((byte *)" "));

    Parser_gen(p, tos2((byte *)", "));

    string arr_typ = Parser_expression(p);

    bool is_map = string_starts_with(arr_typ, tos2((byte *)"map_"));

    if (!string_starts_with(arr_typ, tos2((byte *)"array_")) && !is_map) {

      Parser_error(p, tos2((byte *)"`in` requires an array/map"));
    };

    Type T = Table_find_type(&/* ? */ *p->table, arr_typ);

    if (!is_map && !Type_has_method(&/* ? */ T, tos2((byte *)"contains"))) {

      Parser_error(
          p, _STR("%.*s has no method `contains`", arr_typ.len, arr_typ.str));
    };

    if (is_map) {

      CGen_set_placeholder(p->cgen, ph, tos2((byte *)"_IN_MAP( "));

    } else {

      CGen_set_placeholder(p->cgen, ph, _STR("_IN(%.*s, ", typ.len, typ.str));
    };

    Parser_gen(p, tos2((byte *)")"));

    return tos2((byte *)"bool");
  };

  if (p->tok == main__Token_righ_shift) {

    Parser_next(p);

    Parser_gen(p, tos2((byte *)" >> "));

    Parser_check_types(p, Parser_expression(p), typ);

    return tos2((byte *)"int");
  };

  if (p->tok == main__Token_dot) {

    while (p->tok == main__Token_dot) {

      typ = Parser_dot(p, typ, ph);
    };
  };

  while (p->tok == main__Token_plus || p->tok == main__Token_minus ||
         p->tok == main__Token_pipe || p->tok == main__Token_amp ||
         p->tok == main__Token_xor) {

    Token tok_op = p->tok;

    bool is_num = string_eq(typ, tos2((byte *)"void*")) ||
                  string_eq(typ, tos2((byte *)"byte*")) || is_number_type(typ);

    Parser_check_space(p, p->tok);

    if (is_str && tok_op == main__Token_plus) {

      CGen_set_placeholder(p->cgen, ph, tos2((byte *)"string_add("));

      Parser_gen(p, tos2((byte *)","));

    } else if (is_num) {

      if (string_eq(typ, tos2((byte *)"void*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2((byte *)"(byte*)"));
      };

      Parser_gen(p, Token_str(tok_op));

    } else {

      if (p->pref->translated) {

        Parser_gen(
            p, string_add(Token_str(tok_op), tos2((byte *)" /*doom hack*/")));

      } else {

        Parser_gen(p, tos2((byte *)","));
      };
    };

    Parser_check_types(p, Parser_term(p), typ);

    if (is_str && tok_op == main__Token_plus) {

      Parser_gen(p, tos2((byte *)")"));
    };

    if (!p->pref->translated && !is_str && !is_num) {

      Type T = Table_find_type(&/* ? */ *p->table, typ);

      if (tok_op == main__Token_plus) {

        if (Type_has_method(&/* ? */ T, tos2((byte *)"+"))) {

          CGen_set_placeholder(p->cgen, ph,
                               string_add(typ, tos2((byte *)"_plus(")));

          Parser_gen(p, tos2((byte *)")"));

        } else {

          Parser_error(
              p, _STR("operator + not defined on `%.*s`", typ.len, typ.str));
        };

      } else if (tok_op == main__Token_minus) {

        if (Type_has_method(&/* ? */ T, tos2((byte *)"-"))) {

          CGen_set_placeholder(p->cgen, ph,
                               _STR("%.*s_minus(", typ.len, typ.str));

          Parser_gen(p, tos2((byte *)")"));

        } else {

          Parser_error(
              p, _STR("operator - not defined on `%.*s`", typ.len, typ.str));
        };
      };
    };
  };

  return typ;
}
string Parser_term(Parser *p) {

  int line_nr = p->scanner->line_nr;

  string typ = Parser_unary(p);

  if (p->tok == main__Token_mul && line_nr != p->scanner->line_nr) {

    return typ;
  };

  while (p->tok == main__Token_mul || p->tok == main__Token_div ||
         p->tok == main__Token_mod) {

    Token tok = p->tok;

    bool is_div = tok == main__Token_div;

    bool is_mod = tok == main__Token_mod;

    Parser_next(p);

    Parser_gen(p, Token_str(tok));

    Parser_fgen(p, string_add(string_add(tos2((byte *)" "), Token_str(tok)),
                              tos2((byte *)" ")));

    if ((is_div || is_mod) && p->tok == main__Token_number &&
        string_eq(p->lit, tos2((byte *)"0"))) {

      Parser_error(p, tos2((byte *)"division by zero"));
    };

    if (is_mod && (is_float_type(typ) || !is_number_type(typ))) {

      Parser_error(p, tos2((byte *)"operator .mod requires integer types"));
    };

    Parser_check_types(p, Parser_unary(p), typ);
  };

  return typ;
}
string Parser_unary(Parser *p) {

  string typ = tos2((byte *)"");

  Token tok = p->tok;

  if ((tok == main__Token_not)) { /* case */

    Parser_gen(p, tos2((byte *)"!"));

    Parser_check(p, main__Token_not);

    typ = tos2((byte *)"bool");

    Parser_bool_expression(p);

  } else if ((tok == main__Token_bit_not)) { /* case */

    Parser_gen(p, tos2((byte *)"~"));

    Parser_check(p, main__Token_bit_not);

    typ = Parser_bool_expression(p);

  } else { // default:

    typ = Parser_factor(p);
  };

  return typ;
}
string Parser_factor(Parser *p) {

  string typ = tos2((byte *)"");

  Token tok = p->tok;

  if ((tok == main__Token_number)) { /* case */

    typ = tos2((byte *)"int");

    if ((string_contains(p->lit, tos2((byte *)".")) ||
         (string_contains(p->lit, tos2((byte *)"e")) ||
          string_contains(p->lit, tos2((byte *)"E")))) &&
        !(string_at(p->lit, 0) == '0' &&
          (string_at(p->lit, 1) == 'x' || string_at(p->lit, 1) == 'X'))) {

      typ = tos2((byte *)"f32");

    } else {

      u64 v_u64 = string_u64(p->lit);

      if (((u64)(((u32)(v_u64)))) < v_u64) {

        typ = tos2((byte *)"u64");
      };
    };

    if (string_ne(p->expected_type, tos2((byte *)"")) &&
        !is_valid_int_const(p->lit, p->expected_type)) {

      Parser_error(p, _STR("constant `%.*s` overflows `%.*s`", p->lit.len,
                           p->lit.str, p->expected_type.len,
                           p->expected_type.str));
    };

    Parser_gen(p, p->lit);

    Parser_fgen(p, p->lit);

  } else if ((tok == main__Token_minus)) { /* case */

    Parser_gen(p, tos2((byte *)"-"));

    Parser_fgen(p, tos2((byte *)"-"));

    Parser_next(p);

    return Parser_factor(p);

  } else if ((tok == main__Token_key_sizeof)) { /* case */

    Parser_gen(p, tos2((byte *)"sizeof("));

    Parser_fgen(p, tos2((byte *)"sizeof("));

    Parser_next(p);

    Parser_check(p, main__Token_lpar);

    string sizeof_typ = Parser_get_type(p);

    if (string_ends_with(sizeof_typ, tos2((byte *)"*"))) {

      sizeof_typ = string_add(tos2((byte *)"*"),
                              string_left(sizeof_typ, sizeof_typ.len - 1));
    };

    Parser_check(p, main__Token_rpar);

    Parser_gen(p, _STR("%.*s)", sizeof_typ.len, sizeof_typ.str));

    Parser_fgen(p, _STR("%.*s)", sizeof_typ.len, sizeof_typ.str));

    return tos2((byte *)"int");

  } else if ((tok == main__Token_amp) || (tok == main__Token_dot) ||
             (tok == main__Token_mul)) { /* case */

    return Parser_name_expr(p);

  } else if ((tok == main__Token_name)) { /* case */

    if (string_eq(p->lit, tos2((byte *)"map")) &&
        Parser_peek(p) == main__Token_lsbr) {

      return Parser_map_init(p);
    };

    if (string_eq(p->lit, tos2((byte *)"json")) &&
        Parser_peek(p) == main__Token_dot) {

      if (!(_IN(string, tos2((byte *)"json"), p->table->imports))) {

        Parser_error(p, tos2((byte *)"undefined: `json`, use `import json`"));
      };

      return Parser_js_decode(p);
    };

    typ = Parser_name_expr(p);

    return typ;

  } else if ((tok == main__Token_key_default)) { /* case */

    Parser_next(p);

    Parser_next(p);

    string name = Parser_check_name(p);

    if (string_ne(name, tos2((byte *)"T"))) {

      Parser_error(p, tos2((byte *)"default needs T"));
    };

    Parser_gen(p, tos2((byte *)"default(T)"));

    Parser_next(p);

    return tos2((byte *)"T");

  } else if ((tok == main__Token_lpar)) { /* case */

    Parser_gen(p, tos2((byte *)"("));

    Parser_check(p, main__Token_lpar);

    typ = Parser_bool_expression(p);

    if (!p->ptr_cast) {

      Parser_check(p, main__Token_rpar);
    };

    p->ptr_cast = 0;

    Parser_gen(p, tos2((byte *)")"));

    return typ;

  } else if ((tok == main__Token_chartoken)) { /* case */

    Parser_char_expr(p);

    typ = tos2((byte *)"byte");

    return typ;

  } else if ((tok == main__Token_str)) { /* case */

    Parser_string_expr(p);

    typ = tos2((byte *)"string");

    return typ;

  } else if ((tok == main__Token_key_false)) { /* case */

    typ = tos2((byte *)"bool");

    Parser_gen(p, tos2((byte *)"0"));

    Parser_fgen(p, tos2((byte *)"false"));

  } else if ((tok == main__Token_key_true)) { /* case */

    typ = tos2((byte *)"bool");

    Parser_gen(p, tos2((byte *)"1"));

    Parser_fgen(p, tos2((byte *)"true"));

  } else if ((tok == main__Token_lsbr)) { /* case */

    return Parser_array_init(p);

  } else if ((tok == main__Token_lcbr)) { /* case */

    if (Parser_peek(p) == main__Token_str) {

      return Parser_map_init(p);
    };

    return Parser_assoc(p);

  } else if ((tok == main__Token_key_if)) { /* case */

    typ = Parser_if_st(p, 1, 0);

    return typ;

  } else if ((tok == main__Token_key_match)) { /* case */

    typ = Parser_match_statement(p, 1);

    return typ;

  } else { // default:

    if (p->pref->is_verbose || p->pref->is_debug) {

      Token next = Parser_peek(p);

      printf("prev=%.*s\n", Token_str(p->prev_tok).len,
             Token_str(p->prev_tok).str);

      printf("next=%.*s\n", Token_str(next).len, Token_str(next).str);
    };

    Parser_error(p, _STR("unexpected token: `%.*s`", Token_str(p->tok).len,
                         Token_str(p->tok).str));
  };

  Parser_next(p);

  return typ;
}
string Parser_assoc(Parser *p) {

  Parser_next(p);

  string name = Parser_check_name(p);

  if (!Fn_known_var(p->cur_fn, name)) {

    Parser_error(p, _STR("unknown variable `%.*s`", name.len, name.str));
  };

  Var var = Fn_find_var(&/* ? */ *p->cur_fn, name);

  Parser_check(p, main__Token_pipe);

  Parser_gen(p, _STR("(%.*s){", var.typ.len, var.typ.str));

  array_string fields =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  while (p->tok != main__Token_rcbr) {

    string field = Parser_check_name(p);

    _PUSH(&fields, (field), tmp234, string);

    Parser_gen(p, _STR(".%.*s = ", field.len, field.str));

    Parser_check(p, main__Token_colon);

    Parser_bool_expression(p);

    Parser_gen(p, tos2((byte *)","));

    if (p->tok != main__Token_rcbr) {

      Parser_check(p, main__Token_comma);
    };
  };

  Type T = Table_find_type(&/* ? */ *p->table, var.typ);

  array_Var tmp236 = T.fields;
  ;
  for (int tmp237 = 0; tmp237 < tmp236.len; tmp237++) {
    Var ffield = ((Var *)tmp236.data)[tmp237];

    string f = ffield.name;

    if (_IN(string, f, fields)) {

      continue;
    };

    Parser_gen(p, _STR(".%.*s = %.*s . %.*s,", f.len, f.str, name.len, name.str,
                       f.len, f.str));
  };

  Parser_check(p, main__Token_rcbr);

  Parser_gen(p, tos2((byte *)"}"));

  return var.typ;

  v_array_free(fields); // close_scope free
}
void Parser_char_expr(Parser *p) {

  Parser_gen(p, _STR("\'%.*s\'", p->lit.len, p->lit.str));

  Parser_next(p);
}
string format_str(string _str) {

  string str = string_replace(_str, tos2((byte *)"\""), tos2((byte *)"\\\""));

#ifdef _WIN32

  str = string_replace(str, tos2((byte *)"\r\n"), tos2((byte *)"\\n"));

#endif
  ;

  str = string_replace(str, tos2((byte *)"\n"), tos2((byte *)"\\n"));

  return str;
}
void Parser_string_expr(Parser *p) {

  string str = p->lit;

  if (Parser_peek(p) != main__Token_dollar) {

    Parser_fgen(p, _STR("\'%.*s\'", str.len, str.str));

    string f = format_str(str);

    if (p->calling_c ||
        (p->pref->translated && string_eq(p->mod, tos2((byte *)"main")))) {

      Parser_gen(p, _STR("\"%.*s\"", f.len, f.str));

    } else if (p->is_sql) {

      Parser_gen(p, _STR("\'%.*s\'", str.len, str.str));

    } else {

      Parser_gen(p, _STR("tos2((byte*)\"%.*s\")", f.len, f.str));
    };

    Parser_next(p);

    return;
  };

  p->is_alloc = 1;

  string args = tos2((byte *)"\"");

  string format = tos2((byte *)"\"");

  Parser_fgen(p, tos2((byte *)"\'"));

  bool complex_inter = 0;

  while (p->tok == main__Token_str) {

    Parser_fgen(p, p->lit);

    p->lit = string_replace(p->lit, tos2((byte *)"%"), tos2((byte *)"%%"));

    format = string_add(format, format_str(p->lit));

    Parser_next(p);

    if (p->tok != main__Token_dollar) {

      continue;
    };

    Parser_check(p, main__Token_dollar);

    if (Parser_peek(p) != main__Token_str) {

      Parser_fgen(p, tos2((byte *)"{"));

      complex_inter = 1;
    };

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    string val = CGen_end_tmp(p->cgen);

    val = string_trim_space(val);

    args = string_add(args, _STR(", %.*s", val.len, val.str));

    if (string_eq(typ, tos2((byte *)"string"))) {

      args = string_add(args, _STR(".len, %.*s.str", val.len, val.str));
    };

    if (string_eq(typ, tos2((byte *)"ustring"))) {

      args = string_add(args, _STR(".len, %.*s.s.str", val.len, val.str));
    };

    if (string_eq(typ, tos2((byte *)"bool"))) {
    };

    bool custom = p->tok == main__Token_colon;

    if (custom) {

      string cformat = tos2((byte *)"");

      Parser_next(p);

      if (p->tok == main__Token_dot) {

        cformat = string_add(cformat, tos2((byte *)"."));

        Parser_next(p);
      };

      if (p->tok == main__Token_minus) {

        cformat = string_add(cformat, tos2((byte *)"-"));

        Parser_next(p);
      };

      cformat = string_add(cformat, p->lit);

      Parser_next(p);

      string fspec = p->lit;

      cformat = string_add(cformat, fspec);

      if (string_eq(fspec, tos2((byte *)"s"))) {

        if (string_ne(typ, tos2((byte *)"string"))) {

          Parser_error(
              p, _STR("only v strings can be formatted with a :%.*s format, "
                      "but you have given \"%.*s\", which has type %.*s.",
                      cformat.len, cformat.str, val.len, val.str, typ.len,
                      typ.str));
        };

        args = string_add(
            string_all_before_last(args, _STR("%.*s.len, %.*s.str", val.len,
                                              val.str, val.len, val.str)),
            _STR("%.*s.str", val.len, val.str));
      };

      format = string_add(format, _STR("%%%.*s", cformat.len, cformat.str));

      Parser_next(p);

    } else {

      string f = Parser_typ_to_fmt(p, typ, 0);

      if (string_eq(f, tos2((byte *)""))) {

        bool is_array = string_starts_with(typ, tos2((byte *)"array_"));

        Type typ2 = Table_find_type(&/* ? */ *p->table, typ);

        bool has_str_method = Table_type_has_method(
            &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ2,
            tos2((byte *)"str"));

        if (is_array || has_str_method) {

          if (is_array && !has_str_method) {

            Parser_gen_array_str(p, typ2);
          };

          args = string_add(string_all_before_last(args, val),
                            _STR("%.*s_str(%.*s).len, %.*s_str(%.*s).str",
                                 typ.len, typ.str, val.len, val.str, typ.len,
                                 typ.str, val.len, val.str));

          format = string_add(format, tos2((byte *)"%.*s "));

        } else {

          Parser_error(
              p, _STR("unhandled sprintf format \"%.*s\" ", typ.len, typ.str));
        };
      };

      format = string_add(format, f);
    };
  };

  if (complex_inter) {

    Parser_fgen(p, tos2((byte *)"}"));
  };

  Parser_fgen(p, tos2((byte *)"\'"));

  if (p->cgen->nogen) {

    return;
  };

#ifndef _WIN32

  string cur_line = string_trim_space(p->cgen->cur_line);

  if (string_eq(cur_line, tos2((byte *)"println (")) &&
      p->tok != main__Token_plus) {

    CGen_resetln(p->cgen, string_replace(cur_line, tos2((byte *)"println ("),
                                         tos2((byte *)"printf(")));

    Parser_gen(p,
               _STR("%.*s\\n%.*s", format.len, format.str, args.len, args.str));

    return;
  };

#endif
  ;

  if (p->tok == main__Token_not) {

    Parser_check(p, main__Token_not);

    Parser_gen(p, _STR("_STR_TMP(%.*s%.*s)", format.len, format.str, args.len,
                       args.str));

  } else {

    Parser_gen(
        p, _STR("_STR(%.*s%.*s)", format.len, format.str, args.len, args.str));
  };
}
string Parser_map_init(Parser *p) {

  string keys_gen = tos2((byte *)"");

  string vals_gen = tos2((byte *)"");

  string val_type = tos2((byte *)"");

  if (p->tok == main__Token_lcbr) {

    Parser_check(p, main__Token_lcbr);

    int i = 0;

    while (1) {

      string key = p->lit;

      keys_gen = string_add(keys_gen,
                            _STR("tos2((byte*)\"%.*s\"), ", key.len, key.str));

      Parser_check(p, main__Token_str);

      Parser_check(p, main__Token_colon);

      CGen_start_tmp(p->cgen);

      string t = Parser_bool_expression(p);

      if (i == 0) {

        val_type = t;
      };

      i++;

      if (string_ne(val_type, t)) {

        if (!Parser_check_types_no_throw(p, val_type, t)) {

          Parser_error(p, _STR("bad map element type `%.*s` instead of `%.*s`",
                               val_type.len, val_type.str, t.len, t.str));
        };
      };

      string val_expr = CGen_end_tmp(p->cgen);

      vals_gen =
          string_add(vals_gen, _STR("%.*s, ", val_expr.len, val_expr.str));

      if (p->tok == main__Token_rcbr) {

        Parser_check(p, main__Token_rcbr);

        break;
      };

      if (p->tok == main__Token_comma) {

        Parser_check(p, main__Token_comma);
      };
    };

    Parser_gen(p, string_add(_STR("new_map_init(%d, sizeof(%.*s), ", i,
                                  val_type.len, val_type.str),
                             _STR("(string[]){ %.*s }, (%.*s []){ %.*s } )",
                                  keys_gen.len, keys_gen.str, val_type.len,
                                  val_type.str, vals_gen.len, vals_gen.str)));

    string typ = _STR("map_%.*s", val_type.len, val_type.str);

    Parser_register_map(p, typ);

    return typ;
  };

  Parser_next(p);

  Parser_check(p, main__Token_lsbr);

  string key_type = Parser_check_name(p);

  if (string_ne(key_type, tos2((byte *)"string"))) {

    Parser_error(p, tos2((byte *)"only string key maps allowed for now"));
  };

  Parser_check(p, main__Token_rsbr);

  val_type = Parser_get_type(p);

  string typ = _STR("map_%.*s", val_type.len, val_type.str);

  Parser_register_map(p, typ);

  Parser_gen(p, _STR("new_map(1, sizeof(%.*s))", val_type.len, val_type.str));

  if (p->tok == main__Token_lcbr) {

    Parser_check(p, main__Token_lcbr);

    Parser_check(p, main__Token_rcbr);

    println(
        string_add(_STR("warning: %.*s:%d ", p->file_name.len, p->file_name.str,
                        p->scanner->line_nr),
                   tos2((byte *)"initializaing maps no longer requires `{}`")));
  };

  return typ;
}
string Parser_array_init(Parser *p) {

  p->is_alloc = 1;

  Parser_check(p, main__Token_lsbr);

  bool is_integer = p->tok == main__Token_number;

  bool is_const_len = 0;

  if (p->tok == main__Token_name) {

    Var c = Table_find_const(&/* ? */ *p->table,
                             Parser_prepend_mod(&/* ? */ *p, p->lit));

    if (string_ne(c.name, tos2((byte *)"")) &&
        string_eq(c.typ, tos2((byte *)"int")) &&
        Parser_peek(p) == main__Token_rsbr && !p->inside_const) {

      is_integer = 1;

      is_const_len = 1;
    };
  };

  string lit = p->lit;

  string typ = tos2((byte *)"");

  int new_arr_ph = CGen_add_placeholder(p->cgen);

  int i = 0;

  int pos = p->cgen->cur_line.len;

  while (p->tok != main__Token_rsbr) {

    string val_typ = Parser_bool_expression(p);

    if (i == 0) {

      typ = val_typ;

      if (is_integer && p->tok == main__Token_rsbr &&
          Parser_peek(p) == main__Token_name) {

        byte nextc = string_at(p->scanner->text, p->scanner->pos + 1);

        if (!byte_is_space(nextc)) {

          Parser_check(p, main__Token_rsbr);

          string array_elem_typ = Parser_get_type(p);

          if (Table_known_type(&/* ? */ *p->table, array_elem_typ)) {

            CGen_resetln(p->cgen, tos2((byte *)""));

            Parser_gen(p, tos2((byte *)"{0}"));

            if (is_const_len) {

              return _STR("[%.*s__%.*s]%.*s", p->mod.len, p->mod.str, lit.len,
                          lit.str, array_elem_typ.len, array_elem_typ.str);
            };

            return _STR("[%.*s]%.*s", lit.len, lit.str, array_elem_typ.len,
                        array_elem_typ.str);

          } else {

            Parser_error(p, _STR("bad type `%.*s`", array_elem_typ.len,
                                 array_elem_typ.str));
          };
        };
      };
    };

    if (string_ne(val_typ, typ)) {

      if (!Parser_check_types_no_throw(p, val_typ, typ)) {

        Parser_error(p, _STR("bad array element type `%.*s` instead of `%.*s`",
                             val_typ.len, val_typ.str, typ.len, typ.str));
      };
    };

    if (p->tok != main__Token_rsbr && p->tok != main__Token_semicolon) {

      Parser_gen(p, tos2((byte *)", "));

      Parser_check(p, main__Token_comma);

      Parser_fspace(p);
    };

    i++;

    if (i == 1 && p->tok == main__Token_semicolon) {

      Parser_check_space(p, main__Token_semicolon);

      string val = string_right(p->cgen->cur_line, pos);

      CGen_resetln(p->cgen, string_left(p->cgen->cur_line, pos));

      Parser_gen(p, _STR("array_repeat(& (%.*s[]){ %.*s }, ", typ.len, typ.str,
                         val.len, val.str));

      Parser_check_types(p, Parser_bool_expression(p), tos2((byte *)"int"));

      Parser_gen(p, _STR(", sizeof(%.*s) )", typ.len, typ.str));

      Parser_check(p, main__Token_rsbr);

      return _STR("array_%.*s", typ.len, typ.str);
    };
  };

  Parser_check(p, main__Token_rsbr);

  if (p->tok != main__Token_name && i == 0) {

    Parser_error(p,
                 tos2((byte *)"specify array type: `[]typ` instead of `[]`"));
  };

  if (p->tok == main__Token_name && i == 0) {

    typ = Parser_get_type(p);
  };

  bool no_alloc = p->tok == main__Token_not;

  if (no_alloc) {

    Parser_next(p);
  };

  bool is_fixed_size = p->tok == main__Token_not;

  if (is_fixed_size) {

    Parser_next(p);

    Parser_gen(p, tos2((byte *)" }"));

    if (!Parser_first_pass(&/* ? */ *p)) {

      if (p->inside_const) {

        CGen_set_placeholder(p->cgen, new_arr_ph, tos2((byte *)"{"));

      } else {

        CGen_set_placeholder(p->cgen, new_arr_ph,
                             _STR("(%.*s[]) {", typ.len, typ.str));
      };
    };

    return _STR("[%d]%.*s", i, typ.len, typ.str);
  };

  string new_arr = tos2((byte *)"new_array_from_c_array");

  if (no_alloc) {

    new_arr = string_add(new_arr, tos2((byte *)"_no_alloc"));
  };

  if (i == 0 && string_ne(p->pref->ccompiler, tos2((byte *)"tcc"))) {

    Parser_gen(p, tos2((byte *)" 0 })"));

  } else {

    Parser_gen(p, tos2((byte *)" })"));
  };

  if (!Parser_first_pass(&/* ? */ *p)) {

    string cast = (string_eq(p->pref->ccompiler, tos2((byte *)"tcc")))
                      ? (_STR("(%.*s[%d])", typ.len, typ.str, i))
                      : (_STR("(%.*s[])", typ.len, typ.str));

    CGen_set_placeholder(p->cgen, new_arr_ph,
                         _STR("%.*s(%d, %d, sizeof(%.*s), %.*s { ", new_arr.len,
                              new_arr.str, i, i, typ.len, typ.str, cast.len,
                              cast.str));
  };

  typ = _STR("array_%.*s", typ.len, typ.str);

  Parser_register_array(p, typ);

  return typ;
}
string Parser_struct_init(Parser *p, string typ, bool is_c_struct_init) {

  p->is_struct_init = 1;

  Type t = Table_find_type(&/* ? */ *p->table, typ);

  if (is_c_struct_init) {

    p->is_c_struct_init = 1;

    if (t.cat != main__TypeCategory_c_typedef) {

      CGen_insert_before(p->cgen, tos2((byte *)"struct /*c struct init*/"));
    };
  };

  Parser_next(p);

  strings__Builder_cut(&/* ? */ p->scanner->fmt_out, typ.len);

  bool ptr = string_contains(typ, tos2((byte *)"*"));

  if (string_eq(typ, tos2((byte *)"tm"))) {

    array_set(&/*q*/ p->cgen->lines, p->cgen->lines.len - 1,
              &(string[]){tos2((byte *)"")});
  };

  Parser_check(p, main__Token_lcbr);

  string no_star = string_replace(typ, tos2((byte *)"*"), tos2((byte *)""));

  if (!ptr) {

    if (p->is_c_struct_init) {

      if (p->tok == main__Token_rcbr) {

        p->is_empty_c_struct_init = 1;

        Parser_check(p, main__Token_rcbr);

        return typ;
      };

      Parser_gen(p, _STR("(struct %.*s) {", typ.len, typ.str));

      p->is_c_struct_init = 0;

    } else {

      Parser_gen(p, _STR("(%.*s) {", typ.len, typ.str));
    };

  } else {

    if (p->tok == main__Token_not) {

      Parser_next(p);

      Parser_gen(p, tos2((byte *)"0"));

      Parser_check(p, main__Token_rcbr);

      return typ;
    };

    Parser_gen(p, _STR("(%.*s*)memdup(&(%.*s)  {", no_star.len, no_star.str,
                       no_star.len, no_star.str));
  };

  bool did_gen_something = 0;

  array_string inited_fields =
      new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  Token peek = Parser_peek(p);

  if (peek == main__Token_colon || p->tok == main__Token_rcbr) {

    while (p->tok != main__Token_rcbr) {

      string field = (string_ne(typ, tos2((byte *)"Option")))
                         ? (Table_var_cgen_name(p->table, Parser_check_name(p)))
                         : (Parser_check_name(p));

      if (!Parser_first_pass(&/* ? */ *p) &&
          !Type_has_field(&/* ? */ t, field)) {

        Parser_error(p, _STR("`%.*s` has no field `%.*s`", t.name.len,
                             t.name.str, field.len, field.str));
      };

      if (array_string_contains(inited_fields, field)) {

        Parser_error(p, _STR("already initialized field `%.*s` in `%.*s`",
                             field.len, field.str, t.name.len, t.name.str));
      };

      Var f = Type_find_field(&/* ? */ t, field);

      _PUSH(&inited_fields, (field), tmp291, string);

      Parser_gen(p, _STR(".%.*s = ", field.len, field.str));

      Parser_check(p, main__Token_colon);

      Parser_fspace(p);

      Parser_check_types(p, Parser_bool_expression(p), f.typ);

      if (p->tok == main__Token_comma) {

        Parser_next(p);
      };

      if (p->tok != main__Token_rcbr) {

        Parser_gen(p, tos2((byte *)","));
      };

      Parser_fgenln(p, tos2((byte *)""));

      did_gen_something = 1;
    };

    if (t.fields.len != inited_fields.len && inited_fields.len > 0) {

      Parser_gen(p, tos2((byte *)","));
    };

    array_Var tmp292 = t.fields;
    ;
    for (int i = 0; i < tmp292.len; i++) {
      Var field = ((Var *)tmp292.data)[i];

      if (array_string_contains(inited_fields, field.name)) {

        continue;
      };

      string field_typ = field.typ;

      if (!p->builtin_mod && string_ends_with(field_typ, tos2((byte *)"*")) &&
          string_contains(field_typ, tos2((byte *)"Cfg"))) {

        Parser_error(p, _STR("pointer field `%.*s.%.*s` must be initialized",
                             typ.len, typ.str, field.name.len, field.name.str));
      };

      if (string_starts_with(field_typ, tos2((byte *)"map_"))) {

        Parser_gen(p, _STR(".%.*s = new_map(1, sizeof( %.*s ))", field.name.len,
                           field.name.str, string_right(field_typ, 4).len,
                           string_right(field_typ, 4).str));

        _PUSH(&inited_fields, (field.name), tmp294, string);

        if (i != t.fields.len - 1) {

          Parser_gen(p, tos2((byte *)","));
        };

        did_gen_something = 1;

        continue;
      };

      string def_val = type_default(field_typ);

      if (string_ne(def_val, tos2((byte *)"")) &&
          string_ne(def_val, tos2((byte *)"{0}"))) {

        Parser_gen(p, _STR(".%.*s = %.*s", field.name.len, field.name.str,
                           def_val.len, def_val.str));

        if (i != t.fields.len - 1) {

          Parser_gen(p, tos2((byte *)","));
        };
      };

      did_gen_something = 1;
    };

  } else {

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    if (T.fields.len == 0 && string_ne(T.parent, tos2((byte *)""))) {

      T = Table_find_type(&/* ? */ *p->table, T.parent);
    };

    array_Var tmp297 = T.fields;
    ;
    for (int i = 0; i < tmp297.len; i++) {
      Var ffield = ((Var *)tmp297.data)[i];

      string expr_typ = Parser_bool_expression(p);

      if (!Parser_check_types_no_throw(p, expr_typ, ffield.typ)) {

        Parser_error(
            p, _STR("field value #%d `%.*s` has type `%.*s`, got `%.*s` ",
                    i + 1, ffield.name.len, ffield.name.str, ffield.typ.len,
                    ffield.typ.str, expr_typ.len, expr_typ.str));
      };

      if (i < T.fields.len - 1) {

        if (p->tok != main__Token_comma) {

          Parser_error(
              p, _STR("too few values in `%.*s` literal (%d instead of %d)",
                      typ.len, typ.str, i + 1, T.fields.len));
        };

        Parser_gen(p, tos2((byte *)","));

        Parser_next(p);
      };
    };

    if (p->tok == main__Token_comma) {

      Parser_next(p);
    };

    if (p->tok != main__Token_rcbr) {

      Parser_error(p,
                   _STR("too many fields initialized: `%.*s` has %d field(s)",
                        typ.len, typ.str, T.fields.len));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    Parser_gen(p, tos2((byte *)"0"));
  };

  Parser_gen(p, tos2((byte *)"}"));

  if (ptr) {

    Parser_gen(p, _STR(", sizeof(%.*s))", no_star.len, no_star.str));
  };

  Parser_check(p, main__Token_rcbr);

  p->is_struct_init = 0;

  return typ;

  v_array_free(inited_fields); // close_scope free
}
string Parser_cast(Parser *p, string typ) {

  Parser_next(p);

  int pos = CGen_add_placeholder(p->cgen);

  if (p->tok == main__Token_rpar) {

    p->ptr_cast = 1;

    Parser_next(p);
  };

  Parser_check(p, main__Token_lpar);

  p->expected_type = typ;

  string expr_typ = Parser_bool_expression(p);

  bool casting_voidptr_to_value = string_eq(expr_typ, tos2((byte *)"void*")) &&
                                  string_ne(typ, tos2((byte *)"int")) &&
                                  string_ne(typ, tos2((byte *)"byteptr")) &&
                                  !string_ends_with(typ, tos2((byte *)"*"));

  p->expected_type = tos2((byte *)"");

  bool is_byteptr = string_eq(expr_typ, tos2((byte *)"byte*")) ||
                    string_eq(expr_typ, tos2((byte *)"byteptr"));

  bool is_bytearr = string_eq(expr_typ, tos2((byte *)"array_byte"));

  if (string_eq(typ, tos2((byte *)"string"))) {

    if (is_byteptr || is_bytearr) {

      if (p->tok == main__Token_comma) {

        Parser_check(p, main__Token_comma);

        CGen_set_placeholder(p->cgen, pos, tos2((byte *)"tos((byte *)"));

        if (is_bytearr) {

          Parser_gen(p, tos2((byte *)".data"));
        };

        Parser_gen(p, tos2((byte *)", "));

        Parser_check_types(p, Parser_expression(p), tos2((byte *)"int"));

      } else {

        if (is_bytearr) {

          Parser_gen(p, tos2((byte *)".data"));
        };

        CGen_set_placeholder(p->cgen, pos, tos2((byte *)"tos2((byte *)"));
      };

    } else if (string_eq(expr_typ, tos2((byte *)"int"))) {

      Parser_error(
          p, _STR("cannot cast `%.*s` to `%.*s`, use `str()` method instead",
                  expr_typ.len, expr_typ.str, typ.len, typ.str));

    } else {

      Parser_error(p, _STR("cannot cast `%.*s` to `%.*s`", expr_typ.len,
                           expr_typ.str, typ.len, typ.str));
    };

  } else if (string_eq(typ, tos2((byte *)"byte")) &&
             string_eq(expr_typ, tos2((byte *)"string"))) {

    Parser_error(
        p, _STR("cannot cast `%.*s` to `%.*s`, use backquotes `` to create a "
                "`%.*s` or access the value of an index of `%.*s` using []",
                expr_typ.len, expr_typ.str, typ.len, typ.str, typ.len, typ.str,
                expr_typ.len, expr_typ.str));

  } else if (casting_voidptr_to_value) {

    CGen_set_placeholder(p->cgen, pos, _STR("*(%.*s*)(", typ.len, typ.str));

  } else {

    CGen_set_placeholder(p->cgen, pos, _STR("(%.*s)(", typ.len, typ.str));
  };

  Parser_check(p, main__Token_rpar);

  Parser_gen(p, tos2((byte *)")"));

  return typ;
}
string Parser_get_tmp(Parser *p) {

  p->tmp_cnt++;

  return _STR("tmp%d", p->tmp_cnt);
}
int Parser_get_tmp_counter(Parser *p) {

  p->tmp_cnt++;

  return p->tmp_cnt;
}
string Parser_if_st(Parser *p, bool is_expr, int elif_depth) {

  if (is_expr) {

    p->inside_if_expr = 1;

    Parser_gen(p, tos2((byte *)"("));

  } else {

    Parser_gen(p, tos2((byte *)"if ("));

    Parser_fgen(p, tos2((byte *)"if "));
  };

  Parser_next(p);

  Parser_check_types(p, Parser_bool_expression(p), tos2((byte *)"bool"));

  if (is_expr) {

    Parser_gen(p, tos2((byte *)") ? ("));

  } else {

    Parser_genln(p, tos2((byte *)") {"));
  };

  Parser_fgen(p, tos2((byte *)" "));

  Parser_check(p, main__Token_lcbr);

  string typ = tos2((byte *)"");

  if (p->tok == main__Token_key_if && p->inside_if_expr) {

    typ = Parser_factor(p);

    Parser_next(p);

  } else {

    typ = Parser_statements(p);
  };

  bool if_returns = p->returns;

  p->returns = 0;

  if (p->tok == main__Token_key_else) {

    Parser_fgenln(p, tos2((byte *)""));

    Parser_check(p, main__Token_key_else);

    Parser_fspace(p);

    if (p->tok == main__Token_key_if) {

      if (is_expr) {

        Parser_gen(p, tos2((byte *)") : ("));

        string nested = Parser_if_st(p, is_expr, elif_depth + 1);

        bool nested_returns = p->returns;

        p->returns = if_returns && nested_returns;

        return nested;

      } else {

        Parser_gen(p, tos2((byte *)" else "));

        string nested = Parser_if_st(p, is_expr, 0);

        bool nested_returns = p->returns;

        p->returns = if_returns && nested_returns;

        return nested;
      };
    };

    if (is_expr) {

      Parser_gen(p, tos2((byte *)") : ("));

    } else {

      Parser_genln(p, tos2((byte *)" else { "));
    };

    Parser_check(p, main__Token_lcbr);

    string first_typ = typ;

    typ = Parser_statements(p);

    p->inside_if_expr = 0;

    if (is_expr) {

      Parser_check_types(p, first_typ, typ);

      Parser_gen(p, strings__repeat(')', elif_depth + 1));
    };

    bool else_returns = p->returns;

    p->returns = if_returns && else_returns;

    return typ;
  };

  p->inside_if_expr = 0;

  if (Parser_fileis(&/* ? */ *p, tos2((byte *)"test_test"))) {

    printf("if ret typ=\"%.*s\" line=%d\n", typ.len, typ.str,
           p->scanner->line_nr);
  };

  return typ;
}
void Parser_for_st(Parser *p) {

  Parser_check(p, main__Token_key_for);

  Parser_fgen(p, tos2((byte *)" "));

  p->for_expr_cnt++;

  Token next_tok = Parser_peek(p);

  Fn_open_scope(p->cur_fn);

  if (p->tok == main__Token_lcbr) {

    Parser_gen(p, tos2((byte *)"while (1) {"));

  } else if (p->tok == main__Token_key_mut) {

    Parser_error(p, tos2((byte *)"`mut` is not required in for loops"));

  } else if (next_tok == main__Token_decl_assign ||
             next_tok == main__Token_assign ||
             p->tok == main__Token_semicolon) {

    Parser_genln(p, tos2((byte *)"for ("));

    if (next_tok == main__Token_decl_assign) {

      Parser_var_decl(p);

    } else if (p->tok != main__Token_semicolon) {

      Parser_statement(p, 0);
    };

    Parser_check(p, main__Token_semicolon);

    Parser_gen(p, tos2((byte *)" ; "));

    Parser_fgen(p, tos2((byte *)" "));

    if (p->tok != main__Token_semicolon) {

      Parser_bool_expression(p);
    };

    Parser_check(p, main__Token_semicolon);

    Parser_gen(p, tos2((byte *)" ; "));

    Parser_fgen(p, tos2((byte *)" "));

    if (p->tok != main__Token_lcbr) {

      Parser_statement(p, 0);
    };

    Parser_genln(p, tos2((byte *)") { "));

  } else if (Parser_peek(p) == main__Token_comma) {

    string i = Parser_check_name(p);

    Parser_check(p, main__Token_comma);

    string val = Parser_check_name(p);

    Parser_fgen(p, tos2((byte *)" "));

    Parser_check(p, main__Token_key_in);

    Parser_fgen(p, tos2((byte *)" "));

    string tmp = Parser_get_tmp(p);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    bool is_arr = string_starts_with(typ, tos2((byte *)"array_"));

    bool is_map = string_starts_with(typ, tos2((byte *)"map_"));

    bool is_str = string_eq(typ, tos2((byte *)"string"));

    if (!is_arr && !is_str && !is_map) {

      Parser_error(p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    string expr = CGen_end_tmp(p->cgen);

    Parser_genln(p, _STR("%.*s %.*s = %.*s ;", typ.len, typ.str, tmp.len,
                         tmp.str, expr.len, expr.str));

    int pad = (is_arr) ? (6) : (4);

    string var_typ =
        (is_str) ? (tos2((byte *)"byte")) : (string_right(typ, pad));

    Var val_var = (Var){.name = val,
                        .typ = var_typ,
                        .ptr = string_contains(typ, tos2((byte *)"*")),
                        .is_arg = 0,
                        .is_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos((byte *)"", 0),
                        .is_mut = 0,
                        .is_alloc = 0,
                        .ref = 0,
                        .parent_fn = tos((byte *)"", 0),
                        .mod = tos((byte *)"", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .is_changed = 0,
                        .scope_level = 0};

    Parser_register_var(p, val_var);

    if (is_arr) {

      Var i_var = (Var){.name = i,
                        .typ = tos2((byte *)"int"),
                        .is_mut = 1,
                        .is_changed = 1,
                        .is_arg = 0,
                        .is_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos((byte *)"", 0),
                        .is_alloc = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos((byte *)"", 0),
                        .mod = tos((byte *)"", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .scope_level = 0};

      Parser_register_var(p, i_var);

      Parser_genln(p, _STR(";\nfor (int %.*s = 0; %.*s < %.*s .len; %.*s ++) {",
                           i.len, i.str, i.len, i.str, tmp.len, tmp.str, i.len,
                           i.str));

      Parser_genln(p,
                   _STR("%.*s %.*s = ((%.*s *) %.*s . data)[%.*s];",
                        var_typ.len, var_typ.str, val.len, val.str, var_typ.len,
                        var_typ.str, tmp.len, tmp.str, i.len, i.str));

    } else if (is_map) {

      Var i_var = (Var){.name = i,
                        .typ = tos2((byte *)"string"),
                        .is_mut = 1,
                        .is_changed = 1,
                        .is_arg = 0,
                        .is_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos((byte *)"", 0),
                        .is_alloc = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos((byte *)"", 0),
                        .mod = tos((byte *)"", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .scope_level = 0};

      Parser_register_var(p, i_var);

      Parser_genln(p, _STR("array_string keys_%.*s = map_keys(& %.*s ); ",
                           tmp.len, tmp.str, tmp.len, tmp.str));

      Parser_genln(p, _STR("for (int l = 0; l < keys_%.*s .len; l++) {",
                           tmp.len, tmp.str));

      Parser_genln(p, _STR("  string %.*s = ((string*)keys_%.*s .data)[l];",
                           i.len, i.str, tmp.len, tmp.str));

      string def = type_default(typ);

      Parser_genln(p, _STR("%.*s %.*s = %.*s; map_get(%.*s, %.*s, & %.*s);",
                           var_typ.len, var_typ.str, val.len, val.str, def.len,
                           def.str, tmp.len, tmp.str, i.len, i.str, val.len,
                           val.str));

    } else if (is_str) {

      Var i_var = (Var){.name = i,
                        .typ = tos2((byte *)"byte"),
                        .is_mut = 1,
                        .is_changed = 1,
                        .is_arg = 0,
                        .is_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos((byte *)"", 0),
                        .is_alloc = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos((byte *)"", 0),
                        .mod = tos((byte *)"", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .scope_level = 0};

      Parser_register_var(p, i_var);

      Parser_genln(p, _STR("array_byte bytes_%.*s = string_bytes( %.*s );",
                           tmp.len, tmp.str, tmp.len, tmp.str));

      Parser_genln(p, _STR(";\nfor (int %.*s = 0; %.*s < %.*s .len; %.*s ++) {",
                           i.len, i.str, i.len, i.str, tmp.len, tmp.str, i.len,
                           i.str));

      Parser_genln(p,
                   _STR("%.*s %.*s = ((%.*s *) bytes_%.*s . data)[%.*s];",
                        var_typ.len, var_typ.str, val.len, val.str, var_typ.len,
                        var_typ.str, tmp.len, tmp.str, i.len, i.str));
    };

  } else if (Parser_peek(p) == main__Token_key_in) {

    string val = Parser_check_name(p);

    Parser_fgen(p, tos2((byte *)" "));

    Parser_check(p, main__Token_key_in);

    Parser_fspace(p);

    string tmp = Parser_get_tmp(p);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    string expr = CGen_end_tmp(p->cgen);

    bool is_range = p->tok == main__Token_dotdot;

    string range_end = tos2((byte *)"");

    if (is_range) {

      Parser_check_types(p, typ, tos2((byte *)"int"));

      Parser_check_space(p, main__Token_dotdot);

      CGen_start_tmp(p->cgen);

      Parser_check_types(p, Parser_bool_expression(p), tos2((byte *)"int"));

      range_end = CGen_end_tmp(p->cgen);
    };

    bool is_arr = string_contains(typ, tos2((byte *)"array"));

    bool is_str = string_eq(typ, tos2((byte *)"string"));

    if (!is_arr && !is_str && !is_range) {

      Parser_error(p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    Parser_genln(p, _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len,
                         tmp.str, expr.len, expr.str));

    string var_type = tos2((byte *)"");

    if (is_arr) {

      var_type = string_right(typ, 6);

    } else if (is_str) {

      var_type = tos2((byte *)"byte");

    } else if (is_range) {

      var_type = tos2((byte *)"int");
    };

    Var val_var = (Var){.name = val,
                        .typ = var_type,
                        .ptr = string_contains(typ, tos2((byte *)"*")),
                        .is_changed = 1,
                        .is_arg = 0,
                        .is_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos((byte *)"", 0),
                        .is_mut = 0,
                        .is_alloc = 0,
                        .ref = 0,
                        .parent_fn = tos((byte *)"", 0),
                        .mod = tos((byte *)"", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .scope_level = 0};

    Parser_register_var(p, val_var);

    string i = Parser_get_tmp(p);

    if (is_range) {

      Parser_genln(p, _STR(";\nfor (int %.*s = %.*s; %.*s < %.*s; %.*s++) {",
                           i.len, i.str, tmp.len, tmp.str, i.len, i.str,
                           range_end.len, range_end.str, i.len, i.str));

    } else {

      Parser_genln(p, _STR(";\nfor (int %.*s = 0; %.*s < %.*s .len; %.*s ++) {",
                           i.len, i.str, i.len, i.str, tmp.len, tmp.str, i.len,
                           i.str));
    };

    if (is_arr) {

      Parser_genln(p,
                   _STR("%.*s %.*s = ((%.*s *) %.*s.data)[%.*s];", var_type.len,
                        var_type.str, val.len, val.str, var_type.len,
                        var_type.str, tmp.len, tmp.str, i.len, i.str));

    } else if (is_str) {

      Parser_genln(p,
                   _STR("%.*s %.*s = ((%.*s *) %.*s.str)[%.*s];", var_type.len,
                        var_type.str, val.len, val.str, var_type.len,
                        var_type.str, tmp.len, tmp.str, i.len, i.str));

    } else if (is_range) {

      Parser_genln(p, _STR("%.*s %.*s = %.*s;", var_type.len, var_type.str,
                           val.len, val.str, i.len, i.str));
    };

  } else {

    Parser_gen(p, tos2((byte *)"while ("));

    Parser_check_types(p, Parser_bool_expression(p), tos2((byte *)"bool"));

    Parser_genln(p, tos2((byte *)") {"));
  };

  Parser_fspace(p);

  Parser_check(p, main__Token_lcbr);

  Parser_genln(p, tos2((byte *)""));

  Parser_statements(p);

  Parser_close_scope(p);

  p->for_expr_cnt--;

  p->returns = 0;
}
void Parser_switch_statement(Parser *p) {

  if (p->tok == main__Token_key_switch) {

    Parser_check(p, main__Token_key_switch);

  } else {

    Parser_check(p, main__Token_key_match);
  };

  CGen_start_tmp(p->cgen);

  string typ = Parser_bool_expression(p);

  string expr = CGen_end_tmp(p->cgen);

  Parser_check(p, main__Token_lcbr);

  int i = 0;

  bool all_cases_return = 1;

  while (p->tok == main__Token_key_case || p->tok == main__Token_key_default ||
         Parser_peek(p) == main__Token_arrow ||
         p->tok == main__Token_key_else) {

    p->returns = 0;

    if (p->tok == main__Token_key_default || p->tok == main__Token_key_else) {

      Parser_genln(p, tos2((byte *)"else  { // default:"));

      if (p->tok == main__Token_key_default) {

        Parser_check(p, main__Token_key_default);

        Parser_check(p, main__Token_colon);

      } else {

        Parser_check(p, main__Token_key_else);

        Parser_check(p, main__Token_arrow);
      };

      Parser_statements(p);

      p->returns = all_cases_return && p->returns;

      return;
    };

    if (i > 0) {

      Parser_gen(p, tos2((byte *)"else "));
    };

    Parser_gen(p, tos2((byte *)"if ("));

    bool got_comma = 0;

    while (1) {

      if (got_comma) {

        Parser_gen(p, tos2((byte *)") ||  "));
      };

      if (string_eq(typ, tos2((byte *)"string"))) {

        Parser_gen(p, _STR("string_eq(%.*s, ", expr.len, expr.str));

      } else {

        Parser_gen(p, _STR("(%.*s == ", expr.len, expr.str));
      };

      if (p->tok == main__Token_key_case || p->tok == main__Token_key_default) {

        Parser_check(p, p->tok);
      };

      Parser_bool_expression(p);

      if (p->tok != main__Token_comma) {

        break;
      };

      Parser_check(p, main__Token_comma);

      got_comma = 1;
    };

    if (p->tok == main__Token_colon) {

      Parser_check(p, main__Token_colon);

    } else {

      Parser_check(p, main__Token_arrow);
    };

    Parser_gen(p, tos2((byte *)")) {"));

    Parser_genln(p, tos2((byte *)"/* case */"));

    Parser_statements(p);

    all_cases_return = all_cases_return && p->returns;

    i++;
  };

  p->returns = 0;
}
string Parser_match_statement(Parser *p, bool is_expr) {

  Parser_check(p, main__Token_key_match);

  CGen_start_tmp(p->cgen);

  string typ = Parser_bool_expression(p);

  string expr = CGen_end_tmp(p->cgen);

  string tmp_var = Parser_get_tmp(p);

  CGen_insert_before(p->cgen,
                     _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp_var.len,
                          tmp_var.str, expr.len, expr.str));

  Parser_check(p, main__Token_lcbr);

  int i = 0;

  bool all_cases_return = 1;

  string res_typ = tos2((byte *)"");

  while (p->tok != main__Token_rcbr) {

    if (p->tok == main__Token_key_else) {

      Parser_check(p, main__Token_key_else);

      Parser_check(p, main__Token_arrow);

      if (i == 0) {

        if (is_expr) {

          bool got_brace = p->tok == main__Token_lcbr;

          if (got_brace) {

            Parser_check(p, main__Token_lcbr);
          };

          Parser_gen(p, tos2((byte *)"( "));

          res_typ = Parser_bool_expression(p);

          Parser_gen(p, tos2((byte *)" )"));

          if (got_brace) {

            Parser_check(p, main__Token_rcbr);
          };

          string tmp351 = res_typ;
          { Parser_check(p, main__Token_rcbr); }
          return tmp351;
          ;

        } else {

          p->returns = 0;

          Parser_check(p, main__Token_lcbr);

          Parser_genln(p, tos2((byte *)"{ "));

          Parser_statements(p);

          p->returns = all_cases_return && p->returns;

          string tmp352 = tos2((byte *)"");
          { Parser_check(p, main__Token_rcbr); }
          return tmp352;
          ;
        };
      };

      if (is_expr) {

        Parser_gen(p, tos2((byte *)":("));

        bool got_brace = p->tok == main__Token_lcbr;

        if (got_brace) {

          Parser_check(p, main__Token_lcbr);
        };

        Parser_check_types(p, Parser_bool_expression(p), res_typ);

        if (got_brace) {

          Parser_check(p, main__Token_rcbr);
        };

        Parser_gen(p, strings__repeat(')', i + 1));

        string tmp354 = res_typ;
        { Parser_check(p, main__Token_rcbr); }
        return tmp354;
        ;

      } else {

        p->returns = 0;

        Parser_genln(p, tos2((byte *)"else // default:"));

        Parser_check(p, main__Token_lcbr);

        Parser_genln(p, tos2((byte *)"{ "));

        Parser_statements(p);

        p->returns = all_cases_return && p->returns;

        string tmp355 = tos2((byte *)"");
        { Parser_check(p, main__Token_rcbr); }
        return tmp355;
        ;
      };
    };

    if (i > 0) {

      if (is_expr) {

        Parser_gen(p, tos2((byte *)": ("));

      } else {

        Parser_gen(p, tos2((byte *)"else "));
      };

    } else if (is_expr) {

      Parser_gen(p, tos2((byte *)"("));
    };

    if (is_expr) {

      Parser_gen(p, tos2((byte *)"("));

    } else {

      Parser_gen(p, tos2((byte *)"if ("));
    };

    bool got_comma = 0;

    while (1) {

      if (got_comma) {

        Parser_gen(p, tos2((byte *)") || ("));
      };

      if (string_eq(typ, tos2((byte *)"string"))) {

        Parser_gen(p, _STR("string_eq(%.*s, ", tmp_var.len, tmp_var.str));

      } else {

        Parser_gen(p, _STR("(%.*s == ", tmp_var.len, tmp_var.str));
      };

      p->expected_type = typ;

      Parser_check_types(p, Parser_bool_expression(p), typ);

      p->expected_type = tos2((byte *)"");

      if (p->tok != main__Token_comma) {

        if (got_comma) {

          Parser_gen(p, tos2((byte *)") "));
        };

        break;
      };

      Parser_check(p, main__Token_comma);

      got_comma = 1;
    };

    Parser_gen(p, tos2((byte *)") )"));

    Parser_check(p, main__Token_arrow);

    if (is_expr) {

      Parser_gen(p, tos2((byte *)"? ("));

      Parser_check(p, main__Token_lcbr);

      if (i == 0) {

        res_typ = Parser_bool_expression(p);

      } else {

        Parser_check_types(p, Parser_bool_expression(p), res_typ);
      };

      Parser_check(p, main__Token_rcbr);

      Parser_gen(p, tos2((byte *)")"));

    } else {

      p->returns = 0;

      Parser_check(p, main__Token_lcbr);

      Parser_genln(p, tos2((byte *)"{ "));

      Parser_statements(p);

      all_cases_return = all_cases_return && p->returns;
    };

    i++;
  };

  if (is_expr) {

    Parser_error(p, tos2((byte *)"Match expession requires \"else\""));
  };

  p->returns = 0;

  string tmp357 = tos2((byte *)"");
  { Parser_check(p, main__Token_rcbr); }
  return tmp357;
  ;

  { Parser_check(p, main__Token_rcbr); }
}
void Parser_assert_statement(Parser *p) {

  if (Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  Parser_check(p, main__Token_key_assert);

  Parser_fspace(p);

  string tmp = Parser_get_tmp(p);

  Parser_gen(p, _STR("bool %.*s = ", tmp.len, tmp.str));

  Parser_check_types(p, Parser_bool_expression(p), tos2((byte *)"bool"));

  string filename =
      string_replace(p->file_path, tos2((byte *)"\\"), tos2((byte *)"\\\\"));

  Parser_genln(
      p,
      _STR(
          ";\n\nif (!%.*s) {\n  println(tos2((byte *)\"\\x1B[31mFAILED: %.*s() "
          "in %.*s:%d\\x1B[0m\"));\ng_test_ok = 0 ;\n	// TODO\n	// "
          "Maybe print all vars in a test function if it fails?\n}\nelse {\n  "
          "//puts(\"\\x1B[32mPASSED: %.*s()\\x1B[0m\");\n}",
          tmp.len, tmp.str, p->cur_fn->name.len, p->cur_fn->name.str,
          filename.len, filename.str, p->scanner->line_nr, p->cur_fn->name.len,
          p->cur_fn->name.str));
}
void Parser_return_st(Parser *p) {

  Parser_check(p, main__Token_key_return);

  Parser_fgen(p, tos2((byte *)" "));

  bool fn_returns = string_ne(p->cur_fn->typ, tos2((byte *)"void"));

  if (fn_returns) {

    if (p->tok == main__Token_rcbr) {

      Parser_error(p, _STR("`%.*s` needs to return `%.*s`", p->cur_fn->name.len,
                           p->cur_fn->name.str, p->cur_fn->typ.len,
                           p->cur_fn->typ.str));

    } else {

      int ph = CGen_add_placeholder(p->cgen);

      string expr_type = Parser_bool_expression(p);

      if (string_ends_with(p->cur_fn->typ, expr_type) &&
          string_starts_with(p->cur_fn->typ, tos2((byte *)"Option_"))) {

        string tmp = Parser_get_tmp(p);

        string ret = string_right(p->cgen->cur_line, ph);

        string typ = string_replace(expr_type, tos2((byte *)"Option_"),
                                    tos2((byte *)""));

        p->cgen->cur_line = _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);",
                                 expr_type.len, expr_type.str, tmp.len, tmp.str,
                                 typ.len, typ.str, ret.len, ret.str);

        CGen_resetln(p->cgen,
                     _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);", expr_type.len,
                          expr_type.str, tmp.len, tmp.str, expr_type.len,
                          expr_type.str, ret.len, ret.str));

        Parser_gen(p, _STR("return opt_ok(&%.*s, sizeof(%.*s))", tmp.len,
                           tmp.str, typ.len, typ.str));

      } else {

        string ret = string_right(p->cgen->cur_line, ph);

        string total_text = tos2((byte *)"");

        array_string tmp368 = p->cur_fn->defer_text;
        ;
        for (int tmp369 = 0; tmp369 < tmp368.len; tmp369++) {
          string text = ((string *)tmp368.data)[tmp369];

          if (string_ne(text, tos2((byte *)""))) {

            total_text = string_add(text, total_text);
          };
        };

        if (string_eq(total_text, tos2((byte *)"")) ||
            string_eq(expr_type, tos2((byte *)"void*"))) {

          if (string_eq(expr_type, _STR("%.*s*", p->cur_fn->typ.len,
                                        p->cur_fn->typ.str))) {

            CGen_resetln(p->cgen, _STR("return *%.*s", ret.len, ret.str));

          } else {

            CGen_resetln(p->cgen, _STR("return %.*s", ret.len, ret.str));
          };

        } else {

          string tmp = Parser_get_tmp(p);

          CGen_resetln(p->cgen,
                       _STR("%.*s %.*s = %.*s;\n", expr_type.len, expr_type.str,
                            tmp.len, tmp.str, ret.len, ret.str));

          Parser_genln(p, total_text);

          Parser_genln(p, _STR("return %.*s;", tmp.len, tmp.str));
        };
      };

      Parser_check_types(p, expr_type, p->cur_fn->typ);
    };

  } else {

    if (!p->is_vweb &&
        (p->tok == main__Token_name || p->tok == main__Token_number ||
         p->tok == main__Token_str)) {

      Parser_error(p, _STR("function `%.*s` should not return a value",
                           p->cur_fn->name.len, p->cur_fn->name.str));
    };

    if (string_eq(p->cur_fn->name, tos2((byte *)"main"))) {

      Parser_gen(p, tos2((byte *)"return 0"));

    } else {

      Parser_gen(p, tos2((byte *)"return"));
    };
  };

  p->returns = 1;
}
string prepend_mod(string mod, string name) {

  return _STR("%.*s__%.*s", mod.len, mod.str, name.len, name.str);
}
string Parser_prepend_mod(Parser *p, string name) {

  return prepend_mod(p->mod, name);
}
void Parser_go_statement(Parser *p) {

  Parser_check(p, main__Token_key_go);

  if (Parser_peek(p) == main__Token_dot) {

    string var_name = p->lit;

    Var v = Fn_find_var(&/* ? */ *p->cur_fn, var_name);

    Fn_mark_var_used(p->cur_fn, v);

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    Type typ = Table_find_type(&/* ? */ *p->table, v.typ);

    Fn method = Table_find_method(&/* ? */ *p->table,
                                  &/*112 EXP:"Type*" GOT:"Type" */ typ, p->lit);

    Parser_async_fn_call(p, method, 0, var_name, v.typ);

  } else {

    Fn f = Table_find_fn(&/* ? */ *p->table, p->lit);

    if (string_eq(f.name, tos2((byte *)"println"))) {

      Parser_error(p, tos2((byte *)"`go` cannot be used with `println`"));
    };

    Parser_async_fn_call(p, f, 0, tos2((byte *)""), tos2((byte *)""));
  };
}
void Parser_register_var(Parser *p, Var v) {

  if (v.line_nr == 0) {

    Fn_register_var(p->cur_fn, (Var){
                                   .line_nr = p->scanner->line_nr,
                                   .typ = v.typ,
                                   .name = v.name,
                                   .is_arg = v.is_arg,
                                   .is_const = v.is_const,
                                   .args = v.args,
                                   .attr = v.attr,
                                   .is_mut = v.is_mut,
                                   .is_alloc = v.is_alloc,
                                   .ptr = v.ptr,
                                   .ref = v.ref,
                                   .parent_fn = v.parent_fn,
                                   .mod = v.mod,
                                   .access_mod = v.access_mod,
                                   .is_global = v.is_global,
                                   .is_used = v.is_used,
                                   .is_changed = v.is_changed,
                                   .scope_level = v.scope_level,
                               });

  } else {

    Fn_register_var(p->cur_fn, v);
  };
}
string Parser_js_decode(Parser *p) {

  Parser_check(p, main__Token_name);

  Parser_check(p, main__Token_dot);

  string op = Parser_check_name(p);

  if (string_eq(op, tos2((byte *)"decode"))) {

    Parser_check(p, main__Token_lpar);

    string typ = Parser_get_type(p);

    Parser_check(p, main__Token_comma);

    CGen_start_tmp(p->cgen);

    Parser_check_types(p, Parser_bool_expression(p), tos2((byte *)"string"));

    string expr = CGen_end_tmp(p->cgen);

    Parser_check(p, main__Token_rpar);

    string tmp = Parser_get_tmp(p);

    string cjson_tmp = Parser_get_tmp(p);

    string decl = _STR("%.*s %.*s; ", typ.len, typ.str, tmp.len, tmp.str);

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    array_Var tmp383 = T.fields;
    ;
    for (int tmp384 = 0; tmp384 < tmp383.len; tmp384++) {
      Var field = ((Var *)tmp383.data)[tmp384];

      string def_val = type_default(field.typ);

      if (string_ne(def_val, tos2((byte *)""))) {

        decl = string_add(decl, _STR("%.*s . %.*s = OPTION_CAST(%.*s) %.*s;\n",
                                     tmp.len, tmp.str, field.name.len,
                                     field.name.str, field.typ.len,
                                     field.typ.str, def_val.len, def_val.str));
      };
    };

    Parser_gen_json_for_type(p, T);

    decl = string_add(decl,
                      _STR("cJSON* %.*s = json__json_parse(%.*s);",
                           cjson_tmp.len, cjson_tmp.str, expr.len, expr.str));

    CGen_insert_before(p->cgen, decl);

    Parser_gen(p, _STR("json__jsdecode_%.*s(%.*s, &%.*s); cJSON_Delete(%.*s);",
                       typ.len, typ.str, cjson_tmp.len, cjson_tmp.str, tmp.len,
                       tmp.str, cjson_tmp.len, cjson_tmp.str));

    string opt_type = _STR("Option_%.*s", typ.len, typ.str);

    _PUSH(&p->cgen->typedefs,
          (_STR("typedef Option %.*s;", opt_type.len, opt_type.str)), tmp387,
          string);

    Table_register_type(p->table, opt_type);

    return opt_type;

  } else if (string_eq(op, tos2((byte *)"encode"))) {

    Parser_check(p, main__Token_lpar);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    Parser_gen_json_for_type(p, T);

    string expr = CGen_end_tmp(p->cgen);

    Parser_check(p, main__Token_rpar);

    Parser_gen(p, _STR("json__json_print(json__jsencode_%.*s(%.*s))", typ.len,
                       typ.str, expr.len, expr.str));

    return tos2((byte *)"string");

  } else {

    Parser_error(p, _STR("bad json op \"%.*s\"", op.len, op.str));
  };

  return tos2((byte *)"");
}
void Parser_attribute(Parser *p) {

  Parser_check(p, main__Token_lsbr);

  if (p->tok == main__Token_key_interface) {

    Parser_check(p, main__Token_key_interface);

    Parser_check(p, main__Token_colon);

    p->attr = string_add(tos2((byte *)"interface:"), Parser_check_name(p));

  } else {

    p->attr = Parser_check_name(p);
  };

  Parser_check(p, main__Token_rsbr);

  if (p->tok == main__Token_func) {

    Parser_fn_decl(p);

    p->attr = tos2((byte *)"");

    return;

  } else if (p->tok == main__Token_key_struct) {

    Parser_struct_decl(p);

    p->attr = tos2((byte *)"");

    return;
  };

  Parser_error(p, tos2((byte *)"bad attribute usage"));
}
void Parser_defer_st(Parser *p) {

  Parser_check(p, main__Token_key_defer);

  Parser_check(p, main__Token_lcbr);

  int pos = p->cgen->lines.len;

  Parser_genln(p, tos2((byte *)"{"));

  Parser_statements(p);

  *(string *)array_last(p->cur_fn->defer_text) = string_add(
      array_string_join(array_right(p->cgen->lines, pos), tos2((byte *)"\n")),
      *(string *)array_last(p->cur_fn->defer_text));

  p->cgen->lines = array_left(p->cgen->lines, pos);

  CGen_resetln(p->cgen, tos2((byte *)""));
}
Type Parser_get_type2(Parser *p) {

  bool mul = 0;

  int nr_muls = 0;

  string typ = tos2((byte *)"");

  TypeCategory cat = main__TypeCategory_struct_;

  if (p->tok == main__Token_func) {

    Fn f = (Fn){.name = tos2((byte *)"_"),
                .mod = p->mod,
                .local_vars = new_array(0, 1, sizeof(Var)),
                .var_idx = 0,
                .args = new_array(0, 1, sizeof(Var)),
                .is_interface = 0,
                .scope_level = 0,
                .typ = tos((byte *)"", 0),
                .is_c = 0,
                .receiver_typ = tos((byte *)"", 0),
                .is_public = 0,
                .is_method = 0,
                .returns_error = 0,
                .is_decl = 0,
                .defer_text = new_array(0, 1, sizeof(string))};

    Parser_next(p);

    int line_nr = p->scanner->line_nr;

    Parser_fn_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

    if (p->scanner->line_nr == line_nr) {

      if (p->tok == main__Token_name) {

        f.typ = Parser_get_type(p);

      } else {

        f.typ = tos2((byte *)"void");
      };

    } else {

      f.typ = tos2((byte *)"void");
    };

    Type fn_typ = (Type){.name = Fn_typ_str(f),
                         .mod = p->mod,
                         .func = f,
                         .cat = main__TypeCategory_func,
                         .fields = new_array(0, 1, sizeof(Var)),
                         .methods = new_array(0, 1, sizeof(Fn)),
                         .parent = tos((byte *)"", 0),
                         .is_c = 0,
                         .enum_vals = new_array(0, 1, sizeof(string)),
                         .gen_types = new_array(0, 1, sizeof(string)),
                         .is_placeholder = 0,
                         .gen_str = 0};

    Table_register_type2(p->table, fn_typ);

    return fn_typ;
  };

  bool is_arr = 0;

  bool is_arr2 = 0;

  bool is_question = p->tok == main__Token_question;

  if (is_question) {

    Parser_check(p, main__Token_question);
  };

  if (p->tok == main__Token_lsbr) {

    Parser_check(p, main__Token_lsbr);

    if (p->tok == main__Token_number) {

      typ = _STR("[%.*s]", p->lit.len, p->lit.str);

      Parser_next(p);

    } else {

      is_arr = 1;
    };

    Parser_check(p, main__Token_rsbr);

    if (p->tok == main__Token_lsbr) {

      Parser_next(p);

      if (p->tok == main__Token_number) {

        typ = string_add(typ, _STR("[%.*s]", p->lit.len, p->lit.str));

        Parser_check(p, main__Token_number);

      } else {

        is_arr2 = 1;
      };

      Parser_check(p, main__Token_rsbr);
    };

    cat = main__TypeCategory_array;
  };

  if (!p->builtin_mod && p->tok == main__Token_name &&
      string_eq(p->lit, tos2((byte *)"map"))) {

    Parser_next(p);

    Parser_check(p, main__Token_lsbr);

    string key_type = Parser_check_name(p);

    if (string_ne(key_type, tos2((byte *)"string"))) {

      Parser_error(p, tos2((byte *)"maps only support string keys for now"));
    };

    Parser_check(p, main__Token_rsbr);

    string val_type = Parser_get_type(p);

    typ = _STR("map_%.*s", val_type.len, val_type.str);

    Parser_register_map(p, typ);

    return (Type){.name = typ,
                  .mod = tos((byte *)"", 0),
                  .fields = new_array(0, 1, sizeof(Var)),
                  .methods = new_array(0, 1, sizeof(Fn)),
                  .parent = tos((byte *)"", 0),
                  .is_c = 0,
                  .enum_vals = new_array(0, 1, sizeof(string)),
                  .gen_types = new_array(0, 1, sizeof(string)),
                  .is_placeholder = 0,
                  .gen_str = 0};
  };

  while (p->tok == main__Token_mul) {

    if (Parser_first_pass(&/* ? */ *p)) {

      Parser_warn(p, tos2((byte *)"use `&Foo` instead of `*Foo`"));
    };

    mul = 1;

    nr_muls++;

    Parser_check(p, main__Token_mul);
  };

  if (p->tok == main__Token_amp) {

    mul = 1;

    nr_muls++;

    Parser_check(p, main__Token_amp);
  };

  typ = string_add(typ, p->lit);

  if (!p->is_struct_init) {

    Parser_fgen(p, p->lit);
  };

  if (string_eq(p->lit, tos2((byte *)"C")) &&
      Parser_peek(p) == main__Token_dot) {

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    typ = p->lit;

  } else {

    if (Parser_peek(p) == main__Token_dot) {

      if (!p->builtin_mod &&
          FileImportTable_known_alias(&/* ? */ *p->import_table, typ)) {

        string mod =
            FileImportTable_resolve_alias(&/* ? */ *p->import_table, typ);

        if (string_contains(mod, tos2((byte *)"."))) {

          typ = string_replace(mod, tos2((byte *)"."), tos2((byte *)"_dot_"));
        };
      };

      Parser_next(p);

      Parser_check(p, main__Token_dot);

      typ = string_add(typ, _STR("__%.*s", p->lit.len, p->lit.str));
    };

    Type t = Table_find_type(&/* ? */ *p->table, typ);

    if (string_eq(t.name, tos2((byte *)"")) && !p->builtin_mod) {

      if (!string_contains(typ, tos2((byte *)"array_")) &&
          string_ne(p->mod, tos2((byte *)"main")) &&
          !string_contains(typ, tos2((byte *)"__")) &&
          !string_starts_with(typ, tos2((byte *)"["))) {

        typ = Parser_prepend_mod(&/* ? */ *p, typ);
      };

      t = Table_find_type(&/* ? */ *p->table, typ);

      if (string_eq(t.name, tos2((byte *)"")) && !p->pref->translated &&
          !Parser_first_pass(&/* ? */ *p) &&
          !string_starts_with(typ, tos2((byte *)"["))) {

        println(tos2((byte *)"get_type() bad type"));

        Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
      };
    };
  };

  if (string_eq(typ, tos2((byte *)"void"))) {

    Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
  };

  if (mul) {

    typ = string_add(typ, strings__repeat('*', nr_muls));
  };

  if (is_arr2) {

    typ = _STR("array_array_%.*s", typ.len, typ.str);

    Parser_register_array(p, typ);

  } else if (is_arr) {

    typ = _STR("array_%.*s", typ.len, typ.str);

    Parser_register_array(p, typ);
  };

  Parser_next(p);

  if (p->tok == main__Token_question || is_question) {

    typ = _STR("Option_%.*s", typ.len, typ.str);

    Table_register_type_with_parent(p->table, typ, tos2((byte *)"Option"));

    if (p->tok == main__Token_question) {

      Parser_next(p);
    };
  };

  if (string_last_index(typ, tos2((byte *)"__")) >
      string_index(typ, tos2((byte *)"__"))) {

    Parser_error(p, _STR("2 __ in gettype(): typ=\"%.*s\"", typ.len, typ.str));
  };

  return (Type){.name = typ,
                .cat = cat,
                .mod = tos((byte *)"", 0),
                .fields = new_array(0, 1, sizeof(Var)),
                .methods = new_array(0, 1, sizeof(Fn)),
                .parent = tos((byte *)"", 0),
                .is_c = 0,
                .enum_vals = new_array(0, 1, sizeof(string)),
                .gen_types = new_array(0, 1, sizeof(string)),
                .is_placeholder = 0,
                .gen_str = 0};
}
string sql_params2params_gen(array_string sql_params, array_string sql_types,
                             string qprefix) {

  string params_gen = tos2((byte *)"");

  array_string tmp2 = sql_params;
  ;
  for (int i = 0; i < tmp2.len; i++) {
    string mparam = ((string *)tmp2.data)[i];

    string param = string_trim_space(mparam);

    string paramtype = (*(string *)array__get(sql_types, i));

    if (byte_is_digit(string_at(param, 0))) {

      params_gen = string_add(
          params_gen, _STR("%.*sparams[%d] = int_str(%.*s).str;\n", qprefix.len,
                           qprefix.str, i, param.len, param.str));

    } else if (string_at(param, 0) == '\'') {

      string sparam = string_trim(param, tos2((byte *)"\'"));

      params_gen = string_add(params_gen,
                              _STR("%.*sparams[%d] = \"%.*s\";\n", qprefix.len,
                                   qprefix.str, i, sparam.len, sparam.str));

    } else {

      if (string_eq(paramtype, tos2((byte *)"int"))) {

        params_gen =
            string_add(params_gen,
                       _STR("%.*sparams[%d] = int_str( %.*s ).str;\n",
                            qprefix.len, qprefix.str, i, param.len, param.str));

      } else if (string_eq(paramtype, tos2((byte *)"string"))) {

        params_gen = string_add(params_gen, _STR("%.*sparams[%d] = %.*s.str;\n",
                                                 qprefix.len, qprefix.str, i,
                                                 param.len, param.str));

      } else {

        cerror(tos2((byte *)"orm: only int and string variable types are "
                            "supported in queries"));
      };
    };
  };

  return params_gen;
}
string Parser_select_query(Parser *p, int fn_ph) {

  string qprefix =
      string_add(string_replace(Parser_get_tmp(p), tos2((byte *)"tmp"),
                                tos2((byte *)"sql")),
                 tos2((byte *)"_"));

  p->sql_i = 0;

  p->sql_params = new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  p->sql_types = new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

  string q = tos2((byte *)"select ");

  Parser_check(p, main__Token_key_select);

  string n = Parser_check_name(p);

  if (string_eq(n, tos2((byte *)"count"))) {

    q = string_add(q, tos2((byte *)"count(*) from "));

    Parser_check_name(p);
  };

  string table_name = Parser_check_name(p);

  Type typ = Table_find_type(&/* ? */ *p->table, table_name);

  if (string_eq(typ.name, tos2((byte *)""))) {

    Parser_error(p,
                 _STR("unknown type `%.*s`", table_name.len, table_name.str));
  };

  array_Var fields = new_array_from_c_array(0, 0, sizeof(Var), (Var[]){0});

  array_Var tmp18 = typ.fields;
  ;
  for (int i = 0; i < tmp18.len; i++) {
    Var field = ((Var *)tmp18.data)[i];

    if (string_ne(field.typ, tos2((byte *)"string")) &&
        string_ne(field.typ, tos2((byte *)"int"))) {

      continue;
    };

    _PUSH(&fields, (field), tmp19, Var);
  };

  if (fields.len == 0) {

    Parser_error(p, _STR("V orm: select: empty fields in `%.*s`",
                         table_name.len, table_name.str));
  };

  if (string_ne((*(Var *)array__get(fields, 0)).name, tos2((byte *)"id"))) {

    Parser_error(p, _STR("V orm: `id int` must be the first field in `%.*s`",
                         table_name.len, table_name.str));
  };

  if (string_eq(n, tos2((byte *)"from"))) {

    array_Var tmp22 = fields;
    ;
    for (int i = 0; i < tmp22.len; i++) {
      Var field = ((Var *)tmp22.data)[i];

      q = string_add(q, field.name);

      if (i < fields.len - 1) {

        q = string_add(q, tos2((byte *)", "));
      };
    };

    q = string_add(q, tos2((byte *)" from "));
  };

  array_Var tmp23 = fields;
  ;
  for (int tmp24 = 0; tmp24 < tmp23.len; tmp24++) {
    Var field = ((Var *)tmp23.data)[tmp24];

    if (string_ne(field.typ, tos2((byte *)"string")) &&
        string_ne(field.typ, tos2((byte *)"int"))) {

      continue;
    };

    Fn_register_var(p->cur_fn, (Var){
                                   .is_used = 1,
                                   .typ = field.typ,
                                   .name = field.name,
                                   .is_arg = field.is_arg,
                                   .is_const = field.is_const,
                                   .args = field.args,
                                   .attr = field.attr,
                                   .is_mut = field.is_mut,
                                   .is_alloc = field.is_alloc,
                                   .ptr = field.ptr,
                                   .ref = field.ref,
                                   .parent_fn = field.parent_fn,
                                   .mod = field.mod,
                                   .line_nr = field.line_nr,
                                   .access_mod = field.access_mod,
                                   .is_global = field.is_global,
                                   .is_changed = field.is_changed,
                                   .scope_level = field.scope_level,
                               });
  };

  q = string_add(q, table_name);

  if (p->tok == main__Token_name && string_eq(p->lit, tos2((byte *)"where"))) {

    Parser_next(p);

    CGen_start_tmp(p->cgen);

    p->is_sql = 1;

    Parser_bool_expression(p);

    p->is_sql = 0;

    q = string_add(q,
                   string_add(tos2((byte *)" where "), CGen_end_tmp(p->cgen)));
  };

  bool query_one = 0;

  if (p->tok == main__Token_name && string_eq(p->lit, tos2((byte *)"limit"))) {

    Parser_next(p);

    CGen_start_tmp(p->cgen);

    p->is_sql = 1;

    Parser_bool_expression(p);

    p->is_sql = 0;

    string limit = CGen_end_tmp(p->cgen);

    q = string_add(q, string_add(tos2((byte *)" limit "), limit));

    if (string_eq(string_trim_space(limit), tos2((byte *)"1"))) {

      query_one = 1;
    };
  };

  printf("sql query=\"%.*s\"\n", q.len, q.str);

  CGen_insert_before(
      p->cgen, _STR("// DEBUG_SQL prefix: %.*s | fn_ph: %d | query: \"%.*s\" ",
                    qprefix.len, qprefix.str, fn_ph, q.len, q.str));

  if (string_eq(n, tos2((byte *)"count"))) {

    CGen_set_placeholder(p->cgen, fn_ph, tos2((byte *)"pg__DB_q_int("));

    Parser_gen(p, _STR(", tos2(\"%.*s\"))", q.len, q.str));

  } else {

    string tmp = Parser_get_tmp(p);

    strings__Builder obj_gen = strings__new_builder(300);

    array_Var tmp29 = fields;
    ;
    for (int i = 0; i < tmp29.len; i++) {
      Var field = ((Var *)tmp29.data)[i];

      string cast = tos2((byte *)"");

      if (string_eq(field.typ, tos2((byte *)"int"))) {

        cast = tos2((byte *)"v_string_int");
      };

      strings__Builder_writeln(&/* ? */ obj_gen,
                               _STR("%.*s%.*s . %.*s = %.*s( "
                                    "*(string*)array__get(%.*srow.vals, %d) );",
                                    qprefix.len, qprefix.str, tmp.len, tmp.str,
                                    field.name.len, field.name.str, cast.len,
                                    cast.str, qprefix.len, qprefix.str, i));
    };

    if (query_one) {

      string params_gen =
          sql_params2params_gen(p->sql_params, p->sql_types, qprefix);

      CGen_insert_before(
          p->cgen,
          _STR("\n\nchar* %.*sparams[%d];\n%.*s\n\nOption_%.*s "
               "opt_%.*s%.*s;\nvoid* %.*sres = PQexecParams(db.conn, \"%.*s\", "
               "%d, 0, %.*sparams, 0, 0, 0)  ;\narray_pg__Row %.*srows = "
               "pg__res_to_rows ( %.*sres ) ;\nOption_pg__Row opt_%.*srow = "
               "pg__rows_first_or_empty( %.*srows );\nif (! opt_%.*srow . ok ) "
               "{\n   opt_%.*s%.*s = v_error( opt_%.*srow . error );\n}else{\n "
               "  %.*s %.*s%.*s;\n   pg__Row %.*srow = *(pg__Row*) opt_%.*srow "
               ". data; \n%.*s\n   opt_%.*s%.*s = opt_ok( & %.*s%.*s, "
               "sizeof(%.*s) );\n}\n\n",
               qprefix.len, qprefix.str, p->sql_i, params_gen.len,
               params_gen.str, table_name.len, table_name.str, qprefix.len,
               qprefix.str, tmp.len, tmp.str, qprefix.len, qprefix.str, q.len,
               q.str, p->sql_i, qprefix.len, qprefix.str, qprefix.len,
               qprefix.str, qprefix.len, qprefix.str, qprefix.len, qprefix.str,
               qprefix.len, qprefix.str, qprefix.len, qprefix.str, qprefix.len,
               qprefix.str, tmp.len, tmp.str, qprefix.len, qprefix.str,
               table_name.len, table_name.str, qprefix.len, qprefix.str,
               tmp.len, tmp.str, qprefix.len, qprefix.str, qprefix.len,
               qprefix.str, strings__Builder_str(obj_gen).len,
               strings__Builder_str(obj_gen).str, qprefix.len, qprefix.str,
               tmp.len, tmp.str, qprefix.len, qprefix.str, tmp.len, tmp.str,
               table_name.len, table_name.str));

      CGen_resetln(p->cgen, _STR("opt_%.*s%.*s", qprefix.len, qprefix.str,
                                 tmp.len, tmp.str));

    } else {

      q = string_add(q, tos2((byte *)" order by id"));

      string params_gen =
          sql_params2params_gen(p->sql_params, p->sql_types, qprefix);

      CGen_insert_before(
          p->cgen,
          _STR("char* %.*sparams[%d];\n%.*s \n\nvoid* %.*sres = "
               "PQexecParams(db.conn, \"%.*s\", %d, 0, %.*sparams, 0, 0, 0)  "
               ";\narray_pg__Row %.*srows = pg__res_to_rows(%.*sres);\n\n// "
               "TODO preallocate \narray %.*sarr_%.*s = new_array(0, 0, "
               "sizeof(%.*s));\nfor (int i = 0; i < %.*srows.len; i++) {\n    "
               "pg__Row %.*srow = *(pg__Row*)array__get(%.*srows, i);\n    "
               "%.*s %.*s%.*s;\n    %.*s \n    _PUSH(&%.*sarr_%.*s, %.*s%.*s, "
               "%.*s2, %.*s);\n} \n",
               qprefix.len, qprefix.str, p->sql_i, params_gen.len,
               params_gen.str, qprefix.len, qprefix.str, q.len, q.str, p->sql_i,
               qprefix.len, qprefix.str, qprefix.len, qprefix.str, qprefix.len,
               qprefix.str, qprefix.len, qprefix.str, tmp.len, tmp.str,
               table_name.len, table_name.str, qprefix.len, qprefix.str,
               qprefix.len, qprefix.str, qprefix.len, qprefix.str,
               table_name.len, table_name.str, qprefix.len, qprefix.str,
               tmp.len, tmp.str, strings__Builder_str(obj_gen).len,
               strings__Builder_str(obj_gen).str, qprefix.len, qprefix.str,
               tmp.len, tmp.str, qprefix.len, qprefix.str, tmp.len, tmp.str,
               tmp.len, tmp.str, table_name.len, table_name.str));

      CGen_resetln(p->cgen, _STR("%.*sarr_%.*s", qprefix.len, qprefix.str,
                                 tmp.len, tmp.str));
    };
  };

  if (string_eq(n, tos2((byte *)"count"))) {

    return tos2((byte *)"int");

  } else if (query_one) {

    string opt_type = _STR("Option_%.*s", table_name.len, table_name.str);

    _PUSH(&p->cgen->typedefs,
          (_STR("typedef Option %.*s;", opt_type.len, opt_type.str)), tmp34,
          string);

    Table_register_type(p->table, opt_type);

    return opt_type;

  } else {

    Parser_register_array(p,
                          _STR("array_%.*s", table_name.len, table_name.str));

    return _STR("array_%.*s", table_name.len, table_name.str);
  };

  v_array_free(fields); // close_scope free
}
void Parser_insert_query(Parser *p, int fn_ph) {

  Parser_check_name(p);

  Parser_check(p, main__Token_lpar);

  string var_name = Parser_check_name(p);

  Parser_check(p, main__Token_rpar);

  Var var = Fn_find_var(&/* ? */ *p->cur_fn, var_name);

  Type typ = Table_find_type(&/* ? */ *p->table, var.typ);

  array_Var fields = new_array_from_c_array(0, 0, sizeof(Var), (Var[]){0});

  array_Var tmp39 = typ.fields;
  ;
  for (int i = 0; i < tmp39.len; i++) {
    Var field = ((Var *)tmp39.data)[i];

    if (string_ne(field.typ, tos2((byte *)"string")) &&
        string_ne(field.typ, tos2((byte *)"int"))) {

      continue;
    };

    _PUSH(&fields, (field), tmp40, Var);
  };

  if (fields.len == 0) {

    Parser_error(p, _STR("V orm: insert: empty fields in `%.*s`", var.typ.len,
                         var.typ.str));
  };

  if (string_ne((*(Var *)array__get(fields, 0)).name, tos2((byte *)"id"))) {

    Parser_error(p, _STR("V orm: `id int` must be the first field in `%.*s`",
                         var.typ.len, var.typ.str));
  };

  string table_name = var.typ;

  string sfields = tos2((byte *)"");

  string params = tos2((byte *)"");

  string vals = tos2((byte *)"");

  int nr_vals = 0;

  array_Var tmp48 = fields;
  ;
  for (int i = 0; i < tmp48.len; i++) {
    Var field = ((Var *)tmp48.data)[i];

    if (string_eq(field.name, tos2((byte *)"id"))) {

      continue;
    };

    sfields = string_add(sfields, field.name);

    vals = string_add(vals, string_add(tos2((byte *)"$"), int_str(i)));

    nr_vals++;

    params = string_add(params, _STR("params[%d] = ", i - 1));

    if (string_eq(field.typ, tos2((byte *)"string"))) {

      params = string_add(params,
                          _STR("%.*s . %.*s .str;\n", var_name.len,
                               var_name.str, field.name.len, field.name.str));

    } else if (string_eq(field.typ, tos2((byte *)"int"))) {

      params = string_add(params,
                          _STR("int_str(%.*s . %.*s).str;\n", var_name.len,
                               var_name.str, field.name.len, field.name.str));

    } else {

      Parser_error(p, _STR("V ORM: unsupported type `%.*s`", field.typ.len,
                           field.typ.str));
    };

    if (i < fields.len - 1) {

      sfields = string_add(sfields, tos2((byte *)", "));

      vals = string_add(vals, tos2((byte *)", "));
    };
  };

  CGen_insert_before(p->cgen,
                     string_add(_STR("char* params[%d];", nr_vals), params));

  CGen_set_placeholder(p->cgen, fn_ph, tos2((byte *)"PQexecParams( "));

  Parser_genln(p, _STR(".conn, \"insert into %.*s (%.*s) values (%.*s)\", "
                       "%d,\n0, params, 0, 0, 0)",
                       table_name.len, table_name.str, sfields.len, sfields.str,
                       vals.len, vals.str, nr_vals));

  v_array_free(fields); // close_scope free
}
bool Repl_checks(Repl *r, string line) {

  bool in_string = 0;

  bool was_indent = r->indent > 0;

  for (int i = 0; i < line.len; i++) {

    if (string_at(line, i) == '\'' &&
        (i == 0 || string_at(line, i - 1) != '\\')) {

      in_string = !in_string;
    };

    if (string_at(line, i) == '{' && !in_string) {

      r->indent++;
    };

    if (string_at(line, i) == '}' && !in_string) {

      r->indent--;

      if (r->indent == 0) {

        r->in_func = 0;
      };
    };

    if (i + 2 < line.len && r->indent == 0 && string_at(line, i + 1) == 'f' &&
        string_at(line, i + 2) == 'n') {

      r->in_func = 1;
    };
  };

  return r->in_func || (was_indent && r->indent <= 0) || r->indent > 0;
}
bool Repl_function_call(Repl *r, string line) {

  array_string tmp16 = r->functions_name;
  ;
  for (int tmp17 = 0; tmp17 < tmp16.len; tmp17++) {
    string function = ((string *)tmp16.data)[tmp17];

    if (string_starts_with(line, function)) {

      return 1;
    };
  };

  return 0;
}
void repl_help() {

  printf("\nV %.*s\n  help                   Displays this information.\n  "
         "Ctrl-C, Ctrl-D, exit   Exits the REPL.\n  clear                  "
         "Clears the screen.\n\n",
         main__Version.len, main__Version.str);
}
array_string run_repl() {

  printf("V %.*s\n", main__Version.len, main__Version.str);

  println(tos2((byte *)"Use Ctrl-C or `exit` to exit"));

  string file = tos2((byte *)".vrepl.v");

  string temp_file = tos2((byte *)".vrepl_temp.v");

  Repl r = (Repl){.indent = 0,
                  .in_func = 0,
                  .lines = new_array(0, 1, sizeof(string)),
                  .temp_lines = new_array(0, 1, sizeof(string)),
                  .functions_name = new_array(0, 1, sizeof(string)),
                  .functions = new_array(0, 1, sizeof(string))};

  string vexe = (*(string *)array__get(os__args, 0));

  while (1) {

    if (r.indent == 0) {

      print(tos2((byte *)">>> "));

    } else {

      print(tos2((byte *)"... "));
    };

    string line = os__get_raw_line();

    if (string_eq(string_trim_space(line), tos2((byte *)"")) &&
        string_ends_with(line, tos2((byte *)"\n"))) {

      continue;
    };

    line = string_trim_space(line);

    if (line.len == -1 || string_eq(line, tos2((byte *)"")) ||
        string_eq(line, tos2((byte *)"exit"))) {

      break;
    };

    if (string_eq(line, tos2((byte *)"\n"))) {

      continue;
    };

    if (string_eq(line, tos2((byte *)"clear"))) {

      term__erase_display(tos2((byte *)"2"));

      continue;
    };

    if (string_eq(line, tos2((byte *)"help"))) {

      repl_help();

      continue;
    };

    if (string_starts_with(line, tos2((byte *)"fn"))) {

      r.in_func = 1;

      _PUSH(
          &r.functions_name,
          (string_trim_space(string_all_before(
              string_all_after(line, tos2((byte *)"fn")), tos2((byte *)"(")))),
          tmp25, string);
    };

    bool was_func = r.in_func;

    if (Repl_checks(&/* ? */ r, line)) {

      if (r.in_func || was_func) {

        _PUSH(&r.functions, (line), tmp27, string);

      } else {

        _PUSH(&r.temp_lines, (line), tmp28, string);
      };

      if (r.indent > 0) {

        continue;
      };

      line = tos2((byte *)"");
    };

    if (string_starts_with(line, tos2((byte *)"print"))) {

      string source_code = string_add(
          string_add(
              string_add(array_string_join(r.functions, tos2((byte *)"\n")),
                         array_string_join(r.lines, tos2((byte *)"\n"))),
              tos2((byte *)"\n")),
          line);

      os__write_file(file, source_code);

      Option_os__Result tmp30 = os__exec(
          _STR("%.*s run %.*s -repl", vexe.len, vexe.str, file.len, file.str));
      if (!tmp30.ok) {
        string err = tmp30.error;

        cerror(err);

        array_string tmp31 =
            new_array_from_c_array(0, 0, sizeof(string), (string[]){0});
        {

          os__rm(file);

          os__rm(temp_file);

          os__rm(string_left(file, file.len - 2));

          os__rm(string_left(temp_file, temp_file.len - 2));
        }
        return tmp31;
        ;
      }
      os__Result s = *(os__Result *)tmp30.data;
      ;

      array_string vals = string_split(s.output, tos2((byte *)"\n"));

      for (int i = 0; i < vals.len; i++) {

        println((*(string *)array__get(vals, i)));
      };

    } else {

      string temp_line = line;

      bool temp_flag = 0;

      bool func_call = Repl_function_call(&/* ? */ r, line);

      if (!(string_contains(line, tos2((byte *)" ")) ||
            string_contains(line, tos2((byte *)":")) ||
            string_contains(line, tos2((byte *)"=")) ||
            string_contains(line, tos2((byte *)",")) ||
            string_eq(line, tos2((byte *)""))) &&
          !func_call) {

        temp_line = _STR("println(%.*s)", line.len, line.str);

        temp_flag = 1;
      };

      string temp_source_code = string_add(
          string_add(
              string_add(
                  string_add(array_string_join(r.functions, tos2((byte *)"\n")),
                             array_string_join(r.lines, tos2((byte *)"\n"))),
                  array_string_join(r.temp_lines, tos2((byte *)"\n"))),
              tos2((byte *)"\n")),
          temp_line);

      os__write_file(temp_file, temp_source_code);

      Option_os__Result tmp40 =
          os__exec(_STR("%.*s run %.*s -repl", vexe.len, vexe.str,
                        temp_file.len, temp_file.str));
      if (!tmp40.ok) {
        string err = tmp40.error;

        cerror(err);

        array_string tmp41 =
            new_array_from_c_array(0, 0, sizeof(string), (string[]){0});
        {

          os__rm(file);

          os__rm(temp_file);

          os__rm(string_left(file, file.len - 2));

          os__rm(string_left(temp_file, temp_file.len - 2));
        }
        return tmp41;
        ;
      }
      os__Result s = *(os__Result *)tmp40.data;
      ;

      if (!func_call && !s.exit_code) {

        while (r.temp_lines.len > 0) {

          if (!string_starts_with((*(string *)array__get(r.temp_lines, 0)),
                                  tos2((byte *)"print"))) {

            _PUSH(&r.lines, ((*(string *)array__get(r.temp_lines, 0))), tmp44,
                  string);
          };

          array_delete(&/* ? */ r.temp_lines, 0);
        };

        _PUSH(&r.lines, (line), tmp47, string);

      } else {

        while (r.temp_lines.len > 0) {

          array_delete(&/* ? */ r.temp_lines, 0);
        };
      };

      array_string vals = string_split(s.output, tos2((byte *)"\n"));

      for (int i = 0; i < vals.len; i++) {

        println((*(string *)array__get(vals, i)));
      };
    };
  };

  array_string tmp52 = r.lines;
  {

    os__rm(file);

    os__rm(temp_file);

    os__rm(string_left(file, file.len - 2));

    os__rm(string_left(temp_file, temp_file.len - 2));
  }
  return tmp52;
  ;

  {

    os__rm(file);

    os__rm(temp_file);

    os__rm(string_left(file, file.len - 2));

    os__rm(string_left(temp_file, temp_file.len - 2));
  }
}
Scanner *new_scanner(string file_path) {

  if (!os__file_exists(file_path)) {

    cerror(_STR("\"%.*s\" doesn\'t exist", file_path.len, file_path.str));
  };

  Option_string tmp1 = os__read_file(file_path);
  if (!tmp1.ok) {
    string err = tmp1.error;

    cerror(
        _STR("scanner: failed to open \"%.*s\"", file_path.len, file_path.str));

    return 0;
  }
  string raw_text = *(string *)tmp1.data;
  ;

  if (raw_text.len >= 3) {

    byte *c_text = raw_text.str;

    if (c_text[/*ptr*/ 0] /*rbyte 0*/ == 0xEF &&
        c_text[/*ptr*/ 1] /*rbyte 0*/ == 0xBB &&
        c_text[/*ptr*/ 2] /*rbyte 0*/ == 0xBF) {

      int offset_from_begin = 3;

      raw_text = tos(&/*112 EXP:"byte*" GOT:"byte" */ c_text
                         [/*ptr*/ offset_from_begin] /*rbyte 0*/,
                     strlen(c_text) - offset_from_begin);
    };
  };

  string text = raw_text;

  Scanner *scanner =
      (Scanner *)memdup(&(Scanner){.file_path = file_path,
                                   .text = text,
                                   .fmt_out = strings__new_builder(1000),
                                   .pos = 0,
                                   .line_nr = 0,
                                   .inside_string = 0,
                                   .dollar_start = 0,
                                   .dollar_end = 0,
                                   .debug = 0,
                                   .line_comment = tos((byte *)"", 0),
                                   .started = 0,
                                   .fmt_indent = 0,
                                   .fmt_line_empty = 0,
                                   .fn_name = tos((byte *)"", 0)},
                        sizeof(Scanner));

  return scanner;
}
ScanRes scan_res(Token tok, string lit) { return (ScanRes){tok, lit}; }
string Scanner_ident_name(Scanner *s) {

  int start = s->pos;

  while (1) {

    s->pos++;

    if (s->pos >= s->text.len) {

      break;
    };

    byte c = string_at(s->text, s->pos);

    if (!is_name_char(c) && !byte_is_digit(c)) {

      break;
    };
  };

  string name = string_substr(s->text, start, s->pos);

  s->pos--;

  return name;
}
string Scanner_ident_hex_number(Scanner *s) {

  int start_pos = s->pos;

  s->pos += 2;

  while (1) {

    if (s->pos >= s->text.len) {

      break;
    };

    byte c = string_at(s->text, s->pos);

    if (!byte_is_hex_digit(c)) {

      break;
    };

    s->pos++;
  };

  string number = string_substr(s->text, start_pos, s->pos);

  s->pos--;

  return number;
}
string Scanner_ident_oct_number(Scanner *s) {

  int start_pos = s->pos;

  while (1) {

    if (s->pos >= s->text.len) {

      break;
    };

    byte c = string_at(s->text, s->pos);

    if (byte_is_digit(c)) {

      if (!byte_is_oct_digit(c)) {

        Scanner_error(&/* ? */ *s, tos2((byte *)"malformed octal constant"));
      };

    } else {

      break;
    };

    s->pos++;
  };

  string number = string_substr(s->text, start_pos, s->pos);

  s->pos--;

  return number;
}
string Scanner_ident_dec_number(Scanner *s) {

  int start_pos = s->pos;

  while (s->pos < s->text.len && byte_is_digit(string_at(s->text, s->pos))) {

    s->pos++;
  };

  if (Scanner_expect(s, tos2((byte *)".."), s->pos)) {

    string number = string_substr(s->text, start_pos, s->pos);

    s->pos--;

    return number;
  };

  if (s->pos < s->text.len && string_at(s->text, s->pos) == '.') {

    s->pos++;

    while (s->pos < s->text.len && byte_is_digit(string_at(s->text, s->pos))) {

      s->pos++;
    };

    if (!s->inside_string && s->pos < s->text.len &&
        string_at(s->text, s->pos) == 'f') {

      Scanner_error(&/* ? */ *s, tos2((byte *)"no `f` is needed for floats"));
    };
  };

  bool has_exponential_part = 0;

  if (Scanner_expect(s, tos2((byte *)"e+"), s->pos) ||
      Scanner_expect(s, tos2((byte *)"e-"), s->pos)) {

    int exp_start_pos = s->pos += 2;

    while (s->pos < s->text.len && byte_is_digit(string_at(s->text, s->pos))) {

      s->pos++;
    };

    if (exp_start_pos == s->pos) {

      Scanner_error(&/* ? */ *s, tos2((byte *)"exponent has no digits"));
    };

    has_exponential_part = 1;
  };

  if (s->pos < s->text.len && string_at(s->text, s->pos) == '.') {

    if (has_exponential_part) {

      Scanner_error(&/* ? */ *s,
                    tos2((byte *)"exponential part should be integer"));

    } else {

      Scanner_error(&/* ? */ *s,
                    tos2((byte *)"too many decimal points in number"));
    };
  };

  string number = string_substr(s->text, start_pos, s->pos);

  s->pos--;

  return number;
}
string Scanner_ident_number(Scanner *s) {

  if (Scanner_expect(s, tos2((byte *)"0x"), s->pos)) {

    return Scanner_ident_hex_number(s);
  };

  if (Scanner_expect(s, tos2((byte *)"0."), s->pos) ||
      Scanner_expect(s, tos2((byte *)"0e"), s->pos)) {

    return Scanner_ident_dec_number(s);
  };

  if (string_at(s->text, s->pos) == '0') {

    return Scanner_ident_oct_number(s);
  };

  return Scanner_ident_dec_number(s);
}
bool Scanner_has_gone_over_line_end(Scanner s) {

  int i = s.pos - 1;

  while (i >= 0 && !byte_is_white(string_at(s.text, i))) {

    i--;
  };

  while (i >= 0 && byte_is_white(string_at(s.text, i))) {

    if (is_nl(string_at(s.text, i))) {

      return 1;
    };

    i--;
  };

  return 0;
}
void Scanner_skip_whitespace(Scanner *s) {

  while (s->pos < s->text.len && byte_is_white(string_at(s->text, s->pos))) {

    if (is_nl(string_at(s->text, s->pos)) &&
        !Scanner_expect(s, tos2((byte *)"\r\n"), s->pos - 1)) {

      s->line_nr++;
    };

    s->pos++;
  };
}
ScanRes Scanner_scan(Scanner *s) {

  if (string_ne(s->line_comment, tos2((byte *)""))) {
  };

  if (s->started) {

    s->pos++;
  };

  s->started = 1;

  if (s->pos >= s->text.len) {

    return scan_res(main__Token_eof, tos2((byte *)""));
  };

  if (!s->inside_string) {

    Scanner_skip_whitespace(s);
  };

  if (s->dollar_end) {

    if (string_at(s->text, s->pos) == '\'') {

      s->dollar_end = 0;

      return scan_res(main__Token_str, tos2((byte *)""));
    };

    s->dollar_end = 0;

    return scan_res(main__Token_str, Scanner_ident_string(s));
  };

  Scanner_skip_whitespace(s);

  if (s->pos >= s->text.len) {

    return scan_res(main__Token_eof, tos2((byte *)""));
  };

  byte c = string_at(s->text, s->pos);

  byte nextc = '\0';

  if (s->pos + 1 < s->text.len) {

    nextc = string_at(s->text, s->pos + 1);
  };

  if (is_name_char(c)) {

    string name = Scanner_ident_name(s);

    byte next_char =
        (s->pos + 1 < s->text.len) ? (string_at(s->text, s->pos + 1)) : ('\0');

    if (is_key(name)) {

      return scan_res(key_to_token(name), tos2((byte *)""));
    };

    if (s->inside_string) {

      if (next_char == '\'') {

        s->dollar_end = 1;

        s->dollar_start = 0;

        s->inside_string = 0;
      };
    };

    if (s->dollar_start && next_char != '.') {

      s->dollar_end = 1;

      s->dollar_start = 0;
    };

    if (s->pos == 0 && next_char == ' ') {

      s->pos++;
    };

    return scan_res(main__Token_name, name);

  } else if (byte_is_digit(c) || (c == '.' && byte_is_digit(nextc))) {

    string num = Scanner_ident_number(s);

    return scan_res(main__Token_number, num);
  };

  if ((c == '+')) { /* case */

    if (nextc == '+') {

      s->pos++;

      return scan_res(main__Token_inc, tos2((byte *)""));

    } else if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_plus_assign, tos2((byte *)""));
    };

    return scan_res(main__Token_plus, tos2((byte *)""));

  } else if ((c == '-')) { /* case */

    if (nextc == '-') {

      s->pos++;

      return scan_res(main__Token_dec, tos2((byte *)""));

    } else if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_minus_assign, tos2((byte *)""));
    };

    return scan_res(main__Token_minus, tos2((byte *)""));

  } else if ((c == '*')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_mult_assign, tos2((byte *)""));
    };

    return scan_res(main__Token_mul, tos2((byte *)""));

  } else if ((c == '^')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_xor_assign, tos2((byte *)""));
    };

    return scan_res(main__Token_xor, tos2((byte *)""));

  } else if ((c == '%')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_mod_assign, tos2((byte *)""));
    };

    return scan_res(main__Token_mod, tos2((byte *)""));

  } else if ((c == '?')) { /* case */

    return scan_res(main__Token_question, tos2((byte *)""));

  } else if ((c == '\'')) { /* case */

    return scan_res(main__Token_str, Scanner_ident_string(s));

  } else if ((c == '\`')) { /* case */

    return scan_res(main__Token_chartoken, Scanner_ident_char(s));

  } else if ((c == '(')) { /* case */

    return scan_res(main__Token_lpar, tos2((byte *)""));

  } else if ((c == ')')) { /* case */

    return scan_res(main__Token_rpar, tos2((byte *)""));

  } else if ((c == '[')) { /* case */

    return scan_res(main__Token_lsbr, tos2((byte *)""));

  } else if ((c == ']')) { /* case */

    return scan_res(main__Token_rsbr, tos2((byte *)""));

  } else if ((c == '{')) { /* case */

    if (s->inside_string) {

      return Scanner_scan(s);
    };

    return scan_res(main__Token_lcbr, tos2((byte *)""));

  } else if ((c == '$')) { /* case */

    return scan_res(main__Token_dollar, tos2((byte *)""));

  } else if ((c == '}')) { /* case */

    if (s->inside_string) {

      s->pos++;

      if (string_at(s->text, s->pos) == '\'') {

        s->inside_string = 0;

        return scan_res(main__Token_str, tos2((byte *)""));
      };

      return scan_res(main__Token_str, Scanner_ident_string(s));

    } else {

      return scan_res(main__Token_rcbr, tos2((byte *)""));
    };

  } else if ((c == '&')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_and_assign, tos2((byte *)""));
    };

    if (nextc == '&') {

      s->pos++;

      return scan_res(main__Token_and, tos2((byte *)""));
    };

    return scan_res(main__Token_amp, tos2((byte *)""));

  } else if ((c == '|')) { /* case */

    if (nextc == '|') {

      s->pos++;

      return scan_res(main__Token_logical_or, tos2((byte *)""));
    };

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_or_assign, tos2((byte *)""));
    };

    return scan_res(main__Token_pipe, tos2((byte *)""));

  } else if ((c == ',')) { /* case */

    return scan_res(main__Token_comma, tos2((byte *)""));

  } else if ((c == '@')) { /* case */

    s->pos++;

    string name = Scanner_ident_name(s);

    if (string_eq(name, tos2((byte *)"FN"))) {

      return scan_res(main__Token_str, s->fn_name);
    };

    if (string_eq(name, tos2((byte *)"FILE"))) {

      return scan_res(main__Token_str, os__realpath(s->file_path));
    };

    if (string_eq(name, tos2((byte *)"LINE"))) {

      return scan_res(main__Token_str, int_str((s->line_nr + 1)));
    };

    if (string_eq(name, tos2((byte *)"COLUMN"))) {

      return scan_res(main__Token_str,
                      int_str((Scanner_current_column(&/* ? */ *s))));
    };

    if (!is_key(name)) {

      Scanner_error(
          &/* ? */ *s,
          tos2((byte *)"@ must be used before keywords (e.g. `@type string`)"));
    };

    return scan_res(main__Token_name, name);

  } else if ((c == '\r')) { /* case */

    if (nextc == '\n') {

      s->pos++;

      return scan_res(main__Token_nl, tos2((byte *)""));
    };

  } else if ((c == '\n')) { /* case */

    return scan_res(main__Token_nl, tos2((byte *)""));

  } else if ((c == '.')) { /* case */

    if (nextc == '.') {

      s->pos++;

      return scan_res(main__Token_dotdot, tos2((byte *)""));
    };

    return scan_res(main__Token_dot, tos2((byte *)""));

  } else if ((c == '#')) { /* case */

    int start = s->pos + 1;

    while (s->pos < s->text.len && string_at(s->text, s->pos) != '\n') {

      s->pos++;
    };

    s->line_nr++;

    if (nextc == '!') {

      s->line_comment =
          string_trim_space(string_substr(s->text, start + 1, s->pos));

      Scanner_fgenln(s, _STR("// shebang line \"%.*s\"", s->line_comment.len,
                             s->line_comment.str));

      return Scanner_scan(s);
    };

    string hash = string_substr(s->text, start, s->pos);

    return scan_res(main__Token_hash, string_trim_space(hash));

  } else if ((c == '>')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_ge, tos2((byte *)""));

    } else if (nextc == '>') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return scan_res(main__Token_righ_shift_assign, tos2((byte *)""));
      };

      s->pos++;

      return scan_res(main__Token_righ_shift, tos2((byte *)""));

    } else {

      return scan_res(main__Token_gt, tos2((byte *)""));
    };

  } else if ((c == 0xE2)) { /* case */

    if (nextc == 0x89 && string_at(s->text, s->pos + 2) == 0xA0) {

      s->pos += 2;

      return scan_res(main__Token_ne, tos2((byte *)""));

    } else if (nextc == 0x89 && string_at(s->text, s->pos + 2) == 0xBD) {

      s->pos += 2;

      return scan_res(main__Token_le, tos2((byte *)""));

    } else if (nextc == 0xA9 && string_at(s->text, s->pos + 2) == 0xBE) {

      s->pos += 2;

      return scan_res(main__Token_ge, tos2((byte *)""));
    };

  } else if ((c == '<')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_le, tos2((byte *)""));

    } else if (nextc == '<') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return scan_res(main__Token_left_shift_assign, tos2((byte *)""));
      };

      s->pos++;

      return scan_res(main__Token_left_shift, tos2((byte *)""));

    } else {

      return scan_res(main__Token_lt, tos2((byte *)""));
    };

  } else if ((c == '=')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_eq, tos2((byte *)""));

    } else if (nextc == '>') {

      s->pos++;

      return scan_res(main__Token_arrow, tos2((byte *)""));

    } else {

      return scan_res(main__Token_assign, tos2((byte *)""));
    };

  } else if ((c == ':')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_decl_assign, tos2((byte *)""));

    } else {

      return scan_res(main__Token_colon, tos2((byte *)""));
    };

  } else if ((c == ';')) { /* case */

    return scan_res(main__Token_semicolon, tos2((byte *)""));

  } else if ((c == '!')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_ne, tos2((byte *)""));

    } else {

      return scan_res(main__Token_not, tos2((byte *)""));
    };

  } else if ((c == '~')) { /* case */

    return scan_res(main__Token_bit_not, tos2((byte *)""));

  } else if ((c == '/')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_div_assign, tos2((byte *)""));
    };

    if (nextc == '/') {

      int start = s->pos + 1;

      while (s->pos < s->text.len && string_at(s->text, s->pos) != '\n') {

        s->pos++;
      };

      s->line_nr++;

      s->line_comment = string_substr(s->text, start + 1, s->pos);

      s->line_comment = string_trim_space(s->line_comment);

      Scanner_fgenln(s, _STR("// %.*s \"%.*s\"", Token_str(s->prev_tok).len,
                             Token_str(s->prev_tok).str, s->line_comment.len,
                             s->line_comment.str));

      return Scanner_scan(s);
    };

    if (nextc == '*') {

      int start = s->pos;

      int nest_count = 1;

      while (nest_count > 0) {

        s->pos++;

        if (s->pos >= s->text.len) {

          s->line_nr--;

          Scanner_error(&/* ? */ *s, tos2((byte *)"comment not terminated"));
        };

        if (string_at(s->text, s->pos) == '\n') {

          s->line_nr++;

          continue;
        };

        if (Scanner_expect(s, tos2((byte *)"/*"), s->pos)) {

          nest_count++;

          continue;
        };

        if (Scanner_expect(s, tos2((byte *)"*/"), s->pos)) {

          nest_count--;
        };
      };

      s->pos++;

      int end = s->pos + 1;

      string comm = string_substr(s->text, start, end);

      Scanner_fgenln(s, comm);

      return Scanner_scan(s);
    };

    return scan_res(main__Token_div, tos2((byte *)""));
  };

#ifdef _WIN32

  if (c == '\0') {

    return scan_res(main__Token_eof, tos2((byte *)""));
  };

#endif
  ;

  string msg =
      _STR("invalid character `%.*s`", byte_str(c).len, byte_str(c).str);

  if (c == '"') {

    msg = string_add(msg, tos2((byte *)", use \' to denote strings"));
  };

  Scanner_error(&/* ? */ *s, msg);

  return scan_res(main__Token_eof, tos2((byte *)""));
}
int Scanner_find_current_line_start_position(Scanner *s) {

  if (s->pos >= s->text.len) {

    return s->pos;
  };

  int linestart = s->pos;

  while (1) {

    if (linestart <= 0) {

      break;
    };

    if (string_at(s->text, linestart) == 10 ||
        string_at(s->text, linestart) == 13) {

      break;
    };

    linestart--;
  };

  return linestart;
}
int Scanner_current_column(Scanner *s) {

  return s->pos - Scanner_find_current_line_start_position(&/* ? */ *s);
}
void Scanner_error(Scanner *s, string msg) {

  string fullpath = os__realpath(s->file_path);

  int column = Scanner_current_column(&/* ? */ *s);

  printf("%.*s:%d:%d: %.*s\n", fullpath.len, fullpath.str, s->line_nr + 1,
         column, msg.len, msg.str);

  v_exit(1);
}
int Scanner_count_symbol_before(Scanner s, int p, byte sym) {

  int count = 0;

  for (int i = p; i >= 0; i--) {

    if (string_at(s.text, i) != sym) {

      break;
    };

    count++;
  };

  return count;
}
string Scanner_ident_string(Scanner *s) {

  int start = s->pos;

  s->inside_string = 0;

  byte slash = '\\';

  while (1) {

    s->pos++;

    if (s->pos >= s->text.len) {

      break;
    };

    byte c = string_at(s->text, s->pos);

    byte prevc = string_at(s->text, s->pos - 1);

    if (c == '\'' &&
        (prevc != slash ||
         (prevc == slash && string_at(s->text, s->pos - 2) == slash))) {

      break;
    };

    if (c == '\n') {

      s->line_nr++;
    };

    if (c == '0' && s->pos > 2 && string_at(s->text, s->pos - 1) == '\\') {

      Scanner_error(&/* ? */ *s,
                    tos2((byte *)"0 character in a string literal"));
    };

    if (c == '0' && s->pos > 5 &&
        Scanner_expect(s, tos2((byte *)"\\x0"), s->pos - 3)) {

      Scanner_error(&/* ? */ *s,
                    tos2((byte *)"0 character in a string literal"));
    };

    if (c == '{' && prevc == '$' &&
        Scanner_count_symbol_before(*s, s->pos - 2, '\\') % 2 == 0) {

      s->inside_string = 1;

      s->pos -= 2;

      break;
    };

    if ((byte_is_letter(c) || c == '_') && prevc == '$' &&
        Scanner_count_symbol_before(*s, s->pos - 2, '\\') % 2 == 0) {

      s->inside_string = 1;

      s->dollar_start = 1;

      s->pos -= 2;

      break;
    };
  };

  string lit = tos2((byte *)"");

  if (string_at(s->text, start) == '\'') {

    start++;
  };

  int end = s->pos;

  if (s->inside_string) {

    end++;
  };

  if (start > s->pos) {

  } else {

    lit = string_substr(s->text, start, end);
  };

  return lit;
}
string Scanner_ident_char(Scanner *s) {

  int start = s->pos;

  byte slash = '\\';

  int len = 0;

  while (1) {

    s->pos++;

    if (s->pos >= s->text.len) {

      break;
    };

    if (string_at(s->text, s->pos) != slash) {

      len++;
    };

    bool double_slash = Scanner_expect(s, tos2((byte *)"\\\\"), s->pos - 2);

    if (string_at(s->text, s->pos) == '\`' &&
        (string_at(s->text, s->pos - 1) != slash || double_slash)) {

      if (double_slash) {

        len++;
      };

      break;
    };
  };

  len--;

  string c = string_substr(s->text, start + 1, s->pos);

  if (len != 1) {

    ustring u = string_ustring(c);

    if (u.len != 1) {

      Scanner_error(
          &/* ? */ *s,
          _STR("invalid character literal (more than one character: %d)", len));
    };
  };

  return c;
}
Token Scanner_peek(Scanner *s) {

  int pos = s->pos;

  int line = s->line_nr;

  bool inside_string = s->inside_string;

  bool dollar_start = s->dollar_start;

  bool dollar_end = s->dollar_end;

  ScanRes res = Scanner_scan(s);

  Token tok = res.tok;

  s->pos = pos;

  s->line_nr = line;

  s->inside_string = inside_string;

  s->dollar_start = dollar_start;

  s->dollar_end = dollar_end;

  return tok;
}
bool Scanner_expect(Scanner *s, string want, int start_pos) {

  int end_pos = start_pos + want.len;

  if (start_pos < 0 || start_pos >= s->text.len) {

    return 0;
  };

  if (end_pos < 0 || end_pos > s->text.len) {

    return 0;
  };

  int tmp138 = start_pos;
  ;
  for (int tmp139 = tmp138; tmp139 < end_pos; tmp139++) {
    int pos = tmp139;

    if (string_at(s->text, pos) != string_at(want, pos - start_pos)) {

      return 0;
    };
  };

  return 1;
}
void Scanner_debug_tokens(Scanner *s) {

  s->pos = 0;

  s->debug = 1;

  string fname = string_all_after(s->file_path, tos2((byte *)"/"));

  printf("\n===DEBUG TOKENS %.*s===\n", fname.len, fname.str);

  while (1) {

    ScanRes res = Scanner_scan(s);

    Token tok = res.tok;

    string lit = res.lit;

    print(Token_str(tok));

    if (string_ne(lit, tos2((byte *)""))) {

      printf(" `%.*s`\n", lit.len, lit.str);

    } else {

      println(tos2((byte *)""));
    };

    if (tok == main__Token_eof) {

      println(
          tos2((byte *)"============ END OF DEBUG TOKENS =================="));

      break;
    };
  };
}
bool is_name_char(byte c) { return byte_is_letter(c) || c == '_'; }
bool is_nl(byte c) { return c == '\r' || c == '\n'; }
int Scanner_get_opening_bracket(Scanner *s) {

  int pos = s->pos;

  int parentheses = 0;

  bool inside_string = 0;

  while (pos > 0 && string_at(s->text, pos) != '\n') {

    if (string_at(s->text, pos) == ')' && !inside_string) {

      parentheses++;
    };

    if (string_at(s->text, pos) == '(' && !inside_string) {

      parentheses--;
    };

    if (string_at(s->text, pos) == '\'' &&
        string_at(s->text, pos - 1) != '\\' &&
        string_at(s->text, pos - 1) != '\`') {

      inside_string = !inside_string;
    };

    if (parentheses == 0) {

      break;
    };

    pos--;
  };

  return pos;
}
void Scanner_create_type_string(Scanner *s, Type T, string name) {

  int line = s->line_nr;

  bool inside_string = s->inside_string;

  string newtext = tos2((byte *)"\'{ ");

  int start = Scanner_get_opening_bracket(s) + 1;

  int end = s->pos;

  array_Var tmp168 = T.fields;
  ;
  for (int i = 0; i < tmp168.len; i++) {
    Var field = ((Var *)tmp168.data)[i];

    if (i != 0) {

      newtext = string_add(newtext, tos2((byte *)", "));
    };

    newtext = string_add(
        newtext, string_add(_STR("%.*s: ", field.name.len, field.name.str),
                            _STR("$%.*s.%.*s", name.len, name.str,
                                 field.name.len, field.name.str)));
  };

  newtext = string_add(newtext, tos2((byte *)" }\'"));

  s->text = string_add(string_add(string_substr(s->text, 0, start), newtext),
                       string_substr(s->text, end, s->text.len));

  s->pos = start - 2;

  s->line_nr = line;

  s->inside_string = inside_string;
}
bool contains_capital(string s) {

  for (int i = 0; i < s.len; i++) {

    byte c = string_at(s, i);

    if (c >= 'A' && c <= 'Z') {

      return 1;
    };
  };

  return 0;
}
bool good_type_name(string s) {

  if (s.len < 4) {

    return 1;
  };

  int tmp173 = 2;
  ;
  for (int tmp174 = tmp173; tmp174 < s.len; tmp174++) {
    int i = tmp174;

    if (byte_is_capital(string_at(s, i)) &&
        byte_is_capital(string_at(s, i - 1)) &&
        byte_is_capital(string_at(s, i - 2))) {

      return 0;
    };
  };

  return 1;
}
string Type_str(Type t) {

  string s = _STR("type \"%.*s\" {", t.name.len, t.name.str);

  if (t.fields.len > 0) {

    array_Var tmp2 = t.fields;
    ;
    for (int tmp3 = 0; tmp3 < tmp2.len; tmp3++) {
      Var field = ((Var *)tmp2.data)[tmp3];

      s = string_add(s, _STR("\n    %.*s %.*s", field.name.len, field.name.str,
                             field.typ.len, field.typ.str));
    };

    s = string_add(s, tos2((byte *)"\n"));
  };

  if (t.methods.len > 0) {

    array_Fn tmp4 = t.methods;
    ;
    for (int tmp5 = 0; tmp5 < tmp4.len; tmp5++) {
      Fn method = ((Fn *)tmp4.data)[tmp5];

      s = string_add(
          s, _STR("\n    %.*s", Fn_str(method).len, Fn_str(method).str));
    };

    s = string_add(s, tos2((byte *)"\n"));
  };

  s = string_add(s, tos2((byte *)"}\n"));

  return s;
}
string Fn_str(Fn f) {

  Table t = (Table){.typesmap = new_map(1, sizeof(Type)),
                    .consts = new_array(0, 1, sizeof(Var)),
                    .fns = new_map(1, sizeof(Fn)),
                    .generic_fns = new_array(0, 1, sizeof(GenTable)),
                    .obf_ids = new_map(1, sizeof(int)),
                    .modules = new_array(0, 1, sizeof(string)),
                    .imports = new_array(0, 1, sizeof(string)),
                    .file_imports = new_array(0, 1, sizeof(FileImportTable)),
                    .cflags = new_array(0, 1, sizeof(CFlag)),
                    .fn_cnt = 0,
                    .obfuscate = 0};

  string str_args =
      Fn_str_args(&/* ? */ f, &/*112 EXP:"Table*" GOT:"Table" */ t);

  return _STR("%.*s(%.*s) %.*s", f.name.len, f.name.str, str_args.len,
              str_args.str, f.typ.len, f.typ.str);
}
string Table_debug_fns(Table *t) {

  strings__Builder s = strings__new_builder(1000);

  map_Fn tmp9 = t->fns;
  array_string keys_tmp9 = map_keys(&tmp9);
  for (int l = 0; l < keys_tmp9.len; l++) {
    string _ = ((string *)keys_tmp9.data)[l];
    Fn f = {0};
    map_get(tmp9, _, &f);

    strings__Builder_writeln(&/* ? */ s, f.name);
  };

  return strings__Builder_str(s);
}
bool is_number_type(string typ) { return _IN(string, typ, main__number_types); }
bool is_float_type(string typ) { return _IN(string, typ, main__float_types); }
bool is_primitive_type(string typ) {

  return is_number_type(typ) || string_eq(typ, tos2((byte *)"string"));
}
Table *new_table(bool obfuscate) {

  Table *t = (Table *)memdup(
      &(Table){
          .obfuscate = obfuscate,
          .typesmap = new_map(1, sizeof(Type)),
          .consts = new_array(0, 1, sizeof(Var)),
          .fns = new_map(1, sizeof(Fn)),
          .generic_fns = new_array(0, 1, sizeof(GenTable)),
          .obf_ids = new_map(1, sizeof(int)),
          .modules = new_array(0, 1, sizeof(string)),
          .imports = new_array(0, 1, sizeof(string)),
          .file_imports = new_array(0, 1, sizeof(FileImportTable)),
          .cflags = new_array(0, 1, sizeof(CFlag)),
          .fn_cnt = 0,
      },
      sizeof(Table));

  Table_register_type(t, tos2((byte *)"int"));

  Table_register_type(t, tos2((byte *)"size_t"));

  Table_register_type_with_parent(t, tos2((byte *)"i8"), tos2((byte *)"int"));

  Table_register_type_with_parent(t, tos2((byte *)"byte"), tos2((byte *)"int"));

  Table_register_type_with_parent(t, tos2((byte *)"i16"), tos2((byte *)"int"));

  Table_register_type_with_parent(t, tos2((byte *)"u16"), tos2((byte *)"u32"));

  Table_register_type_with_parent(t, tos2((byte *)"u32"), tos2((byte *)"int"));

  Table_register_type_with_parent(t, tos2((byte *)"i64"), tos2((byte *)"int"));

  Table_register_type_with_parent(t, tos2((byte *)"u64"), tos2((byte *)"u32"));

  Table_register_type(t, tos2((byte *)"byteptr"));

  Table_register_type(t, tos2((byte *)"intptr"));

  Table_register_type(t, tos2((byte *)"f32"));

  Table_register_type(t, tos2((byte *)"f64"));

  Table_register_type(t, tos2((byte *)"rune"));

  Table_register_type(t, tos2((byte *)"bool"));

  Table_register_type(t, tos2((byte *)"void"));

  Table_register_type(t, tos2((byte *)"voidptr"));

  Table_register_type(t, tos2((byte *)"T"));

  Table_register_type(t, tos2((byte *)"va_list"));

  Table_register_const(t, tos2((byte *)"stdin"), tos2((byte *)"int"),
                       tos2((byte *)"main"));

  Table_register_const(t, tos2((byte *)"stdout"), tos2((byte *)"int"),
                       tos2((byte *)"main"));

  Table_register_const(t, tos2((byte *)"stderr"), tos2((byte *)"int"),
                       tos2((byte *)"main"));

  Table_register_const(t, tos2((byte *)"errno"), tos2((byte *)"int"),
                       tos2((byte *)"main"));

  Table_register_type_with_parent(t, tos2((byte *)"map_string"),
                                  tos2((byte *)"map"));

  Table_register_type_with_parent(t, tos2((byte *)"map_int"),
                                  tos2((byte *)"map"));

  return t;
}
string Table_var_cgen_name(Table *t, string name) {

  if (array_string_contains(main__CReserved, name)) {

    return _STR("v_%.*s", name.len, name.str);

  } else {

    return name;
  };
}
void Table_register_module(Table *t, string mod) {

  if (array_string_contains(t->modules, mod)) {

    return;
  };

  _PUSH(&t->modules, (mod), tmp11, string);
}
void Parser_register_array(Parser *p, string typ) {

  if (string_contains(typ, tos2((byte *)"*"))) {

    printf("bad arr %.*s\n", typ.len, typ.str);

    return;
  };

  if (!Table_known_type(&/* ? */ *p->table, typ)) {

    Parser_register_type_with_parent(p, typ, tos2((byte *)"array"));

    _PUSH(&p->cgen->typedefs, (_STR("typedef array %.*s;", typ.len, typ.str)),
          tmp12, string);
  };
}
void Parser_register_map(Parser *p, string typ) {

  if (string_contains(typ, tos2((byte *)"*"))) {

    printf("bad map %.*s\n", typ.len, typ.str);

    return;
  };

  if (!Table_known_type(&/* ? */ *p->table, typ)) {

    Parser_register_type_with_parent(p, typ, tos2((byte *)"map"));

    _PUSH(&p->cgen->typedefs, (_STR("typedef map %.*s;", typ.len, typ.str)),
          tmp13, string);
  };
}
bool Table_known_mod(Table *table, string mod) {

  return _IN(string, mod, table->modules);
}
void Table_register_const(Table *t, string name, string typ, string mod) {

  _PUSH(&t->consts,
        ((Var){.name = name,
               .typ = typ,
               .is_const = 1,
               .mod = mod,
               .is_arg = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos((byte *)"", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos((byte *)"", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .is_changed = 0,
               .scope_level = 0}),
        tmp14, Var);
}
void Parser_register_global(Parser *p, string name, string typ) {

  _PUSH(&p->table->consts,
        ((Var){.name = name,
               .typ = typ,
               .is_const = 1,
               .is_global = 1,
               .mod = p->mod,
               .is_mut = 1,
               .is_arg = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos((byte *)"", 0),
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos((byte *)"", 0),
               .line_nr = 0,
               .is_used = 0,
               .is_changed = 0,
               .scope_level = 0}),
        tmp15, Var);
}
void Table_register_fn(Table *t, Fn new_fn) {

  map__set(&t->fns, new_fn.name, &(Fn[]){new_fn});
}
bool Table_known_type(Table *table, string typ_) {

  string typ = typ_;

  if (string_ends_with(typ, tos2((byte *)"*")) &&
      !string_contains(typ, tos2((byte *)" "))) {

    typ = string_left(typ, typ.len - 1);
  };

  Type tmp17 = {0};
  bool tmp18 = map_get(table->typesmap, typ, &tmp17);

  Type t = tmp17;

  return t.name.len > 0 && !t.is_placeholder;
}
bool Table_known_type_fast(Table *table, Type *t) {

  return t->name.len > 0 && !t->is_placeholder;
}
Fn Table_find_fn(Table *t, string name) {

  Fn tmp20 = {0};
  bool tmp21 = map_get(t->fns, name, &tmp20);

  Fn f = tmp20;

  if (!isnil(f.name.str)) {

    return f;
  };

  return (Fn){.name = tos((byte *)"", 0),
              .mod = tos((byte *)"", 0),
              .local_vars = new_array(0, 1, sizeof(Var)),
              .var_idx = 0,
              .args = new_array(0, 1, sizeof(Var)),
              .is_interface = 0,
              .scope_level = 0,
              .typ = tos((byte *)"", 0),
              .is_c = 0,
              .receiver_typ = tos((byte *)"", 0),
              .is_public = 0,
              .is_method = 0,
              .returns_error = 0,
              .is_decl = 0,
              .defer_text = new_array(0, 1, sizeof(string))};
}
bool Table_known_fn(Table *t, string name) {

  Fn f = Table_find_fn(&/* ? */ *t, name);

  return string_ne(f.name, tos2((byte *)""));
}
bool Table_known_const(Table *t, string name) {

  Var v = Table_find_const(&/* ? */ *t, name);

  return v.name.len > 0;
}
void Table_register_type(Table *t, string typ) {

  if (typ.len == 0) {

    return;
  };

  if (_IN_MAP(typ, t->typesmap)) {

    return;
  };

  map__set(&t->typesmap, typ,
           &(Type[]){(Type){.name = typ,
                            .mod = tos((byte *)"", 0),
                            .fields = new_array(0, 1, sizeof(Var)),
                            .methods = new_array(0, 1, sizeof(Fn)),
                            .parent = tos((byte *)"", 0),
                            .is_c = 0,
                            .enum_vals = new_array(0, 1, sizeof(string)),
                            .gen_types = new_array(0, 1, sizeof(string)),
                            .is_placeholder = 0,
                            .gen_str = 0}});
}
void Parser_register_type_with_parent(Parser *p, string strtyp, string parent) {

  Type typ = (Type){.name = strtyp,
                    .parent = parent,
                    .mod = p->mod,
                    .fields = new_array(0, 1, sizeof(Var)),
                    .methods = new_array(0, 1, sizeof(Fn)),
                    .is_c = 0,
                    .enum_vals = new_array(0, 1, sizeof(string)),
                    .gen_types = new_array(0, 1, sizeof(string)),
                    .is_placeholder = 0,
                    .gen_str = 0};

  Table_register_type2(p->table, typ);
}
void Table_register_type_with_parent(Table *t, string typ, string parent) {

  if (typ.len == 0) {

    return;
  };

  map__set(&t->typesmap, typ,
           &(Type[]){(Type){.name = typ,
                            .parent = parent,
                            .mod = tos((byte *)"", 0),
                            .fields = new_array(0, 1, sizeof(Var)),
                            .methods = new_array(0, 1, sizeof(Fn)),
                            .is_c = 0,
                            .enum_vals = new_array(0, 1, sizeof(string)),
                            .gen_types = new_array(0, 1, sizeof(string)),
                            .is_placeholder = 0,
                            .gen_str = 0}});
}
void Table_register_type2(Table *t, Type typ) {

  if (typ.name.len == 0) {

    return;
  };

  map__set(&t->typesmap, typ.name, &(Type[]){typ});
}
void Table_rewrite_type(Table *t, Type typ) {

  if (typ.name.len == 0) {

    return;
  };

  map__set(&t->typesmap, typ.name, &(Type[]){typ});
}
void Table_add_field(Table *table, string type_name, string field_name,
                     string field_type, bool is_mut, string attr,
                     AccessMod access_mod) {

  if (string_eq(type_name, tos2((byte *)""))) {

    print_backtrace();

    cerror(tos2((byte *)"add_field: empty type"));
  };

  Type tmp26 = {0};
  bool tmp27 = map_get(table->typesmap, type_name, &tmp26);

  Type t = tmp26;

  _PUSH(&t.fields,
        ((Var){.name = field_name,
               .typ = field_type,
               .is_mut = is_mut,
               .attr = attr,
               .parent_fn = type_name,
               .access_mod = access_mod,
               .is_arg = 0,
               .is_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .mod = tos((byte *)"", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .is_changed = 0,
               .scope_level = 0}),
        tmp29, Var);

  map__set(&table->typesmap, type_name, &(Type[]){t});
}
bool Type_has_field(Type *t, string name) {

  Var field = Type_find_field(&/* ? */ *t, name);

  return (string_ne(field.name, tos2((byte *)"")));
}
bool Type_has_enum_val(Type *t, string name) {

  return _IN(string, name, t->enum_vals);
}
Var Type_find_field(Type *t, string name) {

  array_Var tmp31 = t->fields;
  ;
  for (int tmp32 = 0; tmp32 < tmp31.len; tmp32++) {
    Var field = ((Var *)tmp31.data)[tmp32];

    if (string_eq(field.name, name)) {

      return field;
    };
  };

  return (Var){.typ = tos((byte *)"", 0),
               .name = tos((byte *)"", 0),
               .is_arg = 0,
               .is_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos((byte *)"", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos((byte *)"", 0),
               .mod = tos((byte *)"", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .is_changed = 0,
               .scope_level = 0};
}
bool Table_type_has_field(Table *table, Type *typ, string name) {

  Var field = Table_find_field(&/* ? */ *table, typ, name);

  return (string_ne(field.name, tos2((byte *)"")));
}
Var Table_find_field(Table *table, Type *typ, string name) {

  Var field = Type_find_field(&/* ? */ *typ, name);

  if (field.name.len == 0 && typ->parent.len > 0) {

    Type parent = Table_find_type(&/* ? */ *table, typ->parent);

    return Type_find_field(&/* ? */ parent, name);
  };

  return field;
}
void Table_add_method(Table *table, string type_name, Fn f) {

  if (string_eq(type_name, tos2((byte *)""))) {

    print_backtrace();

    cerror(tos2((byte *)"add_method: empty type"));
  };

  Type tmp36 = {0};
  bool tmp37 = map_get(table->typesmap, type_name, &tmp36);

  Type t = tmp36;

  _PUSH(&t.methods, (f), tmp39, Fn);

  map__set(&table->typesmap, type_name, &(Type[]){t});
}
bool Type_has_method(Type *t, string name) {

  Fn method = Type_find_method(&/* ? */ *t, name);

  return (string_ne(method.name, tos2((byte *)"")));
}
bool Table_type_has_method(Table *table, Type *typ, string name) {

  Fn method = Table_find_method(&/* ? */ *table, typ, name);

  return (string_ne(method.name, tos2((byte *)"")));
}
Fn Table_find_method(Table *table, Type *typ, string name) {

  Type tmp42 = {0};
  bool tmp43 = map_get(table->typesmap, typ->name, &tmp42);

  Type t = tmp42;

  Fn method = Type_find_method(&/* ? */ t, name);

  if (method.name.len == 0 && typ->parent.len > 0) {

    Type parent = Table_find_type(&/* ? */ *table, typ->parent);

    return Type_find_method(&/* ? */ parent, name);
  };

  return method;
}
Fn Type_find_method(Type *t, string name) {

  array_Fn tmp47 = t->methods;
  ;
  for (int tmp48 = 0; tmp48 < tmp47.len; tmp48++) {
    Fn method = ((Fn *)tmp47.data)[tmp48];

    if (string_eq(method.name, name)) {

      return method;
    };
  };

  return (Fn){.name = tos((byte *)"", 0),
              .mod = tos((byte *)"", 0),
              .local_vars = new_array(0, 1, sizeof(Var)),
              .var_idx = 0,
              .args = new_array(0, 1, sizeof(Var)),
              .is_interface = 0,
              .scope_level = 0,
              .typ = tos((byte *)"", 0),
              .is_c = 0,
              .receiver_typ = tos((byte *)"", 0),
              .is_public = 0,
              .is_method = 0,
              .returns_error = 0,
              .is_decl = 0,
              .defer_text = new_array(0, 1, sizeof(string))};
}
Type Parser_find_type(Parser *p, string name) {

  Type typ = Table_find_type(&/* ? */ *p->table, name);

  if (string_eq(typ.name, tos2((byte *)""))) {

    return Table_find_type(&/* ? */ *p->table,
                           Parser_prepend_mod(&/* ? */ *p, name));
  };

  return typ;
}
Type Table_find_type(Table *t, string name_) {

  string name = name_;

  if (string_ends_with(name, tos2((byte *)"*")) &&
      !string_contains(name, tos2((byte *)" "))) {

    name = string_left(name, name.len - 1);
  };

  if (!(_IN_MAP(name, t->typesmap))) {

    return (Type){.mod = tos((byte *)"", 0),
                  .name = tos((byte *)"", 0),
                  .fields = new_array(0, 1, sizeof(Var)),
                  .methods = new_array(0, 1, sizeof(Fn)),
                  .parent = tos((byte *)"", 0),
                  .is_c = 0,
                  .enum_vals = new_array(0, 1, sizeof(string)),
                  .gen_types = new_array(0, 1, sizeof(string)),
                  .is_placeholder = 0,
                  .gen_str = 0};
  };

  Type tmp51 = {0};
  bool tmp52 = map_get(t->typesmap, name, &tmp51);

  return tmp51;
}
bool Parser__check_types(Parser *p, string got_, string expected_, bool throw) {

  string got = got_;

  string expected = expected_;

  Parser_log(&/* ? */ *p, _STR("check types got=\"%.*s\" exp=\"%.*s\"  ",
                               got.len, got.str, expected.len, expected.str));

  if (p->pref->translated) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"int")) &&
      string_eq(expected, tos2((byte *)"f32"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"int")) &&
      string_eq(expected, tos2((byte *)"f64"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"f64")) &&
      string_eq(expected, tos2((byte *)"f32"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"f32")) &&
      string_eq(expected, tos2((byte *)"f64"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"int")) &&
      string_eq(expected, tos2((byte *)"i64"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"void*")) &&
      string_starts_with(expected, tos2((byte *)"fn "))) {

    return 1;
  };

  if (string_starts_with(got, tos2((byte *)"[")) &&
      string_eq(expected, tos2((byte *)"byte*"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"void*")) ||
      string_eq(expected, tos2((byte *)"void*"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"int")) &&
      string_eq(expected, tos2((byte *)"byte"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"byteptr")) &&
      string_eq(expected, tos2((byte *)"byte*"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"byte*")) &&
      string_eq(expected, tos2((byte *)"byteptr"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"int")) &&
      string_eq(expected, tos2((byte *)"byte*"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"int")) &&
      string_eq(expected, tos2((byte *)"byteptr"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"Option")) &&
      string_starts_with(expected, tos2((byte *)"Option_"))) {

    return 1;
  };

  if (string_eq(got, tos2((byte *)"array")) &&
      string_starts_with(expected, tos2((byte *)"array_"))) {

    return 1;
  };

  if (string_starts_with(expected, tos2((byte *)"Option_")) &&
      string_ends_with(expected, got)) {

    return 1;
  };

  if (string_ends_with(expected, tos2((byte *)"*")) &&
      string_eq(got, tos2((byte *)"int"))) {

    return 1;
  };

  if (string_eq(expected, tos2((byte *)"void*")) &&
      string_eq(got, tos2((byte *)"int"))) {

    return 1;
  };

  expected = string_replace(expected, tos2((byte *)"*"), tos2((byte *)""));

  got = string_replace(got, tos2((byte *)"*"), tos2((byte *)""));

  if (string_ne(got, expected)) {

    if (string_ends_with(expected, tos2((byte *)"er"))) {

      if (Parser_satisfies_interface(p, expected, got, throw)) {

        return 1;
      };
    };

    if (!throw) {

      return 0;

    } else {

      Parser_error(p, _STR("expected type `%.*s`, but got `%.*s`", expected.len,
                           expected.str, got.len, got.str));
    };
  };

  return 1;
}
bool Parser_check_types(Parser *p, string got, string expected) {

  if (Parser_first_pass(&/* ? */ *p)) {

    return 1;
  };

  return Parser__check_types(p, got, expected, 1);
}
bool Parser_check_types_no_throw(Parser *p, string got, string expected) {

  return Parser__check_types(p, got, expected, 0);
}
bool Parser_satisfies_interface(Parser *p, string interface_name, string _typ,
                                bool throw) {

  Type int_typ = Table_find_type(&/* ? */ *p->table, interface_name);

  Type typ = Table_find_type(&/* ? */ *p->table, _typ);

  array_Fn tmp57 = int_typ.methods;
  ;
  for (int tmp58 = 0; tmp58 < tmp57.len; tmp58++) {
    Fn method = ((Fn *)tmp57.data)[tmp58];

    if (!Type_has_method(&/* ? */ typ, method.name)) {

      Parser_error(p,
                   _STR("Type \"%.*s\" doesn\'t satisfy interface \"%.*s\" "
                        "(method \"%.*s\" is not implemented)",
                        _typ.len, _typ.str, interface_name.len,
                        interface_name.str, method.name.len, method.name.str));

      return 0;
    };
  };

  return 1;
}
string type_default(string typ) {

  if (string_starts_with(typ, tos2((byte *)"array_"))) {

    return _STR("new_array(0, 1, sizeof( %.*s ))", string_right(typ, 6).len,
                string_right(typ, 6).str);
  };

  if (string_ends_with(typ, tos2((byte *)"*"))) {

    return tos2((byte *)"0");
  };

  if (string_contains(typ, tos2((byte *)"__"))) {

    return tos2((byte *)"{0}");
  };

  if (string_eq(typ, tos2((byte *)"bool"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"string"))) { /* case */

    return tos2((byte *)"tos((byte *)\"\", 0)");

  } else if (string_eq(typ, tos2((byte *)"i8"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"i16"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"i64"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"u16"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"u32"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"u64"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"byte"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"int"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"rune"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"f32"))) { /* case */

    return tos2((byte *)"0.0");

  } else if (string_eq(typ, tos2((byte *)"f64"))) { /* case */

    return tos2((byte *)"0.0");

  } else if (string_eq(typ, tos2((byte *)"byteptr"))) { /* case */

    return tos2((byte *)"0");

  } else if (string_eq(typ, tos2((byte *)"voidptr"))) { /* case */

    return tos2((byte *)"0");
  };

  return tos2((byte *)"{0}");
}
bool Table_is_interface(Table *table, string name) {

  if (!(_IN_MAP(name, table->typesmap))) {

    return 0;
  };

  Type tmp59 = {0};
  bool tmp60 = map_get(table->typesmap, name, &tmp59);

  Type t = tmp59;

  return t.cat == main__TypeCategory_interface_;
}
bool Table_main_exists(Table *t) {

  map_Fn tmp62 = t->fns;
  array_string keys_tmp62 = map_keys(&tmp62);
  for (int l = 0; l < keys_tmp62.len; l++) {
    string _ = ((string *)keys_tmp62.data)[l];
    Fn f = {0};
    map_get(tmp62, _, &f);

    if (string_eq(f.name, tos2((byte *)"main"))) {

      return 1;
    };
  };

  return 0;
}
Var Table_find_const(Table *t, string name) {

  array_Var tmp63 = t->consts;
  ;
  for (int tmp64 = 0; tmp64 < tmp63.len; tmp64++) {
    Var c = ((Var *)tmp63.data)[tmp64];

    if (string_eq(c.name, name)) {

      return c;
    };
  };

  return (Var){.typ = tos((byte *)"", 0),
               .name = tos((byte *)"", 0),
               .is_arg = 0,
               .is_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos((byte *)"", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos((byte *)"", 0),
               .mod = tos((byte *)"", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .is_changed = 0,
               .scope_level = 0};
}
string Table_cgen_name(Table *table, Fn *f) {

  string name = f->name;

  if (f->is_method) {

    name = _STR("%.*s_%.*s", f->receiver_typ.len, f->receiver_typ.str,
                f->name.len, f->name.str);

    name = string_replace(name, tos2((byte *)" "), tos2((byte *)""));

    name = string_replace(name, tos2((byte *)"*"), tos2((byte *)""));

    name = string_replace(name, tos2((byte *)"+"), tos2((byte *)"plus"));

    name = string_replace(name, tos2((byte *)"-"), tos2((byte *)"minus"));
  };

  if (string_eq(f->mod, tos2((byte *)"builtin")) &&
      array_string_contains(main__CReserved, f->name)) {

    return _STR("v_%.*s", name.len, name.str);
  };

  if (table->obfuscate && string_ne(f->name, tos2((byte *)"main")) &&
      string_ne(f->name, tos2((byte *)"WinMain")) &&
      string_ne(f->mod, tos2((byte *)"builtin")) && !f->is_c &&
      string_ne(f->mod, tos2((byte *)"darwin")) &&
      string_ne(f->mod, tos2((byte *)"os")) &&
      !string_contains(f->name, tos2((byte *)"window_proc")) &&
      string_ne(f->name, tos2((byte *)"gg__vec2")) &&
      string_ne(f->name, tos2((byte *)"build_token_str")) &&
      string_ne(f->name, tos2((byte *)"build_keys")) &&
      string_ne(f->mod, tos2((byte *)"json")) &&
      !string_ends_with(name, tos2((byte *)"_str")) &&
      !string_contains(name, tos2((byte *)"contains"))) {

    int tmp66 = 0;
    bool tmp67 = map_get(table->obf_ids, name, &tmp66);

    int idx = tmp66;

    if (idx == 0) {

      table->fn_cnt++;

      map__set(&table->obf_ids, name, &(int[]){table->fn_cnt});

      idx = table->fn_cnt;
    };

    string old = name;

    name = _STR("f_%d", idx);

    printf("%.*s ==> %.*s\n", old.len, old.str, name.len, name.str);
  };

  return name;
}
string Table_cgen_name_type_pair(Table *table, string name, string typ) {

  if (typ.len > 0 && string_at(typ, 0) == '[') {

    string tmp = string_all_after(typ, tos2((byte *)"]"));

    string size = string_all_before(typ, tos2((byte *)"]"));

    return _STR("%.*s %.*s  %.*s ]", tmp.len, tmp.str, name.len, name.str,
                size.len, size.str);

  } else if (string_starts_with(typ, tos2((byte *)"fn ("))) {

    Type T = Table_find_type(&/* ? */ *table, typ);

    if (string_eq(T.name, tos2((byte *)""))) {

      println(tos2((byte *)"this should never happen"));

      v_exit(1);
    };

    string str_args = Fn_str_args(&/* ? */ T.func, table);

    return _STR("%.*s (*%.*s)( %.*s /*FFF*/ )", T.func.typ.len, T.func.typ.str,
                name.len, name.str, str_args.len, str_args.str);

  } else if (string_eq(typ, tos2((byte *)"tm"))) {

    return _STR("struct /*TM*/ tm %.*s", name.len, name.str);
  };

  return _STR("%.*s %.*s", typ.len, typ.str, name.len, name.str);
}
bool is_valid_int_const(string val, string typ) {

  int x = v_string_int(val);

  if (string_eq(typ, tos2((byte *)"byte"))) { /* case */

    return 0 <= x && x <= math__MaxU8;

  } else if (string_eq(typ, tos2((byte *)"u16"))) { /* case */

    return 0 <= x && x <= math__MaxU16;

  } else if (string_eq(typ, tos2((byte *)"i8"))) { /* case */

    return math__MinI8 <= x && x <= math__MaxI8;

  } else if (string_eq(typ, tos2((byte *)"i16"))) { /* case */

    return math__MinI16 <= x && x <= math__MaxI16;

  } else if (string_eq(typ, tos2((byte *)"int"))) { /* case */

    return math__MinI32 <= x && x <= math__MaxI32;
  };

  return 1;
}
void Table_register_generic_fn(Table *t, string fn_name) {

  _PUSH(&t->generic_fns,
        ((GenTable){fn_name, new_array_from_c_array(0, 0, sizeof(string),
                                                    (string[]){0})}),
        tmp77, GenTable);
}
array_string Table_fn_gen_types(Table *t, string fn_name) {

  array_GenTable tmp78 = t->generic_fns;
  ;
  for (int _ = 0; _ < tmp78.len; _++) {
    GenTable f = ((GenTable *)tmp78.data)[_];

    if (string_eq(f.fn_name, fn_name)) {

      return f.types;
    };
  };

  cerror(_STR("function %.*s not found", fn_name.len, fn_name.str));

  return new_array_from_c_array(0, 0, sizeof(string), (string[]){0});
}
void Table_register_generic_fn_type(Table *t, string fn_name, string typ) {

  array_GenTable tmp79 = t->generic_fns;
  ;
  for (int i = 0; i < tmp79.len; i++) {
    GenTable f = ((GenTable *)tmp79.data)[i];

    if (string_eq(f.fn_name, fn_name)) {

      _PUSH(&(*(GenTable *)array__get(t->generic_fns, i)).types, (typ), tmp82,
            string);

      return;
    };
  };
}
string Parser_typ_to_fmt(Parser *p, string typ, int level) {

  Type t = Table_find_type(&/* ? */ *p->table, typ);

  if (t.cat == main__TypeCategory_enum_) {

    return tos2((byte *)"%d");
  };

  if (string_eq(typ, tos2((byte *)"string"))) { /* case */

    return tos2((byte *)"%.*s");

  } else if (string_eq(typ, tos2((byte *)"ustring"))) { /* case */

    return tos2((byte *)"%.*s");

  } else if (string_eq(typ, tos2((byte *)"byte")) ||
             string_eq(typ, tos2((byte *)"bool")) ||
             string_eq(typ, tos2((byte *)"int")) ||
             string_eq(typ, tos2((byte *)"char")) ||
             string_eq(typ, tos2((byte *)"byte")) ||
             string_eq(typ, tos2((byte *)"i16")) ||
             string_eq(typ, tos2((byte *)"i8"))) { /* case */

    return tos2((byte *)"%d");

  } else if (string_eq(typ, tos2((byte *)"u16")) ||
             string_eq(typ, tos2((byte *)"u32"))) { /* case */

    return tos2((byte *)"%u");

  } else if (string_eq(typ, tos2((byte *)"f64")) ||
             string_eq(typ, tos2((byte *)"f32"))) { /* case */

    return tos2((byte *)"%f");

  } else if (string_eq(typ, tos2((byte *)"i64"))) { /* case */

    return tos2((byte *)"%lld");

  } else if (string_eq(typ, tos2((byte *)"u64"))) { /* case */

    return tos2((byte *)"%llu");

  } else if (string_eq(typ, tos2((byte *)"byte*")) ||
             string_eq(typ, tos2((byte *)"byteptr"))) { /* case */

    return tos2((byte *)"%s");

  } else if (string_eq(typ, tos2((byte *)"void"))) { /* case */

    Parser_error(p, tos2((byte *)"cannot interpolate this value"));

  } else { // default:

    if (string_ends_with(typ, tos2((byte *)"*"))) {

      return tos2((byte *)"%p");
    };
  };

  if (string_ne(t.parent, tos2((byte *)"")) && level == 0) {

    return Parser_typ_to_fmt(p, t.parent, level + 1);
  };

  return tos2((byte *)"");
}
bool is_compile_time_const(string s_) {

  string s = string_trim_space(s_);

  if (string_eq(s, tos2((byte *)""))) {

    return 0;
  };

  if (string_contains(s, tos2((byte *)"\'"))) {

    return 1;
  };

  string tmp85 = s;
  ;
  for (int tmp86 = 0; tmp86 < tmp85.len; tmp86++) {
    byte c = ((byte *)tmp85.str)[tmp86];

    if (!((c >= '0' && c <= '9') || c == '.')) {

      return 0;
    };
  };

  return 1;
}
string Table_qualify_module(Table *table, string mod, string file_path) {

  array_string tmp87 = table->imports;
  ;
  for (int tmp88 = 0; tmp88 < tmp87.len; tmp88++) {
    string m = ((string *)tmp87.data)[tmp88];

    if (string_contains(m, tos2((byte *)".")) && string_contains(m, mod)) {

      array_string m_parts = string_split(m, tos2((byte *)"."));

      string m_path = array_string_join(m_parts, tos2((byte *)"/"));

      if (string_eq(mod, (*(string *)array__get(m_parts, m_parts.len - 1))) &&
          string_contains(file_path, m_path)) {

        return m;
      };
    };
  };

  return mod;
}
FileImportTable *new_file_import_table(string file_path) {

  return (FileImportTable *)memdup(
      &(FileImportTable){
          .file_path = file_path,
          .imports = new_map(1, sizeof(string)),
          .module_name = tos((byte *)"", 0),
      },
      sizeof(FileImportTable));
}
bool FileImportTable_known_import(FileImportTable *fit, string mod) {

  return _IN_MAP(mod, fit->imports) ||
         FileImportTable_is_aliased(&/* ? */ *fit, mod);
}
void FileImportTable_register_import(FileImportTable *fit, string mod) {

  FileImportTable_register_alias(fit, mod, mod);
}
void FileImportTable_register_alias(FileImportTable *fit, string alias,
                                    string mod) {

  if (_IN_MAP(alias, fit->imports)) {

    cerror(_STR("cannot import %.*s as %.*s: import name %.*s already in use "
                "in \"%.*s\".",
                mod.len, mod.str, alias.len, alias.str, alias.len, alias.str,
                fit->file_path.len, fit->file_path.str));
  };

  if (string_contains(mod, tos2((byte *)".internal."))) {

    array_string mod_parts = string_split(mod, tos2((byte *)"."));

    array_string internal_mod_parts =
        new_array_from_c_array(0, 0, sizeof(string), (string[]){0});

    array_string tmp95 = mod_parts;
    ;
    for (int tmp96 = 0; tmp96 < tmp95.len; tmp96++) {
      string part = ((string *)tmp95.data)[tmp96];

      if (string_eq(part, tos2((byte *)"internal"))) {

        break;
      };

      _PUSH(&internal_mod_parts, (part), tmp97, string);
    };

    string internal_parent =
        array_string_join(internal_mod_parts, tos2((byte *)"."));

    if (!string_starts_with(fit->module_name, internal_parent)) {

      cerror(_STR("module %.*s can only be imported internally by libs.",
                  mod.len, mod.str));
    };

    v_array_free(internal_mod_parts); // close_scope free
  };

  map__set(&fit->imports, alias, &(string[]){mod});
}
bool FileImportTable_known_alias(FileImportTable *fit, string alias) {

  return _IN_MAP(alias, fit->imports);
}
bool FileImportTable_is_aliased(FileImportTable *fit, string mod) {

  map_string tmp99 = fit->imports;
  array_string keys_tmp99 = map_keys(&tmp99);
  for (int l = 0; l < keys_tmp99.len; l++) {
    string _ = ((string *)keys_tmp99.data)[l];
    string val = {0};
    map_get(tmp99, _, &val);

    if (string_eq(val, mod)) {

      return 1;
    };
  };

  return 0;
}
string FileImportTable_resolve_alias(FileImportTable *fit, string alias) {

  string tmp100 = tos((byte *)"", 0);
  bool tmp101 = map_get(fit->imports, alias, &tmp100);

  if (!tmp101)
    tmp100 = tos((byte *)"", 0);

  return tmp100;
}
bool Type_contains_field_type(Type *t, string typ) {

  if (!byte_is_capital(string_at(t->name, 0))) {

    return 0;
  };

  array_Var tmp104 = t->fields;
  ;
  for (int tmp105 = 0; tmp105 < tmp104.len; tmp105++) {
    Var field = ((Var *)tmp104.data)[tmp105];

    if (string_eq(field.typ, typ)) {

      return 1;
    };
  };

  return 0;
}
map_int build_keys() {

  map_int res = new_map(1, sizeof(int));

  for (int t = ((int)(main__Token_keyword_beg)) + 1;
       t < ((int)(main__Token_keyword_end)); t++) {

    string key = (*(string *)array__get(main__TokenStr, t));

    map__set(&res, key, &(int[]){((int)(t))});
  };

  return res;
}
array_string build_token_str() {

  array_string s = array_repeat(&(string[]){tos2((byte *)"")}, main__NrTokens,
                                sizeof(string));

  array_set(&/*q*/ s, main__Token_keyword_beg, &(string[]){tos2((byte *)"")});

  array_set(&/*q*/ s, main__Token_keyword_end, &(string[]){tos2((byte *)"")});

  array_set(&/*q*/ s, main__Token_eof, &(string[]){tos2((byte *)"eof")});

  array_set(&/*q*/ s, main__Token_name, &(string[]){tos2((byte *)"name")});

  array_set(&/*q*/ s, main__Token_number, &(string[]){tos2((byte *)"number")});

  array_set(&/*q*/ s, main__Token_str, &(string[]){tos2((byte *)"STR")});

  array_set(&/*q*/ s, main__Token_chartoken, &(string[]){tos2((byte *)"char")});

  array_set(&/*q*/ s, main__Token_plus, &(string[]){tos2((byte *)"+")});

  array_set(&/*q*/ s, main__Token_minus, &(string[]){tos2((byte *)"-")});

  array_set(&/*q*/ s, main__Token_mul, &(string[]){tos2((byte *)"*")});

  array_set(&/*q*/ s, main__Token_div, &(string[]){tos2((byte *)"/")});

  array_set(&/*q*/ s, main__Token_mod, &(string[]){tos2((byte *)"%")});

  array_set(&/*q*/ s, main__Token_xor, &(string[]){tos2((byte *)"^")});

  array_set(&/*q*/ s, main__Token_bit_not, &(string[]){tos2((byte *)"~")});

  array_set(&/*q*/ s, main__Token_pipe, &(string[]){tos2((byte *)"|")});

  array_set(&/*q*/ s, main__Token_hash, &(string[]){tos2((byte *)"#")});

  array_set(&/*q*/ s, main__Token_amp, &(string[]){tos2((byte *)"&")});

  array_set(&/*q*/ s, main__Token_inc, &(string[]){tos2((byte *)"++")});

  array_set(&/*q*/ s, main__Token_dec, &(string[]){tos2((byte *)"--")});

  array_set(&/*q*/ s, main__Token_and, &(string[]){tos2((byte *)"&&")});

  array_set(&/*q*/ s, main__Token_logical_or, &(string[]){tos2((byte *)"||")});

  array_set(&/*q*/ s, main__Token_not, &(string[]){tos2((byte *)"!")});

  array_set(&/*q*/ s, main__Token_dot, &(string[]){tos2((byte *)".")});

  array_set(&/*q*/ s, main__Token_dotdot, &(string[]){tos2((byte *)"..")});

  array_set(&/*q*/ s, main__Token_comma, &(string[]){tos2((byte *)",")});

  array_set(&/*q*/ s, main__Token_semicolon, &(string[]){tos2((byte *)";")});

  array_set(&/*q*/ s, main__Token_colon, &(string[]){tos2((byte *)":")});

  array_set(&/*q*/ s, main__Token_arrow, &(string[]){tos2((byte *)"=>")});

  array_set(&/*q*/ s, main__Token_assign, &(string[]){tos2((byte *)"=")});

  array_set(&/*q*/ s, main__Token_decl_assign, &(string[]){tos2((byte *)":=")});

  array_set(&/*q*/ s, main__Token_plus_assign, &(string[]){tos2((byte *)"+=")});

  array_set(&/*q*/ s, main__Token_minus_assign,
            &(string[]){tos2((byte *)"-=")});

  array_set(&/*q*/ s, main__Token_mult_assign, &(string[]){tos2((byte *)"*=")});

  array_set(&/*q*/ s, main__Token_div_assign, &(string[]){tos2((byte *)"/=")});

  array_set(&/*q*/ s, main__Token_xor_assign, &(string[]){tos2((byte *)"^=")});

  array_set(&/*q*/ s, main__Token_mod_assign, &(string[]){tos2((byte *)"%=")});

  array_set(&/*q*/ s, main__Token_or_assign, &(string[]){tos2((byte *)"|=")});

  array_set(&/*q*/ s, main__Token_and_assign, &(string[]){tos2((byte *)"&=")});

  array_set(&/*q*/ s, main__Token_righ_shift_assign,
            &(string[]){tos2((byte *)">>=")});

  array_set(&/*q*/ s, main__Token_left_shift_assign,
            &(string[]){tos2((byte *)"<<=")});

  array_set(&/*q*/ s, main__Token_lcbr, &(string[]){tos2((byte *)"{")});

  array_set(&/*q*/ s, main__Token_rcbr, &(string[]){tos2((byte *)"}")});

  array_set(&/*q*/ s, main__Token_lpar, &(string[]){tos2((byte *)"(")});

  array_set(&/*q*/ s, main__Token_rpar, &(string[]){tos2((byte *)")")});

  array_set(&/*q*/ s, main__Token_lsbr, &(string[]){tos2((byte *)"[")});

  array_set(&/*q*/ s, main__Token_rsbr, &(string[]){tos2((byte *)"]")});

  array_set(&/*q*/ s, main__Token_eq, &(string[]){tos2((byte *)"==")});

  array_set(&/*q*/ s, main__Token_ne, &(string[]){tos2((byte *)"!=")});

  array_set(&/*q*/ s, main__Token_gt, &(string[]){tos2((byte *)">")});

  array_set(&/*q*/ s, main__Token_lt, &(string[]){tos2((byte *)"<")});

  array_set(&/*q*/ s, main__Token_ge, &(string[]){tos2((byte *)">=")});

  array_set(&/*q*/ s, main__Token_le, &(string[]){tos2((byte *)"<=")});

  array_set(&/*q*/ s, main__Token_question, &(string[]){tos2((byte *)"?")});

  array_set(&/*q*/ s, main__Token_left_shift, &(string[]){tos2((byte *)"<<")});

  array_set(&/*q*/ s, main__Token_righ_shift, &(string[]){tos2((byte *)">>")});

  array_set(&/*q*/ s, main__Token_nl, &(string[]){tos2((byte *)"NLL")});

  array_set(&/*q*/ s, main__Token_dollar, &(string[]){tos2((byte *)"$")});

  array_set(&/*q*/ s, main__Token_key_assert,
            &(string[]){tos2((byte *)"assert")});

  array_set(&/*q*/ s, main__Token_key_struct,
            &(string[]){tos2((byte *)"struct")});

  array_set(&/*q*/ s, main__Token_key_if, &(string[]){tos2((byte *)"if")});

  array_set(&/*q*/ s, main__Token_key_else, &(string[]){tos2((byte *)"else")});

  array_set(&/*q*/ s, main__Token_key_return,
            &(string[]){tos2((byte *)"return")});

  array_set(&/*q*/ s, main__Token_key_module,
            &(string[]){tos2((byte *)"module")});

  array_set(&/*q*/ s, main__Token_key_sizeof,
            &(string[]){tos2((byte *)"sizeof")});

  array_set(&/*q*/ s, main__Token_key_go, &(string[]){tos2((byte *)"go")});

  array_set(&/*q*/ s, main__Token_key_goto, &(string[]){tos2((byte *)"goto")});

  array_set(&/*q*/ s, main__Token_key_const,
            &(string[]){tos2((byte *)"const")});

  array_set(&/*q*/ s, main__Token_key_mut, &(string[]){tos2((byte *)"mut")});

  array_set(&/*q*/ s, main__Token_key_type, &(string[]){tos2((byte *)"type")});

  array_set(&/*q*/ s, main__Token_key_for, &(string[]){tos2((byte *)"for")});

  array_set(&/*q*/ s, main__Token_key_switch,
            &(string[]){tos2((byte *)"switch")});

  array_set(&/*q*/ s, main__Token_key_case, &(string[]){tos2((byte *)"case")});

  array_set(&/*q*/ s, main__Token_func, &(string[]){tos2((byte *)"fn")});

  array_set(&/*q*/ s, main__Token_key_true, &(string[]){tos2((byte *)"true")});

  array_set(&/*q*/ s, main__Token_key_false,
            &(string[]){tos2((byte *)"false")});

  array_set(&/*q*/ s, main__Token_key_continue,
            &(string[]){tos2((byte *)"continue")});

  array_set(&/*q*/ s, main__Token_key_break,
            &(string[]){tos2((byte *)"break")});

  array_set(&/*q*/ s, main__Token_key_import,
            &(string[]){tos2((byte *)"import")});

  array_set(&/*q*/ s, main__Token_key_embed,
            &(string[]){tos2((byte *)"embed")});

  array_set(&/*q*/ s, main__Token_key_default,
            &(string[]){tos2((byte *)"default")});

  array_set(&/*q*/ s, main__Token_key_enum, &(string[]){tos2((byte *)"enum")});

  array_set(&/*q*/ s, main__Token_key_interface,
            &(string[]){tos2((byte *)"interface")});

  array_set(&/*q*/ s, main__Token_key_pub, &(string[]){tos2((byte *)"pub")});

  array_set(&/*q*/ s, main__Token_key_import_const,
            &(string[]){tos2((byte *)"import_const")});

  array_set(&/*q*/ s, main__Token_key_in, &(string[]){tos2((byte *)"in")});

  array_set(&/*q*/ s, main__Token_key_atomic,
            &(string[]){tos2((byte *)"atomic")});

  array_set(&/*q*/ s, main__Token_key_orelse, &(string[]){tos2((byte *)"or")});

  array_set(&/*q*/ s, main__Token_key_global,
            &(string[]){tos2((byte *)"__global")});

  array_set(&/*q*/ s, main__Token_key_union,
            &(string[]){tos2((byte *)"union")});

  array_set(&/*q*/ s, main__Token_key_static,
            &(string[]){tos2((byte *)"static")});

  array_set(&/*q*/ s, main__Token_key_as, &(string[]){tos2((byte *)"as")});

  array_set(&/*q*/ s, main__Token_key_defer,
            &(string[]){tos2((byte *)"defer")});

  array_set(&/*q*/ s, main__Token_key_match,
            &(string[]){tos2((byte *)"match")});

  array_set(&/*q*/ s, main__Token_key_select,
            &(string[]){tos2((byte *)"select")});

  return s;

  v_array_free(s); // close_scope free
}
Token key_to_token(string key) {

  int tmp7 = 0;
  bool tmp8 = map_get(main__KEYWORDS, key, &tmp7);

  Token a = ((Token)(tmp7));

  return a;
}
bool is_key(string key) { return ((int)(key_to_token(key))) > 0; }
string Token_str(Token t) {

  return (*(string *)array__get(main__TokenStr, ((int)(t))));
}
bool Token_is_decl(Token t) {

  return t == main__Token_key_enum || t == main__Token_key_interface ||
         t == main__Token_func || t == main__Token_key_struct ||
         t == main__Token_key_type || t == main__Token_key_const ||
         t == main__Token_key_import_const || t == main__Token_key_pub ||
         t == main__Token_eof;
}
bool Token_is_assign(Token t) { return _IN(Token, t, main__AssignTokens); }
bool array_Token_contains(array_Token t, Token val) {

  array_Token tmp12 = t;
  ;
  for (int tmp13 = 0; tmp13 < tmp12.len; tmp13++) {
    Token tt = ((Token *)tmp12.data)[tmp13];

    if (tt == val) {

      return 1;
    };
  };

  return 0;
}
void Scanner_fgen(Scanner *scanner, string s_) {

  string s = s_;

  if (scanner->fmt_line_empty) {

    s = string_add(strings__repeat('\t', scanner->fmt_indent), s);
  };

  strings__Builder_write(&/* ? */ scanner->fmt_out, s);

  scanner->fmt_line_empty = 0;
}
void Scanner_fgenln(Scanner *scanner, string s_) {

  string s = s_;

  if (scanner->fmt_line_empty) {

    s = string_add(strings__repeat('\t', scanner->fmt_indent), s);
  };

  strings__Builder_writeln(&/* ? */ scanner->fmt_out, s);

  scanner->fmt_line_empty = 1;
}
void Parser_fgen(Parser *p, string s) { Scanner_fgen(p->scanner, s); }
void Parser_fspace(Parser *p) { Parser_fgen(p, tos2((byte *)" ")); }
void Parser_fgenln(Parser *p, string s) { Scanner_fgenln(p->scanner, s); }
Token Parser_peek(Parser *p) {

  while (1) {

    p->cgen->line = p->scanner->line_nr + 1;

    Token tok = Scanner_peek(p->scanner);

    if (tok != main__Token_nl) {

      return tok;
    };
  };

  return main__Token_eof;
}
void Parser_fmt_inc(Parser *p) { p->scanner->fmt_indent++; }
void Parser_fmt_dec(Parser *p) { p->scanner->fmt_indent--; }
void init_consts() {
#ifdef _WIN32
#ifndef _BOOTSTRAP_NO_UNICODE_STREAM
  _setmode(_fileno(stdout), _O_U8TEXT);
  SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),
                 ENABLE_PROCESSED_OUTPUT | 0x0004);
// ENABLE_VIRTUAL_TERMINAL_PROCESSING
#endif
#endif
  g_str_buf = malloc(1000);
  os__FILE_ATTR_READONLY = 0x1;
  os__FILE_ATTR_HIDDEN = 0x2;
  os__FILE_ATTR_SYSTEM = 0x4;
  os__FILE_ATTR_DIRECTORY = 0x10;
  os__FILE_ATTR_ARCHIVE = 0x20;
  os__FILE_ATTR_DEVICE = 0x40;
  os__FILE_ATTR_NORMAL = 0x80;
  os__FILE_ATTR_TEMPORARY = 0x100;
  os__FILE_ATTR_SPARSE_FILE = 0x200;
  os__FILE_ATTR_REPARSE_POINT = 0x400;
  os__FILE_ATTR_COMPRESSED = 0x800;
  os__FILE_ATTR_OFFLINE = 0x1000;
  os__FILE_ATTR_NOT_CONTENT_INDEXED = 0x2000;
  os__FILE_ATTR_ENCRYPTED = 0x4000;
  os__FILE_ATTR_INTEGRITY_STREAM = 0x8000;
  os__FILE_ATTR_VIRTUAL = 0x10000;
  os__FILE_ATTR_NO_SCRUB_DATA = 0x20000;
  os__FILE_TYPE_DISK = 0x1;
  os__FILE_TYPE_CHAR = 0x2;
  os__FILE_TYPE_PIPE = 0x3;
  os__FILE_TYPE_UNKNOWN = 0x0;
  os__FILE_INVALID_FILE_ID = (-1);
  os__S_IFMT = 0xF000;
  os__S_IFDIR = 0x4000;
  os__INVALID_HANDLE_VALUE = -1;
  os__STD_INPUT_HANDLE = -10;
  os__STD_OUTPUT_HANDLE = -11;
  os__STD_ERROR_HANDLE = -12;
  os__ENABLE_ECHO_INPUT = 0x0004;
  os__ENABLE_EXTENDED_FLAGS = 0x0080;
  os__ENABLE_INSERT_MODE = 0x0020;
  os__ENABLE_LINE_INPUT = 0x0002;
  os__ENABLE_MOUSE_INPUT = 0x0010;
  os__ENABLE_PROCESSED_INPUT = 0x0001;
  os__ENABLE_QUICK_EDIT_MODE = 0x0040;
  os__ENABLE_WINDOW_INPUT = 0x0008;
  os__ENABLE_VIRTUAL_TERMINAL_INPUT = 0x0200;
  os__ENABLE_PROCESSED_OUTPUT = 0x0001;
  os__ENABLE_WRAP_AT_EOL_OUTPUT = 0x0002;
  os__ENABLE_VIRTUAL_TERMINAL_PROCESSING = 0x0004;
  os__DISABLE_NEWLINE_AUTO_RETURN = 0x0008;
  os__ENABLE_LVB_GRID_WORLDWIDE = 0x0010;
  os__args = new_array_from_c_array(0, 0, sizeof(string), (string[]){0});
  os__PathSeparator = tos2((byte *)"\\");
  os__FORMAT_MESSAGE_ALLOCATE_BUFFER = 0x00000100;
  os__FORMAT_MESSAGE_ARGUMENT_ARRAY = 0x00002000;
  os__FORMAT_MESSAGE_FROM_HMODULE = 0x00000800;
  os__FORMAT_MESSAGE_FROM_STRING = 0x00000400;
  os__FORMAT_MESSAGE_FROM_SYSTEM = 0x00001000;
  os__FORMAT_MESSAGE_IGNORE_INSERTS = 0x00000200;
  os__SUBLANG_NEUTRAL = 0x00;
  os__SUBLANG_DEFAULT = 0x01;
  os__LANG_NEUTRAL = (os__SUBLANG_NEUTRAL);
  math__Log2E = 1.0 / math__Ln2;
  math__Log10E = 1.0 / math__Ln10;
  math__MaxI8 = (1 << 7) - 1;
  math__MinI8 = -1 << 7;
  math__MaxI16 = (1 << 15) - 1;
  math__MinI16 = -1 << 15;
  math__MaxI32 = (1 << 31) - 1;
  math__MinI32 = -1 << 31;
  math__MaxU8 = (1 << 8) - 1;
  math__MaxU16 = (1 << 16) - 1;
  math__MaxU32 = (1 << 32) - 1;
  math__MaxU64 = (1 << 64) - 1;
  time__MonthDays = new_array_from_c_array(
      12, 12, sizeof(int),
      (int[]){31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
  time__absoluteZeroYear = ((i64)(-292277022399));
  time__secondsPerHour = 60 * time__secondsPerMinute;
  time__secondsPerDay = 24 * time__secondsPerHour;
  time__secondsPerWeek = 7 * time__secondsPerDay;
  time__daysPer400Years = 365 * 400 + 97;
  time__daysPer100Years = 365 * 100 + 24;
  time__daysPer4Years = 365 * 4 + 1;
  time__daysBefore = new_array_from_c_array(
      13, 13, sizeof(int),
      (int[]){
          0,
          31,
          31 + 28,
          31 + 28 + 31,
          31 + 28 + 31 + 30,
          31 + 28 + 31 + 30 + 31,
          31 + 28 + 31 + 30 + 31 + 30,
          31 + 28 + 31 + 30 + 31 + 30 + 31,
          31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
          31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
          31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
          31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
          31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31,
      });
  time__Months = tos2((byte *)"JanFebMarAprMayJunJulAugSepOctNovDec");
  time__Days = tos2((byte *)"MonTueWedThuFriSatSun");
  main__CommonCHeaders = tos2((
      byte *)"\n\n#include <stdio.h>  // TODO remove all these includes, "
             "define all function signatures and types manually\n#include "
             "<stdlib.h>\n#include <signal.h>\n#include <stdarg.h> // for "
             "va_list\n#include <inttypes.h>  // int64_t etc\n#include "
             "<string.h> // memcpy\n\n#ifndef _WIN32\n#include "
             "<ctype.h>\n#include <locale.h> // tolower\n#include "
             "<sys/time.h>\n#include <unistd.h> // sleep	"
             "\n#endif\n\n#ifdef __APPLE__\n#include <libproc.h> // "
             "proc_pidpath\n#include <execinfo.h> // backtrace and "
             "backtrace_symbols_fd\n#endif\n\n#ifdef __linux__\n#include "
             "<execinfo.h> // backtrace and backtrace_symbols_fd\n#pragma weak "
             "backtrace\n#pragma weak backtrace_symbols_fd\n#endif\n\n#ifdef "
             "__linux__\n#include <sys/types.h>\n#include <sys/wait.h> // "
             "os__wait uses wait on nix\n#endif\n\n\n#define "
             "EMPTY_STRUCT_DECLARATION\n#define OPTION_CAST(x) (x)\n\n#ifdef "
             "_WIN32\n#define WIN32_LEAN_AND_MEAN\n#include <windows.h>\n\n// "
             "must be included after <windows.h>\n#ifndef __TINYC__\n#include "
             "<shellapi.h>\n#endif\n\n#include <io.h> // _waccess\n#include "
             "<fcntl.h> // _O_U8TEXT\n#include <direct.h> // "
             "_wgetcwd\n//#include <WinSock2.h>\n#ifdef _MSC_VER\n// On MSVC "
             "these are the same (as long as /volatile:ms is passed)\n#define "
             "_Atomic volatile\n\n// MSVC cannot parse some things "
             "properly\n//#undef EMPTY_STRUCT_DECLARATION\n//#define "
             "EMPTY_STRUCT_DECLARATION void *____dummy_variable\n#undef "
             "OPTION_CAST\n#define OPTION_CAST(x)\n#endif\n\nvoid "
             "pthread_mutex_lock(HANDLE *m) {\n	WaitForSingleObject(*m, "
             "INFINITE);\n}\n\nvoid pthread_mutex_unlock(HANDLE *m) {\n	"
             "ReleaseMutex(*m);\n}\n#else\n#include "
             "<pthread.h>\n#endif\n\n//================================== "
             "TYPEDEFS ================================*/\n\ntypedef int64_t "
             "i64;\ntypedef int16_t i16;\ntypedef int8_t i8;\ntypedef uint64_t "
             "u64;\ntypedef uint32_t u32;\ntypedef uint16_t u16;\ntypedef "
             "uint8_t byte;\ntypedef uint32_t rune;\ntypedef float "
             "f32;\ntypedef double f64;\ntypedef unsigned char* "
             "byteptr;\ntypedef int* intptr;\ntypedef void* voidptr;\ntypedef "
             "struct array array;\ntypedef struct map map;\ntypedef array "
             "array_string;\ntypedef array array_int;\ntypedef array "
             "array_byte;\ntypedef array array_f32;\ntypedef array "
             "array_f64;\ntypedef map map_int;\ntypedef map "
             "map_string;\n#ifndef bool\n	typedef int bool;\n	"
             "#define true 1\n	#define false "
             "0\n#endif\n\n//============================== HELPER C MACROS "
             "=============================*/\n\n#define _PUSH(arr, val, tmp, "
             "tmp_typ) {tmp_typ tmp = (val); array__push(arr, &tmp);}\n#define "
             "_PUSH_MANY(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); "
             "array__push_many(arr, tmp.data, tmp.len);}\n#define _IN(typ, "
             "val, arr) array_##typ##_contains(arr, val)\n#define _IN_MAP(val, "
             "m) map__exists(m, val)\n//#define ALLOC_INIT(type, ...) (type "
             "*)memdup((type[]){ __VA_ARGS__ }, "
             "sizeof(type))\n\n//================================== GLOBALS "
             "=================================*/\nbyteptr g_str_buf;\nint "
             "load_so(byteptr);\nvoid reload_so();\nvoid init_consts();\n\n");
  main__Version = tos2((byte *)"0.1.18");
  main__SupportedPlatforms = new_array_from_c_array(
      8, 8, sizeof(string),
      (string[]){tos2((byte *)"windows"), tos2((byte *)"mac"),
                 tos2((byte *)"linux"), tos2((byte *)"freebsd"),
                 tos2((byte *)"openbsd"), tos2((byte *)"netbsd"),
                 tos2((byte *)"dragonfly"), tos2((byte *)"msvc")});
  main__ModPath = string_add(os__home_dir(), tos2((byte *)"/.vmodules/"));
  main__HelpText = tos2(
      (byte *)"\nUsage: v [options] [file | directory]\n\nOptions:\n  -        "
              "         Read from stdin (Default; Interactive mode if in a "
              "tty)\n  -h, help          Display this information.\n  -v, "
              "version       Display compiler version.\n  -prod             "
              "Build an optimized executable.\n  -o <file>         Place "
              "output into <file>.\n  -obf              Obfuscate the "
              "resulting binary.\n  -show_c_cmd       Print the full C "
              "compilation command and how much time it took.\n  -debug        "
              "    Leave a C file for debugging in .program.c.\n  -live        "
              "     Enable hot code reloading (required by functions marked "
              "with [live]).\n  fmt               Run vfmt to format the "
              "source code.\n  up                Update V.\n  run              "
              " Build and execute a V program. You can add arguments after the "
              "file name.\n  build module      Compile a module into an object "
              "file.\n\n\nFiles:\n  <file>_test.v     Test file.\n");
  main__HKEY_LOCAL_MACHINE = ((RegKey)(0x80000002));
  main__KEY_QUERY_VALUE = (0x0001);
  main__KEY_WOW64_32KEY = (0x0200);
  main__KEY_ENUMERATE_SUB_KEYS = (0x0008);
  main__EmptyFn =
      (Fn *)memdup(&(Fn){.name = tos((byte *)"", 0),
                         .mod = tos((byte *)"", 0),
                         .local_vars = new_array(0, 1, sizeof(Var)),
                         .var_idx = 0,
                         .args = new_array(0, 1, sizeof(Var)),
                         .is_interface = 0,
                         .scope_level = 0,
                         .typ = tos((byte *)"", 0),
                         .is_c = 0,
                         .receiver_typ = tos((byte *)"", 0),
                         .is_public = 0,
                         .is_method = 0,
                         .returns_error = 0,
                         .is_decl = 0,
                         .defer_text = new_array(0, 1, sizeof(string))},
                   sizeof(Fn));
  main__MainFn =
      (Fn *)memdup(&(Fn){.name = tos2((byte *)"main"),
                         .mod = tos((byte *)"", 0),
                         .local_vars = new_array(0, 1, sizeof(Var)),
                         .var_idx = 0,
                         .args = new_array(0, 1, sizeof(Var)),
                         .is_interface = 0,
                         .scope_level = 0,
                         .typ = tos((byte *)"", 0),
                         .is_c = 0,
                         .receiver_typ = tos((byte *)"", 0),
                         .is_public = 0,
                         .is_method = 0,
                         .returns_error = 0,
                         .is_decl = 0,
                         .defer_text = new_array(0, 1, sizeof(string))},
                   sizeof(Fn));
  main__and_or_error = string_add(
      tos2((byte *)"use `()` to make the boolean expression clear\n"),
      tos2((byte *)"for example: `(a && b) || c` instead of `a && b || c`"));
  main__CReserved = new_array_from_c_array(
      41, 41, sizeof(string),
      (string[]){
          tos2((byte *)"exit"),     tos2((byte *)"unix"),
          tos2((byte *)"error"),    tos2((byte *)"malloc"),
          tos2((byte *)"calloc"),   tos2((byte *)"free"),
          tos2((byte *)"panic"),    tos2((byte *)"auto"),
          tos2((byte *)"break"),    tos2((byte *)"case"),
          tos2((byte *)"char"),     tos2((byte *)"const"),
          tos2((byte *)"continue"), tos2((byte *)"default"),
          tos2((byte *)"do"),       tos2((byte *)"double"),
          tos2((byte *)"else"),     tos2((byte *)"enum"),
          tos2((byte *)"extern"),   tos2((byte *)"float"),
          tos2((byte *)"for"),      tos2((byte *)"goto"),
          tos2((byte *)"if"),       tos2((byte *)"inline"),
          tos2((byte *)"int"),      tos2((byte *)"long"),
          tos2((byte *)"register"), tos2((byte *)"restrict"),
          tos2((byte *)"return"),   tos2((byte *)"short"),
          tos2((byte *)"signed"),   tos2((byte *)"sizeof"),
          tos2((byte *)"static"),   tos2((byte *)"struct"),
          tos2((byte *)"switch"),   tos2((byte *)"typedef"),
          tos2((byte *)"union"),    tos2((byte *)"unsigned"),
          tos2((byte *)"void"),     tos2((byte *)"volatile"),
          tos2((byte *)"while"),
      });
  main__number_types = new_array_from_c_array(
      11, 11, sizeof(string),
      (string[]){tos2((byte *)"number"), tos2((byte *)"int"),
                 tos2((byte *)"i8"), tos2((byte *)"i16"), tos2((byte *)"u16"),
                 tos2((byte *)"u32"), tos2((byte *)"byte"), tos2((byte *)"i64"),
                 tos2((byte *)"u64"), tos2((byte *)"f32"),
                 tos2((byte *)"f64")});
  main__float_types = new_array_from_c_array(
      2, 2, sizeof(string),
      (string[]){tos2((byte *)"f32"), tos2((byte *)"f64")});
  main__TokenStr = build_token_str();
  main__KEYWORDS = build_keys();
  main__AssignTokens = new_array_from_c_array(
      11, 11, sizeof(Token),
      (Token[]){main__Token_assign, main__Token_plus_assign,
                main__Token_minus_assign, main__Token_mult_assign,
                main__Token_div_assign, main__Token_xor_assign,
                main__Token_mod_assign, main__Token_or_assign,
                main__Token_and_assign, main__Token_righ_shift_assign,
                main__Token_left_shift_assign});
}

string _STR(const char *fmt, ...) {
  va_list argptr;
  va_start(argptr, fmt);
  size_t len = vsnprintf(0, 0, fmt, argptr) + 1;
  va_end(argptr);
  byte *buf = malloc(len);
  va_start(argptr, fmt);
  vsprintf((char *)buf, fmt, argptr);
  va_end(argptr);
#ifdef DEBUG_ALLOC
  puts("_STR:");
  puts(buf);
#endif
  return tos2(buf);
}

string _STR_TMP(const char *fmt, ...) {
  va_list argptr;
  va_start(argptr, fmt);
  // size_t len = vsnprintf(0, 0, fmt, argptr) + 1;
  va_end(argptr);
  va_start(argptr, fmt);
  vsprintf((char *)g_str_buf, fmt, argptr);
  va_end(argptr);
#ifdef DEBUG_ALLOC
  // puts("_STR_TMP:");
  // puts(g_str_buf);
#endif
  return tos2(g_str_buf);
}
