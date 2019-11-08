#define V_COMMIT_HASH "db4a7ed"
#ifndef V_COMMIT_HASH
#define V_COMMIT_HASH "5a8c3da"
#endif

#include <stdio.h> // TODO remove all these includes, define all function signatures and types manually
#include <stdlib.h>

//#include "fns.h"
#include <inttypes.h> // int64_t etc
#include <signal.h>
#include <stdarg.h> // for va_list
#include <string.h> // memcpy

#ifndef _WIN32
#include <ctype.h>
#include <locale.h> // tolower
#include <sys/time.h>
#include <unistd.h> // sleep
#else
#if defined(__MSVCRT_VERSION__) && __MSVCRT_VERSION__ < __MSVCR90_DLL
#error Please upgrade your MinGW distribution to use msvcr90.dll or later.
#endif
#endif

#if defined(__CYGWIN__) && !defined(_WIN32)
#error Cygwin is not supported, please use MinGW or Visual Studio.
#endif

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h> // os__wait uses wait on nix
#endif

#ifdef __FreeBSD__
#include <sys/types.h>
#include <sys/wait.h> // os__wait uses wait on nix
#endif

#ifdef __DragonFly__
#include <sys/types.h>
#include <sys/wait.h> // os__wait uses wait on nix
#endif

#ifdef __OpenBSD__
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h> // os__wait uses wait on nix
#endif

#define EMPTY_STRUCT_DECLARATION
#define EMPTY_STRUCT_INITIALIZATION 0
// Due to a tcc bug, the length of an array needs to be specified, but GCC
// crashes if it is...
#define EMPTY_ARRAY_OF_ELEMS(x, n) (x[])
#define TCCSKIP(x) x

#ifdef __TINYC__
#undef EMPTY_STRUCT_INITIALIZATION
#define EMPTY_STRUCT_INITIALIZATION
#undef EMPTY_ARRAY_OF_ELEMS
#define EMPTY_ARRAY_OF_ELEMS(x, n) (x[n])
#undef TCCSKIP
#define TCCSKIP(x)
#endif

#define OPTION_CAST(x) (x)

#ifdef _WIN32
#define WINVER 0x0600
#define _WIN32_WINNT 0x0600
#define WIN32_LEAN_AND_MEAN
#define _UNICODE
#define UNICODE
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
#undef EMPTY_STRUCT_DECLARATION
#undef OPTION_CAST

#define EMPTY_STRUCT_DECLARATION int ____dummy_variable
#define OPTION_CAST(x)
#endif

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
    array_push(arr, &tmp);                                                     \
  }
#define _PUSH_MANY(arr, val, tmp, tmp_typ)                                     \
  {                                                                            \
    tmp_typ tmp = (val);                                                       \
    array_push_many(arr, tmp.data, tmp.len);                                   \
  }
#define _IN(typ, val, arr) array_##typ##_contains(arr, val)
#define _IN_MAP(val, m) map_exists(m, val)
#define DEFAULT_EQUAL(a, b) (a == b)
#define DEFAULT_NOT_EQUAL(a, b) (a != b)
#define DEFAULT_LT(a, b) (a < b)
#define DEFAULT_LE(a, b) (a <= b)
#define DEFAULT_GT(a, b) (a > b)
#define DEFAULT_GE(a, b) (a >= b)
//================================== GLOBALS =================================*/
byteptr g_str_buf;
int load_so(byteptr);
void reload_so();

int g_test_oks = 0;
int g_test_fails = 0;
#include <errno.h>
#include <float.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <time.h>
typedef struct array array;
typedef array array_string;
typedef array array_bool;
typedef array array_byte;
typedef array array_int;
typedef array array_char;
typedef array array_T;
typedef array array_i64;
typedef array array_f32;
typedef struct hashmap hashmap;
typedef array array_hashmapentry;
typedef struct hashmapentry hashmapentry;
typedef struct map map;
typedef struct mapnode mapnode;
typedef struct Option Option;
typedef struct string string;
typedef struct ustring ustring;
typedef struct strings__Builder strings__Builder;
typedef struct os__File os__File;
typedef struct os__FileInfo os__FileInfo;
typedef Option Option_string;
typedef Option Option_bool;
typedef Option Option_bool;
typedef array array_ustring;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef struct _V_MulRet_int_V_bool _V_MulRet_int_V_bool;
typedef struct os__Result os__Result;
typedef struct varg_string varg_string;

typedef voidptr HANDLE; // type alias name="HANDLE" parent=`voidptr`
typedef struct os__Filetime os__Filetime;
typedef struct os__Win32finddata os__Win32finddata;
typedef struct os__ProcessInformation os__ProcessInformation;
typedef struct os__StartupInfo os__StartupInfo;
typedef struct os__SecurityAttributes os__SecurityAttributes;
typedef Option Option_array_string;
typedef Option Option_string;
typedef Option Option_os__Result;
typedef struct rand__Pcg32 rand__Pcg32;
typedef struct rand__Splitmix64 rand__Splitmix64;
typedef struct compiler__CFlag compiler__CFlag;
typedef array array_compiler__CFlag;
typedef Option Option_bool;
typedef struct compiler__CGen compiler__CGen;
typedef array array_compiler__Type;
typedef struct compiler__ScannerPos compiler__ScannerPos;
typedef struct compiler__DepGraphNode compiler__DepGraphNode;
typedef struct compiler__DepGraph compiler__DepGraph;
typedef array array_compiler__DepGraphNode;
typedef struct compiler__DepSet compiler__DepSet;
typedef struct compiler__Fn compiler__Fn;
typedef array array_compiler__Var;
typedef array array_compiler__TypeInst;
typedef struct compiler__TypeInst compiler__TypeInst;
typedef Option Option_compiler__Var;
typedef Option Option_compiler__Var;
typedef struct _V_MulRet_string_V_array_string _V_MulRet_string_V_array_string;
typedef array array_compiler__Fn;
typedef struct compiler__V compiler__V;
typedef array array_compiler__Parser;
typedef struct compiler__Preferences compiler__Preferences;
typedef Option Option_int;
typedef struct compiler__VhGen compiler__VhGen;
typedef array array_compiler__Token;
typedef struct compiler__ImportTable compiler__ImportTable;
typedef Option Option_string;
typedef struct compiler__MsvcResult compiler__MsvcResult;
typedef voidptr RegKey; // type alias name="RegKey" parent=`voidptr`
typedef Option Option_string;
typedef struct compiler__WindowsKit compiler__WindowsKit;
typedef Option Option_compiler__WindowsKit;
typedef struct compiler__VsInstallation compiler__VsInstallation;
typedef Option Option_compiler__VsInstallation;
typedef Option Option_compiler__MsvcResult;
typedef struct compiler__MsvcStringFlags compiler__MsvcStringFlags;
typedef struct compiler__Parser compiler__Parser;
typedef map map_bool;
typedef struct compiler__IndexConfig compiler__IndexConfig;
typedef struct _V_MulRet_string_V_string _V_MulRet_string_V_string;
typedef struct _V_MulRet_bool_V_string _V_MulRet_bool_V_string;
typedef struct compiler__Scanner compiler__Scanner;
typedef struct compiler__ScanRes compiler__ScanRes;
typedef struct compiler__Table compiler__Table;
typedef map map_compiler__Type;
typedef map map_compiler__Fn;
typedef array array_compiler__VargAccess;
typedef struct compiler__VargAccess compiler__VargAccess;
typedef struct compiler__Name compiler__Name;
typedef struct compiler__Var compiler__Var;
typedef struct compiler__Type compiler__Type;
typedef struct compiler__TypeNode compiler__TypeNode;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Var;
typedef Option Option_compiler__Var;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Var;
typedef struct compiler__Token compiler__Token;
typedef array array_compiler__TokenKind;
typedef struct time__Time time__Time;
typedef Option Option_int;
typedef struct benchmark__Benchmark benchmark__Benchmark;
typedef Option Option_string;
typedef Option Option_bool;
typedef Option Option_bool;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_array_string;
typedef Option Option_string;
typedef Option Option_os__Result;
typedef Option Option_bool;
typedef map map_compiler__DepGraphNode;
typedef map map_compiler__DepSet;
typedef Option Option_compiler__Var;
typedef Option Option_compiler__Var;
typedef int compiler__BuildMode;
typedef int compiler__OS;
typedef int compiler__Pass;
typedef Option Option_int;
typedef Option Option_string;
typedef Option Option_string;
typedef Option Option_compiler__WindowsKit;
typedef Option Option_compiler__VsInstallation;
typedef Option Option_compiler__MsvcResult;
typedef int compiler__IndexType;
typedef int compiler__NameCategory;
typedef int compiler__AccessMod;
typedef int compiler__TypeCategory;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Var;
typedef Option Option_compiler__Var;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Fn;
typedef Option Option_compiler__Var;
typedef int compiler__TokenKind;
typedef int time__FormatTime;
typedef int time__FormatDate;
typedef int time__FormatDelimiter;
typedef Option Option_int;
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
  byte data[300];
  string error;
  int ecode;
  bool ok;
  bool is_none;
};

//----
struct _V_MulRet_string_V_string {
  string var_0;
  string var_1;
};

struct compiler__CFlag {
  string mod;
  string os;
  string name;
  string value;
};

struct compiler__MsvcResult {
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

struct compiler__WindowsKit {
  string um_lib_path;
  string ucrt_lib_path;
  string um_include_path;
  string ucrt_include_path;
  string shared_include_path;
};

struct compiler__VsInstallation {
  string include_path;
  string lib_path;
  string exe_path;
};

struct os__File {
  void *cfile;
};

struct _V_MulRet_int_V_bool {
  int var_0;
  bool var_1;
};

struct _V_MulRet_bool_V_string {
  bool var_0;
  string var_1;
};

struct _V_MulRet_string_V_array_string {
  string var_0;
  array_string var_1;
};

struct benchmark__Benchmark {
  i64 bench_start_time;
  i64 bench_end_time;
  i64 step_start_time;
  i64 step_end_time;
  int ntotal;
  int nok;
  int nfail;
  bool verbose;
};

struct compiler__Table {
  map_compiler__Type typesmap;
  array_compiler__Var consts;
  map_compiler__Fn fns;
  map_int obf_ids;
  array_string modules;
  array_string imports;
  array_compiler__CFlag cflags;
  int fn_cnt;
  bool obfuscate;
  array_compiler__VargAccess varg_access;
};

struct compiler__CGen {
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
  compiler__Pass pass;
  bool nogen;
  array_string prev_tmps;
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

struct compiler__DepGraphNode {
  string name;
  array_string deps;
};

struct compiler__DepGraph {
  bool acyclic;
  array_compiler__DepGraphNode nodes;
};

struct compiler__DepSet {
  array_string items;
};

struct compiler__ImportTable {
  map_string imports;
  array_string used_imports;
  map_int import_tok_idx;
};

struct compiler__IndexConfig {
  bool is_map;
  bool is_str;
  bool is_ptr;
  bool is_arr;
  bool is_arr0;
  bool is_slice;
};

struct compiler__MsvcStringFlags {
  array_string real_libs;
  array_string inc_paths;
  array_string lib_paths;
  array_string other_flags;
};

struct compiler__Name {
  compiler__NameCategory cat;
  int idx;
};

struct compiler__Preferences {
  compiler__BuildMode build_mode;
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
  bool is_debug;
  bool is_vlines;
  bool is_keep_c;
  bool is_cache;
  bool is_stats;
  bool no_auto_free;
  string cflags;
  string ccompiler;
  bool building_v;
  bool autofree;
  bool compress;
  string comptime_define;
  bool fast;
  bool enable_globals;
};

struct compiler__ScanRes {
  compiler__TokenKind tok;
  string lit;
};

struct compiler__ScannerPos {
  int pos;
  int line_nr;
  int last_nl_pos;
};

struct compiler__TypeInst {
  map_string inst;
  bool done;
};

struct compiler__Token {
  compiler__TokenKind tok;
  string lit;
  int line_nr;
  int name_idx;
  int col;
};

struct compiler__VargAccess {
  string fn_name;
  int tok_idx;
  int index;
};

struct compiler__Var {
  string typ;
  string name;
  int idx;
  bool is_arg;
  bool is_const;
  array_compiler__Var args;
  string attr;
  bool is_mut;
  bool is_alloc;
  bool is_returned;
  bool ptr;
  bool ref;
  string parent_fn;
  string mod;
  compiler__AccessMod access_mod;
  bool is_global;
  bool is_used;
  bool is_changed;
  int scope_level;
  bool is_c;
  bool is_moved;
  int line_nr;
  int token_idx;
  bool is_for_var;
  bool is_public;
};

struct hashmap {
  int cap;
  array_string keys;
  array_hashmapentry table;
  int elm_size;
  int nr_collisions;
};

struct hashmapentry {
  string key;
  int val;
  hashmapentry *next;
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

struct os__Filetime {
  u32 dwLowDateTime;
  u32 dwHighDateTime;
};

struct os__ProcessInformation {
  void *hProcess;
  void *hThread;
  u32 dwProcessId;
  u32 dwThreadId;
};

struct os__StartupInfo {
  u32 cb;
  u16 *lpReserved;
  u16 *lpDesktop;
  u16 *lpTitle;
  u32 dwX;
  u32 dwY;
  u32 dwXSize;
  u32 dwYSize;
  u32 dwXCountChars;
  u32 dwYCountChars;
  u32 dwFillAttribute;
  u32 dwFlags;
  u16 wShowWindow;
  u16 cbReserved2;
  byte *lpReserved2;
  void *hStdInput;
  void *hStdOutput;
  void *hStdError;
};

struct os__SecurityAttributes {
  u32 nLength;
  void *lpSecurityDescriptor;
  bool bInheritHandle;
};

struct rand__Pcg32 {
  u64 state;
  u64 inc;
};

struct rand__Splitmix64 {
  u64 state;
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

struct varg_string {
  int len;
  string args[4];
};

struct compiler__V {
  compiler__OS os;
  string out_name_c;
  array_string files;
  string dir;
  compiler__Table *table;
  compiler__CGen *cgen;
  compiler__Preferences *pref;
  string lang_dir;
  string out_name;
  string vroot;
  string mod;
  array_compiler__Parser parsers;
  strings__Builder vgen_buf;
  map_int file_parser_idx;
  array_string cached_mods;
};

struct compiler__Fn {
  string name;
  string mod;
  array_compiler__Var args;
  bool is_interface;
  int scope_level;
  string typ;
  string receiver_typ;
  bool is_c;
  bool is_public;
  bool is_method;
  bool is_decl;
  bool is_unsafe;
  bool is_deprecated;
  bool is_variadic;
  bool is_generic;
  bool returns_error;
  array_string defer_text;
  array_string type_pars;
  array_compiler__TypeInst type_inst;
  compiler__TypeInst dispatch_of;
  int body_idx;
  int fn_name_token_idx;
  string comptime_define;
  bool is_used;
};

struct compiler__Scanner {
  string file_path;
  string text;
  int pos;
  int line_nr;
  int last_nl_pos;
  bool inside_string;
  bool inter_start;
  bool inter_end;
  bool debug;
  string line_comment;
  bool started;
  strings__Builder fmt_out;
  int fmt_indent;
  bool fmt_line_empty;
  compiler__TokenKind prev_tok;
  string fn_name;
  bool should_print_line_on_error;
  bool should_print_errors_in_color;
  bool should_print_relative_paths_on_error;
  byte quote;
  array_int line_ends;
  int nlines;
  bool is_vh;
};

struct compiler__VhGen {
  int i;
  strings__Builder consts;
  strings__Builder fns;
  strings__Builder types;
  array_compiler__Token tokens;
};

struct os__Win32finddata {
  u32 dwFileAttributes;
  os__Filetime ftCreationTime;
  os__Filetime ftLastAccessTime;
  os__Filetime ftLastWriteTime;
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

struct compiler__Parser {
  string file_path;
  string file_name;
  string file_platform;
  string file_pcguard;
  compiler__V *v;
  compiler__Preferences *pref;
  compiler__Scanner *scanner;
  array_compiler__Token tokens;
  int token_idx;
  compiler__TokenKind tok;
  compiler__TokenKind prev_tok;
  compiler__TokenKind prev_tok2;
  string lit;
  compiler__CGen *cgen;
  compiler__Table *table;
  compiler__ImportTable import_table;
  compiler__Pass pass;
  compiler__OS os;
  bool inside_const;
  compiler__Var expr_var;
  bool has_immutable_field;
  compiler__Var first_immutable_field;
  string assigned_type;
  string expected_type;
  int tmp_cnt;
  bool builtin_mod;
  bool inside_if_expr;
  bool inside_unwrapping_match_statement;
  bool inside_return_expr;
  bool inside_unsafe;
  bool is_struct_init;
  bool is_var_decl;
  int if_expr_cnt;
  int for_expr_cnt;
  bool ptr_cast;
  bool calling_c;
  compiler__Fn cur_fn;
  array_compiler__Var local_vars;
  int var_idx;
  bool returns;
  string vroot;
  bool is_c_struct_init;
  bool is_empty_c_struct_init;
  bool is_c_fn_call;
  bool can_chash;
  string attr;
  bool v_script;
  string var_decl_name;
  bool is_alloc;
  bool is_const_literal;
  bool in_dispatch;
  bool is_vgen;
  bool is_vweb;
  bool is_sql;
  bool is_js;
  int sql_i;
  array_string sql_params;
  array_string sql_types;
  bool is_vh;
  string mod;
};

struct compiler__Type {
  string mod;
  string name;
  compiler__TypeCategory cat;
  bool is_public;
  array_compiler__Var fields;
  array_compiler__Fn methods;
  string parent;
  compiler__Fn func;
  bool is_c;
  array_string enum_vals;
  array_string gen_types;
  bool is_placeholder;
  bool gen_str;
};

struct compiler__TypeNode {
  compiler__TypeNode *next;
  compiler__Type typ;
};

string _STR(const char *, ...);

string _STR_TMP(const char *, ...);

array new_array(int mylen, int cap, int elm_size);
array make(int len, int cap, int elm_size);
array new_array_from_c_array(int len, int cap, int elm_size, void *c_array);
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size,
                                      void *c_array);
void array_ensure_cap(array *a, int required);
array array_repeat_old(void *val, int nr_repeats, int elm_size);
array array_repeat(array a, int nr_repeats);
void array_sort_with_compare(array *a, void *compare);
void array_insert(array *a, int i, void *val);
void array_prepend(array *a, void *val);
void v_array_delete(array *a, int i);
void *array_get(array a, int i);
void *array_first(array a);
void *array_last(array a);
array array_left(array a, int n);
array array_right(array a, int n);
array array_slice2(array a, int start, int _end, bool end_max);
array array_slice(array a, int start, int _end);
void array_set(array *a, int i, void *val);
void array_push(array *a, void *val);
void array_push_many(array *a, void *val, int size);
array array_reverse(array a);
array array_clone(array a);
void v_array_free(array a);
string array_string_str(array_string a);
string array_bool_str(array_bool a);
string array_byte_hex(array_byte b);
int copy(array_byte dst, array_byte src);
int compare_ints(int a, int b);
void array_int_sort(array_int *a);
int array_string_index(array_string a, string v);
int array_int_index(array_int a, int v);
int array_byte_index(array_byte a, byte v);
int array_char_index(array_char a, char v);
int array_int_reduce(array_int a, int (*iter)(int accum, int curr /*FFF*/),
                     int accum_start);
bool array_int_eq(array_int a, array_int a2);
bool array_i64_eq(array_i64 a, array_i64 a2);
bool array_string_eq(array_string a, array_string a2);
bool array_byte_eq(array_byte a, array_byte a2);
bool array_f32_eq(array_f32 a, array_f32 a2);
void builtin__init();
void v_exit(int code);
bool isnil(void *v);
void on_panic(int (*f)(int /*FFF*/));
void print_backtrace_skipping_top_frames(int skipframes);
void print_backtrace();
void panic_debug(int line_no, string file, string mod, string fn_name,
                 string s);
void v_panic(string s);
void println(string s);
void eprintln(string s);
void print(string s);
byte *v_malloc(int n);
byte *v_calloc(int n);
void v_free(void *ptr);
void *memdup(void *src, int sz);
void v_ptr_free(void *ptr);
int is_atty(int fd);
int backtrace(void *a, int b);
byteptr *backtrace_symbols(void *, int);
void backtrace_symbols_fd(void *, int, int);
int proc_pidpath(int, void *, int);
string f64_str(f64 d);
string f32_str(f32 d);
f32 f32_abs(f32 a);
f64 f64_abs(f64 a);
bool f64_eq(f64 a, f64 b);
bool f32_eq(f32 a, f32 b);
bool f64_eqbit(f64 a, f64 b);
bool f32_eqbit(f32 a, f32 b);
bool f64_ne(f64 a, f64 b);
bool f32_ne(f32 a, f32 b);
bool f64_nebit(f64 a, f64 b);
bool f32_nebit(f32 a, f32 b);
bool f64_lt(f64 a, f64 b);
bool f32_lt(f32 a, f32 b);
bool f64_ltbit(f64 a, f64 b);
bool f32_ltbit(f32 a, f32 b);
bool f64_le(f64 a, f64 b);
bool f32_le(f32 a, f32 b);
bool f64_lebit(f64 a, f64 b);
bool f32_lebit(f32 a, f32 b);
bool f64_gt(f64 a, f64 b);
bool f32_gt(f32 a, f32 b);
bool f64_gtbit(f64 a, f64 b);
bool f32_gtbit(f32 a, f32 b);
bool f64_ge(f64 a, f64 b);
bool f32_ge(f32 a, f32 b);
bool f64_gebit(f64 a, f64 b);
bool f32_gebit(f32 a, f32 b);
hashmap new_hashmap(int planned_nr_items);
void hashmap_set(hashmap *m, string key, int val);
int hashmap_get(hashmap *m, string key);
static inline f64 b_fabs(int v);
string ptr_str(void *ptr);
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
map new_map(int cap, int elm_size);
map new_map_init(int cap, int elm_size, string *keys, void *vals);
mapnode *new_node(string key, void *val, int element_size);
void map_insert(map *m, mapnode *n, string key, void *val);
bool mapnode_find(mapnode *n, string key, void *out, int element_size);
bool mapnode_find2(mapnode *n, string key, int element_size);
void map_set(map *m, string key, void *val);
int preorder_keys(mapnode *node, array_string *keys, int key_i);
array_string map_keys(map *m);
bool map_get(map m, string key, void *out);
void v_mapnode_delete(mapnode *n, string key, int element_size);
void v_map_delete(map *m, string key);
bool map_exists(map m, string key);
void map_print(map m);
void v_mapnode_free(mapnode *n);
void v_map_free(map *m);
string map_string_str(map_string m);
Option opt_ok(void *data, int size);
Option opt_none();
Option v_error(string s);
Option error_with_code(string s, int code);
int vstrlen(byte *s);
string tos(byte *s, int len);
string tos_clone(byte *s);
string tos2(byte *s);
string tos3(char *s);
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
string string_substr2(string s, int start, int _end, bool end_max);
string string_substr(string s, int start, int end);
int string_index(string s, string p);
int string_index_kmp(string s, string p);
int string_index_any(string s, string chars);
int string_last_index(string s, string p);
int string_index_after(string s, string p, int start);
int string_index_byte(string s, byte c);
int string_last_index_byte(string s, byte c);
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
bool ustring_eq(ustring u, ustring a);
bool ustring_ne(ustring u, ustring a);
bool ustring_lt(ustring u, ustring a);
bool ustring_le(ustring u, ustring a);
bool ustring_gt(ustring u, ustring a);
bool ustring_ge(ustring u, ustring a);
ustring ustring_add(ustring u, ustring a);
int ustring_index_after(ustring u, ustring p, int start);
int ustring_count(ustring u, ustring substr);
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
string string_repeat(string s, int count);
int utf8_char_len(byte b);
string utf32_to_str(u32 code);
string utf32_to_str_no_malloc(u32 code, void *buf);
int string_utf32_code(string _rune);
u16 *string_to_wide(string _str);
string string_from_wide(u16 *_wstr);
string string_from_wide2(u16 *_wstr, int len);
int utf8_len(byte c);
int utf8_getchar();
strings__Builder strings__new_builder(int initial_size);
void strings__Builder_write(strings__Builder *b, string s);
void strings__Builder_writeln(strings__Builder *b, string s);
string strings__Builder_str(strings__Builder b);
void strings__Builder_cut(strings__Builder *b, int n);
void strings__Builder_free(strings__Builder *b);
int strings__levenshtein_distance(string a, string b);
f32 strings__levenshtein_distance_percentage(string a, string b);
f32 strings__dice_coefficient(string s1, string s2);
string strings__repeat(byte c, int n);
byte strconv__byte_to_lower(byte c);
u64 strconv__parse_uint(string s, int _base, int _bit_size);
i64 strconv__parse_int(string _s, int base, int _bit_size);
int strconv__atoi(string s);
bool strconv__underscore_ok(string s);
array_byte os__File_read_bytes(os__File f, int size);
array_byte os__File_read_bytes_at(os__File f, int size, int pos);
Option_string os__read_file(string path);
int os__file_size(string path);
void os__mv(string old, string new);
Option_bool os__cp(string old, string new);
Option_bool os__cp_r(string source_path, string dest_path, bool overwrite);
FILE *os__vfopen(string path, string mode);
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
void *os__vpopen(string path);
_V_MulRet_int_V_bool os__posix_wait4_to_exit_status(int waitret);
int os__vpclose(void *f);
int os__system(string cmd);
string os__sigint_to_signal_name(int si);
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
void os__walk(string path, void (*fnc)(string path /*FFF*/));
void os__signal(int signum, void *handler);
int os__fork();
int os__wait();
int os__file_last_mod_unix(string path);
void os__log(string s);
void os__flush_stdout();
void os__print_backtrace();
void os__mkdir_all(string path);
string os__join(string base, varg_string *dirs);
array_string os__init_os_args(int argc, byteptr *argv);
Option_array_string os__ls(string path);
bool os__dir_exists(string path);
void os__mkdir(string path);
HANDLE os__get_file_handle(string path);
Option_string os__get_module_filename(HANDLE handle);
void *os__ptr_win_get_error_msg(u32 code);
string os__get_error_msg(int code);
Option_os__Result os__exec(string cmd);
rand__Pcg32 rand__new_pcg32(u64 initstate, u64 initseq);
static inline u32 rand__Pcg32_next(rand__Pcg32 *rng);
static inline u32 rand__Pcg32_bounded_next(rand__Pcg32 *rng, u32 bound);
void rand__seed(int s);
int rand__next(int max);
int rand__rand_r(int *seed);
rand__Splitmix64 rand__new_splitmix64(u64 seed);
static inline u64 rand__Splitmix64_next(rand__Splitmix64 *rng);
static inline u64 rand__Splitmix64_bounded_next(rand__Splitmix64 *rng,
                                                u64 bound);
bool term__can_show_color_on_stdout();
bool term__can_show_color_on_stderr();
bool term__supports_escape_sequences(int fd);
string term__ok_message(string s);
string term__fail_message(string s);
string term__format(string msg, string open, string close);
string term__format_rgb(int r, int g, int b, string msg, string open,
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
void compiler__todo();
void compiler__V_cc(compiler__V *v);
void compiler__V_cc_windows_cross(compiler__V *c);
void compiler__V_build_thirdparty_obj_files(compiler__V *c);
string compiler__find_c_compiler();
string compiler__find_c_compiler_default();
string compiler__find_c_compiler_thirdparty_options();
string compiler__get_cmdline_cflags(array_string args);
string compiler__CFlag_str(compiler__CFlag *c);
array_compiler__CFlag compiler__V_get_os_cflags(compiler__V *v);
array_compiler__CFlag compiler__V_get_rest_of_module_cflags(compiler__V *v,
                                                            compiler__CFlag *c);
string compiler__CFlag_format(compiler__CFlag *cf);
bool compiler__Table_has_cflag(compiler__Table *table, compiler__CFlag cflag);
Option_bool compiler__Table_parse_cflag(compiler__Table *table, string cflag,
                                        string mod);
string array_compiler__CFlag_c_options_before_target_msvc(
    array_compiler__CFlag cflags);
string
array_compiler__CFlag_c_options_after_target_msvc(array_compiler__CFlag cflags);
string
array_compiler__CFlag_c_options_before_target(array_compiler__CFlag cflags);
string
array_compiler__CFlag_c_options_after_target(array_compiler__CFlag cflags);
string array_compiler__CFlag_c_options_without_object_files(
    array_compiler__CFlag cflags);
string
array_compiler__CFlag_c_options_only_object_files(array_compiler__CFlag cflags);
compiler__CGen *compiler__new_cgen(string out_name_c);
void compiler__CGen_genln(compiler__CGen *g, string s);
void compiler__CGen_gen(compiler__CGen *g, string s);
void compiler__CGen_resetln(compiler__CGen *g, string s);
void compiler__CGen_save(compiler__CGen *g);
void compiler__CGen_start_tmp(compiler__CGen *g);
string compiler__CGen_end_tmp(compiler__CGen *g);
int compiler__CGen_add_placeholder(compiler__CGen *g);
void compiler__CGen_start_cut(compiler__CGen *g);
string compiler__CGen_cut(compiler__CGen *g);
void compiler__CGen_set_placeholder(compiler__CGen *g, int pos, string val);
void compiler__CGen_insert_before(compiler__CGen *g, string val);
void compiler__CGen_register_thread_fn(compiler__CGen *g, string wrapper_name,
                                       string wrapper_text, string struct_text);
string compiler__V_prof_counters(compiler__V *v);
string compiler__Parser_print_prof_counters(compiler__Parser *p);
void compiler__Parser_gen_typedef(compiler__Parser *p, string s);
void compiler__Parser_gen_type_alias(compiler__Parser *p, string s);
void compiler__CGen_add_to_main(compiler__CGen *g, string s);
void compiler__build_thirdparty_obj_file(string path,
                                         array_compiler__CFlag moduleflags);
string compiler__os_name_to_ifdef(string name);
string compiler__platform_postfix_to_ifdefguard(string name);
string compiler__V_type_definitions(compiler__V *v);
array_compiler__Type compiler__sort_structs(array_compiler__Type types);
void compiler__Parser_error(compiler__Parser *p, string s);
void compiler__Parser_warn(compiler__Parser *p, string s);
void compiler__Parser_production_error_with_token_index(compiler__Parser *p,
                                                        string e,
                                                        int tokenindex);
void compiler__Parser_error_with_token_index(compiler__Parser *p, string s,
                                             int tokenindex);
void compiler__Parser_warn_with_token_index(compiler__Parser *p, string s,
                                            int tokenindex);
void compiler__Parser_error_with_position(compiler__Parser *p, string s,
                                          compiler__ScannerPos sp);
void compiler__Parser_warn_with_position(compiler__Parser *p, string s,
                                         compiler__ScannerPos sp);
void compiler__Scanner_error(compiler__Scanner *s, string msg);
void compiler__Scanner_warn(compiler__Scanner *s, string msg);
void compiler__Scanner_warn_with_col(compiler__Scanner *s, string msg, int col);
void compiler__Scanner_error_with_col(compiler__Scanner *s, string msg,
                                      int col);
static inline int compiler__Parser_cur_tok_index(compiler__Parser *p);
static inline int compiler__imax(int a, int b);
static inline int compiler__imin(int a, int b);
string compiler__Scanner_get_error_filepath(compiler__Scanner *s);
bool compiler__Scanner_is_color_output_on(compiler__Scanner *s);
void compiler__Parser_print_error_context(compiler__Parser *p);
string compiler__normalized_error(string s);
string compiler__ScannerPos_str(compiler__ScannerPos s);
compiler__ScannerPos compiler__Scanner_get_scanner_pos(compiler__Scanner *s);
void compiler__Scanner_goto_scanner_position(compiler__Scanner *s,
                                             compiler__ScannerPos scp);
compiler__ScannerPos
compiler__Scanner_get_scanner_pos_of_token(compiler__Scanner *s,
                                           compiler__Token *t);
void compiler__Scanner_eat_single_newline(compiler__Scanner *s);
void compiler__Parser_comp_time(compiler__Parser *p);
void compiler__Parser_chash(compiler__Parser *p);
void compiler__Parser_comptime_method_call(compiler__Parser *p,
                                           compiler__Type typ);
void compiler__Parser_gen_array_str(compiler__Parser *p, compiler__Type typ);
void compiler__Parser_gen_struct_str(compiler__Parser *p, compiler__Type typ);
void compiler__Parser_gen_varg_str(compiler__Parser *p, compiler__Type typ);
void compiler__Parser_gen_array_filter(compiler__Parser *p, string str_typ,
                                       int method_ph);
string compiler__Parser_gen_array_map(compiler__Parser *p, string str_typ,
                                      int method_ph);
void compiler__Parser_comptime_if_block(compiler__Parser *p, string name);
void compiler__DepSet_add(compiler__DepSet *dset, string item);
compiler__DepSet compiler__DepSet_diff(compiler__DepSet *dset,
                                       compiler__DepSet otherset);
int compiler__DepSet_size(compiler__DepSet *dset);
compiler__DepGraph *compiler__new_dep_graph();
void compiler__DepGraph_add(compiler__DepGraph *graph, string mod,
                            array_string deps);
compiler__DepGraph *compiler__DepGraph_resolve(compiler__DepGraph *graph);
compiler__DepGraphNode compiler__DepGraph_last_node(compiler__DepGraph *graph);
string compiler__DepGraph_display(compiler__DepGraph *graph);
string compiler__DepGraph_display_cycles(compiler__DepGraph *graph);
void compiler__Parser_enum_decl(compiler__Parser *p, bool no_name);
void compiler__Parser_check_enum_member_access(compiler__Parser *p);
string compiler__Parser_bool_expression(compiler__Parser *p);
string compiler__Parser_bterm(compiler__Parser *p);
string compiler__Parser_name_expr(compiler__Parser *p);
string compiler__Parser_expression(compiler__Parser *p);
void compiler__Parser_handle_operator(compiler__Parser *p, string op,
                                      string typ, string cpostfix, int ph,
                                      compiler__Type *T);
string compiler__Parser_term(compiler__Parser *p);
string compiler__Parser_unary(compiler__Parser *p);
string compiler__Parser_factor(compiler__Parser *p);
string array_compiler__TypeInst_str(array_compiler__TypeInst a);
Option_compiler__Var compiler__Parser_find_var(compiler__Parser *p,
                                               string name);
Option_compiler__Var
compiler__Parser_find_var_check_new_var(compiler__Parser *p, string name);
void compiler__Parser_open_scope(compiler__Parser *p);
void compiler__Parser_mark_var_used(compiler__Parser *p, compiler__Var v);
void compiler__Parser_mark_var_returned(compiler__Parser *p, compiler__Var v);
void compiler__Parser_mark_var_changed(compiler__Parser *p, compiler__Var v);
void compiler__Parser_mark_arg_moved(compiler__Parser *p, compiler__Var v);
bool compiler__Parser_known_var(compiler__Parser *p, string name);
bool compiler__Parser_known_var_check_new_var(compiler__Parser *p, string name);
void compiler__Parser_register_var(compiler__Parser *p, compiler__Var v);
void compiler__Parser_clear_vars(compiler__Parser *p);
void compiler__Parser_fn_decl(compiler__Parser *p);
static inline void compiler__Parser_skip_fn_body(compiler__Parser *p);
string compiler__Parser_get_linkage_prefix(compiler__Parser p);
void compiler__Parser_check_unused_variables(compiler__Parser *p);
void compiler__Parser_async_fn_call(compiler__Parser *p, compiler__Fn f,
                                    int method_ph, string receiver_var,
                                    string receiver_type);
void compiler__Parser_fn_call(compiler__Parser *p, compiler__Fn *f,
                              int method_ph, string receiver_var,
                              string receiver_type);
void compiler__Parser_fn_args(compiler__Parser *p, compiler__Fn *f);
void compiler__Parser_fn_call_args(compiler__Parser *p, compiler__Fn *f);
compiler__TypeInst compiler__Parser_extract_type_inst(compiler__Parser *p,
                                                      compiler__Fn *f,
                                                      array_string args_);
array_string compiler__Parser_replace_type_params(compiler__Parser *p,
                                                  compiler__Fn *f,
                                                  compiler__TypeInst ti);
string compiler__Parser_register_vargs_stuct(compiler__Parser *p, string typ,
                                             int len);
_V_MulRet_string_V_array_string
compiler__Parser_fn_call_vargs(compiler__Parser *p, compiler__Fn f);
void compiler__Parser_fn_gen_caller_vargs(compiler__Parser *p, compiler__Fn *f,
                                          string varg_type,
                                          array_string values);
string compiler__Parser_register_multi_return_stuct(compiler__Parser *p,
                                                    array_string types);
void compiler__Parser_rename_generic_fn_instance(compiler__Parser *p,
                                                 compiler__Fn *f,
                                                 compiler__TypeInst ti);
void compiler__Parser_dispatch_generic_fn_instance(compiler__Parser *p,
                                                   compiler__Fn *f,
                                                   compiler__TypeInst ti);
string compiler__Fn_typ_str(compiler__Fn *f);
string compiler__Fn_str_args(compiler__Fn *f, compiler__Table *table);
string compiler__Parser_find_misspelled_local_var(compiler__Parser *p,
                                                  string name, f32 min_match);
bool array_compiler__Fn_contains(array_compiler__Fn fns, compiler__Fn f);
string compiler__Fn_v_fn_module(compiler__Fn f);
string compiler__Fn_v_fn_name(compiler__Fn f);
void compiler__Parser_for_st(compiler__Parser *p);
string compiler__Parser_gen_var_decl(compiler__Parser *p, string name,
                                     bool is_static);
void compiler__Parser_gen_fn_decl(compiler__Parser *p, compiler__Fn f,
                                  string typ, string str_args);
void compiler__Parser_gen_blank_identifier_assign(compiler__Parser *p);
string compiler__Parser_gen_handle_option_or_else(compiler__Parser *p,
                                                  string _typ, string name,
                                                  int fn_call_ph);
string compiler__types_to_c(array_compiler__Type types, compiler__Table *table);
void compiler__Parser_index_get(compiler__Parser *p, string typ, int fn_ph,
                                compiler__IndexConfig cfg);
string compiler__Table_fn_gen_name(compiler__Table *table, compiler__Fn *f);
void compiler__Parser_gen_method_call(compiler__Parser *p,
                                      compiler__Var *receiver,
                                      string receiver_type, string cgen_name,
                                      string ftyp, int method_ph);
void compiler__Parser_gen_array_at(compiler__Parser *p, string typ_,
                                   bool is_arr0, int fn_ph);
void compiler__Parser_gen_for_header(compiler__Parser *p, string i, string tmp,
                                     string var_typ, string val);
void compiler__Parser_gen_for_str_header(compiler__Parser *p, string i,
                                         string tmp, string var_typ,
                                         string val);
void compiler__Parser_gen_for_range_header(compiler__Parser *p, string i,
                                           string range_end, string tmp,
                                           string var_type, string val);
void compiler__Parser_gen_for_map_header(compiler__Parser *p, string i,
                                         string tmp, string var_typ, string val,
                                         string typ);
void compiler__Parser_gen_for_varg_header(compiler__Parser *p, string i,
                                          string varg, string var_typ,
                                          string val);
void compiler__Parser_gen_array_init(compiler__Parser *p, string typ,
                                     bool no_alloc, int new_arr_ph,
                                     int nr_elems);
void compiler__Parser_gen_array_set(compiler__Parser *p, string typ,
                                    bool is_ptr, bool is_map, int fn_ph,
                                    int assign_pos, bool is_cao);
bool compiler__Parser_gen_struct_init(compiler__Parser *p, string typ,
                                      compiler__Type t);
void compiler__Parser_gen_struct_field_init(compiler__Parser *p, string field);
void compiler__Parser_gen_empty_map(compiler__Parser *p, string typ);
void compiler__Parser_cast(compiler__Parser *p, string typ);
string compiler__type_default(string typ);
void compiler__Parser_gen_array_push(compiler__Parser *p, int ph, string typ,
                                     string expr_type, string tmp,
                                     string elm_type);
void compiler__Parser_gen_json_for_type(compiler__Parser *p,
                                        compiler__Type typ);
bool compiler__is_js_prim(string typ);
string compiler__Parser_decode_array(compiler__Parser *p, string array_type);
string compiler__js_enc_name(string typ);
string compiler__js_dec_name(string typ);
string compiler__Parser_encode_array(compiler__Parser *p, string array_type);
array_string
compiler__V_generate_hotcode_reloading_compiler_flags(compiler__V *v);
void compiler__V_generate_hotcode_reloading_declarations(compiler__V *v);
void compiler__V_generate_hotcode_reloading_main_caller(compiler__V *v);
void compiler__V_generate_hot_reload_code(compiler__V *v);
void compiler__V_finalize_compilation(compiler__V *v);
int compiler__V_add_parser(compiler__V *v, compiler__Parser parser);
Option_int compiler__V_get_file_parser_index(compiler__V *v, string file);
int compiler__V_parse(compiler__V *v, string file, compiler__Pass pass);
void compiler__V_compile(compiler__V *v);
void compiler__V_generate_init(compiler__V *v);
void compiler__V_generate_main(compiler__V *v);
void compiler__V_gen_main_start(compiler__V *v, bool add_os_args);
void compiler__V_gen_main_end(compiler__V *v, string return_statement);
string compiler__final_target_out_name(string out_name);
void compiler__V_run_compiled_executable_and_exit(compiler__V v);
array_string compiler__V_v_files_from_dir(compiler__V *v, string dir);
void compiler__V_add_v_files_to_compile(compiler__V *v);
array_string compiler__V_get_builtin_files(compiler__V *v);
array_string compiler__V_get_user_files(compiler__V *v);
array_string compiler__V_get_imported_module_files(compiler__V *v, string mod);
void compiler__V_parse_lib_imports(compiler__V *v);
string compiler__get_arg(string joined_args, string arg, string def);
string compiler__get_param_after(string joined_args, string arg, string def);
void compiler__V_log(compiler__V *v, string s);
compiler__V *compiler__new_v(array_string args);
array_string compiler__env_vflags_and_os_args();
void compiler__vfmt(array_string args);
void compiler__create_symlink();
string compiler__vexe_path();
void compiler__verror(string s);
string compiler__vhash();
string compiler__cescaped_path(string s);
compiler__OS compiler__os_from_string(string os);
void compiler__set_vroot_folder(string vroot_path);
compiler__V *compiler__new_v_compiler_with_args(array_string args);
string compiler__Parser_match_statement(compiler__Parser *p, bool is_expr);
void compiler__Parser_switch_statement(compiler__Parser *p);
void compiler__generate_vh(string mod);
void compiler__VhGen_generate_fn(compiler__VhGen *g);
void compiler__VhGen_generate_alias(compiler__VhGen *g);
void compiler__VhGen_generate_const(compiler__VhGen *g);
void compiler__VhGen_generate_type(compiler__VhGen *g);
string compiler__Table_qualify_module(compiler__Table *table, string mod,
                                      string file_path);
compiler__ImportTable compiler__new_import_table();
void compiler__Parser_register_import(compiler__Parser *p, string mod,
                                      int tok_idx);
void compiler__Parser_register_import_alias(compiler__Parser *p, string alias,
                                            string mod, int tok_idx);
int compiler__ImportTable_get_import_tok_idx(compiler__ImportTable *it,
                                             string mod);
bool compiler__ImportTable_known_import(compiler__ImportTable *it, string mod);
bool compiler__ImportTable_known_alias(compiler__ImportTable *it, string alias);
bool compiler__ImportTable_is_aliased(compiler__ImportTable *it, string mod);
string compiler__ImportTable_resolve_alias(compiler__ImportTable *it,
                                           string alias);
void compiler__ImportTable_register_used_import(compiler__ImportTable *it,
                                                string alias);
bool compiler__ImportTable_is_used_import(compiler__ImportTable *it,
                                          string alias);
bool compiler__Parser_is_mod_in_scope(compiler__Parser *p, string mod);
compiler__DepGraph *compiler__V_resolve_deps(compiler__V *v);
compiler__DepGraph *compiler__V_import_graph(compiler__V *v);
array_string compiler__DepGraph_imports(compiler__DepGraph *graph);
string compiler__V_module_path(compiler__V *v, string mod);
Option_string compiler__V_find_module_path(compiler__V *v, string mod);
static inline string compiler__mod_gen_name(string mod);
static inline string compiler__mod_gen_name_rev(string mod);
Option_string compiler__find_windows_kit_internal(RegKey key,
                                                  array_string versions);
Option_compiler__WindowsKit compiler__find_windows_kit_root(string host_arch);
Option_compiler__VsInstallation compiler__find_vs(string vswhere_dir,
                                                  string host_arch);
Option_compiler__MsvcResult compiler__find_msvc();
void compiler__V_cc_msvc(compiler__V *v);
void compiler__build_thirdparty_obj_file_with_msvc(
    string path, array_compiler__CFlag moduleflags);
compiler__MsvcStringFlags
array_compiler__CFlag_msvc_string_flags(array_compiler__CFlag cflags);
void compiler__Parser_in_optimization(compiler__Parser *p, string typ, int ph);
compiler__Parser compiler__V_new_parser_from_string(compiler__V *v,
                                                    string text);
void compiler__V_reset_cgen_file_line_parameters(compiler__V *v);
compiler__Parser compiler__V_new_parser_from_file(compiler__V *v, string path);
compiler__Parser compiler__V_new_parser(compiler__V *v,
                                        compiler__Scanner *scanner);
void compiler__Parser_scan_tokens(compiler__Parser *p);
void compiler__Parser_set_current_fn(compiler__Parser *p, compiler__Fn f);
void compiler__Parser_next(compiler__Parser *p);
compiler__TokenKind compiler__Parser_peek(compiler__Parser *p);
static inline compiler__Token compiler__Parser_prev_token(compiler__Parser *p);
static inline compiler__Token compiler__Parser_cur_tok(compiler__Parser *p);
static inline compiler__Token compiler__Parser_peek_token(compiler__Parser *p);
void compiler__Parser_log(compiler__Parser *p, string s);
void compiler__Parser_parse(compiler__Parser *p, compiler__Pass pass);
void compiler__Parser_imports(compiler__Parser *p);
void compiler__Parser_import_statement(compiler__Parser *p);
void compiler__Parser_const_decl(compiler__Parser *p);
void compiler__Parser_type_decl(compiler__Parser *p);
compiler__Fn *compiler__Parser_interface_method(compiler__Parser *p,
                                                string field_name,
                                                string receiver);
compiler__TypeCategory compiler__key_to_type_cat(compiler__TokenKind tok);
string compiler__Parser_check_name(compiler__Parser *p);
string compiler__Parser_check_string(compiler__Parser *p);
void compiler__Parser_check_not_reserved(compiler__Parser *p);
string compiler__Parser_strtok(compiler__Parser *p);
void compiler__Parser_check_space(compiler__Parser *p,
                                  compiler__TokenKind expected);
void compiler__Parser_check(compiler__Parser *p, compiler__TokenKind expected);
static inline bool compiler__Parser_first_pass(compiler__Parser *p);
string compiler__Parser_get_type(compiler__Parser *p);
void compiler__Parser_print_tok(compiler__Parser *p);
string compiler__Parser_statements(compiler__Parser *p);
string compiler__Parser_statements_no_rcbr(compiler__Parser *p);
void compiler__Parser_close_scope(compiler__Parser *p);
void compiler__Parser_genln(compiler__Parser *p, string s);
void compiler__Parser_gen(compiler__Parser *p, string s);
string compiler__Parser_statement(compiler__Parser *p, bool add_semi);
void compiler__Parser_assign_statement(compiler__Parser *p, compiler__Var v,
                                       int ph, bool is_map);
void compiler__Parser_var_decl(compiler__Parser *p);
string compiler__Parser_get_struct_type(compiler__Parser *p, string name_,
                                        bool is_c, bool is_ptr);
string compiler__Parser_get_var_type(compiler__Parser *p, string name,
                                     bool is_ptr, bool is_deref);
string compiler__Parser_get_const_type(compiler__Parser *p, string name,
                                       bool is_ptr);
string compiler__Parser_get_c_func_type(compiler__Parser *p, string name);
void compiler__Parser_undefined_error(compiler__Parser *p, string name,
                                      string orig_name);
string compiler__Parser_var_expr(compiler__Parser *p, compiler__Var v);
string compiler__Parser_dot(compiler__Parser *p, string str_typ_,
                            int method_ph);
compiler__IndexType compiler__get_index_type(string typ);
string compiler__Parser_index_expr(compiler__Parser *p, string typ_, int fn_ph);
bool compiler__Parser_fileis(compiler__Parser *p, string s);
string compiler__Parser_indot_expr(compiler__Parser *p);
string compiler__Parser_assoc(compiler__Parser *p);
void compiler__Parser_char_expr(compiler__Parser *p);
string compiler__format_str(string _str);
void compiler__Parser_string_expr(compiler__Parser *p);
string compiler__Parser_map_init(compiler__Parser *p);
string compiler__Parser_array_init(compiler__Parser *p);
string compiler__Parser_get_tmp(compiler__Parser *p);
int compiler__Parser_get_tmp_counter(compiler__Parser *p);
_V_MulRet_string_V_string compiler__Parser_tmp_expr(compiler__Parser *p);
string compiler__Parser_if_st(compiler__Parser *p, bool is_expr,
                              int elif_depth);
void compiler__Parser_assert_statement(compiler__Parser *p);
void compiler__Parser_return_st(compiler__Parser *p);
string compiler__Parser_get_deferred_text(compiler__Parser p);
string compiler__prepend_mod(string mod, string name);
string compiler__Parser_prepend_mod(compiler__Parser *p, string name);
void compiler__Parser_go_statement(compiler__Parser *p);
string compiler__Parser_js_decode(compiler__Parser *p);
void compiler__Parser_attribute(compiler__Parser *p);
void compiler__Parser_defer_st(compiler__Parser *p);
void compiler__Parser_check_and_register_used_imported_type(compiler__Parser *p,
                                                            string typ_name);
void compiler__Parser_check_unused_imports(compiler__Parser *p);
_V_MulRet_bool_V_string compiler__Parser_is_expr_fn_call(compiler__Parser *p,
                                                         int start_tok_idx);
compiler__Type compiler__Parser_get_type2(compiler__Parser *p);
string compiler__sql_params2params_gen(array_string sql_params,
                                       array_string sql_types, string qprefix);
string compiler__Parser_select_query(compiler__Parser *p, int fn_ph);
void compiler__Parser_insert_query(compiler__Parser *p, int fn_ph);
compiler__Scanner *compiler__new_scanner_file(string file_path);
compiler__Scanner *compiler__new_scanner(string text);
compiler__ScanRes compiler__scan_res(compiler__TokenKind tok, string lit);
string compiler__Scanner_ident_name(compiler__Scanner *s);
string compiler__Scanner_ident_hex_number(compiler__Scanner *s);
string compiler__Scanner_ident_oct_number(compiler__Scanner *s);
string compiler__Scanner_ident_dec_number(compiler__Scanner *s);
string compiler__Scanner_ident_number(compiler__Scanner *s);
void compiler__Scanner_skip_whitespace(compiler__Scanner *s);
compiler__ScanRes compiler__Scanner_end_of_file(compiler__Scanner *s);
compiler__ScanRes compiler__Scanner_scan(compiler__Scanner *s);
int compiler__Scanner_current_column(compiler__Scanner *s);
int compiler__Scanner_count_symbol_before(compiler__Scanner s, int p, byte sym);
string compiler__Scanner_ident_string(compiler__Scanner *s);
string compiler__Scanner_ident_char(compiler__Scanner *s);
bool compiler__Scanner_expect(compiler__Scanner *s, string want, int start_pos);
void compiler__Scanner_debug_tokens(compiler__Scanner *s);
void compiler__Scanner_ignore_line(compiler__Scanner *s);
void compiler__Scanner_eat_to_end_of_line(compiler__Scanner *s);
void compiler__Scanner_inc_line_number(compiler__Scanner *s);
string compiler__Scanner_line(compiler__Scanner s, int n);
bool compiler__is_name_char(byte c);
static inline bool compiler__is_nl(byte c);
bool compiler__contains_capital(string s);
bool compiler__good_type_name(string s);
void compiler__Scanner_validate_var_name(compiler__Scanner *s, string name);
void compiler__Parser_struct_decl(compiler__Parser *p);
string compiler__Parser_struct_init(compiler__Parser *p, string typ);
string compiler__Fn_str(compiler__Fn f);
string compiler__Table_debug_fns(compiler__Table *t);
bool compiler__is_number_type(string typ);
bool compiler__is_integer_type(string typ);
bool compiler__is_float_type(string typ);
bool compiler__is_primitive_type(string typ);
compiler__Table *compiler__new_table(bool obfuscate);
string compiler__Table_var_cgen_name(compiler__Table *t, string name);
void compiler__Table_register_module(compiler__Table *t, string mod);
void compiler__Parser_register_array(compiler__Parser *p, string typ);
void compiler__Parser_register_map(compiler__Parser *p, string typ);
bool compiler__Table_known_mod(compiler__Table *table, string mod);
void compiler__Table_register_const(compiler__Table *t, string name, string typ,
                                    string mod, bool is_pub);
void compiler__Parser_register_global(compiler__Parser *p, string name,
                                      string typ);
void compiler__Table_register_fn(compiler__Table *t, compiler__Fn new_fn);
bool compiler__Table_known_type(compiler__Table *table, string typ_);
bool compiler__Table_known_type_fast(compiler__Table *table, compiler__Type *t);
Option_compiler__Fn compiler__Table_find_fn(compiler__Table *t, string name);
Option_compiler__Fn compiler__Table_find_fn_is_script(compiler__Table *t,
                                                      string name,
                                                      bool is_script);
bool compiler__Table_known_fn(compiler__Table *t, string name);
bool compiler__Table_known_const(compiler__Table *t, string name);
void compiler__Table_register_builtin(compiler__Table *t, string typ);
void compiler__Parser_register_type_with_parent(compiler__Parser *p,
                                                string strtyp, string parent);
void compiler__Table_register_type_with_parent(compiler__Table *t, string typ,
                                               string parent);
void compiler__Table_register_type2(compiler__Table *t, compiler__Type typ);
void compiler__Table_rewrite_type(compiler__Table *t, compiler__Type typ);
void compiler__Table_add_field(compiler__Table *table, string type_name,
                               string field_name, string field_type,
                               bool is_mut, string attr,
                               compiler__AccessMod access_mod);
bool compiler__Type_has_field(compiler__Type *t, string name);
bool compiler__Type_has_enum_val(compiler__Type *t, string name);
Option_compiler__Var compiler__Type_find_field(compiler__Type *t, string name);
bool compiler__Table_type_has_field(compiler__Table *table, compiler__Type *typ,
                                    string name);
Option_compiler__Var compiler__Table_find_field(compiler__Table *table,
                                                compiler__Type *typ,
                                                string name);
void compiler__Parser_add_method(compiler__Parser *p, string type_name,
                                 compiler__Fn f);
bool compiler__Type_has_method(compiler__Type *t, string name);
bool compiler__Table_type_has_method(compiler__Table *table,
                                     compiler__Type *typ, string name);
Option_compiler__Fn compiler__Table_find_method(compiler__Table *table,
                                                compiler__Type *typ,
                                                string name);
Option_compiler__Fn compiler__Type_find_method(compiler__Type *t, string name);
compiler__Type compiler__Parser_find_type(compiler__Parser *p, string name);
compiler__Type compiler__Table_find_type(compiler__Table *t, string name_);
bool compiler__Parser_check_types2(compiler__Parser *p, string got_,
                                   string expected_, bool throw);
bool compiler__Parser_check_types(compiler__Parser *p, string got,
                                  string expected);
bool compiler__Parser_check_types_no_throw(compiler__Parser *p, string got,
                                           string expected);
void compiler__Parser_check_types_with_token_index(compiler__Parser *p,
                                                   string got, string expected,
                                                   int var_token_idx);
bool compiler__Parser_satisfies_interface(compiler__Parser *p,
                                          string interface_name, string _typ,
                                          bool throw);
bool compiler__Table_is_interface(compiler__Table *table, string name);
bool compiler__Table_main_exists(compiler__Table *t);
bool compiler__Table_has_at_least_one_test_fn(compiler__Table *t);
Option_compiler__Var compiler__Table_find_const(compiler__Table *t,
                                                string name);
string compiler__Table_cgen_name_type_pair(compiler__Table *table, string name,
                                           string typ);
bool compiler__is_valid_int_const(string val, string typ);
string compiler__Parser_typ_to_fmt(compiler__Parser *p, string typ, int level);
string compiler__type_to_safe_str(string typ);
bool compiler__is_compile_time_const(string s_);
bool compiler__Type_contains_field_type(compiler__Type *t, string typ);
string compiler__Parser_identify_typo(compiler__Parser *p, string name);
f32 compiler__typo_compare_name_mod(string a, string b, string b_mod);
string compiler__Table_find_misspelled_fn(compiler__Table *table, string name,
                                          compiler__Parser *p, f32 min_match);
string compiler__Table_find_misspelled_imported_mod(compiler__Table *table,
                                                    string name,
                                                    compiler__Parser *p,
                                                    f32 min_match);
string compiler__Table_find_misspelled_const(compiler__Table *table,
                                             string name, compiler__Parser *p,
                                             f32 min_match);
_V_MulRet_string_V_string
compiler__Table_find_misspelled_type(compiler__Table *table, string name,
                                     compiler__Parser *p, f32 min_match);
string compiler__type_cat_str(compiler__TypeCategory tc);
map_int compiler__build_keys();
array_string compiler__build_token_str();
compiler__TokenKind compiler__key_to_token(string key);
bool compiler__is_key(string key);
string compiler__TokenKind_str(compiler__TokenKind t);
bool compiler__TokenKind_is_decl(compiler__TokenKind t);
bool compiler__TokenKind_is_assign(compiler__TokenKind t);
bool array_compiler__TokenKind_contains(array_compiler__TokenKind t,
                                        compiler__TokenKind val);
string compiler__Token_str(compiler__Token t);
void compiler__Scanner_fgen(compiler__Scanner *scanner, string s_);
void compiler__Scanner_fgenln(compiler__Scanner *scanner, string s_);
void compiler__Parser_fgen(compiler__Parser *p, string s);
void compiler__Parser_fspace(compiler__Parser *p);
void compiler__Parser_fgenln(compiler__Parser *p, string s);
void compiler__Parser_fmt_inc(compiler__Parser *p);
void compiler__Parser_fmt_dec(compiler__Parser *p);
void compiler__launch_tool(string tname);
string filepath__ext(string path);
bool filepath__is_abs(string path);
string filepath__join(string base, varg_string *dirs);
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
string time__Time_ddmmy(time__Time t);
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
string time__Time_get_fmt_time_str(time__Time t, time__FormatTime fmt_time);
string time__Time_get_fmt_date_str(time__Time t,
                                   time__FormatDelimiter fmt_dlmtr,
                                   time__FormatDate fmt_date);
string time__Time_get_fmt_str(time__Time t, time__FormatDelimiter fmt_dlmtr,
                              time__FormatTime fmt_time,
                              time__FormatDate fmt_date);
string vweb_dot_tmpl__compile_template(string path);
benchmark__Benchmark benchmark__new_benchmark();
void benchmark__Benchmark_stop(benchmark__Benchmark *b);
void benchmark__Benchmark_step(benchmark__Benchmark *b);
void benchmark__Benchmark_fail(benchmark__Benchmark *b);
void benchmark__Benchmark_ok(benchmark__Benchmark *b);
void benchmark__Benchmark_fail_many(benchmark__Benchmark *b, int n);
void benchmark__Benchmark_ok_many(benchmark__Benchmark *b, int n);
void benchmark__Benchmark_neither_fail_nor_ok(benchmark__Benchmark *b);
string benchmark__Benchmark_step_message(benchmark__Benchmark *b, string msg);
string benchmark__Benchmark_total_message(benchmark__Benchmark *b, string msg);
i64 benchmark__Benchmark_total_duration(benchmark__Benchmark *b);
string benchmark__Benchmark_tdiff_in_ms(benchmark__Benchmark *b, string s,
                                        i64 sticks, i64 eticks);
i64 benchmark__now();
void main__main();
bool array_eq_T_int(array_int a1, array_int a2) {

  if (a1.len != a2.len) {

    return 0;
  };

  for (int i = 0; i < a1.len; i++) {

    if ((*(int *)array_get(a1, i)) != (*(int *)array_get(a2, i))) {

      return 0;
    };
  };

  return 1;
}
bool array_eq_T_i64(array_i64 a1, array_i64 a2) {

  if (a1.len != a2.len) {

    return 0;
  };

  for (int i = 0; i < a1.len; i++) {

    if ((*(i64 *)array_get(a1, i)) != (*(i64 *)array_get(a2, i))) {

      return 0;
    };
  };

  return 1;
}
bool array_eq_T_string(array_string a1, array_string a2) {

  if (a1.len != a2.len) {

    return 0;
  };

  for (int i = 0; i < a1.len; i++) {

    if (string_ne((*(string *)array_get(a1, i)),
                  (*(string *)array_get(a2, i)))) {

      return 0;
    };
  };

  return 1;
}
bool array_eq_T_byte(array_byte a1, array_byte a2) {

  if (a1.len != a2.len) {

    return 0;
  };

  for (int i = 0; i < a1.len; i++) {

    if ((*(byte *)array_get(a1, i)) != (*(byte *)array_get(a2, i))) {

      return 0;
    };
  };

  return 1;
}
bool array_eq_T_f32(array_f32 a1, array_f32 a2) {

  if (a1.len != a2.len) {

    return 0;
  };

  for (int i = 0; i < a1.len; i++) {

    if (f32_ne((*(f32 *)array_get(a1, i)), (*(f32 *)array_get(a2, i)))) {

      return 0;
    };
  };

  return 1;
}
i64 total_m = 0; // global
int builtin__min_cap;
int builtin__max_cap;
array_int g_ustring_runes; // global
#define builtin__CP_UTF8 65001
#define strconv__int_size 32
u64 strconv__max_u64;
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
int os__STD_INPUT_HANDLE;
int os__STD_OUTPUT_HANDLE;
int os__STD_ERROR_HANDLE;
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
int os__INVALID_HANDLE_VALUE;
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
string os__path_separator;
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
string compiler__CommonCHeaders;
string compiler__js_headers;
string compiler__warn_match_arrow;
string compiler__err_used_as_value;
string compiler__and_or_error;
#define compiler__MaxLocalVars 50
compiler__Fn compiler__EmptyFn;
compiler__Fn compiler__MainFn;
string compiler__dot_ptr;
string compiler__Version;
#define compiler__compiler__BuildMode_default_mode 0
#define compiler__compiler__BuildMode_build_module 1
array_string compiler__supported_platforms;
#define compiler__compiler__OS_mac 0
#define compiler__compiler__OS_linux 1
#define compiler__compiler__OS_windows 2
#define compiler__compiler__OS_freebsd 3
#define compiler__compiler__OS_openbsd 4
#define compiler__compiler__OS_netbsd 5
#define compiler__compiler__OS_dragonfly 6
#define compiler__compiler__OS_js 7
#define compiler__compiler__OS_android 8
#define compiler__compiler__OS_solaris 9
#define compiler__compiler__Pass_imports 0
#define compiler__compiler__Pass_decl 1
#define compiler__compiler__Pass_main 2
string compiler__v_modules_path;
RegKey compiler__HKEY_LOCAL_MACHINE;
int compiler__KEY_QUERY_VALUE;
int compiler__KEY_WOW64_32KEY;
int compiler__KEY_ENUMERATE_SUB_KEYS;
#define compiler__MaxModuleDepth 4
map_bool compiler__Reserved_Types;
#define compiler__compiler__IndexType_noindex 0
#define compiler__compiler__IndexType_str 1
#define compiler__compiler__IndexType_map 2
#define compiler__compiler__IndexType_array 3
#define compiler__compiler__IndexType_array0 4
#define compiler__compiler__IndexType_fixed_array 5
#define compiler__compiler__IndexType_ptr 6
#define compiler__single_quote '\''
#define compiler__double_quote '"'
#define compiler__error_context_before 2
#define compiler__error_context_after 2
#define compiler__compiler__NameCategory_constant 0
#define compiler__compiler__NameCategory_mod 1
#define compiler__compiler__NameCategory_var 2
#define compiler__compiler__NameCategory_typ 3
#define compiler__compiler__AccessMod_private 0
#define compiler__compiler__AccessMod_private_mut 1
#define compiler__compiler__AccessMod_public 2
#define compiler__compiler__AccessMod_public_mut 3
#define compiler__compiler__AccessMod_public_mut_mut 4
#define compiler__compiler__TypeCategory_builtin 0
#define compiler__compiler__TypeCategory_struct_ 1
#define compiler__compiler__TypeCategory_func 2
#define compiler__compiler__TypeCategory_interface_ 3
#define compiler__compiler__TypeCategory_enum_ 4
#define compiler__compiler__TypeCategory_union_ 5
#define compiler__compiler__TypeCategory_c_struct 6
#define compiler__compiler__TypeCategory_c_typedef 7
#define compiler__compiler__TypeCategory_objc_interface 8
#define compiler__compiler__TypeCategory_array 9
#define compiler__compiler__TypeCategory_alias 10
array_string compiler__CReserved;
array_string compiler__integer_types;
array_string compiler__float_types;
array_string compiler__reserved_type_param_names;
#define compiler__compiler__TokenKind_eof 0
#define compiler__compiler__TokenKind_name 1
#define compiler__compiler__TokenKind_number 2
#define compiler__compiler__TokenKind_str 3
#define compiler__compiler__TokenKind_str_inter 4
#define compiler__compiler__TokenKind_chartoken 5
#define compiler__compiler__TokenKind_plus 6
#define compiler__compiler__TokenKind_minus 7
#define compiler__compiler__TokenKind_mul 8
#define compiler__compiler__TokenKind_div 9
#define compiler__compiler__TokenKind_mod 10
#define compiler__compiler__TokenKind_xor 11
#define compiler__compiler__TokenKind_pipe 12
#define compiler__compiler__TokenKind_inc 13
#define compiler__compiler__TokenKind_dec 14
#define compiler__compiler__TokenKind_and 15
#define compiler__compiler__TokenKind_logical_or 16
#define compiler__compiler__TokenKind_not 17
#define compiler__compiler__TokenKind_bit_not 18
#define compiler__compiler__TokenKind_question 19
#define compiler__compiler__TokenKind_comma 20
#define compiler__compiler__TokenKind_semicolon 21
#define compiler__compiler__TokenKind_colon 22
#define compiler__compiler__TokenKind_arrow 23
#define compiler__compiler__TokenKind_amp 24
#define compiler__compiler__TokenKind_hash 25
#define compiler__compiler__TokenKind_dollar 26
#define compiler__compiler__TokenKind_left_shift 27
#define compiler__compiler__TokenKind_righ_shift 28
#define compiler__compiler__TokenKind_assign 29
#define compiler__compiler__TokenKind_decl_assign 30
#define compiler__compiler__TokenKind_plus_assign 31
#define compiler__compiler__TokenKind_minus_assign 32
#define compiler__compiler__TokenKind_div_assign 33
#define compiler__compiler__TokenKind_mult_assign 34
#define compiler__compiler__TokenKind_xor_assign 35
#define compiler__compiler__TokenKind_mod_assign 36
#define compiler__compiler__TokenKind_or_assign 37
#define compiler__compiler__TokenKind_and_assign 38
#define compiler__compiler__TokenKind_righ_shift_assign 39
#define compiler__compiler__TokenKind_left_shift_assign 40
#define compiler__compiler__TokenKind_lcbr 41
#define compiler__compiler__TokenKind_rcbr 42
#define compiler__compiler__TokenKind_lpar 43
#define compiler__compiler__TokenKind_rpar 44
#define compiler__compiler__TokenKind_lsbr 45
#define compiler__compiler__TokenKind_rsbr 46
#define compiler__compiler__TokenKind_eq 47
#define compiler__compiler__TokenKind_ne 48
#define compiler__compiler__TokenKind_gt 49
#define compiler__compiler__TokenKind_lt 50
#define compiler__compiler__TokenKind_ge 51
#define compiler__compiler__TokenKind_le 52
#define compiler__compiler__TokenKind_nl 53
#define compiler__compiler__TokenKind_dot 54
#define compiler__compiler__TokenKind_dotdot 55
#define compiler__compiler__TokenKind_ellipsis 56
#define compiler__compiler__TokenKind_keyword_beg 57
#define compiler__compiler__TokenKind_key_as 58
#define compiler__compiler__TokenKind_key_assert 59
#define compiler__compiler__TokenKind_key_atomic 60
#define compiler__compiler__TokenKind_key_break 61
#define compiler__compiler__TokenKind_key_const 62
#define compiler__compiler__TokenKind_key_continue 63
#define compiler__compiler__TokenKind_key_defer 64
#define compiler__compiler__TokenKind_key_else 65
#define compiler__compiler__TokenKind_key_embed 66
#define compiler__compiler__TokenKind_key_enum 67
#define compiler__compiler__TokenKind_key_false 68
#define compiler__compiler__TokenKind_key_for 69
#define compiler__compiler__TokenKind_key_fn 70
#define compiler__compiler__TokenKind_key_global 71
#define compiler__compiler__TokenKind_key_go 72
#define compiler__compiler__TokenKind_key_goto 73
#define compiler__compiler__TokenKind_key_if 74
#define compiler__compiler__TokenKind_key_import 75
#define compiler__compiler__TokenKind_key_import_const 76
#define compiler__compiler__TokenKind_key_in 77
#define compiler__compiler__TokenKind_key_interface 78
#define compiler__compiler__TokenKind_key_match 79
#define compiler__compiler__TokenKind_key_module 80
#define compiler__compiler__TokenKind_key_mut 81
#define compiler__compiler__TokenKind_key_none 82
#define compiler__compiler__TokenKind_key_return 83
#define compiler__compiler__TokenKind_key_select 84
#define compiler__compiler__TokenKind_key_sizeof 85
#define compiler__compiler__TokenKind_key_struct 86
#define compiler__compiler__TokenKind_key_switch 87
#define compiler__compiler__TokenKind_key_true 88
#define compiler__compiler__TokenKind_key_type 89
#define compiler__compiler__TokenKind_key_orelse 90
#define compiler__compiler__TokenKind_key_union 91
#define compiler__compiler__TokenKind_key_pub 92
#define compiler__compiler__TokenKind_key_static 93
#define compiler__compiler__TokenKind_key_unsafe 94
#define compiler__compiler__TokenKind_keyword_end 95
#define compiler__NrTokens 140
array_string compiler__TokenStr;
map_int compiler__KEYWORDS;
array_compiler__TokenKind compiler__AssignTokens;
#define compiler__help_text                                                    \
  tos3(                                                                        \
      "Usage: v [options/commands] [file.v | directory]\n\n   When V is run "  \
      "without any arguments, it is run in REPL mode.\n\n   When given a .v "  \
      "file, it will be compiled. The executable will have the\n   same name " \
      "as the input .v file: `v foo.v` produces `./foo` on *nix systems,\n  "  \
      "`foo.exe` on Windows.\n\n   You can use -o to specify a different "     \
      "output executable\'s name.\n\n   When given a directory, all .v files " \
      "contained in it will be compiled as\n   part of a single main "         \
      "module.\n\n   By default the executable will have the same name as "    \
      "the directory.\n\n   To compile all V files in current directory, run " \
      "`v .`\n\n   Any file ending in _test.v, will be treated as a test.\n  " \
      " It will be compiled and run, evaluating the assert statements in "     \
      "every\n   function named test_xxx.\n\n   You can put common options "   \
      "inside an environment variable named VFLAGS, so that\n   you don\'t "   \
      "have to repeat them.\n\n   You can set it like this: `export "          \
      "VFLAGS=\"-cc clang -debug\"` on *nix,\n   `set VFLAGS=-cc msvc` on "    \
      "Windows.\n\nOptions/commands:\n  -h, help          Display this "       \
      "information.\n  -o <file>         Write output to <file>.\n  -o "       \
      "<file>.c       Produce C source without compiling it.\n  -o <file>.js " \
      "     Produce JavaScript source.\n  -prod             Build an "         \
      "optimized executable.\n  -v, version       Display compiler version "   \
      "and git hash of the compiler source.\n  -live             Enable hot "  \
      "code reloading (required by functions marked with [live]).\n  -os "     \
      "<OS>          Produce an executable for the selected OS.\n            " \
      "        OS can be linux, mac, windows, msvc.\n                    Use " \
      "msvc if you want to use the MSVC compiler on Windows.\n  -shared      " \
      "     Build a shared library.\n  -stats            Show additional "     \
      "stats when compiling/running tests. Try `v -stats test .`\n\n  -cache " \
      "           Turn on usage of the precompiled module cache.\n           " \
      "         It very significantly speeds up secondary compilations.\n\n  " \
      "-obf              Obfuscate the resulting binary.\n  -                " \
      " Shorthand for `v runrepl`.\n\nOptions for debugging/troubleshooting "  \
      "v programs:\n  -g                Generate debugging information in "    \
      "the backtraces. Add *V* line numbers to the generated executable.\n  "  \
      "-cg               Same as -g, but add *C* line numbers to the "         \
      "generated executable instead of *V* line numbers.\n  -keep_c          " \
      " Do NOT remove the generated .tmp.c files after compilation.\n        " \
      "            It is useful when using debuggers like gdb/visual studio, " \
      "when given after -g / -cg .\n  -show_c_cmd       Print the full C "     \
      "compilation command and how much time it took.\n  -cc <ccompiler>   "   \
      "Specify which C compiler you want to use as a C backend.\n            " \
      "        The C backend compiler should be able to handle C99 "           \
      "compatible C code.\n                    Common C compilers are gcc, "   \
      "clang, tcc, icc, cl...\n  -cflags <flags>   Pass additional C flags "   \
      "to the C backend compiler.\n                    Example: -cflags "      \
      "`sdl2-config --cflags`\n\nCommands:\n  up                Update V. "    \
      "Run `v up` at least once per day, since V development is rapid and "    \
      "features/bugfixes are added constantly.\n  run <file.v>      Build "    \
      "and execute the V program in file.v. You can add arguments for the V "  \
      "program *after* the file name.\n  build <module>    Compile a module "  \
      "into an object file.\n  runrepl           Run the V REPL. If V is "     \
      "running in a tty terminal, the REPL is interactive, otherwise it just " \
      "reads from stdin.\n  symlink           Useful on Unix systems. "        \
      "Symlinks the current V executable to /usr/local/bin/v, so that V is "   \
      "globally available.\n  test v            Run all V test files, and "    \
      "compile all V examples.\n  test folder/      Run all V test files "     \
      "located in the folder and its subfolders. You can also pass "           \
      "individual _test.v files too.\n  fmt               Run vfmt to format " \
      "the source code. [wip]\n  doc               Run vdoc over the source "  \
      "code and produce documentation.\n  translate         Translates C to "  \
      "V. [wip, will be available in V 0.3]\n\nV package management "          \
      "commands:\n  search  keywords  Search the https://vpm.vlang.io/ "       \
      "module repository for matching modules and shows their details.\n  "    \
      "install <module>  Install a user module from https://vpm.vlang.io/.\n " \
      " update  [module]  Updates an already installed module, or ALL "        \
      "installed modules at once, when no module name is given.\n  remove  "   \
      "[module]  Removes an installed module, or ALL installed modules at "    \
      "once, when no module name is given.\n")
string time__days_string;
array_int time__month_days;
string time__months_string;
i64 time__absolute_zero_year;
#define time__seconds_per_minute 60
int time__seconds_per_hour;
int time__seconds_per_day;
int time__seconds_per_week;
int time__days_per_400_years;
int time__days_per_100_years;
int time__days_per_4_years;
array_int time__days_before;
#define time__time__FormatTime_hhmm12 0
#define time__time__FormatTime_hhmm24 1
#define time__time__FormatTime_hhmmss12 2
#define time__time__FormatTime_hhmmss24 3
#define time__time__FormatTime_no_time 4
#define time__time__FormatDate_ddmmyy 0
#define time__time__FormatDate_ddmmyyyy 1
#define time__time__FormatDate_mmddyy 2
#define time__time__FormatDate_mmddyyyy 3
#define time__time__FormatDate_mmmd 4
#define time__time__FormatDate_mmmdd 5
#define time__time__FormatDate_mmmddyyyy 6
#define time__time__FormatDate_no_date 7
#define time__time__FormatDate_yyyymmdd 8
#define time__time__FormatDelimiter_dot 0
#define time__time__FormatDelimiter_hyphen 1
#define time__time__FormatDelimiter_slash 2
#define time__time__FormatDelimiter_space 3
#define vweb_dot_tmpl__STR_START tos3("sb.write(\'")
#define vweb_dot_tmpl__STR_END tos3("\' ) ")

array new_array(int mylen, int cap, int elm_size) {

  array arr = (array){.len = mylen,
                      .cap = cap,
                      .element_size = elm_size,
                      .data = v_calloc(cap * elm_size)};

  return arr;
}
array make(int len, int cap, int elm_size) {

  return new_array(len, cap, elm_size);
}
array new_array_from_c_array(int len, int cap, int elm_size, void *c_array) {

  array arr = (array){.len = len,
                      .cap = cap,
                      .element_size = elm_size,
                      .data = v_calloc(cap * elm_size)};

  memcpy(arr.data, c_array, len * elm_size);

  return arr;
}
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size,
                                      void *c_array) {

  array arr = (array){
      .len = len, .cap = cap, .element_size = elm_size, .data = c_array};

  return arr;
}
void array_ensure_cap(array *a, int required) {

  if (required > a->cap) {

    int cap = (a->cap == 0) ? (2) : (a->cap * 2);

    while (required > cap) {

      cap *= 2;
    };

    if (a->cap == 0) {

      a->data = v_calloc(cap * a->element_size);

    } else {

      a->data = realloc(a->data, cap * a->element_size);
    };

    a->cap = cap;
  };
}
array array_repeat_old(void *val, int nr_repeats, int elm_size) {

  if (nr_repeats < 0) {

    v_panic(_STR("[0; len]: `len` is negative (len == %d)", nr_repeats));
  };

  array arr = (array){.len = nr_repeats,
                      .cap = nr_repeats,
                      .element_size = elm_size,
                      .data = v_calloc(nr_repeats * elm_size)};

  for (int i = 0; i < nr_repeats; i++) {

    memcpy((byte *)arr.data + i * elm_size, val, elm_size);
  };

  return arr;
}
array array_repeat(array a, int nr_repeats) {

  if (nr_repeats < 0) {

    v_panic(_STR("array.repeat: count is negative (count == %d)", nr_repeats));
  };

  array arr = (array){.len = nr_repeats * a.len,
                      .cap = nr_repeats * a.len,
                      .element_size = a.element_size,
                      .data = v_calloc(nr_repeats * a.len * a.element_size)};

  for (int i = 0; i < nr_repeats; i++) {

    memcpy((byte *)arr.data + i * a.len * a.element_size, a.data,
           a.len * a.element_size);
  };

  return arr;
}
void array_sort_with_compare(array *a, void *compare) {

  qsort(a->data, a->len, a->element_size, compare);
}
void array_insert(array *a, int i, void *val) {

  if (i < 0 || i > a->len) {

    v_panic(_STR("array.insert: index out of range (i == %d, a.len == %d)", i,
                 a->len));
  };

  array_ensure_cap(a, a->len + 1);

  int size = a->element_size;

  memmove((byte *)a->data + (i + 1) * size, (byte *)a->data + i * size,
          (a->len - i) * size);

  memcpy((byte *)a->data + i * size, val, size);

  a->len++;
}
void array_prepend(array *a, void *val) { array_insert(a, 0, val); }
void v_array_delete(array *a, int i) {

  if (i < 0 || i >= a->len) {

    v_panic(_STR("array.delete: index out of range (i == %d, a.len == %d)", i,
                 a->len));
  };

  int size = a->element_size;

  memmove((byte *)a->data + i * size, (byte *)a->data + (i + 1) * size,
          (a->len - i) * size);

  a->len--;
}
void *array_get(array a, int i) {

  if (i < 0 || i >= a.len) {

    v_panic(
        _STR("array.get: index out of range (i == %d, a.len == %d)", i, a.len));
  };

  return (byte *)a.data + i * a.element_size;
}
void *array_first(array a) {

  if (a.len == 0) {

    v_panic(tos3("array.first: array is empty"));
  };

  return (byte *)a.data + 0;
}
void *array_last(array a) {

  if (a.len == 0) {

    v_panic(tos3("array.last: array is empty"));
  };

  return (byte *)a.data + (a.len - 1) * a.element_size;
}
array array_left(array a, int n) {

  if (n < 0) {

    v_panic(_STR("array.left: index is negative (n == %d)", n));
  };

  if (n >= a.len) {

    return array_slice(a, 0, a.len);
  };

  return array_slice(a, 0, n);
}
array array_right(array a, int n) {

  if (n < 0) {

    v_panic(_STR("array.right: index is negative (n == %d)", n));
  };

  if (n >= a.len) {

    return new_array(0, 0, a.element_size);
  };

  return array_slice(a, n, a.len);
}
array array_slice2(array a, int start, int _end, bool end_max) {

  int end = (end_max) ? (a.len) : (_end);

  return array_slice(a, start, end);
}
array array_slice(array a, int start, int _end) {

  int end = _end;

  if (start > end) {

    v_panic(_STR("array.slice: invalid slice index (%d > %d)", start, end));
  };

  if (end > a.len) {

    v_panic(
        _STR("array.slice: slice bounds out of range (%d >= %d)", end, a.len));
  };

  if (start < 0) {

    v_panic(_STR("array.slice: slice bounds out of range (%d < 0)", start));
  };

  int l = end - start;

  array res = (array){.element_size = a.element_size,
                      .data = (byte *)a.data + start * a.element_size,
                      .len = l,
                      .cap = l};

  return res;
}
void array_set(array *a, int i, void *val) {

  if (i < 0 || i >= a->len) {

    v_panic(_STR("array.set: index out of range (i == %d, a.len == %d)", i,
                 a->len));
  };

  memcpy((byte *)a->data + a->element_size * i, val, a->element_size);
}
void array_push(array *a, void *val) {

  array_ensure_cap(a, a->len + 1);

  memcpy((byte *)a->data + a->element_size * a->len, val, a->element_size);

  a->len++;
}
void array_push_many(array *a, void *val, int size) {

  array_ensure_cap(a, a->len + size);

  memcpy((byte *)a->data + a->element_size * a->len, val,
         a->element_size * size);

  a->len += size;
}
array array_reverse(array a) {

  array arr = (array){.len = a.len,
                      .cap = a.cap,
                      .element_size = a.element_size,
                      .data = v_calloc(a.cap * a.element_size)};

  for (int i = 0; i < a.len; i++) {

    memcpy((byte *)arr.data + i * arr.element_size,
           &(*(array *)array_get(a, a.len - 1 - i)), arr.element_size);
  };

  return arr;
}
array array_clone(array a) {

  array arr = (array){.len = a.len,
                      .cap = a.cap,
                      .element_size = a.element_size,
                      .data = v_calloc(a.cap * a.element_size)};

  memcpy(arr.data, a.data, a.cap * a.element_size);

  return arr;
}
void v_array_free(array a) { free(a.data); }
string array_string_str(array_string a) {

  strings__Builder sb = strings__new_builder(a.len * 3);

  strings__Builder_write(&/* ? */ sb, tos3("["));

  for (int i = 0; i < a.len; i++) {

    string val = (*(string *)array_get(a, i));

    strings__Builder_write(&/* ? */ sb, tos3("\""));

    strings__Builder_write(&/* ? */ sb, val);

    strings__Builder_write(&/* ? */ sb, tos3("\""));

    if (i < a.len - 1) {

      strings__Builder_write(&/* ? */ sb, tos3(", "));
    };
  };

  strings__Builder_write(&/* ? */ sb, tos3("]"));

  return strings__Builder_str(sb);
}
string array_bool_str(array_bool a) {

  strings__Builder sb = strings__new_builder(a.len * 3);

  strings__Builder_write(&/* ? */ sb, tos3("["));

  for (int i = 0; i < a.len; i++) {

    bool val = (*(bool *)array_get(a, i));

    if (val) {

      strings__Builder_write(&/* ? */ sb, tos3("true"));

    } else {

      strings__Builder_write(&/* ? */ sb, tos3("false"));
    };

    if (i < a.len - 1) {

      strings__Builder_write(&/* ? */ sb, tos3(", "));
    };
  };

  strings__Builder_write(&/* ? */ sb, tos3("]"));

  return strings__Builder_str(sb);
}
string array_byte_hex(array_byte b) {

  byte *hex = v_malloc(b.len * 2 + 1);

  byte *ptr = &hex[/*ptr*/ 0] /*rbyte 1*/;

  for (int i = 0; i < b.len; i++) {

    ptr += sprintf(((char *)(ptr)), "%02x", (*(byte *)array_get(b, i)));
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
int compare_ints(int a, int b) {

  if (a < b) {

    return -1;
  };

  if (a > b) {

    return 1;
  };

  return 0;
}
void array_int_sort(array_int *a) {

  array_sort_with_compare(
      a, &/*112 EXP:"void*" GOT:"fn (int,int) int" */ compare_ints);
}
int array_string_index(array_string a, string v) {

  for (int i = 0; i < a.len; i++) {

    if (string_eq((*(string *)array_get(a, i)), v)) {

      return i;
    };
  };

  return -1;
}
int array_int_index(array_int a, int v) {

  for (int i = 0; i < a.len; i++) {

    if ((*(int *)array_get(a, i)) == v) {

      return i;
    };
  };

  return -1;
}
int array_byte_index(array_byte a, byte v) {

  for (int i = 0; i < a.len; i++) {

    if ((*(byte *)array_get(a, i)) == v) {

      return i;
    };
  };

  return -1;
}
int array_char_index(array_char a, char v) {

  for (int i = 0; i < a.len; i++) {

    if ((*(char *)array_get(a, i)) == v) {

      return i;
    };
  };

  return -1;
}
int array_int_reduce(array_int a, int (*iter)(int accum, int curr /*FFF*/),
                     int accum_start) {

  int _accum = 0;

  _accum = accum_start;

  for (int i = 0; i < a.len; i++) {

    _accum = iter(_accum, (*(int *)array_get(a, i)));
  };

  return _accum;
}
bool array_int_eq(array_int a, array_int a2) { return array_eq_T_int(a, a2); }
bool array_i64_eq(array_i64 a, array_i64 a2) { return array_eq_T_i64(a, a2); }
bool array_string_eq(array_string a, array_string a2) {

  return array_eq_T_string(a, a2);
}
bool array_byte_eq(array_byte a, array_byte a2) {

  return array_eq_T_byte(a, a2);
}
bool array_f32_eq(array_f32 a, array_f32 a2) { return array_eq_T_f32(a, a2); }
void builtin__init() {

#ifdef _WIN32

  if (is_atty(0) > 0) {

    _setmode(_fileno(stdin), _O_U16TEXT);

  } else {

    _setmode(_fileno(stdin), _O_U8TEXT);
  };

  _setmode(_fileno(stdout), _O_U8TEXT);

  SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),
                 ENABLE_PROCESSED_OUTPUT | 0x0004);

  setbuf(stdout, 0);

#endif
  ;
}
void v_exit(int code) { exit(code); }
bool isnil(void *v) { return v == 0; }
void on_panic(int (*f)(int /*FFF*/)) {}
void print_backtrace_skipping_top_frames(int skipframes) {

#ifdef __APPLE__

  byte *buffer[100];

  int nr_ptrs = backtrace(((voidptr *)(buffer)), 100);

  backtrace_symbols_fd(((voidptr *)(&buffer[skipframes] /*rbyte* 0*/)),
                       nr_ptrs - skipframes, 1);

  return;

#endif
  ;

#ifdef __linux__

#ifndef __BIONIC__

#ifdef __GLIBC__

  byte *buffer[100];

  int nr_ptrs = backtrace(((voidptr *)(buffer)), 100);

  int nr_actual_frames = nr_ptrs - skipframes;

  array_string sframes = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  byteptr *csymbols = ((byteptr *)(backtrace_symbols(
      ((voidptr *)(&buffer[skipframes] /*rbyte* 0*/)), nr_actual_frames)));

  int tmp1 = 0;
  ;
  for (int tmp2 = tmp1; tmp2 < nr_actual_frames; tmp2++) {
    int i = tmp2;

    _PUSH(&sframes,
          (/*typ = array_string   tmp_typ=string*/ tos2(
              csymbols[/*ptr*/ i] /*rbyteptr 0*/)),
          tmp3, string);
  };

  array_string tmp4 = sframes;
  for (int tmp5 = 0; tmp5 < tmp4.len; tmp5++) {
    string sframe = ((string *)tmp4.data)[tmp5];

    string executable = string_all_before(sframe, tos3("("));

    string addr =
        string_all_before(string_all_after(sframe, tos3("[")), tos3("]"));

    string cmd = _STR("addr2line -e %.*s %.*s", executable.len, executable.str,
                      addr.len, addr.str);

    void *f = popen((char *)cmd.str, "r");

    if (isnil(f)) {

      println(sframe);

      continue;
    };

    byte buf[1000] = {0};

    string output = tos3("");

    while (fgets(((voidptr)(buf)), 1000, f) != 0) {

      output = string_add(output, tos(buf, vstrlen(buf)));
    };

    output = string_add(string_trim_space(output), tos3(":"));

    if (0 != ((int)(pclose(f)))) {

      println(sframe);

      continue;
    };

    printf("%-45s | %.*s\n", output.str, sframe.len, sframe.str);
  };

  return;

#else

  printf("backtrace_symbols_fd is missing, so printing backtraces is not "
         "available.\n");

  printf("Some libc implementations like musl simply do not provide it.\n");

#endif
  ;

#endif
  ;

#endif
  ;

  println(tos3("print_backtrace_skipping_top_frames is not implemented on this "
               "platform for now...\n"));
}
void print_backtrace() { print_backtrace_skipping_top_frames(2); }
void panic_debug(int line_no, string file, string mod, string fn_name,
                 string s) {

  println(tos3("================ V panic ================"));

  printf("   module: %.*s\n", mod.len, mod.str);

  printf(" function: %.*s()\n", fn_name.len, fn_name.str);

  printf("     file: %.*s\n", file.len, file.str);

  println(string_add(tos3("     line: "), int_str(line_no)));

  printf("  message: %.*s\n", s.len, s.str);

  println(tos3("========================================="));

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

    v_panic(tos3("println(NIL)"));
  };

#ifdef _WIN32

  _putws(string_to_wide(s));

#else

  printf("%.*s\n", s.len, (char *)s.str);

#endif
  ;
}
void eprintln(string s) {

  if (isnil(s.str)) {

    v_panic(tos3("eprintln(NIL)"));
  };

#ifdef __APPLE__

  fprintf(stderr, "%.*s\n", s.len, (char *)s.str);

  fflush(stderr);

  return;

#endif
  ;

#ifdef __linux__

  fprintf(stderr, "%.*s\n", s.len, (char *)s.str);

  fflush(stderr);

  return;

#endif
  ;

  println(s);
}
void print(string s) {

#ifdef _WIN32

  wprintf(string_to_wide(s));

#else

  printf("%.*s", s.len, (char *)s.str);

#endif
  ;
}
byte *v_malloc(int n) {

  if (n < 0) {

    v_panic(tos3("malloc(<0)"));
  };

  byte *ptr = malloc(n);

  if (isnil(ptr)) {

    v_panic(_STR("malloc(%d) failed", n));
  };

  return ptr;
}
byte *v_calloc(int n) {

  if (n < 0) {

    v_panic(tos3("calloc(<0)"));
  };

  return calloc(n, 1);
}
void v_free(void *ptr) { free(ptr); }
void *memdup(void *src, int sz) {

  byte *mem = v_malloc(sz);

  return memcpy((char *)mem, src, sz);
}
void v_ptr_free(void *ptr) { free(ptr); }
int is_atty(int fd) {

#ifdef _WIN32

  int mode = 0;

  GetConsoleMode(_get_osfhandle(fd), &mode);

  return mode;

#else

  return isatty(fd);

#endif
  ;
}
int backtrace(void *a, int b);
byteptr *backtrace_symbols(void *, int);
void backtrace_symbols_fd(void *, int, int);
int proc_pidpath(int, void *, int);
string f64_str(f64 d) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(((char *)(buf)), "%f", d);

  return tos(buf, vstrlen(buf));
}
string f32_str(f32 d) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(((char *)(buf)), "%f", d);

  return tos(buf, vstrlen(buf));
}
f32 f32_abs(f32 a) { return (a < 0) ? (-a) : (a); }
f64 f64_abs(f64 a) { return (a < 0) ? (-a) : (a); }
bool f64_eq(f64 a, f64 b) { return f64_abs(a - b) <= DBL_EPSILON; }
bool f32_eq(f32 a, f32 b) { return f32_abs(a - b) <= FLT_EPSILON; }
bool f64_eqbit(f64 a, f64 b) { return DEFAULT_EQUAL(a, b); }
bool f32_eqbit(f32 a, f32 b) { return DEFAULT_EQUAL(a, b); }
bool f64_ne(f64 a, f64 b) { return !f64_eq(a, b); }
bool f32_ne(f32 a, f32 b) { return !f32_eq(a, b); }
bool f64_nebit(f64 a, f64 b) { return DEFAULT_NOT_EQUAL(a, b); }
bool f32_nebit(f32 a, f32 b) { return DEFAULT_NOT_EQUAL(a, b); }
bool f64_lt(f64 a, f64 b) { return f64_ne(a, b) && f64_ltbit(a, b); }
bool f32_lt(f32 a, f32 b) { return f32_ne(a, b) && f32_ltbit(a, b); }
bool f64_ltbit(f64 a, f64 b) { return DEFAULT_LT(a, b); }
bool f32_ltbit(f32 a, f32 b) { return DEFAULT_LT(a, b); }
bool f64_le(f64 a, f64 b) { return !f64_gt(a, b); }
bool f32_le(f32 a, f32 b) { return !f32_gt(a, b); }
bool f64_lebit(f64 a, f64 b) { return DEFAULT_LE(a, b); }
bool f32_lebit(f32 a, f32 b) { return DEFAULT_LE(a, b); }
bool f64_gt(f64 a, f64 b) { return f64_ne(a, b) && f64_gtbit(a, b); }
bool f32_gt(f32 a, f32 b) { return f32_ne(a, b) && f32_gtbit(a, b); }
bool f64_gtbit(f64 a, f64 b) { return DEFAULT_GT(a, b); }
bool f32_gtbit(f32 a, f32 b) { return DEFAULT_GT(a, b); }
bool f64_ge(f64 a, f64 b) { return !f64_lt(a, b); }
bool f32_ge(f32 a, f32 b) { return !f32_lt(a, b); }
bool f64_gebit(f64 a, f64 b) { return DEFAULT_GE(a, b); }
bool f32_gebit(f32 a, f32 b) { return DEFAULT_GE(a, b); }
hashmap new_hashmap(int planned_nr_items) {

  int cap = planned_nr_items * 5;

  if (cap < builtin__min_cap) {

    cap = builtin__min_cap;
  };

  if (cap > builtin__max_cap) {

    cap = builtin__max_cap;
  };

  return (hashmap){.cap = cap,
                   .elm_size = 4,
                   .table = make(cap, cap, sizeof(hashmapentry)),
                   .keys = new_array(0, 1, sizeof(string)),
                   .nr_collisions = 0};
}
void hashmap_set(hashmap *m, string key, int val) {

  int hash = ((int)(b_fabs(string_hash(key))));

  int idx = hash % m->cap;

  if ((*(hashmapentry *)array_get(m->table, idx)).key.len != 0) {

    m->nr_collisions++;

    hashmapentry *e = &(*(hashmapentry *)array_get(m->table, idx));

    while (e->next != 0) {

      e = e->next;
    };

    e->next = (hashmapentry *)memdup(&(hashmapentry){key, val, 0},
                                     sizeof(hashmapentry));

  } else {

    array_set(&/*q*/ m->table, idx,
              &(hashmapentry[]){(hashmapentry){key, val, 0}});
  };
}
int hashmap_get(hashmap *m, string key) {

  int hash = ((int)(b_fabs(string_hash(key))));

  int idx = hash % m->cap;

  hashmapentry *e = &(*(hashmapentry *)array_get(m->table, idx));

  while (e->next != 0) {

    if (string_eq(e->key, key)) {

      return e->val;
    };

    e = e->next;
  };

  return e->val;
}
static inline f64 b_fabs(int v) { return (v < 0) ? (-v) : (v); }
string ptr_str(void *ptr) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(((char *)(buf)), "%p", ptr);

  return tos(buf, vstrlen(buf));
}
string int_str(int nn) {

  int n = nn;

  if (n == 0) {

    return tos3("0");
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

    return tos3("0");
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

    return tos3("0");
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

    return tos3("0");
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

    return tos3("true");
  };

  return tos3("false");
}
string int_hex(int n) {

  int len = (n >= 0) ? (int_str(n).len + 3) : (11);

  byte *hex = v_malloc(len);

  int count = ((int)(sprintf(((char *)(hex)), "0x%x", n)));

  return tos(hex, count);
}
string i64_hex(i64 n) {

  int len = (n >= ((i64)(0))) ? (i64_str(n).len + 3) : (19);

  byte *hex = v_malloc(len);

  int count = ((int)(sprintf(((char *)(hex)), "0x%" PRIx64, n)));

  return tos(hex, count);
}
bool array_byte_contains(array_byte a, byte val) {

  array_byte tmp1 = a;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    byte aa = ((byte *)tmp1.data)[tmp2];

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

  array_byte res = array_repeat(
      new_array_from_c_array(1, 1, sizeof(byte),
                             EMPTY_ARRAY_OF_ELEMS(byte, 1){((byte)(0))}),
      b.len);

  for (int i = 0; i < b.len; i++) {

    array_set(&/*q*/ res, i, &(byte[]){(*(byte *)array_get(b, i))});
  };

  return res;
}
map new_map(int cap, int elm_size) {

  map res = (map){.element_size = elm_size, .root = 0, .size = 0};

  return res;
}
map new_map_init(int cap, int elm_size, string *keys, void *vals) {

  map res = (map){.element_size = elm_size, .root = 0, .size = 0};

  int tmp1 = 0;
  ;
  for (int tmp2 = tmp1; tmp2 < cap; tmp2++) {
    int i = tmp2;

    map_set(&/* ? */ res, keys[/*ptr*/ i] /*rstring 0*/,
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
void map_set(map *m, string key, void *val) {

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

    array_set(keys, i, &(string[]){node->key});

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

  array_string keys = array_repeat(
      new_array_from_c_array(1, 1, sizeof(string),
                             EMPTY_ARRAY_OF_ELEMS(string, 1){tos3("")}),
      m->size);

  if (isnil(m->root)) {

    return keys;
  };

  preorder_keys(m->root, &/*111*/ (array[]){keys}[0], 0);

  return keys;
}
bool map_get(map m, string key, void *out) {

  if (m.root == 0) {

    return 0;
  };

  return mapnode_find(&/* ? */ *m.root, key, out, m.element_size);
}
void v_mapnode_delete(mapnode *n, string key, int element_size) {

  if (string_eq(n->key, key)) {

    memset(n->val, 0, element_size);

    n->is_empty = 1;

    return;

  } else if (string_gt(n->key, key)) {

    if (isnil(n->left)) {

      return;

    } else {

      v_mapnode_delete(n->left, key, element_size);
    };

  } else {

    if (isnil(n->right)) {

      return;

    } else {

      v_mapnode_delete(n->right, key, element_size);
    };
  };
}
void v_map_delete(map *m, string key) {

  if (map_exists(*m, key)) {

    v_mapnode_delete(m->root, key, m->element_size);

    m->size--;
  };
}
bool map_exists(map m, string key) {

  return !isnil(m.root) && mapnode_find2(&/* ? */ *m.root, key, m.element_size);
}
void map_print(map m) {

  println(tos3("<<<<<<<<"));

  println(tos3(">>>>>>>>>>"));
}
void v_mapnode_free(mapnode *n) {

  if (n->val != 0) {

    v_free(n->val);
  };

  if (n->left != 0) {

    v_mapnode_free(n->left);
  };

  if (n->right != 0) {

    v_mapnode_free(n->right);
  };

  v_free(n);
}
void v_map_free(map *m) {

  if (m->root == 0) {

    return;
  };

  v_mapnode_free(m->root);
}
string map_string_str(map_string m) {

  if (m.size == 0) {

    return tos3("{}");
  };

  strings__Builder sb = strings__new_builder(50);

  strings__Builder_writeln(&/* ? */ sb, tos3("{"));

  map_string tmp3 = m;
  array_string keys_tmp3 = map_keys(&tmp3);
  for (int l = 0; l < keys_tmp3.len; l++) {
    string key = ((string *)keys_tmp3.data)[l];
    string val = tos3("");
    map_get(tmp3, key, &val);

    strings__Builder_writeln(
        &/* ? */ sb,
        _STR("  \"%.*s\" => \"%.*s\"", key.len, key.str, val.len, val.str));
  };

  strings__Builder_writeln(&/* ? */ sb, tos3("}"));

  return strings__Builder_str(sb);
}
Option opt_ok(void *data, int size) {

  if (size >= 300) {

    v_panic(
        _STR("option size too big: %d (max is 300), this is a temporary limit",
             size));
  };

  Option res = (Option){.ok = 1, .error = tos3(""), .ecode = 0, .is_none = 0};

  memcpy(res.data, data, size);

  return res;
}
Option opt_none() {

  return (Option){
      .is_none = 1,
      .error = tos3(""),
      .ecode = 0,
      .ok = 0,
  };
}
Option v_error(string s) {

  return (Option){.error = s, .ecode = 0, .ok = 0, .is_none = 0};
}
Option error_with_code(string s, int code) {

  return (Option){.error = s, .ecode = code, .ok = 0, .is_none = 0};
}
int vstrlen(byte *s) { return strlen(((char *)(s))); }
string tos(byte *s, int len) {

  if (s == 0) {

    v_panic(tos3("tos(): nil string"));
  };

  return (string){.str = s, .len = len};
}
string tos_clone(byte *s) {

  if (s == 0) {

    v_panic(tos3("tos: nil string"));
  };

  return string_clone(tos2(s));
}
string tos2(byte *s) {

  if (s == 0) {

    v_panic(tos3("tos2: nil string"));
  };

  return (string){.str = s, .len = vstrlen(s)};
}
string tos3(char *s) {

  if (s == 0) {

    v_panic(tos3("tos3: nil string"));
  };

  return (string){.str = ((byteptr)(s)), .len = strlen(s)};
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

  array_int idxs = new_array_from_c_array(
      0, 0, sizeof(int), EMPTY_ARRAY_OF_ELEMS(int, 0){TCCSKIP(0)});

  string rem = s;

  int rstart = 0;

  while (1) {

    int i = string_index(rem, rep);

    if (i < 0) {

      break;
    };

    _PUSH(&idxs, (/*typ = array_int   tmp_typ=int*/ rstart + i), tmp1, int);

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

  int cur_idx = (*(int *)array_get(idxs, idx_pos));

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

        cur_idx = (*(int *)array_get(idxs, idx_pos));
      };

    } else {

      b[/*ptr*/ b_i] /*rbyte 1*/ = s.str[i] /*rbyte 0*/;

      b_i++;
    };
  };

  b[/*ptr*/ new_len] /*rbyte 1*/ = '\0';

  return tos(b, new_len);
}
int v_string_int(string s) {

  bool neg = 0;

  int i = 0;

  if (s.str[0] /*rbyte 0*/ == '-') {

    neg = 1;

    i++;

  } else if (s.str[0] /*rbyte 0*/ == '+') {

    i++;
  };

  int n = 0;

  while (isdigit(s.str[i] /*rbyte 0*/)) {

    n = 10 * n - ((int)(s.str[i] /*rbyte 0*/ - '0'));

    i++;
  };

  return (neg) ? (n) : (-n);
}
i64 string_i64(string s) { return strconv__parse_int(s, 0, 64); }
f32 string_f32(string s) { return atof(((char *)(s.str))); }
f64 string_f64(string s) { return atof(((char *)(s.str))); }
u32 string_u32(string s) {

  bool neg = 0;

  int i = 0;

  if (s.str[0] /*rbyte 0*/ == '-') {

    neg = 1;

    i++;

  } else if (s.str[0] /*rbyte 0*/ == '+') {

    i++;
  };

  u32 n = ((u32)(0));

  while (isdigit(s.str[i] /*rbyte 0*/)) {

    n = ((u32)(10)) * n - ((u32)(s.str[i] /*rbyte 0*/ - '0'));

    i++;
  };

  return (neg) ? (n) : (-n);
}
u64 string_u64(string s) { return strconv__parse_uint(s, 0, 64); }
bool string_eq(string s, string a) {

  if (isnil(s.str)) {

    v_panic(tos3("string.eq(): nil string"));
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

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (delim.len == 0) {

    _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ s), tmp6, string);

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

        _PUSH(&res,
              (/*typ = array_string   tmp_typ=string*/ string_trim_space(val)),
              tmp7, string);
      };

      start = i;
    };

    i++;
  };

  return res;
}
array_string string_split_single(string s, byte delim) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (((int)(delim)) == 0) {

    _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ s), tmp8, string);

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

        _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ val), tmp9,
              string);
      };

      start = i + 1;
    };

    i++;
  };

  return res;
}
array_string string_split_into_lines(string s) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

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

      _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ line), tmp10,
            string);

      start = i + 1;
    };
  };

  return res;
}
string string_left(string s, int n) {

  if (n >= s.len) {

    return s;
  };

  return string_substr(s, 0, n);
}
string string_right(string s, int n) {

  if (n >= s.len) {

    return tos3("");
  };

  return string_substr(s, n, s.len);
}
string string_substr2(string s, int start, int _end, bool end_max) {

  int end = (end_max) ? (s.len) : (_end);

  return string_substr(s, start, end);
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

  int i = 0;

  while (i < s.len) {

    int j = 0;

    while (j < p.len && s.str[i + j] /*rbyte 0*/ == p.str[j] /*rbyte 0*/) {

      j++;
    };

    if (j == p.len) {

      return i;
    };

    i++;
  };

  return -1;
}
int string_index_kmp(string s, string p) {

  if (p.len > s.len) {

    return -1;
  };

  array_int prefix =
      array_repeat(new_array_from_c_array(1, 1, sizeof(int),
                                          EMPTY_ARRAY_OF_ELEMS(int, 1){0}),
                   p.len);

  int j = 0;

  for (int i = 1; i < p.len; i++) {

    while (p.str[j] /*rbyte 0*/ != p.str[i] /*rbyte 0*/ && j > 0) {

      j = (*(int *)array_get(prefix, j - 1));
    };

    if (p.str[j] /*rbyte 0*/ == p.str[i] /*rbyte 0*/) {

      j++;
    };

    array_set(&/*q*/ prefix, i, &(int[]){j});
  };

  j = 0;

  for (int i = 0; i < s.len; i++) {

    while (p.str[j] /*rbyte 0*/ != s.str[i] /*rbyte 0*/ && j > 0) {

      j = (*(int *)array_get(prefix, j - 1));
    };

    if (p.str[j] /*rbyte 0*/ == s.str[i] /*rbyte 0*/) {

      j++;
    };

    if (j == p.len) {

      return i - p.len + 1;
    };
  };

  return -1;
}
int string_index_any(string s, string chars) {

  string tmp15 = chars;
  array_byte bytes_tmp15 = string_bytes(tmp15);
  ;
  for (int tmp16 = 0; tmp16 < tmp15.len; tmp16++) {
    byte c = ((byte *)bytes_tmp15.data)[tmp16];

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
int string_index_byte(string s, byte c) {

  for (int i = 0; i < s.len; i++) {

    if (s.str[i] /*rbyte 0*/ == c) {

      return i;
    };
  };

  return -1;
}
int string_last_index_byte(string s, byte c) {

  for (int i = s.len - 1; i >= 0; i--) {

    if (s.str[i] /*rbyte 0*/ == c) {

      return i;
    };
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

  array_string words = string_split(s, tos3(" "));

  array_string tit = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string tmp17 = words;
  for (int tmp18 = 0; tmp18 < tmp17.len; tmp18++) {
    string word = ((string *)tmp17.data)[tmp18];

    _PUSH(&tit,
          (/*typ = array_string   tmp_typ=string*/ string_capitalize(word)),
          tmp19, string);
  };

  string title = array_string_join(tit, tos3(" "));

  return title;
}
string string_find_between(string s, string start, string end) {

  int start_pos = string_index(s, start);

  if (start_pos == -1) {

    return tos3("");
  };

  string val = string_right(s, start_pos + start.len);

  int end_pos = string_index(val, end);

  if (end_pos == -1) {

    return val;
  };

  return string_left(val, end_pos);
}
bool array_string_contains(array_string ar, string val) {

  array_string tmp20 = ar;
  for (int tmp21 = 0; tmp21 < tmp20.len; tmp21++) {
    string s = ((string *)tmp20.data)[tmp21];

    if (string_eq(s, val)) {

      return 1;
    };
  };

  return 0;
}
bool array_int_contains(array_int ar, int val) {

  array_int tmp22 = ar;
  for (int i = 0; i < tmp22.len; i++) {
    int s = ((int *)tmp22.data)[i];

    if (s == val) {

      return 1;
    };
  };

  return 0;
}
bool byte_is_space(byte c) {

  return c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' ||
         c == '\r';
}
string string_trim_space(string s) {

  return string_trim(s, tos3(" \n\t\v\f\r"));
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

    if ((_IN(byte, (s.str[pos_left] /*rbyte 0*/), cs_arr))) {

      pos_left++;

      cs_match = 1;
    };

    if ((_IN(byte, (s.str[pos_right] /*rbyte 0*/), cs_arr))) {

      pos_right--;

      cs_match = 1;
    };

    if (pos_left > pos_right) {

      return tos3("");
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

  while (pos <= s.len && (_IN(byte, (s.str[pos] /*rbyte 0*/), cs_arr))) {

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

  while (pos >= -1 && (_IN(byte, (s.str[pos] /*rbyte 0*/), cs_arr))) {

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

  array_sort_with_compare(
      s, &/*112 EXP:"void*" GOT:"fn (string*,string*) int" */ compare_strings);
}
void array_string_sort_ignore_case(array_string *s) {

  array_sort_with_compare(s,
                          &/*112 EXP:"void*" GOT:"fn (string*,string*) int" */
                          compare_lower_strings);
}
void array_string_sort_by_len(array_string *s) {

  array_sort_with_compare(s,
                          &/*112 EXP:"void*" GOT:"fn (string*,string*) int" */
                          compare_strings_by_len);
}
ustring string_ustring(string s) {

  ustring res =
      (ustring){.s = s, .runes = new_array(0, s.len, sizeof(int)), .len = 0};

  for (int i = 0; i < s.len; i++) {

    int char_len = utf8_char_len(s.str[/*ptr*/ i] /*rbyte 0*/);

    _PUSH(&res.runes, (/*typ = array_int   tmp_typ=int*/ i), tmp23, int);

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
bool ustring_eq(ustring u, ustring a) {

  if (u.len != a.len || string_ne(u.s, a.s)) {

    return 0;
  };

  return 1;
}
bool ustring_ne(ustring u, ustring a) { return !ustring_eq(u, a); }
bool ustring_lt(ustring u, ustring a) { return string_lt(u.s, a.s); }
bool ustring_le(ustring u, ustring a) {

  return ustring_lt(u, a) || ustring_eq(u, a);
}
bool ustring_gt(ustring u, ustring a) { return !ustring_le(u, a); }
bool ustring_ge(ustring u, ustring a) { return !ustring_lt(u, a); }
ustring ustring_add(ustring u, ustring a) {

  ustring res = (ustring){.s = string_add(u.s, a.s),
                          .runes = new_array(0, u.s.len + a.s.len, sizeof(int)),
                          .len = 0};

  int j = 0;

  for (int i = 0; i < u.s.len; i++) {

    int char_len = utf8_char_len(u.s.str[/*ptr*/ i] /*rbyte 0*/);

    _PUSH(&res.runes, (/*typ = array_int   tmp_typ=int*/ j), tmp24, int);

    i += char_len - 1;

    j += char_len;

    res.len++;
  };

  for (int i = 0; i < a.s.len; i++) {

    int char_len = utf8_char_len(a.s.str[/*ptr*/ i] /*rbyte 0*/);

    _PUSH(&res.runes, (/*typ = array_int   tmp_typ=int*/ j), tmp25, int);

    i += char_len - 1;

    j += char_len;

    res.len++;
  };

  return res;
}
int ustring_index_after(ustring u, ustring p, int start) {

  if (p.len > u.len) {

    return -1;
  };

  int strt = start;

  if (start < 0) {

    strt = 0;
  };

  if (start > u.len) {

    return -1;
  };

  int i = strt;

  while (i < u.len) {

    int j = 0;

    int ii = i;

    while (j < p.len && string_eq(ustring_at(u, ii), ustring_at(p, j))) {

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
int ustring_count(ustring u, ustring substr) {

  if (u.len == 0 || substr.len == 0) {

    return 0;
  };

  if (substr.len > u.len) {

    return 0;
  };

  int n = 0;

  int i = 0;

  while (1) {

    i = ustring_index_after(u, substr, i);

    if (i == -1) {

      return n;
    };

    i += substr.len;

    n++;
  };

  return 0;
}
string ustring_substr(ustring u, int _start, int _end) {

  if (_start > _end || _start > u.len || _end > u.len || _start < 0 ||
      _end < 0) {

    v_panic(_STR("substr(%d, %d) out of bounds (len=%d)", _start, _end, u.len));
  };

  int end = (_end >= u.len) ? (u.s.len) : ((*(int *)array_get(u.runes, _end)));

  return string_substr(u.s, (*(int *)array_get(u.runes, _start)), end);
}
string ustring_left(ustring u, int pos) {

  if (pos >= u.len) {

    return u.s;
  };

  return ustring_substr(u, 0, pos);
}
string ustring_right(ustring u, int pos) {

  if (pos >= u.len) {

    return tos3("");
  };

  return ustring_substr(u, pos, u.len);
}
byte string_at(string s, int idx) {

  if (idx < 0 || idx >= s.len) {

    v_panic(_STR("string index out of range: %d / %d", idx, s.len));
  };

  return s.str[/*ptr*/ idx] /*rbyte 0*/;
}
string ustring_at(ustring u, int idx) {

  if (idx < 0 || idx >= u.len) {

    v_panic(_STR("string index out of range: %d / %d", idx, u.runes.len));
  };

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

    return tos3("");
  };

  int len = 0;

  array_string tmp30 = a;
  for (int i = 0; i < tmp30.len; i++) {
    string val = ((string *)tmp30.data)[i];

    len += val.len + del.len;
  };

  len -= del.len;

  string res = tos3("");

  res.len = len;

  res.str = v_malloc(res.len + 1);

  int idx = 0;

  array_string tmp31 = a;
  for (int i = 0; i < tmp31.len; i++) {
    string val = ((string *)tmp31.data)[i];

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

  return array_string_join(s, tos3("\n"));
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

    string tmp32 = s;
    array_byte bytes_tmp32 = string_bytes(tmp32);
    ;
    for (int tmp33 = 0; tmp33 < tmp32.len; tmp33++) {
      byte c = ((byte *)bytes_tmp32.data)[tmp33];

      h = h * 31 + ((int)(c));
    };
  };

  return h;
}
array_byte string_bytes(string s) {

  if (s.len == 0) {

    return new_array_from_c_array(0, 0, sizeof(byte),
                                  EMPTY_ARRAY_OF_ELEMS(byte, 0){TCCSKIP(0)});
  };

  array_byte buf = array_repeat(
      new_array_from_c_array(1, 1, sizeof(byte),
                             EMPTY_ARRAY_OF_ELEMS(byte, 1){((byte)(0))}),
      s.len);

  memcpy(buf.data, (char *)s.str, s.len);

  return buf;
}
string string_repeat(string s, int count) {

  if (count <= 1) {

    return s;
  };

  byte *ret = v_malloc(s.len * count + 1);

  int tmp34 = 0;
  ;
  for (int tmp35 = tmp34; tmp35 < count; tmp35++) {
    int i = tmp35;

    int tmp36 = 0;
    ;
    for (int tmp37 = tmp36; tmp37 < s.len; tmp37++) {
      int j = tmp37;

      ret[/*ptr*/ i * s.len + j] /*rbyte 1*/ = s.str[j] /*rbyte 0*/;
    };
  };

  ret[/*ptr*/ s.len * count] /*rbyte 1*/ = 0;

  return (tos2((byte *)ret));
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

  return tos3("");
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

  return tos3("");
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

  int num_chars = ((int)(MultiByteToWideChar(
      builtin__CP_UTF8, 0, (char *)_str.str, _str.len, 0, 0)));

  u16 *wstr = ((u16 *)(v_malloc((num_chars + 1) * 2)));

  if (wstr > 0) {

    MultiByteToWideChar(builtin__CP_UTF8, 0, (char *)_str.str, _str.len, wstr,
                        num_chars);

    memset((char *)((byte *)(wstr)) + num_chars * 2, 0, 2);
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

  return tos3("");

#endif
  ;
}
string string_from_wide2(u16 *_wstr, int len) {

#ifdef _WIN32

  int num_chars =
      ((int)(WideCharToMultiByte(builtin__CP_UTF8, 0, _wstr, len, 0, 0, 0, 0)));

  byte *str_to = ((byte *)(v_malloc(num_chars + 1)));

  if (str_to > 0) {

    WideCharToMultiByte(builtin__CP_UTF8, 0, _wstr, len, (char *)str_to,
                        num_chars, 0, 0);

    memset((char *)((byte *)(str_to)) + num_chars, 0, 1);
  };

  return tos2(str_to);

#else

  return tos3("");

#endif
  ;
}
int utf8_len(byte c) {

  int b = 0;

  byte x = c;

  if (((x & 240) != 0)) {

    x >>= 4;

  } else {

    b += 4;
  };

  if (((x & 12) != 0)) {

    x >>= 2;

  } else {

    b += 2;
  };

  if (((x & 2) == 0)) {

    b++;
  };

  return b;
}
int utf8_getchar() {

  int c = ((int)(getchar()));

  int len = utf8_len(~c);

  if (c < 0) {

    return 0;

  } else if (len == 0) {

    return c;

  } else if (len == 1) {

    return -1;

  } else {

    int uc = ((int)(c & ((1 << (7 - len)) - 1)));

    for (int i = 0; i + 1 < len; i++) {

      int c2 = ((int)(getchar()));

      if (c2 != -1 && (c2 >> 6) == 2) {

        uc <<= 6;

        uc |= ((int)((c2 & 63)));

      } else if (c2 == -1) {

        return 0;

      } else {

        return -1;
      };
    };

    return uc;
  };
}
strings__Builder strings__new_builder(int initial_size) {

  return (strings__Builder){.buf = make(0, initial_size, sizeof(byte)),
                            .len = 0};
}
void strings__Builder_write(strings__Builder *b, string s) {

  array_push_many(&/* ? */ b->buf, s.str, s.len);

  b->len += s.len;
}
void strings__Builder_writeln(strings__Builder *b, string s) {

  array_push_many(&/* ? */ b->buf, s.str, s.len);

  _PUSH(&b->buf, (/*typ = array_byte   tmp_typ=byte*/ '\n'), tmp1, byte);

  b->len += s.len + 1;
}
string strings__Builder_str(strings__Builder b) {

  return (tos((byte *)b.buf.data, b.len));
}
void strings__Builder_cut(strings__Builder *b, int n) { b->len -= n; }
void strings__Builder_free(strings__Builder *b) {}
int strings__levenshtein_distance(string a, string b) {

  array_int f =
      array_repeat(new_array_from_c_array(1, 1, sizeof(int),
                                          EMPTY_ARRAY_OF_ELEMS(int, 1){0}),
                   b.len + 1);

  string tmp1 = a;
  array_byte bytes_tmp1 = string_bytes(tmp1);
  ;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    byte ca = ((byte *)bytes_tmp1.data)[tmp2];

    int j = 1;

    int fj1 = (*(int *)array_get(f, 0));

    (*(int *)array_get(f, 0))++;

    string tmp7 = b;
    array_byte bytes_tmp7 = string_bytes(tmp7);
    ;
    for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
      byte cb = ((byte *)bytes_tmp7.data)[tmp8];

      int mn =
          ((*(int *)array_get(f, j)) + 1 <= (*(int *)array_get(f, j - 1)) + 1)
              ? ((*(int *)array_get(f, j)) + 1)
              : ((*(int *)array_get(f, j - 1)) + 1);

      if (cb != ca) {

        mn = (mn <= fj1 + 1) ? (mn) : (fj1 + 1);

      } else {

        mn = (mn <= fj1) ? (mn) : (fj1);
      };

      fj1 = (*(int *)array_get(f, j));

      array_set(&/*q*/ f, j, &(int[]){mn});

      j++;
    };
  };

  return (*(int *)array_get(f, f.len - 1));
}
f32 strings__levenshtein_distance_percentage(string a, string b) {

  int d = strings__levenshtein_distance(a, b);

  int l = (a.len >= b.len) ? (a.len) : (b.len);

  return (1.00 - ((f32)(d)) / ((f32)(l))) * 100.00;
}
f32 strings__dice_coefficient(string s1, string s2) {

  if (s1.len == 0 || s2.len == 0) {

    return 0.0;
  };

  if (string_eq(s1, s2)) {

    return 1.0;
  };

  if (s1.len < 2 || s2.len < 2) {

    return 0.0;
  };

  string a = (s1.len > s2.len) ? (s1) : (s2);

  string b = (string_eq(a, s1)) ? (s2) : (s1);

  map_int first_bigrams = new_map(1, sizeof(int));

  for (int i = 0; i < a.len - 1; i++) {

    string bigram = string_substr2(a, i, i + 2, false);

    int tmp23 = 0;
    bool tmp24 = map_get(/*similarity.v : 47*/ first_bigrams, bigram, &tmp23);

    int q = ((_IN_MAP((bigram), first_bigrams))) ? (tmp23 + 1) : (1);

    map_set(&first_bigrams, bigram, &(int[]){q});
  };

  int intersection_size = 0;

  for (int i = 0; i < b.len - 1; i++) {

    string bigram = string_substr2(b, i, i + 2, false);

    int tmp27 = 0;
    bool tmp28 = map_get(/*similarity.v : 53*/ first_bigrams, bigram, &tmp27);

    int count = ((_IN_MAP((bigram), first_bigrams))) ? (tmp27) : (0);

    if (count > 0) {

      map_set(&first_bigrams, bigram, &(int[]){count - 1});

      intersection_size++;
    };
  };

  return (2.0 * intersection_size) / (((f32)(a.len)) + ((f32)(b.len)) - 2);
}
string strings__repeat(byte c, int n) {

  if (n <= 0) {

    return tos3("");
  };

  array_byte arr =
      array_repeat(new_array_from_c_array(1, 1, sizeof(byte),
                                          EMPTY_ARRAY_OF_ELEMS(byte, 1){c}),
                   n + 1);

  array_set(&/*q*/ arr, n, &(byte[]){'\0'});

  return (tos((byte *)arr.data, n));
}
byte strconv__byte_to_lower(byte c) { return c | ('x' - 'X'); }
u64 strconv__parse_uint(string s, int _base, int _bit_size) {

  int bit_size = _bit_size;

  int base = _base;

  if (s.len < 1 || !strconv__underscore_ok(s)) {

    return ((u64)(0));
  };

  bool base0 = base == 0;

  int start_index = 0;

  if (2 <= base && base <= 36) {

  } else if (base == 0) {

    base = 10;

    if (string_at(s, 0) == '0') {

      if (s.len >= 3 && strconv__byte_to_lower(string_at(s, 1)) == 'b') {

        base = 2;

        start_index += 2;

      } else if (s.len >= 3 && strconv__byte_to_lower(string_at(s, 1)) == 'o') {

        base = 8;

        start_index += 2;

      } else if (s.len >= 3 && strconv__byte_to_lower(string_at(s, 1)) == 'x') {

        base = 16;

        start_index += 2;

      } else {

        base = 8;

        start_index++;
      };
    };

  } else {

    return ((u64)(0));
  };

  if (bit_size == 0) {

    bit_size = ((int)(strconv__int_size));

  } else if (bit_size < 0 || bit_size > 64) {

    return ((u64)(0));
  };

  u64 cutoff = ((u64)(strconv__max_u64 / ((u64)(base)))) + ((u64)(1));

  u64 max_val = (bit_size == 64)
                    ? (strconv__max_u64)
                    : (((u64)(((u64)(1)) << ((u64)(bit_size)))) - ((u64)(1)));

  bool underscores = 0;

  u64 n = ((u64)(0));

  int tmp9 = start_index;
  ;
  for (int tmp10 = tmp9; tmp10 < s.len; tmp10++) {
    int i = tmp10;

    byte c = string_at(s, i);

    byte cl = strconv__byte_to_lower(c);

    byte d = ((byte)(0));

    if (c == '_' && base0) {

      underscores = 1;

      continue;

    } else if ('0' <= c && c <= '9') {

      d = c - '0';

    } else if ('a' <= cl && cl <= 'z') {

      d = cl - 'a' + 10;

    } else {

      return ((u64)(0));
    };

    if (d >= ((byte)(base))) {

      return ((u64)(0));
    };

    if (n >= cutoff) {

      return max_val;
    };

    n *= ((u64)(base));

    u64 n1 = n + ((u64)(d));

    if (n1 < n || n1 > max_val) {

      return max_val;
    };

    n = n1;
  };

  if (underscores && !strconv__underscore_ok(s)) {

    return ((u64)(0));
  };

  return n;
}
i64 strconv__parse_int(string _s, int base, int _bit_size) {

  string s = _s;

  int bit_size = _bit_size;

  if (s.len < 1) {

    return ((i64)(0));
  };

  bool neg = 0;

  if (string_at(s, 0) == '+') {

    s = string_substr2(s, 1, -1, true);

  } else if (string_at(s, 0) == '-') {

    neg = 1;

    s = string_substr2(s, 1, -1, true);
  };

  u64 un = strconv__parse_uint(s, base, bit_size);

  if (un == 0) {

    return ((i64)(0));
  };

  if (bit_size == 0) {

    bit_size = ((int)(strconv__int_size));
  };

  u64 cutoff = ((u64)(((u64)(1)) << ((u64)(bit_size - 1))));

  if (!neg && un >= cutoff) {

    return ((i64)(cutoff - ((u64)(1))));
  };

  if (neg && un > cutoff) {

    return -((i64)(cutoff));
  };

  return (neg) ? (-((i64)(un))) : (((i64)(un)));
}
int strconv__atoi(string s) {

  if ((strconv__int_size == 32 && (0 < s.len && s.len < 10)) ||
      (strconv__int_size == 64 && (0 < s.len && s.len < 19))) {

    int start_idx = 0;

    if (string_at(s, 0) == '-' || string_at(s, 0) == '+') {

      start_idx++;

      if (s.len - start_idx < 1) {

        return 0;
      };
    };

    int n = 0;

    int tmp25 = start_idx;
    ;
    for (int tmp26 = tmp25; tmp26 < s.len; tmp26++) {
      int i = tmp26;

      byte ch = string_at(s, i) - '0';

      if (ch > 9) {

        return 0;
      };

      n = n * 10 + ((int)(ch));
    };

    return (string_at(s, 0) == '-') ? (-n) : (n);
  };

  i64 int64 = strconv__parse_int(s, 10, 0);

  return ((int)(int64));
}
bool strconv__underscore_ok(string s) {

  byte saw = '^';

  int i = 0;

  if (s.len >= 1 && (string_at(s, 0) == '-' || string_at(s, 0) == '+')) {

    i++;
  };

  bool hex = 0;

  if (s.len - i >= 2 && string_at(s, i) == '0' &&
      (strconv__byte_to_lower(string_at(s, i + 1)) == 'b' ||
       strconv__byte_to_lower(string_at(s, i + 1)) == 'o' ||
       strconv__byte_to_lower(string_at(s, i + 1)) == 'x')) {

    saw = '0';

    hex = strconv__byte_to_lower(string_at(s, i + 1)) == 'x';

    i += 2;
  };

  for (; i < s.len; i++) {

    if (('0' <= string_at(s, i) && string_at(s, i) <= '9') ||
        (hex && 'a' <= strconv__byte_to_lower(string_at(s, i)) &&
         strconv__byte_to_lower(string_at(s, i)) <= 'f')) {

      saw = '0';

      continue;
    };

    if (string_at(s, i) == '_') {

      if (saw != '0') {

        return 0;
      };

      saw = '_';

      continue;
    };

    if (saw == '_') {

      return 0;
    };

    saw = '!';
  };

  return saw != '_';
}
array_byte os__File_read_bytes(os__File f, int size) {

  return os__File_read_bytes_at(f, size, 0);
}
array_byte os__File_read_bytes_at(os__File f, int size, int pos) {

  byte *data = v_malloc(size);

  array_byte arr =
      array_repeat(new_array_from_c_array(1, 1, sizeof(byte),
                                          EMPTY_ARRAY_OF_ELEMS(byte, 1){'0'}),
                   size);

  fseek(f.cfile, pos, SEEK_SET);

  fread((char *)data, 1, size, f.cfile);

  fseek(f.cfile, 0, SEEK_SET);

  for (int e = 0; e < size; e++) {

    array_set(&/*q*/ arr, e, &(byte[]){data[/*ptr*/ e] /*rbyte 1*/});
  };

  return arr;
}
Option_string os__read_file(string path) {

  string mode = tos3("rb");

  FILE *fp = os__vfopen(path, mode);

  if (isnil(fp)) {

    return v_error(_STR("failed to open file \"%.*s\"", path.len, path.str));
  };

  fseek(fp, 0, SEEK_END);

  int fsize = ftell(fp);

  rewind(fp);

  byte *str = v_malloc(fsize + 1);

  fread((char *)str, fsize, 1, fp);

  fclose(fp);

  str[/*ptr*/ fsize] /*rbyte 1*/ = 0;

  string tmp1 = OPTION_CAST(string)((tos((byte *)str, fsize)));
  return opt_ok(&tmp1, sizeof(string));
}
int os__file_size(string path) {

  struct /*c struct init*/

      stat s;

#ifdef _WIN32

  _wstat(string_to_wide(path), &s);

#else

  stat(((char *)(path.str)), &s);

#endif
  ;

  return s.st_size;
}
void os__mv(string old, string new) {

#ifdef _WIN32

  _wrename(string_to_wide(old), string_to_wide(new));

#else

  rename(((char *)(old.str)), ((char *)(new.str)));

#endif
  ;
}
Option_bool os__cp(string old, string new) {

#ifdef _WIN32

  string _old = string_replace(old, tos3("/"), tos3("\\"));

  string _new = string_replace(new, tos3("/"), tos3("\\"));

  CopyFile(string_to_wide(_old), string_to_wide(_new), 0);

  u32 result = GetLastError();

  if (result == 0) {

    bool tmp2 = OPTION_CAST(bool)(1);
    return opt_ok(&tmp2, sizeof(bool));

  } else {

    return error_with_code(
        _STR("failed to copy %.*s to %.*s", old.len, old.str, new.len, new.str),
        ((int)(result)));
  };

#else

  os__system(_STR("cp %.*s %.*s", old.len, old.str, new.len, new.str));

  bool tmp3 = OPTION_CAST(bool)(1);
  return opt_ok(&tmp3, sizeof(bool));

#endif
  ;
}
Option_bool os__cp_r(string source_path, string dest_path, bool overwrite) {

  if (!os__file_exists(source_path)) {

    return v_error(tos3("Source path doesn\'t exist"));
  };

  if (!os__is_dir(source_path)) {

    string adjasted_path =
        (os__is_dir(dest_path))
            ? (filepath__join(
                  dest_path,
                  &(varg_string){.len = 1, .args = {os__basedir(source_path)}}))
            : (dest_path);

    if (os__file_exists(adjasted_path)) {

      if (overwrite) {

        os__rm(adjasted_path);

      } else {

        return v_error(tos3("Destination file path already exist"));
      };
    };

    Option_bool tmp4 = os__cp(source_path, adjasted_path);
    if (!tmp4.ok) {
      string err = tmp4.error;
      int errcode = tmp4.ecode;

      return v_error(err);
    };

    bool tmp5 = OPTION_CAST(bool)(1);
    return opt_ok(&tmp5, sizeof(bool));
  };

  if (!os__is_dir(dest_path)) {

    return v_error(tos3("Destination path is not a valid directory"));
  };

  Option_array_string tmp6 = os__ls(source_path);
  array_string files;
  if (!tmp6.ok) {
    string err = tmp6.error;
    int errcode = tmp6.ecode;

    return v_error(err);
  }
  files = *(array_string *)tmp6.data;
  ;

  array_string tmp7 = files;
  for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
    string file = ((string *)tmp7.data)[tmp8];

    string sp =
        filepath__join(source_path, &(varg_string){.len = 1, .args = {file}});

    string dp =
        filepath__join(dest_path, &(varg_string){.len = 1, .args = {file}});

    if (os__is_dir(sp)) {

      os__mkdir(dp);
    };

    Option_bool tmp9 = os__cp_r(sp, dp, overwrite);
    if (!tmp9.ok) {
      string err = tmp9.error;
      int errcode = tmp9.ecode;

      os__rmdir(dp);

      v_panic(err);
    };
  };

  bool tmp10 = OPTION_CAST(bool)(1);
  return opt_ok(&tmp10, sizeof(bool));
}
FILE *os__vfopen(string path, string mode) {

#ifdef _WIN32

  return _wfopen(string_to_wide(path), string_to_wide(mode));

#else

  return fopen(((char *)(path.str)), ((char *)(mode.str)));

#endif
  ;
}
array_string os__read_lines(string path) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  int buf_len = 1024;

  byte *buf = v_malloc(buf_len);

  string mode = tos3("rb");

  FILE *fp = os__vfopen(path, mode);

  if (isnil(fp)) {

    return res;
  };

  int buf_index = 0;

  while (fgets((char *)buf + buf_index, buf_len - buf_index, fp) != 0) {

    int len = vstrlen(buf);

    if (len == buf_len - 1 && buf[/*ptr*/ len - 1] /*rbyte 1*/ != 10) {

      buf_len *= 2;

      buf = realloc((char *)buf, buf_len);

      if (isnil(buf)) {

        v_panic(tos3("Could not reallocate the read buffer"));
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

    _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ tos_clone(buf)), tmp11,
          string);

    buf_index = 0;
  };

  fclose(fp);

  return res;
}
array_ustring os__read_ulines(string path) {

  array_string lines = os__read_lines(path);

  array_ustring ulines = new_array_from_c_array(
      0, 0, sizeof(ustring), EMPTY_ARRAY_OF_ELEMS(ustring, 0){TCCSKIP(0)});

  array_string tmp12 = lines;
  for (int tmp13 = 0; tmp13 < tmp12.len; tmp13++) {
    string myline = ((string *)tmp12.data)[tmp13];

    _PUSH(&ulines,
          (/*typ = array_ustring   tmp_typ=ustring*/ string_ustring(myline)),
          tmp14, ustring);
  };

  return ulines;
}
Option_os__File os__open(string path) {

  os__File file = (os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(path);

  string mode = tos3("rb");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(((char *)(cpath)), "rb")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(_STR("failed to open file \"%.*s\"", path.len, path.str));
  };

  os__File tmp15 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp15, sizeof(os__File));
}
Option_os__File os__create(string path) {

  os__File file = (os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(string_replace(path, tos3("/"), tos3("\\")));

  string mode = tos3("wb");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(((char *)(cpath)), "wb")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(_STR("failed to create file \"%.*s\"", path.len, path.str));
  };

  os__File tmp16 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp16, sizeof(os__File));
}
Option_os__File os__open_append(string path) {

  os__File file = (os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(string_replace(path, tos3("/"), tos3("\\")));

  string mode = tos3("ab");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(((char *)(cpath)), "ab")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(
        _STR("failed to create(append) file \"%.*s\"", path.len, path.str));
  };

  os__File tmp17 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp17, sizeof(os__File));
}
void os__File_write(os__File f, string s) { fputs((char *)s.str, f.cfile); }
void os__File_write_bytes(os__File f, void *data, int size) {

  fwrite(data, 1, size, f.cfile);
}
void os__File_write_bytes_at(os__File f, void *data, int size, int pos) {

  fseek(f.cfile, pos, SEEK_SET);

  fwrite(data, 1, size, f.cfile);

  fseek(f.cfile, 0, SEEK_END);
}
void os__File_writeln(os__File f, string s) {

  fputs((char *)s.str, f.cfile);

  fputs("\n", f.cfile);
}
void os__File_flush(os__File f) { fflush(f.cfile); }
void os__File_close(os__File f) { fclose(f.cfile); }
void *os__vpopen(string path) {

#ifdef _WIN32

  string mode = tos3("rb");

  u16 *wpath = string_to_wide(path);

  return _wpopen(wpath, string_to_wide(mode));

#else

  byte *cpath = path.str;

  return popen((char *)cpath, "r");

#endif
  ;
}
_V_MulRet_int_V_bool os__posix_wait4_to_exit_status(int waitret) {

#ifdef _WIN32

  return (_V_MulRet_int_V_bool){.var_0 = waitret, .var_1 = 0};

#else

  int ret = 0;

  bool is_signaled = 1;

  if (WIFEXITED(waitret)) {

    ret = WEXITSTATUS(waitret);

    is_signaled = 0;

  } else if (WIFSIGNALED(waitret)) {

    ret = WTERMSIG(waitret);

    is_signaled = 1;
  };

  return (_V_MulRet_int_V_bool){.var_0 = ret, .var_1 = is_signaled};

#endif
  ;
}
int os__vpclose(void *f) {

#ifdef _WIN32

  return ((int)(_pclose(f)));

#else

  _V_MulRet_int_V_bool _V_mret_ret__ =
      os__posix_wait4_to_exit_status(((int)(pclose(f))));
  int ret = _V_mret_ret__.var_0;

  return ret;

#endif
  ;
}
int os__system(string cmd) {

  if (string_contains(cmd, tos3(";")) || string_contains(cmd, tos3("&&")) ||
      string_contains(cmd, tos3("||")) || string_contains(cmd, tos3("\n"))) {

    v_panic(tos3(";, &&, || and \\n are not allowed in shell commands"));
  };

  int ret = ((int)(0));

#ifdef _WIN32

  ret = _wsystem(string_to_wide(cmd));

#else

  ret = system((char *)cmd.str);

#endif
  ;

  if (ret == -1) {

    os__print_c_errno();
  };

#ifndef _WIN32

  _V_MulRet_int_V_bool _V_mret_pret_is_signaled =
      os__posix_wait4_to_exit_status(ret);
  int pret = _V_mret_pret_is_signaled.var_0;
  bool is_signaled = _V_mret_pret_is_signaled.var_1;

  if (is_signaled) {

    println(string_add(string_add(_STR("Terminated by signal %2d (", ret),
                                  os__sigint_to_signal_name(pret)),
                       tos3(")")));
  };

  ret = pret;

#endif
  ;

  return ret;
}
string os__sigint_to_signal_name(int si) {

  int tmp18 = si;

  if (tmp18 == 1) {

    return tos3("SIGHUP");

  } else if (tmp18 == 2) {

    return tos3("SIGINT");

  } else if (tmp18 == 3) {

    return tos3("SIGQUIT");

  } else if (tmp18 == 4) {

    return tos3("SIGILL");

  } else if (tmp18 == 6) {

    return tos3("SIGABRT");

  } else if (tmp18 == 8) {

    return tos3("SIGFPE");

  } else if (tmp18 == 9) {

    return tos3("SIGKILL");

  } else if (tmp18 == 11) {

    return tos3("SIGSEGV");

  } else if (tmp18 == 13) {

    return tos3("SIGPIPE");

  } else if (tmp18 == 14) {

    return tos3("SIGALRM");

  } else if (tmp18 == 15) {

    return tos3("SIGTERM");
  };

#ifdef __linux__

  int tmp19 = si;

  if ((tmp19 == 30) || (tmp19 == 10) || (tmp19 == 16)) {

    return tos3("SIGUSR1");

  } else if ((tmp19 == 31) || (tmp19 == 12) || (tmp19 == 17)) {

    return tos3("SIGUSR2");

  } else if ((tmp19 == 20) || (tmp19 == 17) || (tmp19 == 18)) {

    return tos3("SIGCHLD");

  } else if ((tmp19 == 19) || (tmp19 == 18) || (tmp19 == 25)) {

    return tos3("SIGCONT");

  } else if ((tmp19 == 17) || (tmp19 == 19) || (tmp19 == 23)) {

    return tos3("SIGSTOP");

  } else if ((tmp19 == 18) || (tmp19 == 20) || (tmp19 == 24)) {

    return tos3("SIGTSTP");

  } else if ((tmp19 == 21) || (tmp19 == 21) || (tmp19 == 26)) {

    return tos3("SIGTTIN");

  } else if ((tmp19 == 22) || (tmp19 == 22) || (tmp19 == 27)) {

    return tos3("SIGTTOU");

  } else if (tmp19 == 5) {

    return tos3("SIGTRAP");

  } else if (tmp19 == 7) {

    return tos3("SIGBUS");
  };

#endif
  ;

  return tos3("unknown");
}
string os__getenv(string key) {

#ifdef _WIN32

  void *s = _wgetenv(string_to_wide(key));

  if (isnil(s)) {

    return tos3("");
  };

  return string_from_wide(s);

#else

  byte *s = ((byte *)(getenv((char *)key.str)));

  if (isnil(s)) {

    return tos3("");
  };

  return (tos2((byte *)s));

#endif
  ;
}
int os__setenv(string name, string value, bool overwrite) {

#ifdef _WIN32

  string format = _STR("%.*s=%.*s", name.len, name.str, value.len, value.str);

  if (overwrite) {

    return _putenv((char *)format.str);
  };

  return -1;

#else

  return setenv((char *)name.str, (char *)value.str, overwrite);

#endif
  ;
}
int os__unsetenv(string name) {

#ifdef _WIN32

  string format = _STR("%.*s=", name.len, name.str);

  return _putenv((char *)format.str);

#else

  return unsetenv((char *)name.str);

#endif
  ;
}
bool os__file_exists(string _path) {

#ifdef _WIN32

  string path = string_replace(_path, tos3("/"), tos3("\\"));

  return _waccess(string_to_wide(path), 0) != -1;

#else

  return access((char *)_path.str, 0) != -1;

#endif
  ;
}
void os__rm(string path) {

#ifdef _WIN32

  _wremove(string_to_wide(path));

#else

  remove((char *)path.str);

#endif
  ;
}
void os__rmdir(string path) {

#ifndef _WIN32

  rmdir((char *)path.str);

#else

  RemoveDirectory(string_to_wide(path));

#endif
  ;
}
void os__print_c_errno() {}
string os__ext(string path) {

  int pos = string_last_index(path, tos3("."));

  if (pos == -1) {

    return tos3("");
  };

  return string_substr2(path, pos, -1, true);
}
string os__dir(string path) {

  if (string_eq(path, tos3("."))) {

    return os__getwd();
  };

  int pos = string_last_index(path, os__path_separator);

  if (pos == -1) {

    return tos3(".");
  };

  return string_substr2(path, 0, pos, false);
}
string os__path_sans_ext(string path) {

  int pos = string_last_index(path, tos3("."));

  if (pos == -1) {

    return path;
  };

  return string_substr2(path, 0, pos, false);
}
string os__basedir(string path) {

  int pos = string_last_index(path, os__path_separator);

  if (pos == -1) {

    return path;
  };

  return string_substr2(path, 0, pos + 1, false);
}
string os__filename(string path) {

  return string_all_after(path, os__path_separator);
}
string os__get_line() {

  string str = os__get_raw_line();

#ifdef _WIN32

  return string_trim_right(str, tos3("\r\n"));

#else

  return string_trim_right(str, tos3("\n"));

#endif
  ;
}
string os__get_raw_line() {

#ifdef _WIN32

  int max_line_chars = 256;

  byte *buf = ((byte *)(v_malloc(max_line_chars * 2)));

  if (is_atty(0) > 0) {

    void *h_input = GetStdHandle(os__STD_INPUT_HANDLE);

    int nr_chars = 0;

    ReadConsole(h_input, (char *)buf, max_line_chars * 2, &nr_chars, 0);

    return string_from_wide2(((u16 *)(buf)), nr_chars);
  };

  int res = ((int)(fgetws((char *)buf, max_line_chars, stdin)));

  int len = ((int)(wcslen(((u16 *)(buf)))));

  if (0 != res) {

    return string_from_wide2(((u16 *)(buf)), len);
  };

  return tos3("");

#else

  size_t max = ((size_t)(256));

  char *buf = ((char *)(v_malloc(((int)(max)))));

  int nr_chars = getline(&buf, &max, stdin);

  if (nr_chars == 0) {

    return tos3("");
  };

  return (tos((byte *)((byteptr)(buf)), nr_chars));

#endif
  ;
}
array_string os__get_lines() {

  string line = tos3("");

  array_string inputstr = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (1) {

    line = os__get_line();

    if ((line.len <= 0)) {

      break;
    };

    line = string_trim_space(line);

    _PUSH(&inputstr, (/*typ = array_string   tmp_typ=string*/ line), tmp28,
          string);
  };

  return inputstr;
}
string os__get_lines_joined() {

  string line = tos3("");

  string inputstr = tos3("");

  while (1) {

    line = os__get_line();

    if (line.len <= 0) {

      break;
    };

    line = string_trim_space(line);

    inputstr = string_add(inputstr, line);
  };

  return inputstr;
}
string os__user_os() {

#ifdef __linux__

  return tos3("linux");

#endif
  ;

#ifdef __APPLE__

  return tos3("mac");

#endif
  ;

#ifdef _WIN32

  return tos3("windows");

#endif
  ;

#ifdef __FreeBSD__

  return tos3("freebsd");

#endif
  ;

#ifdef __OpenBSD__

  return tos3("openbsd");

#endif
  ;

#ifdef __NetBSD__

  return tos3("netbsd");

#endif
  ;

#ifdef __DragonFly__

  return tos3("dragonfly");

#endif
  ;

#ifdef __BIONIC__

  return tos3("android");

#endif
  ;

#ifdef __sun

  return tos3("solaris");

#endif
  ;

  return tos3("unknown");
}
string os__home_dir() {

  string home = os__getenv(tos3("HOME"));

#ifdef _WIN32

  home = os__getenv(tos3("HOMEDRIVE"));

  if (home.len == 0) {

    home = os__getenv(tos3("SYSTEMDRIVE"));
  };

  string homepath = os__getenv(tos3("HOMEPATH"));

  if (homepath.len == 0) {

    homepath = string_add(tos3("\\Users\\"), os__getenv(tos3("USERNAME")));
  };

  home = string_add(home, homepath);

#endif
  ;

  home = string_add(home, os__path_separator);

  return home;
}
void os__write_file(string path, string text) {

  Option_os__File tmp29 = os__create(path);
  os__File f;
  if (!tmp29.ok) {
    string err = tmp29.error;
    int errcode = tmp29.ecode;

    return;
  }
  f = *(os__File *)tmp29.data;
  ;

  os__File_write(f, text);

  os__File_close(f);
}
void os__clear() {

#ifndef _WIN32

  printf("\x1b[2J");

  printf("\x1b[H");

#endif
  ;
}
void os__on_segfault(void *f) {

#ifdef _WIN32

  return;

#endif
  ;

#ifdef __APPLE__

  struct /*c struct init*/

      sigaction sa;

  memset(&sa, 0, sizeof(sigaction));

  sigemptyset(&sa.sa_mask);

  sa.sa_sigaction = f;

  sa.sa_flags = SA_SIGINFO;

  sigaction(SIGSEGV, &sa, 0);

#endif
  ;
}
string os__executable() {

#ifdef __linux__

  byte *result = v_malloc(os__MAX_PATH);

  int count = ((int)(readlink("/proc/self/exe", (char *)result, os__MAX_PATH)));

  if (count < 0) {

    v_panic(tos3("error reading /proc/self/exe to get exe path"));
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

  int pid = getpid();

  int ret = proc_pidpath(pid, (char *)result, os__MAX_PATH);

  if (ret <= 0) {

    println(tos3("os.executable() failed"));

    return tos3(".");
  };

  return (tos2((byte *)result));

#endif
  ;

#ifdef __FreeBSD__

  byte *result = v_malloc(os__MAX_PATH);

  array_int mib = new_array_from_c_array(
      4, 4, sizeof(int), EMPTY_ARRAY_OF_ELEMS(int, 4){1, 14, 12, -1});

  int size = os__MAX_PATH;

  sysctl(mib.data, 4, (char *)result, &size, 0, 0);

  return (tos2((byte *)result));

#endif
  ;

#ifdef __OpenBSD__

  return (*(string *)array_get(os__args, 0));

#endif
  ;

#ifdef __sun

#endif
  ;

#ifdef __NetBSD__

  byte *result = v_malloc(os__MAX_PATH);

  int count =
      ((int)(readlink("/proc/curproc/exe", (char *)result, os__MAX_PATH)));

  if (count < 0) {

    v_panic(tos3("error reading /proc/curproc/exe to get exe path"));
  };

  return (tos((byte *)result, count));

#endif
  ;

#ifdef __DragonFly__

  byte *result = v_malloc(os__MAX_PATH);

  int count =
      ((int)(readlink("/proc/curproc/file", (char *)result, os__MAX_PATH)));

  if (count < 0) {

    v_panic(tos3("error reading /proc/curproc/file to get exe path"));
  };

  return (tos((byte *)result, count));

#endif
  ;

  return (*(string *)array_get(os__args, 0));
}
bool os__is_dir(string path) {

#ifdef _WIN32

  return os__dir_exists(path);

#else

  struct /*c struct init*/

      stat statbuf;

  byte *cstr = path.str;

  if (stat((char *)cstr, &statbuf) != 0) {

    return 0;
  };

  return (((int)(statbuf.st_mode)) & os__S_IFMT) == os__S_IFDIR;

#endif
  ;
}
void os__chdir(string path) {

#ifdef _WIN32

  _wchdir(string_to_wide(path));

#else

  chdir((char *)path.str);

#endif
  ;
}
string os__getwd() {

#ifdef _WIN32

  int max = 512;

  u16 *buf = ((u16 *)(v_malloc(max * 2)));

  if (_wgetcwd(buf, max) == 0) {

    return tos3("");
  };

  return string_from_wide(buf);

#else

  byte *buf = v_malloc(512);

  if (getcwd((char *)buf, 512) == 0) {

    return tos3("");
  };

  return (tos2((byte *)buf));

#endif
  ;
}
string os__realpath(string fpath) {

  byte *fullpath = v_malloc(os__MAX_PATH);

  int res = 0;

#ifdef _WIN32

  res = ((int)(_fullpath((char *)fullpath, (char *)fpath.str, os__MAX_PATH)));

#else

  res = ((int)(!isnil(realpath((char *)fpath.str, (char *)fullpath))));

#endif
  ;

  if (res != 0) {

    return (tos((byte *)fullpath, vstrlen(fullpath)));
  };

  return fpath;
}
array_string os__walk_ext(string path, string ext) {

  if (!os__is_dir(path)) {

    return new_array_from_c_array(0, 0, sizeof(string),
                                  EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});
  };

  Option_array_string tmp34 = os__ls(path);
  array_string files;
  if (!tmp34.ok) {
    string err = tmp34.error;
    int errcode = tmp34.ecode;

    v_panic(err);
  }
  files = *(array_string *)tmp34.data;
  ;

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string tmp35 = files;
  for (int i = 0; i < tmp35.len; i++) {
    string file = ((string *)tmp35.data)[i];

    if (string_starts_with(file, tos3("."))) {

      continue;
    };

    string p = string_add(string_add(path, os__path_separator), file);

    if (os__is_dir(p)) {

      _PUSH_MANY(&res,
                 (/*typ = array_string   tmp_typ=string*/ os__walk_ext(p, ext)),
                 tmp36, array_string);

    } else if (string_ends_with(file, ext)) {

      _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ p), tmp37, string);
    };
  };

  return res;
}
void os__walk(string path, void (*fnc)(string path /*FFF*/)) {

  if (!os__is_dir(path)) {

    return;
  };

  Option_array_string tmp38 = os__ls(path);
  array_string files;
  if (!tmp38.ok) {
    string err = tmp38.error;
    int errcode = tmp38.ecode;

    v_panic(err);
  }
  files = *(array_string *)tmp38.data;
  ;

  array_string tmp39 = files;
  for (int tmp40 = 0; tmp40 < tmp39.len; tmp40++) {
    string file = ((string *)tmp39.data)[tmp40];

    string p = string_add(string_add(path, os__path_separator), file);

    if (os__is_dir(p)) {

      os__walk(p, fnc);

    } else if (os__file_exists(p)) {

      fnc(p);
    };
  };

  return;
}
void os__signal(int signum, void *handler) { signal(signum, handler); }
int os__fork() {

#ifndef _WIN32

  int pid = fork();

  return pid;

#endif
  ;

  v_panic(tos3("os.fork not supported in windows"));
}
int os__wait() {

#ifndef _WIN32

  int pid = wait(0);

  return pid;

#endif
  ;

  v_panic(tos3("os.wait not supported in windows"));
}
int os__file_last_mod_unix(string path) {

  struct /*c struct init*/

      stat attr;

  stat((char *)path.str, &attr);

  return attr.st_mtime;
}
void os__log(string s) { println(string_add(tos3("os.log: "), s)); }
void os__flush_stdout() { fflush(stdout); }
void os__print_backtrace() {}
void os__mkdir_all(string path) {

  string p = (string_starts_with(path, os__path_separator))
                 ? (os__path_separator)
                 : (tos3(""));

  array_string tmp41 = string_split(path, os__path_separator);
  for (int tmp42 = 0; tmp42 < tmp41.len; tmp42++) {
    string subdir = ((string *)tmp41.data)[tmp42];

    p = string_add(p, string_add(subdir, os__path_separator));

    if (!os__dir_exists(p)) {

      os__mkdir(p);
    };
  };
}
string os__join(string base, varg_string *dirs) {

  println(tos3("use filepath.join"));

  return filepath__join(base, dirs);
}
array_string os__init_os_args(int argc, byteptr *argv) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  voidptr *args_list = ((voidptr *)(0));

  int args_count = 0;

  args_list = CommandLineToArgvW(GetCommandLine(), &args_count);

  for (int i = 0; i < args_count; i++) {

    _PUSH(&args,
          (/*typ = array_string   tmp_typ=string*/ string_from_wide(
              ((u16 *)(args_list[/*ptr*/ i] /*rvoidptr 1*/)))),
          tmp1, string);
  };

  LocalFree(args_list);

  return args;
}
Option_array_string os__ls(string path) {

  os__Win32finddata find_file_data = (os__Win32finddata){.dwFileAttributes = 0,
                                                         .nFileSizeHigh = 0,
                                                         .nFileSizeLow = 0,
                                                         .dwReserved0 = 0,
                                                         .dwReserved1 = 0,
                                                         .dwFileType = 0,
                                                         .dwCreatorType = 0,
                                                         .wFinderFlags = 0};

  array_string dir_files = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (!os__dir_exists(path)) {

    return v_error(
        _STR("ls() couldnt open dir \"%.*s\": directory does not exist",
             path.len, path.str));
  };

  string path_files = _STR("%.*s\\*", path.len, path.str);

  void *h_find_files =
      FindFirstFile(string_to_wide(path_files), &find_file_data);

  string first_filename = string_from_wide(((u16 *)(find_file_data.cFileName)));

  if (string_ne(first_filename, tos3(".")) &&
      string_ne(first_filename, tos3(".."))) {

    _PUSH(&dir_files, (/*typ = array_string   tmp_typ=string*/ first_filename),
          tmp2, string);
  };

  while (FindNextFile(h_find_files, &find_file_data)) {

    string filename = string_from_wide(((u16 *)(find_file_data.cFileName)));

    if (string_ne(filename, tos3(".")) && string_ne(filename, tos3(".."))) {

      _PUSH(&dir_files,
            (/*typ = array_string   tmp_typ=string*/ string_clone(filename)),
            tmp3, string);
    };
  };

  FindClose(h_find_files);

  array_string tmp4 = OPTION_CAST(array_string)(dir_files);
  return opt_ok(&tmp4, sizeof(array_string));
}
bool os__dir_exists(string path) {

  string _path = string_replace(path, tos3("/"), tos3("\\"));

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

  string _path = string_replace(path, tos3("/"), tos3("\\"));

  if (string_last_index(_path, tos3("\\")) != -1) {

    os__mkdir(string_all_before_last(_path, tos3("\\")));
  };

  CreateDirectory(string_to_wide(_path), 0);
}
HANDLE os__get_file_handle(string path) {

  string mode = tos3("rb");

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

    void *status = GetModuleFileName(handle, &buf, sz);

    void *tmp5 = status;

    if (tmp5 == os__SUCCESS) {

      string _filename = string_from_wide2(buf, sz);

      string tmp6 = OPTION_CAST(string)(_filename);
      return opt_ok(&tmp6, sizeof(string));

    } else // default:
    {

      return v_error(tos3("Cannot get file name from handle"));
    };
  };

  v_panic(tos3("this should be unreachable"));
}
void *os__ptr_win_get_error_msg(u32 code) {

  voidptr buf = ((voidptr)(0));

  if (code > ((u32)(os__MAX_ERROR_CODE))) {

    return buf;
  };

  FormatMessage(
      os__FORMAT_MESSAGE_ALLOCATE_BUFFER | os__FORMAT_MESSAGE_FROM_SYSTEM |
          os__FORMAT_MESSAGE_IGNORE_INSERTS,
      0, code, MAKELANGID(os__LANG_NEUTRAL, os__SUBLANG_DEFAULT), &buf, 0, 0);

  return buf;
}
string os__get_error_msg(int code) {

  if (code < 0) {

    return tos3("");
  };

  void *_ptr_text = os__ptr_win_get_error_msg(((u32)(code)));

  if (_ptr_text == 0) {

    return tos3("");
  };

  return string_from_wide(_ptr_text);
}
Option_os__Result os__exec(string cmd) {

  if (string_contains(cmd, tos3(";")) || string_contains(cmd, tos3("&&")) ||
      string_contains(cmd, tos3("||")) || string_contains(cmd, tos3("\n"))) {

    return v_error(tos3(";, &&, || and \\n are not allowed in shell commands"));
  };

  u32 *child_stdin = ((u32 *)(0));

  u32 *child_stdout_read = ((u32 *)(0));

  u32 *child_stdout_write = ((u32 *)(0));

  os__SecurityAttributes sa = (os__SecurityAttributes){
      .nLength = 0, .lpSecurityDescriptor = 0, .bInheritHandle = 0};

  sa.nLength = sizeof(SECURITY_ATTRIBUTES);

  sa.bInheritHandle = 1;

  void *create_pipe_result =
      CreatePipe(&child_stdout_read, &child_stdout_write, &sa, 0);

  if (create_pipe_result == 0) {

    string error_msg = os__get_error_msg(((int)(GetLastError())));

    return v_error(
        _STR("exec failed (CreatePipe): %.*s", error_msg.len, error_msg.str));
  };

  void *set_handle_info_result =
      SetHandleInformation(child_stdout_read, HANDLE_FLAG_INHERIT, 0);

  if (set_handle_info_result == 0) {

    string error_msg = os__get_error_msg(((int)(GetLastError())));

    v_panic(_STR("exec failed (SetHandleInformation): %.*s", error_msg.len,
                 error_msg.str));
  };

  os__ProcessInformation proc_info = (os__ProcessInformation){
      .hProcess = 0, .hThread = 0, .dwProcessId = 0, .dwThreadId = 0};

  os__StartupInfo start_info = (os__StartupInfo){.cb = 0,
                                                 .lpReserved = 0,
                                                 .lpDesktop = 0,
                                                 .lpTitle = 0,
                                                 .dwX = 0,
                                                 .dwY = 0,
                                                 .dwXSize = 0,
                                                 .dwYSize = 0,
                                                 .dwXCountChars = 0,
                                                 .dwYCountChars = 0,
                                                 .dwFillAttribute = 0,
                                                 .dwFlags = 0,
                                                 .wShowWindow = 0,
                                                 .cbReserved2 = 0,
                                                 .lpReserved2 = 0,
                                                 .hStdInput = 0,
                                                 .hStdOutput = 0,
                                                 .hStdError = 0};

  start_info.cb = sizeof(PROCESS_INFORMATION);

  start_info.hStdInput = child_stdin;

  start_info.hStdOutput = child_stdout_write;

  start_info.hStdError = child_stdout_write;

  start_info.dwFlags = ((u32)(STARTF_USESTDHANDLES));

  u16 command_line[32768] = {0};

  ExpandEnvironmentStrings(string_to_wide(cmd), &command_line, 32768);

  void *create_process_result = CreateProcess(0, command_line, 0, 0, TRUE, 0, 0,
                                              0, &start_info, &proc_info);

  if (create_process_result == 0) {

    string error_msg = os__get_error_msg(((int)(GetLastError())));

    return v_error(_STR("exec failed (CreateProcess): %.*s", error_msg.len,
                        error_msg.str));
  };

  CloseHandle(child_stdin);

  CloseHandle(child_stdout_write);

  byte buf[1000] = {0};

  int bytes_read = 0;

  string read_data = tos3("");

  while (1) {

    void *readfile_result =
        ReadFile(child_stdout_read, buf, 1000, &bytes_read, 0);

    read_data = string_add(read_data, tos(buf, bytes_read));

    if ((readfile_result == 0 || bytes_read == 0)) {

      break;
    };
  };

  read_data = string_trim_space(read_data);

  int exit_code = 0;

  WaitForSingleObject(proc_info.hProcess, INFINITE);

  GetExitCodeProcess(proc_info.hProcess, &exit_code);

  CloseHandle(proc_info.hProcess);

  CloseHandle(proc_info.hThread);

  os__Result tmp7 = OPTION_CAST(os__Result)(
      (os__Result){.output = read_data, .exit_code = exit_code});
  return opt_ok(&tmp7, sizeof(os__Result));
}
rand__Pcg32 rand__new_pcg32(u64 initstate, u64 initseq) {

  rand__Pcg32 rng = (rand__Pcg32){.state = 0, .inc = 0};

  rng.state = ((u64)(0));

  rng.inc = ((u64)(((u64)(initseq << ((u64)(1)))) | ((u64)(1))));

  rand__Pcg32_next(&/* ? */ rng);

  rng.state += initstate;

  rand__Pcg32_next(&/* ? */ rng);

  return rng;
}
static inline u32 rand__Pcg32_next(rand__Pcg32 *rng) {

  u64 oldstate = rng->state;

  rng->state = oldstate * ((u64)(6364136223846793005)) + rng->inc;

  u32 xorshifted = ((u32)(
      ((u64)(((u64)(oldstate >> ((u64)(18)))) ^ oldstate)) >> ((u64)(27))));

  u32 rot = ((u32)(oldstate >> ((u64)(59))));

  return ((u32)((xorshifted >> rot) | (xorshifted << ((-rot) & ((u32)(31))))));
}
static inline u32 rand__Pcg32_bounded_next(rand__Pcg32 *rng, u32 bound) {

  u32 threshold = ((u32)(-bound % bound));

  while (1) {

    u32 r = rand__Pcg32_next(rng);

    if (r >= threshold) {

      return ((u32)(r % bound));
    };
  };

  return ((u32)(0));
}
void rand__seed(int s) { srand(s); }
int rand__next(int max) { return rand() % max; }
int rand__rand_r(int *seed) {

  int *rs = seed;

  int ns = (*rs * 1103515245 + 12345);

  *rs = ns;

  return ns & 0x7fffffff;
}
rand__Splitmix64 rand__new_splitmix64(u64 seed) {

  return (rand__Splitmix64){seed};
}
static inline u64 rand__Splitmix64_next(rand__Splitmix64 *rng) {

  rng->state += ((u64)(0x9e3779b97f4a7c15));

  u64 z = rng->state;

  z = (z ^ ((u64)((z >> ((u64)(30)))))) * ((u64)(0xbf58476d1ce4e5b9));

  z = (z ^ ((u64)((z >> ((u64)(27)))))) * ((u64)(0x94d049bb133111eb));

  return z ^ ((u64)(z >> ((u64)(31))));
}
static inline u64 rand__Splitmix64_bounded_next(rand__Splitmix64 *rng,
                                                u64 bound) {

  u64 threshold = ((u64)(-bound % bound));

  while (1) {

    u64 r = rand__Splitmix64_next(rng);

    if (r >= threshold) {

      return ((u64)(r % bound));
    };
  };

  return ((u64)(0));
}
bool term__can_show_color_on_stdout() {

  return term__supports_escape_sequences(1);
}
bool term__can_show_color_on_stderr() {

  return term__supports_escape_sequences(2);
}
bool term__supports_escape_sequences(int fd) {

#ifdef _WIN32

  return (is_atty(fd) & 0x0004) > 0 &&
         string_ne(os__getenv(tos3("TERM")), tos3("dumb"));

#else

  return is_atty(fd) > 0 && string_ne(os__getenv(tos3("TERM")), tos3("dumb"));

#endif
  ;
}
string term__ok_message(string s) {

  return (term__can_show_color_on_stdout()) ? (term__green(s)) : (s);
}
string term__fail_message(string s) {

  return (term__can_show_color_on_stdout()) ? (term__red(s)) : (s);
}
string term__format(string msg, string open, string close) {

  return string_add(
      string_add(
          string_add(
              string_add(string_add(string_add(tos3("\x1b["), open), tos3("m")),
                         msg),
              tos3("\x1b[")),
          close),
      tos3("m"));
}
string term__format_rgb(int r, int g, int b, string msg, string open,
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
                                              string_add(tos3("\x1b["), open),
                                              tos3(";2;")),
                                          int_str(r)),
                                      tos3(";")),
                                  int_str(g)),
                              tos3(";")),
                          int_str(b)),
                      tos3("m")),
                  msg),
              tos3("\x1b[")),
          close),
      tos3("m"));
}
string term__rgb(int r, int g, int b, string msg) {

  return term__format_rgb(r, g, b, msg, tos3("38"), tos3("39"));
}
string term__bg_rgb(int r, int g, int b, string msg) {

  return term__format_rgb(r, g, b, msg, tos3("48"), tos3("49"));
}
string term__hex(int hex, string msg) {

  return term__format_rgb(hex >> 16, hex >> 8 & 0xFF, hex & 0xFF, msg,
                          tos3("38"), tos3("39"));
}
string term__bg_hex(int hex, string msg) {

  return term__format_rgb(hex >> 16, hex >> 8 & 0xFF, hex & 0xFF, msg,
                          tos3("48"), tos3("49"));
}
string term__bg_black(string msg) {

  return term__format(msg, tos3("40"), tos3("49"));
}
string term__bright_bg_black(string msg) {

  return term__format(msg, tos3("100"), tos3("49"));
}
string term__bg_blue(string msg) {

  return term__format(msg, tos3("44"), tos3("49"));
}
string term__bright_bg_blue(string msg) {

  return term__format(msg, tos3("104"), tos3("49"));
}
string term__bg_cyan(string msg) {

  return term__format(msg, tos3("46"), tos3("49"));
}
string term__bright_bg_cyan(string msg) {

  return term__format(msg, tos3("106"), tos3("49"));
}
string term__bg_green(string msg) {

  return term__format(msg, tos3("42"), tos3("49"));
}
string term__bright_bg_green(string msg) {

  return term__format(msg, tos3("102"), tos3("49"));
}
string term__bg_magenta(string msg) {

  return term__format(msg, tos3("45"), tos3("49"));
}
string term__bright_bg_magenta(string msg) {

  return term__format(msg, tos3("105"), tos3("49"));
}
string term__bg_red(string msg) {

  return term__format(msg, tos3("41"), tos3("49"));
}
string term__bright_bg_red(string msg) {

  return term__format(msg, tos3("101"), tos3("49"));
}
string term__bg_white(string msg) {

  return term__format(msg, tos3("47"), tos3("49"));
}
string term__bright_bg_white(string msg) {

  return term__format(msg, tos3("107"), tos3("49"));
}
string term__bg_yellow(string msg) {

  return term__format(msg, tos3("43"), tos3("49"));
}
string term__bright_bg_yellow(string msg) {

  return term__format(msg, tos3("103"), tos3("49"));
}
string term__black(string msg) {

  return term__format(msg, tos3("30"), tos3("39"));
}
string term__bright_black(string msg) {

  return term__format(msg, tos3("90"), tos3("39"));
}
string term__blue(string msg) {

  return term__format(msg, tos3("34"), tos3("39"));
}
string term__bright_blue(string msg) {

  return term__format(msg, tos3("94"), tos3("39"));
}
string term__bold(string msg) {

  return term__format(msg, tos3("1"), tos3("22"));
}
string term__cyan(string msg) {

  return term__format(msg, tos3("36"), tos3("39"));
}
string term__bright_cyan(string msg) {

  return term__format(msg, tos3("96"), tos3("39"));
}
string term__dim(string msg) {

  return term__format(msg, tos3("2"), tos3("22"));
}
string term__green(string msg) {

  return term__format(msg, tos3("32"), tos3("39"));
}
string term__bright_green(string msg) {

  return term__format(msg, tos3("92"), tos3("39"));
}
string term__gray(string msg) { return term__bright_black(msg); }
string term__hidden(string msg) {

  return term__format(msg, tos3("8"), tos3("28"));
}
string term__italic(string msg) {

  return term__format(msg, tos3("3"), tos3("23"));
}
string term__inverse(string msg) {

  return term__format(msg, tos3("7"), tos3("27"));
}
string term__magenta(string msg) {

  return term__format(msg, tos3("35"), tos3("39"));
}
string term__bright_magenta(string msg) {

  return term__format(msg, tos3("95"), tos3("39"));
}
string term__reset(string msg) {

  return term__format(msg, tos3("0"), tos3("0"));
}
string term__red(string msg) {

  return term__format(msg, tos3("31"), tos3("39"));
}
string term__bright_red(string msg) {

  return term__format(msg, tos3("91"), tos3("39"));
}
string term__strikethrough(string msg) {

  return term__format(msg, tos3("9"), tos3("29"));
}
string term__underline(string msg) {

  return term__format(msg, tos3("4"), tos3("24"));
}
string term__white(string msg) {

  return term__format(msg, tos3("37"), tos3("39"));
}
string term__bright_white(string msg) {

  return term__format(msg, tos3("97"), tos3("39"));
}
string term__yellow(string msg) {

  return term__format(msg, tos3("33"), tos3("39"));
}
string term__bright_yellow(string msg) {

  return term__format(msg, tos3("93"), tos3("39"));
}
void term__set_cursor_position(int x, int y) {

  print(string_add(_STR("\x1b[%d;%d", y, x), tos3("H")));
}
void term__move(int n, string direction) {

  print(_STR("\x1b[%d%.*s", n, direction.len, direction.str));
}
void term__cursor_up(int n) { term__move(n, tos3("A")); }
void term__cursor_down(int n) { term__move(n, tos3("B")); }
void term__cursor_forward(int n) { term__move(n, tos3("C")); }
void term__cursor_back(int n) { term__move(n, tos3("D")); }
void term__erase_display(string t) {

  print(string_add(string_add(tos3("\x1b["), t), tos3("J")));
}
void term__erase_toend() { term__erase_display(tos3("0")); }
void term__erase_tobeg() { term__erase_display(tos3("1")); }
void term__erase_clear() { term__erase_display(tos3("2")); }
void term__erase_del_clear() { term__erase_display(tos3("3")); }
void term__erase_line(string t) {

  print(string_add(string_add(tos3("\x1b["), t), tos3("K")));
}
void term__erase_line_toend() { term__erase_line(tos3("0")); }
void term__erase_line_tobeg() { term__erase_line(tos3("1")); }
void term__erase_line_clear() { term__erase_line(tos3("2")); }
void term__show_cursor() { print(tos3("\x1b[?25h")); }
void term__hide_cursor() { print(tos3("\x1b[?25l")); }
void compiler__todo() {}
void compiler__V_cc(compiler__V *v) {

  compiler__V_build_thirdparty_obj_files(&/* ? */ *v);

  string vexe = compiler__vexe_path();

  string vdir = os__dir(vexe);

  if (string_ends_with(v->out_name, tos3(".c")) ||
      string_ends_with(v->out_name, tos3(".js"))) {

#ifndef _VJS

    if (string_ends_with(v->out_name, tos3(".js"))) {

      string vjs_path = string_add(vexe, tos3("js"));

      if (!os__file_exists(vjs_path)) {

        println(tos3("V.js compiler not found, building..."));

        int ret =
            os__system(_STR("%.*s -o %.*s -os js %.*s/v.v", vexe.len, vexe.str,
                            vjs_path.len, vjs_path.str, vdir.len, vdir.str));

        if (ret == 0) {

          println(tos3("Done."));

        } else {

          println(tos3("Failed."));

          v_exit(1);
        };
      };

      int ret = os__system(_STR("%.*s -o %.*s %.*s", vjs_path.len, vjs_path.str,
                                v->out_name.len, v->out_name.str, v->dir.len,
                                v->dir.str));

      if (ret == 0) {

        printf("Done. Run it with `node %.*s`\n", v->out_name.len,
               v->out_name.str);

        println(tos3("JS backend is at a very early stage."));
      };
    };

#endif
    ;

    os__mv(v->out_name_c, v->out_name);

    v_exit(0);
  };

  if (v->os == compiler__compiler__OS_windows) {

#ifndef _WIN32

    compiler__V_cc_windows_cross(v);

    return;

#endif
    ;
  };

#ifdef _WIN32

  if (string_eq(v->pref->ccompiler, tos3("msvc"))) {

    compiler__V_cc_msvc(v);

    return;
  };

#endif
  ;

  if (v->pref->fast) {

#ifdef __linux__

#ifndef __BIONIC__

    string tcc_3rd = _STR("%.*s/thirdparty/tcc/bin/tcc", vdir.len, vdir.str);

    string tcc_path = tos3("/var/tmp/tcc/bin/tcc");

    if (os__file_exists(tcc_3rd) && !os__file_exists(tcc_path)) {

      os__system(_STR("mv %.*s/thirdparty/tcc /var/tmp/", vdir.len, vdir.str));
    };

    if (string_eq(v->pref->ccompiler, tos3("cc")) &&
        os__file_exists(tcc_path)) {

      v->pref->ccompiler = tcc_path;
    };

#endif
    ;

#else

    compiler__verror(tos3("-fast is only supported on Linux right now"));

#endif
    ;
  };

  compiler__V_log(&/* ? */ *v,
                  _STR("cc() isprod=%d outname=%.*s", v->pref->is_prod,
                       v->out_name.len, v->out_name.str));

  array_string a = new_array_from_c_array(
      3, 3, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 3){v->pref->cflags, tos3("-std=gnu11"),
                                      tos3("-w")});

  if (v->pref->is_so) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-shared -fPIC ")),
          tmp1, string);

    v->out_name = string_add(v->out_name, tos3(".so"));
  };

  if (v->pref->build_mode == compiler__compiler__BuildMode_build_module) {

    string out_dir =
        (string_starts_with(v->dir, tos3("vlib")))
            ? (_STR("%.*s%.*scache%.*s%.*s", compiler__v_modules_path.len,
                    compiler__v_modules_path.str, os__path_separator.len,
                    os__path_separator.str, os__path_separator.len,
                    os__path_separator.str, v->dir.len, v->dir.str))
            : (_STR("%.*s%.*s%.*s", compiler__v_modules_path.len,
                    compiler__v_modules_path.str, os__path_separator.len,
                    os__path_separator.str, v->dir.len, v->dir.str));

    string pdir = string_all_before_last(out_dir, os__path_separator);

    if (!os__dir_exists(pdir)) {

      os__mkdir_all(pdir);
    };

    v->out_name = _STR("%.*s.o", out_dir.len, out_dir.str);

    printf("Building %.*s...\n", v->out_name.len, v->out_name.str);
  };

  bool debug_mode = v->pref->is_debug;

  string debug_options = tos3("-g");

  string optimization_options = tos3("-O2");

  if (string_contains(v->pref->ccompiler, tos3("clang"))) {

    if (debug_mode) {

      debug_options = tos3("-g -O0 -no-pie");
    };

    optimization_options = tos3("-O3 -flto");
  };

  if (string_contains(v->pref->ccompiler, tos3("gcc"))) {

    if (debug_mode) {

      debug_options = tos3("-g3 -no-pie");
    };

    optimization_options = tos3("-O3 -fno-strict-aliasing -flto");
  };

  if (debug_mode) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ debug_options), tmp2,
          string);
  };

  if (v->pref->is_prod) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ optimization_options),
          tmp3, string);
  };

  if (debug_mode && string_ne(os__user_os(), tos3("windows"))) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3(" -rdynamic ")),
          tmp4, string);
  };

  if (string_ne(v->pref->ccompiler, tos3("msvc")) &&
      v->os != compiler__compiler__OS_freebsd) {

    _PUSH(&a,
          (/*typ = array_string   tmp_typ=string*/ tos3(
              "-Werror=implicit-function-declaration")),
          tmp5, string);
  };

  array_string tmp6 =
      compiler__V_generate_hotcode_reloading_compiler_flags(&/* ? */ *v);
  for (int tmp7 = 0; tmp7 < tmp6.len; tmp7++) {
    string f = ((string *)tmp6.data)[tmp7];

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ f), tmp8, string);
  };

  string libs = tos3("");

  if (v->pref->build_mode == compiler__compiler__BuildMode_build_module) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-c")), tmp9,
          string);

  } else if (v->pref->is_cache) {

    string builtin_o_path =
        filepath__join(compiler__v_modules_path,
                       &(varg_string){.len = 3,
                                      .args = {tos3("cache"), tos3("vlib"),
                                               tos3("builtin.o")}});

    _PUSH(&a,
          (/*typ = array_string   tmp_typ=string*/ string_replace(
              builtin_o_path, tos3("builtin.o"), tos3("strconv.o"))),
          tmp10, string);

    if (os__file_exists(builtin_o_path)) {

      libs = builtin_o_path;

    } else {

      printf("%.*s not found... building module builtin\n", builtin_o_path.len,
             builtin_o_path.str);

      os__system(_STR("%.*s build module vlib%.*sbuiltin", vexe.len, vexe.str,
                      os__path_separator.len, os__path_separator.str));
    };

    array_string tmp11 = v->table->imports;
    for (int tmp12 = 0; tmp12 < tmp11.len; tmp12++) {
      string imp = ((string *)tmp11.data)[tmp12];

      if (string_contains(imp, tos3("vweb"))) {

        continue;
      };

      if (string_eq(imp, tos3("webview"))) {

        continue;
      };

      string imp_path = string_replace(imp, tos3("."), os__path_separator);

      string path =
          _STR("%.*s%.*scache%.*svlib%.*s%.*s.o", compiler__v_modules_path.len,
               compiler__v_modules_path.str, os__path_separator.len,
               os__path_separator.str, os__path_separator.len,
               os__path_separator.str, os__path_separator.len,
               os__path_separator.str, imp_path.len, imp_path.str);

      if (os__file_exists(path)) {

        libs = string_add(libs, string_add(tos3(" "), path));

      } else {

        printf("%.*s not found... building module %.*s\n", path.len, path.str,
               imp.len, imp.str);

        if (string_ends_with(path, tos3("vlib/ui.o"))) {

          println(tos3("copying ui..."));

          Option_bool tmp13 =
              os__cp(_STR("%.*s/thirdparty/ui/ui.o", vdir.len, vdir.str), path);
          if (!tmp13.ok) {
            string err = tmp13.error;
            int errcode = tmp13.ecode;

            v_panic(tos3("error copying ui files"));
          };

          Option_bool tmp14 =
              os__cp(_STR("%.*s/thirdparty/ui/ui.vh", vdir.len, vdir.str),
                     string_add(compiler__v_modules_path, tos3("/vlib/ui.vh")));
          if (!tmp14.ok) {
            string err = tmp14.error;
            int errcode = tmp14.ecode;

            v_panic(tos3("error copying ui files"));
          };

        } else {

          os__system(_STR("%.*s build module vlib%.*s%.*s", vexe.len, vexe.str,
                          os__path_separator.len, os__path_separator.str,
                          imp_path.len, imp_path.str));
        };
      };

      if (string_ends_with(path, tos3("vlib/ui.o"))) {

        _PUSH(&a,
              (/*typ = array_string   tmp_typ=string*/ tos3(
                  "-framework Cocoa -framework Carbon")),
              tmp15, string);
      };
    };
  };

  if (v->pref->sanitize) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-fsanitize=leak")),
          tmp16, string);
  };

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-o \"%.*s\"", v->out_name.len, v->out_name.str)),
        tmp17, string);

  if (os__dir_exists(v->out_name)) {

    compiler__verror(
        _STR("\'%.*s\' is a directory", v->out_name.len, v->out_name.str));
  };

  if (v->os == compiler__compiler__OS_mac) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-x objective-c")),
          tmp18, string);
  };

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "\"%.*s\"", v->out_name_c.len, v->out_name_c.str)),
        tmp19, string);

  if (v->os == compiler__compiler__OS_mac) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-x none")), tmp20,
          string);
  };

  if (v->os == compiler__compiler__OS_mac) {

    _PUSH(&a,
          (/*typ = array_string   tmp_typ=string*/ tos3(
              "-mmacosx-version-min=10.7")),
          tmp21, string);
  };

  array_compiler__CFlag cflags = compiler__V_get_os_cflags(&/* ? */ *v);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/
         array_compiler__CFlag_c_options_only_object_files(cflags)),
        tmp22, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/
         array_compiler__CFlag_c_options_without_object_files(cflags)),
        tmp23, string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ libs), tmp24, string);

  if (v->pref->build_mode != compiler__compiler__BuildMode_build_module &&
      (v->os == compiler__compiler__OS_linux ||
       v->os == compiler__compiler__OS_freebsd ||
       v->os == compiler__compiler__OS_openbsd ||
       v->os == compiler__compiler__OS_netbsd ||
       v->os == compiler__compiler__OS_dragonfly ||
       v->os == compiler__compiler__OS_solaris)) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-lm -lpthread ")),
          tmp25, string);

    if (v->os == compiler__compiler__OS_linux) {

      _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3(" -ldl ")), tmp26,
            string);
    };
  };

  if (v->os == compiler__compiler__OS_js &&
      string_eq(os__user_os(), tos3("linux"))) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-lm")), tmp27,
          string);
  };

  string args = array_string_join(a, tos3(" "));

start:;

  compiler__todo();

  string cmd = _STR("%.*s %.*s", v->pref->ccompiler.len, v->pref->ccompiler.str,
                    args.len, args.str);

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    println(tos3("\n=========="));

    println(cmd);
  };

  i64 ticks = time__ticks();

  Option_os__Result tmp28 = os__exec(cmd);
  os__Result res;
  if (!tmp28.ok) {
    string err = tmp28.error;
    int errcode = tmp28.ecode;

    compiler__verror(err);

    return;
  }
  res = *(os__Result *)tmp28.data;
  ;

  if (res.exit_code != 0) {

    if (res.exit_code == 127) {

#ifdef __linux__

      if (string_contains(v->pref->ccompiler, tos3("tcc"))) {

        v->pref->ccompiler = tos3("cc");

        goto start;
      };

#endif
      ;

      compiler__verror(string_add(
          string_add(
              string_add(
                  string_add(
                      string_add(
                          tos3("C compiler error, while attempting to run: \n"),
                          tos3("-----------------------------------------------"
                               "------------\n")),
                      _STR("%.*s\n", cmd.len, cmd.str)),
                  tos3("-------------------------------------------------------"
                       "----\n")),
              tos3("Probably your C compiler is missing. \n")),
          tos3("Please reinstall it, or make it available in your PATH.")));
    };

    if (v->pref->is_debug) {

      println(res.output);

    } else {

      string partial_output =
          string_trim_right(string_limit(res.output, 200), tos3("\r\n"));

      print(partial_output);

      if (res.output.len > partial_output.len) {

        println(tos3("...\n(Use `v -g` to print the entire error message)\n"));

      } else {

        println(tos3(""));
      };
    };

    compiler__verror(
        string_add(tos3("C error. This should never happen. "),
                   tos3("\nPlease create a GitHub issue: "
                        "https://github.com/vlang/v/issues/new/choose")));
  };

  i64 diff = time__ticks() - ticks;

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    printf("%.*s took %lld ms\n", v->pref->ccompiler.len,
           v->pref->ccompiler.str, diff);

    println(tos3("=========\n"));
  };

  if (!v->pref->is_keep_c && string_ne(v->out_name_c, tos3("v.c"))) {

    os__rm(v->out_name_c);
  };

  if (v->pref->compress) {

#ifdef _WIN32

    println(tos3("-compress does not work on Windows for now"));

    return;

#endif
    ;

    int ret = os__system(_STR("strip %.*s", v->out_name.len, v->out_name.str));

    if (ret != 0) {

      println(tos3("strip failed"));

      return;
    };

    int ret2 = os__system(
        _STR("upx --lzma -qqq %.*s", v->out_name.len, v->out_name.str));

    if (ret2 != 0) {

      println(tos3("upx failed"));

#ifdef __APPLE__

      println(tos3("install upx with `brew install upx`"));

#endif
      ;

#ifdef __linux__

      println(string_add(
          tos3("install upx\n"),
          tos3("for example, on Debian/Ubuntu run `sudo apt install upx`")));

#endif
      ;

#ifdef _WIN32

#endif
      ;
    };
  };
}
void compiler__V_cc_windows_cross(compiler__V *c) {

  if (!string_ends_with(c->out_name, tos3(".exe"))) {

    c->out_name = string_add(c->out_name, tos3(".exe"));
  };

  string args = _STR("-o %.*s -w -L. ", c->out_name.len, c->out_name.str);

  array_compiler__CFlag cflags = compiler__V_get_os_cflags(&/* ? */ *c);

  args = string_add(
      args, (string_eq(c->pref->ccompiler, tos3("msvc")))
                ? (array_compiler__CFlag_c_options_before_target_msvc(cflags))
                : (array_compiler__CFlag_c_options_before_target(cflags)));

  string libs = tos3("");

  if (c->pref->build_mode == compiler__compiler__BuildMode_default_mode) {

    libs = _STR("\"%.*s/vlib/builtin.o\"", compiler__v_modules_path.len,
                compiler__v_modules_path.str);

    if (!os__file_exists(libs)) {

      printf("`%.*s` not found\n", libs.len, libs.str);

      v_exit(1);
    };

    array_string tmp29 = c->table->imports;
    for (int tmp30 = 0; tmp30 < tmp29.len; tmp30++) {
      string imp = ((string *)tmp29.data)[tmp30];

      libs = string_add(
          libs, _STR(" \"%.*s/vlib/%.*s.o\"", compiler__v_modules_path.len,
                     compiler__v_modules_path.str, imp.len, imp.str));
    };
  };

  args = string_add(args, _STR(" %.*s ", c->out_name_c.len, c->out_name_c.str));

  args = string_add(
      args, (string_eq(c->pref->ccompiler, tos3("msvc")))
                ? (array_compiler__CFlag_c_options_after_target_msvc(cflags))
                : (array_compiler__CFlag_c_options_after_target(cflags)));

  println(tos3("Cross compiling for Windows..."));

  string winroot = _STR("%.*s/winroot", compiler__v_modules_path.len,
                        compiler__v_modules_path.str);

  if (!os__dir_exists(winroot)) {

    string winroot_url = tos3(
        "https://github.com/vlang/v/releases/download/v0.1.10/winroot.zip");

    printf("\"%.*s\" not found.\n", winroot.len, winroot.str);

    printf("Download it from %.*s and save it in %.*s\n", winroot_url.len,
           winroot_url.str, compiler__v_modules_path.len,
           compiler__v_modules_path.str);

    println(tos3("Unzip it afterwards.\n"));

    println(string_add(
        tos3("winroot.zip contains all library and header files needed "),
        tos3("to cross-compile for Windows.")));

    v_exit(1);
  };

  string obj_name = c->out_name;

  obj_name = string_replace(obj_name, tos3(".exe"), tos3(""));

  obj_name = string_replace(obj_name, tos3(".o.o"), tos3(".o"));

  string include = _STR("-I %.*s/include ", winroot.len, winroot.str);

  string cmd =
      _STR("clang -o %.*s -w %.*s -m32 -c -target x86_64-win32 %.*s/%.*s",
           obj_name.len, obj_name.str, include.len, include.str,
           compiler__v_modules_path.len, compiler__v_modules_path.str,
           c->out_name_c.len, c->out_name_c.str);

  if (c->pref->show_c_cmd) {

    println(cmd);
  };

  if (os__system(cmd) != 0) {

    println(tos3("Cross compilation for Windows failed. Make sure you have "
                 "clang installed."));

    v_exit(1);
  };

  if (c->pref->build_mode != compiler__compiler__BuildMode_build_module) {

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

      println(tos3("Cross compilation for Windows failed. Make sure you have "
                   "lld linker installed."));

      v_exit(1);
    };
  };

  println(tos3("Done!"));
}
void compiler__V_build_thirdparty_obj_files(compiler__V *c) {

  array_compiler__CFlag tmp31 = compiler__V_get_os_cflags(&/* ? */ *c);
  for (int tmp32 = 0; tmp32 < tmp31.len; tmp32++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp31.data)[tmp32];

    if (string_ends_with(flag.value, tos3(".o"))) {

      array_compiler__CFlag rest_of_module_flags =
          compiler__V_get_rest_of_module_cflags(
              &/* ? */ *c,
              &/*112 EXP:"compiler__CFlag*" GOT:"compiler__CFlag" */ flag);

      if (string_eq(c->pref->ccompiler, tos3("msvc"))) {

        compiler__build_thirdparty_obj_file_with_msvc(flag.value,
                                                      rest_of_module_flags);

      } else {

        compiler__build_thirdparty_obj_file(flag.value, rest_of_module_flags);
      };
    };
  };
}
string compiler__find_c_compiler() {

  string args =
      array_string_join(compiler__env_vflags_and_os_args(), tos3(" "));

  string defaultcc = compiler__find_c_compiler_default();

  return compiler__get_arg(args, tos3("cc"), defaultcc);
}
string compiler__find_c_compiler_default() {

#ifdef _WIN32

  return tos3("gcc");

#endif
  ;

  return tos3("cc");
}
string compiler__find_c_compiler_thirdparty_options() {

  array_string fullargs = compiler__env_vflags_and_os_args();

  string cflags = compiler__get_cmdline_cflags(fullargs);

#ifndef _WIN32

  cflags = string_add(cflags, tos3(" -fPIC"));

#endif
  ;

  if ((_IN(string, (tos3("-m32")), fullargs))) {

    cflags = string_add(cflags, tos3(" -m32"));
  };

  return cflags;
}
string compiler__get_cmdline_cflags(array_string args) {

  string cflags = tos3("");

  array_string tmp33 = args;
  for (int ci = 0; ci < tmp33.len; ci++) {
    string cv = ((string *)tmp33.data)[ci];

    if (string_eq(cv, tos3("-cflags"))) {

      cflags = string_add(
          cflags, string_add((*(string *)array_get(args, ci + 1)), tos3(" ")));
    };
  };

  return cflags;
}
string compiler__CFlag_str(compiler__CFlag *c) {

  return _STR(
      "CFlag{ name: \"%.*s\" value: \"%.*s\" mod: \"%.*s\" os: \"%.*s\" }",
      c->name.len, c->name.str, c->value.len, c->value.str, c->mod.len,
      c->mod.str, c->os.len, c->os.str);
}
array_compiler__CFlag compiler__V_get_os_cflags(compiler__V *v) {

  array_compiler__CFlag flags = new_array_from_c_array(
      0, 0, sizeof(compiler__CFlag),
      EMPTY_ARRAY_OF_ELEMS(compiler__CFlag, 0){TCCSKIP(0)});

  array_compiler__CFlag tmp1 = v->table->cflags;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp1.data)[tmp2];

    if (string_eq(flag.os, tos3("")) ||
        (string_eq(flag.os, tos3("linux")) &&
         v->os == compiler__compiler__OS_linux) ||
        (string_eq(flag.os, tos3("darwin")) &&
         v->os == compiler__compiler__OS_mac) ||
        (string_eq(flag.os, tos3("freebsd")) &&
         v->os == compiler__compiler__OS_freebsd) ||
        (string_eq(flag.os, tos3("windows")) &&
         v->os == compiler__compiler__OS_windows)) {

      _PUSH(&flags,
            (/*typ = array_compiler__CFlag   tmp_typ=compiler__CFlag*/ flag),
            tmp3, compiler__CFlag);
    };
  };

  return flags;
}
array_compiler__CFlag
compiler__V_get_rest_of_module_cflags(compiler__V *v, compiler__CFlag *c) {

  array_compiler__CFlag flags = new_array_from_c_array(
      0, 0, sizeof(compiler__CFlag),
      EMPTY_ARRAY_OF_ELEMS(compiler__CFlag, 0){TCCSKIP(0)});

  array_compiler__CFlag cflags = compiler__V_get_os_cflags(&/* ? */ *v);

  array_compiler__CFlag tmp4 = cflags;
  for (int tmp5 = 0; tmp5 < tmp4.len; tmp5++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp4.data)[tmp5];

    if (string_eq(c->mod, flag.mod)) {

      if (string_eq(c->name, flag.name) && string_eq(c->value, flag.value) &&
          string_eq(c->os, flag.os)) {

        continue;
      };

      _PUSH(&flags,
            (/*typ = array_compiler__CFlag   tmp_typ=compiler__CFlag*/ flag),
            tmp6, compiler__CFlag);
    };
  };

  return flags;
}
string compiler__CFlag_format(compiler__CFlag *cf) {

  string value = cf->value;

  if (string_eq(cf->name, tos3("-l")) && value.len > 0) {

    return string_trim_space(
        _STR("%.*s%.*s", cf->name.len, cf->name.str, value.len, value.str));
  };

  if (string_eq(cf->name, tos3("-I")) || string_eq(cf->name, tos3("-L")) ||
      string_ends_with(value, tos3(".o"))) {

    value = string_add(string_add(tos3("\""), os__realpath(value)), tos3("\""));
  };

  return string_trim_space(
      _STR("%.*s %.*s", cf->name.len, cf->name.str, value.len, value.str));
}
bool compiler__Table_has_cflag(compiler__Table *table, compiler__CFlag cflag) {

  array_compiler__CFlag tmp7 = table->cflags;
  for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
    compiler__CFlag cf = ((compiler__CFlag *)tmp7.data)[tmp8];

    if (string_eq(cf.os, cflag.os) && string_eq(cf.name, cflag.name) &&
        string_eq(cf.value, cflag.value)) {

      return 1;
    };
  };

  return 0;
}
Option_bool compiler__Table_parse_cflag(compiler__Table *table, string cflag,
                                        string mod) {

  array_string allowed_flags =
      new_array_from_c_array(5, 5, sizeof(string),
                             EMPTY_ARRAY_OF_ELEMS(string, 5){
                                 tos3("framework"),
                                 tos3("library"),
                                 tos3("I"),
                                 tos3("l"),
                                 tos3("L"),
                             });

  string flag_orig = string_trim_space(cflag);

  string flag = flag_orig;

  if (string_eq(flag, tos3(""))) {

    bool tmp9 = OPTION_CAST(bool)(1);
    return opt_ok(&tmp9, sizeof(bool));
  };

  string fos = tos3("");

  string name = tos3("");

  if (string_starts_with(flag, tos3("linux")) ||
      string_starts_with(flag, tos3("darwin")) ||
      string_starts_with(flag, tos3("freebsd")) ||
      string_starts_with(flag, tos3("windows"))) {

    int pos = string_index(flag, tos3(" "));

    fos = string_trim_space(string_substr2(flag, 0, pos, false));

    flag = string_trim_space(string_substr2(flag, pos, -1, true));
  };

  while (1) {

    int index = -1;

    string value = tos3("");

    if (string_at(flag, 0) == '-') {

      array_string tmp16 = allowed_flags;
      for (int tmp17 = 0; tmp17 < tmp16.len; tmp17++) {
        string f = ((string *)tmp16.data)[tmp17];

        int i = 1 + f.len;

        if (i <= flag.len && string_eq(f, string_substr2(flag, 1, i, false))) {

          name = string_trim_space(string_substr2(flag, 0, i, false));

          flag = string_trim_space(string_substr2(flag, i, -1, true));

          break;
        };
      };
    };

    array_int tmp24 = new_array_from_c_array(
        2, 2, sizeof(int),
        EMPTY_ARRAY_OF_ELEMS(int, 2){string_index(flag, tos3(" ")),
                                     string_index(flag, tos3(","))});
    for (int tmp25 = 0; tmp25 < tmp24.len; tmp25++) {
      int i = ((int *)tmp24.data)[tmp25];

      if (index == -1 || (i != -1 && i < index)) {

        index = i;
      };
    };

    if (index != -1 && string_at(flag, index) == ' ' &&
        string_at(flag, index + 1) == '-') {

      array_string tmp30 = allowed_flags;
      for (int tmp31 = 0; tmp31 < tmp30.len; tmp31++) {
        string f = ((string *)tmp30.data)[tmp31];

        int i = index + f.len;

        if (i < flag.len &&
            string_eq(f, string_substr2(flag, index, i, false))) {

          index = i;

          break;
        };
      };

      value = string_trim_space(string_substr2(flag, 0, index, false));

      flag = string_trim_space(string_substr2(flag, index, -1, true));

    } else if (index != -1 && index < flag.len - 2 &&
               string_at(flag, index) == ',') {

      value = string_trim_space(string_substr2(flag, 0, index, false));

      flag = string_trim_space(string_substr2(flag, index + 1, -1, true));

    } else {

      value = string_trim_space(flag);

      index = -1;
    };

    if ((string_eq(name, tos3("-I")) || string_eq(name, tos3("-l")) ||
         string_eq(name, tos3("-L"))) &&
        string_eq(value, tos3(""))) {

      string hint = (string_eq(name, tos3("-l"))) ? (tos3("library name"))
                                                  : (tos3("path"));

      return v_error(_STR("bad #flag `%.*s`: missing %.*s after `%.*s`",
                          flag_orig.len, flag_orig.str, hint.len, hint.str,
                          name.len, name.str));
    };

    compiler__CFlag cf =
        (compiler__CFlag){.mod = mod, .os = fos, .name = name, .value = value};

    if (!compiler__Table_has_cflag(&/* ? */ *table, cf)) {

      _PUSH(&table->cflags,
            (/*typ = array_compiler__CFlag   tmp_typ=compiler__CFlag*/ cf),
            tmp44, compiler__CFlag);
    };

    if (index == -1) {

      break;
    };
  };

  bool tmp45 = OPTION_CAST(bool)(1);
  return opt_ok(&tmp45, sizeof(bool));
}
string array_compiler__CFlag_c_options_before_target_msvc(
    array_compiler__CFlag cflags) {

  return tos3("");
}
string array_compiler__CFlag_c_options_after_target_msvc(
    array_compiler__CFlag cflags) {

  return tos3("");
}
string
array_compiler__CFlag_c_options_before_target(array_compiler__CFlag cflags) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__CFlag tmp46 = cflags;
  for (int tmp47 = 0; tmp47 < tmp46.len; tmp47++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp46.data)[tmp47];

    if (string_ne(flag.name, tos3("-l"))) {

      _PUSH(&args,
            (/*typ = array_string   tmp_typ=string*/ compiler__CFlag_format(
                &/* ? */ flag)),
            tmp48, string);
    };
  };

  return array_string_join(args, tos3(" "));
}
string
array_compiler__CFlag_c_options_after_target(array_compiler__CFlag cflags) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__CFlag tmp49 = cflags;
  for (int tmp50 = 0; tmp50 < tmp49.len; tmp50++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp49.data)[tmp50];

    if (string_eq(flag.name, tos3("-l"))) {

      _PUSH(&args,
            (/*typ = array_string   tmp_typ=string*/ compiler__CFlag_format(
                &/* ? */ flag)),
            tmp51, string);
    };
  };

  return array_string_join(args, tos3(" "));
}
string array_compiler__CFlag_c_options_without_object_files(
    array_compiler__CFlag cflags) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__CFlag tmp52 = cflags;
  for (int tmp53 = 0; tmp53 < tmp52.len; tmp53++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp52.data)[tmp53];

    if (string_ends_with(flag.value, tos3(".o")) ||
        string_ends_with(flag.value, tos3(".obj"))) {

      continue;
    };

    _PUSH(&args,
          (/*typ = array_string   tmp_typ=string*/ compiler__CFlag_format(
              &/* ? */ flag)),
          tmp54, string);
  };

  return array_string_join(args, tos3(" "));
}
string array_compiler__CFlag_c_options_only_object_files(
    array_compiler__CFlag cflags) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__CFlag tmp55 = cflags;
  for (int tmp56 = 0; tmp56 < tmp55.len; tmp56++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp55.data)[tmp56];

    if (string_ends_with(flag.value, tos3(".o")) ||
        string_ends_with(flag.value, tos3(".obj"))) {

      _PUSH(&args,
            (/*typ = array_string   tmp_typ=string*/ compiler__CFlag_format(
                &/* ? */ flag)),
            tmp57, string);
    };
  };

  return array_string_join(args, tos3(" "));
}
compiler__CGen *compiler__new_cgen(string out_name_c) {

  string path = out_name_c;

  Option_os__File tmp1 = os__create(path);
  os__File out;
  if (!tmp1.ok) {
    string err = tmp1.error;
    int errcode = tmp1.ecode;

    printf("failed to create %.*s\n", path.len, path.str);

    return (compiler__CGen *)memdup(
        &(compiler__CGen){.out_path = tos3(""),
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
                          .prev_tmps = new_array(0, 1, sizeof(string)),
                          .tmp_line = tos3(""),
                          .cur_line = tos3(""),
                          .prev_line = tos3(""),
                          .is_tmp = 0,
                          .fn_main = tos3(""),
                          .stash = tos3(""),
                          .file = tos3(""),
                          .line = 0,
                          .line_directives = 0,
                          .cut_pos = 0},
        sizeof(compiler__CGen));
  }
  out = *(os__File *)tmp1.data;
  ;

  compiler__CGen *gen = (compiler__CGen *)memdup(
      &(compiler__CGen){.out_path = path,
                        .out = out,
                        .lines = make(0, 1000, sizeof(string)),
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
                        .prev_tmps = new_array(0, 1, sizeof(string)),
                        .tmp_line = tos3(""),
                        .cur_line = tos3(""),
                        .prev_line = tos3(""),
                        .is_tmp = 0,
                        .fn_main = tos3(""),
                        .stash = tos3(""),
                        .file = tos3(""),
                        .line = 0,
                        .line_directives = 0,
                        .cut_pos = 0},
      sizeof(compiler__CGen));

  return gen;
}
void compiler__CGen_genln(compiler__CGen *g, string s) {

  if (g->nogen || g->pass != compiler__compiler__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    g->tmp_line =
        _STR("%.*s %.*s\n", g->tmp_line.len, g->tmp_line.str, s.len, s.str);

    return;
  };

  g->cur_line =
      _STR("%.*s %.*s", g->cur_line.len, g->cur_line.str, s.len, s.str);

  if (string_ne(g->cur_line, tos3(""))) {

    if (g->line_directives &&
        string_ne(string_trim_space(g->cur_line), tos3(""))) {

      if (g->file.len > 0 && g->line > 0) {

        _PUSH(&g->lines,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "\n#line %d \"%.*s\"", g->line, g->file.len, g->file.str)),
              tmp2, string);
      };
    };

    _PUSH(&g->lines, (/*typ = array_string   tmp_typ=string*/ g->cur_line),
          tmp3, string);

    g->prev_line = g->cur_line;

    g->cur_line = tos3("");
  };
}
void compiler__CGen_gen(compiler__CGen *g, string s) {

  if (g->nogen || g->pass != compiler__compiler__Pass_main) {

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
void compiler__CGen_resetln(compiler__CGen *g, string s) {

  if (g->nogen || g->pass != compiler__compiler__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    g->tmp_line = s;

  } else {

    g->cur_line = s;
  };
}
void compiler__CGen_save(compiler__CGen *g) {

  string s = array_string_join(g->lines, tos3("\n"));

  os__File_writeln(g->out, s);

  os__File_close(g->out);
}
void compiler__CGen_start_tmp(compiler__CGen *g) {

  if (g->is_tmp) {

    _PUSH(&g->prev_tmps, (/*typ = array_string   tmp_typ=string*/ g->tmp_line),
          tmp4, string);
  };

  g->tmp_line = tos3("");

  g->is_tmp = 1;
}
string compiler__CGen_end_tmp(compiler__CGen *g) {

  string res = g->tmp_line;

  if (g->prev_tmps.len > 0) {

    g->tmp_line = *(string *)array_last(g->prev_tmps);

    g->prev_tmps = array_slice2(g->prev_tmps, 0, g->prev_tmps.len - 1, false);

  } else {

    g->tmp_line = tos3("");

    g->is_tmp = 0;
  };

  return res;
}
int compiler__CGen_add_placeholder(compiler__CGen *g) {

  if (g->is_tmp) {

    return g->tmp_line.len;
  };

  return g->cur_line.len;
}
void compiler__CGen_start_cut(compiler__CGen *g) {

  g->cut_pos = compiler__CGen_add_placeholder(&/* ? */ *g);
}
string compiler__CGen_cut(compiler__CGen *g) {

  int pos = g->cut_pos;

  g->cut_pos = 0;

  if (g->is_tmp) {

    string res = string_substr2(g->tmp_line, pos, -1, true);

    g->tmp_line = string_substr2(g->tmp_line, 0, pos, false);

    return res;
  };

  string res = string_substr2(g->cur_line, pos, -1, true);

  g->cur_line = string_substr2(g->cur_line, 0, pos, false);

  return res;
}
void compiler__CGen_set_placeholder(compiler__CGen *g, int pos, string val) {

  if (g->nogen || g->pass != compiler__compiler__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    string left = string_substr2(g->tmp_line, 0, pos, false);

    string right = string_substr2(g->tmp_line, pos, -1, true);

    g->tmp_line = _STR("%.*s%.*s%.*s", left.len, left.str, val.len, val.str,
                       right.len, right.str);

    return;
  };

  string left = string_substr2(g->cur_line, 0, pos, false);

  string right = string_substr2(g->cur_line, pos, -1, true);

  g->cur_line = _STR("%.*s%.*s%.*s", left.len, left.str, val.len, val.str,
                     right.len, right.str);
}
void compiler__CGen_insert_before(compiler__CGen *g, string val) {

  if (g->nogen) {

    return;
  };

  string prev = (*(string *)array_get(g->lines, g->lines.len - 1));

  array_set(&/*q*/ g->lines, g->lines.len - 1,
            &(string[]){
                _STR("%.*s \n %.*s \n", prev.len, prev.str, val.len, val.str)});
}
void compiler__CGen_register_thread_fn(compiler__CGen *g, string wrapper_name,
                                       string wrapper_text,
                                       string struct_text) {

  array_string tmp25 = g->thread_args;
  for (int tmp26 = 0; tmp26 < tmp25.len; tmp26++) {
    string arg = ((string *)tmp25.data)[tmp26];

    if (string_contains(arg, wrapper_name)) {

      return;
    };
  };

  _PUSH(&g->thread_args, (/*typ = array_string   tmp_typ=string*/ struct_text),
        tmp27, string);

  _PUSH(&g->thread_args, (/*typ = array_string   tmp_typ=string*/ wrapper_text),
        tmp28, string);
}
string compiler__V_prof_counters(compiler__V *v) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  return array_string_join(res, tos3(";\n"));
}
string compiler__Parser_print_prof_counters(compiler__Parser *p) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  return array_string_join(res, tos3(";\n"));
}
void compiler__Parser_gen_typedef(compiler__Parser *p, string s) {

  if (!compiler__Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->typedefs, (/*typ = array_string   tmp_typ=string*/ s), tmp29,
        string);
}
void compiler__Parser_gen_type_alias(compiler__Parser *p, string s) {

  if (!compiler__Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->type_aliases, (/*typ = array_string   tmp_typ=string*/ s),
        tmp30, string);
}
void compiler__CGen_add_to_main(compiler__CGen *g, string s) {

  g->fn_main = string_add(g->fn_main, s);
}
void compiler__build_thirdparty_obj_file(string path,
                                         array_compiler__CFlag moduleflags) {

  string obj_path = os__realpath(path);

  if (os__file_exists(obj_path)) {

    return;
  };

  printf("%.*s not found, building it...\n", obj_path.len, obj_path.str);

  string parent = os__dir(obj_path);

  Option_array_string tmp31 = os__ls(parent);
  array_string files;
  if (!tmp31.ok) {
    string err = tmp31.error;
    int errcode = tmp31.ecode;

    v_panic(err);
  }
  files = *(array_string *)tmp31.data;
  ;

  string cfiles = tos3("");

  array_string tmp32 = files;
  for (int tmp33 = 0; tmp33 < tmp32.len; tmp33++) {
    string file = ((string *)tmp32.data)[tmp33];

    if (string_ends_with(file, tos3(".c"))) {

      cfiles = string_add(
          cfiles,
          string_add(
              string_add(tos3("\""),
                         os__realpath(string_add(
                             string_add(parent, os__path_separator), file))),
              tos3("\" ")));
    };
  };

  string cc = compiler__find_c_compiler();

  string cc_thirdparty_options = compiler__find_c_compiler_thirdparty_options();

  string btarget = array_compiler__CFlag_c_options_before_target(moduleflags);

  string atarget = array_compiler__CFlag_c_options_after_target(moduleflags);

  string cmd = _STR("%.*s %.*s %.*s -c -o \"%.*s\" %.*s %.*s ", cc.len, cc.str,
                    cc_thirdparty_options.len, cc_thirdparty_options.str,
                    btarget.len, btarget.str, obj_path.len, obj_path.str,
                    cfiles.len, cfiles.str, atarget.len, atarget.str);

  Option_os__Result tmp34 = os__exec(cmd);
  os__Result res;
  if (!tmp34.ok) {
    string err = tmp34.error;
    int errcode = tmp34.ecode;

    printf("failed thirdparty object build cmd: %.*s\n", cmd.len, cmd.str);

    compiler__verror(err);

    return;
  }
  res = *(os__Result *)tmp34.data;
  ;

  if (res.exit_code != 0) {

    printf("failed thirdparty object build cmd: %.*s\n", cmd.len, cmd.str);

    compiler__verror(res.output);

    return;
  };

  println(res.output);
}
string compiler__os_name_to_ifdef(string name) {

  string tmp35 = name;

  if (string_eq(tmp35, tos3("windows"))) {

    return tos3("_WIN32");

  } else if (string_eq(tmp35, tos3("mac"))) {

    return tos3("__APPLE__");

  } else if (string_eq(tmp35, tos3("linux"))) {

    return tos3("__linux__");

  } else if (string_eq(tmp35, tos3("freebsd"))) {

    return tos3("__FreeBSD__");

  } else if (string_eq(tmp35, tos3("openbsd"))) {

    return tos3("__OpenBSD__");

  } else if (string_eq(tmp35, tos3("netbsd"))) {

    return tos3("__NetBSD__");

  } else if (string_eq(tmp35, tos3("dragonfly"))) {

    return tos3("__DragonFly__");

  } else if (string_eq(tmp35, tos3("msvc"))) {

    return tos3("_MSC_VER");

  } else if (string_eq(tmp35, tos3("android"))) {

    return tos3("__BIONIC__");

  } else if (string_eq(tmp35, tos3("js"))) {

    return tos3("_VJS");

  } else if (string_eq(tmp35, tos3("solaris"))) {

    return tos3("__sun");
  };

  compiler__verror(_STR("bad os ifdef name \"%.*s\"", name.len, name.str));

  return tos3("");
}
string compiler__platform_postfix_to_ifdefguard(string name) {

  string tmp36 = name;

  string s =
      ((string_eq(tmp36, tos3(".v")))
           ? (tos3(""))
           : (((string_eq(tmp36, tos3("_win.v"))) ||
               (string_eq(tmp36, tos3("_windows.v"))))
                  ? (tos3("#ifdef _WIN32"))
                  : ((string_eq(tmp36, tos3("_nix.v")))
                         ? (tos3("#ifndef _WIN32"))
                         : (((string_eq(tmp36, tos3("_lin.v"))) ||
                             (string_eq(tmp36, tos3("_linux.v"))))
                                ? (tos3("#ifdef __linux__"))
                                : (((string_eq(tmp36, tos3("_mac.v"))) ||
                                    (string_eq(tmp36, tos3("_darwin.v"))))
                                       ? (tos3("#ifdef __APPLE__"))
                                       : ((string_eq(tmp36, tos3("_solaris.v")))
                                              ? (tos3("#ifdef __sun"))
                                              : (tos3(""))))))));

  if (string_eq(s, tos3(""))) {

    compiler__verror(_STR("bad platform_postfix \"%.*s\"", name.len, name.str));
  };

  return s;
}
string compiler__V_type_definitions(compiler__V *v) {

  array_compiler__Type types = new_array_from_c_array(
      0, 0, sizeof(compiler__Type),
      EMPTY_ARRAY_OF_ELEMS(compiler__Type, 0){TCCSKIP(0)});

  array_compiler__Type builtin_types = new_array_from_c_array(
      0, 0, sizeof(compiler__Type),
      EMPTY_ARRAY_OF_ELEMS(compiler__Type, 0){TCCSKIP(0)});

  array_string builtins = new_array_from_c_array(
      4, 4, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 4){tos3("string"), tos3("array"),
                                      tos3("map"), tos3("Option")});

  array_string tmp37 = builtins;
  for (int tmp38 = 0; tmp38 < tmp37.len; tmp38++) {
    string builtin = ((string *)tmp37.data)[tmp38];

    compiler__Type tmp39 = {0};
    bool tmp40 = map_get(/*cgen.v : 330*/ v->table->typesmap, builtin, &tmp39);

    compiler__Type typ = tmp39;

    _PUSH(&builtin_types,
          (/*typ = array_compiler__Type   tmp_typ=compiler__Type*/ typ), tmp41,
          compiler__Type);
  };

  map_compiler__Type tmp42 = v->table->typesmap;
  array_string keys_tmp42 = map_keys(&tmp42);
  for (int l = 0; l < keys_tmp42.len; l++) {
    string t_name = ((string *)keys_tmp42.data)[l];
    compiler__Type t = {0};
    map_get(tmp42, t_name, &t);

    if ((_IN(string, (t_name), builtins))) {

      continue;
    };

    _PUSH(&types, (/*typ = array_compiler__Type   tmp_typ=compiler__Type*/ t),
          tmp43, compiler__Type);
  };

  array_compiler__Type types_sorted = compiler__sort_structs(types);

  string res =
      string_add(string_add(compiler__types_to_c(builtin_types, v->table),
                            tos3("\n//----\n")),
                 compiler__types_to_c(types_sorted, v->table));

  return res;
}
array_compiler__Type compiler__sort_structs(array_compiler__Type types) {

  compiler__DepGraph *dep_graph = compiler__new_dep_graph();

  array_string type_names = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__Type tmp44 = types;
  for (int tmp45 = 0; tmp45 < tmp44.len; tmp45++) {
    compiler__Type t = ((compiler__Type *)tmp44.data)[tmp45];

    _PUSH(&type_names, (/*typ = array_string   tmp_typ=string*/ t.name), tmp46,
          string);
  };

  array_compiler__Type tmp47 = types;
  for (int tmp48 = 0; tmp48 < tmp47.len; tmp48++) {
    compiler__Type t = ((compiler__Type *)tmp47.data)[tmp48];

    array_string field_deps = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    array_compiler__Var tmp49 = t.fields;
    for (int tmp50 = 0; tmp50 < tmp49.len; tmp50++) {
      compiler__Var field = ((compiler__Var *)tmp49.data)[tmp50];

      if (!((_IN(string, (field.typ), type_names))) ||
          (_IN(string, (field.typ), field_deps))) {

        continue;
      };

      _PUSH(&field_deps, (/*typ = array_string   tmp_typ=string*/ field.typ),
            tmp51, string);
    };

    compiler__DepGraph_add(dep_graph, t.name, field_deps);
  };

  compiler__DepGraph *dep_graph_sorted =
      compiler__DepGraph_resolve(&/* ? */ *dep_graph);

  if (!dep_graph_sorted->acyclic) {

    compiler__verror(string_add(
        string_add(
            string_add(
                tos3("cgen.sort_structs(): the following structs form a "
                     "dependency cycle:\n"),
                compiler__DepGraph_display_cycles(&/* ? */ *dep_graph_sorted)),
            tos3("\nyou can solve this by making one or both of the dependant "
                 "struct fields references, eg: field &MyStruct")),
        tos3("\nif you feel this is an error, please create a new issue here: "
             "https://github.com/vlang/v/issues and tag @joe-conigliaro")));
  };

  array_compiler__Type types_sorted = new_array_from_c_array(
      0, 0, sizeof(compiler__Type),
      EMPTY_ARRAY_OF_ELEMS(compiler__Type, 0){TCCSKIP(0)});

  array_compiler__DepGraphNode tmp52 = dep_graph_sorted->nodes;
  for (int tmp53 = 0; tmp53 < tmp52.len; tmp53++) {
    compiler__DepGraphNode node = ((compiler__DepGraphNode *)tmp52.data)[tmp53];

    array_compiler__Type tmp54 = types;
    for (int tmp55 = 0; tmp55 < tmp54.len; tmp55++) {
      compiler__Type t = ((compiler__Type *)tmp54.data)[tmp55];

      if (string_eq(t.name, node.name)) {

        _PUSH(&types_sorted,
              (/*typ = array_compiler__Type   tmp_typ=compiler__Type*/ t),
              tmp56, compiler__Type);

        continue;
      };
    };
  };

  return types_sorted;
}
void compiler__Parser_error(compiler__Parser *p, string s) {

  compiler__Parser_error_with_token_index(p, s, p->token_idx - 1);
}
void compiler__Parser_warn(compiler__Parser *p, string s) {

  compiler__Parser_warn_with_token_index(p, s, p->token_idx - 1);
}
void compiler__Parser_production_error_with_token_index(compiler__Parser *p,
                                                        string e,
                                                        int tokenindex) {

  if (p->pref->is_prod) {

    compiler__Parser_error_with_token_index(p, e, tokenindex);

  } else {

    compiler__Parser_warn_with_token_index(p, e, tokenindex);
  };
}
void compiler__Parser_error_with_token_index(compiler__Parser *p, string s,
                                             int tokenindex) {

  compiler__Parser_error_with_position(
      p, s,
      compiler__Scanner_get_scanner_pos_of_token(
          p->scanner, &/*112 EXP:"compiler__Token*" GOT:"compiler__Token" */ (*(
                          compiler__Token *)array_get(p->tokens, tokenindex))));
}
void compiler__Parser_warn_with_token_index(compiler__Parser *p, string s,
                                            int tokenindex) {

  compiler__Parser_warn_with_position(
      p, s,
      compiler__Scanner_get_scanner_pos_of_token(
          p->scanner, &/*112 EXP:"compiler__Token*" GOT:"compiler__Token" */ (*(
                          compiler__Token *)array_get(p->tokens, tokenindex))));
}
void compiler__Parser_error_with_position(compiler__Parser *p, string s,
                                          compiler__ScannerPos sp) {

  compiler__Parser_print_error_context(p);

  string e = compiler__normalized_error(s);

  compiler__Scanner_goto_scanner_position(p->scanner, sp);

  compiler__Scanner_error_with_col(&/* ? */ *p->scanner, e,
                                   sp.pos - sp.last_nl_pos);
}
void compiler__Parser_warn_with_position(compiler__Parser *p, string s,
                                         compiler__ScannerPos sp) {

  compiler__ScannerPos cpos =
      compiler__Scanner_get_scanner_pos(&/* ? */ *p->scanner);

  string e = compiler__normalized_error(s);

  compiler__Scanner_goto_scanner_position(p->scanner, sp);

  compiler__Scanner_warn_with_col(&/* ? */ *p->scanner, e,
                                  sp.pos - sp.last_nl_pos);

  compiler__Scanner_goto_scanner_position(p->scanner, cpos);
}
void compiler__Scanner_error(compiler__Scanner *s, string msg) {

  compiler__Scanner_error_with_col(&/* ? */ *s, msg, 0);
}
void compiler__Scanner_warn(compiler__Scanner *s, string msg) {

  compiler__Scanner_warn_with_col(&/* ? */ *s, msg, 0);
}
void compiler__Scanner_warn_with_col(compiler__Scanner *s, string msg,
                                     int col) {

  string fullpath = compiler__Scanner_get_error_filepath(&/* ? */ *s);

  bool color_on = compiler__Scanner_is_color_output_on(&/* ? */ *s);

  string final_message =
      (color_on) ? (term__bold(term__bright_blue(msg))) : (msg);

  eprintln(_STR("warning: %.*s:%d:%d: %.*s", fullpath.len, fullpath.str,
                s->line_nr + 1, col, final_message.len, final_message.str));
}
void compiler__Scanner_error_with_col(compiler__Scanner *s, string msg,
                                      int col) {

  string fullpath = compiler__Scanner_get_error_filepath(&/* ? */ *s);

  bool color_on = compiler__Scanner_is_color_output_on(&/* ? */ *s);

  string final_message = (color_on) ? (term__red(term__bold(msg))) : (msg);

  eprintln(_STR("%.*s:%d:%d: %.*s", fullpath.len, fullpath.str, s->line_nr + 1,
                col, final_message.len, final_message.str));

  if (s->should_print_line_on_error && s->nlines > 0) {

    int context_start_line =
        compiler__imax(0, (s->line_nr - compiler__error_context_before));

    int context_end_line = compiler__imin(
        s->nlines - 1, (s->line_nr + compiler__error_context_after + 1));

    for (int cline = context_start_line; cline < context_end_line; cline++) {

      string line = string_add(_STR("%5d| ", (cline + 1)),
                               compiler__Scanner_line(*s, cline));

      string coloredline =
          (cline == s->line_nr && color_on) ? (term__red(line)) : (line);

      eprintln(coloredline);

      if (cline != s->line_nr) {

        continue;
      };

      array_string pointerline = new_array_from_c_array(
          0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

      string tmp5 = line;
      array_byte bytes_tmp5 = string_bytes(tmp5);
      ;
      for (int i = 0; i < tmp5.len; i++) {
        byte c = ((byte *)bytes_tmp5.data)[i];

        if (i < col) {

          byte x = (byte_is_space(c)) ? (c) : (' ');

          _PUSH(&pointerline,
                (/*typ = array_string   tmp_typ=string*/ byte_str(x)), tmp6,
                string);

          continue;
        };

        _PUSH(&pointerline,
              (/*typ = array_string   tmp_typ=string*/ (color_on)
                   ? (term__bold(term__blue(tos3("^"))))
                   : (tos3("^"))),
              tmp7, string);

        break;
      };

      eprintln(
          string_add(tos3("      "), array_string_join(pointerline, tos3(""))));
    };
  };

  v_exit(1);
}
static inline int compiler__Parser_cur_tok_index(compiler__Parser *p) {

  return p->token_idx - 1;
}
static inline int compiler__imax(int a, int b) { return (a > b) ? (a) : (b); }
static inline int compiler__imin(int a, int b) { return (a < b) ? (a) : (b); }
string compiler__Scanner_get_error_filepath(compiler__Scanner *s) {

  string verror_paths_override = os__getenv(tos3("VERROR_PATHS"));

  string tmp8 = verror_paths_override;

  bool use_relative_paths =
      ((string_eq(tmp8, tos3("relative")))
           ? (1)
           : ((string_eq(tmp8, tos3("absolute")))
                  ? (0)
                  : (s->should_print_relative_paths_on_error)));

  if (use_relative_paths) {

    string workdir = string_add(os__getwd(), os__path_separator);

    if (string_starts_with(s->file_path, workdir)) {

      return string_replace(s->file_path, workdir, tos3(""));
    };

    return s->file_path;
  };

  return os__realpath(s->file_path);
}
bool compiler__Scanner_is_color_output_on(compiler__Scanner *s) {

  return s->should_print_errors_in_color && term__can_show_color_on_stderr();
}
void compiler__Parser_print_error_context(compiler__Parser *p) {

  if (p->pref->is_debug) {

    os__write_file(tos3("fns.txt"),
                   compiler__Table_debug_fns(&/* ? */ *p->table));
  };

  if (p->pref->is_verbose || p->pref->is_debug) {

    printf("pass=%d fn=`%.*s`\n\n", p->pass, p->cur_fn.name.len,
           p->cur_fn.name.str);
  };

  compiler__CGen_save(p->cgen);

  string cur_path = os__getwd();

  if (!p->pref->is_repl && !p->pref->is_test &&
      (string_contains(p->file_path, tos3("v/compiler")) ||
       string_contains(cur_path, tos3("v/compiler")))) {

    println(tos3("\n========================="));

    println(tos3("It looks like you are building V. It is being frequently "
                 "updated every day."));

    println(tos3("If you didn\'t modify V\'s code, most likely there was a "
                 "change that "));

    println(tos3("lead to this error."));

    println(tos3("\nRun `v up`, that will most likely fix it."));

    println(tos3("\nIf this doesn\'t help, please create a GitHub issue."));

    println(tos3("=========================\n"));
  };

  if (p->pref->is_debug) {

    print_backtrace();
  };
}
string compiler__normalized_error(string s) {

  return string_replace(
      string_replace(
          string_replace(string_replace(s, tos3("array_"), tos3("[]")),
                         tos3("__"), tos3(".")),
          tos3("Option_"), tos3("?")),
      tos3("main."), tos3(""));
}
string compiler__ScannerPos_str(compiler__ScannerPos s) {

  return _STR("ScannerPos{ %5d , %5d , %5d }", s.pos, s.line_nr, s.last_nl_pos);
}
compiler__ScannerPos compiler__Scanner_get_scanner_pos(compiler__Scanner *s) {

  return (compiler__ScannerPos){
      .pos = s->pos, .line_nr = s->line_nr, .last_nl_pos = s->last_nl_pos};
}
void compiler__Scanner_goto_scanner_position(compiler__Scanner *s,
                                             compiler__ScannerPos scp) {

  s->pos = scp.pos;

  s->line_nr = scp.line_nr;

  s->last_nl_pos = scp.last_nl_pos;
}
compiler__ScannerPos
compiler__Scanner_get_scanner_pos_of_token(compiler__Scanner *s,
                                           compiler__Token *t) {

  int tline = t->line_nr;

  int tcol = (t->line_nr == 0) ? (t->col + 1) : (t->col - 1);

  compiler__ScannerPos cpos = compiler__Scanner_get_scanner_pos(&/* ? */ *s);

  compiler__ScannerPos sptoken =
      (compiler__ScannerPos){.pos = 0, .line_nr = 0, .last_nl_pos = 0};

  compiler__Scanner_goto_scanner_position(
      s, (compiler__ScannerPos){.pos = 0, .line_nr = 0, .last_nl_pos = 0});

  int prevlinepos = 0;

  int ate = 0;

  ate++;

  int maxline =
      compiler__imin(s->nlines, tline + 2 * compiler__error_context_after);

  while (1) {

    prevlinepos = s->pos;

    if (s->pos >= s->text.len) {

      break;
    };

    if (s->line_nr > maxline) {

      break;
    };

    if (tline == s->line_nr) {

      sptoken = compiler__Scanner_get_scanner_pos(&/* ? */ *s);

      sptoken.pos += tcol;
    };

    compiler__Scanner_ignore_line(s);

    compiler__Scanner_eat_single_newline(s);
  };

  compiler__Scanner_goto_scanner_position(s, cpos);

  return sptoken;
}
void compiler__Scanner_eat_single_newline(compiler__Scanner *s) {

  if (s->pos >= s->text.len) {

    return;
  };

  if (compiler__Scanner_expect(&/* ? */ *s, tos3("\r\n"), s->pos)) {

    s->pos += 2;

    return;
  };

  if (string_at(s->text, s->pos) == '\n') {

    s->pos++;

    return;
  };

  if (string_at(s->text, s->pos) == '\r') {

    s->pos++;

    return;
  };
}
void compiler__Parser_comp_time(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_dollar);

  if (p->tok == compiler__compiler__TokenKind_key_if) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_if);

    ;

    bool not = p->tok == compiler__compiler__TokenKind_not;

    if (not) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_not);
    };

    string name = compiler__Parser_check_name(p);

    ;

    if ((_IN(string, (name), compiler__supported_platforms))) {

      string ifdef_name = compiler__os_name_to_ifdef(name);

      if (not) {

        compiler__Parser_genln(
            p, _STR("#ifndef %.*s", ifdef_name.len, ifdef_name.str));

      } else {

        compiler__Parser_genln(
            p, _STR("#ifdef %.*s", ifdef_name.len, ifdef_name.str));
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

      compiler__OS os = compiler__os_from_string(name);

      if (0 && compiler__Parser_fileis(&/* ? */ *p, tos3("runtime.v")) &&
          os != p->os) {

        int stack = 1;

        while (1) {

          if (p->tok == compiler__compiler__TokenKind_lcbr) {

            stack++;

          } else if (p->tok == compiler__compiler__TokenKind_rcbr) {

            stack--;
          };

          if (p->tok == compiler__compiler__TokenKind_eof) {

            break;
          };

          if (stack <= 0 && p->tok == compiler__compiler__TokenKind_rcbr) {

            compiler__Parser_next(p);

            break;
          };

          compiler__Parser_next(p);
        };

      } else {

        compiler__Parser_statements_no_rcbr(p);
      };

      if (!(p->tok == compiler__compiler__TokenKind_dollar &&
            compiler__Parser_peek(&/* ? */ *p) ==
                compiler__compiler__TokenKind_key_else)) {

        compiler__Parser_genln(p, tos3("#endif"));
      };

    } else if (string_eq(name, tos3("debug"))) {

      compiler__Parser_genln(p, tos3("#ifdef VDEBUG"));

      compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

      compiler__Parser_statements_no_rcbr(p);

      compiler__Parser_genln(p, tos3("#endif"));

    } else if (string_eq(name, tos3("tinyc"))) {

      compiler__Parser_comptime_if_block(p, tos3("__TINYC__"));

    } else if (string_eq(name, tos3("glibc"))) {

      compiler__Parser_comptime_if_block(p, tos3("__GLIBC__"));

    } else if (string_eq(name, tos3("mingw"))) {

      compiler__Parser_comptime_if_block(p, tos3("__MINGW32__"));

    } else if (string_eq(name, tos3("msvc"))) {

      compiler__Parser_comptime_if_block(p, tos3("__MSC_VER__"));

    } else if (string_eq(name, tos3("clang"))) {

      compiler__Parser_comptime_if_block(p, tos3("__clang__"));

    } else {

      println(tos3("Supported platforms:"));

      println(array_string_str(compiler__supported_platforms));

      compiler__Parser_error(
          p, _STR("unknown platform `%.*s`", name.len, name.str));
    };

    bool if_returns = p->returns;

    p->returns = 0;

    if (p->tok == compiler__compiler__TokenKind_dollar &&
        compiler__Parser_peek(&/* ? */ *p) ==
            compiler__compiler__TokenKind_key_else) {

      compiler__Parser_next(p);

      compiler__Parser_next(p);

      compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

      compiler__Parser_genln(p, tos3("#else"));

      compiler__Parser_statements_no_rcbr(p);

      compiler__Parser_genln(p, tos3("#endif"));

      bool else_returns = p->returns;

      p->returns = if_returns && else_returns;
    };

  } else if (p->tok == compiler__compiler__TokenKind_key_for) {

    compiler__Parser_next(p);

    string name = compiler__Parser_check_name(p);

    if (string_ne(name, tos3("field"))) {

      compiler__Parser_error(p, tos3("for field only"));
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_in);

    compiler__Parser_check_name(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    compiler__Parser_check_name(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    string res_name = compiler__Parser_check_name(p);

    println(res_name);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dollar);

    compiler__Parser_check(p, compiler__compiler__TokenKind_name);

    compiler__Parser_check(p, compiler__compiler__TokenKind_assign);

    compiler__CGen_start_tmp(p->cgen);

    compiler__Parser_bool_expression(p);

    string val = compiler__CGen_end_tmp(p->cgen);

    println(val);

    compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

  } else if (p->tok == compiler__compiler__TokenKind_name &&
             string_eq(p->lit, tos3("vweb"))) {

    string path = string_add(p->cur_fn.name, tos3(".html"));

    if (p->pref->is_debug) {

      printf("compiling tmpl %.*s\n", path.len, path.str);
    };

    if (!os__file_exists(path)) {

      path = string_add(string_add(os__dir(p->scanner->file_path), tos3("/")),
                        path);

      if (!os__file_exists(path)) {

        compiler__Parser_error(p, _STR("vweb HTML template \"%.*s\" not found",
                                       path.len, path.str));
      };
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_name);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    compiler__Parser_check(p, compiler__compiler__TokenKind_name);

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    string v_code = vweb_dot_tmpl__compile_template(path);

    if (os__file_exists(tos3(".vwebtmpl.v"))) {

      os__rm(tos3(".vwebtmpl.v"));
    };

    os__write_file(tos3(".vwebtmpl.v"), string_clone(v_code));

    compiler__Parser_genln(p, tos3(""));

    int pos = p->cgen->lines.len - 1;

    compiler__Parser pp =
        compiler__V_new_parser_from_file(p->v, tos3(".vwebtmpl.v"));

    if (!p->pref->is_debug) {

      os__rm(tos3(".vwebtmpl.v"));
    };

    pp.is_vweb = 1;

    compiler__Parser_set_current_fn(&/* ? */ pp, p->cur_fn);

    compiler__Parser_parse(&/* ? */ pp, compiler__compiler__Pass_main);

    compiler__V_add_parser(pp.v, pp);

    string tmpl_fn_body = string_clone(array_string_join(
        array_slice(p->cgen->lines, pos + 2, p->cgen->lines.len), tos3("\n")));

    int end_pos =
        string_last_index(tmpl_fn_body, tos3("Builder_str( sb )")) + 19;

    p->cgen->lines = array_slice2(p->cgen->lines, 0, pos, false);

    compiler__Parser_genln(p, tos3("/////////////////// tmpl start"));

    compiler__Parser_genln(p, string_substr2(tmpl_fn_body, 0, end_pos, false));

    compiler__Parser_genln(p, tos3("/////////////////// tmpl end"));

    compiler__Var receiver = (*(compiler__Var *)array_get(p->cur_fn.args, 0));

    string dot = (receiver.is_mut) ? (tos3("->")) : (tos3("."));

    compiler__Parser_genln(
        p, _STR("vweb__Context_html(%.*s %.*s vweb, tmpl_res)",
                receiver.name.len, receiver.name.str, dot.len, dot.str));

  } else {

    compiler__Parser_error(p, tos3("bad comptime expr"));
  };
}
void compiler__Parser_chash(compiler__Parser *p) {

  string hash = string_trim_space(p->lit);

  compiler__Parser_next(p);

  if (string_starts_with(hash, tos3("flag "))) {

    if (compiler__Parser_first_pass(&/* ? */ *p)) {

      string flag = string_substr2(hash, 5, -1, true);

      flag = string_replace(flag, tos3("@VROOT"), p->vroot);

      flag = string_replace(flag, tos3("@VMOD"), compiler__v_modules_path);

      Option_bool tmp9 = compiler__Table_parse_cflag(p->table, flag, p->mod);
      if (!tmp9.ok) {
        string err = tmp9.error;
        int errcode = tmp9.ecode;

        compiler__Parser_error_with_token_index(
            p, err, compiler__Parser_cur_tok_index(&/* ? */ *p) - 1);

        return;
      };
    };

    return;
  };

  if (string_starts_with(hash, tos3("include"))) {

    if (compiler__Parser_first_pass(&/* ? */ *p) && !p->is_vh) {

      if (p->file_pcguard.len != 0) {

        _PUSH(&p->cgen->includes,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "%.*s\n#%.*s\n#endif", p->file_pcguard.len,
                  p->file_pcguard.str, hash.len, hash.str)),
              tmp10, string);

        return;
      };

      _PUSH(&p->cgen->includes,
            (/*typ = array_string   tmp_typ=string*/ _STR("#%.*s", hash.len,
                                                          hash.str)),
            tmp11, string);

      return;
    };

  } else if (string_contains(hash, tos3("embed"))) {

    int pos = string_index(hash, tos3("embed")) + 5;

    string file = string_substr2(hash, pos, -1, true);

    compiler__Parser_genln(p, _STR("#include %.*s", file.len, file.str));

  } else if (string_contains(hash, tos3("define"))) {

    _PUSH(&p->cgen->includes,
          (/*typ = array_string   tmp_typ=string*/ _STR("#%.*s", hash.len,
                                                        hash.str)),
          tmp14, string);

  } else if (string_eq(hash, tos3("-js"))) {

#ifdef _VJS

    while (p->tok != compiler__compiler__TokenKind_eof) {

      compiler__Parser_next(p);
    };

#else

    compiler__Parser_next(p);

#endif
    ;

  } else {

#ifndef _VJS

    if (!p->can_chash) {

      printf("hash=\"%.*s\"\n", hash.len, hash.str);

      if (string_starts_with(hash, tos3("include"))) {

        println(tos3("include"));

      } else {
      };

      compiler__Parser_error(
          p, tos3("bad token `#` (embedding C code is no longer supported)"));
    };

#endif
    ;

    compiler__Parser_genln(p, hash);
  };
}
void compiler__Parser_comptime_method_call(compiler__Parser *p,
                                           compiler__Type typ) {

  p->cgen->cur_line = tos3("");

  compiler__Parser_check(p, compiler__compiler__TokenKind_dollar);

  string var = compiler__Parser_check_name(p);

  array_compiler__Fn tmp15 = typ.methods;
  for (int i = 0; i < tmp15.len; i++) {
    compiler__Fn method = ((compiler__Fn *)tmp15.data)[i];

    if (string_ne(method.typ, tos3("void"))) {

      continue;
    };

    compiler__Var receiver = (*(compiler__Var *)array_get(method.args, 0));

    string amp = (receiver.is_mut) ? (tos3("&")) : (tos3(""));

    if (i > 0) {

      compiler__Parser_gen(p, tos3(" else "));
    };

    compiler__Parser_gen(
        p, _STR("if ( string_eq(%.*s, _STR(\"%.*s\")) ) %.*s_%.*s(%.*s %.*s);",
                var.len, var.str, method.name.len, method.name.str,
                typ.name.len, typ.name.str, method.name.len, method.name.str,
                amp.len, amp.str, p->expr_var.name.len, p->expr_var.name.str));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  if (p->tok == compiler__compiler__TokenKind_key_orelse) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_orelse);

    compiler__Parser_genln(p, tos3("else {"));

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    compiler__Parser_statements(p);
  };
}
void compiler__Parser_gen_array_str(compiler__Parser *p, compiler__Type typ) {

  if (compiler__Type_has_method(&/* ? */ typ, tos3("str"))) {

    return;
  };

  compiler__Parser_add_method(
      p, typ.name,
      (compiler__Fn){.name = tos3("str"),
                     .typ = tos3("string"),
                     .args = new_array_from_c_array(
                         1, 1, sizeof(compiler__Var),
                         EMPTY_ARRAY_OF_ELEMS(compiler__Var, 1){(compiler__Var){
                             .typ = typ.name,
                             .is_arg = 1,
                             .name = tos3(""),
                             .idx = 0,
                             .is_const = 0,
                             .args = new_array(0, 1, sizeof(compiler__Var)),
                             .attr = tos3(""),
                             .is_mut = 0,
                             .is_alloc = 0,
                             .is_returned = 0,
                             .ptr = 0,
                             .ref = 0,
                             .parent_fn = tos3(""),
                             .mod = tos3(""),
                             .is_global = 0,
                             .is_used = 0,
                             .is_changed = 0,
                             .scope_level = 0,
                             .is_c = 0,
                             .is_moved = 0,
                             .line_nr = 0,
                             .token_idx = 0,
                             .is_for_var = 0,
                             .is_public = 0}}),
                     .is_method = 1,
                     .is_public = 1,
                     .receiver_typ = typ.name,
                     .mod = tos3(""),
                     .is_interface = 0,
                     .scope_level = 0,
                     .is_c = 0,
                     .is_decl = 0,
                     .is_unsafe = 0,
                     .is_deprecated = 0,
                     .is_variadic = 0,
                     .is_generic = 0,
                     .returns_error = 0,
                     .defer_text = new_array(0, 1, sizeof(string)),
                     .type_pars = new_array(0, 1, sizeof(string)),
                     .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                     .body_idx = 0,
                     .fn_name_token_idx = 0,
                     .comptime_define = tos3(""),
                     .is_used = 0});

  string elm_type = string_substr2(typ.name, 6, -1, true);

  compiler__Type elm_type2 =
      compiler__Table_find_type(&/* ? */ *p->table, elm_type);

  bool is_array = string_starts_with(elm_type, tos3("array_"));

  if (is_array) {

    compiler__Parser_gen_array_str(p, elm_type2);

  } else if (string_eq(compiler__Parser_typ_to_fmt(p, elm_type, 0), tos3("")) &&
             !compiler__Table_type_has_method(
                 &/* ? */ *p->table,
                 &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ elm_type2,
                 tos3("str"))) {

    compiler__Parser_error(p, _STR("cant print %.*s[], unhandled print of %.*s",
                                   elm_type.len, elm_type.str, elm_type.len,
                                   elm_type.str));
  };

  strings__Builder_writeln(
      &/* ? */ p->v->vgen_buf,
      _STR(
          "\nfn (a %.*s) str() string {\n	mut sb := "
          "strings.new_builder(a.len * 3)\n	sb.write(\"[\")\n	for i, "
          "elm in a {\n		sb.write(elm.str())\n		if i < a.len - "
          "1 {\n			sb.write(\", \")\n		"
          "}\n	}\n	sb.write(\"]\")\n	return sb.str()\n}\n	",
          typ.name.len, typ.name.str));

  _PUSH(&p->cgen->fns,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "string %.*s_str();", typ.name.len, typ.name.str)),
        tmp20, string);
}
void compiler__Parser_gen_struct_str(compiler__Parser *p, compiler__Type typ) {

  compiler__Parser_add_method(
      p, typ.name,
      (compiler__Fn){.name = tos3("str"),
                     .typ = tos3("string"),
                     .args = new_array_from_c_array(
                         1, 1, sizeof(compiler__Var),
                         EMPTY_ARRAY_OF_ELEMS(compiler__Var, 1){(compiler__Var){
                             .typ = typ.name,
                             .is_arg = 1,
                             .name = tos3(""),
                             .idx = 0,
                             .is_const = 0,
                             .args = new_array(0, 1, sizeof(compiler__Var)),
                             .attr = tos3(""),
                             .is_mut = 0,
                             .is_alloc = 0,
                             .is_returned = 0,
                             .ptr = 0,
                             .ref = 0,
                             .parent_fn = tos3(""),
                             .mod = tos3(""),
                             .is_global = 0,
                             .is_used = 0,
                             .is_changed = 0,
                             .scope_level = 0,
                             .is_c = 0,
                             .is_moved = 0,
                             .line_nr = 0,
                             .token_idx = 0,
                             .is_for_var = 0,
                             .is_public = 0}}),
                     .is_method = 1,
                     .is_public = 1,
                     .receiver_typ = typ.name,
                     .mod = tos3(""),
                     .is_interface = 0,
                     .scope_level = 0,
                     .is_c = 0,
                     .is_decl = 0,
                     .is_unsafe = 0,
                     .is_deprecated = 0,
                     .is_variadic = 0,
                     .is_generic = 0,
                     .returns_error = 0,
                     .defer_text = new_array(0, 1, sizeof(string)),
                     .type_pars = new_array(0, 1, sizeof(string)),
                     .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                     .body_idx = 0,
                     .fn_name_token_idx = 0,
                     .comptime_define = tos3(""),
                     .is_used = 0});

  strings__Builder sb = strings__new_builder(typ.fields.len * 20);

  strings__Builder_writeln(
      &/* ? */ sb,
      _STR("fn (a %.*s) str() string {\nreturn", typ.name.len, typ.name.str));

  strings__Builder_writeln(&/* ? */ sb, tos3("'{"));

  array_compiler__Var tmp21 = typ.fields;
  for (int tmp22 = 0; tmp22 < tmp21.len; tmp22++) {
    compiler__Var field = ((compiler__Var *)tmp21.data)[tmp22];

    strings__Builder_writeln(
        &/* ? */ sb,
        string_add(_STR("\t%.*s: $", field.name.len, field.name.str),
                   _STR("a.%.*s", field.name.len, field.name.str)));
  };

  strings__Builder_writeln(&/* ? */ sb, tos3("}'"));

  strings__Builder_writeln(&/* ? */ sb, tos3("}"));

  strings__Builder_writeln(&/* ? */ p->v->vgen_buf, strings__Builder_str(sb));

  _PUSH(&p->cgen->fns,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "string %.*s_str();", typ.name.len, typ.name.str)),
        tmp23, string);
}
void compiler__Parser_gen_varg_str(compiler__Parser *p, compiler__Type typ) {

  string elm_type = string_substr2(typ.name, 5, -1, true);

  compiler__Type elm_type2 =
      compiler__Table_find_type(&/* ? */ *p->table, elm_type);

  bool is_array = string_starts_with(elm_type, tos3("array_"));

  if (is_array) {

    compiler__Parser_gen_array_str(p, elm_type2);

  } else if (elm_type2.cat == compiler__compiler__TypeCategory_struct_) {

    compiler__Parser_gen_struct_str(p, elm_type2);
  };

  strings__Builder_writeln(
      &/* ? */ p->v->vgen_buf,
      _STR("\nfn (a %.*s) str() string {\n	mut sb := "
           "strings.new_builder(a.len * 3)\n	sb.write(\"[\")\n	for i, "
           "elm in a {\n		sb.write(elm.str())\n		if i < "
           "a.len - 1 {\n			sb.write(\", \")\n	"
           "	}\n	}\n	sb.write(\"]\")\n	return sb.str()\n}",
           typ.name.len, typ.name.str));

  _PUSH(&p->cgen->fns,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "string %.*s_str();", typ.name.len, typ.name.str)),
        tmp26, string);
}
void compiler__Parser_gen_array_filter(compiler__Parser *p, string str_typ,
                                       int method_ph) {

  string val_type = string_substr2(str_typ, 6, -1, true);

  compiler__Parser_open_scope(p);

  compiler__Parser_register_var(
      p, (compiler__Var){.name = tos3("it"),
                         .typ = val_type,
                         .idx = 0,
                         .is_arg = 0,
                         .is_const = 0,
                         .args = new_array(0, 1, sizeof(compiler__Var)),
                         .attr = tos3(""),
                         .is_mut = 0,
                         .is_alloc = 0,
                         .is_returned = 0,
                         .ptr = 0,
                         .ref = 0,
                         .parent_fn = tos3(""),
                         .mod = tos3(""),
                         .is_global = 0,
                         .is_used = 0,
                         .is_changed = 0,
                         .scope_level = 0,
                         .is_c = 0,
                         .is_moved = 0,
                         .line_nr = 0,
                         .token_idx = 0,
                         .is_for_var = 0,
                         .is_public = 0});

  compiler__Parser_next(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  compiler__CGen_resetln(p->cgen, tos3(""));

  string tmp = compiler__Parser_get_tmp(p);

  string a = p->expr_var.name;

  compiler__CGen_set_placeholder(
      p->cgen, method_ph,
      _STR("\n%.*s %.*s = new_array(0, %.*s .len,sizeof(%.*s));\n", str_typ.len,
           str_typ.str, tmp.len, tmp.str, a.len, a.str, val_type.len,
           val_type.str));

  compiler__Parser_genln(
      p, _STR("for (int i = 0; i < %.*s.len; i++) {", a.len, a.str));

  compiler__Parser_genln(p, _STR("%.*s it = ((%.*s*)%.*s.data)[i];",
                                 val_type.len, val_type.str, val_type.len,
                                 val_type.str, a.len, a.str));

  compiler__Parser_gen(p, tos3("if ("));

  compiler__Parser_bool_expression(p);

  compiler__Parser_genln(p,
                         _STR(") array_push(&%.*s, &it);", tmp.len, tmp.str));

  compiler__Parser_genln(p, tos3("}"));

  compiler__Parser_gen(p, tmp);

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  compiler__Parser_close_scope(p);
}
string compiler__Parser_gen_array_map(compiler__Parser *p, string str_typ,
                                      int method_ph) {

  string val_type = string_substr2(str_typ, 6, -1, true);

  compiler__Parser_open_scope(p);

  compiler__Parser_register_var(
      p, (compiler__Var){.name = tos3("it"),
                         .typ = val_type,
                         .idx = 0,
                         .is_arg = 0,
                         .is_const = 0,
                         .args = new_array(0, 1, sizeof(compiler__Var)),
                         .attr = tos3(""),
                         .is_mut = 0,
                         .is_alloc = 0,
                         .is_returned = 0,
                         .ptr = 0,
                         .ref = 0,
                         .parent_fn = tos3(""),
                         .mod = tos3(""),
                         .is_global = 0,
                         .is_used = 0,
                         .is_changed = 0,
                         .scope_level = 0,
                         .is_c = 0,
                         .is_moved = 0,
                         .line_nr = 0,
                         .token_idx = 0,
                         .is_for_var = 0,
                         .is_public = 0});

  compiler__Parser_next(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  compiler__CGen_resetln(p->cgen, tos3(""));

  string tmp = compiler__Parser_get_tmp(p);

  string tmp_elm = compiler__Parser_get_tmp(p);

  string a = p->expr_var.name;

  _V_MulRet_string_V_string _V_mret_map_type_expr =
      compiler__Parser_tmp_expr(p);
  string map_type = _V_mret_map_type_expr.var_0;
  string expr = _V_mret_map_type_expr.var_1;

  compiler__CGen_set_placeholder(
      p->cgen, method_ph,
      string_add(_STR("\narray %.*s = new_array(0, %.*s .len, ", tmp.len,
                      tmp.str, a.len, a.str),
                 _STR("sizeof(%.*s));\n", map_type.len, map_type.str)));

  compiler__Parser_genln(
      p, _STR("for (int i = 0; i < %.*s.len; i++) {", a.len, a.str));

  compiler__Parser_genln(p, _STR("%.*s it = ((%.*s*)%.*s.data)[i];",
                                 val_type.len, val_type.str, val_type.len,
                                 val_type.str, a.len, a.str));

  compiler__Parser_genln(p, _STR("_PUSH(&%.*s, %.*s, %.*s, %.*s)", tmp.len,
                                 tmp.str, expr.len, expr.str, tmp_elm.len,
                                 tmp_elm.str, map_type.len, map_type.str));

  compiler__Parser_genln(p, tos3("}"));

  compiler__Parser_gen(p, tmp);

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  compiler__Parser_close_scope(p);

  return string_add(tos3("array_"), map_type);
}
void compiler__Parser_comptime_if_block(compiler__Parser *p, string name) {

  compiler__Parser_genln(p, _STR("#ifdef %.*s", name.len, name.str));

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  compiler__Parser_statements_no_rcbr(p);

  if (!(p->tok == compiler__compiler__TokenKind_dollar &&
        compiler__Parser_peek(&/* ? */ *p) ==
            compiler__compiler__TokenKind_key_else)) {

    compiler__Parser_genln(p, tos3("#endif"));
  };
}
void compiler__DepSet_add(compiler__DepSet *dset, string item) {

  _PUSH(&dset->items, (/*typ = array_string   tmp_typ=string*/ item), tmp1,
        string);
}
compiler__DepSet compiler__DepSet_diff(compiler__DepSet *dset,
                                       compiler__DepSet otherset) {

  compiler__DepSet diff =
      (compiler__DepSet){.items = new_array(0, 1, sizeof(string))};

  array_string tmp2 = dset->items;
  for (int tmp3 = 0; tmp3 < tmp2.len; tmp3++) {
    string item = ((string *)tmp2.data)[tmp3];

    if (!(_IN(string, (item), otherset.items))) {

      _PUSH(&diff.items, (/*typ = array_string   tmp_typ=string*/ item), tmp4,
            string);
    };
  };

  return diff;
}
int compiler__DepSet_size(compiler__DepSet *dset) { return dset->items.len; }
compiler__DepGraph *compiler__new_dep_graph() {

  return (compiler__DepGraph *)memdup(
      &(compiler__DepGraph){
          .acyclic = 1,
          .nodes = new_array(0, 1, sizeof(compiler__DepGraphNode))},
      sizeof(compiler__DepGraph));
}
void compiler__DepGraph_add(compiler__DepGraph *graph, string mod,
                            array_string deps) {

  _PUSH(
      &graph->nodes,
      (/*typ = array_compiler__DepGraphNode   tmp_typ=compiler__DepGraphNode*/ (
          compiler__DepGraphNode){.name = mod, .deps = array_clone(deps)}),
      tmp5, compiler__DepGraphNode);
}
compiler__DepGraph *compiler__DepGraph_resolve(compiler__DepGraph *graph) {

  map_compiler__DepGraphNode node_names =
      new_map(1, sizeof(compiler__DepGraphNode));

  map_compiler__DepSet node_deps = new_map(1, sizeof(compiler__DepSet));

  array_compiler__DepGraphNode tmp6 = graph->nodes;
  for (int _ = 0; _ < tmp6.len; _++) {
    compiler__DepGraphNode node = ((compiler__DepGraphNode *)tmp6.data)[_];

    map_set(&node_names, node.name, &(compiler__DepGraphNode[]){node});

    compiler__DepSet dep_set =
        (compiler__DepSet){.items = new_array(0, 1, sizeof(string))};

    array_string tmp7 = node.deps;
    for (int _ = 0; _ < tmp7.len; _++) {
      string dep = ((string *)tmp7.data)[_];

      compiler__DepSet_add(&/* ? */ dep_set, dep);
    };

    map_set(&node_deps, node.name, &(compiler__DepSet[]){dep_set});
  };

  compiler__DepGraph *resolved = compiler__new_dep_graph();

  while (node_deps.size != 0) {

    compiler__DepSet ready_set =
        (compiler__DepSet){.items = new_array(0, 1, sizeof(string))};

    map_compiler__DepSet tmp8 = node_deps;
    array_string keys_tmp8 = map_keys(&tmp8);
    for (int l = 0; l < keys_tmp8.len; l++) {
      string name = ((string *)keys_tmp8.data)[l];
      compiler__DepSet deps = {0};
      map_get(tmp8, name, &deps);

      if (compiler__DepSet_size(&/* ? */ deps) == 0) {

        compiler__DepSet_add(&/* ? */ ready_set, name);
      };
    };

    if (compiler__DepSet_size(&/* ? */ ready_set) == 0) {

      compiler__DepGraph *g = compiler__new_dep_graph();

      g->acyclic = 0;

      map_compiler__DepSet tmp9 = node_deps;
      array_string keys_tmp9 = map_keys(&tmp9);
      for (int l = 0; l < keys_tmp9.len; l++) {
        string name = ((string *)keys_tmp9.data)[l];

        compiler__DepGraphNode tmp11 = {0};
        bool tmp12 = map_get(/*depgraph.v : 87*/ node_names, name, &tmp11);

        _PUSH(&g->nodes,
              (/*typ = array_compiler__DepGraphNode
                  tmp_typ=compiler__DepGraphNode*/
               tmp11),
              tmp10, compiler__DepGraphNode);
      };

      return g;
    };

    array_string tmp13 = ready_set.items;
    for (int tmp14 = 0; tmp14 < tmp13.len; tmp14++) {
      string name = ((string *)tmp13.data)[tmp14];

      v_map_delete(&/* ? */ node_deps, name);

      compiler__DepGraphNode tmp16 = {0};
      bool tmp17 = map_get(/*depgraph.v : 94*/ node_names, name, &tmp16);

      _PUSH(&resolved->nodes,
            (/*typ = array_compiler__DepGraphNode
                tmp_typ=compiler__DepGraphNode*/
             tmp16),
            tmp15, compiler__DepGraphNode);
    };

    map_compiler__DepSet tmp18 = node_deps;
    array_string keys_tmp18 = map_keys(&tmp18);
    for (int l = 0; l < keys_tmp18.len; l++) {
      string name = ((string *)keys_tmp18.data)[l];
      compiler__DepSet deps = {0};
      map_get(tmp18, name, &deps);

      map_set(&node_deps, name,
              &(compiler__DepSet[]){
                  compiler__DepSet_diff(&/* ? */ deps, ready_set)});
    };
  };

  return resolved;
}
compiler__DepGraphNode compiler__DepGraph_last_node(compiler__DepGraph *graph) {

  return (
      *(compiler__DepGraphNode *)array_get(graph->nodes, graph->nodes.len - 1));
}
string compiler__DepGraph_display(compiler__DepGraph *graph) {

  string out = tos3("\n");

  array_compiler__DepGraphNode tmp21 = graph->nodes;
  for (int tmp22 = 0; tmp22 < tmp21.len; tmp22++) {
    compiler__DepGraphNode node = ((compiler__DepGraphNode *)tmp21.data)[tmp22];

    array_string tmp23 = node.deps;
    for (int tmp24 = 0; tmp24 < tmp23.len; tmp24++) {
      string dep = ((string *)tmp23.data)[tmp24];

      out = string_add(out, _STR(" * %.*s -> %.*s\n", node.name.len,
                                 node.name.str, dep.len, dep.str));
    };
  };

  return out;
}
string compiler__DepGraph_display_cycles(compiler__DepGraph *graph) {

  map_compiler__DepGraphNode node_names =
      new_map(1, sizeof(compiler__DepGraphNode));

  array_compiler__DepGraphNode tmp25 = graph->nodes;
  for (int tmp26 = 0; tmp26 < tmp25.len; tmp26++) {
    compiler__DepGraphNode node = ((compiler__DepGraphNode *)tmp25.data)[tmp26];

    map_set(&node_names, node.name, &(compiler__DepGraphNode[]){node});
  };

  string out = tos3("\n");

  array_compiler__DepGraphNode tmp27 = graph->nodes;
  for (int tmp28 = 0; tmp28 < tmp27.len; tmp28++) {
    compiler__DepGraphNode node = ((compiler__DepGraphNode *)tmp27.data)[tmp28];

    array_string tmp29 = node.deps;
    for (int tmp30 = 0; tmp30 < tmp29.len; tmp30++) {
      string dep = ((string *)tmp29.data)[tmp30];

      if (!((_IN_MAP((dep), node_names)))) {

        continue;
      };

      compiler__DepGraphNode tmp31 = {0};
      bool tmp32 = map_get(/*depgraph.v : 128*/ node_names, dep, &tmp31);

      compiler__DepGraphNode dn = tmp31;

      if ((_IN(string, (node.name), dn.deps))) {

        out = string_add(out, _STR(" * %.*s -> %.*s\n", node.name.len,
                                   node.name.str, dep.len, dep.str));
      };
    };
  };

  return out;
}
void compiler__Parser_enum_decl(compiler__Parser *p, bool no_name) {

  bool is_pub = p->tok == compiler__compiler__TokenKind_key_pub;

  if (is_pub) {

    compiler__Parser_next(p);
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_enum);

  string enum_name = compiler__Parser_check_name(p);

  bool is_c = string_eq(enum_name, tos3("C")) &&
              p->tok == compiler__compiler__TokenKind_dot;

  if (is_c) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    enum_name = compiler__Parser_check_name(p);
  };

  if (!p->builtin_mod && string_ne(p->mod, tos3("main"))) {

    enum_name = compiler__Parser_prepend_mod(&/* ? */ *p, enum_name);
  };

  if (!no_name && !compiler__Parser_first_pass(&/* ? */ *p)) {

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "typedef int %.*s;", enum_name.len, enum_name.str)),
          tmp1, string);
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  int val = 0;

  array_string fields = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (p->tok == compiler__compiler__TokenKind_name) {

    string field = compiler__Parser_check_name(p);

    if (compiler__contains_capital(field)) {

      compiler__Parser_warn(p, tos3("enum values cannot contain uppercase "
                                    "letters, use snake_case instead"));
    };

    _PUSH(&fields, (/*typ = array_string   tmp_typ=string*/ field), tmp2,
          string);

    ;

    string name = _STR("%.*s__%.*s_%.*s", compiler__mod_gen_name(p->mod).len,
                       compiler__mod_gen_name(p->mod).str, enum_name.len,
                       enum_name.str, field.len, field.str);

    if (p->tok == compiler__compiler__TokenKind_assign) {

      int enum_assign_tidx = compiler__Parser_cur_tok_index(&/* ? */ *p);

      if (compiler__Parser_peek(&/* ? */ *p) ==
          compiler__compiler__TokenKind_number) {

        compiler__Parser_next(p);

        val = v_string_int(p->lit);

        compiler__Parser_next(p);

      } else {

        compiler__Parser_next(p);

        enum_assign_tidx = compiler__Parser_cur_tok_index(&/* ? */ *p);

        compiler__Parser_error_with_token_index(
            p, tos3("only numbers are allowed in enum initializations"),
            enum_assign_tidx);
      };
    };

    if (p->pass == compiler__compiler__Pass_main) {

      _PUSH(&p->cgen->consts,
            (/*typ = array_string   tmp_typ=string*/ _STR(
                "#define %.*s %d", name.len, name.str, val)),
            tmp3, string);
    };

    if (p->tok == compiler__compiler__TokenKind_comma) {

      compiler__Parser_next(p);
    };

    val++;
  };

  compiler__Table_register_type2(
      p->table,
      (compiler__Type){.name = enum_name,
                       .mod = p->mod,
                       .parent = tos3("int"),
                       .cat = compiler__compiler__TypeCategory_enum_,
                       .enum_vals = array_clone(fields),
                       .is_public = is_pub,
                       .fields = new_array(0, 1, sizeof(compiler__Var)),
                       .methods = new_array(0, 1, sizeof(compiler__Fn)),
                       .is_c = 0,
                       .gen_types = new_array(0, 1, sizeof(string)),
                       .is_placeholder = 0,
                       .gen_str = 0});

  compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

  ;
}
void compiler__Parser_check_enum_member_access(compiler__Parser *p) {

  compiler__Type T = compiler__Parser_find_type(&/* ? */ *p, p->expected_type);

  if (T.cat == compiler__compiler__TypeCategory_enum_) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    string val = compiler__Parser_check_name(p);

    if (!compiler__Type_has_enum_val(&/* ? */ T, val)) {

      compiler__Parser_error(p, _STR("enum `%.*s` does not have value `%.*s`",
                                     T.name.len, T.name.str, val.len, val.str));
    };

    compiler__Parser_gen(
        p, string_add(
               string_add(string_add(string_add(compiler__mod_gen_name(T.mod),
                                                tos3("__")),
                                     p->expected_type),
                          tos3("_")),
               val));

  } else {

    compiler__Parser_error(
        p, _STR("`%.*s` is not an enum", T.name.len, T.name.str));
  };
}
string compiler__Parser_bool_expression(compiler__Parser *p) {

  compiler__TokenKind tok = p->tok;

  string typ = compiler__Parser_bterm(p);

  bool got_and = 0;

  bool got_or = 0;

  while (p->tok == compiler__compiler__TokenKind_and ||
         p->tok == compiler__compiler__TokenKind_logical_or) {

    if (p->tok == compiler__compiler__TokenKind_and) {

      got_and = 1;

      if (got_or) {

        compiler__Parser_error(p, compiler__and_or_error);
      };
    };

    if (p->tok == compiler__compiler__TokenKind_logical_or) {

      got_or = 1;

      if (got_and) {

        compiler__Parser_error(p, compiler__and_or_error);
      };
    };

    if (p->is_sql) {

      if (p->tok == compiler__compiler__TokenKind_and) {

        compiler__Parser_gen(p, tos3(" and "));

      } else if (p->tok == compiler__compiler__TokenKind_logical_or) {

        compiler__Parser_gen(p, tos3(" or "));
      };

    } else {

      compiler__Parser_gen(p,
                           _STR(" %.*s ", compiler__TokenKind_str(p->tok).len,
                                compiler__TokenKind_str(p->tok).str));
    };

    compiler__Parser_check_space(p, p->tok);

    compiler__Parser_check_types(p, compiler__Parser_bterm(p), typ);

    if (string_ne(typ, tos3("bool"))) {

      compiler__Parser_error(
          p, tos3("logical operators `&&` and `||` require booleans"));
    };
  };

  if (string_eq(typ, tos3(""))) {

    println(tos3("curline:"));

    println(p->cgen->cur_line);

    println(compiler__TokenKind_str(tok));

    compiler__Parser_error(p, tos3("expr() returns empty type"));
  };

  return typ;
}
string compiler__Parser_bterm(compiler__Parser *p) {

  int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = compiler__Parser_expression(p);

  p->expected_type = typ;

  bool is_str = string_eq(typ, tos3("string")) && !p->is_sql;

  bool is_ustr = string_eq(typ, tos3("ustring"));

  bool is_float =
      string_at(typ, 0) == 'f' &&
      (string_eq(typ, tos3("f64")) || string_eq(typ, tos3("f32"))) &&
      !(string_eq(p->cur_fn.name, tos3("f64_abs")) ||
        string_eq(p->cur_fn.name, tos3("f32_abs"))) &&
      !(string_eq(p->cur_fn.name, tos3("eq")));

  bool is_array = string_contains(typ, tos3("array_"));

  string expr_type = typ;

  compiler__TokenKind tok = p->tok;

  if (tok == compiler__compiler__TokenKind_eq ||
      tok == compiler__compiler__TokenKind_gt ||
      tok == compiler__compiler__TokenKind_lt ||
      tok == compiler__compiler__TokenKind_le ||
      tok == compiler__compiler__TokenKind_ge ||
      tok == compiler__compiler__TokenKind_ne) {

    if (is_array) {

      compiler__Parser_error(p, tos3("Array comparing is not supported yet"));
    };

    ;

    if ((is_float || is_str || is_ustr) && !p->is_js) {

      compiler__Parser_gen(p, tos3(","));

    } else if (p->is_sql && tok == compiler__compiler__TokenKind_eq) {

      compiler__Parser_gen(p, tos3("="));

    } else {

      compiler__Parser_gen(p, compiler__TokenKind_str(tok));
    };

    compiler__Parser_next(p);

    if (p->is_sql) {

      p->sql_i++;

      compiler__Parser_gen(p, string_add(tos3("$"), int_str(p->sql_i)));

      compiler__CGen_start_cut(p->cgen);

      compiler__Parser_check_types(p, compiler__Parser_expression(p), typ);

      string sql_param = compiler__CGen_cut(p->cgen);

      _PUSH(&p->sql_params, (/*typ = array_string   tmp_typ=string*/ sql_param),
            tmp3, string);

      _PUSH(&p->sql_types, (/*typ = array_string   tmp_typ=string*/ typ), tmp4,
            string);

    } else {

      compiler__Parser_check_types(p, compiler__Parser_expression(p), typ);
    };

    typ = tos3("bool");

    if (is_str && !p->is_js) {

      compiler__Parser_gen(p, tos3(")"));

      compiler__TokenKind tmp5 = tok;

      if (tmp5 == compiler__compiler__TokenKind_eq) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("string_eq("));

      } else if (tmp5 == compiler__compiler__TokenKind_ne) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("string_ne("));

      } else if (tmp5 == compiler__compiler__TokenKind_le) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("string_le("));

      } else if (tmp5 == compiler__compiler__TokenKind_ge) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("string_ge("));

      } else if (tmp5 == compiler__compiler__TokenKind_gt) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("string_gt("));

      } else if (tmp5 == compiler__compiler__TokenKind_lt) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("string_lt("));
      };
    };

    if (is_ustr) {

      compiler__Parser_gen(p, tos3(")"));

      compiler__TokenKind tmp6 = tok;

      if (tmp6 == compiler__compiler__TokenKind_eq) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("ustring_eq("));

      } else if (tmp6 == compiler__compiler__TokenKind_ne) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("ustring_ne("));

      } else if (tmp6 == compiler__compiler__TokenKind_le) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("ustring_le("));

      } else if (tmp6 == compiler__compiler__TokenKind_ge) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("ustring_ge("));

      } else if (tmp6 == compiler__compiler__TokenKind_gt) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("ustring_gt("));

      } else if (tmp6 == compiler__compiler__TokenKind_lt) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("ustring_lt("));
      };
    };

    if (is_float && string_ne(p->cur_fn.name, tos3("f32_abs")) &&
        string_ne(p->cur_fn.name, tos3("f64_abs"))) {

      compiler__Parser_gen(p, tos3(")"));

      compiler__TokenKind tmp7 = tok;

      if (tmp7 == compiler__compiler__TokenKind_eq) {

        compiler__CGen_set_placeholder(
            p->cgen, ph, _STR("%.*s_eq(", expr_type.len, expr_type.str));

      } else if (tmp7 == compiler__compiler__TokenKind_ne) {

        compiler__CGen_set_placeholder(
            p->cgen, ph, _STR("%.*s_ne(", expr_type.len, expr_type.str));

      } else if (tmp7 == compiler__compiler__TokenKind_le) {

        compiler__CGen_set_placeholder(
            p->cgen, ph, _STR("%.*s_le(", expr_type.len, expr_type.str));

      } else if (tmp7 == compiler__compiler__TokenKind_ge) {

        compiler__CGen_set_placeholder(
            p->cgen, ph, _STR("%.*s_ge(", expr_type.len, expr_type.str));

      } else if (tmp7 == compiler__compiler__TokenKind_gt) {

        compiler__CGen_set_placeholder(
            p->cgen, ph, _STR("%.*s_gt(", expr_type.len, expr_type.str));

      } else if (tmp7 == compiler__compiler__TokenKind_lt) {

        compiler__CGen_set_placeholder(
            p->cgen, ph, _STR("%.*s_lt(", expr_type.len, expr_type.str));
      };
    };
  };

  return typ;
}
string compiler__Parser_name_expr(compiler__Parser *p) {

  p->has_immutable_field = 0;

  p->is_const_literal = 0;

  int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  bool ptr = p->tok == compiler__compiler__TokenKind_amp;

  bool deref = p->tok == compiler__compiler__TokenKind_mul;

  if (ptr || deref) {

    compiler__Parser_next(p);
  };

  string name = p->lit;

  if (string_eq(name, tos3("r")) &&
      compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_str) {

    compiler__Parser_string_expr(p);

    return tos3("string");
  };

  ;

  string orig_name = name;

  bool is_c =
      string_eq(name, tos3("C")) &&
      compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_dot;

  if (is_c) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_name);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    name = p->lit;

    if (compiler__Parser_peek(&/* ? */ *p) ==
            compiler__compiler__TokenKind_lcbr &&
        compiler__Table_known_type(&/* ? */ *p->table, name)) {

      return compiler__Parser_get_struct_type(p, name, 1, ptr);
    };

    if (compiler__Parser_peek(&/* ? */ *p) ==
        compiler__compiler__TokenKind_lpar) {

      return compiler__Parser_get_c_func_type(p, name);
    };

    compiler__Parser_gen(p, name);

    compiler__Parser_next(p);

    return tos3("int");
  };

  if (p->tok == compiler__compiler__TokenKind_dot) {

    if (compiler__Table_known_type(&/* ? */ *p->table, p->expected_type)) {

      compiler__Parser_check_enum_member_access(p);

      return p->expected_type;

    } else {

      compiler__Parser_error(p,
                             _STR("unknown enum: `%.*s`", p->expected_type.len,
                                  p->expected_type.str));
    };
  };

  if (compiler__Parser_known_var_check_new_var(p, name)) {

    return compiler__Parser_get_var_type(p, name, ptr, deref);
  };

  if (compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_dot &&
      (string_eq(name, p->mod) ||
       compiler__ImportTable_known_alias(&/* ? */ p->import_table, name)) &&
      !is_c) {

    string mod = name;

    if (string_ne(name, p->mod) &&
        compiler__ImportTable_known_alias(&/* ? */ p->import_table, name)) {

      compiler__ImportTable_register_used_import(&/* ? */ p->import_table,
                                                 name);

      mod = compiler__ImportTable_resolve_alias(&/* ? */ p->import_table, name);
    };

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    name = p->lit;

    ;

    name = compiler__prepend_mod(compiler__mod_gen_name(mod), name);

  } else if (!compiler__Table_known_type(&/* ? */ *p->table, name) &&
             !compiler__Table_known_fn(&/* ? */ *p->table, name) &&
             !compiler__Table_known_const(&/* ? */ *p->table, name) && !is_c) {

    name = compiler__Parser_prepend_mod(&/* ? */ *p, name);

  } else {
  };

  if (compiler__Parser_known_var_check_new_var(p, name)) {

    return compiler__Parser_get_var_type(p, name, ptr, deref);
  };

  if (compiler__Table_known_type(&/* ? */ *p->table, name)) {

    if (!is_c && (compiler__Parser_peek(&/* ? */ *p) ==
                      compiler__compiler__TokenKind_lpar ||
                  (deref && compiler__Parser_peek(&/* ? */ *p) ==
                                compiler__compiler__TokenKind_rpar))) {

      if (deref) {

        name = string_add(name, tos3("*"));

      } else if (ptr) {

        name = string_add(name, tos3("*"));
      };

      compiler__Parser_gen(p, tos3("("));

      string typ = name;

      if ((_IN(string, (typ), map_keys(&/* ? */ p->cur_fn.dispatch_of.inst)))) {

        string tmp8 = tos3("");
        bool tmp9 = map_get(/*expression.v : 224*/ p->cur_fn.dispatch_of.inst,
                            typ, &tmp8);

        if (!tmp9)
          tmp8 = tos((byte *)"", 0);

        typ = tmp8;
      };

      compiler__Parser_cast(p, typ);

      compiler__Parser_gen(p, tos3(")"));

      while (p->tok == compiler__compiler__TokenKind_dot) {

        typ = compiler__Parser_dot(p, typ, ph);
      };

      return typ;

    } else if (compiler__Parser_peek(&/* ? */ *p) ==
               compiler__compiler__TokenKind_dot) {

      compiler__Type enum_type =
          compiler__Table_find_type(&/* ? */ *p->table, name);

      if (enum_type.cat != compiler__compiler__TypeCategory_enum_) {

        compiler__Parser_error(
            p, _STR("`%.*s` is not an enum", name.len, name.str));
      };

      compiler__Parser_next(p);

      compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

      string val = p->lit;

      if (!compiler__Type_has_enum_val(&/* ? */ enum_type, val)) {

        compiler__Parser_error(p, _STR("enum `%.*s` does not have value `%.*s`",
                                       enum_type.name.len, enum_type.name.str,
                                       val.len, val.str));
      };

      if (string_eq(p->expected_type, enum_type.name)) {

        compiler__Parser_warn(p, _STR("`%.*s.%.*s` is unnecessary, use `.%.*s`",
                                      enum_type.name.len, enum_type.name.str,
                                      val.len, val.str, val.len, val.str));
      };

      compiler__Parser_gen(
          p, string_add(string_add(string_add(string_add(compiler__mod_gen_name(
                                                             enum_type.mod),
                                                         tos3("__")),
                                              enum_type.name),
                                   tos3("_")),
                        val));

      compiler__Parser_next(p);

      return enum_type.name;

    } else if (compiler__Parser_peek(&/* ? */ *p) ==
               compiler__compiler__TokenKind_lcbr) {

      return compiler__Parser_get_struct_type(p, name, 0, ptr);
    };
  };

  if (compiler__Table_known_const(&/* ? */ *p->table, name)) {

    return compiler__Parser_get_const_type(p, name, ptr);
  };

  Option_compiler__Fn tmp10 =
      compiler__Table_find_fn_is_script(&/* ? */ *p->table, name, p->v_script);
  compiler__Fn f;
  if (!tmp10.ok) {
    string err = tmp10.error;
    int errcode = tmp10.ecode;

    if (compiler__Parser_first_pass(&/* ? */ *p)) {

      compiler__Parser_next(p);

      return tos3("void");
    };

    compiler__Parser_undefined_error(p, name, orig_name);

    return tos3("");
  }
  f = *(compiler__Fn *)tmp10.data;
  ;

  compiler__TokenKind peek = compiler__Parser_peek(&/* ? */ *p);

  if (peek != compiler__compiler__TokenKind_lpar &&
      peek != compiler__compiler__TokenKind_lt) {

    compiler__Type fn_typ =
        (compiler__Type){.name = compiler__Fn_typ_str(&/* ? */ f),
                         .mod = p->mod,
                         .func = f,
                         .is_public = 0,
                         .fields = new_array(0, 1, sizeof(compiler__Var)),
                         .methods = new_array(0, 1, sizeof(compiler__Fn)),
                         .parent = tos3(""),
                         .is_c = 0,
                         .enum_vals = new_array(0, 1, sizeof(string)),
                         .gen_types = new_array(0, 1, sizeof(string)),
                         .is_placeholder = 0,
                         .gen_str = 0};

    compiler__Table_register_type2(p->table, fn_typ);

    compiler__Parser_gen(
        p, compiler__Table_fn_gen_name(
               p->table, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f));

    compiler__Parser_next(p);

    return compiler__Fn_typ_str(&/* ? */ f);
  };

  if (string_eq(f.typ, tos3("void")) && !p->inside_if_expr) {
  };

  int fn_call_ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  compiler__Fn new_f = f;

  compiler__Parser_fn_call(
      p, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ new_f, 0, tos3(""),
      tos3(""));

  if (f.is_generic) {

    Option_compiler__Fn tmp11 =
        compiler__Table_find_fn(&/* ? */ *p->table, f.name);
    compiler__Fn f2;
    if (!tmp11.ok) {
      string err = tmp11.error;
      int errcode = tmp11.ecode;

      return tos3("");
    }
    f2 = *(compiler__Fn *)tmp11.data;
    ;
  };

  f = new_f;

  bool is_or_else = p->tok == compiler__compiler__TokenKind_key_orelse;

  if (!p->is_var_decl && is_or_else) {

    f.typ = compiler__Parser_gen_handle_option_or_else(p, f.typ, tos3(""),
                                                       fn_call_ph);

  } else if (!p->is_var_decl && !is_or_else && !p->inside_return_expr &&
             string_starts_with(f.typ, tos3("Option_"))) {

    string opt_type = string_substr2(f.typ, 7, -1, true);

    compiler__Parser_error(
        p, _STR("unhandled option type: `?%.*s`", opt_type.len, opt_type.str));
  };

  if (p->tok == compiler__compiler__TokenKind_dot) {

    string typ = tos3("");

    while (p->tok == compiler__compiler__TokenKind_dot) {

      typ = compiler__Parser_dot(p, f.typ, ph);
    };

    return typ;
  };

  if (string_ends_with(f.typ, tos3("*"))) {

    p->is_alloc = 1;
  };

  return f.typ;
}
string compiler__Parser_expression(compiler__Parser *p) {

  p->is_const_literal = 1;

  int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = compiler__Parser_indot_expr(p);

  bool is_str = string_eq(typ, tos3("string"));

  bool is_ustr = string_eq(typ, tos3("ustring"));

  if (p->tok == compiler__compiler__TokenKind_left_shift) {

    if (string_contains(typ, tos3("array_"))) {

      string tmp = compiler__Parser_get_tmp(p);

      string tmp_typ = string_substr2(typ, 6, -1, true);

      compiler__Parser_check_space(p, compiler__compiler__TokenKind_left_shift);

      compiler__Parser_gen(p, tos3(", ("));

      if (!p->expr_var.is_mut && !p->pref->translated) {

        compiler__Parser_error(p, _STR("`%.*s` is immutable (can\'t <<)",
                                       p->expr_var.name.len,
                                       p->expr_var.name.str));
      };

      if (p->expr_var.is_arg &&
          string_starts_with(p->expr_var.typ, tos3("array_"))) {

        compiler__Parser_error(
            p, string_add(
                   tos3("for now it's not possible to append an element to "),
                   _STR("a mutable array argument `%.*s`", p->expr_var.name.len,
                        p->expr_var.name.str)));
      };

      if (!p->expr_var.is_changed) {

        compiler__Parser_mark_var_changed(p, p->expr_var);
      };

      compiler__Parser_gen(p, _STR("/*typ = %.*s   tmp_typ=%.*s*/", typ.len,
                                   typ.str, tmp_typ.len, tmp_typ.str));

      int ph_clone = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

      string expr_type = compiler__Parser_expression(p);

      if (p->pref->autofree && string_eq(typ, tos3("array_string")) &&
          string_eq(expr_type, tos3("string"))) {

        compiler__CGen_set_placeholder(p->cgen, ph_clone,
                                       tos3("string_clone("));

        compiler__Parser_gen(p, tos3(")"));
      };

      compiler__Parser_gen_array_push(p, ph, typ, expr_type, tmp, tmp_typ);

      return tos3("void");

    } else {

      if (!compiler__is_integer_type(typ)) {

        compiler__Parser_error(
            p, _STR("cannot use shift operator on non-integer type `%.*s`",
                    typ.len, typ.str));
      };

      compiler__Parser_next(p);

      compiler__Parser_gen(p, tos3(" << "));

      compiler__Parser_check_types(p, compiler__Parser_expression(p),
                                   tos3("integer"));

      return typ;
    };
  };

  if (p->tok == compiler__compiler__TokenKind_righ_shift) {

    if (!compiler__is_integer_type(typ)) {

      compiler__Parser_error(
          p, _STR("cannot use shift operator on non-integer type `%.*s`",
                  typ.len, typ.str));
    };

    compiler__Parser_next(p);

    compiler__Parser_gen(p, tos3(" >> "));

    compiler__Parser_check_types(p, compiler__Parser_expression(p),
                                 tos3("integer"));

    return typ;
  };

  while (p->tok == compiler__compiler__TokenKind_plus ||
         p->tok == compiler__compiler__TokenKind_minus ||
         p->tok == compiler__compiler__TokenKind_pipe ||
         p->tok == compiler__compiler__TokenKind_amp ||
         p->tok == compiler__compiler__TokenKind_xor) {

    compiler__TokenKind tok_op = p->tok;

    if (string_eq(typ, tos3("bool"))) {

      compiler__Parser_error(p, _STR("operator %.*s not defined on bool ",
                                     compiler__TokenKind_str(p->tok).len,
                                     compiler__TokenKind_str(p->tok).str));
    };

    bool is_num = string_eq(typ, tos3("void*")) ||
                  string_eq(typ, tos3("byte*")) ||
                  compiler__is_number_type(typ);

    compiler__Parser_check_space(p, p->tok);

    if (is_str && tok_op == compiler__compiler__TokenKind_plus && !p->is_js) {

      compiler__CGen_set_placeholder(p->cgen, ph, tos3("string_add("));

      compiler__Parser_gen(p, tos3(","));

    } else if (is_ustr && tok_op == compiler__compiler__TokenKind_plus) {

      compiler__CGen_set_placeholder(p->cgen, ph, tos3("ustring_add("));

      compiler__Parser_gen(p, tos3(","));

    } else if (is_num || p->is_js) {

      if (string_eq(typ, tos3("void*"))) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("(byte*)"));
      };

      compiler__Parser_gen(p, compiler__TokenKind_str(tok_op));

    } else {

      if (p->pref->translated) {

        compiler__Parser_gen(p, string_add(compiler__TokenKind_str(tok_op),
                                           tos3(" /*doom hack*/")));

      } else {

        compiler__Parser_gen(p, tos3(","));
      };
    };

    if (is_str && tok_op != compiler__compiler__TokenKind_plus) {

      compiler__Parser_error(p, tos3("strings only support `+` operator"));
    };

    string expr_type = compiler__Parser_term(p);

    if ((tok_op == compiler__compiler__TokenKind_pipe ||
         tok_op == compiler__compiler__TokenKind_amp) &&
        !(compiler__is_integer_type(expr_type) &&
          compiler__is_integer_type(typ))) {

      compiler__Parser_error(
          p, tos3("operators `&` and `|` are defined only on integer types"));
    };

    compiler__Parser_check_types(p, expr_type, typ);

    if ((is_str || is_ustr) && tok_op == compiler__compiler__TokenKind_plus &&
        !p->is_js) {

      compiler__Parser_gen(p, tos3(")"));
    };

    if (!p->pref->translated && !is_str && !is_ustr && !is_num) {

      compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, typ);

      if (tok_op == compiler__compiler__TokenKind_plus) {

        compiler__Parser_handle_operator(
            p, tos3("+"), typ, tos3("op_plus"), ph,
            &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ T);

      } else if (tok_op == compiler__compiler__TokenKind_minus) {

        compiler__Parser_handle_operator(
            p, tos3("-"), typ, tos3("op_minus"), ph,
            &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ T);
      };
    };
  };

  return typ;
}
void compiler__Parser_handle_operator(compiler__Parser *p, string op,
                                      string typ, string cpostfix, int ph,
                                      compiler__Type *T) {

  if (compiler__Type_has_method(&/* ? */ *T, op)) {

    compiler__CGen_set_placeholder(
        p->cgen, ph,
        _STR("%.*s_%.*s(", typ.len, typ.str, cpostfix.len, cpostfix.str));

    compiler__Parser_gen(p, tos3(")"));

  } else {

    compiler__Parser_error(p, _STR("operator %.*s not defined on `%.*s`",
                                   op.len, op.str, typ.len, typ.str));
  };
}
string compiler__Parser_term(compiler__Parser *p) {

  int line_nr = p->scanner->line_nr;

  int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = compiler__Parser_unary(p);

  if (p->tok == compiler__compiler__TokenKind_mul &&
      line_nr != p->scanner->line_nr) {

    return typ;
  };

  while (p->tok == compiler__compiler__TokenKind_mul ||
         p->tok == compiler__compiler__TokenKind_div ||
         p->tok == compiler__compiler__TokenKind_mod) {

    compiler__TokenKind tok = p->tok;

    bool is_div = tok == compiler__compiler__TokenKind_div;

    bool is_mod = tok == compiler__compiler__TokenKind_mod;

    compiler__Parser_next(p);

    compiler__Parser_gen(p, compiler__TokenKind_str(tok));

    int oph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

    ;

    if ((is_div || is_mod) && p->tok == compiler__compiler__TokenKind_number &&
        string_eq(p->lit, tos3("0"))) {

      compiler__Parser_error(p, tos3("division or modulo by zero"));
    };

    string expr_type = compiler__Parser_unary(p);

    if (!compiler__is_primitive_type(expr_type) && string_eq(expr_type, typ)) {

      compiler__Parser_check_types(p, expr_type, typ);

      compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, typ);

      string before_oph = string_substr2(p->cgen->cur_line, 0, oph - 1, false);

      string after_oph = string_substr2(p->cgen->cur_line, oph, -1, true);

      p->cgen->cur_line =
          string_add(string_add(before_oph, tos3(",")), after_oph);

      compiler__TokenKind tmp20 = tok;

      if (tmp20 == compiler__compiler__TokenKind_mul) {

        compiler__Parser_handle_operator(
            p, tos3("*"), typ, tos3("op_mul"), ph,
            &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ T);

      } else if (tmp20 == compiler__compiler__TokenKind_div) {

        compiler__Parser_handle_operator(
            p, tos3("/"), typ, tos3("op_div"), ph,
            &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ T);

      } else if (tmp20 == compiler__compiler__TokenKind_mod) {

        compiler__Parser_handle_operator(
            p, tos3("%"), typ, tos3("op_mod"), ph,
            &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ T);
      };

      continue;
    };

    if (is_mod) {

      if (!(compiler__is_integer_type(expr_type) &&
            compiler__is_integer_type(typ))) {

        compiler__Parser_error(p,
                               tos3("operator `mod` requires integer types"));
      };

    } else {

      compiler__Parser_check_types(p, expr_type, typ);
    };
  };

  return typ;
}
string compiler__Parser_unary(compiler__Parser *p) {

  string typ = tos3("");

  compiler__TokenKind tok = p->tok;

  compiler__TokenKind tmp21 = tok;

  if (tmp21 == compiler__compiler__TokenKind_not) {

    compiler__Parser_gen(p, tos3("!"));

    compiler__Parser_check(p, compiler__compiler__TokenKind_not);

    typ = compiler__Parser_indot_expr(p);

    if (string_ne(typ, tos3("bool"))) {

      compiler__Parser_error(
          p,
          _STR("operator ! requires bool type, not `%.*s`", typ.len, typ.str));
    };

  } else if (tmp21 == compiler__compiler__TokenKind_bit_not) {

    compiler__Parser_gen(p, tos3("~"));

    compiler__Parser_check(p, compiler__compiler__TokenKind_bit_not);

    typ = compiler__Parser_bool_expression(p);

  } else // default:
  {

    typ = compiler__Parser_factor(p);
  };

  return typ;
}
string compiler__Parser_factor(compiler__Parser *p) {

  string typ = tos3("");

  compiler__TokenKind tok = p->tok;

  compiler__TokenKind tmp22 = tok;

  if (tmp22 == compiler__compiler__TokenKind_key_none) {

    if (!string_starts_with(p->expected_type, tos3("Option_"))) {

      compiler__Parser_error(p,
                             _STR("need \"%.*s\" got none",
                                  p->expected_type.len, p->expected_type.str));
    };

    compiler__Parser_gen(p, tos3("opt_none()"));

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_none);

    return p->expected_type;

  } else if (tmp22 == compiler__compiler__TokenKind_number) {

    typ = tos3("int");

    if ((string_contains(p->lit, tos3(".")) ||
         (string_contains(p->lit, tos3("e")) ||
          string_contains(p->lit, tos3("E")))) &&
        !(string_at(p->lit, 0) == '0' &&
          (string_at(p->lit, 1) == 'x' || string_at(p->lit, 1) == 'X'))) {

      typ = tos3("f32");

    } else {

      u64 v_u64 = string_u64(p->lit);

      if (((u64)(((u32)(v_u64)))) < v_u64) {

        typ = tos3("u64");
      };
    };

    if (string_ne(p->expected_type, tos3("")) &&
        !compiler__is_valid_int_const(p->lit, p->expected_type)) {

      compiler__Parser_error(
          p, _STR("constant `%.*s` overflows `%.*s`", p->lit.len, p->lit.str,
                  p->expected_type.len, p->expected_type.str));
    };

    compiler__Parser_gen(p, p->lit);

    ;

  } else if (tmp22 == compiler__compiler__TokenKind_minus) {

    compiler__Parser_gen(p, tos3("-"));

    ;

    compiler__Parser_next(p);

    return compiler__Parser_factor(p);

  } else if (tmp22 == compiler__compiler__TokenKind_key_sizeof) {

    compiler__Parser_gen(p, tos3("sizeof("));

    ;

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    string sizeof_typ = compiler__Parser_get_type(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    compiler__Parser_gen(p, _STR("%.*s)", sizeof_typ.len, sizeof_typ.str));

    ;

    return tos3("int");

  } else if ((tmp22 == compiler__compiler__TokenKind_amp) ||
             (tmp22 == compiler__compiler__TokenKind_dot) ||
             (tmp22 == compiler__compiler__TokenKind_mul)) {

    return compiler__Parser_name_expr(p);

  } else if (tmp22 == compiler__compiler__TokenKind_name) {

    if (string_eq(p->lit, tos3("map")) &&
        compiler__Parser_peek(&/* ? */ *p) ==
            compiler__compiler__TokenKind_lsbr) {

      return compiler__Parser_map_init(p);
    };

    if (string_eq(p->lit, tos3("json")) &&
        compiler__Parser_peek(&/* ? */ *p) ==
            compiler__compiler__TokenKind_dot) {

      if (!((_IN(string, (tos3("json")), p->table->imports)))) {

        compiler__Parser_error(p, tos3("undefined: `json`, use `import json`"));
      };

      compiler__ImportTable_register_used_import(&/* ? */ p->import_table,
                                                 tos3("json"));

      return compiler__Parser_js_decode(p);
    };

    typ = compiler__Parser_name_expr(p);

    return typ;

  } else if (tmp22 == compiler__compiler__TokenKind_lpar) {

    compiler__Parser_gen(p, tos3("("));

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    typ = compiler__Parser_bool_expression(p);

    if (!p->ptr_cast) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);
    };

    p->ptr_cast = 0;

    compiler__Parser_gen(p, tos3(")"));

    return typ;

  } else if (tmp22 == compiler__compiler__TokenKind_chartoken) {

    compiler__Parser_char_expr(p);

    typ = tos3("byte");

    return typ;

  } else if (tmp22 == compiler__compiler__TokenKind_str) {

    compiler__Parser_string_expr(p);

    typ = tos3("string");

    return typ;

  } else if (tmp22 == compiler__compiler__TokenKind_key_false) {

    typ = tos3("bool");

    compiler__Parser_gen(p, tos3("0"));

    ;

  } else if (tmp22 == compiler__compiler__TokenKind_key_true) {

    typ = tos3("bool");

    compiler__Parser_gen(p, tos3("1"));

    ;

  } else if (tmp22 == compiler__compiler__TokenKind_lsbr) {

    return compiler__Parser_array_init(p);

  } else if (tmp22 == compiler__compiler__TokenKind_lcbr) {

    if (compiler__Parser_peek(&/* ? */ *p) ==
        compiler__compiler__TokenKind_str) {

      return compiler__Parser_map_init(p);
    };

    return compiler__Parser_assoc(p);

  } else if (tmp22 == compiler__compiler__TokenKind_key_if) {

    typ = compiler__Parser_if_st(p, 1, 0);

    return typ;

  } else if (tmp22 == compiler__compiler__TokenKind_key_match) {

    typ = compiler__Parser_match_statement(p, 1);

    return typ;

  } else // default:
  {

    if (p->pref->is_verbose || p->pref->is_debug) {

      compiler__TokenKind next = compiler__Parser_peek(&/* ? */ *p);

      printf("prev=%.*s\n", compiler__TokenKind_str(p->prev_tok).len,
             compiler__TokenKind_str(p->prev_tok).str);

      printf("next=%.*s\n", compiler__TokenKind_str(next).len,
             compiler__TokenKind_str(next).str);
    };

    compiler__Parser_error(p, _STR("unexpected token: `%.*s`",
                                   compiler__TokenKind_str(p->tok).len,
                                   compiler__TokenKind_str(p->tok).str));
  };

  compiler__Parser_next(p);

  return typ;
}
string array_compiler__TypeInst_str(array_compiler__TypeInst a) {

  array_string r = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__TypeInst tmp1 = a;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    compiler__TypeInst t = ((compiler__TypeInst *)tmp1.data)[tmp2];

    string s = tos3(" | ");

    array_string tmp3 = map_keys(&/* ? */ t.inst);
    for (int tmp4 = 0; tmp4 < tmp3.len; tmp4++) {
      string k = ((string *)tmp3.data)[tmp4];

      string tmp5 = tos3("");
      bool tmp6 = map_get(/*fn.v : 66*/ t.inst, k, &tmp5);

      if (!tmp6)
        tmp5 = tos((byte *)"", 0);

      s = string_add(s,
                     string_add(string_add(string_add(k, tos3(" -> ")), tmp5),
                                tos3(" | ")));
    };

    _PUSH(&r, (/*typ = array_string   tmp_typ=string*/ s), tmp7, string);
  };

  return array_string_str(r);
}
Option_compiler__Var compiler__Parser_find_var(compiler__Parser *p,
                                               string name) {

  int tmp8 = 0;
  ;
  for (int tmp9 = tmp8; tmp9 < p->var_idx; tmp9++) {
    int i = tmp9;

    if (string_eq((*(compiler__Var *)array_get(p->local_vars, i)).name, name)) {

      compiler__Var tmp14 = OPTION_CAST(compiler__Var)(
          (*(compiler__Var *)array_get(p->local_vars, i)));
      return opt_ok(&tmp14, sizeof(compiler__Var));
    };
  };

  return opt_none();
}
Option_compiler__Var
compiler__Parser_find_var_check_new_var(compiler__Parser *p, string name) {

  int tmp15 = 0;
  ;
  for (int tmp16 = tmp15; tmp16 < p->var_idx; tmp16++) {
    int i = tmp16;

    if (string_eq((*(compiler__Var *)array_get(p->local_vars, i)).name, name)) {

      compiler__Var tmp21 = OPTION_CAST(compiler__Var)(
          (*(compiler__Var *)array_get(p->local_vars, i)));
      return opt_ok(&tmp21, sizeof(compiler__Var));
    };
  };

  if (string_eq(name, string_add(tos3("main__"), p->var_decl_name))) {

    compiler__Var tmp22 = OPTION_CAST(compiler__Var)(
        (compiler__Var){.name = p->var_decl_name,
                        .typ = tos3("voidptr"),
                        .is_mut = 1,
                        .idx = 0,
                        .is_arg = 0,
                        .is_const = 0,
                        .args = new_array(0, 1, sizeof(compiler__Var)),
                        .attr = tos3(""),
                        .is_alloc = 0,
                        .is_returned = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos3(""),
                        .mod = tos3(""),
                        .is_global = 0,
                        .is_used = 0,
                        .is_changed = 0,
                        .scope_level = 0,
                        .is_c = 0,
                        .is_moved = 0,
                        .line_nr = 0,
                        .token_idx = 0,
                        .is_for_var = 0,
                        .is_public = 0});
    return opt_ok(&tmp22, sizeof(compiler__Var));
  };

  return opt_none();
}
void compiler__Parser_open_scope(compiler__Parser *p) {

  _PUSH(&p->cur_fn.defer_text,
        (/*typ = array_string   tmp_typ=string*/ tos3("")), tmp23, string);

  p->cur_fn.scope_level++;
}
void compiler__Parser_mark_var_used(compiler__Parser *p, compiler__Var v) {

  if (v.idx == -1 || v.idx >= p->local_vars.len) {

    return;
  };

  (*(compiler__Var *)array_get(p->local_vars, v.idx)).is_used = 1;
}
void compiler__Parser_mark_var_returned(compiler__Parser *p, compiler__Var v) {

  if (v.idx == -1 || v.idx >= p->local_vars.len) {

    return;
  };

  (*(compiler__Var *)array_get(p->local_vars, v.idx)).is_returned = 1;
}
void compiler__Parser_mark_var_changed(compiler__Parser *p, compiler__Var v) {

  if (v.idx == -1 || v.idx >= p->local_vars.len) {

    return;
  };

  (*(compiler__Var *)array_get(p->local_vars, v.idx)).is_changed = 1;
}
void compiler__Parser_mark_arg_moved(compiler__Parser *p, compiler__Var v) {

  array_compiler__Var tmp30 = p->cur_fn.args;
  for (int i = 0; i < tmp30.len; i++) {
    compiler__Var arg = ((compiler__Var *)tmp30.data)[i];

    if (string_eq(arg.name, v.name)) {

      (*(compiler__Var *)array_get(p->cur_fn.args, i)).is_moved = 1;

      break;
    };
  };

  map_set(&p->table->fns, p->cur_fn.name, &(compiler__Fn[]){p->cur_fn});
}
bool compiler__Parser_known_var(compiler__Parser *p, string name) {

  Option_compiler__Var tmp33 = compiler__Parser_find_var(&/* ? */ *p, name);
  if (!tmp33.ok) {
    string err = tmp33.error;
    int errcode = tmp33.ecode;

    return 0;
  };

  return 1;
}
bool compiler__Parser_known_var_check_new_var(compiler__Parser *p,
                                              string name) {

  Option_compiler__Var tmp34 =
      compiler__Parser_find_var_check_new_var(&/* ? */ *p, name);
  if (!tmp34.ok) {
    string err = tmp34.error;
    int errcode = tmp34.ecode;

    return 0;
  };

  return 1;
}
void compiler__Parser_register_var(compiler__Parser *p, compiler__Var v) {

  compiler__Var new_var = (compiler__Var){
      .idx = p->var_idx,
      .scope_level = p->cur_fn.scope_level,
      .typ = v.typ,
      .name = v.name,
      .is_arg = v.is_arg,
      .is_const = v.is_const,
      .args = v.args,
      .attr = v.attr,
      .is_mut = v.is_mut,
      .is_alloc = v.is_alloc,
      .is_returned = v.is_returned,
      .ptr = v.ptr,
      .ref = v.ref,
      .parent_fn = v.parent_fn,
      .mod = v.mod,
      .access_mod = v.access_mod,
      .is_global = v.is_global,
      .is_used = v.is_used,
      .is_changed = v.is_changed,
      .is_c = v.is_c,
      .is_moved = v.is_moved,
      .line_nr = v.line_nr,
      .token_idx = v.token_idx,
      .is_for_var = v.is_for_var,
      .is_public = v.is_public,
  };

  if (v.line_nr == 0) {

    new_var.token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

    new_var.line_nr = compiler__Parser_cur_tok(&/* ? */ *p).line_nr;
  };

  if (p->var_idx >= p->local_vars.len) {

    _PUSH(&p->local_vars,
          (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ new_var),
          tmp35, compiler__Var);

  } else {

    array_set(&/*q*/ p->local_vars, p->var_idx, &(compiler__Var[]){new_var});
  };

  p->var_idx++;
}
void compiler__Parser_clear_vars(compiler__Parser *p) {

  p->var_idx = 0;

  if (p->local_vars.len > 0) {

    if (p->pref->autofree) {
    };

    p->local_vars = new_array_from_c_array(
        0, 0, sizeof(compiler__Var),
        EMPTY_ARRAY_OF_ELEMS(compiler__Var, 0){TCCSKIP(0)});
  };
}
void compiler__Parser_fn_decl(compiler__Parser *p) {

  compiler__Parser_clear_vars(p);

  ;

  bool is_pub = p->tok == compiler__compiler__TokenKind_key_pub;

  compiler__Fn f = (compiler__Fn){
      .mod = p->mod,
      .is_public = is_pub || p->is_vh,
      .is_unsafe = string_eq(p->attr, tos3("unsafe_fn")),
      .is_deprecated = string_eq(p->attr, tos3("deprecated")),
      .comptime_define = (string_starts_with(p->attr, tos3("if ")))
                             ? (string_right(p->attr, 3))
                             : (tos3("")),
      .name = tos3(""),
      .args = new_array(0, 1, sizeof(compiler__Var)),
      .is_interface = 0,
      .scope_level = 0,
      .typ = tos3(""),
      .receiver_typ = tos3(""),
      .is_c = 0,
      .is_method = 0,
      .is_decl = 0,
      .is_variadic = 0,
      .is_generic = 0,
      .returns_error = 0,
      .defer_text = new_array(0, 1, sizeof(string)),
      .type_pars = new_array(0, 1, sizeof(string)),
      .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
      .body_idx = 0,
      .fn_name_token_idx = 0,
      .is_used = 0};

  bool is_live =
      string_eq(p->attr, tos3("live")) && !p->pref->is_so && p->pref->is_live;

  if (string_eq(p->attr, tos3("live")) &&
      compiler__Parser_first_pass(&/* ? */ *p) && !p->pref->is_live &&
      !p->pref->is_so) {

    println(tos3(
        "INFO: run `v -live program.v` if you want to use [live] functions"));
  };

  if (is_pub) {

    compiler__Parser_next(p);
  };

  p->returns = 0;

  compiler__Parser_next(p);

  string receiver_typ = tos3("");

  if (p->tok == compiler__compiler__TokenKind_lpar) {

    f.is_method = 1;

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    string receiver_name = compiler__Parser_check_name(p);

    bool is_mut = p->tok == compiler__compiler__TokenKind_key_mut;

    bool is_amp = p->tok == compiler__compiler__TokenKind_amp;

    if (is_mut || is_amp) {

      compiler__Parser_check_space(p, p->tok);
    };

    receiver_typ = compiler__Parser_get_type(p);

    compiler__Type t =
        compiler__Table_find_type(&/* ? */ *p->table, receiver_typ);

    if ((string_eq(t.name, tos3("")) || t.is_placeholder) &&
        !compiler__Parser_first_pass(&/* ? */ *p)) {

      compiler__Parser_error(p, _STR("unknown receiver type `%.*s`",
                                     receiver_typ.len, receiver_typ.str));
    };

    if (t.cat == compiler__compiler__TypeCategory_interface_) {

      compiler__Parser_error(
          p, _STR("invalid receiver type `%.*s` (`%.*s` is an interface)",
                  receiver_typ.len, receiver_typ.str, receiver_typ.len,
                  receiver_typ.str));
    };

    if (!compiler__Parser_first_pass(&/* ? */ *p) && !p->builtin_mod &&
        string_ne(t.mod, p->mod) && !p->is_vgen) {

      compiler__Parser_error(
          p, _STR("cannot define new methods on non-local type `%.*s`",
                  receiver_typ.len, receiver_typ.str));
    };

    if (string_ends_with(receiver_typ, tos3("*"))) {

      string tt = string_replace(receiver_typ, tos3("*"), tos3(""));

      compiler__Parser_error(
          p, _STR("use `(%.*s mut %.*s)` instead of `(%.*s *%.*s)`",
                  receiver_name.len, receiver_name.str, tt.len, tt.str,
                  receiver_name.len, receiver_name.str, tt.len, tt.str));
    };

    f.receiver_typ = receiver_typ;

    if (is_mut || is_amp) {

      receiver_typ = string_add(receiver_typ, tos3("*"));
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    ;

    compiler__Var receiver = (compiler__Var){
        .name = receiver_name,
        .is_arg = 1,
        .typ = receiver_typ,
        .is_mut = is_mut,
        .ref = is_amp,
        .ptr = is_mut,
        .line_nr = p->scanner->line_nr,
        .token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p),
        .idx = 0,
        .is_const = 0,
        .args = new_array(0, 1, sizeof(compiler__Var)),
        .attr = tos3(""),
        .is_alloc = 0,
        .is_returned = 0,
        .parent_fn = tos3(""),
        .mod = tos3(""),
        .is_global = 0,
        .is_used = 0,
        .is_changed = 0,
        .scope_level = 0,
        .is_c = 0,
        .is_moved = 0,
        .is_for_var = 0,
        .is_public = 0};

    _PUSH(&f.args,
          (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ receiver),
          tmp36, compiler__Var);

    compiler__Parser_register_var(p, receiver);
  };

  if (p->tok == compiler__compiler__TokenKind_plus ||
      p->tok == compiler__compiler__TokenKind_minus ||
      p->tok == compiler__compiler__TokenKind_mul ||
      p->tok == compiler__compiler__TokenKind_div ||
      p->tok == compiler__compiler__TokenKind_mod) {

    f.name = compiler__TokenKind_str(p->tok);

    compiler__Parser_next(p);

  } else {

    f.name = compiler__Parser_check_name(p);
  };

  f.fn_name_token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

  if (string_eq(f.name, tos3("init")) && !f.is_method && f.is_public &&
      !p->is_vh) {

    compiler__Parser_error(p, tos3("init function cannot be public"));
  };

  bool is_c = string_eq(f.name, tos3("C")) &&
              p->tok == compiler__compiler__TokenKind_dot;

  if (p->is_vh) {
  };

  if (is_c) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    f.name = compiler__Parser_check_name(p);

    f.is_c = 1;

  } else if (!p->pref->translated) {

    if (compiler__contains_capital(f.name) &&
        !compiler__Parser_fileis(&/* ? */ *p, tos3("view.v"))) {

      printf("`%.*s`\n", f.name.len, f.name.str);

      compiler__Parser_error(p, tos3("function names cannot contain uppercase "
                                     "letters, use snake_case instead"));
    };

    if (string_at(f.name, 0) == '_') {

      compiler__Parser_error(
          p,
          tos3("function names cannot start with `_`, use snake_case instead"));
    };

    if (string_contains(f.name, tos3("__"))) {

      compiler__Parser_error(
          p, tos3("function names cannot contain double underscores, use "
                  "single underscores instead"));
    };
  };

  bool has_receiver = receiver_typ.len > 0;

  if (string_ne(receiver_typ, tos3(""))) {
  };

  if (!is_c && !has_receiver &&
      (!p->builtin_mod ||
       (p->builtin_mod && string_eq(f.name, tos3("init"))))) {

    f.name = compiler__Parser_prepend_mod(&/* ? */ *p, f.name);
  };

  if (compiler__Parser_first_pass(&/* ? */ *p) && receiver_typ.len == 0) {

    Option_compiler__Fn tmp39 =
        compiler__Table_find_fn(&/* ? */ *p->table, f.name);

    if (tmp39.ok) {
      compiler__Fn existing_fn = *(compiler__Fn *)tmp39.data;

      if (!existing_fn.is_decl) {

        compiler__Parser_error(
            p, _STR("redefinition of `%.*s`", f.name.len, f.name.str));
      };
    };
  };

  if (p->tok == compiler__compiler__TokenKind_lt) {

    f.is_generic = 1;

    compiler__Parser_next(p);

    while (1) {

      string type_par = compiler__Parser_check_name(p);

      if (type_par.len > 1 ||
          !((_IN(string, (type_par), compiler__reserved_type_param_names)))) {

        string tmp40 = array_string_str(compiler__reserved_type_param_names);

        compiler__Parser_error(
            p, _STR("type parameters must be single-character, upper-case "
                    "letters of the following set: %.*s ",
                    tmp40.len, tmp40.str));
      };

      if ((_IN(string, (type_par), f.type_pars))) {

        compiler__Parser_error(p, _STR("redeclaration of type parameter `%.*s`",
                                       type_par.len, type_par.str));
      };

      _PUSH(&f.type_pars, (/*typ = array_string   tmp_typ=string*/ type_par),
            tmp41, string);

      if (p->tok == compiler__compiler__TokenKind_gt) {

        break;
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
    };

    compiler__Parser_set_current_fn(p, f);

    compiler__Parser_check(p, compiler__compiler__TokenKind_gt);
  };

  compiler__Parser_fn_args(p,
                           &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f);

  if (p->tok == compiler__compiler__TokenKind_not) {

    compiler__Parser_next(p);

    f.returns_error = 1;
  };

  string typ = tos3("void");

  if (p->tok == compiler__compiler__TokenKind_name ||
      p->tok == compiler__compiler__TokenKind_mul ||
      p->tok == compiler__compiler__TokenKind_amp ||
      p->tok == compiler__compiler__TokenKind_lsbr ||
      p->tok == compiler__compiler__TokenKind_question ||
      p->tok == compiler__compiler__TokenKind_lpar) {

    ;

    typ = compiler__Parser_get_type(p);
  };

  bool is_fn_header =
      !is_c && !p->is_vh && p->tok != compiler__compiler__TokenKind_lcbr;

  if (is_fn_header) {

    f.is_decl = 1;
  };

  if (!is_c && !p->is_vh && !is_fn_header) {

    ;

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);
  };

  if (string_starts_with(typ, tos3("Option_"))) {

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR("typedef Option %.*s;",
                                                        typ.len, typ.str)),
          tmp42, string);
  };

  f.typ = typ;

  string str_args = compiler__Fn_str_args(&/* ? */ f, p->table);

  if (string_eq(f.name, tos3("main__main")) && !has_receiver) {

    if (string_ne(str_args, tos3("")) || string_ne(typ, tos3("void"))) {

      compiler__Parser_error_with_token_index(
          p, tos3("fn main must have no arguments and no return values"),
          f.fn_name_token_idx);
    };
  };

  string dll_export_linkage = compiler__Parser_get_linkage_prefix(*p);

  if (!p->is_vweb) {

    compiler__Parser_set_current_fn(p, f);
  };

  string fn_name_cgen = compiler__Table_fn_gen_name(
      p->table, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f);

  bool skip_main_in_test = 0;

  if (!is_c && !is_live && !p->is_vh && !is_fn_header && !skip_main_in_test) {

    if (p->pref->obfuscate) {

      compiler__Parser_genln(p, _STR("; // %.*s", f.name.len, f.name.str));
    };

    if (f.is_generic) {

      if (compiler__Parser_first_pass(&/* ? */ *p)) {

        f.body_idx = compiler__Parser_cur_tok_index(&/* ? */ *p) + 1;

        if (f.is_method) {

          compiler__Type rcv =
              compiler__Table_find_type(&/* ? */ *p->table, receiver_typ);

          if (compiler__Parser_first_pass(&/* ? */ *p) &&
              string_eq(rcv.name, tos3(""))) {

            compiler__Type r = (compiler__Type){
                .name = string_replace(rcv.name, tos3("*"), tos3("")),
                .mod = p->mod,
                .is_placeholder = 1,
                .is_public = 0,
                .fields = new_array(0, 1, sizeof(compiler__Var)),
                .methods = new_array(0, 1, sizeof(compiler__Fn)),
                .parent = tos3(""),
                .is_c = 0,
                .enum_vals = new_array(0, 1, sizeof(string)),
                .gen_types = new_array(0, 1, sizeof(string)),
                .gen_str = 0};

            compiler__Table_register_type2(p->table, r);
          };

          compiler__Parser_add_method(p, rcv.name, f);

        } else {

          compiler__Table_register_fn(p->table, f);
        };
      };

      if (f.is_method) {

        compiler__Parser_mark_var_changed(
            p, (*(compiler__Var *)array_get(f.args, 0)));
      };

      compiler__Parser_check_unused_variables(p);

      compiler__Parser_set_current_fn(p, compiler__EmptyFn);

      p->returns = 0;

      compiler__Parser_skip_fn_body(p);

      return;

    } else {

      compiler__Parser_gen_fn_decl(p, f, typ, str_args);
    };
  };

  if (is_fn_header) {

    compiler__Parser_genln(p, _STR("%.*s %.*s(%.*s);", typ.len, typ.str,
                                   fn_name_cgen.len, fn_name_cgen.str,
                                   str_args.len, str_args.str));

    ;
  };

  if (is_c) {

    ;
  };

  if (string_ne(receiver_typ, tos3(""))) {

    compiler__Type receiver_t =
        compiler__Table_find_type(&/* ? */ *p->table, receiver_typ);

    if (compiler__Parser_first_pass(&/* ? */ *p) &&
        string_eq(receiver_t.name, tos3(""))) {

      receiver_t = (compiler__Type){
          .name = string_replace(receiver_typ, tos3("*"), tos3("")),
          .mod = p->mod,
          .is_placeholder = 1,
          .is_public = 0,
          .fields = new_array(0, 1, sizeof(compiler__Var)),
          .methods = new_array(0, 1, sizeof(compiler__Fn)),
          .parent = tos3(""),
          .is_c = 0,
          .enum_vals = new_array(0, 1, sizeof(string)),
          .gen_types = new_array(0, 1, sizeof(string)),
          .gen_str = 0};

      compiler__Table_register_type2(p->table, receiver_t);
    };

    compiler__Parser_add_method(p, receiver_t.name, f);

  } else if (compiler__Parser_first_pass(&/* ? */ *p)) {

    compiler__Table_register_fn(p->table, f);
  };

  if (p->is_vh || compiler__Parser_first_pass(&/* ? */ *p) || is_live ||
      is_fn_header || skip_main_in_test) {

    if (!p->is_vh && !is_fn_header) {

      compiler__Parser_skip_fn_body(p);
    };

    if (is_live && compiler__Parser_first_pass(&/* ? */ *p) &&
        string_eq(p->mod, tos3("main"))) {

      _PUSH(&p->cgen->so_fns,
            (/*typ = array_string   tmp_typ=string*/ fn_name_cgen), tmp45,
            string);

      fn_name_cgen = _STR("(* %.*s )", fn_name_cgen.len, fn_name_cgen.str);
    };

    string fn_decl =
        _STR("%.*s%.*s %.*s(%.*s)", dll_export_linkage.len,
             dll_export_linkage.str, typ.len, typ.str, fn_name_cgen.len,
             fn_name_cgen.str, str_args.len, str_args.str);

    if (p->pref->obfuscate) {

      fn_decl = string_add(fn_decl, _STR("; // %.*s", f.name.len, f.name.str));
    };

    if (!is_c && compiler__Parser_first_pass(&/* ? */ *p)) {

      _PUSH(&p->cgen->fns,
            (/*typ = array_string   tmp_typ=string*/ string_add(fn_decl,
                                                                tos3(";"))),
            tmp46, string);
    };

    return;
  };

  if (string_eq(p->attr, tos3("live")) && p->pref->is_so) {

    compiler__Parser_genln(p, tos3("pthread_mutex_lock(&live_fn_mutex);"));
  };

  if (string_eq(f.name, tos3("main__main")) ||
      string_eq(f.name, tos3("main")) || string_eq(f.name, tos3("WinMain"))) {

    if (p->pref->is_test) {

      compiler__Parser_error_with_token_index(
          p, tos3("tests cannot have function `main`"), f.fn_name_token_idx);
    };
  };

  if (is_c || p->is_vh || is_fn_header) {

    return;
  };

  if (p->pref->is_prof && string_ne(f.name, tos3("time__ticks"))) {

    compiler__Parser_genln(p, _STR("double _PROF_START = time__ticks();//%.*s",
                                   f.name.len, f.name.str));

    string cgen_name = compiler__Table_fn_gen_name(
        p->table, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f);

    if (f.defer_text.len > f.scope_level) {

      array_set(&/*q*/ f.defer_text, f.scope_level,
                &(string[]){_STR("  %.*s_time += time__ticks() - _PROF_START;",
                                 cgen_name.len, cgen_name.str)});
    };
  };

  compiler__Parser_statements_no_rcbr(p);

  if (p->pref->is_prof && string_eq(f.name, tos3("main"))) {

    compiler__Parser_genln(p,
                           compiler__Parser_print_prof_counters(&/* ? */ *p));
  };

  if (!p->is_vweb) {

    if (f.defer_text.len > f.scope_level) {

      compiler__Parser_genln(
          p, (*(string *)array_get(f.defer_text, f.scope_level)));
    };
  };

  if (string_ne(typ, tos3("void")) && !p->returns) {

    compiler__Parser_error_with_token_index(p,
                                            _STR("%.*s must return \"%.*s\"",
                                                 f.name.len, f.name.str,
                                                 typ.len, typ.str),
                                            f.fn_name_token_idx);
  };

  if (string_eq(p->attr, tos3("live")) && p->pref->is_so) {

    compiler__Parser_genln(p, tos3("pthread_mutex_unlock(&live_fn_mutex);"));
  };

  if (string_eq(p->mod, tos3("main"))) {
  };

  if (p->cur_fn.scope_level > 2) {
  };

  if (string_ne(p->mod, tos3("main"))) {

    compiler__Parser_genln(p, tos3("}"));

    return;
  };

  compiler__Parser_genln(p, tos3("}"));

  compiler__Parser_check_unused_variables(p);

  compiler__Parser_set_current_fn(p, compiler__EmptyFn);

  p->returns = 0;
}
static inline void compiler__Parser_skip_fn_body(compiler__Parser *p) {

  int opened_scopes = 0;

  int closed_scopes = 0;

  while (1) {

    if (p->tok == compiler__compiler__TokenKind_lcbr) {

      opened_scopes++;
    };

    if (p->tok == compiler__compiler__TokenKind_rcbr) {

      closed_scopes++;
    };

    if (compiler__TokenKind_is_decl(p->tok)) {

      break;
    };

    if (closed_scopes > opened_scopes &&
        p->prev_tok == compiler__compiler__TokenKind_rcbr) {

      if (p->tok == compiler__compiler__TokenKind_lsbr) {

        break;
      };
    };

    compiler__Parser_next(p);
  };
}
string compiler__Parser_get_linkage_prefix(compiler__Parser p) {

  return (string_eq(p.pref->ccompiler, tos3("msvc")) &&
          string_eq(p.attr, tos3("live")) && p.pref->is_so)
             ? (tos3("__declspec(dllexport) "))
             : ((string_eq(p.attr, tos3("inline"))) ? (tos3("static inline "))
                                                    : (tos3("")));
}
void compiler__Parser_check_unused_variables(compiler__Parser *p) {

  array_compiler__Var tmp49 = p->local_vars;
  for (int tmp50 = 0; tmp50 < tmp49.len; tmp50++) {
    compiler__Var var = ((compiler__Var *)tmp49.data)[tmp50];

    if (string_eq(var.name, tos3(""))) {

      break;
    };

    if (!var.is_used && !p->pref->is_repl && !var.is_arg &&
        !p->pref->translated) {

      compiler__Parser_production_error_with_token_index(
          p, _STR("`%.*s` declared and not used", var.name.len, var.name.str),
          var.token_idx);
    };

    if (!var.is_changed && var.is_mut && !p->pref->is_repl &&
        !p->pref->translated && string_ne(var.typ, tos3("T*"))) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("`%.*s` is declared as mutable, but it was never changed",
               var.name.len, var.name.str),
          var.token_idx);
    };
  };
}
void compiler__Parser_async_fn_call(compiler__Parser *p, compiler__Fn f,
                                    int method_ph, string receiver_var,
                                    string receiver_type) {

  string thread_name = tos3("");

  string fn_name = f.name;

  if (f.is_method) {

    fn_name = string_add(
        string_add(string_replace(receiver_type, tos3("*"), tos3("")),
                   tos3("_")),
        f.name);
  };

  string arg_struct_name = _STR("thread_arg_%.*s", fn_name.len, fn_name.str);

  string tmp_struct = compiler__Parser_get_tmp(p);

  compiler__Parser_genln(p, _STR("%.*s * %.*s = malloc(sizeof(%.*s));",
                                 arg_struct_name.len, arg_struct_name.str,
                                 tmp_struct.len, tmp_struct.str,
                                 arg_struct_name.len, arg_struct_name.str));

  string arg_struct = _STR("typedef struct  %.*s   { ", arg_struct_name.len,
                           arg_struct_name.str);

  compiler__Parser_next(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  string str_args = tos3("");

  bool did_gen_something = 0;

  array_compiler__Var tmp51 = f.args;
  for (int i = 0; i < tmp51.len; i++) {
    compiler__Var arg = ((compiler__Var *)tmp51.data)[i];

    arg_struct =
        string_add(arg_struct, _STR("%.*s %.*s ;", arg.typ.len, arg.typ.str,
                                    arg.name.len, arg.name.str));

    str_args = string_add(str_args, _STR("arg %.*s %.*s", compiler__dot_ptr.len,
                                         compiler__dot_ptr.str, arg.name.len,
                                         arg.name.str));

    if (i == 0 && f.is_method) {

      compiler__Parser_genln(
          p, _STR("%.*s %.*s %.*s =  %.*s ;", tmp_struct.len, tmp_struct.str,
                  compiler__dot_ptr.len, compiler__dot_ptr.str, arg.name.len,
                  arg.name.str, receiver_var.len, receiver_var.str));

      if (i < f.args.len - 1) {

        str_args = string_add(str_args, tos3(","));
      };

      did_gen_something = 1;

      continue;
    };

    compiler__Parser_genln(p, _STR("%.*s %.*s %.*s =  ", tmp_struct.len,
                                   tmp_struct.str, compiler__dot_ptr.len,
                                   compiler__dot_ptr.str, arg.name.len,
                                   arg.name.str));

    compiler__Parser_expression(p);

    compiler__Parser_genln(p, tos3(";"));

    if (i < f.args.len - 1) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

      str_args = string_add(str_args, tos3(","));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    arg_struct = string_add(arg_struct, tos3("EMPTY_STRUCT_DECLARATION;"));
  };

  arg_struct = string_add(
      arg_struct, _STR("} %.*s ;", arg_struct_name.len, arg_struct_name.str));

  fn_name = compiler__Table_fn_gen_name(
      p->table, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f);

  string wrapper_name = _STR("%.*s_thread_wrapper", fn_name.len, fn_name.str);

  string wrapper_type = tos3("void*");

  if (p->os == compiler__compiler__OS_windows) {

    wrapper_type = tos3("void* __stdcall");
  };

  string wrapper_text =
      _STR("%.*s %.*s(%.*s * arg) {%.*s( /*f*/%.*s ); return NULL; }",
           wrapper_type.len, wrapper_type.str, wrapper_name.len,
           wrapper_name.str, arg_struct_name.len, arg_struct_name.str,
           fn_name.len, fn_name.str, str_args.len, str_args.str);

  compiler__CGen_register_thread_fn(p->cgen, wrapper_name, wrapper_text,
                                    arg_struct);

  int tmp_nr = compiler__Parser_get_tmp_counter(p);

  thread_name = _STR("_thread%d", tmp_nr);

  if (p->os != compiler__compiler__OS_windows) {

    compiler__Parser_genln(
        p, _STR("pthread_t %.*s;", thread_name.len, thread_name.str));
  };

  string tmp2 = compiler__Parser_get_tmp(p);

  string parg = tos3("NULL");

  if (f.args.len > 0) {

    parg = _STR(" %.*s", tmp_struct.len, tmp_struct.str);
  };

  if (p->os == compiler__compiler__OS_windows) {

    compiler__Parser_genln(p, _STR(" CreateThread(0,0, %.*s, %.*s, 0,0);",
                                   wrapper_name.len, wrapper_name.str, parg.len,
                                   parg.str));

  } else {

    compiler__Parser_genln(
        p, _STR("int %.*s = pthread_create(& %.*s, NULL, (void *)%.*s, %.*s);",
                tmp2.len, tmp2.str, thread_name.len, thread_name.str,
                wrapper_name.len, wrapper_name.str, parg.len, parg.str));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);
}
void compiler__Parser_fn_call(compiler__Parser *p, compiler__Fn *f,
                              int method_ph, string receiver_var,
                              string receiver_type) {

  if (f->is_unsafe && !p->builtin_mod && !p->inside_unsafe) {

    compiler__Parser_warn(
        p,
        tos3("you are calling an unsafe function outside of an unsafe block"));
  };

  if (f->is_deprecated) {

    compiler__Parser_warn(p,
                          _STR("%.*s is deprecated", f->name.len, f->name.str));
  };

  if (!f->is_public && !f->is_c && !p->pref->is_test && !f->is_interface &&
      string_ne(f->mod, p->mod)) {

    if (string_eq(f->name, tos3("contains"))) {

      println(
          tos3("use `value in numbers` instead of `numbers.contains(value)`"));
    };

    compiler__Parser_error(
        p, _STR("function `%.*s` is private", f->name.len, f->name.str));
  };

  bool is_comptime_define =
      string_ne(f->comptime_define, tos3("")) &&
      string_ne(f->comptime_define, p->pref->comptime_define);

  if (is_comptime_define) {

    p->cgen->nogen = 1;
  };

  p->calling_c = f->is_c;

  if (f->is_c && !p->builtin_mod) {

    if (string_eq(f->name, tos3("free"))) {

      compiler__Parser_error(p, tos3("use `free()` instead of `C.free()`"));

    } else if (string_eq(f->name, tos3("malloc"))) {

      compiler__Parser_error(p, tos3("use `malloc()` instead of `C.malloc()`"));
    };
  };

  f->is_used = 1;

  string cgen_name = compiler__Table_fn_gen_name(p->table, f);

  compiler__Parser_next(p);

  if (p->tok == compiler__compiler__TokenKind_lt) {

    int i = p->token_idx;

    while (1) {

      if ((*(compiler__Token *)array_get(p->tokens, i)).tok ==
          compiler__compiler__TokenKind_gt) {

        compiler__Parser_error(
            p, tos3("explicit type arguments are not allowed; remove `<...>`"));

      } else if ((*(compiler__Token *)array_get(p->tokens, i)).tok ==
                 compiler__compiler__TokenKind_lpar) {

        break;
      };

      i += 1;
    };
  };

  if (f->is_method) {

    compiler__Var receiver = *(compiler__Var *)array_first(f->args);

    if (receiver.is_mut && !p->expr_var.is_mut) {

      if (p->expr_var.is_for_var) {

        compiler__Parser_error(
            p, string_add(_STR("`%.*s` is immutable, `for` variables",
                               p->expr_var.name.len, p->expr_var.name.str),
                          tos3(" always are")));

      } else {

        compiler__Parser_error(
            p, _STR("`%.*s` is immutable, declare it with `mut`",
                    p->expr_var.name.len, p->expr_var.name.str));
      };
    };

    if (!p->expr_var.is_changed && receiver.is_mut) {

      compiler__Parser_mark_var_changed(p, p->expr_var);
    };

    compiler__Parser_gen_method_call(
        p, &/*112 EXP:"compiler__Var*" GOT:"compiler__Var" */ receiver,
        receiver_type, cgen_name, f->typ, method_ph);

  } else {

    compiler__Parser_gen(p, _STR("%.*s (", cgen_name.len, cgen_name.str));
  };

  bool generic = f->is_generic;

  compiler__Parser_fn_call_args(p, f);

  if (generic) {

    compiler__CGen_resetln(
        p->cgen, string_replace(p->cgen->cur_line,
                                _STR("%.*s (", cgen_name.len, cgen_name.str),
                                _STR("%.*s (", f->name.len, f->name.str)));
  };

  compiler__Parser_gen(p, tos3(")"));

  p->calling_c = 0;

  if (is_comptime_define) {

    p->cgen->nogen = 0;

    compiler__CGen_resetln(p->cgen, tos3(""));
  };
}
void compiler__Parser_fn_args(compiler__Parser *p, compiler__Fn *f) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  if (f->is_interface) {

    compiler__Var int_arg = (compiler__Var){
        .typ = f->receiver_typ,
        .token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p),
        .name = tos3(""),
        .idx = 0,
        .is_arg = 0,
        .is_const = 0,
        .args = new_array(0, 1, sizeof(compiler__Var)),
        .attr = tos3(""),
        .is_mut = 0,
        .is_alloc = 0,
        .is_returned = 0,
        .ptr = 0,
        .ref = 0,
        .parent_fn = tos3(""),
        .mod = tos3(""),
        .is_global = 0,
        .is_used = 0,
        .is_changed = 0,
        .scope_level = 0,
        .is_c = 0,
        .is_moved = 0,
        .line_nr = 0,
        .is_for_var = 0,
        .is_public = 0};

    _PUSH(&f->args,
          (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ int_arg),
          tmp56, compiler__Var);
  };

  bool types_only =
      p->tok == compiler__compiler__TokenKind_mul ||
      p->tok == compiler__compiler__TokenKind_amp ||
      (compiler__Parser_peek(&/* ? */ *p) ==
           compiler__compiler__TokenKind_comma &&
       compiler__Table_known_type(&/* ? */ *p->table, p->lit)) ||
      compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_rpar;

  if (types_only) {

    while (p->tok != compiler__compiler__TokenKind_rpar) {

      string typ = compiler__Parser_get_type(p);

      compiler__Parser_check_and_register_used_imported_type(p, typ);

      compiler__Var v = (compiler__Var){
          .typ = typ,
          .is_arg = 1,
          .line_nr = p->scanner->line_nr,
          .token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p),
          .name = tos3(""),
          .idx = 0,
          .is_const = 0,
          .args = new_array(0, 1, sizeof(compiler__Var)),
          .attr = tos3(""),
          .is_mut = 0,
          .is_alloc = 0,
          .is_returned = 0,
          .ptr = 0,
          .ref = 0,
          .parent_fn = tos3(""),
          .mod = tos3(""),
          .is_global = 0,
          .is_used = 0,
          .is_changed = 0,
          .scope_level = 0,
          .is_c = 0,
          .is_moved = 0,
          .is_for_var = 0,
          .is_public = 0};

      _PUSH(&f->args, (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ v),
            tmp57, compiler__Var);

      if (p->tok == compiler__compiler__TokenKind_comma) {

        compiler__Parser_next(p);
      };
    };
  };

  while (p->tok != compiler__compiler__TokenKind_rpar) {

    array_string names = new_array_from_c_array(
        1, 1, sizeof(string),
        EMPTY_ARRAY_OF_ELEMS(string, 1){compiler__Parser_check_name(p)});

    while (p->tok == compiler__compiler__TokenKind_comma) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

      ;

      _PUSH(
          &names,
          (/*typ = array_string   tmp_typ=string*/ compiler__Parser_check_name(
              p)),
          tmp58, string);
    };

    ;

    bool is_mut = p->tok == compiler__compiler__TokenKind_key_mut;

    if (is_mut) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_key_mut);
    };

    if (p->tok == compiler__compiler__TokenKind_ellipsis) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_ellipsis);

      if (p->tok == compiler__compiler__TokenKind_rpar) {

        compiler__Parser_error(
            p, tos3("you must provide a type for vargs: eg `...string`. "
                    "multiple types `...` are not supported yet."));
      };

      f->is_variadic = 1;
    };

    string typ = compiler__Parser_get_type(p);

    if (!compiler__Parser_first_pass(&/* ? */ *p) &&
        !compiler__Table_known_type(&/* ? */ *p->table, typ)) {

      compiler__Parser_error(
          p, _STR("fn_args: unknown type %.*s", typ.len, typ.str));
    };

    if (f->is_variadic) {

      if (!f->is_c) {

        if (compiler__Parser_first_pass(&/* ? */ *p) && !f->is_generic) {

          compiler__Parser_register_vargs_stuct(p, typ, 0);
        };

        typ = _STR("varg_%.*s", typ.len, typ.str);

      } else {

        typ = _STR("...%.*s", typ.len, typ.str);
      };
    };

    compiler__Parser_check_and_register_used_imported_type(p, typ);

    if (is_mut && compiler__is_primitive_type(typ)) {

      compiler__Parser_error(
          p, string_add(tos3("mutable arguments are only allowed for arrays, "
                             "maps, and structs."),
                        tos3("\nreturn values instead: `foo(n mut int)` => "
                             "`foo(n int) int`")));
    };

    array_string tmp59 = names;
    for (int tmp60 = 0; tmp60 < tmp59.len; tmp60++) {
      string name = ((string *)tmp59.data)[tmp60];

      if (is_mut) {

        typ = string_add(typ, tos3("*"));
      };

      compiler__Var v = (compiler__Var){
          .name = name,
          .typ = typ,
          .is_arg = 1,
          .is_mut = is_mut,
          .ptr = is_mut,
          .line_nr = p->scanner->line_nr,
          .token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p),
          .idx = 0,
          .is_const = 0,
          .args = new_array(0, 1, sizeof(compiler__Var)),
          .attr = tos3(""),
          .is_alloc = 0,
          .is_returned = 0,
          .ref = 0,
          .parent_fn = tos3(""),
          .mod = tos3(""),
          .is_global = 0,
          .is_used = 0,
          .is_changed = 0,
          .scope_level = 0,
          .is_c = 0,
          .is_moved = 0,
          .is_for_var = 0,
          .is_public = 0};

      compiler__Parser_register_var(p, v);

      _PUSH(&f->args, (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ v),
            tmp61, compiler__Var);
    };

    if (p->tok == compiler__compiler__TokenKind_comma) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
    };

    if (p->tok == compiler__compiler__TokenKind_ellipsis) {

      if (!f->is_c) {

        compiler__Parser_error(
            p, tos3("variadic argument syntax must be `arg_name ...type` eg "
                    "`argname ...string`."));
      };

      _PUSH(&f->args,
            (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ (
                compiler__Var){.typ = tos3("..."),
                               .name = tos3(""),
                               .idx = 0,
                               .is_arg = 0,
                               .is_const = 0,
                               .args = new_array(0, 1, sizeof(compiler__Var)),
                               .attr = tos3(""),
                               .is_mut = 0,
                               .is_alloc = 0,
                               .is_returned = 0,
                               .ptr = 0,
                               .ref = 0,
                               .parent_fn = tos3(""),
                               .mod = tos3(""),
                               .is_global = 0,
                               .is_used = 0,
                               .is_changed = 0,
                               .scope_level = 0,
                               .is_c = 0,
                               .is_moved = 0,
                               .line_nr = 0,
                               .token_idx = 0,
                               .is_for_var = 0,
                               .is_public = 0}),
            tmp62, compiler__Var);

      compiler__Parser_next(p);
    };
  };

  { compiler__Parser_check(p, compiler__compiler__TokenKind_rpar); }
}
void compiler__Parser_fn_call_args(compiler__Parser *p, compiler__Fn *f) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  if (f->is_c) {

    while (p->tok != compiler__compiler__TokenKind_rpar) {

      p->calling_c = 1;

      int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

      string typ = compiler__Parser_bool_expression(p);

      if (string_eq(typ, tos3("byte*"))) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("(char*)"));
      };

      if (p->tok == compiler__compiler__TokenKind_comma) {

        compiler__Parser_gen(p, tos3(", "));

        compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
      };
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    return;
  };

  if (p->v->pref->is_debug && string_eq(f->name, tos3("panic")) && !p->is_js) {

    string mod_name = string_replace(p->mod, tos3("_dot_"), tos3("."));

    string fn_name = string_replace(
        p->cur_fn.name, _STR("%.*s__", p->mod.len, p->mod.str), tos3(""));

    string file_path = compiler__cescaped_path(p->file_path);

    compiler__CGen_resetln(
        p->cgen, string_replace(p->cgen->cur_line, tos3("v_panic ("),
                                _STR("panic_debug (%d, tos3(\"%.*s\"), "
                                     "tos3(\"%.*s\"), tos2((byte *)\"%.*s\"), ",
                                     p->scanner->line_nr, file_path.len,
                                     file_path.str, mod_name.len, mod_name.str,
                                     fn_name.len, fn_name.str)));
  };

  array_string saved_args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__Var tmp63 = f->args;
  for (int i = 0; i < tmp63.len; i++) {
    compiler__Var arg = ((compiler__Var *)tmp63.data)[i];

    if (i == 0 && f->is_method) {

      if (f->args.len > 1) {

        compiler__Parser_gen(p, tos3(","));
      };

      continue;
    };

    if (i == f->args.len - 1 && string_starts_with(arg.typ, tos3("varg_"))) {

      break;
    };

    int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

    if (p->tok == compiler__compiler__TokenKind_rpar) {

      string str_args = compiler__Fn_str_args(&/* ? */ *f, p->table);

      compiler__Parser_error(
          p, _STR("not enough arguments in call to `%.*s (%.*s)`", f->name.len,
                  f->name.str, str_args.len, str_args.str));
    };

    if (arg.is_mut) {

      if (p->tok != compiler__compiler__TokenKind_key_mut &&
          p->tok == compiler__compiler__TokenKind_name) {

        string dots_example = _STR("mut %.*s", p->lit.len, p->lit.str);

        if (i > 0) {

          dots_example = string_add(tos3(".., "), dots_example);
        };

        if (i < f->args.len - 1) {

          dots_example = string_add(dots_example, tos3(",.."));
        };

        compiler__Parser_error(p, _STR("`%.*s` is a mutable argument, you need "
                                       "to provide `mut`: `%.*s(%.*s)`",
                                       arg.name.len, arg.name.str, f->name.len,
                                       f->name.str, dots_example.len,
                                       dots_example.str));
      };

      if (compiler__Parser_peek(&/* ? */ *p) !=
          compiler__compiler__TokenKind_name) {

        compiler__Parser_error(
            p, _STR("`%.*s` is a mutable argument, you need to provide a "
                    "variable to modify: `%.*s(... mut a...)`",
                    arg.name.len, arg.name.str, f->name.len, f->name.str));
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_key_mut);

      string var_name = p->lit;

      Option_compiler__Var tmp64 =
          compiler__Parser_find_var(&/* ? */ *p, var_name);
      compiler__Var v;
      if (!tmp64.ok) {
        string err = tmp64.error;
        int errcode = tmp64.ecode;

        compiler__Parser_error(
            p, _STR("`%.*s` is a mutable argument, you need to provide a "
                    "variable to modify: `%.*s(... mut a...)`",
                    arg.name.len, arg.name.str, f->name.len, f->name.str));

        v_exit(1);
      }
      v = *(compiler__Var *)tmp64.data;
      ;

      if (!v.is_changed) {

        compiler__Parser_mark_var_changed(p, v);
      };
    };

    p->expected_type = arg.typ;

    bool clone = p->pref->autofree && string_eq(arg.typ, tos3("string")) &&
                 arg.is_moved && string_ne(p->mod, tos3("builtin"));

    if (clone) {

      compiler__Parser_gen(
          p,
          _STR("/*YY f=%.*s arg=%.*s is_moved=%d*/string_clone(", f->name.len,
               f->name.str, arg.name.len, arg.name.str, arg.is_moved));
    };

    string typ = compiler__Parser_bool_expression(p);

    if (clone) {

      compiler__Parser_gen(p, tos3(")"));
    };

    if (i == 0 &&
        (string_eq(f->name, tos3("println")) ||
         string_eq(f->name, tos3("print"))) &&
        string_eq(typ, tos3("ustring"))) {

      if (string_eq(typ, tos3("ustring"))) {

        compiler__Parser_gen(p, tos3(".s"));
      };

      typ = tos3("string");
    };

    if (i == 0 &&
        (string_eq(f->name, tos3("println")) ||
         string_eq(f->name, tos3("print"))) &&
        !(string_eq(typ, tos3("string")) || string_eq(typ, tos3("ustring")) ||
          string_eq(typ, tos3("void")))) {

      compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, typ);

#ifndef _WIN32

#ifndef _VJS

      string fmt = compiler__Parser_typ_to_fmt(p, typ, 0);

      if (string_ne(fmt, tos3("")) && string_ne(typ, tos3("bool"))) {

        string nl =
            (string_eq(f->name, tos3("println"))) ? (tos3("\\n")) : (tos3(""));

        compiler__CGen_resetln(
            p->cgen, string_replace(
                         p->cgen->cur_line, string_add(f->name, tos3(" (")),
                         string_add(string_add(tos3("/*opt*/printf (\""), fmt),
                                    _STR("%.*s\", ", nl.len, nl.str))));

        continue;
      };

#endif
      ;

#endif
      ;

      if (string_ends_with(typ, tos3("*"))) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("ptr_str("));

        compiler__Parser_gen(p, tos3(")"));

        continue;
      };

#ifndef _VJS

      if (!compiler__Type_has_method(&/* ? */ T, tos3("str"))) {

        if (string_starts_with(T.name, tos3("varg_"))) {

          compiler__Parser_gen_varg_str(p, T);

          compiler__CGen_set_placeholder(p->cgen, ph,
                                         _STR("%.*s_str(", typ.len, typ.str));

          compiler__Parser_gen(p, tos3(")"));

          continue;

        } else if (string_starts_with(T.name, tos3("array_"))) {

          compiler__Parser_gen_array_str(p, T);

          compiler__CGen_set_placeholder(p->cgen, ph,
                                         _STR("%.*s_str(", typ.len, typ.str));

          compiler__Parser_gen(p, tos3(")"));

          continue;

        } else if (T.cat == compiler__compiler__TypeCategory_struct_) {

          compiler__Parser_gen_struct_str(p, T);

          compiler__CGen_set_placeholder(p->cgen, ph,
                                         _STR("%.*s_str(", typ.len, typ.str));

          compiler__Parser_gen(p, tos3(")"));

          continue;
        };

        string error_msg =
            (_STR("`%.*s` needs to have method `str() string` to be printable",
                  typ.len, typ.str));

        compiler__Parser_error(p, error_msg);
      };

      compiler__CGen_set_placeholder(p->cgen, ph,
                                     _STR("%.*s_str(", typ.len, typ.str));

      compiler__Parser_gen(p, tos3(")"));

#endif
      ;

      continue;
    };

    string got = typ;

    string expected = arg.typ;

    bool got_ptr = string_ends_with(got, tos3("*"));

    bool exp_ptr = string_ends_with(expected, tos3("*"));

    bool type_mismatch =
        !compiler__Parser_check_types_no_throw(p, got, expected);

    if (type_mismatch && f->is_generic) {

      _PUSH(&saved_args, (/*typ = array_string   tmp_typ=string*/ got), tmp65,
            string);

    } else if (type_mismatch) {

      int j = i;

      if (f->is_method) {

        j--;
      };

      string nr = _STR("%dth", i + 1);

      if (j == 0) {

        nr = tos3("first");

      } else if (j == 1) {

        nr = tos3("second");

      } else if (j == 2) {

        nr = tos3("third");
      };

      compiler__Parser_error(
          p, string_add(
                 _STR("cannot use type `%.*s` as type `%.*s` in %.*s ", typ.len,
                      typ.str, arg.typ.len, arg.typ.str, nr.len, nr.str),
                 _STR("argument to `%.*s()`", f->name.len, f->name.str)));

    } else {

      _PUSH(&saved_args, (/*typ = array_string   tmp_typ=string*/ tos3("")),
            tmp66, string);
    };

    bool is_interface =
        compiler__Table_is_interface(&/* ? */ *p->table, arg.typ);

    if (!is_interface) {

      if (got_ptr && !exp_ptr) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("*"));
      };

      if (!got_ptr && exp_ptr && string_ne(got, tos3("voidptr"))) {

        if (string_starts_with(expected, tos3("array_")) && exp_ptr) {

          compiler__CGen_set_placeholder(p->cgen, ph,
                                         tos3("& /*111*/ (array[]){"));

          compiler__Parser_gen(p, tos3("}[0] "));

        } else if (!(string_eq(expected, tos3("void*")) &&
                     string_eq(got, tos3("int"))) &&
                   !(string_eq(expected, tos3("byte*")) &&
                     string_contains(got, tos3("]byte"))) &&
                   !(string_eq(expected, tos3("byte*")) &&
                     string_eq(got, tos3("string"))) &&
                   !(string_eq(expected, tos3("byte*")) &&
                     string_eq(got, tos3("byteptr")))) {

          compiler__CGen_set_placeholder(
              p->cgen, ph,
              _STR("& /*112 EXP:\"%.*s\" GOT:\"%.*s\" */", expected.len,
                   expected.str, got.len, got.str));
        };
      };

    } else if (is_interface) {

      if (!got_ptr) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3("&"));
      };

      compiler__Type interface_type =
          compiler__Table_find_type(&/* ? */ *p->table, arg.typ);

      array_compiler__Fn tmp67 = interface_type.methods;
      for (int tmp68 = 0; tmp68 < tmp67.len; tmp68++) {
        compiler__Fn method = ((compiler__Fn *)tmp67.data)[tmp68];

        compiler__Parser_gen(p, _STR(", %.*s_%.*s ", typ.len, typ.str,
                                     method.name.len, method.name.str));
      };
    };

    if (i < f->args.len - 1) {

      if (p->tok != compiler__compiler__TokenKind_comma && !f->is_variadic) {

        compiler__Parser_error(p, _STR("wrong number of arguments for %d,%.*s "
                                       "fn `%.*s`: expected %d, but got less",
                                       i, arg.name.len, arg.name.str,
                                       f->name.len, f->name.str, f->args.len));
      };

      if (p->tok == compiler__compiler__TokenKind_comma &&
          (!f->is_variadic || (f->is_variadic && i < f->args.len - 2))) {

        compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

        compiler__Parser_gen(p, tos3(","));
      };
    };
  };

  _V_MulRet_string_V_array_string _V_mret_varg_type_varg_values =
      compiler__Parser_fn_call_vargs(p, *f);
  string varg_type = _V_mret_varg_type_varg_values.var_0;
  array_string varg_values = _V_mret_varg_type_varg_values.var_1;

  if (f->is_variadic) {

    _PUSH(&saved_args, (/*typ = array_string   tmp_typ=string*/ varg_type),
          tmp69, string);
  };

  if (p->tok == compiler__compiler__TokenKind_comma) {

    compiler__Parser_error(p, _STR("wrong number of arguments for fn `%.*s`: "
                                   "expected %d, but got more",
                                   f->name.len, f->name.str, f->args.len));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  if (f->is_generic) {

    compiler__TypeInst type_map =
        compiler__Parser_extract_type_inst(p, f, saved_args);

    compiler__Parser_dispatch_generic_fn_instance(p, f, type_map);
  };

  if (f->is_variadic) {

    compiler__Parser_fn_gen_caller_vargs(p, f, varg_type, varg_values);
  };
}
compiler__TypeInst compiler__Parser_extract_type_inst(compiler__Parser *p,
                                                      compiler__Fn *f,
                                                      array_string args_) {

  compiler__TypeInst r =
      (compiler__TypeInst){.inst = new_map(1, sizeof(string)), .done = 0};

  int i = 0;

  array_string args = args_;

  if (string_ne(f->typ, tos3("void"))) {

    _PUSH(&args, (/*typ = array_string   tmp_typ=string*/ f->typ), tmp70,
          string);
  };

  array_string tmp71 = args;
  for (int tmp72 = 0; tmp72 < tmp71.len; tmp72++) {
    string e = ((string *)tmp71.data)[tmp72];

    if (string_eq(e, tos3(""))) {

      continue;
    };

    string tp = (*(string *)array_get(f->type_pars, i));

    string ti = e;

    if (string_starts_with(ti, tos3("fn ("))) {

      array_string fn_args = string_split(
          string_all_before(string_substr2(ti, 4, -1, true), tos3(") ")),
          tos3(","));

      bool found = 0;

      array_string tmp77 = fn_args;
      for (int tmp78 = 0; tmp78 < tmp77.len; tmp78++) {
        string fa_ = ((string *)tmp77.data)[tmp78];

        string fa = fa_;

        while (string_starts_with(fa, tos3("array_"))) {

          fa = string_substr2(fa, 6, -1, true);
        };

        if (string_eq(fa, tp)) {

          map_set(&r.inst, tp, &(string[]){fa});

          found = 1;

          i += 1;

          break;
        };
      };

      if (found) {

        continue;
      };

      ti = string_all_after(ti, tos3(") "));
    };

    while (string_starts_with(ti, tos3("array_"))) {

      ti = string_substr2(ti, 6, -1, true);
    };

    string tmp83 = tos3("");
    bool tmp84 = map_get(/*fn.v : 1145*/ r.inst, tp, &tmp83);

    if (!tmp84)
      tmp83 = tos((byte *)"", 0);

    if (string_ne(tmp83, tos3(""))) {

      string tmp85 = tos3("");
      bool tmp86 = map_get(/*fn.v : 1146*/ r.inst, tp, &tmp85);

      if (!tmp86)
        tmp85 = tos((byte *)"", 0);

      if (string_ne(tmp85, ti)) {

        string tmp87 = tos3("");
        bool tmp88 = map_get(/*fn.v : 1147*/ r.inst, tp, &tmp87);

        if (!tmp88)
          tmp87 = tos((byte *)"", 0);

        compiler__Parser_error(
            p, _STR("type parameter `%.*s` has type %.*s, not `%.*s`", tp.len,
                    tp.str, tmp87.len, tmp87.str, ti.len, ti.str));
      };

      continue;
    };

    map_set(&r.inst, tp, &(string[]){ti});

    i += 1;

    if (i >= f->type_pars.len) {

      break;
    };
  };

  string tmp89 = tos3("");
  bool tmp90 = map_get(/*fn.v : 1156*/ r.inst, f->typ, &tmp89);

  if (!tmp90)
    tmp89 = tos((byte *)"", 0);

  if (string_eq(tmp89, tos3("")) && (_IN(string, (f->typ), f->type_pars))) {

    map_set(&r.inst, f->typ, &(string[]){tos3("_ANYTYPE_")});
  };

  array_string tmp91 = f->type_pars;
  for (int tmp92 = 0; tmp92 < tmp91.len; tmp92++) {
    string tp = ((string *)tmp91.data)[tmp92];

    string tmp93 = tos3("");
    bool tmp94 = map_get(/*fn.v : 1160*/ r.inst, tp, &tmp93);

    if (!tmp94)
      tmp93 = tos((byte *)"", 0);

    if (string_eq(tmp93, tos3(""))) {

      compiler__Parser_error_with_token_index(
          p, _STR("unused type parameter `%.*s`", tp.len, tp.str),
          f->body_idx - 2);
    };
  };

  return r;
}
array_string compiler__Parser_replace_type_params(compiler__Parser *p,
                                                  compiler__Fn *f,
                                                  compiler__TypeInst ti) {

  array_string sig = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__Var tmp95 = f->args;
  for (int tmp96 = 0; tmp96 < tmp95.len; tmp96++) {
    compiler__Var a = ((compiler__Var *)tmp95.data)[tmp96];

    _PUSH(&sig, (/*typ = array_string   tmp_typ=string*/ a.typ), tmp97, string);
  };

  _PUSH(&sig, (/*typ = array_string   tmp_typ=string*/ f->typ), tmp98, string);

  array_string r = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string tmp99 = sig;
  for (int _ = 0; _ < tmp99.len; _++) {
    string a = ((string *)tmp99.data)[_];

    string fi = a;

    string fr = tos3("");

    if (string_starts_with(fi, tos3("fn ("))) {

      fr = string_add(fr, tos3("fn ("));

      array_string fn_args = string_split(
          string_all_before(string_substr2(fi, 4, -1, true), tos3(") ")),
          tos3(","));

      _PUSH(&fn_args,
            (/*typ = array_string   tmp_typ=string*/ string_all_after(
                fi, tos3(") "))),
            tmp102, string);

      array_string tmp103 = fn_args;
      for (int i = 0; i < tmp103.len; i++) {
        string fa_ = ((string *)tmp103.data)[i];

        string fna = string_trim_space(fa_);

        while (string_starts_with(fna, tos3("array_"))) {

          fna = string_substr2(fna, 6, -1, true);

          fr = string_add(fr, tos3("array_"));
        };

        if ((_IN(string, (fna), map_keys(&/* ? */ ti.inst)))) {

          string tmp106 = tos3("");
          bool tmp107 = map_get(/*fn.v : 1190*/ ti.inst, fna, &tmp106);

          if (!tmp107)
            tmp106 = tos((byte *)"", 0);

          fr = string_add(fr, tmp106);

        } else {

          fr = string_add(fr, fna);
        };

        if (i <= fn_args.len - 3) {

          fr = string_add(fr, tos3(","));

        } else if (i == fn_args.len - 2) {

          fr = string_add(fr, tos3(") "));
        };
      };

      _PUSH(&r, (/*typ = array_string   tmp_typ=string*/ fr), tmp108, string);

      continue;
    };

    while (string_starts_with(fi, tos3("array_"))) {

      fi = string_substr2(fi, 6, -1, true);

      fr = string_add(fr, tos3("array_"));
    };

    if (string_starts_with(fi, tos3("varg_"))) {

      fi = string_substr2(fi, 5, -1, true);

      fr = string_add(fr, tos3("varg_"));
    };

    if ((_IN(string, (fi), map_keys(&/* ? */ ti.inst)))) {

      string tmp113 = tos3("");
      bool tmp114 = map_get(/*fn.v : 1212*/ ti.inst, fi, &tmp113);

      if (!tmp114)
        tmp113 = tos((byte *)"", 0);

      string t = tmp113;

      fr = string_add(fr, t);

    } else {

      fr = string_add(fr, fi);
    };

    _PUSH(&r, (/*typ = array_string   tmp_typ=string*/ fr), tmp115, string);
  };

  return r;
}
string compiler__Parser_register_vargs_stuct(compiler__Parser *p, string typ,
                                             int len) {

  string vargs_struct = _STR("varg_%.*s", typ.len, typ.str);

  compiler__Type varg_type =
      (compiler__Type){.cat = compiler__compiler__TypeCategory_struct_,
                       .name = vargs_struct,
                       .mod = p->mod,
                       .is_public = 0,
                       .fields = new_array(0, 1, sizeof(compiler__Var)),
                       .methods = new_array(0, 1, sizeof(compiler__Fn)),
                       .parent = tos3(""),
                       .is_c = 0,
                       .enum_vals = new_array(0, 1, sizeof(string)),
                       .gen_types = new_array(0, 1, sizeof(string)),
                       .is_placeholder = 0,
                       .gen_str = 0};

  int varg_len = len;

  if (!compiler__Table_known_type(&/* ? */ *p->table, vargs_struct)) {

    compiler__Table_register_type2(p->table, varg_type);

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "typedef struct %.*s %.*s;\n", vargs_struct.len, vargs_struct.str,
              vargs_struct.len, vargs_struct.str)),
          tmp116, string);

  } else {

    compiler__Type ex_typ =
        compiler__Table_find_type(&/* ? */ *p->table, vargs_struct);

    int ex_len = v_string_int(string_substr2(
        (*(compiler__Var *)array_get(ex_typ.fields, 1)).name, 5,
        (*(compiler__Var *)array_get(ex_typ.fields, 1)).name.len - 1, false));

    if (ex_len > varg_len) {

      varg_len = ex_len;
    };

    compiler__Table_rewrite_type(p->table, varg_type);
  };

  compiler__Table_add_field(p->table, vargs_struct, tos3("len"), tos3("int"), 0,
                            tos3(""), compiler__compiler__AccessMod_public);

  compiler__Table_add_field(p->table, vargs_struct, _STR("args[%d]", varg_len),
                            typ, 0, tos3(""),
                            compiler__compiler__AccessMod_public);

  return vargs_struct;
}
_V_MulRet_string_V_array_string
compiler__Parser_fn_call_vargs(compiler__Parser *p, compiler__Fn f) {

  if (!f.is_variadic) {

    return (_V_MulRet_string_V_array_string){
        .var_0 = tos3(""),
        .var_1 = new_array_from_c_array(
            0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)})};
  };

  compiler__Var last_arg = *(compiler__Var *)array_last(f.args);

  string varg_def_type = string_substr2(last_arg.typ, 3, -1, true);

  array_string types = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string values = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (p->tok != compiler__compiler__TokenKind_rpar) {

    if (p->tok == compiler__compiler__TokenKind_comma) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
    };

    compiler__CGen_start_tmp(p->cgen);

    string varg_type = compiler__Parser_bool_expression(p);

    string varg_value = compiler__CGen_end_tmp(p->cgen);

    if (string_starts_with(varg_type, tos3("varg_")) &&
        (values.len > 0 || p->tok == compiler__compiler__TokenKind_comma)) {

      compiler__Parser_error(
          p, tos3("You cannot pass additional vargs when forwarding vargs to "
                  "another function/method"));
    };

    if (!f.is_generic) {

      compiler__Parser_check_types(p, last_arg.typ, varg_type);

    } else {

      if (types.len > 0) {

        array_string tmp125 = types;
        for (int tmp126 = 0; tmp126 < tmp125.len; tmp126++) {
          string t = ((string *)tmp125.data)[tmp126];

          compiler__Parser_check_types(p, varg_type, t);
        };
      };
    };

    string ref_deref = (string_ends_with(last_arg.typ, tos3("*")) &&
                        !string_ends_with(varg_type, tos3("*")))
                           ? (tos3("&"))
                           : ((!string_ends_with(last_arg.typ, tos3("*")) &&
                               string_ends_with(varg_type, tos3("*")))
                                  ? (tos3("*"))
                                  : (tos3("")));

    _PUSH(&types, (/*typ = array_string   tmp_typ=string*/ varg_type), tmp127,
          string);

    _PUSH(&values,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "%.*s%.*s", ref_deref.len, ref_deref.str, varg_value.len,
              varg_value.str)),
          tmp128, string);
  };

  array_compiler__VargAccess tmp129 = p->table->varg_access;
  for (int tmp130 = 0; tmp130 < tmp129.len; tmp130++) {
    compiler__VargAccess va = ((compiler__VargAccess *)tmp129.data)[tmp130];

    if (string_ne(va.fn_name, f.name)) {

      continue;
    };

    if (va.index >= values.len) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("variadic arg index out of range: %d/%d, vargs are 0 indexed",
               va.index, values.len - 1),
          va.tok_idx);
    };
  };

  if (!f.is_method && f.args.len > 1) {

    compiler__CGen_gen(p->cgen, tos3(","));
  };

  return (_V_MulRet_string_V_array_string){
      .var_0 = (*(string *)array_get(types, 0)), .var_1 = values};
}
void compiler__Parser_fn_gen_caller_vargs(compiler__Parser *p, compiler__Fn *f,
                                          string varg_type,
                                          array_string values) {

  bool is_varg = string_starts_with(varg_type, tos3("varg_"));

  if (is_varg) {

    compiler__CGen_gen(p->cgen,
                       _STR("%.*s", (*(string *)array_get(values, 0)).len,
                            (*(string *)array_get(values, 0)).str));

  } else {

    string vargs_struct =
        compiler__Parser_register_vargs_stuct(p, varg_type, values.len);

    compiler__CGen_gen(
        p->cgen,
        string_add(string_add(_STR("&(%.*s){.len=%d,.args={", vargs_struct.len,
                                   vargs_struct.str, values.len),
                              array_string_join(values, tos3(","))),
                   tos3("}}")));
  };
}
string compiler__Parser_register_multi_return_stuct(compiler__Parser *p,
                                                    array_string types) {

  string typ = string_add(tos3("_V_MulRet_"),
                          string_replace(array_string_join(types, tos3("_V_")),
                                         tos3("*"), tos3("_PTR_")));

  if (compiler__Table_known_type(&/* ? */ *p->table, typ)) {

    return typ;
  };

  compiler__Table_register_type2(
      p->table,
      (compiler__Type){.cat = compiler__compiler__TypeCategory_struct_,
                       .name = typ,
                       .mod = p->mod,
                       .is_public = 0,
                       .fields = new_array(0, 1, sizeof(compiler__Var)),
                       .methods = new_array(0, 1, sizeof(compiler__Fn)),
                       .parent = tos3(""),
                       .is_c = 0,
                       .enum_vals = new_array(0, 1, sizeof(string)),
                       .gen_types = new_array(0, 1, sizeof(string)),
                       .is_placeholder = 0,
                       .gen_str = 0});

  array_string tmp135 = string_split(
      string_replace(string_replace(typ, tos3("_V_MulRet_"), tos3("")),
                     tos3("_PTR_"), tos3("*")),
      tos3("_V_"));
  for (int i = 0; i < tmp135.len; i++) {
    string t = ((string *)tmp135.data)[i];

    compiler__Table_add_field(p->table, typ, _STR("var_%d", i), t, 0, tos3(""),
                              compiler__compiler__AccessMod_public);
  };

  _PUSH(&p->cgen->typedefs,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "typedef struct %.*s %.*s;", typ.len, typ.str, typ.len, typ.str)),
        tmp136, string);

  return typ;
}
void compiler__Parser_rename_generic_fn_instance(compiler__Parser *p,
                                                 compiler__Fn *f,
                                                 compiler__TypeInst ti) {

  if (f->is_method) {

    f->name = string_add(string_add(f->receiver_typ, tos3("_")), f->name);
  };

  f->name = string_add(f->name, tos3("_T"));

  array_string tmp137 = map_keys(&/* ? */ ti.inst);
  for (int tmp138 = 0; tmp138 < tmp137.len; tmp138++) {
    string k = ((string *)tmp137.data)[tmp138];

    string tmp139 = tos3("");
    bool tmp140 = map_get(/*fn.v : 1322*/ ti.inst, k, &tmp139);

    if (!tmp140)
      tmp139 = tos((byte *)"", 0);

    f->name = string_add(string_add(f->name, tos3("_")),
                         compiler__type_to_safe_str(tmp139));
  };
}
void compiler__Parser_dispatch_generic_fn_instance(compiler__Parser *p,
                                                   compiler__Fn *f,
                                                   compiler__TypeInst ti) {

  bool new_inst = 1;

  array_compiler__TypeInst tmp141 = f->type_inst;
  for (int tmp142 = 0; tmp142 < tmp141.len; tmp142++) {
    compiler__TypeInst e = ((compiler__TypeInst *)tmp141.data)[tmp142];

    if (string_eq(map_string_str(e.inst), map_string_str(ti.inst))) {

      new_inst = 0;

      break;
    };
  };

  if (!new_inst) {

    compiler__Parser_rename_generic_fn_instance(p, f, ti);

    Option_compiler__Fn tmp143 =
        compiler__Table_find_fn(&/* ? */ *p->table, f->name);
    compiler__Fn _f;
    if (!tmp143.ok) {
      string err = tmp143.error;
      int errcode = tmp143.ecode;

      compiler__Parser_error(p, _STR("function instance `%.*s` not found",
                                     f->name.len, f->name.str));

      return;
    }
    _f = *(compiler__Fn *)tmp143.data;
    ;

    f->args = _f.args;

    f->typ = _f.typ;

    f->is_generic = 0;

    f->type_inst = new_array_from_c_array(
        0, 0, sizeof(compiler__TypeInst),
        EMPTY_ARRAY_OF_ELEMS(compiler__TypeInst, 0){TCCSKIP(0)});

    f->dispatch_of = ti;

    return;
  };

  _PUSH(&f->type_inst,
        (/*typ = array_compiler__TypeInst   tmp_typ=compiler__TypeInst*/ ti),
        tmp144, compiler__TypeInst);

  compiler__Table_register_fn(p->table, *f);

  int saved_tok_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

  compiler__Fn saved_fn = p->cur_fn;

  int saved_var_idx = p->var_idx;

  array_compiler__Var saved_local_vars = p->local_vars;

  compiler__Parser_clear_vars(p);

  string saved_line = p->cgen->cur_line;

  array_string saved_lines = p->cgen->lines;

  bool saved_is_tmp = p->cgen->is_tmp;

  string saved_tmp_line = p->cgen->tmp_line;

  bool returns = p->returns;

  compiler__Parser_rename_generic_fn_instance(p, f, ti);

  f->is_generic = 0;

  f->type_inst = new_array_from_c_array(
      0, 0, sizeof(compiler__TypeInst),
      EMPTY_ARRAY_OF_ELEMS(compiler__TypeInst, 0){TCCSKIP(0)});

  f->scope_level = 0;

  f->dispatch_of = ti;

  f->defer_text = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__Var old_args = f->args;

  array_string new_types = compiler__Parser_replace_type_params(p, f, ti);

  f->args = new_array_from_c_array(
      0, 0, sizeof(compiler__Var),
      EMPTY_ARRAY_OF_ELEMS(compiler__Var, 0){TCCSKIP(0)});

  int tmp145 = 0;
  ;
  for (int tmp146 = tmp145; tmp146 < new_types.len - 1; tmp146++) {
    int i = tmp146;

    compiler__Var v = (*(compiler__Var *)array_get(old_args, i));

    v.typ = (*(string *)array_get(new_types, i));

    _PUSH(&f->args, (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ v),
          tmp151, compiler__Var);
  };

  f->typ = *(string *)array_last(new_types);

  if ((_IN(string, (f->typ), f->type_pars))) {

    f->typ = tos3("_ANYTYPE_");
  };

  if ((_IN_MAP((f->typ), ti.inst))) {

    string tmp152 = tos3("");
    bool tmp153 = map_get(/*fn.v : 1388*/ ti.inst, f->typ, &tmp152);

    if (!tmp153)
      tmp152 = tos((byte *)"", 0);

    f->typ = tmp152;
  };

  if (f->is_method) {

    compiler__Parser_add_method(
        p, (*(compiler__Var *)array_get(f->args, 0)).name, *f);

  } else {

    compiler__Table_register_fn(p->table, *f);
  };

  p->cgen->is_tmp = 0;

  p->returns = 0;

  p->cgen->tmp_line = tos3("");

  p->cgen->cur_line = tos3("");

  p->cgen->lines = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  p->cur_fn = *f;

  array_compiler__Var tmp156 = f->args;
  for (int tmp157 = 0; tmp157 < tmp156.len; tmp157++) {
    compiler__Var arg = ((compiler__Var *)tmp156.data)[tmp157];

    compiler__Parser_register_var(p, arg);
  };

  p->token_idx = f->body_idx - 1;

  compiler__Parser_next(p);

  string str_args = compiler__Fn_str_args(&/* ? */ *f, p->table);

  p->in_dispatch = 1;

  compiler__Parser_genln(p, _STR("%.*s%.*s %.*s(%.*s) {",
                                 compiler__Parser_get_linkage_prefix(*p).len,
                                 compiler__Parser_get_linkage_prefix(*p).str,
                                 f->typ.len, f->typ.str, f->name.len,
                                 f->name.str, str_args.len, str_args.str));

  compiler__Parser_statements(p);

  p->in_dispatch = 0;

  if (string_eq(f->typ, tos3("_ANYTYPE_"))) {

    f->typ = p->cur_fn.typ;

    f->name = string_replace(f->name, tos3("_ANYTYPE_"),
                             compiler__type_to_safe_str(f->typ));

    array_set(
        &/*q*/ p->cgen->lines, 0,
        &(string[]){string_replace((*(string *)array_get(p->cgen->lines, 0)),
                                   tos3("_ANYTYPE_"), f->typ)});

    compiler__Table_register_fn(p->table, *f);
  };

  array_string tmp160 = p->cgen->lines;
  for (int tmp161 = 0; tmp161 < tmp160.len; tmp161++) {
    string l = ((string *)tmp160.data)[tmp161];

    _PUSH(&p->cgen->fns, (/*typ = array_string   tmp_typ=string*/ l), tmp162,
          string);
  };

  p->token_idx = saved_tok_idx - 1;

  compiler__Parser_next(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  p->cur_fn = saved_fn;

  p->var_idx = saved_var_idx;

  p->local_vars = saved_local_vars;

  p->cgen->lines = saved_lines;

  p->cgen->cur_line = saved_line;

  p->cgen->is_tmp = saved_is_tmp;

  p->cgen->tmp_line = saved_tmp_line;

  p->returns = 0;
}
string compiler__Fn_typ_str(compiler__Fn *f) {

  strings__Builder sb = strings__new_builder(50);

  strings__Builder_write(&/* ? */ sb, tos3("fn ("));

  array_compiler__Var tmp163 = f->args;
  for (int i = 0; i < tmp163.len; i++) {
    compiler__Var arg = ((compiler__Var *)tmp163.data)[i];

    strings__Builder_write(&/* ? */ sb, arg.typ);

    if (i < f->args.len - 1) {

      strings__Builder_write(&/* ? */ sb, tos3(","));
    };
  };

  strings__Builder_write(&/* ? */ sb, tos3(")"));

  if (string_ne(f->typ, tos3("void"))) {

    strings__Builder_write(&/* ? */ sb, _STR(" %.*s", f->typ.len, f->typ.str));
  };

  return strings__Builder_str(sb);
}
string compiler__Fn_str_args(compiler__Fn *f, compiler__Table *table) {

  string s = tos3("");

  array_compiler__Var tmp164 = f->args;
  for (int i = 0; i < tmp164.len; i++) {
    compiler__Var arg = ((compiler__Var *)tmp164.data)[i];

    if (compiler__Table_is_interface(&/* ? */ *table, arg.typ)) {

      s = string_add(s, _STR(" void* %.*s", arg.name.len, arg.name.str));

      compiler__Type interface_type =
          compiler__Table_find_type(&/* ? */ *table, arg.typ);

      array_compiler__Fn tmp165 = interface_type.methods;
      for (int tmp166 = 0; tmp166 < tmp165.len; tmp166++) {
        compiler__Fn method = ((compiler__Fn *)tmp165.data)[tmp166];

        s = string_add(s, _STR(", %.*s (*%.*s_%.*s)(void*", method.typ.len,
                               method.typ.str, arg.typ.len, arg.typ.str,
                               method.name.len, method.name.str));

        if (method.args.len > 1) {

          array_compiler__Var tmp167 = array_slice2(method.args, 1, -1, true);
          for (int tmp170 = 0; tmp170 < tmp167.len; tmp170++) {
            compiler__Var a = ((compiler__Var *)tmp167.data)[tmp170];

            s = string_add(s, _STR(", %.*s", a.typ.len, a.typ.str));
          };
        };

        s = string_add(s, tos3(")"));
      };

    } else if (string_starts_with(arg.typ, tos3("varg_"))) {

      s = string_add(s, _STR("%.*s *%.*s", arg.typ.len, arg.typ.str,
                             arg.name.len, arg.name.str));

    } else {

      s = string_add(s, compiler__Table_cgen_name_type_pair(&/* ? */ *table,
                                                            arg.name, arg.typ));
    };

    if (i < f->args.len - 1) {

      s = string_add(s, tos3(", "));
    };
  };

  return s;
}
string compiler__Parser_find_misspelled_local_var(compiler__Parser *p,
                                                  string name, f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_var = tos3("");

  array_compiler__Var tmp171 = p->local_vars;
  for (int tmp172 = 0; tmp172 < tmp171.len; tmp172++) {
    compiler__Var var = ((compiler__Var *)tmp171.data)[tmp172];

    if (var.scope_level > p->cur_fn.scope_level) {

      continue;
    };

    string n = string_all_after(name, tos3("."));

    if (string_eq(var.name, tos3("")) ||
        (n.len - var.name.len > 2 || var.name.len - n.len > 2)) {

      continue;
    };

    f32 c = strings__dice_coefficient(var.name, n);

    if (f32_gt(c, closest)) {

      closest = c;

      closest_var = var.name;
    };
  };

  return (f32_ge(closest, min_match)) ? (closest_var) : (tos3(""));
}
bool array_compiler__Fn_contains(array_compiler__Fn fns, compiler__Fn f) {

  array_compiler__Fn tmp173 = fns;
  for (int tmp174 = 0; tmp174 < tmp173.len; tmp174++) {
    compiler__Fn ff = ((compiler__Fn *)tmp173.data)[tmp174];

    if (string_eq(ff.name, f.name)) {

      return 1;
    };
  };

  return 0;
}
string compiler__Fn_v_fn_module(compiler__Fn f) { return f.mod; }
string compiler__Fn_v_fn_name(compiler__Fn f) {

  return string_replace(f.name, _STR("%.*s__", f.mod.len, f.mod.str), tos3(""));
}
void compiler__Parser_for_st(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_for);

  ;

  p->for_expr_cnt++;

  compiler__TokenKind next_tok = compiler__Parser_peek(&/* ? */ *p);

  compiler__Parser_open_scope(p);

  if (p->tok == compiler__compiler__TokenKind_lcbr) {

    compiler__Parser_gen(p, tos3("while (1) {"));

  } else if (p->tok == compiler__compiler__TokenKind_key_mut) {

    compiler__Parser_error(p, tos3("`mut` is not required in for loops"));

  } else if (next_tok == compiler__compiler__TokenKind_decl_assign ||
             next_tok == compiler__compiler__TokenKind_assign ||
             p->tok == compiler__compiler__TokenKind_semicolon) {

    compiler__Parser_genln(p, tos3("for ("));

    if (next_tok == compiler__compiler__TokenKind_decl_assign) {

      compiler__Parser_check_not_reserved(p);

      compiler__Parser_var_decl(p);

    } else if (p->tok != compiler__compiler__TokenKind_semicolon) {

      compiler__Parser_statement(p, 0);
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_semicolon);

    compiler__Parser_gen(p, tos3(" ; "));

    ;

    if (p->tok != compiler__compiler__TokenKind_semicolon) {

      compiler__Parser_bool_expression(p);
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_semicolon);

    compiler__Parser_gen(p, tos3(" ; "));

    ;

    if (p->tok != compiler__compiler__TokenKind_lcbr) {

      compiler__Parser_statement(p, 0);
    };

    compiler__Parser_genln(p, tos3(") { "));

  } else if (compiler__Parser_peek(&/* ? */ *p) ==
             compiler__compiler__TokenKind_comma) {

    string i = compiler__Parser_check_name(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

    string val = compiler__Parser_check_name(p);

    if (string_eq(i, tos3("_")) && string_eq(val, tos3("_"))) {

      compiler__Parser_error(p,
                             tos3("no new variables on the left side of `in`"));
    };

    ;

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_in);

    ;

    string tmp = compiler__Parser_get_tmp(p);

    compiler__CGen_start_tmp(p->cgen);

    string typ = compiler__Parser_bool_expression(p);

    bool is_arr = string_starts_with(typ, tos3("array_"));

    bool is_map = string_starts_with(typ, tos3("map_"));

    bool is_str = string_eq(typ, tos3("string"));

    bool is_variadic_arg = string_starts_with(typ, tos3("varg_"));

    if (!is_arr && !is_str && !is_map && !is_variadic_arg) {

      compiler__Parser_error(
          p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    string expr = compiler__CGen_end_tmp(p->cgen);

    if (!is_variadic_arg) {

      if (p->is_js) {

        compiler__Parser_genln(
            p, _STR("var %.*s = %.*s;", tmp.len, tmp.str, expr.len, expr.str));

      } else {

        compiler__Parser_genln(p, _STR("%.*s %.*s = %.*s;", typ.len, typ.str,
                                       tmp.len, tmp.str, expr.len, expr.str));
      };
    };

    string i_var_type = tos3("int");

    if (is_variadic_arg) {

      typ = string_substr2(typ, 5, -1, true);

      compiler__Parser_gen_for_varg_header(p, i, expr, typ, val);

    } else if (is_arr) {

      typ = string_substr2(typ, 6, -1, true);

      compiler__Parser_gen_for_header(p, i, tmp, typ, val);

    } else if (is_map) {

      i_var_type = tos3("string");

      typ = string_substr2(typ, 4, -1, true);

      compiler__Parser_gen_for_map_header(p, i, tmp, typ, val, typ);

    } else if (is_str) {

      typ = tos3("byte");

      compiler__Parser_gen_for_str_header(p, i, tmp, typ, val);
    };

    if (string_ne(i, tos3("_"))) {

      compiler__Parser_register_var(
          p, (compiler__Var){.name = i,
                             .typ = i_var_type,
                             .is_mut = 1,
                             .is_changed = 1,
                             .idx = 0,
                             .is_arg = 0,
                             .is_const = 0,
                             .args = new_array(0, 1, sizeof(compiler__Var)),
                             .attr = tos3(""),
                             .is_alloc = 0,
                             .is_returned = 0,
                             .ptr = 0,
                             .ref = 0,
                             .parent_fn = tos3(""),
                             .mod = tos3(""),
                             .is_global = 0,
                             .is_used = 0,
                             .scope_level = 0,
                             .is_c = 0,
                             .is_moved = 0,
                             .line_nr = 0,
                             .token_idx = 0,
                             .is_for_var = 0,
                             .is_public = 0});
    };

    if (string_ne(val, tos3("_"))) {

      compiler__Parser_register_var(
          p, (compiler__Var){.name = val,
                             .typ = typ,
                             .ptr = string_contains(typ, tos3("*")),
                             .idx = 0,
                             .is_arg = 0,
                             .is_const = 0,
                             .args = new_array(0, 1, sizeof(compiler__Var)),
                             .attr = tos3(""),
                             .is_mut = 0,
                             .is_alloc = 0,
                             .is_returned = 0,
                             .ref = 0,
                             .parent_fn = tos3(""),
                             .mod = tos3(""),
                             .is_global = 0,
                             .is_used = 0,
                             .is_changed = 0,
                             .scope_level = 0,
                             .is_c = 0,
                             .is_moved = 0,
                             .line_nr = 0,
                             .token_idx = 0,
                             .is_for_var = 0,
                             .is_public = 0});
    };

  } else if (compiler__Parser_peek(&/* ? */ *p) ==
             compiler__compiler__TokenKind_key_in) {

    string val = compiler__Parser_check_name(p);

    ;

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_in);

    ;

    string tmp = compiler__Parser_get_tmp(p);

    compiler__CGen_start_tmp(p->cgen);

    string typ = compiler__Parser_bool_expression(p);

    string expr = compiler__CGen_end_tmp(p->cgen);

    bool is_range = p->tok == compiler__compiler__TokenKind_dotdot;

    bool is_variadic_arg = string_starts_with(typ, tos3("varg_"));

    string range_end = tos3("");

    if (is_range) {

      compiler__Parser_check_types(p, typ, tos3("int"));

      compiler__Parser_check_space(p, compiler__compiler__TokenKind_dotdot);

      compiler__CGen_start_tmp(p->cgen);

      compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                   tos3("int"));

      range_end = compiler__CGen_end_tmp(p->cgen);
    };

    bool is_arr = string_contains(typ, tos3("array"));

    bool is_str = string_eq(typ, tos3("string"));

    if (!is_arr && !is_str && !is_range && !is_variadic_arg) {

      compiler__Parser_error(
          p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    if (!is_variadic_arg) {

      if (p->is_js) {

        compiler__Parser_genln(
            p, _STR("var %.*s = %.*s;", tmp.len, tmp.str, expr.len, expr.str));

      } else {

        compiler__Parser_genln(p, _STR("%.*s %.*s = %.*s;", typ.len, typ.str,
                                       tmp.len, tmp.str, expr.len, expr.str));
      };
    };

    string i = compiler__Parser_get_tmp(p);

    if (is_variadic_arg) {

      typ = string_substr2(typ, 5, -1, true);

      compiler__Parser_gen_for_varg_header(p, i, expr, typ, val);

    } else if (is_range) {

      typ = tos3("int");

      compiler__Parser_gen_for_range_header(p, i, range_end, tmp, typ, val);

    } else if (is_arr) {

      typ = string_substr2(typ, 6, -1, true);

      compiler__Parser_gen_for_header(p, i, tmp, typ, val);

    } else if (is_str) {

      typ = tos3("byte");

      compiler__Parser_gen_for_str_header(p, i, tmp, typ, val);
    };

    if (string_ne(val, tos3("_"))) {

      compiler__Parser_register_var(
          p, (compiler__Var){.name = val,
                             .typ = typ,
                             .ptr = string_contains(typ, tos3("*")),
                             .is_changed = 1,
                             .is_mut = 0,
                             .is_for_var = 1,
                             .idx = 0,
                             .is_arg = 0,
                             .is_const = 0,
                             .args = new_array(0, 1, sizeof(compiler__Var)),
                             .attr = tos3(""),
                             .is_alloc = 0,
                             .is_returned = 0,
                             .ref = 0,
                             .parent_fn = tos3(""),
                             .mod = tos3(""),
                             .is_global = 0,
                             .is_used = 0,
                             .scope_level = 0,
                             .is_c = 0,
                             .is_moved = 0,
                             .line_nr = 0,
                             .token_idx = 0,
                             .is_public = 0});
    };

  } else {

    compiler__Parser_gen(p, tos3("while ("));

    compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                 tos3("bool"));

    compiler__Parser_genln(p, tos3(") {"));
  };

  ;

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  compiler__Parser_genln(p, tos3(""));

  compiler__Parser_statements(p);

  compiler__Parser_close_scope(p);

  p->for_expr_cnt--;

  p->returns = 0;
}
string compiler__Parser_gen_var_decl(compiler__Parser *p, string name,
                                     bool is_static) {

  int pos = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  p->is_var_decl = 1;

  string typ = compiler__Parser_bool_expression(p);

  p->is_var_decl = 0;

  if (string_starts_with(typ, tos3("..."))) {

    typ = string_substr2(typ, 3, -1, true);
  };

  bool or_else = p->tok == compiler__compiler__TokenKind_key_orelse;

  if (or_else) {

    return compiler__Parser_gen_handle_option_or_else(p, typ, name, pos);
  };

  string gen_name = compiler__Table_var_cgen_name(&/* ? */ *p->table, name);

  string nt_gen =
      compiler__Table_cgen_name_type_pair(&/* ? */ *p->table, gen_name, typ);

  if (!p->is_empty_c_struct_init && !string_starts_with(typ, tos3("["))) {

    nt_gen = string_add(nt_gen, tos3("="));

  } else if (string_starts_with(typ, tos3("[")) &&
             string_at(typ, typ.len - 1) != '*') {

    string initializer = string_substr2(p->cgen->cur_line, pos, -1, true);

    if (initializer.len > 0) {

      compiler__CGen_resetln(
          p->cgen,
          string_add(tos3(" = {"), string_all_after(initializer, tos3("{"))));

    } else if (initializer.len == 0) {

      compiler__CGen_resetln(p->cgen, tos3(" = { 0 }"));
    };
  };

  if (is_static) {

    nt_gen = _STR("static %.*s", nt_gen.len, nt_gen.str);
  };

  compiler__CGen_set_placeholder(p->cgen, pos, nt_gen);

  return typ;
}
void compiler__Parser_gen_fn_decl(compiler__Parser *p, compiler__Fn f,
                                  string typ, string str_args) {

  string dll_export_linkage =
      (string_eq(p->pref->ccompiler, tos3("msvc")) &&
       string_eq(p->attr, tos3("live")) && p->pref->is_so)
          ? (tos3("__declspec(dllexport) "))
          : ((string_eq(p->attr, tos3("inline"))) ? (tos3("static inline "))
                                                  : (tos3("")));

  string fn_name_cgen = compiler__Table_fn_gen_name(
      p->table, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f);

  compiler__Parser_genln(p, _STR("%.*s%.*s %.*s(%.*s) {",
                                 dll_export_linkage.len, dll_export_linkage.str,
                                 typ.len, typ.str, fn_name_cgen.len,
                                 fn_name_cgen.str, str_args.len, str_args.str));
}
void compiler__Parser_gen_blank_identifier_assign(compiler__Parser *p) {

  int assign_error_tok_idx = p->token_idx;

  compiler__Parser_check_name(p);

  compiler__Parser_check_space(p, compiler__compiler__TokenKind_assign);

  bool is_indexer =
      compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_lsbr;

  _V_MulRet_bool_V_string _V_mret_is_fn_call_next_expr =
      compiler__Parser_is_expr_fn_call(p, p->token_idx);
  bool is_fn_call = _V_mret_is_fn_call_next_expr.var_0;
  string next_expr = _V_mret_is_fn_call_next_expr.var_1;

  int pos = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  p->is_var_decl = 1;

  string typ = compiler__Parser_bool_expression(p);

  if (string_eq(typ, tos3("void"))) {

    compiler__Parser_error_with_token_index(
        p,
        _STR("%.*s() %.*s", next_expr.len, next_expr.str,
             compiler__err_used_as_value.len, compiler__err_used_as_value.str),
        p->token_idx - 2);
  };

  p->is_var_decl = 0;

  if (!is_indexer && !is_fn_call) {

    compiler__Parser_error_with_token_index(
        p,
        _STR("assigning `%.*s` to `_` is redundant", next_expr.len,
             next_expr.str),
        assign_error_tok_idx);
  };

  if (p->tok == compiler__compiler__TokenKind_key_orelse) {

    compiler__Parser_gen_handle_option_or_else(p, typ, tos3(""), pos);

  } else {

    if (is_fn_call) {

      compiler__Parser_gen(p, tos3(";"));

    } else {

      compiler__CGen_resetln(p->cgen, _STR("{%.*s _ = %.*s;}", typ.len, typ.str,
                                           p->cgen->cur_line.len,
                                           p->cgen->cur_line.str));
    };
  };
}
string compiler__Parser_gen_handle_option_or_else(compiler__Parser *p,
                                                  string _typ, string name,
                                                  int fn_call_ph) {

  string typ = _typ;

  if (!string_starts_with(typ, tos3("Option_"))) {

    compiler__Parser_error(
        p, tos3("`or` block cannot be applied to non-optional type"));
  };

  bool is_assign = name.len > 0;

  string tmp = compiler__Parser_get_tmp(p);

  compiler__CGen_set_placeholder(
      p->cgen, fn_call_ph,
      _STR("%.*s %.*s = ", typ.len, typ.str, tmp.len, tmp.str));

  typ = string_substr2(typ, 7, -1, true);

  compiler__Parser_genln(p, tos3(";"));

  int or_tok_idx = p->token_idx;

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_orelse);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  compiler__Parser_register_var(
      p, (compiler__Var){.name = tos3("err"),
                         .typ = tos3("string"),
                         .is_mut = 0,
                         .is_used = 1,
                         .idx = 0,
                         .is_arg = 0,
                         .is_const = 0,
                         .args = new_array(0, 1, sizeof(compiler__Var)),
                         .attr = tos3(""),
                         .is_alloc = 0,
                         .is_returned = 0,
                         .ptr = 0,
                         .ref = 0,
                         .parent_fn = tos3(""),
                         .mod = tos3(""),
                         .is_global = 0,
                         .is_changed = 0,
                         .scope_level = 0,
                         .is_c = 0,
                         .is_moved = 0,
                         .line_nr = 0,
                         .token_idx = 0,
                         .is_for_var = 0,
                         .is_public = 0});

  compiler__Parser_register_var(
      p, (compiler__Var){.name = tos3("errcode"),
                         .typ = tos3("int"),
                         .is_mut = 0,
                         .is_used = 1,
                         .idx = 0,
                         .is_arg = 0,
                         .is_const = 0,
                         .args = new_array(0, 1, sizeof(compiler__Var)),
                         .attr = tos3(""),
                         .is_alloc = 0,
                         .is_returned = 0,
                         .ptr = 0,
                         .ref = 0,
                         .parent_fn = tos3(""),
                         .mod = tos3(""),
                         .is_global = 0,
                         .is_changed = 0,
                         .scope_level = 0,
                         .is_c = 0,
                         .is_moved = 0,
                         .line_nr = 0,
                         .token_idx = 0,
                         .is_for_var = 0,
                         .is_public = 0});

  if (is_assign) {

    compiler__Parser_genln(
        p, _STR("%.*s %.*s;", typ.len, typ.str, name.len, name.str));
  };

  compiler__Parser_genln(p, _STR("if (!%.*s .ok) {", tmp.len, tmp.str));

  compiler__Parser_genln(p,
                         _STR("string err = %.*s . error;", tmp.len, tmp.str));

  compiler__Parser_genln(p,
                         _STR("int errcode = %.*s . ecode;", tmp.len, tmp.str));

  int last_ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  string last_typ = compiler__Parser_statements(p);

  if (is_assign && string_eq(last_typ, typ)) {

    string expr_line =
        (*(string *)array_get(p->cgen->lines, p->cgen->lines.len - 3));

    string last_expr = string_substr2(expr_line, last_ph, -1, true);

    array_set(&/*q*/ p->cgen->lines, p->cgen->lines.len - 3,
              &(string[]){tos3("")});

    compiler__Parser_genln(p, _STR("if (!%.*s .ok) {", tmp.len, tmp.str));

    compiler__Parser_genln(p, _STR("%.*s = %.*s;", name.len, name.str,
                                   last_expr.len, last_expr.str));

    compiler__Parser_genln(p, tos3("}"));

  } else if (is_assign) {

    compiler__Parser_genln(p,
                           _STR("%.*s = *(%.*s*) %.*s . data;", name.len,
                                name.str, typ.len, typ.str, tmp.len, tmp.str));
  };

  if (!p->returns && string_ne(last_typ, typ) && is_assign &&
      p->prev_tok2 != compiler__compiler__TokenKind_key_continue &&
      p->prev_tok2 != compiler__compiler__TokenKind_key_break) {

    compiler__Parser_error_with_token_index(
        p,
        tos3("`or` block must provide a default value or "
             "return/exit/continue/break/panic"),
        or_tok_idx);
  };

  p->returns = 0;

  return typ;
}
string compiler__types_to_c(array_compiler__Type types,
                            compiler__Table *table) {

  strings__Builder sb = strings__new_builder(10);

  array_compiler__Type tmp13 = types;
  for (int tmp14 = 0; tmp14 < tmp13.len; tmp14++) {
    compiler__Type t = ((compiler__Type *)tmp13.data)[tmp14];

    if (t.cat != compiler__compiler__TypeCategory_union_ &&
        t.cat != compiler__compiler__TypeCategory_struct_ &&
        t.cat != compiler__compiler__TypeCategory_objc_interface) {

      continue;
    };

    if (t.cat == compiler__compiler__TypeCategory_objc_interface) {

      strings__Builder_writeln(
          &/* ? */ sb, _STR("@interface %.*s : %.*s { @public", t.name.len,
                            t.name.str, t.parent.len, t.parent.str));

    } else {

      string kind = (t.cat == compiler__compiler__TypeCategory_union_)
                        ? (tos3("union"))
                        : (tos3("struct"));

      strings__Builder_writeln(
          &/* ? */ sb,
          _STR("%.*s %.*s {", kind.len, kind.str, t.name.len, t.name.str));
    };

    array_compiler__Var tmp15 = t.fields;
    for (int tmp16 = 0; tmp16 < tmp15.len; tmp16++) {
      compiler__Var field = ((compiler__Var *)tmp15.data)[tmp16];

      strings__Builder_write(&/* ? */ sb, tos3("\t"));

      strings__Builder_writeln(
          &/* ? */ sb, string_add(compiler__Table_cgen_name_type_pair(
                                      &/* ? */ *table, field.name, field.typ),
                                  tos3(";")));
    };

    strings__Builder_writeln(&/* ? */ sb, tos3("};\n"));

    if (t.cat == compiler__compiler__TypeCategory_objc_interface) {

      strings__Builder_writeln(&/* ? */ sb, tos3("@end"));
    };
  };

  return strings__Builder_str(sb);
}
void compiler__Parser_index_get(compiler__Parser *p, string typ, int fn_ph,
                                compiler__IndexConfig cfg) {

  string index_expr = tos3("");

  if (p->cgen->is_tmp) {

    index_expr = string_substr2(p->cgen->tmp_line, fn_ph, -1, true);

    compiler__CGen_resetln(p->cgen,
                           string_substr2(p->cgen->tmp_line, 0, fn_ph, false));

  } else {

    index_expr = string_substr2(p->cgen->cur_line, fn_ph, -1, true);

    compiler__CGen_resetln(p->cgen,
                           string_substr2(p->cgen->cur_line, 0, fn_ph, false));
  };

  string tmp = compiler__Parser_get_tmp(p);

  string tmp_ok = compiler__Parser_get_tmp(p);

  if (cfg.is_map) {

    compiler__Parser_gen(p, _STR("%.*s", tmp.len, tmp.str));

    string def = compiler__type_default(typ);

    compiler__CGen_insert_before(
        p->cgen,
        string_add(_STR("%.*s %.*s = %.*s; ", typ.len, typ.str, tmp.len,
                        tmp.str, def.len, def.str),
                   _STR("bool %.*s = map_get(/*%.*s : %d*/%.*s, & %.*s);",
                        tmp_ok.len, tmp_ok.str, p->file_name.len,
                        p->file_name.str, p->scanner->line_nr, index_expr.len,
                        index_expr.str, tmp.len, tmp.str)));

  } else if (cfg.is_arr) {

    if (p->pref->translated && !p->builtin_mod) {

      compiler__Parser_gen(p, _STR("%.*s ]", index_expr.len, index_expr.str));

    } else {

      string ref = (cfg.is_ptr) ? (tos3("*")) : (tos3(""));

      if (cfg.is_slice) {

        compiler__Parser_gen(p, _STR(" array_slice2(%.*s %.*s) ", ref.len,
                                     ref.str, index_expr.len, index_expr.str));

      } else {

        compiler__Parser_gen(p, _STR("( *(%.*s*) array_get(%.*s %.*s) )",
                                     typ.len, typ.str, ref.len, ref.str,
                                     index_expr.len, index_expr.str));
      };
    };

  } else if (cfg.is_str && !p->builtin_mod) {

    if (cfg.is_slice) {

      compiler__Parser_gen(
          p, _STR("string_substr2(%.*s)", index_expr.len, index_expr.str));

    } else {

      compiler__Parser_gen(
          p, _STR("string_at(%.*s)", index_expr.len, index_expr.str));
    };
  };

  if (cfg.is_map && string_eq(typ, tos3("string"))) {

    compiler__CGen_insert_before(
        p->cgen, _STR("if (!%.*s) %.*s = tos((byte *)\"\", 0);", tmp_ok.len,
                      tmp_ok.str, tmp.len, tmp.str));
  };
}
string compiler__Table_fn_gen_name(compiler__Table *table, compiler__Fn *f) {

  string name = f->name;

  if (f->is_method) {

    name = _STR("%.*s_%.*s", f->receiver_typ.len, f->receiver_typ.str,
                f->name.len, f->name.str);

    name = string_replace(name, tos3(" "), tos3(""));

    if (f->name.len == 1) {

      byte tmp27 = string_at(f->name, 0);

      if (tmp27 == '+') {

        name = string_replace(name, tos3("+"), tos3("op_plus"));

      } else if (tmp27 == '-') {

        name = string_replace(name, tos3("-"), tos3("op_minus"));

      } else if (tmp27 == '*') {

        name = string_replace(name, tos3("*"), tos3("op_mul"));

      } else if (tmp27 == '/') {

        name = string_replace(name, tos3("/"), tos3("op_div"));

      } else if (tmp27 == '%') {

        name = string_replace(name, tos3("%"), tos3("op_mod"));
      };
    };
  };

  if (string_eq(f->mod, tos3("builtin")) &&
      (_IN(string, (f->name), compiler__CReserved))) {

    return _STR("v_%.*s", name.len, name.str);
  };

  if (table->obfuscate && !f->is_c && string_ne(f->name, tos3("main")) &&
      string_ne(f->name, tos3("WinMain")) &&
      string_ne(f->name, tos3("main__main")) &&
      string_ne(f->name, tos3("gg__vec2")) &&
      string_ne(f->name, tos3("build_token_str")) &&
      string_ne(f->name, tos3("build_keys")) &&
      string_ne(f->mod, tos3("builtin")) && string_ne(f->mod, tos3("darwin")) &&
      string_ne(f->mod, tos3("os")) && string_ne(f->mod, tos3("json")) &&
      !string_ends_with(f->name, tos3("_init")) &&
      !string_contains(f->name, tos3("window_proc")) &&
      !string_ends_with(name, tos3("_str")) &&
      !string_contains(name, tos3("contains"))) {

    int tmp28 = 0;
    bool tmp29 = map_get(/*gen_c.v : 265*/ table->obf_ids, name, &tmp28);

    int idx = tmp28;

    if (idx == 0) {

      table->fn_cnt++;

      map_set(&table->obf_ids, name, &(int[]){table->fn_cnt});

      idx = table->fn_cnt;
    };

    string old = name;

    name = _STR("f_%d", idx);

    printf("%.*s ==> %.*s\n", old.len, old.str, name.len, name.str);
  };

  return name;
}
void compiler__Parser_gen_method_call(compiler__Parser *p,
                                      compiler__Var *receiver,
                                      string receiver_type, string cgen_name,
                                      string ftyp, int method_ph) {

  string method_call = string_add(cgen_name, tos3(" ("));

  if (receiver->ref ||
      (receiver->is_mut && !string_contains(receiver_type, tos3("*")))) {

    method_call = string_add(method_call, tos3("& /* ? */"));
  };

  if (!receiver->is_mut && string_contains(receiver_type, tos3("*"))) {

    method_call = string_add(method_call, tos3("*"));
  };

  string cast = tos3("");

  if (string_eq(ftyp, tos3("void*"))) {

    if (string_starts_with(receiver_type, tos3("array_"))) {

      cast = string_all_after(receiver_type, tos3("array_"));

      cast = _STR("*(%.*s*) ", cast.len, cast.str);

    } else {

      cast = tos3("(voidptr) ");
    };
  };

  compiler__CGen_set_placeholder(
      p->cgen, method_ph,
      _STR("%.*s %.*s", cast.len, cast.str, method_call.len, method_call.str));
}
void compiler__Parser_gen_array_at(compiler__Parser *p, string typ_,
                                   bool is_arr0, int fn_ph) {

  string typ = typ_;

  if (string_eq(typ, tos3("array"))) {

    typ = tos3("void*");
  };

  if (p->pref->translated && !p->builtin_mod) {

    compiler__CGen_set_placeholder(p->cgen, fn_ph,
                                   _STR("((%.*s*)(", typ.len, typ.str));

    compiler__Parser_gen(p, tos3(".data))["));

  } else {

    compiler__Parser_gen(p, tos3(","));
  };
}
void compiler__Parser_gen_for_header(compiler__Parser *p, string i, string tmp,
                                     string var_typ, string val) {

  compiler__Parser_genln(
      p, _STR("for (int %.*s = 0; %.*s < %.*s.len; %.*s++) {", i.len, i.str,
              i.len, i.str, tmp.len, tmp.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  compiler__Parser_genln(p, _STR("%.*s %.*s = ((%.*s *) %.*s . data)[%.*s];",
                                 var_typ.len, var_typ.str, val.len, val.str,
                                 var_typ.len, var_typ.str, tmp.len, tmp.str,
                                 i.len, i.str));
}
void compiler__Parser_gen_for_str_header(compiler__Parser *p, string i,
                                         string tmp, string var_typ,
                                         string val) {

  compiler__Parser_genln(p,
                         _STR("array_byte bytes_%.*s = string_bytes( %.*s );",
                              tmp.len, tmp.str, tmp.len, tmp.str));

  compiler__Parser_genln(
      p, _STR(";\nfor (int %.*s = 0; %.*s < %.*s .len; %.*s ++) {", i.len,
              i.str, i.len, i.str, tmp.len, tmp.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  compiler__Parser_genln(
      p, _STR("%.*s %.*s = ((%.*s *) bytes_%.*s . data)[%.*s];", var_typ.len,
              var_typ.str, val.len, val.str, var_typ.len, var_typ.str, tmp.len,
              tmp.str, i.len, i.str));
}
void compiler__Parser_gen_for_range_header(compiler__Parser *p, string i,
                                           string range_end, string tmp,
                                           string var_type, string val) {

  compiler__Parser_genln(p,
                         _STR(";\nfor (int %.*s = %.*s; %.*s < %.*s; %.*s++) {",
                              i.len, i.str, tmp.len, tmp.str, i.len, i.str,
                              range_end.len, range_end.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  compiler__Parser_genln(p, _STR("%.*s %.*s = %.*s;", var_type.len,
                                 var_type.str, val.len, val.str, i.len, i.str));
}
void compiler__Parser_gen_for_map_header(compiler__Parser *p, string i,
                                         string tmp, string var_typ, string val,
                                         string typ) {

  string def = compiler__type_default(typ);

  compiler__Parser_genln(p, _STR("array_string keys_%.*s = map_keys(& %.*s ); ",
                                 tmp.len, tmp.str, tmp.len, tmp.str));

  compiler__Parser_genln(
      p, _STR("for (int l = 0; l < keys_%.*s .len; l++) {", tmp.len, tmp.str));

  compiler__Parser_genln(p, _STR("string %.*s = ((string*)keys_%.*s .data)[l];",
                                 i.len, i.str, tmp.len, tmp.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  compiler__Parser_genln(
      p, _STR("%.*s %.*s = %.*s; map_get(%.*s, %.*s, & %.*s);", var_typ.len,
              var_typ.str, val.len, val.str, def.len, def.str, tmp.len, tmp.str,
              i.len, i.str, val.len, val.str));
}
void compiler__Parser_gen_for_varg_header(compiler__Parser *p, string i,
                                          string varg, string var_typ,
                                          string val) {

  compiler__Parser_genln(
      p, _STR("for (int %.*s = 0; %.*s < %.*s->len; %.*s++) {", i.len, i.str,
              i.len, i.str, varg.len, varg.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  compiler__Parser_genln(p, _STR("%.*s %.*s = ((%.*s *) %.*s->args)[%.*s];",
                                 var_typ.len, var_typ.str, val.len, val.str,
                                 var_typ.len, var_typ.str, varg.len, varg.str,
                                 i.len, i.str));
}
void compiler__Parser_gen_array_init(compiler__Parser *p, string typ,
                                     bool no_alloc, int new_arr_ph,
                                     int nr_elems) {

  string new_arr = tos3("new_array_from_c_array");

  if (no_alloc) {

    new_arr = string_add(new_arr, tos3("_no_alloc"));
  };

  if (nr_elems == 0) {

    compiler__Parser_gen(p, tos3(" TCCSKIP(0) })"));

  } else {

    compiler__Parser_gen(p, tos3(" })"));
  };

  if (!compiler__Parser_first_pass(&/* ? */ *p)) {

    compiler__CGen_set_placeholder(
        p->cgen, new_arr_ph,
        _STR("%.*s(%d, %d, sizeof(%.*s), EMPTY_ARRAY_OF_ELEMS( %.*s, %d ) { ",
             new_arr.len, new_arr.str, nr_elems, nr_elems, typ.len, typ.str,
             typ.len, typ.str, nr_elems));
  };
}
void compiler__Parser_gen_array_set(compiler__Parser *p, string typ,
                                    bool is_ptr, bool is_map, int fn_ph,
                                    int assign_pos, bool is_cao) {

  string val = string_substr2(p->cgen->cur_line, assign_pos, -1, true);

  compiler__CGen_resetln(
      p->cgen, string_substr2(p->cgen->cur_line, 0, assign_pos, false));

  string cao_tmp = p->cgen->cur_line;

  string func = tos3("");

  if (is_map) {

    func = tos3("map_set(&");

  } else {

    if (is_ptr) {

      func = tos3("array_set(");

      if (is_cao) {

        cao_tmp = _STR("*(%.*s *) array_get(*%.*s)", p->expected_type.len,
                       p->expected_type.str, cao_tmp.len, cao_tmp.str);
      };

    } else {

      func = tos3("array_set(&/*q*/");

      if (is_cao) {

        cao_tmp = _STR("*(%.*s *) array_get(%.*s)", p->expected_type.len,
                       p->expected_type.str, cao_tmp.len, cao_tmp.str);
      };
    };
  };

  compiler__CGen_set_placeholder(p->cgen, fn_ph, func);

  if (is_cao) {

    val = string_add(string_add(cao_tmp, string_all_before(val, tos3("="))),
                     string_all_after(val, tos3("=")));
  };

  compiler__Parser_gen(
      p, _STR(", & (%.*s []) { %.*s })", typ.len, typ.str, val.len, val.str));
}
bool compiler__Parser_gen_struct_init(compiler__Parser *p, string typ,
                                      compiler__Type t) {

  if (p->is_c_struct_init) {

    if (t.cat != compiler__compiler__TypeCategory_c_typedef) {

      compiler__CGen_insert_before(p->cgen, tos3("struct /*c struct init*/"));
    };
  };

  if (string_eq(typ, tos3("tm"))) {

    array_set(&/*q*/ p->cgen->lines, p->cgen->lines.len - 1,
              &(string[]){tos3("")});
  };

  compiler__Parser_next(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  bool ptr = string_contains(typ, tos3("*"));

  if (!ptr) {

    if (p->is_c_struct_init) {

      if (p->tok == compiler__compiler__TokenKind_rcbr) {

        p->is_empty_c_struct_init = 1;

        compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

        return 1;
      };

      compiler__Parser_gen(p, _STR("(struct %.*s) {", typ.len, typ.str));

      p->is_c_struct_init = 0;

    } else {

      compiler__Parser_gen(p, _STR("(%.*s) {", typ.len, typ.str));
    };

  } else {

    if (p->tok == compiler__compiler__TokenKind_not) {

      compiler__Parser_next(p);

      compiler__Parser_gen(p, tos3("0"));

      compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

      return 1;
    };

    compiler__Parser_gen(p, _STR("(%.*s*)memdup(&(%.*s)  {", t.name.len,
                                 t.name.str, t.name.len, t.name.str));
  };

  return 0;
}
void compiler__Parser_gen_struct_field_init(compiler__Parser *p, string field) {

  compiler__Parser_gen(p, _STR(".%.*s = ", field.len, field.str));
}
void compiler__Parser_gen_empty_map(compiler__Parser *p, string typ) {

  compiler__Parser_gen(p, _STR("new_map(1, sizeof(%.*s))", typ.len, typ.str));
}
void compiler__Parser_cast(compiler__Parser *p, string typ) {

  compiler__Parser_next(p);

  int pos = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  if (p->tok == compiler__compiler__TokenKind_rpar) {

    p->ptr_cast = 1;

    compiler__Parser_next(p);
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  p->expected_type = typ;

  string expr_typ = compiler__Parser_bool_expression(p);

  bool casting_voidptr_to_value =
      string_eq(expr_typ, tos3("void*")) && string_ne(typ, tos3("int")) &&
      string_ne(typ, tos3("byteptr")) && !string_ends_with(typ, tos3("*"));

  p->expected_type = tos3("");

  bool is_byteptr = string_eq(expr_typ, tos3("byte*")) ||
                    string_eq(expr_typ, tos3("byteptr"));

  bool is_bytearr = string_eq(expr_typ, tos3("array_byte"));

  if (string_eq(typ, tos3("string"))) {

    if (is_byteptr || is_bytearr) {

      if (p->tok == compiler__compiler__TokenKind_comma) {

        compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

        compiler__CGen_set_placeholder(p->cgen, pos, tos3("tos((byte *)"));

        if (is_bytearr) {

          compiler__Parser_gen(p, tos3(".data"));
        };

        compiler__Parser_gen(p, tos3(", "));

        compiler__Parser_check_types(p, compiler__Parser_expression(p),
                                     tos3("int"));

      } else {

        if (is_bytearr) {

          compiler__Parser_gen(p, tos3(".data"));
        };

        compiler__CGen_set_placeholder(p->cgen, pos, tos3("tos2((byte *)"));
      };

    } else if (string_eq(expr_typ, tos3("int"))) {

      compiler__Parser_error(
          p, _STR("cannot cast `%.*s` to `%.*s`, use `str()` method instead",
                  expr_typ.len, expr_typ.str, typ.len, typ.str));

    } else {

      compiler__Parser_error(p,
                             _STR("cannot cast `%.*s` to `%.*s`", expr_typ.len,
                                  expr_typ.str, typ.len, typ.str));
    };

  } else if (string_eq(typ, tos3("byte")) &&
             string_eq(expr_typ, tos3("string"))) {

    compiler__Parser_error(
        p, _STR("cannot cast `%.*s` to `%.*s`, use backquotes `` to create a "
                "`%.*s` or access the value of an index of `%.*s` using []",
                expr_typ.len, expr_typ.str, typ.len, typ.str, typ.len, typ.str,
                expr_typ.len, expr_typ.str));

  } else if (casting_voidptr_to_value) {

    compiler__CGen_set_placeholder(p->cgen, pos,
                                   _STR("*(%.*s*)(", typ.len, typ.str));

  } else {

    if (string_eq(typ, tos3("bool"))) {

      if (compiler__is_number_type(expr_typ) ||
          compiler__is_float_type(expr_typ)) {

        compiler__Parser_error(p, tos3("cannot cast a number to `bool`"));
      };

      compiler__Parser_error(
          p, _STR("cannot cast `%.*s` to `bool`", expr_typ.len, expr_typ.str));
    };

    if (string_eq(expr_typ, tos3("string"))) {

      compiler__Parser_error(p,
                             _STR("cannot cast `%.*s` to `%.*s`", expr_typ.len,
                                  expr_typ.str, typ.len, typ.str));
    };

    compiler__CGen_set_placeholder(p->cgen, pos,
                                   _STR("(%.*s)(", typ.len, typ.str));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  compiler__Parser_gen(p, tos3(")"));
}
string compiler__type_default(string typ) {

  if (string_starts_with(typ, tos3("array_"))) {

    return _STR("new_array(0, 1, sizeof( %.*s ))",
                string_substr2(typ, 6, -1, true).len,
                string_substr2(typ, 6, -1, true).str);
  };

  if (string_ends_with(typ, tos3("*"))) {

    return tos3("0");
  };

  if (string_contains(typ, tos3("__"))) {

    return tos3("{0}");
  };

  string tmp36 = typ;

  if (string_eq(tmp36, tos3("bool"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("string"))) {

    return tos3("tos3(\"\")");

  } else if (string_eq(tmp36, tos3("i8"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("i16"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("i64"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("u16"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("u32"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("u64"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("byte"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("int"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("rune"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("f32"))) {

    return tos3("0.0");

  } else if (string_eq(tmp36, tos3("f64"))) {

    return tos3("0.0");

  } else if (string_eq(tmp36, tos3("byteptr"))) {

    return tos3("0");

  } else if (string_eq(tmp36, tos3("voidptr"))) {

    return tos3("0");
  };

  return tos3("{0}");
}
void compiler__Parser_gen_array_push(compiler__Parser *p, int ph, string typ,
                                     string expr_type, string tmp,
                                     string elm_type) {

  bool push_array = string_eq(typ, expr_type);

  if (push_array) {

    compiler__CGen_set_placeholder(p->cgen, ph, tos3("_PUSH_MANY(&"));

    compiler__Parser_gen(
        p, _STR("), %.*s, %.*s)", tmp.len, tmp.str, typ.len, typ.str));

  } else {

    compiler__Parser_check_types(p, expr_type, elm_type);

    string push_call = (string_contains(typ, tos3("*"))) ? (tos3("_PUSH("))
                                                         : (tos3("_PUSH(&"));

    compiler__CGen_set_placeholder(p->cgen, ph, push_call);

    if (string_ends_with(elm_type, tos3("*"))) {

      compiler__Parser_gen(
          p, _STR("), %.*s, %.*s)", tmp.len, tmp.str,
                  string_substr2(elm_type, 0, elm_type.len - 1, false).len,
                  string_substr2(elm_type, 0, elm_type.len - 1, false).str));

    } else {

      compiler__Parser_gen(p, _STR("), %.*s, %.*s)", tmp.len, tmp.str,
                                   elm_type.len, elm_type.str));
    };
  };
}
void compiler__Parser_gen_json_for_type(compiler__Parser *p,
                                        compiler__Type typ) {

  string dec = tos3("");

  string enc = tos3("");

  string t = typ.name;

  if (string_eq(t, tos3("int")) || string_eq(t, tos3("string")) ||
      string_eq(t, tos3("bool"))) {

    return;
  };

  if (compiler__Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  compiler__Fn dec_fn =
      (compiler__Fn){.mod = p->mod,
                     .typ = _STR("Option_%.*s", typ.name.len, typ.name.str),
                     .name = compiler__js_dec_name(t),
                     .args = new_array(0, 1, sizeof(compiler__Var)),
                     .is_interface = 0,
                     .scope_level = 0,
                     .receiver_typ = tos3(""),
                     .is_c = 0,
                     .is_public = 0,
                     .is_method = 0,
                     .is_decl = 0,
                     .is_unsafe = 0,
                     .is_deprecated = 0,
                     .is_variadic = 0,
                     .is_generic = 0,
                     .returns_error = 0,
                     .defer_text = new_array(0, 1, sizeof(string)),
                     .type_pars = new_array(0, 1, sizeof(string)),
                     .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                     .body_idx = 0,
                     .fn_name_token_idx = 0,
                     .comptime_define = tos3(""),
                     .is_used = 0};

  if (compiler__Table_known_fn(&/* ? */ *p->table, dec_fn.name)) {

    return;
  };

  compiler__Var arg =
      (compiler__Var){.typ = tos3("cJSON*"),
                      .name = tos3(""),
                      .idx = 0,
                      .is_arg = 0,
                      .is_const = 0,
                      .args = new_array(0, 1, sizeof(compiler__Var)),
                      .attr = tos3(""),
                      .is_mut = 0,
                      .is_alloc = 0,
                      .is_returned = 0,
                      .ptr = 0,
                      .ref = 0,
                      .parent_fn = tos3(""),
                      .mod = tos3(""),
                      .is_global = 0,
                      .is_used = 0,
                      .is_changed = 0,
                      .scope_level = 0,
                      .is_c = 0,
                      .is_moved = 0,
                      .line_nr = 0,
                      .token_idx = 0,
                      .is_for_var = 0,
                      .is_public = 0};

  _PUSH(&dec_fn.args,
        (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ arg), tmp1,
        compiler__Var);

  compiler__Table_register_fn(p->table, dec_fn);

  compiler__Fn enc_fn =
      (compiler__Fn){.mod = p->mod,
                     .typ = tos3("cJSON*"),
                     .name = compiler__js_enc_name(t),
                     .args = new_array(0, 1, sizeof(compiler__Var)),
                     .is_interface = 0,
                     .scope_level = 0,
                     .receiver_typ = tos3(""),
                     .is_c = 0,
                     .is_public = 0,
                     .is_method = 0,
                     .is_decl = 0,
                     .is_unsafe = 0,
                     .is_deprecated = 0,
                     .is_variadic = 0,
                     .is_generic = 0,
                     .returns_error = 0,
                     .defer_text = new_array(0, 1, sizeof(string)),
                     .type_pars = new_array(0, 1, sizeof(string)),
                     .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                     .body_idx = 0,
                     .fn_name_token_idx = 0,
                     .comptime_define = tos3(""),
                     .is_used = 0};

  compiler__Var enc_arg =
      (compiler__Var){.typ = t,
                      .name = tos3(""),
                      .idx = 0,
                      .is_arg = 0,
                      .is_const = 0,
                      .args = new_array(0, 1, sizeof(compiler__Var)),
                      .attr = tos3(""),
                      .is_mut = 0,
                      .is_alloc = 0,
                      .is_returned = 0,
                      .ptr = 0,
                      .ref = 0,
                      .parent_fn = tos3(""),
                      .mod = tos3(""),
                      .is_global = 0,
                      .is_used = 0,
                      .is_changed = 0,
                      .scope_level = 0,
                      .is_c = 0,
                      .is_moved = 0,
                      .line_nr = 0,
                      .token_idx = 0,
                      .is_for_var = 0,
                      .is_public = 0};

  _PUSH(&enc_fn.args,
        (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ enc_arg), tmp2,
        compiler__Var);

  compiler__Table_register_fn(p->table, enc_fn);

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

  if (string_starts_with(t, tos3("array_"))) {

    dec = string_add(dec, compiler__Parser_decode_array(p, t));

    enc = string_add(enc, compiler__Parser_encode_array(&/* ? */ *p, t));
  };

  array_compiler__Var tmp3 = typ.fields;
  for (int tmp4 = 0; tmp4 < tmp3.len; tmp4++) {
    compiler__Var field = ((compiler__Var *)tmp3.data)[tmp4];

    if (string_eq(field.attr, tos3("skip"))) {

      continue;
    };

    string name = (string_starts_with(field.attr, tos3("json:")))
                      ? (string_substr2(field.attr, 5, -1, true))
                      : (field.name);

    compiler__Type field_type =
        compiler__Table_find_type(&/* ? */ *p->table, field.typ);

    string _typ = string_replace(field.typ, tos3("*"), tos3(""));

    string enc_name = compiler__js_enc_name(_typ);

    if (string_eq(field.attr, tos3("raw"))) {

      dec = string_add(
          dec,
          string_add(_STR(" res->%.*s = tos2(cJSON_PrintUnformatted(",
                          field.name.len, field.name.str),
                     _STR("js_get(root, \"%.*s\")));\n", name.len, name.str)));

    } else {

      compiler__Parser_gen_json_for_type(p, field_type);

      string dec_name = compiler__js_dec_name(_typ);

      if (compiler__is_js_prim(_typ)) {

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

      dec = string_add(dec, tos3(";\n"));
    };

    enc = string_add(
        enc, _STR("  cJSON_AddItemToObject(o,  \"%.*s\",%.*s(val.%.*s)); \n",
                  name.len, name.str, enc_name.len, enc_name.str,
                  field.name.len, field.name.str));
  };

  _PUSH(&p->cgen->fns,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "%.*s return opt_ok(res, sizeof(*res)); \n}", dec.len, dec.str)),
        tmp7, string);

  _PUSH(&p->cgen->fns,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/*enc start*/ %.*s return o;}", enc.len, enc.str)),
        tmp8, string);
}
bool compiler__is_js_prim(string typ) {

  return string_eq(typ, tos3("int")) || string_eq(typ, tos3("string")) ||
         string_eq(typ, tos3("bool")) || string_eq(typ, tos3("f32")) ||
         string_eq(typ, tos3("f64")) || string_eq(typ, tos3("i8")) ||
         string_eq(typ, tos3("i16")) || string_eq(typ, tos3("i64")) ||
         string_eq(typ, tos3("u16")) || string_eq(typ, tos3("u32")) ||
         string_eq(typ, tos3("u64"));
}
string compiler__Parser_decode_array(compiler__Parser *p, string array_type) {

  string typ = string_replace(array_type, tos3("array_"), tos3(""));

  compiler__Type t = compiler__Table_find_type(&/* ? */ *p->table, typ);

  string fn_name = compiler__js_dec_name(typ);

  compiler__Parser_gen_json_for_type(p, t);

  string s = tos3("");

  if (compiler__is_js_prim(typ)) {

    s = _STR("%.*s val= %.*s(jsval); ", typ.len, typ.str, fn_name.len,
             fn_name.str);

  } else {

    s = _STR("  %.*s val; %.*s(jsval, &val); ", typ.len, typ.str, fn_name.len,
             fn_name.str);
  };

  return _STR("\n*res = new_array(0, 0, sizeof(%.*s));\nconst cJSON *jsval = "
              "NULL;\ncJSON_ArrayForEach(jsval, root)\n{\n%.*s\n  "
              "array_push(res, &val);\n}\n",
              typ.len, typ.str, s.len, s.str);
}
string compiler__js_enc_name(string typ) {

  string name = _STR("json__jsencode_%.*s", typ.len, typ.str);

  return name;
}
string compiler__js_dec_name(string typ) {

  string name = _STR("json__jsdecode_%.*s", typ.len, typ.str);

  return name;
}
string compiler__Parser_encode_array(compiler__Parser *p, string array_type) {

  string typ = string_replace(array_type, tos3("array_"), tos3(""));

  string fn_name = compiler__js_enc_name(typ);

  return _STR(
      "\no = cJSON_CreateArray();\nfor (int i = 0; i < val.len; i++){\n  "
      "cJSON_AddItemToArray(o, %.*s(  ((%.*s*)val.data)[i]  ));\n}\n",
      fn_name.len, fn_name.str, typ.len, typ.str);
}
array_string
compiler__V_generate_hotcode_reloading_compiler_flags(compiler__V *v) {

  array_string a = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (v->pref->is_live || v->pref->is_so) {

    if ((v->os == compiler__compiler__OS_linux ||
         string_eq(os__user_os(), tos3("linux")))) {

      _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-rdynamic")),
            tmp1, string);
    };

    if ((v->os == compiler__compiler__OS_mac ||
         string_eq(os__user_os(), tos3("mac")))) {

      _PUSH(&a,
            (/*typ = array_string   tmp_typ=string*/ tos3("-flat_namespace")),
            tmp2, string);
    };
  };

  return a;
}
void compiler__V_generate_hotcode_reloading_declarations(compiler__V *v) {

  compiler__CGen *cgen = v->cgen;

  if (v->os != compiler__compiler__OS_windows) {

    if (v->pref->is_so) {

      compiler__CGen_genln(cgen, tos3("pthread_mutex_t live_fn_mutex;"));
    };

    if (v->pref->is_live) {

      compiler__CGen_genln(
          cgen,
          tos3("pthread_mutex_t live_fn_mutex = PTHREAD_MUTEX_INITIALIZER;"));
    };

  } else {

    if (v->pref->is_so) {

      compiler__CGen_genln(cgen, tos3("HANDLE live_fn_mutex;"));

      compiler__CGen_genln(
          cgen,
          tos3("\nvoid pthread_mutex_lock(HANDLE *m) {\n	"
               "WaitForSingleObject(*m, INFINITE);\n}\n\nvoid "
               "pthread_mutex_unlock(HANDLE *m) {\n	ReleaseMutex(*m);\n}"));
    };

    if (v->pref->is_live) {

      compiler__CGen_genln(cgen, tos3("HANDLE live_fn_mutex = 0;"));
    };
  };
}
void compiler__V_generate_hotcode_reloading_main_caller(compiler__V *v) {

  if (!v->pref->is_live) {

    return;
  };

  compiler__CGen *cgen = v->cgen;

  compiler__CGen_genln(cgen, tos3(""));

  string file_base = string_replace(os__filename(v->dir), tos3(".v"), tos3(""));

  if (v->os != compiler__compiler__OS_windows) {

    string so_name = string_add(file_base, tos3(".so"));

    compiler__CGen_genln(cgen, _STR("  char *live_library_name = \"%.*s\";",
                                    so_name.len, so_name.str));

    compiler__CGen_genln(cgen, tos3("  load_so(live_library_name);"));

    compiler__CGen_genln(cgen, tos3("  pthread_t _thread_so;"));

    compiler__CGen_genln(cgen, tos3("  pthread_create(&_thread_so , NULL, "
                                    "(void *)&reload_so, live_library_name);"));

  } else {

    string so_name =
        string_add(file_base, (string_eq(v->pref->ccompiler, tos3("msvc")))
                                  ? (tos3(".dll"))
                                  : (tos3(".so")));

    compiler__CGen_genln(cgen, _STR("  char *live_library_name = \"%.*s\";",
                                    so_name.len, so_name.str));

    compiler__CGen_genln(cgen,
                         tos3("  live_fn_mutex = CreateMutexA(0, 0, 0);"));

    compiler__CGen_genln(cgen, tos3("  load_so(live_library_name);"));

    compiler__CGen_genln(cgen, tos3("  unsigned long _thread_so;"));

    compiler__CGen_genln(cgen,
                         tos3("  _thread_so = CreateThread(0, 0, "
                              "(LPTHREAD_START_ROUTINE)&reload_so, 0, 0, 0);"));
  };
}
void compiler__V_generate_hot_reload_code(compiler__V *v) {

  compiler__CGen *cgen = v->cgen;

  if (v->pref->is_live) {

    string file = os__realpath(v->dir);

    string file_base = string_replace(os__filename(file), tos3(".v"), tos3(""));

    string so_name = string_add(file_base, tos3(".so"));

    string vexe = (*(string *)array_get(os__args, 0));

    if (string_eq(os__user_os(), tos3("windows"))) {

      vexe = compiler__cescaped_path(vexe);

      file = compiler__cescaped_path(file);
    };

    string msvc = tos3("");

    if (string_eq(v->pref->ccompiler, tos3("msvc"))) {

      msvc = tos3("-cc msvc");
    };

    string so_debug_flag = (v->pref->is_debug) ? (tos3("-g")) : (tos3(""));

    string cmd_compile_shared_library =
        _STR("%.*s %.*s %.*s -o %.*s -shared %.*s", vexe.len, vexe.str,
             msvc.len, msvc.str, so_debug_flag.len, so_debug_flag.str,
             file_base.len, file_base.str, file.len, file.str);

    if (v->pref->show_c_cmd) {

      println(cmd_compile_shared_library);
    };

    i64 ticks = time__ticks();

    os__system(cmd_compile_shared_library);

    i64 diff = time__ticks() - ticks;

    printf("compiling shared library took %lld ms\n", diff);

    println(tos3("=========\n"));

    compiler__CGen_genln(
        cgen, tos3("\n\nvoid lfnmutex_print(char *s){\n	if(0){\n	"
                   "	fflush(stderr);\n		fprintf(stderr,\">> "
                   "live_fn_mutex: %p | %s\\n\", &live_fn_mutex, s);\n	"
                   "	fflush(stderr);\n	}\n}\n"));

    if (v->os != compiler__compiler__OS_windows) {

      compiler__CGen_genln(
          cgen,
          tos3(
              "\n#include <dlfcn.h>\nvoid* live_lib=0;\nint load_so(byteptr "
              "path) {\n	char cpath[1024];\n	"
              "sprintf(cpath,\"./%s\", path);\n	//printf(\"load_so %s\\n\", "
              "cpath);\n	if (live_lib) dlclose(live_lib);\n	"
              "live_lib = dlopen(cpath, RTLD_LAZY);\n	if (!live_lib) "
              "{\n		puts(\"open failed\");\n		"
              "exit(1);\n		return 0;\n	}\n"));

      array_string tmp5 = cgen->so_fns;
      for (int tmp6 = 0; tmp6 < tmp5.len; tmp6++) {
        string so_fn = ((string *)tmp5.data)[tmp6];

        compiler__CGen_genln(cgen,
                             _STR("%.*s = dlsym(live_lib, \"%.*s\");  ",
                                  so_fn.len, so_fn.str, so_fn.len, so_fn.str));
      };

    } else {

      compiler__CGen_genln(
          cgen, tos3("\nvoid pthread_mutex_lock(HANDLE *m) {\n	"
                     "WaitForSingleObject(*m, INFINITE);\n}\n\nvoid "
                     "pthread_mutex_unlock(HANDLE *m) {\n	"
                     "ReleaseMutex(*m);\n}\n\nvoid* live_lib=0;\nint "
                     "load_so(byteptr path) {\n	char cpath[1024];\n	"
                     "sprintf(cpath, \"./%s\", path);\n	if (live_lib) "
                     "FreeLibrary(live_lib);\n	live_lib = "
                     "LoadLibraryA(cpath);\n	if (!live_lib) {\n	"
                     "	puts(\"open failed\");\n		"
                     "exit(1);\n		return 0;\n	}\n"));

      array_string tmp7 = cgen->so_fns;
      for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
        string so_fn = ((string *)tmp7.data)[tmp8];

        compiler__CGen_genln(
            cgen, _STR("%.*s = (void *)GetProcAddress(live_lib, \"%.*s\");  ",
                       so_fn.len, so_fn.str, so_fn.len, so_fn.str));
      };
    };

    compiler__CGen_genln(
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

    compiler__CGen_genln(cgen,
                         tos3(" int load_so(byteptr path) { return 0; }"));
  };
}
void compiler__V_finalize_compilation(compiler__V *v) {

  if (v->pref->autofree) {
  };
}
int compiler__V_add_parser(compiler__V *v, compiler__Parser parser) {

  _PUSH(&v->parsers,
        (/*typ = array_compiler__Parser   tmp_typ=compiler__Parser*/ parser),
        tmp1, compiler__Parser);

  int pidx = v->parsers.len - 1;

  map_set(&v->file_parser_idx, os__realpath(parser.file_path), &(int[]){pidx});

  return pidx;
}
Option_int compiler__V_get_file_parser_index(compiler__V *v, string file) {

  string file_path = os__realpath(file);

  if ((_IN_MAP((file_path), v->file_parser_idx))) {

    int tmp2 = 0;
    bool tmp3 = map_get(/*main.v : 155*/ v->file_parser_idx, file_path, &tmp2);

    int tmp4 = OPTION_CAST(int)(tmp2);
    return opt_ok(&tmp4, sizeof(int));
  };

  return v_error(_STR("parser for \"%.*s\" not found", file.len, file.str));
}
int compiler__V_parse(compiler__V *v, string file, compiler__Pass pass) {

  Option_int tmp5 = compiler__V_get_file_parser_index(&/* ? */ *v, file);
  int pidx;
  if (!tmp5.ok) {
    string err = tmp5.error;
    int errcode = tmp5.ecode;

    compiler__Parser p = compiler__V_new_parser_from_file(v, file);

    compiler__Parser_parse(&/* ? */ p, pass);

    return compiler__V_add_parser(v, p);
  }
  pidx = *(int *)tmp5.data;
  ;

  compiler__Parser_parse(
      &/* ? */ (*(compiler__Parser *)array_get(v->parsers, pidx)), pass);

  return pidx;
}
void compiler__V_compile(compiler__V *v) {

  if (string_ne(os__user_os(), tos3("windows")) &&
      string_eq(v->pref->ccompiler, tos3("msvc"))) {

    compiler__verror(_STR("Cannot build with msvc on %.*s", os__user_os().len,
                          os__user_os().str));
  };

  compiler__CGen *cgen = v->cgen;

  compiler__CGen_genln(cgen, tos3("// Generated by V"));

  if (v->pref->is_verbose) {

    println(tos3("all .v files before:"));

    println(array_string_str(v->files));
  };

  compiler__V_add_v_files_to_compile(v);

  if (v->pref->is_verbose || v->pref->is_debug) {

    println(tos3("all .v files:"));

    println(array_string_str(v->files));
  };

  array_string tmp8 = v->files;
  for (int tmp9 = 0; tmp9 < tmp8.len; tmp9++) {
    string file = ((string *)tmp8.data)[tmp9];

    compiler__V_parse(v, file, compiler__compiler__Pass_decl);
  };

  cgen->pass = compiler__compiler__Pass_main;

  if (v->pref->is_debug) {

#ifdef _VJS

    compiler__CGen_genln(cgen, tos3("const VDEBUG = 1;\n"));

#else

    compiler__CGen_genln(cgen, tos3("#define VDEBUG (1)"));

#endif
    ;
  };

  if (v->os == compiler__compiler__OS_js) {

    compiler__CGen_genln(cgen, tos3("#define _VJS (1) "));
  };

  string v_hash = compiler__vhash();

#ifdef _VJS

  compiler__CGen_genln(
      cgen, _STR("const V_COMMIT_HASH = \"%.*s\";\n", v_hash.len, v_hash.str));

#else

  compiler__CGen_genln(cgen, tos3("#ifndef V_COMMIT_HASH"));

  compiler__CGen_genln(
      cgen, _STR("#define V_COMMIT_HASH \"%.*s\"", v_hash.len, v_hash.str));

  compiler__CGen_genln(cgen, tos3("#endif"));

#endif
  ;

  bool q = cgen->nogen;

  cgen->nogen = 0;

#ifdef _VJS

  compiler__CGen_genln(cgen, compiler__js_headers);

#else

  compiler__CGen_genln(cgen, compiler__CommonCHeaders);

#endif
  ;

  compiler__V_generate_hotcode_reloading_declarations(&/* ? */ *v);

  bool imports_json = (_IN(string, (tos3("json")), v->table->imports));

  if (v->pref->build_mode == compiler__compiler__BuildMode_default_mode) {

    if (imports_json) {

      compiler__CGen_genln(cgen, tos3("#include \"cJSON.h\""));
    };
  };

  if (v->pref->build_mode == compiler__compiler__BuildMode_default_mode) {

#ifndef _VJS

    compiler__CGen_genln(cgen, tos3("int g_test_oks = 0;"));

    compiler__CGen_genln(cgen, tos3("int g_test_fails = 0;"));

#endif
    ;

    if (imports_json) {

      compiler__CGen_genln(
          cgen, tos3("\n#define js_get(object, key) "
                     "cJSON_GetObjectItemCaseSensitive((object), (key))\n"));
    };
  };

  if ((_IN(string, (tos3("-debug_alloc")), os__args))) {

    compiler__CGen_genln(cgen, tos3("#define DEBUG_ALLOC 1"));
  };

  compiler__CGen_genln(cgen,
                       tos3("// this line will be replaced with definitions"));

  int defs_pos = cgen->lines.len - 1;

  if (defs_pos == -1) {

    defs_pos = 0;
  };

  cgen->nogen = q;

  array_string tmp10 = v->files;
  for (int tmp11 = 0; tmp11 < tmp10.len; tmp11++) {
    string file = ((string *)tmp10.data)[tmp11];

    compiler__V_parse(v, file, compiler__compiler__Pass_main);

    if (!v->pref->nofmt && !string_contains(file, tos3("/vlib/"))) {
    };
  };

  if (v->pref->build_mode == compiler__compiler__BuildMode_build_module) {

    compiler__generate_vh(v->dir);
  };

  compiler__Parser vgen_parser =
      compiler__V_new_parser_from_string(v, strings__Builder_str(v->vgen_buf));

  vgen_parser.is_vgen = 1;

  strings__Builder_free(&/* ? */ v->vgen_buf);

  compiler__Parser_parse(&/* ? */ vgen_parser, compiler__compiler__Pass_main);

  strings__Builder def = strings__new_builder(10000);

#ifndef _VJS

  strings__Builder_writeln(&/* ? */ def,
                           array_string_join_lines(cgen->includes));

  strings__Builder_writeln(&/* ? */ def,
                           array_string_join_lines(cgen->typedefs));

  strings__Builder_writeln(&/* ? */ def,
                           compiler__V_type_definitions(&/* ? */ *v));

  strings__Builder_writeln(&/* ? */ def,
                           tos3("\nstring _STR(const char*, ...);\n"));

  strings__Builder_writeln(&/* ? */ def,
                           tos3("\nstring _STR_TMP(const char*, ...);\n"));

  strings__Builder_writeln(&/* ? */ def, array_string_join_lines(cgen->fns));

#else

  strings__Builder_writeln(&/* ? */ def,
                           compiler__V_type_definitions(&/* ? */ *v));

#endif
  ;

  strings__Builder_writeln(&/* ? */ def, array_string_join_lines(cgen->consts));

  strings__Builder_writeln(&/* ? */ def,
                           array_string_join_lines(cgen->thread_args));

  if (v->pref->is_prof) {

    strings__Builder_writeln(&/* ? */ def, tos3("; // Prof counters:"));

    strings__Builder_writeln(&/* ? */ def,
                             compiler__V_prof_counters(&/* ? */ *v));
  };

  array_set(&/*q*/ cgen->lines, defs_pos,
            &(string[]){strings__Builder_str(def)});

  compiler__V_generate_init(v);

  compiler__V_generate_main(v);

  compiler__V_generate_hot_reload_code(&/* ? */ *v);

  if (v->pref->is_verbose) {

    compiler__V_log(&/* ? */ *v, tos3("flags="));

    array_compiler__CFlag tmp12 = compiler__V_get_os_cflags(&/* ? */ *v);
    for (int tmp13 = 0; tmp13 < tmp12.len; tmp13++) {
      compiler__CFlag flag = ((compiler__CFlag *)tmp12.data)[tmp13];

      println(string_add(tos3(" * "), compiler__CFlag_format(&/* ? */ flag)));
    };
  };

#ifdef _VJS

  compiler__CGen_genln(cgen, tos3("main__main();"));

#endif
  ;

  compiler__CGen_save(cgen);

  compiler__V_cc(v);
}
void compiler__V_generate_init(compiler__V *v) {

#ifdef _VJS

  return;

#endif
  ;

  if (v->pref->build_mode == compiler__compiler__BuildMode_build_module) {

    bool nogen = v->cgen->nogen;

    v->cgen->nogen = 0;

    string consts_init_body = array_string_join_lines(v->cgen->consts_init);

    string init_fn_name =
        string_add(compiler__mod_gen_name(v->mod), tos3("__init_consts"));

    compiler__CGen_genln(
        v->cgen, _STR("void %.*s();\nvoid %.*s() {\n%.*s\n}", init_fn_name.len,
                      init_fn_name.str, init_fn_name.len, init_fn_name.str,
                      consts_init_body.len, consts_init_body.str));

    v->cgen->nogen = nogen;
  };

  if (v->pref->build_mode == compiler__compiler__BuildMode_default_mode) {

    string call_mod_init = tos3("");

    string call_mod_init_consts = tos3("");

    if ((_IN(string, (tos3("builtin")), v->cached_mods))) {

      compiler__CGen_genln(v->cgen, tos3("void builtin__init_consts();"));

      call_mod_init_consts =
          string_add(call_mod_init_consts, tos3("builtin__init_consts();\n"));
    };

    array_string tmp14 = v->table->imports;
    for (int tmp15 = 0; tmp15 < tmp14.len; tmp15++) {
      string mod = ((string *)tmp14.data)[tmp15];

      string init_fn_name =
          string_add(compiler__mod_gen_name(mod), tos3("__init"));

      if (compiler__Table_known_fn(&/* ? */ *v->table, init_fn_name)) {

        call_mod_init =
            string_add(call_mod_init,
                       _STR("%.*s();\n", init_fn_name.len, init_fn_name.str));
      };

      if ((_IN(string, (mod), v->cached_mods))) {

        compiler__CGen_genln(v->cgen, _STR("void %.*s_consts();",
                                           init_fn_name.len, init_fn_name.str));

        call_mod_init_consts = string_add(
            call_mod_init_consts,
            _STR("%.*s_consts();\n", init_fn_name.len, init_fn_name.str));
      };
    };

    string consts_init_body = array_string_join_lines(v->cgen->consts_init);

    compiler__CGen_genln(
        v->cgen,
        _STR(
            "void init() "
            "{\ng_str_buf=malloc(1000);\n%.*s\n%.*s\nbuiltin__init();\n%.*s\n}",
            call_mod_init_consts.len, call_mod_init_consts.str,
            consts_init_body.len, consts_init_body.str, call_mod_init.len,
            call_mod_init.str));

    compiler__CGen_genln(
        v->cgen,
        tos3("\nstring _STR(const char *fmt, ...) {\n	va_list "
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
             "fmt);\n	vsprintf((char *)g_str_buf, fmt, argptr);\n	"
             "va_end(argptr);\n#ifdef DEBUG_ALLOC\n	"
             "//puts(\"_STR_TMP:\");\n	//puts(g_str_buf);\n#endif\n	return "
             "tos2(g_str_buf);\n}\n\n"));
  };
}
void compiler__V_generate_main(compiler__V *v) {

  compiler__CGen *cgen = v->cgen;

#ifdef _VJS

  return;

#endif
  ;

  if (v->pref->is_vlines) {

    int lines_so_far =
        string_count(array_string_join(cgen->lines, tos3("\n")), tos3("\n")) +
        5;

    compiler__CGen_genln(cgen, tos3(""));

    compiler__CGen_genln(
        cgen,
        tos3("////////////////// Reset the file/line numbers //////////"));

    _PUSH(&cgen->lines,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "#line %d \"%.*s\"", lines_so_far,
              compiler__cescaped_path(os__realpath(cgen->out_path)).len,
              compiler__cescaped_path(os__realpath(cgen->out_path)).str)),
          tmp16, string);

    compiler__CGen_genln(cgen, tos3(""));
  };

  if (v->pref->build_mode != compiler__compiler__BuildMode_build_module) {

    if (!compiler__Table_main_exists(&/* ? */ *v->table) && !v->pref->is_test) {

      if (v->pref->is_script) {

        compiler__V_gen_main_start(v, 1);

        compiler__CGen_genln(
            cgen, _STR("%.*s;", cgen->fn_main.len, cgen->fn_main.str));

        compiler__V_gen_main_end(v, tos3("return 0"));

      } else {

        compiler__verror(
            tos3("function `main` is not declared in the main module"));
      };

    } else if (v->pref->is_test) {

      if (compiler__Table_main_exists(&/* ? */ *v->table)) {

        compiler__verror(tos3("test files cannot have function `main`"));
      };

      if (!compiler__Table_has_at_least_one_test_fn(&/* ? */ *v->table)) {

        compiler__verror(
            tos3("test files need to have at least one test function"));
      };

      compiler__V_gen_main_start(v, 0);

      if (v->pref->is_stats) {

        compiler__CGen_genln(cgen,
                             tos3("BenchedTests bt = main__start_testing();"));
      };

      map_compiler__Fn tmp17 = v->table->fns;
      array_string keys_tmp17 = map_keys(&tmp17);
      for (int l = 0; l < keys_tmp17.len; l++) {
        string _ = ((string *)keys_tmp17.data)[l];
        compiler__Fn f = {0};
        map_get(tmp17, _, &f);

        if (string_starts_with(f.name, tos3("main__test_"))) {

          if (v->pref->is_stats) {

            compiler__CGen_genln(
                cgen,
                _STR("BenchedTests_testing_step_start(&bt, tos3(\"%.*s\"));",
                     f.name.len, f.name.str));
          };

          compiler__CGen_genln(cgen, _STR("%.*s();", f.name.len, f.name.str));

          if (v->pref->is_stats) {

            compiler__CGen_genln(cgen,
                                 tos3("BenchedTests_testing_step_end(&bt);"));
          };
        };
      };

      if (v->pref->is_stats) {

        compiler__CGen_genln(cgen, tos3("BenchedTests_end_testing(&bt);"));
      };

      compiler__V_gen_main_end(v, tos3("return g_test_fails > 0"));

    } else if (compiler__Table_main_exists(&/* ? */ *v->table)) {

      compiler__V_gen_main_start(v, 1);

      compiler__CGen_genln(cgen, tos3("  main__main();"));

      compiler__V_gen_main_end(v, tos3("return 0"));
    };
  };
}
void compiler__V_gen_main_start(compiler__V *v, bool add_os_args) {

  compiler__CGen_genln(v->cgen, tos3("int main(int argc, char** argv) { "));

  compiler__CGen_genln(v->cgen, tos3("  init();"));

  if (add_os_args && (_IN(string, (tos3("os")), v->table->imports))) {

    compiler__CGen_genln(
        v->cgen, tos3("  os__args = os__init_os_args(argc, (byteptr*)argv);"));
  };

  compiler__V_generate_hotcode_reloading_main_caller(&/* ? */ *v);

  compiler__CGen_genln(v->cgen, tos3(""));
}
void compiler__V_gen_main_end(compiler__V *v, string return_statement) {

  compiler__CGen_genln(v->cgen, tos3(""));

  compiler__CGen_genln(
      v->cgen, _STR("  %.*s;", return_statement.len, return_statement.str));

  compiler__CGen_genln(v->cgen, tos3("}"));
}
string compiler__final_target_out_name(string out_name) {

#ifdef _WIN32

  return string_add(string_replace(out_name, tos3("/"), tos3("\\")),
                    tos3(".exe"));

#endif
  ;

  return (string_starts_with(out_name, tos3("/")))
             ? (out_name)
             : (string_add(tos3("./"), out_name));
}
void compiler__V_run_compiled_executable_and_exit(compiler__V v) {

  array_string args = compiler__env_vflags_and_os_args();

  if (v.pref->is_verbose) {

    printf("============ running %.*s ============\n", v.out_name.len,
           v.out_name.str);
  };

  string cmd = string_add(
      string_add(tos3("\""),
                 string_replace(compiler__final_target_out_name(v.out_name),
                                tos3(".exe"), tos3(""))),
      tos3("\""));

  string args_after = tos3(" ");

  array_string tmp18 = args;
  for (int i = 0; i < tmp18.len; i++) {
    string a = ((string *)tmp18.data)[i];

    if (i == 0) {

      continue;
    };

    if (string_starts_with(a, tos3("-"))) {

      continue;
    };

    if (string_eq(a, tos3("run")) || string_eq(a, tos3("test"))) {

      args_after = string_add(
          args_after,
          array_string_join(array_slice2(args, i + 2, -1, true), tos3(" ")));

      break;
    };
  };

  cmd = string_add(cmd, args_after);

  if (v.pref->is_test) {

    int ret = os__system(cmd);

    if (ret != 0) {

      v_exit(1);
    };
  };

  if (v.pref->is_run) {

    int ret = os__system(cmd);

    v_exit(ret);
  };

  v_exit(0);
}
array_string compiler__V_v_files_from_dir(compiler__V *v, string dir) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (!os__file_exists(dir)) {

    if (string_eq(dir, tos3("compiler")) && os__dir_exists(tos3("vlib"))) {

      println(tos3("looks like you are trying to build V with an old command"));

      println(tos3("use `v -o v v.v` instead of `v -o v compiler`"));
    };

    compiler__verror(_STR("%.*s doesn't exist", dir.len, dir.str));

  } else if (!os__dir_exists(dir)) {

    compiler__verror(_STR("%.*s isn't a directory", dir.len, dir.str));
  };

  Option_array_string tmp21 = os__ls(dir);
  array_string files;
  if (!tmp21.ok) {
    string err = tmp21.error;
    int errcode = tmp21.ecode;

    v_panic(err);
  }
  files = *(array_string *)tmp21.data;
  ;

  if (v->pref->is_verbose) {

    printf("v_files_from_dir (\"%.*s\")\n", dir.len, dir.str);
  };

  array_string_sort(&/* ? */ files);

  array_string tmp22 = files;
  for (int tmp23 = 0; tmp23 < tmp22.len; tmp23++) {
    string file = ((string *)tmp22.data)[tmp23];

    if (!string_ends_with(file, tos3(".v")) &&
        !string_ends_with(file, tos3(".vh"))) {

      continue;
    };

    if (string_ends_with(file, tos3("_test.v"))) {

      continue;
    };

    if ((string_ends_with(file, tos3("_win.v")) ||
         string_ends_with(file, tos3("_windows.v"))) &&
        v->os != compiler__compiler__OS_windows) {

      continue;
    };

    if ((string_ends_with(file, tos3("_lin.v")) ||
         string_ends_with(file, tos3("_linux.v"))) &&
        v->os != compiler__compiler__OS_linux) {

      continue;
    };

    if ((string_ends_with(file, tos3("_mac.v")) ||
         string_ends_with(file, tos3("_darwin.v"))) &&
        v->os != compiler__compiler__OS_mac) {

      continue;
    };

    if (string_ends_with(file, tos3("_nix.v")) &&
        v->os == compiler__compiler__OS_windows) {

      continue;
    };

    if (string_ends_with(file, tos3("_js.v")) &&
        v->os != compiler__compiler__OS_js) {

      continue;
    };

    if (string_ends_with(file, tos3("_c.v")) &&
        v->os == compiler__compiler__OS_js) {

      continue;
    };

    _PUSH(&res,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "%.*s%.*s%.*s", dir.len, dir.str, os__path_separator.len,
              os__path_separator.str, file.len, file.str)),
          tmp24, string);
  };

  return res;
}
void compiler__V_add_v_files_to_compile(compiler__V *v) {

  array_string builtin_files = compiler__V_get_builtin_files(&/* ? */ *v);

  string builtin_vh = _STR(
      "%.*s%.*svlib%.*sbuiltin.vh", compiler__v_modules_path.len,
      compiler__v_modules_path.str, os__path_separator.len,
      os__path_separator.str, os__path_separator.len, os__path_separator.str);

  if (v->pref->is_cache && os__file_exists(builtin_vh)) {

    _PUSH(&v->cached_mods,
          (/*typ = array_string   tmp_typ=string*/ tos3("builtin")), tmp25,
          string);

    builtin_files = new_array_from_c_array(
        1, 1, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 1){builtin_vh});
  };

  array_string tmp26 = builtin_files;
  for (int tmp27 = 0; tmp27 < tmp26.len; tmp27++) {
    string file = ((string *)tmp26.data)[tmp27];

    _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ file), tmp28,
          string);

    compiler__Parser p = compiler__V_new_parser_from_file(v, file);

    compiler__Parser_parse(&/* ? */ p, compiler__compiler__Pass_imports);

    compiler__V_add_parser(v, p);
  };

  array_string tmp29 = compiler__V_get_user_files(&/* ? */ *v);
  for (int tmp30 = 0; tmp30 < tmp29.len; tmp30++) {
    string file = ((string *)tmp29.data)[tmp30];

    compiler__Parser p = compiler__V_new_parser_from_file(v, file);

    compiler__Parser_parse(&/* ? */ p, compiler__compiler__Pass_imports);

    if (p.v_script) {

      compiler__V_log(&/* ? */ *v, tos3("imports0:"));

      println(array_string_str(v->table->imports));

      println(array_string_str(v->files));

      compiler__Parser_register_import(&/* ? */ p, tos3("os"), 0);

      _PUSH(&p.table->imports,
            (/*typ = array_string   tmp_typ=string*/ tos3("os")), tmp31,
            string);

      compiler__Table_register_module(p.table, tos3("os"));
    };

    compiler__V_add_parser(v, p);
  };

  compiler__V_parse_lib_imports(v);

  if (v->pref->is_verbose) {

    compiler__V_log(&/* ? */ *v, tos3("imports:"));

    println(array_string_str(v->table->imports));
  };

  array_string imported_mods = compiler__DepGraph_imports(
      &/* ? */ *compiler__V_resolve_deps(&/* ? */ *v));

  array_string tmp32 = imported_mods;
  for (int tmp33 = 0; tmp33 < tmp32.len; tmp33++) {
    string mod = ((string *)tmp32.data)[tmp33];

    if (string_eq(mod, tos3("builtin")) || string_eq(mod, tos3("main"))) {

      continue;
    };

    if (v->pref->build_mode != compiler__compiler__BuildMode_build_module &&
        !string_contains(mod, tos3("vweb"))) {

      string mod_path = string_replace(mod, tos3("."), os__path_separator);

      string vh_path =
          _STR("%.*s%.*svlib%.*s%.*s.vh", compiler__v_modules_path.len,
               compiler__v_modules_path.str, os__path_separator.len,
               os__path_separator.str, os__path_separator.len,
               os__path_separator.str, mod_path.len, mod_path.str);

      if (v->pref->is_cache && os__file_exists(vh_path)) {

        eprintln(_STR("using cached module `%.*s`: %.*s", mod.len, mod.str,
                      vh_path.len, vh_path.str));

        _PUSH(&v->cached_mods, (/*typ = array_string   tmp_typ=string*/ mod),
              tmp34, string);

        _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ vh_path),
              tmp35, string);

        continue;
      };
    };

    array_string vfiles =
        compiler__V_get_imported_module_files(&/* ? */ *v, mod);

    array_string tmp36 = vfiles;
    for (int tmp37 = 0; tmp37 < tmp36.len; tmp37++) {
      string file = ((string *)tmp36.data)[tmp37];

      _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ file), tmp38,
            string);
    };
  };

  array_compiler__Parser tmp39 = v->parsers;
  for (int tmp40 = 0; tmp40 < tmp39.len; tmp40++) {
    compiler__Parser p = ((compiler__Parser *)tmp39.data)[tmp40];

    if (string_ne(p.mod, tos3("main"))) {

      continue;
    };

    _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ p.file_path),
          tmp41, string);
  };
}
array_string compiler__V_get_builtin_files(compiler__V *v) {

#ifdef _VJS

  return compiler__V_v_files_from_dir(
      &/* ? */ *v,
      _STR("%.*s%.*svlib%.*sbuiltin%.*sjs", v->vroot.len, v->vroot.str,
           os__path_separator.len, os__path_separator.str,
           os__path_separator.len, os__path_separator.str,
           os__path_separator.len, os__path_separator.str));

#endif
  ;

  return compiler__V_v_files_from_dir(
      &/* ? */ *v, _STR("%.*s%.*svlib%.*sbuiltin", v->vroot.len, v->vroot.str,
                        os__path_separator.len, os__path_separator.str,
                        os__path_separator.len, os__path_separator.str));
}
array_string compiler__V_get_user_files(compiler__V *v) {

  string dir = v->dir;

  compiler__V_log(&/* ? */ *v, _STR("get_v_files(%.*s)", dir.len, dir.str));

  array_string user_files = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (v->pref->is_test) {

    _PUSH(&user_files,
          (/*typ = array_string   tmp_typ=string*/ filepath__join(
              v->vroot, &(varg_string){.len = 4,
                                       .args = {tos3("vlib"), tos3("compiler"),
                                                tos3("preludes"),
                                                tos3("tests_assertions.v")}})),
          tmp42, string);
  };

  if (v->pref->is_test && v->pref->is_stats) {

    _PUSH(&user_files,
          (/*typ = array_string   tmp_typ=string*/ filepath__join(
              v->vroot, &(varg_string){.len = 4,
                                       .args = {tos3("vlib"), tos3("compiler"),
                                                tos3("preludes"),
                                                tos3("tests_with_stats.v")}})),
          tmp43, string);
  };

  bool is_test_with_imports =
      string_ends_with(dir, tos3("_test.v")) &&
      (string_contains(dir, _STR("%.*svolt", os__path_separator.len,
                                 os__path_separator.str)) ||
       string_contains(dir, _STR("%.*sc2volt", os__path_separator.len,
                                 os__path_separator.str)));

  if (is_test_with_imports) {

    _PUSH(&user_files, (/*typ = array_string   tmp_typ=string*/ dir), tmp44,
          string);

    int pos = string_last_index(dir, os__path_separator);

    dir = string_add(string_substr2(dir, 0, pos, false), os__path_separator);
  };

  if (string_ends_with(dir, tos3(".v")) ||
      string_ends_with(dir, tos3(".vsh"))) {

    _PUSH(&user_files, (/*typ = array_string   tmp_typ=string*/ dir), tmp47,
          string);

    dir = string_all_before(dir, os__path_separator);

  } else {

    array_string files = compiler__V_v_files_from_dir(&/* ? */ *v, dir);

    array_string tmp48 = files;
    for (int tmp49 = 0; tmp49 < tmp48.len; tmp49++) {
      string file = ((string *)tmp48.data)[tmp49];

      _PUSH(&user_files, (/*typ = array_string   tmp_typ=string*/ file), tmp50,
            string);
    };
  };

  if (user_files.len == 0) {

    println(tos3("No input .v files"));

    v_exit(1);
  };

  if (v->pref->is_verbose) {

    compiler__V_log(&/* ? */ *v, tos3("user_files:"));

    println(array_string_str(user_files));
  };

  return user_files;
}
array_string compiler__V_get_imported_module_files(compiler__V *v, string mod) {

  array_string files = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__Parser tmp51 = v->parsers;
  for (int tmp52 = 0; tmp52 < tmp51.len; tmp52++) {
    compiler__Parser p = ((compiler__Parser *)tmp51.data)[tmp52];

    if (string_eq(p.mod, mod)) {

      _PUSH(&files, (/*typ = array_string   tmp_typ=string*/ p.file_path),
            tmp53, string);
    };
  };

  return files;
}
void compiler__V_parse_lib_imports(compiler__V *v) {

  array_string done_imports = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  int tmp54 = 0;
  ;
  for (int tmp55 = tmp54; tmp55 < v->parsers.len; tmp55++) {
    int i = tmp55;

    map_string tmp56 =
        (*(compiler__Parser *)array_get(v->parsers, i)).import_table.imports;
    array_string keys_tmp56 = map_keys(&tmp56);
    for (int l = 0; l < keys_tmp56.len; l++) {
      string _ = ((string *)keys_tmp56.data)[l];
      string mod = tos3("");
      map_get(tmp56, _, &mod);

      if ((_IN(string, (mod), done_imports))) {

        continue;
      };

      Option_string tmp59 = compiler__V_find_module_path(&/* ? */ *v, mod);
      string import_path;
      if (!tmp59.ok) {
        string err = tmp59.error;
        int errcode = tmp59.ecode;

        compiler__Parser_error_with_token_index(
            &/* ? */ (*(compiler__Parser *)array_get(v->parsers, i)),
            _STR("cannot import module \"%.*s\" (not found)", mod.len, mod.str),
            compiler__ImportTable_get_import_tok_idx(
                &/* ? */ (*(compiler__Parser *)array_get(v->parsers, i))
                     .import_table,
                mod));

        break;
      }
      import_path = *(string *)tmp59.data;
      ;

      array_string vfiles =
          compiler__V_v_files_from_dir(&/* ? */ *v, import_path);

      if (vfiles.len == 0) {

        compiler__Parser_error_with_token_index(
            &/* ? */ (*(compiler__Parser *)array_get(v->parsers, i)),
            _STR("cannot import module \"%.*s\" (no .v files in \"%.*s\")",
                 mod.len, mod.str, import_path.len, import_path.str),
            compiler__ImportTable_get_import_tok_idx(
                &/* ? */ (*(compiler__Parser *)array_get(v->parsers, i))
                     .import_table,
                mod));
      };

      array_string tmp68 = vfiles;
      for (int tmp69 = 0; tmp69 < tmp68.len; tmp69++) {
        string file = ((string *)tmp68.data)[tmp69];

        int pidx = compiler__V_parse(v, file, compiler__compiler__Pass_imports);

        string p_mod = (*(compiler__Parser *)array_get(v->parsers, pidx)).mod;

        if (string_ne(p_mod, mod)) {

          compiler__Parser_error_with_token_index(
              &/* ? */ (*(compiler__Parser *)array_get(v->parsers, pidx)),
              _STR("bad module definition: %.*s imports module \"%.*s\" but "
                   "%.*s is defined as module `%.*s`",
                   (*(compiler__Parser *)array_get(v->parsers, pidx))
                       .file_path.len,
                   (*(compiler__Parser *)array_get(v->parsers, pidx))
                       .file_path.str,
                   mod.len, mod.str, file.len, file.str, p_mod.len, p_mod.str),
              1);
        };
      };

      _PUSH(&done_imports, (/*typ = array_string   tmp_typ=string*/ mod), tmp76,
            string);
    };
  };
}
string compiler__get_arg(string joined_args, string arg, string def) {

  return compiler__get_param_after(joined_args, _STR("-%.*s", arg.len, arg.str),
                                   def);
}
string compiler__get_param_after(string joined_args, string arg, string def) {

  string key = _STR("%.*s ", arg.len, arg.str);

  int pos = string_index(joined_args, key);

  if (pos == -1) {

    return def;
  };

  pos += key.len;

  int space = string_index_after(joined_args, tos3(" "), pos);

  if (space == -1) {

    space = joined_args.len;
  };

  string res = string_substr2(joined_args, pos, space, false);

  return res;
}
void compiler__V_log(compiler__V *v, string s) {

  if (!v->pref->is_verbose) {

    return;
  };

  println(s);
}
compiler__V *compiler__new_v(array_string args) {

  if (!os__dir_exists(compiler__v_modules_path)) {

    os__mkdir(compiler__v_modules_path);

    os__mkdir(_STR("%.*s%.*scache", compiler__v_modules_path.len,
                   compiler__v_modules_path.str, os__path_separator.len,
                   os__path_separator.str));
  };

  string vroot = os__dir(compiler__vexe_path());

  strings__Builder vgen_buf = strings__new_builder(1000);

  strings__Builder_writeln(&/* ? */ vgen_buf,
                           tos3("module vgen\nimport strings"));

  string joined_args = array_string_join(args, tos3(" "));

  string target_os = compiler__get_arg(joined_args, tos3("os"), tos3(""));

  string comptime_define = compiler__get_arg(joined_args, tos3("d"), tos3(""));

  string out_name = compiler__get_arg(joined_args, tos3("o"), tos3("a.out"));

  string dir = *(string *)array_last(args);

  if ((_IN(string, (tos3("run")), args))) {

    dir = compiler__get_param_after(joined_args, tos3("run"), tos3(""));
  };

  if (string_ends_with(dir, os__path_separator)) {

    dir = string_all_before_last(dir, os__path_separator);
  };

  if (string_starts_with(
          dir, _STR(".%.*s", os__path_separator.len, os__path_separator.str))) {

    dir = string_substr2(dir, 2, -1, true);
  };

  if (args.len < 2) {

    dir = tos3("");
  };

  compiler__BuildMode build_mode = compiler__compiler__BuildMode_default_mode;

  string mod = tos3("");

  if (string_contains(joined_args, tos3("build module "))) {

    build_mode = compiler__compiler__BuildMode_build_module;

    os__chdir(vroot);

    string mod_path =
        (string_contains(dir, tos3("vlib")))
            ? (string_all_after(dir,
                                string_add(tos3("vlib"), os__path_separator)))
            : ((string_starts_with(dir, tos3(".\\")) ||
                string_starts_with(dir, tos3("./")))
                   ? (string_substr2(dir, 2, -1, true))
                   : ((string_starts_with(dir, os__path_separator))
                          ? (string_all_after(dir, os__path_separator))
                          : (dir)));

    mod = string_replace(mod_path, os__path_separator, tos3("."));

    printf("Building module \"%.*s\" (dir=\"%.*s\")...\n", mod.len, mod.str,
           dir.len, dir.str);

    out_name = mod;
  };

  bool is_test = string_ends_with(dir, tos3("_test.v"));

  bool is_script =
      string_ends_with(dir, tos3(".v")) || string_ends_with(dir, tos3(".vsh"));

  if (is_script && !os__file_exists(dir)) {

    printf("`%.*s` does not exist\n", dir.len, dir.str);

    v_exit(1);
  };

  if (string_eq(out_name, tos3("a.out")) && string_ends_with(dir, tos3(".v")) &&
      string_ne(dir, tos3(".v"))) {

    out_name = string_substr2(dir, 0, dir.len - 2, false);

    if (string_eq(out_name, tos3("v")) &&
        os__dir_exists(tos3("vlib/compiler"))) {

      println(tos3("Saving the resulting V executable in `./v2`"));

      println(
          string_add(tos3("Use `v -o v v.v` if you want to replace current "),
                     tos3("V executable.")));

      out_name = tos3("v2");
    };
  };

  if (string_eq(dir, tos3(".")) && string_eq(out_name, tos3("a.out"))) {

    string base = string_all_after(os__getwd(), os__path_separator);

    out_name = string_trim_space(base);
  };

  if (string_contains(out_name, os__path_separator)) {

    string d = string_all_before_last(out_name, os__path_separator);

    if (!os__dir_exists(d)) {

      printf("creating a new directory \"%.*s\"\n", d.len, d.str);

      os__mkdir(d);
    };
  };

  compiler__OS _os = compiler__compiler__OS_mac;

  if (string_eq(target_os, tos3(""))) {

#ifdef __linux__

    _os = compiler__compiler__OS_linux;

#endif
    ;

#ifdef __APPLE__

    _os = compiler__compiler__OS_mac;

#endif
    ;

#ifdef _WIN32

    _os = compiler__compiler__OS_windows;

#endif
    ;

#ifdef __FreeBSD__

    _os = compiler__compiler__OS_freebsd;

#endif
    ;

#ifdef __OpenBSD__

    _os = compiler__compiler__OS_openbsd;

#endif
    ;

#ifdef __NetBSD__

    _os = compiler__compiler__OS_netbsd;

#endif
    ;

#ifdef __DragonFly__

    _os = compiler__compiler__OS_dragonfly;

#endif
    ;

#ifdef __sun

    _os = compiler__compiler__OS_solaris;

#endif
    ;

  } else {

    _os = compiler__os_from_string(target_os);
  };

  if (!os__dir_exists(vroot) ||
      !os__dir_exists(string_add(vroot, tos3("/vlib/builtin")))) {

    println(tos3("vlib not found, downloading it..."));

    println(tos3("vlib not found. It should be next to the V executable. "));

    println(tos3("Go to https://vlang.io to install V."));

    v_exit(1);
  };

  string out_name_c =
      os__realpath(_STR("%.*s.tmp.c", out_name.len, out_name.str));

  string cflags = compiler__get_cmdline_cflags(args);

  string rdir = os__realpath(dir);

  string rdir_name = os__filename(rdir);

  bool obfuscate = (_IN(string, (tos3("-obf")), args));

  bool is_repl = (_IN(string, (tos3("-repl")), args));

  compiler__Preferences *pref = (compiler__Preferences *)memdup(
      &(compiler__Preferences){
          .is_test = is_test,
          .is_script = is_script,
          .is_so = (_IN(string, (tos3("-shared")), args)),
          .is_prod = (_IN(string, (tos3("-prod")), args)),
          .is_verbose = (_IN(string, (tos3("-verbose")), args)) ||
                        (_IN(string, (tos3("--verbose")), args)),
          .is_debug = (_IN(string, (tos3("-g")), args)) ||
                      (_IN(string, (tos3("-cg")), args)),
          .is_vlines = (_IN(string, (tos3("-g")), args)) &&
                       !((_IN(string, (tos3("-cg")), args))),
          .is_keep_c = (_IN(string, (tos3("-keep_c")), args)),
          .is_cache = (_IN(string, (tos3("-cache")), args)),
          .is_stats = (_IN(string, (tos3("-stats")), args)),
          .obfuscate = obfuscate,
          .is_prof = (_IN(string, (tos3("-prof")), args)),
          .is_live = (_IN(string, (tos3("-live")), args)),
          .sanitize = (_IN(string, (tos3("-sanitize")), args)),
          .nofmt = (_IN(string, (tos3("-nofmt")), args)),
          .show_c_cmd = (_IN(string, (tos3("-show_c_cmd")), args)),
          .translated = (_IN(string, (tos3("translated")), args)),
          .is_run = (_IN(string, (tos3("run")), args)),
          .autofree = (_IN(string, (tos3("-autofree")), args)),
          .compress = (_IN(string, (tos3("-compress")), args)),
          .enable_globals = (_IN(string, (tos3("--enable-globals")), args)),
          .fast = (_IN(string, (tos3("-fast")), args)),
          .is_repl = is_repl,
          .build_mode = build_mode,
          .cflags = cflags,
          .ccompiler = compiler__find_c_compiler(),
          .building_v = !is_repl && (string_eq(rdir_name, tos3("compiler")) ||
                                     string_eq(rdir_name, tos3("v.v")) ||
                                     string_contains(dir, tos3("vlib"))),
          .comptime_define = comptime_define,
          .no_auto_free = 0,
      },
      sizeof(compiler__Preferences));

  if (pref->is_verbose || pref->is_debug) {

    printf("C compiler=%.*s\n", pref->ccompiler.len, pref->ccompiler.str);
  };

  if (pref->is_so) {

    out_name_c = string_add(string_all_after(out_name, os__path_separator),
                            tos3("_shared_lib.c"));
  };

  return (compiler__V *)memdup(
      &(compiler__V){.os = _os,
                     .out_name = out_name,
                     .dir = dir,
                     .lang_dir = vroot,
                     .table = compiler__new_table(obfuscate),
                     .out_name_c = out_name_c,
                     .cgen = compiler__new_cgen(out_name_c),
                     .vroot = vroot,
                     .pref = pref,
                     .mod = mod,
                     .vgen_buf = vgen_buf,
                     .files = new_array(0, 1, sizeof(string)),
                     .parsers = new_array(0, 1, sizeof(compiler__Parser)),
                     .file_parser_idx = new_map(1, sizeof(int)),
                     .cached_mods = new_array(0, 1, sizeof(string))},
      sizeof(compiler__V));
}
array_string compiler__env_vflags_and_os_args() {

  string vosargs = os__getenv(tos3("VOSARGS"));

  if (string_ne(tos3(""), vosargs)) {

    return string_split(vosargs, tos3(" "));
  };

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  string vflags = os__getenv(tos3("VFLAGS"));

  if (string_ne(tos3(""), vflags)) {

    _PUSH(&args,
          (/*typ = array_string   tmp_typ=string*/ (
              *(string *)array_get(os__args, 0))),
          tmp85, string);

    _PUSH_MANY(&args,
               (/*typ = array_string   tmp_typ=string*/ string_split(
                   vflags, tos3(" "))),
               tmp88, array_string);

    if (os__args.len > 1) {

      _PUSH_MANY(&args,
                 (/*typ = array_string   tmp_typ=string*/ array_slice2(
                     os__args, 1, -1, true)),
                 tmp89, array_string);
    };

  } else {

    _PUSH_MANY(&args, (/*typ = array_string   tmp_typ=string*/ os__args), tmp92,
               array_string);
  };

  return args;
}
void compiler__vfmt(array_string args) {

  string file = *(string *)array_last(args);

  if (!os__file_exists(file)) {

    printf("\"%.*s\" does not exist\n", file.len, file.str);

    v_exit(1);
  };

  if (!string_ends_with(file, tos3(".v"))) {

    println(tos3("v fmt can only be used on .v files"));

    v_exit(1);
  };

  println(tos3("vfmt is temporarily disabled"));
}
void compiler__create_symlink() {

  string vexe = compiler__vexe_path();

  string link_path = tos3("/usr/local/bin/v");

  int ret = os__system(_STR("ln -sf %.*s %.*s", vexe.len, vexe.str,
                            link_path.len, link_path.str));

  if (ret == 0) {

    printf("symlink \"%.*s\" has been created\n", link_path.len, link_path.str);

  } else {

    println(string_add(_STR("failed to create symlink \"%.*s\", ",
                            link_path.len, link_path.str),
                       tos3("make sure you run with sudo")));
  };
}
string compiler__vexe_path() {

  string vexe = os__getenv(tos3("VEXE"));

  if (string_ne(tos3(""), vexe)) {

    return vexe;
  };

  return os__executable();
}
void compiler__verror(string s) {

  printf("V error: %.*s\n", s.len, s.str);

  os__flush_stdout();

  v_exit(1);
}
string compiler__vhash() {

  byte buf[50] = {0};

  buf[0] /*rbyte 1*/ = 0;

  snprintf(((char *)(buf)), 50, "%s", V_COMMIT_HASH);

  return tos_clone(buf);
}
string compiler__cescaped_path(string s) {

  return string_replace(s, tos3("\\"), tos3("\\\\"));
}
compiler__OS compiler__os_from_string(string os) {

  string tmp93 = os;

  if (string_eq(tmp93, tos3("linux"))) {

    return compiler__compiler__OS_linux;

  } else if (string_eq(tmp93, tos3("windows"))) {

    return compiler__compiler__OS_windows;

  } else if (string_eq(tmp93, tos3("mac"))) {

    return compiler__compiler__OS_mac;

  } else if (string_eq(tmp93, tos3("freebsd"))) {

    return compiler__compiler__OS_freebsd;

  } else if (string_eq(tmp93, tos3("openbsd"))) {

    return compiler__compiler__OS_openbsd;

  } else if (string_eq(tmp93, tos3("netbsd"))) {

    return compiler__compiler__OS_netbsd;

  } else if (string_eq(tmp93, tos3("dragonfly"))) {

    return compiler__compiler__OS_dragonfly;

  } else if (string_eq(tmp93, tos3("js"))) {

    return compiler__compiler__OS_js;

  } else if (string_eq(tmp93, tos3("solaris"))) {

    return compiler__compiler__OS_solaris;

  } else if (string_eq(tmp93, tos3("android"))) {

    return compiler__compiler__OS_android;

  } else if (string_eq(tmp93, tos3("msvc"))) {

    compiler__verror(tos3("use the flag `-cc msvc` to build using msvc"));
  };

  printf("bad os %.*s\n", os.len, os.str);

  return compiler__compiler__OS_linux;
}
void compiler__set_vroot_folder(string vroot_path) {

  string vname = (string_eq(os__user_os(), tos3("windows"))) ? (tos3("v.exe"))
                                                             : (tos3("v"));

  os__setenv(tos3("VEXE"),
             os__realpath(array_string_join(
                 new_array_from_c_array(
                     2, 2, sizeof(string),
                     EMPTY_ARRAY_OF_ELEMS(string, 2){vroot_path, vname}),
                 os__path_separator)),
             1);
}
compiler__V *compiler__new_v_compiler_with_args(array_string args) {

  string vexe = compiler__vexe_path();

  array_string allargs = new_array_from_c_array(
      1, 1, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 1){vexe});

  _PUSH_MANY(&allargs, (/*typ = array_string   tmp_typ=string*/ args), tmp94,
             array_string);

  os__setenv(tos3("VOSARGS"), array_string_join(allargs, tos3(" ")), 1);

  return compiler__new_v(allargs);
}
string compiler__Parser_match_statement(compiler__Parser *p, bool is_expr) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_match);

  compiler__CGen_start_tmp(p->cgen);

  string typ = compiler__Parser_bool_expression(p);

  if (string_starts_with(typ, tos3("array_"))) {

    compiler__Parser_error(p, tos3("arrays cannot be compared"));
  };

  string expr = compiler__CGen_end_tmp(p->cgen);

  string tmp_var = compiler__Parser_get_tmp(p);

  compiler__CGen_insert_before(p->cgen, _STR("%.*s %.*s = %.*s;", typ.len,
                                             typ.str, tmp_var.len, tmp_var.str,
                                             expr.len, expr.str));

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  int i = 0;

  bool all_cases_return = 1;

  string res_typ = tos3("");

  while (p->tok != compiler__compiler__TokenKind_rcbr) {

    if (p->tok == compiler__compiler__TokenKind_key_else) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_key_else);

      if (p->tok == compiler__compiler__TokenKind_arrow) {

        compiler__Parser_warn(p, compiler__warn_match_arrow);

        compiler__Parser_check(p, compiler__compiler__TokenKind_arrow);
      };

      if (i == 0) {

        if (is_expr) {

          bool got_brace = p->tok == compiler__compiler__TokenKind_lcbr;

          if (got_brace) {

            compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);
          };

          compiler__Parser_gen(p, tos3("( "));

          res_typ = compiler__Parser_bool_expression(p);

          compiler__Parser_gen(p, tos3(" )"));

          if (got_brace) {

            compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);
          };

          string tmp1 = res_typ;
          { compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr); }
          return tmp1;
          ;

        } else {

          p->returns = 0;

          compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

          compiler__Parser_genln(p, tos3("{ "));

          compiler__Parser_statements(p);

          p->returns = all_cases_return && p->returns;

          string tmp2 = tos3("");
          { compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr); }
          return tmp2;
          ;
        };
      };

      if (is_expr) {

        compiler__Parser_gen(p, tos3(":("));

        bool got_brace = p->tok == compiler__compiler__TokenKind_lcbr;

        if (got_brace) {

          compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);
        };

        compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                     res_typ);

        if (got_brace) {

          compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);
        };

        compiler__Parser_gen(p, strings__repeat(')', i + 1));

        string tmp3 = res_typ;
        { compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr); }
        return tmp3;
        ;

      } else {

        p->returns = 0;

        compiler__Parser_genln(p, tos3("else // default:"));

        compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

        compiler__Parser_genln(p, tos3("{ "));

        compiler__Parser_statements(p);

        p->returns = all_cases_return && p->returns;

        string tmp4 = tos3("");
        { compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr); }
        return tmp4;
        ;
      };
    };

    if (i > 0) {

      if (is_expr) {

        compiler__Parser_gen(p, tos3(": ("));

      } else {

        compiler__Parser_gen(p, tos3("else "));
      };

    } else if (is_expr) {

      compiler__Parser_gen(p, tos3("("));
    };

    if (is_expr) {

      compiler__Parser_gen(p, tos3("("));

    } else {

      compiler__Parser_gen(p, tos3("if ("));
    };

    int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

    bool got_comma = 0;

    while (1) {

      if (got_comma) {

        compiler__Parser_gen(p, tos3(") || ("));
      };

      bool got_string = 0;

      if (string_eq(typ, tos3("string"))) {

        got_string = 1;

        compiler__Parser_gen(
            p, _STR("string_eq(%.*s, ", tmp_var.len, tmp_var.str));

      } else {

        compiler__Parser_gen(p, _STR("%.*s == ", tmp_var.len, tmp_var.str));
      };

      p->expected_type = typ;

      compiler__Parser_check_types(p, compiler__Parser_bool_expression(p), typ);

      p->expected_type = tos3("");

      if (got_string) {

        compiler__Parser_gen(p, tos3(")"));
      };

      if (p->tok != compiler__compiler__TokenKind_comma) {

        if (got_comma) {

          compiler__Parser_gen(p, tos3(") "));

          compiler__CGen_set_placeholder(p->cgen, ph, tos3("("));
        };

        break;
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

      got_comma = 1;
    };

    compiler__Parser_gen(p, tos3(")"));

    if (p->tok == compiler__compiler__TokenKind_arrow) {

      compiler__Parser_warn(p, compiler__warn_match_arrow);

      compiler__Parser_check(p, compiler__compiler__TokenKind_arrow);
    };

    if (is_expr) {

      compiler__Parser_gen(p, tos3("? ("));

      compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

      if (i == 0) {

        res_typ = compiler__Parser_bool_expression(p);

      } else {

        compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                     res_typ);
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

      compiler__Parser_gen(p, tos3(")"));

    } else {

      p->returns = 0;

      compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

      compiler__Parser_genln(p, tos3("{ "));

      compiler__Parser_statements(p);

      all_cases_return = all_cases_return && p->returns;
    };

    i++;
  };

  if (is_expr) {

    compiler__Parser_error(p, tos3("Match expression requires \"else\""));
  };

  p->returns = 0;

  string tmp5 = tos3("");
  { compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr); }
  return tmp5;
  ;

  { compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr); }
}
void compiler__Parser_switch_statement(compiler__Parser *p) {

  compiler__Parser_error(
      p,
      string_add(
          tos3("`switch` statement has been removed, use `match` instead:\n"),
          tos3("https://vlang.io/docs#match")));
}
void compiler__generate_vh(string mod) {

  printf("\n\n\n\n1Generating a V header file for module `%.*s`\n", mod.len,
         mod.str);

  string vexe = os__executable();

  string full_mod_path = string_add(string_add(os__dir(vexe), tos3("/")), mod);

  string mod_path = string_replace(mod, tos3("."), os__path_separator);

  string dir = (string_starts_with(mod, tos3("vlib")))
                   ? (_STR("%.*s%.*s%.*s", compiler__v_modules_path.len,
                           compiler__v_modules_path.str, os__path_separator.len,
                           os__path_separator.str, mod.len, mod.str))
                   : (_STR("%.*s%.*s%.*s", compiler__v_modules_path.len,
                           compiler__v_modules_path.str, os__path_separator.len,
                           os__path_separator.str, mod.len, mod.str));

  string path = string_add(dir, tos3(".vh"));

  string pdir = string_all_before_last(dir, os__path_separator);

  if (!os__dir_exists(pdir)) {

    os__mkdir_all(pdir);
  };

  Option_os__File tmp1 = os__create(path);
  os__File out;
  if (!tmp1.ok) {
    string err = tmp1.error;
    int errcode = tmp1.ecode;

    v_panic(err);
  }
  out = *(os__File *)tmp1.data;
  ;

  string mod_def = (string_contains(mod, tos3("/")))
                       ? (string_all_after(mod, tos3("/")))
                       : (mod);

  os__File_writeln(out, _STR("// %.*s module header \n", mod.len, mod.str));

  os__File_writeln(out, _STR("module %.*s\n", mod_def.len, mod_def.str));

  println(full_mod_path);

  array_string vfiles = os__walk_ext(full_mod_path, tos3(".v"));

  array_string tmp2 = new_array(0, vfiles.len, sizeof(string));
  for (int i = 0; i < vfiles.len; i++) {
    string it = ((string *)vfiles.data)[i];
    if (string_ends_with(it, tos3(".v")) &&
        !string_ends_with(it, tos3("test.v")) &&
        !string_ends_with(it, tos3("_windows.v")) &&
        !string_ends_with(it, tos3("_win.v")) &&
        !string_ends_with(it, tos3("_lin.v")) &&
        !string_contains(it, tos3("/examples")) &&
        !string_contains(it, tos3("_js.v")) &&
        !string_contains(it, tos3("/js")))
      array_push(&tmp2, &it);
  }
  array_string filtered = tmp2;

  println(tos3("f:"));

  println(array_string_str(filtered));

  compiler__V *v = compiler__new_v(new_array_from_c_array(
      1, 1, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 1){tos3("foo.v")}));

  compiler__VhGen g =
      (compiler__VhGen){.consts = strings__new_builder(1000),
                        .fns = strings__new_builder(1000),
                        .types = strings__new_builder(1000),
                        .i = 0,
                        .tokens = new_array(0, 1, sizeof(compiler__Token))};

  array_string tmp3 = filtered;
  for (int tmp4 = 0; tmp4 < tmp3.len; tmp4++) {
    string file = ((string *)tmp3.data)[tmp4];

    compiler__Parser p = compiler__V_new_parser_from_file(v, file);

    p.scanner->is_vh = 1;

    compiler__Parser_parse(&/* ? */ p, compiler__compiler__Pass_decl);

    g.tokens = p.tokens;

    g.i = 0;

    for (; g.i < p.tokens.len; g.i++) {

      if (!compiler__TokenKind_is_decl(
              (*(compiler__Token *)array_get(p.tokens, g.i)).tok)) {

        continue;
      };

      compiler__TokenKind tmp9 =
          (*(compiler__Token *)array_get(g.tokens, g.i)).tok;

      if (tmp9 == compiler__compiler__TokenKind_key_fn) {

        compiler__VhGen_generate_fn(&/* ? */ g);

      } else if (tmp9 == compiler__compiler__TokenKind_key_const) {

        compiler__VhGen_generate_const(&/* ? */ g);

      } else if (tmp9 == compiler__compiler__TokenKind_key_struct) {

        compiler__VhGen_generate_type(&/* ? */ g);

      } else if (tmp9 == compiler__compiler__TokenKind_key_type) {

        compiler__VhGen_generate_alias(&/* ? */ g);
      };
    };
  };

  string result = string_add(
      string_add(strings__Builder_str(g.types), strings__Builder_str(g.consts)),
      string_replace(string_replace(strings__Builder_str(g.fns), tos3("\n\n\n"),
                                    tos3("\n")),
                     tos3("\n\n"), tos3("\n")));

  os__File_writeln(
      out, string_replace(string_replace(result, tos3("[ ] "), tos3("[]")),
                          tos3("? "), tos3("?")));

  os__File_close(out);
}
void compiler__VhGen_generate_fn(compiler__VhGen *g) {

  if (g->i >= g->tokens.len - 2) {

    return;
  };

  compiler__Token next = (*(compiler__Token *)array_get(g->tokens, g->i + 1));

  if (g->i > 0 && (*(compiler__Token *)array_get(g->tokens, g->i - 1)).tok !=
                      compiler__compiler__TokenKind_key_pub) {
  };

  if (next.tok == compiler__compiler__TokenKind_name &&
      string_eq(next.lit, tos3("C"))) {

    println(tos3("skipping C"));

    return;
  };

  compiler__Token tok = (*(compiler__Token *)array_get(g->tokens, g->i));

  while (g->i < g->tokens.len - 1 &&
         tok.tok != compiler__compiler__TokenKind_lcbr) {

    next = (*(compiler__Token *)array_get(g->tokens, g->i + 1));

    strings__Builder_write(&/* ? */ g->fns, compiler__Token_str(tok));

    if (tok.tok != compiler__compiler__TokenKind_lpar &&
        !(next.tok == compiler__compiler__TokenKind_comma ||
          next.tok == compiler__compiler__TokenKind_rpar)) {

      strings__Builder_write(&/* ? */ g->fns, tos3(" "));
    };

    g->i++;

    tok = (*(compiler__Token *)array_get(g->tokens, g->i));
  };

  strings__Builder_writeln(&/* ? */ g->fns, tos3(""));
}
void compiler__VhGen_generate_alias(compiler__VhGen *g) {

  compiler__Token tok = (*(compiler__Token *)array_get(g->tokens, g->i));

  while (g->i < g->tokens.len - 1) {

    strings__Builder_write(&/* ? */ g->types, compiler__Token_str(tok));

    strings__Builder_write(&/* ? */ g->types, tos3(" "));

    if (tok.line_nr !=
        (*(compiler__Token *)array_get(g->tokens, g->i + 1)).line_nr) {

      break;
    };

    g->i++;

    tok = (*(compiler__Token *)array_get(g->tokens, g->i));
  };

  strings__Builder_writeln(&/* ? */ g->types, tos3("\n"));
}
void compiler__VhGen_generate_const(compiler__VhGen *g) {

  compiler__Token tok = (*(compiler__Token *)array_get(g->tokens, g->i));

  while (g->i < g->tokens.len &&
         tok.tok != compiler__compiler__TokenKind_rpar) {

    strings__Builder_write(&/* ? */ g->consts, compiler__Token_str(tok));

    strings__Builder_write(&/* ? */ g->consts, tos3(" "));

    if ((*(compiler__Token *)array_get(g->tokens, g->i + 2)).tok ==
        compiler__compiler__TokenKind_assign) {

      strings__Builder_write(&/* ? */ g->consts, tos3("\n\t"));
    };

    g->i++;

    tok = (*(compiler__Token *)array_get(g->tokens, g->i));
  };

  strings__Builder_writeln(&/* ? */ g->consts, tos3("\n)"));
}
void compiler__VhGen_generate_type(compiler__VhGen *g) {

  compiler__Token tok = (*(compiler__Token *)array_get(g->tokens, g->i));

  while (g->i < g->tokens.len &&
         tok.tok != compiler__compiler__TokenKind_rcbr) {

    strings__Builder_write(&/* ? */ g->types, compiler__Token_str(tok));

    strings__Builder_write(&/* ? */ g->types, tos3(" "));

    if ((*(compiler__Token *)array_get(g->tokens, g->i + 1)).line_nr !=
        (*(compiler__Token *)array_get(g->tokens, g->i)).line_nr) {

      strings__Builder_write(&/* ? */ g->types, tos3("\n\t"));
    };

    g->i++;

    tok = (*(compiler__Token *)array_get(g->tokens, g->i));
  };

  strings__Builder_writeln(&/* ? */ g->types, tos3("\n}"));
}
string compiler__Table_qualify_module(compiler__Table *table, string mod,
                                      string file_path) {

  array_string tmp1 = table->imports;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    string m = ((string *)tmp1.data)[tmp2];

    if (string_contains(m, tos3(".")) && string_contains(m, mod)) {

      array_string m_parts = string_split(m, tos3("."));

      string m_path = array_string_join(m_parts, os__path_separator);

      if (string_eq(mod, (*(string *)array_get(m_parts, m_parts.len - 1))) &&
          string_contains(file_path, m_path)) {

        return m;
      };
    };
  };

  return mod;
}
compiler__ImportTable compiler__new_import_table() {

  return (compiler__ImportTable){.imports = new_map(1, sizeof(string)),
                                 .used_imports =
                                     new_array(0, 1, sizeof(string)),
                                 .import_tok_idx = new_map(1, sizeof(int))};
}
void compiler__Parser_register_import(compiler__Parser *p, string mod,
                                      int tok_idx) {

  compiler__Parser_register_import_alias(p, mod, mod, tok_idx);
}
void compiler__Parser_register_import_alias(compiler__Parser *p, string alias,
                                            string mod, int tok_idx) {

  string tmp5 = tos3("");
  bool tmp6 = map_get(/*modules.v : 48*/ p->import_table.imports, alias, &tmp5);

  if (!tmp6)
    tmp5 = tos((byte *)"", 0);

  if ((_IN_MAP((alias), p->import_table.imports)) && string_ne(tmp5, mod)) {

    compiler__Parser_error(
        p, _STR("cannot import %.*s as %.*s: import name %.*s already in use\"",
                mod.len, mod.str, alias.len, alias.str, alias.len, alias.str));
  };

  if (string_contains(mod, tos3(".internal."))) {

    array_string mod_parts = string_split(mod, tos3("."));

    array_string internal_mod_parts = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    array_string tmp7 = mod_parts;
    for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
      string part = ((string *)tmp7.data)[tmp8];

      if (string_eq(part, tos3("internal"))) {

        break;
      };

      _PUSH(&internal_mod_parts, (/*typ = array_string   tmp_typ=string*/ part),
            tmp9, string);
    };

    string internal_parent = array_string_join(internal_mod_parts, tos3("."));

    if (!string_starts_with(p->mod, internal_parent)) {

      compiler__Parser_error(
          p, _STR("module %.*s can only be imported internally by libs",
                  mod.len, mod.str));
    };
  };

  map_set(&p->import_table.imports, alias, &(string[]){mod});

  map_set(&p->import_table.import_tok_idx, mod, &(int[]){tok_idx});
}
int compiler__ImportTable_get_import_tok_idx(compiler__ImportTable *it,
                                             string mod) {

  int tmp10 = 0;
  bool tmp11 = map_get(/*modules.v : 69*/ it->import_tok_idx, mod, &tmp10);

  return tmp10;
}
bool compiler__ImportTable_known_import(compiler__ImportTable *it, string mod) {

  return (_IN_MAP((mod), it->imports)) ||
         compiler__ImportTable_is_aliased(&/* ? */ *it, mod);
}
bool compiler__ImportTable_known_alias(compiler__ImportTable *it,
                                       string alias) {

  return (_IN_MAP((alias), it->imports));
}
bool compiler__ImportTable_is_aliased(compiler__ImportTable *it, string mod) {

  map_string tmp12 = it->imports;
  array_string keys_tmp12 = map_keys(&tmp12);
  for (int l = 0; l < keys_tmp12.len; l++) {
    string _ = ((string *)keys_tmp12.data)[l];
    string val = tos3("");
    map_get(tmp12, _, &val);

    if (string_eq(val, mod)) {

      return 1;
    };
  };

  return 0;
}
string compiler__ImportTable_resolve_alias(compiler__ImportTable *it,
                                           string alias) {

  string tmp13 = tos3("");
  bool tmp14 = map_get(/*modules.v : 90*/ it->imports, alias, &tmp13);

  if (!tmp14)
    tmp13 = tos((byte *)"", 0);

  return tmp13;
}
void compiler__ImportTable_register_used_import(compiler__ImportTable *it,
                                                string alias) {

  if (!((_IN(string, (alias), it->used_imports)))) {

    _PUSH(&it->used_imports, (/*typ = array_string   tmp_typ=string*/ alias),
          tmp15, string);
  };
}
bool compiler__ImportTable_is_used_import(compiler__ImportTable *it,
                                          string alias) {

  return (_IN(string, (alias), it->used_imports));
}
bool compiler__Parser_is_mod_in_scope(compiler__Parser *p, string mod) {

  array_string mods_in_scope = new_array_from_c_array(
      4, 4, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 4){tos3(""), tos3("builtin"), tos3("main"),
                                      p->mod});

  map_string tmp16 = p->import_table.imports;
  array_string keys_tmp16 = map_keys(&tmp16);
  for (int l = 0; l < keys_tmp16.len; l++) {
    string _ = ((string *)keys_tmp16.data)[l];
    string m = tos3("");
    map_get(tmp16, _, &m);

    _PUSH(&mods_in_scope, (/*typ = array_string   tmp_typ=string*/ m), tmp17,
          string);
  };

  return (_IN(string, (mod), mods_in_scope));
}
compiler__DepGraph *compiler__V_resolve_deps(compiler__V *v) {

  compiler__DepGraph *graph = compiler__V_import_graph(&/* ? */ *v);

  compiler__DepGraph *deps_resolved =
      compiler__DepGraph_resolve(&/* ? */ *graph);

  if (!deps_resolved->acyclic) {

    compiler__verror(string_add(
        tos3("import cycle detected between the following modules: \n"),
        compiler__DepGraph_display_cycles(&/* ? */ *deps_resolved)));
  };

  return deps_resolved;
}
compiler__DepGraph *compiler__V_import_graph(compiler__V *v) {

  compiler__DepGraph *graph = compiler__new_dep_graph();

  array_compiler__Parser tmp18 = v->parsers;
  for (int tmp19 = 0; tmp19 < tmp18.len; tmp19++) {
    compiler__Parser p = ((compiler__Parser *)tmp18.data)[tmp19];

    array_string deps = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    map_string tmp20 = p.import_table.imports;
    array_string keys_tmp20 = map_keys(&tmp20);
    for (int l = 0; l < keys_tmp20.len; l++) {
      string _ = ((string *)keys_tmp20.data)[l];
      string m = tos3("");
      map_get(tmp20, _, &m);

      _PUSH(&deps, (/*typ = array_string   tmp_typ=string*/ m), tmp21, string);
    };

    compiler__DepGraph_add(graph, p.mod, deps);
  };

  return graph;
}
array_string compiler__DepGraph_imports(compiler__DepGraph *graph) {

  array_string mods = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__DepGraphNode tmp22 = graph->nodes;
  for (int tmp23 = 0; tmp23 < tmp22.len; tmp23++) {
    compiler__DepGraphNode node = ((compiler__DepGraphNode *)tmp22.data)[tmp23];

    _PUSH(&mods, (/*typ = array_string   tmp_typ=string*/ node.name), tmp24,
          string);
  };

  return mods;
}
string compiler__V_module_path(compiler__V *v, string mod) {

  if (string_contains(mod, tos3("."))) {

    return string_replace(mod, tos3("."), os__path_separator);
  };

  return mod;
}
Option_string compiler__V_find_module_path(compiler__V *v, string mod) {

  string mod_path = compiler__V_module_path(&/* ? */ *v, mod);

  string import_path = string_add(
      os__getwd(), _STR("%.*s%.*s", os__path_separator.len,
                        os__path_separator.str, mod_path.len, mod_path.str));

  if (string_eq(mod, tos3("compiler")) || !os__dir_exists(import_path)) {

    import_path = _STR("%.*s%.*svlib%.*s%.*s", v->lang_dir.len, v->lang_dir.str,
                       os__path_separator.len, os__path_separator.str,
                       os__path_separator.len, os__path_separator.str,
                       mod_path.len, mod_path.str);
  };

  if (!os__dir_exists(import_path)) {

    import_path = _STR("%.*s%.*s%.*s", compiler__v_modules_path.len,
                       compiler__v_modules_path.str, os__path_separator.len,
                       os__path_separator.str, mod_path.len, mod_path.str);

    if (!os__dir_exists(import_path)) {

      return v_error(_STR("module \"%.*s\" not found", mod.len, mod.str));
    };
  };

  string tmp25 = OPTION_CAST(string)(import_path);
  return opt_ok(&tmp25, sizeof(string));
}
static inline string compiler__mod_gen_name(string mod) {

  return string_replace(mod, tos3("."), tos3("_dot_"));
}
static inline string compiler__mod_gen_name_rev(string mod) {

  return string_replace(mod, tos3("_dot_"), tos3("."));
}
Option_string compiler__find_windows_kit_internal(RegKey key,
                                                  array_string versions) {

#ifdef _WIN32

  array_string tmp1 = versions;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    string version = ((string *)tmp1.data)[tmp2];

    int required_bytes = 0;

    void *result =
        RegQueryValueEx(key, string_to_wide(version), 0, 0, 0, &required_bytes);

    int length = required_bytes / 2;

    if (result != 0) {

      continue;
    };

    int alloc_length = (required_bytes + 2);

    u16 *value = ((u16 *)(v_malloc(alloc_length)));

    if (isnil(value)) {

      continue;
    };

    void *result2 = RegQueryValueEx(key, string_to_wide(version), 0, 0, value,
                                    &alloc_length);

    if (result2 != 0) {

      continue;
    };

    if ((value[/*ptr*/ length - 1] /*ru16 1*/ != ((u16)(0)))) {

      value[/*ptr*/ length] /*ru16 1*/ = ((u16)(0));
    };

    string tmp3 = OPTION_CAST(string)(string_from_wide(value));
    return opt_ok(&tmp3, sizeof(string));
  };

#endif
  ;

  return v_error(tos3("windows kit not found"));
}
Option_compiler__WindowsKit compiler__find_windows_kit_root(string host_arch) {

#ifdef _WIN32

  RegKey root_key = ((RegKey)(0));

  void *rc =
      RegOpenKeyEx(compiler__HKEY_LOCAL_MACHINE,
                   string_to_wide(tos3(
                       "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots")),
                   0,
                   compiler__KEY_QUERY_VALUE | compiler__KEY_WOW64_32KEY |
                       compiler__KEY_ENUMERATE_SUB_KEYS,
                   &root_key);

  if (rc != 0) {

    Option tmp4 = v_error(tos3("Unable to open root key"));
    { RegCloseKey(root_key); }
    return tmp4;
    ;
  };

  Option_string tmp5 = compiler__find_windows_kit_internal(
      root_key,
      new_array_from_c_array(2, 2, sizeof(string),
                             EMPTY_ARRAY_OF_ELEMS(string, 2){
                                 tos3("KitsRoot10"), tos3("KitsRoot81")}));
  string kit_root;
  if (!tmp5.ok) {
    string err = tmp5.error;
    int errcode = tmp5.ecode;

    Option tmp6 = v_error(tos3("Unable to find a windows kit"));
    { RegCloseKey(root_key); }
    return tmp6;
    ;
  }
  kit_root = *(string *)tmp5.data;
  ;

  string kit_lib = string_add(kit_root, tos3("Lib"));

  Option_array_string tmp7 = os__ls(kit_lib);
  array_string files;
  if (!tmp7.ok) {
    string err = tmp7.error;
    int errcode = tmp7.ecode;

    v_panic(err);
  }
  files = *(array_string *)tmp7.data;
  ;

  string highest_path = tos3("");

  int highest_int = 0;

  array_string tmp8 = files;
  for (int tmp9 = 0; tmp9 < tmp8.len; tmp9++) {
    string f = ((string *)tmp8.data)[tmp9];

    string no_dot = string_replace(f, tos3("."), tos3(""));

    int v_int = v_string_int(no_dot);

    if (v_int > highest_int) {

      highest_int = v_int;

      highest_path = f;
    };
  };

  string kit_lib_highest =
      string_add(kit_lib, _STR("\\%.*s", highest_path.len, highest_path.str));

  string kit_include_highest =
      string_replace(kit_lib_highest, tos3("Lib"), tos3("Include"));

  compiler__WindowsKit tmp10 = OPTION_CAST(
      compiler__WindowsKit)((compiler__WindowsKit){
      .um_lib_path = string_add(
          kit_lib_highest, _STR("\\um\\%.*s", host_arch.len, host_arch.str)),
      .ucrt_lib_path = string_add(
          kit_lib_highest, _STR("\\ucrt\\%.*s", host_arch.len, host_arch.str)),
      .um_include_path = string_add(kit_include_highest, tos3("\\um")),
      .ucrt_include_path = string_add(kit_include_highest, tos3("\\ucrt")),
      .shared_include_path =
          string_add(kit_include_highest, tos3("\\shared"))});
  { RegCloseKey(root_key); }
  return opt_ok(&tmp10, sizeof(compiler__WindowsKit));

  {

    RegCloseKey(root_key);
  }
#endif
  ;

  return v_error(tos3("Host OS does not support funding a windows kit"));
}
Option_compiler__VsInstallation compiler__find_vs(string vswhere_dir,
                                                  string host_arch) {

#ifndef _WIN32

  return v_error(tos3("Host OS does not support finding a Vs installation"));

#endif
  ;

  Option_os__Result tmp11 =
      os__exec(_STR("\"%.*s\\Microsoft Visual Studio\\Installer\\vswhere.exe\" "
                    "-latest -prerelease -products * -requires "
                    "Microsoft.VisualStudio.Component.VC.Tools.x86.x64 "
                    "-property installationPath",
                    vswhere_dir.len, vswhere_dir.str));
  os__Result res;
  if (!tmp11.ok) {
    string err = tmp11.error;
    int errcode = tmp11.ecode;

    return v_error(err);
  }
  res = *(os__Result *)tmp11.data;
  ;

  Option_string tmp12 = os__read_file(
      _STR("%.*s\\VC\\Auxiliary\\Build\\Microsoft.VCToolsVersion.default.txt",
           res.output.len, res.output.str));
  string version;
  if (!tmp12.ok) {
    string err = tmp12.error;
    int errcode = tmp12.ecode;

    println(tos3("Unable to find msvc version"));

    return v_error(tos3("Unable to find vs installation"));
  }
  version = *(string *)tmp12.data;
  ;

  string v = (string_ends_with(version, tos3("\n")))
                 ? (string_substr2(version, 0, version.len - 2, false))
                 : (version);

  string lib_path =
      _STR("%.*s\\VC\\Tools\\MSVC\\%.*s\\lib\\%.*s", res.output.len,
           res.output.str, v.len, v.str, host_arch.len, host_arch.str);

  string include_path = _STR("%.*s\\VC\\Tools\\MSVC\\%.*s\\include",
                             res.output.len, res.output.str, v.len, v.str);

  if (os__file_exists(
          _STR("%.*s\\vcruntime.lib", lib_path.len, lib_path.str))) {

    string p = _STR("%.*s\\VC\\Tools\\MSVC\\%.*s\\bin\\Host%.*s\\%.*s",
                    res.output.len, res.output.str, v.len, v.str, host_arch.len,
                    host_arch.str, host_arch.len, host_arch.str);

    compiler__VsInstallation tmp15 =
        OPTION_CAST(compiler__VsInstallation)((compiler__VsInstallation){
            .exe_path = p, .lib_path = lib_path, .include_path = include_path});
    return opt_ok(&tmp15, sizeof(compiler__VsInstallation));
  };

  printf(
      "Unable to find vs installation (attempted to use lib path \"%.*s\")\n",
      lib_path.len, lib_path.str);

  return v_error(tos3("Unable to find vs exe folder"));
}
Option_compiler__MsvcResult compiler__find_msvc() {

#ifdef _WIN32

  string processor_architecture = os__getenv(tos3("PROCESSOR_ARCHITECTURE"));

  string vswhere_dir = (string_eq(processor_architecture, tos3("x86")))
                           ? (tos3("%ProgramFiles%"))
                           : (tos3("%ProgramFiles(x86)%"));

  string host_arch = (string_eq(processor_architecture, tos3("x86")))
                         ? (tos3("X86"))
                         : (tos3("X64"));

  Option_compiler__WindowsKit tmp16 =
      compiler__find_windows_kit_root(host_arch);
  compiler__WindowsKit wk;
  if (!tmp16.ok) {
    string err = tmp16.error;
    int errcode = tmp16.ecode;

    return v_error(tos3("Unable to find windows sdk"));
  }
  wk = *(compiler__WindowsKit *)tmp16.data;
  ;

  Option_compiler__VsInstallation tmp17 =
      compiler__find_vs(vswhere_dir, host_arch);
  compiler__VsInstallation vs;
  if (!tmp17.ok) {
    string err = tmp17.error;
    int errcode = tmp17.ecode;

    return v_error(tos3("Unable to find visual studio"));
  }
  vs = *(compiler__VsInstallation *)tmp17.data;
  ;

  compiler__MsvcResult tmp18 =
      OPTION_CAST(compiler__MsvcResult)((compiler__MsvcResult){
          .full_cl_exe_path = os__realpath(string_add(
              string_add(vs.exe_path, os__path_separator), tos3("cl.exe"))),
          .exe_path = vs.exe_path,
          .um_lib_path = wk.um_lib_path,
          .ucrt_lib_path = wk.ucrt_lib_path,
          .vs_lib_path = vs.lib_path,
          .um_include_path = wk.um_include_path,
          .ucrt_include_path = wk.ucrt_include_path,
          .vs_include_path = vs.include_path,
          .shared_include_path = wk.shared_include_path});
  return opt_ok(&tmp18, sizeof(compiler__MsvcResult));

#else

  compiler__verror(tos3("Cannot find msvc on this OS"));

  return v_error(tos3("msvc not found"));

#endif
  ;
}
void compiler__V_cc_msvc(compiler__V *v) {

  Option_compiler__MsvcResult tmp19 = compiler__find_msvc();
  compiler__MsvcResult r;
  if (!tmp19.ok) {
    string err = tmp19.error;
    int errcode = tmp19.ecode;

    if (!v->pref->is_keep_c && string_ne(v->out_name_c, tos3("v.c")) &&
        string_ne(v->out_name_c, tos3("v_macos.c"))) {

      os__rm(v->out_name_c);
    };

    compiler__verror(tos3("Cannot find MSVC on this OS"));

    return;
  }
  r = *(compiler__MsvcResult *)tmp19.data;
  ;

  string out_name_obj = os__realpath(string_add(v->out_name_c, tos3(".obj")));

  array_string a = new_array_from_c_array(
      4, 4, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 4){
          tos3("-w"), tos3("/we4013"), tos3("/volatile:ms"),
          _STR("/Fo\"%.*s\"", out_name_obj.len, out_name_obj.str)});

  if (v->pref->is_prod) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/O2")), tmp20,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/MD")), tmp21,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/Zi")), tmp22,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/DNDEBUG")), tmp23,
          string);

  } else {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/Zi")), tmp24,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/MDd")), tmp25,
          string);
  };

  if (v->pref->is_so) {

    if (!string_ends_with(v->out_name, tos3(".dll"))) {

      v->out_name = string_add(v->out_name, tos3(".dll"));
    };

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/LD")), tmp26,
          string);

  } else if (!string_ends_with(v->out_name, tos3(".exe"))) {

    v->out_name = string_add(v->out_name, tos3(".exe"));
  };

  v->out_name = os__realpath(v->out_name);

  if (v->pref->build_mode == compiler__compiler__BuildMode_build_module) {

  } else if (v->pref->build_mode ==
             compiler__compiler__BuildMode_default_mode) {
  };

  if (v->pref->sanitize) {

    println(tos3("Sanitize not supported on msvc."));
  };

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ string_add(
            string_add(tos3("\""), os__realpath(v->out_name_c)), tos3("\""))),
        tmp27, string);

  array_string real_libs = new_array_from_c_array(
      12, 12, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 12){
          tos3("kernel32.lib"), tos3("user32.lib"), tos3("gdi32.lib"),
          tos3("winspool.lib"), tos3("comdlg32.lib"), tos3("advapi32.lib"),
          tos3("shell32.lib"), tos3("ole32.lib"), tos3("oleaut32.lib"),
          tos3("uuid.lib"), tos3("odbc32.lib"), tos3("odbccp32.lib")});

  compiler__MsvcStringFlags sflags = array_compiler__CFlag_msvc_string_flags(
      compiler__V_get_os_cflags(&/* ? */ *v));

  _PUSH_MANY(&real_libs,
             (/*typ = array_string   tmp_typ=string*/ sflags.real_libs), tmp28,
             array_string);

  array_string inc_paths = sflags.inc_paths;

  array_string lib_paths = sflags.lib_paths;

  array_string other_flags = sflags.other_flags;

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-I \"%.*s\"", r.ucrt_include_path.len, r.ucrt_include_path.str)),
        tmp29, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-I \"%.*s\"", r.vs_include_path.len, r.vs_include_path.str)),
        tmp30, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-I \"%.*s\"", r.um_include_path.len, r.um_include_path.str)),
        tmp31, string);

  _PUSH(
      &a,
      (/*typ = array_string   tmp_typ=string*/ _STR(
          "-I \"%.*s\"", r.shared_include_path.len, r.shared_include_path.str)),
      tmp32, string);

  _PUSH_MANY(&a, (/*typ = array_string   tmp_typ=string*/ inc_paths), tmp33,
             array_string);

  _PUSH_MANY(&a, (/*typ = array_string   tmp_typ=string*/ other_flags), tmp34,
             array_string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ array_string_join(real_libs,
                                                                   tos3(" "))),
        tmp35, string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/link")), tmp36,
        string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/NOLOGO")), tmp37,
        string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/OUT:\"%.*s\"", v->out_name.len, v->out_name.str)),
        tmp38, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/LIBPATH:\"%.*s\"", r.ucrt_lib_path.len, r.ucrt_lib_path.str)),
        tmp39, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/LIBPATH:\"%.*s\"", r.um_lib_path.len, r.um_lib_path.str)),
        tmp40, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/LIBPATH:\"%.*s\"", r.vs_lib_path.len, r.vs_lib_path.str)),
        tmp41, string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/DEBUG:FULL")),
        tmp42, string);

  if (v->pref->is_prod) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/INCREMENTAL:NO")),
          tmp43, string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/OPT:REF")), tmp44,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/OPT:ICF")), tmp45,
          string);
  };

  _PUSH_MANY(&a, (/*typ = array_string   tmp_typ=string*/ lib_paths), tmp46,
             array_string);

  string args = array_string_join(a, tos3(" "));

  string cmd = _STR("\"%.*s\" %.*s", r.full_cl_exe_path.len,
                    r.full_cl_exe_path.str, args.len, args.str);

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    println(tos3("\n========== cl cmd line:"));

    println(cmd);

    println(tos3("==========\n"));
  };

  Option_os__Result tmp47 = os__exec(cmd);
  os__Result res;
  if (!tmp47.ok) {
    string err = tmp47.error;
    int errcode = tmp47.ecode;

    println(err);

    compiler__verror(tos3("msvc error"));

    return;
  }
  res = *(os__Result *)tmp47.data;
  ;

  if (res.exit_code != 0) {

    compiler__verror(res.output);
  };

  if (!v->pref->is_keep_c && string_ne(v->out_name_c, tos3("v.c")) &&
      string_ne(v->out_name_c, tos3("v_macos.c"))) {

    os__rm(v->out_name_c);
  };

  os__rm(out_name_obj);
}
void compiler__build_thirdparty_obj_file_with_msvc(
    string path, array_compiler__CFlag moduleflags) {

  Option_compiler__MsvcResult tmp48 = compiler__find_msvc();
  compiler__MsvcResult msvc;
  if (!tmp48.ok) {
    string err = tmp48.error;
    int errcode = tmp48.ecode;

    println(tos3("Could not find visual studio"));

    return;
  }
  msvc = *(compiler__MsvcResult *)tmp48.data;
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

  Option_array_string tmp49 = os__ls(parent);
  array_string files;
  if (!tmp49.ok) {
    string err = tmp49.error;
    int errcode = tmp49.ecode;

    v_panic(err);
  }
  files = *(array_string *)tmp49.data;
  ;

  string cfiles = tos3("");

  array_string tmp50 = files;
  for (int tmp51 = 0; tmp51 < tmp50.len; tmp51++) {
    string file = ((string *)tmp50.data)[tmp51];

    if (string_ends_with(file, tos3(".c"))) {

      cfiles = string_add(
          cfiles,
          string_add(
              string_add(tos3("\""),
                         os__realpath(string_add(
                             string_add(parent, os__path_separator), file))),
              tos3("\" ")));
    };
  };

  string include_string =
      _STR("-I \"%.*s\" -I \"%.*s\" -I \"%.*s\" -I \"%.*s\"",
           msvc.ucrt_include_path.len, msvc.ucrt_include_path.str,
           msvc.vs_include_path.len, msvc.vs_include_path.str,
           msvc.um_include_path.len, msvc.um_include_path.str,
           msvc.shared_include_path.len, msvc.shared_include_path.str);

  string btarget =
      array_compiler__CFlag_c_options_before_target_msvc(moduleflags);

  string atarget =
      array_compiler__CFlag_c_options_after_target_msvc(moduleflags);

  string cmd = _STR(
      "\"%.*s\" /volatile:ms /Zi /DNDEBUG %.*s /c %.*s %.*s %.*s /Fo\"%.*s\"",
      msvc.full_cl_exe_path.len, msvc.full_cl_exe_path.str, include_string.len,
      include_string.str, btarget.len, btarget.str, cfiles.len, cfiles.str,
      atarget.len, atarget.str, obj_path.len, obj_path.str);

  printf("thirdparty cmd line: %.*s\n", cmd.len, cmd.str);

  Option_os__Result tmp52 = os__exec(cmd);
  os__Result res;
  if (!tmp52.ok) {
    string err = tmp52.error;
    int errcode = tmp52.ecode;

    printf("msvc: failed thirdparty object build cmd: %.*s\n", cmd.len,
           cmd.str);

    compiler__verror(err);

    return;
  }
  res = *(os__Result *)tmp52.data;
  ;

  if (res.exit_code != 0) {

    printf("msvc: failed thirdparty object build cmd: %.*s\n", cmd.len,
           cmd.str);

    compiler__verror(res.output);

    return;
  };

  println(res.output);
}
compiler__MsvcStringFlags
array_compiler__CFlag_msvc_string_flags(array_compiler__CFlag cflags) {

  array_string real_libs = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string inc_paths = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string lib_paths = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string other_flags = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_compiler__CFlag tmp53 = cflags;
  for (int tmp54 = 0; tmp54 < tmp53.len; tmp54++) {
    compiler__CFlag flag = ((compiler__CFlag *)tmp53.data)[tmp54];

    if (string_eq(flag.name, tos3("-l"))) {

      if (string_ends_with(flag.value, tos3(".dll"))) {

        compiler__verror(
            _STR("MSVC cannot link against a dll (`#flag -l %.*s`)",
                 flag.value.len, flag.value.str));
      };

      string lib_lib = string_add(flag.value, tos3(".lib"));

      _PUSH(&real_libs, (/*typ = array_string   tmp_typ=string*/ lib_lib),
            tmp55, string);

    } else if (string_eq(flag.name, tos3("-I"))) {

      _PUSH(&inc_paths,
            (/*typ = array_string   tmp_typ=string*/ compiler__CFlag_format(
                &/* ? */ flag)),
            tmp56, string);

    } else if (string_eq(flag.name, tos3("-L"))) {

      _PUSH(&lib_paths, (/*typ = array_string   tmp_typ=string*/ flag.value),
            tmp57, string);

      _PUSH(&lib_paths,
            (/*typ = array_string   tmp_typ=string*/ string_add(
                string_add(flag.value, os__path_separator), tos3("msvc"))),
            tmp58, string);

    } else if (string_ends_with(flag.value, tos3(".o"))) {

      _PUSH(&other_flags,
            (/*typ = array_string   tmp_typ=string*/ _STR(
                "\"%.*sbj\"", flag.value.len, flag.value.str)),
            tmp59, string);

    } else {

      _PUSH(&other_flags, (/*typ = array_string   tmp_typ=string*/ flag.value),
            tmp60, string);
    };
  };

  array_string lpaths = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string tmp61 = lib_paths;
  for (int tmp62 = 0; tmp62 < tmp61.len; tmp62++) {
    string l = ((string *)tmp61.data)[tmp62];

    _PUSH(&lpaths,
          (/*typ = array_string   tmp_typ=string*/ string_add(
              string_add(tos3("/LIBPATH:\""), os__realpath(l)), tos3("\""))),
          tmp63, string);
  };

  return (compiler__MsvcStringFlags){real_libs, inc_paths, lpaths, other_flags};
}
void compiler__Parser_in_optimization(compiler__Parser *p, string typ, int ph) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

  int i = 0;

  string expr = string_substr2(p->cgen->cur_line, ph, -1, true);

  bool is_str = string_eq(typ, tos3("string"));

  while (p->tok != compiler__compiler__TokenKind_rsbr &&
         p->tok != compiler__compiler__TokenKind_eof) {

    if (i > 0) {

      if (is_str) {

        compiler__Parser_gen(p,
                             _STR(" || string_eq(%.*s, ", expr.len, expr.str));

      } else {

        compiler__Parser_gen(p, _STR(" || %.*s == ", expr.len, expr.str));
      };
    };

    if (i == 0) {

      if (is_str) {

        compiler__CGen_set_placeholder(p->cgen, ph, tos3(" string_eq("));

        compiler__Parser_gen(p, tos3(", "));

      } else {

        compiler__Parser_gen(p, tos3(" =="));
      };
    };

    compiler__Parser_check_types(p, compiler__Parser_bool_expression(p), typ);

    if (is_str) {

      compiler__Parser_gen(p, tos3(")"));
    };

    if (p->tok != compiler__compiler__TokenKind_rsbr) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
    };

    i++;
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);
}
compiler__Parser compiler__V_new_parser_from_string(compiler__V *v,
                                                    string text) {

  compiler__Parser p = compiler__V_new_parser(v, compiler__new_scanner(text));

  compiler__Parser_scan_tokens(&/* ? */ p);

  return p;
}
void compiler__V_reset_cgen_file_line_parameters(compiler__V *v) {

  v->cgen->line = 0;

  v->cgen->file = tos3("");

  v->cgen->line_directives = v->pref->is_vlines;
}
compiler__Parser compiler__V_new_parser_from_file(compiler__V *v, string path) {

  compiler__V_reset_cgen_file_line_parameters(v);

  string path_pcguard = tos3("");

  string path_platform = tos3(".v");

  array_string tmp1 = new_array_from_c_array(
      7, 7, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 7){
          tos3("_lin.v"), tos3("_mac.v"), tos3("_win.v"), tos3("_nix.v"),
          tos3("_linux.v"), tos3("_darwin.v"), tos3("_windows.v")});
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    string path_ending = ((string *)tmp1.data)[tmp2];

    if (string_ends_with(path, path_ending)) {

      if (string_eq(path_ending, tos3("_mac.v"))) {

        string p =
            string_replace(path_ending, tos3("_mac.v"), tos3("_darwin.v"));

        printf("warning: use \"%.*s\" file name instead of \"%.*s\"\n", p.len,
               p.str, path.len, path.str);
      };

      if (string_eq(path_ending, tos3("_lin.v"))) {

        string p =
            string_replace(path_ending, tos3("_lin.v"), tos3("_linux.v"));

        printf("warning: use \"%.*s\" file name instead of \"%.*s\"\n", p.len,
               p.str, path.len, path.str);
      };

      if (string_eq(path_ending, tos3("_win.v"))) {

        string p =
            string_replace(path_ending, tos3("_win.v"), tos3("_windows.v"));

        printf("warning: use \"%.*s\" file name instead of \"%.*s\"\n", p.len,
               p.str, path.len, path.str);
      };

      path_platform = path_ending;

      path_pcguard = compiler__platform_postfix_to_ifdefguard(path_ending);

      break;
    };
  };

  compiler__Parser p =
      compiler__V_new_parser(v, compiler__new_scanner_file(path));

  p = (compiler__Parser){
      .file_path = path,
      .file_name = string_all_after(path, os__path_separator),
      .file_platform = path_platform,
      .file_pcguard = path_pcguard,
      .is_vh = string_ends_with(path, tos3(".vh")),
      .v_script = string_ends_with(path, tos3(".vsh")),
      .v = p.v,
      .pref = p.pref,
      .scanner = p.scanner,
      .tokens = p.tokens,
      .token_idx = p.token_idx,
      .tok = p.tok,
      .prev_tok = p.prev_tok,
      .prev_tok2 = p.prev_tok2,
      .lit = p.lit,
      .cgen = p.cgen,
      .table = p.table,
      .import_table = p.import_table,
      .pass = p.pass,
      .os = p.os,
      .inside_const = p.inside_const,
      .expr_var = p.expr_var,
      .has_immutable_field = p.has_immutable_field,
      .first_immutable_field = p.first_immutable_field,
      .assigned_type = p.assigned_type,
      .expected_type = p.expected_type,
      .tmp_cnt = p.tmp_cnt,
      .builtin_mod = p.builtin_mod,
      .inside_if_expr = p.inside_if_expr,
      .inside_unwrapping_match_statement = p.inside_unwrapping_match_statement,
      .inside_return_expr = p.inside_return_expr,
      .inside_unsafe = p.inside_unsafe,
      .is_struct_init = p.is_struct_init,
      .is_var_decl = p.is_var_decl,
      .if_expr_cnt = p.if_expr_cnt,
      .for_expr_cnt = p.for_expr_cnt,
      .ptr_cast = p.ptr_cast,
      .calling_c = p.calling_c,
      .cur_fn = p.cur_fn,
      .local_vars = p.local_vars,
      .var_idx = p.var_idx,
      .returns = p.returns,
      .vroot = p.vroot,
      .is_c_struct_init = p.is_c_struct_init,
      .is_empty_c_struct_init = p.is_empty_c_struct_init,
      .is_c_fn_call = p.is_c_fn_call,
      .can_chash = p.can_chash,
      .attr = p.attr,
      .var_decl_name = p.var_decl_name,
      .is_alloc = p.is_alloc,
      .is_const_literal = p.is_const_literal,
      .in_dispatch = p.in_dispatch,
      .is_vgen = p.is_vgen,
      .is_vweb = p.is_vweb,
      .is_sql = p.is_sql,
      .is_js = p.is_js,
      .sql_i = p.sql_i,
      .sql_params = p.sql_params,
      .sql_types = p.sql_types,
      .mod = p.mod,
  };

  if (p.v_script) {

    println(tos3("new_parser: V script"));
  };

  if (p.pref->building_v) {

    p.scanner->should_print_relative_paths_on_error = 1;
  };

  compiler__Parser_scan_tokens(&/* ? */ p);

  return p;
}
compiler__Parser compiler__V_new_parser(compiler__V *v,
                                        compiler__Scanner *scanner) {

  compiler__V_reset_cgen_file_line_parameters(v);

  compiler__Parser p = (compiler__Parser){
      .scanner = scanner,
      .v = v,
      .table = v->table,
      .cur_fn = compiler__EmptyFn,
      .cgen = v->cgen,
      .pref = v->pref,
      .os = v->os,
      .vroot = v->vroot,
      .local_vars = array_repeat(
          new_array_from_c_array(
              1, 1, sizeof(compiler__Var),
              EMPTY_ARRAY_OF_ELEMS(compiler__Var, 1){(compiler__Var){
                  .typ = tos3(""),
                  .name = tos3(""),
                  .idx = 0,
                  .is_arg = 0,
                  .is_const = 0,
                  .args = new_array(0, 1, sizeof(compiler__Var)),
                  .attr = tos3(""),
                  .is_mut = 0,
                  .is_alloc = 0,
                  .is_returned = 0,
                  .ptr = 0,
                  .ref = 0,
                  .parent_fn = tos3(""),
                  .mod = tos3(""),
                  .is_global = 0,
                  .is_used = 0,
                  .is_changed = 0,
                  .scope_level = 0,
                  .is_c = 0,
                  .is_moved = 0,
                  .line_nr = 0,
                  .token_idx = 0,
                  .is_for_var = 0,
                  .is_public = 0}}),
          compiler__MaxLocalVars),
      .import_table = compiler__new_import_table(),
      .file_path = tos3(""),
      .file_name = tos3(""),
      .file_platform = tos3(""),
      .file_pcguard = tos3(""),
      .tokens = new_array(0, 1, sizeof(compiler__Token)),
      .token_idx = 0,
      .lit = tos3(""),
      .inside_const = 0,
      .has_immutable_field = 0,
      .assigned_type = tos3(""),
      .expected_type = tos3(""),
      .tmp_cnt = 0,
      .builtin_mod = 0,
      .inside_if_expr = 0,
      .inside_unwrapping_match_statement = 0,
      .inside_return_expr = 0,
      .inside_unsafe = 0,
      .is_struct_init = 0,
      .is_var_decl = 0,
      .if_expr_cnt = 0,
      .for_expr_cnt = 0,
      .ptr_cast = 0,
      .calling_c = 0,
      .var_idx = 0,
      .returns = 0,
      .is_c_struct_init = 0,
      .is_empty_c_struct_init = 0,
      .is_c_fn_call = 0,
      .can_chash = 0,
      .attr = tos3(""),
      .v_script = 0,
      .var_decl_name = tos3(""),
      .is_alloc = 0,
      .is_const_literal = 0,
      .in_dispatch = 0,
      .is_vgen = 0,
      .is_vweb = 0,
      .is_sql = 0,
      .is_js = 0,
      .sql_i = 0,
      .sql_params = new_array(0, 1, sizeof(string)),
      .sql_types = new_array(0, 1, sizeof(string)),
      .is_vh = 0,
      .mod = tos3("")};

#ifdef _VJS

  p.is_js = 1;

#endif
  ;

  if (p.pref->is_repl) {

    p.scanner->should_print_line_on_error = 0;

    p.scanner->should_print_errors_in_color = 0;

    p.scanner->should_print_relative_paths_on_error = 1;
  };

  return p;
}
void compiler__Parser_scan_tokens(compiler__Parser *p) {

  while (1) {

    compiler__ScanRes res = compiler__Scanner_scan(p->scanner);

    _PUSH(&p->tokens,
          (/*typ = array_compiler__Token   tmp_typ=compiler__Token*/ (
              compiler__Token){
              .tok = res.tok,
              .lit = res.lit,
              .line_nr = p->scanner->line_nr,
              .col = p->scanner->pos - p->scanner->last_nl_pos,
              .name_idx = 0,
          }),
          tmp3, compiler__Token);

    if (res.tok == compiler__compiler__TokenKind_eof) {

      break;
    };
  };
}
void compiler__Parser_set_current_fn(compiler__Parser *p, compiler__Fn f) {

  p->cur_fn = f;

  p->scanner->fn_name =
      _STR("%.*s.%.*s", f.mod.len, f.mod.str, f.name.len, f.name.str);
}
void compiler__Parser_next(compiler__Parser *p) {

  p->prev_tok2 = p->prev_tok;

  p->prev_tok = p->tok;

  p->scanner->prev_tok = p->tok;

  if (p->token_idx >= p->tokens.len) {

    p->tok = compiler__compiler__TokenKind_eof;

    p->lit = tos3("");

    return;
  };

  compiler__Token res =
      (*(compiler__Token *)array_get(p->tokens, p->token_idx));

  p->token_idx++;

  p->tok = res.tok;

  p->lit = res.lit;

  p->scanner->line_nr = res.line_nr;

  p->cgen->line = res.line_nr;
}
compiler__TokenKind compiler__Parser_peek(compiler__Parser *p) {

  if (p->token_idx >= p->tokens.len - 2) {

    return compiler__compiler__TokenKind_eof;
  };

  compiler__Token tok =
      (*(compiler__Token *)array_get(p->tokens, p->token_idx));

  return tok.tok;
}
static inline compiler__Token compiler__Parser_prev_token(compiler__Parser *p) {

  return (*(compiler__Token *)array_get(p->tokens, p->token_idx - 2));
}
static inline compiler__Token compiler__Parser_cur_tok(compiler__Parser *p) {

  return (*(compiler__Token *)array_get(p->tokens, p->token_idx - 1));
}
static inline compiler__Token compiler__Parser_peek_token(compiler__Parser *p) {

  if (p->token_idx >= p->tokens.len - 2) {

    return (compiler__Token){.tok = compiler__compiler__TokenKind_eof,
                             .lit = tos3(""),
                             .line_nr = 0,
                             .name_idx = 0,
                             .col = 0};
  };

  return (*(compiler__Token *)array_get(p->tokens, p->token_idx));
}
void compiler__Parser_log(compiler__Parser *p, string s) {}
void compiler__Parser_parse(compiler__Parser *p, compiler__Pass pass) {

  p->cgen->line = 0;

  p->cgen->file = compiler__cescaped_path(os__realpath(p->file_path));

  p->pass = pass;

  p->token_idx = 0;

  compiler__Parser_next(p);

  if (p->pref->is_script || p->pref->is_test) {

    if (p->tok == compiler__compiler__TokenKind_key_module) {

      compiler__Parser_next(p);

      ;

      p->mod = compiler__Parser_check_name(p);

    } else {

      p->mod = tos3("main");
    };

  } else {

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_module);

    ;

    p->mod = compiler__Parser_check_name(p);
  };

  p->cgen->nogen = 0;

  if (p->pref->build_mode == compiler__compiler__BuildMode_build_module &&
      string_ne(p->mod, p->v->mod)) {

    p->cgen->nogen = 1;
  };

  ;

  p->builtin_mod = string_eq(p->mod, tos3("builtin"));

  p->can_chash =
      string_eq(p->mod, tos3("ui")) || string_eq(p->mod, tos3("darwin"));

  string fq_mod =
      (p->pref->build_mode == compiler__compiler__BuildMode_build_module &&
       string_ends_with(p->v->mod, p->mod))
          ? (p->v->mod)
          : (compiler__Table_qualify_module(&/* ? */ *p->table, p->mod,
                                            p->file_path));

  compiler__Table_register_module(p->table, fq_mod);

  p->mod = fq_mod;

  if (p->pass == compiler__compiler__Pass_imports) {

    while (p->tok == compiler__compiler__TokenKind_key_import &&
           compiler__Parser_peek(&/* ? */ *p) !=
               compiler__compiler__TokenKind_key_const) {

      compiler__Parser_imports(p);
    };

    if ((_IN(string, (tos3("builtin")), p->table->imports))) {

      compiler__Parser_error(p, tos3("module `builtin` cannot be imported"));
    };

    return;
  };

  while (1) {

    compiler__TokenKind tmp14 = p->tok;

    if (tmp14 == compiler__compiler__TokenKind_key_import) {

      if (compiler__Parser_peek(&/* ? */ *p) ==
          compiler__compiler__TokenKind_key_const) {

        compiler__Parser_const_decl(p);

      } else {

        compiler__Parser_imports(p);

        if (p->tok != compiler__compiler__TokenKind_key_import) {

          ;
        };
      };

    } else if (tmp14 == compiler__compiler__TokenKind_key_enum) {

      compiler__TokenKind next = compiler__Parser_peek(&/* ? */ *p);

      if (next == compiler__compiler__TokenKind_name) {

        ;

        ;

        compiler__Parser_enum_decl(p, 0);

      } else if (next == compiler__compiler__TokenKind_lcbr &&
                 p->pref->translated) {

        compiler__Parser_enum_decl(p, 1);
      };

    } else if (tmp14 == compiler__compiler__TokenKind_key_pub) {

      compiler__TokenKind next = compiler__Parser_peek(&/* ? */ *p);

      compiler__TokenKind tmp15 = next;

      if (tmp15 == compiler__compiler__TokenKind_key_fn) {

        compiler__Parser_fn_decl(p);

      } else if (tmp15 == compiler__compiler__TokenKind_key_const) {

        compiler__Parser_const_decl(p);

      } else if ((tmp15 == compiler__compiler__TokenKind_key_struct) ||
                 (tmp15 == compiler__compiler__TokenKind_key_union) ||
                 (tmp15 == compiler__compiler__TokenKind_key_interface)) {

        compiler__Parser_struct_decl(p);

      } else if (tmp15 == compiler__compiler__TokenKind_key_enum) {

        compiler__Parser_enum_decl(p, 0);

      } else // default:
      {

        compiler__Parser_error(p, tos3("wrong pub keyword usage"));
      };

    } else if (tmp14 == compiler__compiler__TokenKind_key_fn) {

      compiler__Parser_fn_decl(p);

    } else if (tmp14 == compiler__compiler__TokenKind_key_type) {

      compiler__Parser_type_decl(p);

    } else if (tmp14 == compiler__compiler__TokenKind_lsbr) {

      compiler__Parser_attribute(p);

    } else if ((tmp14 == compiler__compiler__TokenKind_key_struct) ||
               (tmp14 == compiler__compiler__TokenKind_key_interface) ||
               (tmp14 == compiler__compiler__TokenKind_key_union) ||
               (tmp14 == compiler__compiler__TokenKind_lsbr)) {

      compiler__Parser_struct_decl(p);

    } else if (tmp14 == compiler__compiler__TokenKind_key_const) {

      compiler__Parser_const_decl(p);

    } else if (tmp14 == compiler__compiler__TokenKind_hash) {

      compiler__Parser_chash(p);

    } else if (tmp14 == compiler__compiler__TokenKind_dollar) {

      compiler__Parser_comp_time(p);

    } else if (tmp14 == compiler__compiler__TokenKind_key_global) {

      if (!p->pref->translated && !p->pref->is_live && !p->builtin_mod &&
          !p->pref->building_v && string_ne(p->mod, tos3("ui")) &&
          !string_contains(os__getwd(), tos3("/volt")) &&
          !p->pref->enable_globals) {

        compiler__Parser_error(
            p, tos3("use `v --enable-globals ...` to enable globals"));
      };

      compiler__Parser_next(p);

      string name = compiler__Parser_check_name(p);

      string typ = compiler__Parser_get_type(p);

      compiler__Parser_register_global(p, name, typ);

      string g =
          compiler__Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ);

      if (p->tok == compiler__compiler__TokenKind_assign) {

        compiler__Parser_next(p);

        g = string_add(g, tos3(" = "));

        _V_MulRet_string_V_string _V_mret___expr = compiler__Parser_tmp_expr(p);
        string expr = _V_mret___expr.var_1;

        g = string_add(g, expr);
      };

      g = string_add(g, tos3("; // global"));

      if (!p->cgen->nogen) {

        _PUSH(&p->cgen->consts, (/*typ = array_string   tmp_typ=string*/ g),
              tmp16, string);
      };

    } else if (tmp14 == compiler__compiler__TokenKind_eof) {

      if (!compiler__Parser_first_pass(&/* ? */ *p) && !p->pref->is_repl) {

        compiler__Parser_check_unused_imports(p);
      };

      if (0 && !compiler__Parser_first_pass(&/* ? */ *p) &&
          compiler__Parser_fileis(&/* ? */ *p, tos3("main.v"))) {

        Option_os__File tmp17 = os__create(tos3("/var/tmp/fmt.v"));
        os__File out;
        if (!tmp17.ok) {
          string err = tmp17.error;
          int errcode = tmp17.ecode;

          compiler__verror(tos3("failed to create fmt.v"));

          return;
        }
        out = *(os__File *)tmp17.data;
        ;

        os__File_writeln(out, strings__Builder_str(p->scanner->fmt_out));

        os__File_close(out);
      };

      return;

    } else // default:
    {

      if (p->pref->is_script && !p->pref->is_test) {

        if (string_eq(p->cur_fn.name, tos3(""))) {

          compiler__Parser_set_current_fn(p, compiler__MainFn);

          if (p->pref->is_repl) {

            if (compiler__Parser_first_pass(&/* ? */ *p)) {

              return;
            };

            compiler__Parser_clear_vars(p);
          };
        };

        int start = p->cgen->lines.len;

        compiler__Parser_statement(p, 1);

        if (start > 0 &&
            string_ne((*(string *)array_get(p->cgen->lines, start - 1)),
                      tos3("")) &&
            string_ne(p->cgen->fn_main, tos3(""))) {

          start--;
        };

        compiler__Parser_genln(p, tos3(""));

        int end = p->cgen->lines.len;

        array_string lines = array_slice(p->cgen->lines, start, end);

        p->cgen->fn_main =
            string_add(p->cgen->fn_main, array_string_join(lines, tos3("\n")));

        compiler__CGen_resetln(p->cgen, tos3(""));

        for (int i = start; i < end; i++) {

          array_set(&/*q*/ p->cgen->lines, i, &(string[]){tos3("")});
        };

      } else {

        compiler__Parser_error(p,
                               _STR("unexpected token `%.*s`",
                                    compiler__Parser_strtok(&/* ? */ *p).len,
                                    compiler__Parser_strtok(&/* ? */ *p).str));
      };
    };
  };
}
void compiler__Parser_imports(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_import);

  if (p->tok == compiler__compiler__TokenKind_lpar) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    while (p->tok != compiler__compiler__TokenKind_rpar &&
           p->tok != compiler__compiler__TokenKind_eof) {

      compiler__Parser_import_statement(p);
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    return;
  };

  compiler__Parser_import_statement(p);
}
void compiler__Parser_import_statement(compiler__Parser *p) {

  if (p->tok != compiler__compiler__TokenKind_name) {

    compiler__Parser_error(p, tos3("bad import format"));
  };

  if (compiler__Parser_peek(&/* ? */ *p) ==
      compiler__compiler__TokenKind_number) {

    compiler__Parser_error(p, tos3("bad import format. module/submodule names "
                                   "cannot begin with a number"));
  };

  int import_tok_idx = p->token_idx - 1;

  string mod = string_trim_space(compiler__Parser_check_name(p));

  string mod_alias = mod;

  int depth = 1;

  while (p->tok == compiler__compiler__TokenKind_dot) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    string submodule = compiler__Parser_check_name(p);

    mod_alias = submodule;

    mod = string_add(mod, string_add(tos3("."), submodule));

    depth++;

    if (depth > compiler__MaxModuleDepth) {

      compiler__Parser_error(p,
                             _STR("module depth of %d exceeded: %.*s",
                                  compiler__MaxModuleDepth, mod.len, mod.str));
    };
  };

  if (p->tok == compiler__compiler__TokenKind_key_as &&
      compiler__Parser_peek(&/* ? */ *p) ==
          compiler__compiler__TokenKind_name) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_as);

    mod_alias = compiler__Parser_check_name(p);
  };

  compiler__Parser_register_import_alias(p, mod_alias, mod, import_tok_idx);

  if ((_IN(string, (mod), p->table->imports))) {

    return;
  };

  _PUSH(&p->table->imports, (/*typ = array_string   tmp_typ=string*/ mod),
        tmp20, string);

  compiler__Table_register_module(p->table, mod);

  ;
}
void compiler__Parser_const_decl(compiler__Parser *p) {

  bool is_pub = p->tok == compiler__compiler__TokenKind_key_pub;

  if (is_pub) {

    compiler__Parser_next(p);
  };

  p->inside_const = 1;

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_const);

  ;

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  ;

  ;

  while (p->tok == compiler__compiler__TokenKind_name) {

    if (string_eq(p->lit, tos3("_")) &&
        compiler__Parser_peek(&/* ? */ *p) ==
            compiler__compiler__TokenKind_assign &&
        !p->cgen->nogen) {

      compiler__Parser_gen_blank_identifier_assign(p);

      _PUSH(&p->cgen->consts_init,
            (/*typ = array_string   tmp_typ=string*/ string_trim_space(
                p->cgen->cur_line)),
            tmp21, string);

      compiler__CGen_resetln(p->cgen, tos3(""));

      continue;
    };

    string name = compiler__Parser_check_name(p);

    name = compiler__Parser_prepend_mod(&/* ? */ *p, name);

    string typ = tos3("");

    if (p->is_vh) {

      if (p->tok == compiler__compiler__TokenKind_assign) {

        compiler__Parser_next(p);

        p->cgen->nogen = 1;

        typ = compiler__Parser_expression(p);

        p->cgen->nogen = 0;

      } else {

        typ = compiler__Parser_get_type(p);
      };

      compiler__Table_register_const(p->table, name, typ, p->mod, is_pub);

      _PUSH(
          &p->cgen->consts,
          (/*typ = array_string   tmp_typ=string*/ string_add(
              (string_add(tos3("extern "), compiler__Table_cgen_name_type_pair(
                                               &/* ? */ *p->table, name, typ))),
              tos3(";"))),
          tmp22, string);

      continue;

    } else {

      compiler__Parser_check_space(p, compiler__compiler__TokenKind_assign);

      typ = compiler__Parser_expression(p);
    };

    if (compiler__Parser_first_pass(&/* ? */ *p) &&
        compiler__Table_known_const(&/* ? */ *p->table, name)) {

      compiler__Parser_error(
          p, _STR("redefinition of `%.*s`", name.len, name.str));
    };

    if (compiler__Parser_first_pass(&/* ? */ *p)) {

      compiler__Table_register_const(p->table, name, typ, p->mod, is_pub);
    };

    Option_compiler__Var tmp23 =
        compiler__Table_find_const(&/* ? */ *p->v->table, name);

    if (tmp23.ok) {
      compiler__Var my_const = *(compiler__Var *)tmp23.data;

      if (string_eq(my_const.typ, tos3("void"))) {

        array_compiler__Var tmp24 = p->v->table->consts;
        for (int i = 0; i < tmp24.len; i++) {
          compiler__Var v = ((compiler__Var *)tmp24.data)[i];

          if (string_eq(v.name, name)) {

            (*(compiler__Var *)array_get(p->v->table->consts, i)).typ = typ;

            break;
          };
        };
      };
    };

    if (p->pass == compiler__compiler__Pass_main && p->cgen->nogen &&
        p->pref->build_mode == compiler__compiler__BuildMode_build_module) {

      _PUSH(
          &p->cgen->consts,
          (/*typ = array_string   tmp_typ=string*/ string_add(
              (string_add(tos3("extern "), compiler__Table_cgen_name_type_pair(
                                               &/* ? */ *p->table, name, typ))),
              tos3(";"))),
          tmp27, string);
    };

    if (p->pass == compiler__compiler__Pass_main && !p->cgen->nogen) {

      if (p->pref->build_mode != compiler__compiler__BuildMode_build_module &&
          compiler__is_compile_time_const(p->cgen->cur_line)) {

        _PUSH(&p->cgen->consts,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "#define %.*s %.*s", name.len, name.str,
                  p->cgen->cur_line.len, p->cgen->cur_line.str)),
              tmp28, string);

        compiler__CGen_resetln(p->cgen, tos3(""));

        ;

        continue;
      };

      if (string_starts_with(typ, tos3("["))) {

        _PUSH(&p->cgen->consts,
              (/*typ = array_string   tmp_typ=string*/ string_add(
                  compiler__Table_cgen_name_type_pair(&/* ? */ *p->table, name,
                                                      typ),
                  _STR(" = %.*s;", p->cgen->cur_line.len,
                       p->cgen->cur_line.str))),
              tmp29, string);

      } else {

        _PUSH(&p->cgen->consts,
              (/*typ = array_string   tmp_typ=string*/ string_add(
                  compiler__Table_cgen_name_type_pair(&/* ? */ *p->table, name,
                                                      typ),
                  tos3(";"))),
              tmp30, string);

        _PUSH(&p->cgen->consts_init,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "%.*s = %.*s;", name.len, name.str, p->cgen->cur_line.len,
                  p->cgen->cur_line.str)),
              tmp31, string);
      };

      compiler__CGen_resetln(p->cgen, tos3(""));
    };

    ;
  };

  ;

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  ;

  p->inside_const = 0;
}
void compiler__Parser_type_decl(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_type);

  string name = compiler__Parser_check_name(p);

  if (p->tok == compiler__compiler__TokenKind_key_struct) {

    compiler__Parser_error(
        p, _STR("use `struct %.*s {` instead of `type %.*s struct {`", name.len,
                name.str, name.len, name.str));
  };

  compiler__Type parent = compiler__Parser_get_type2(p);

  string nt_pair = compiler__Table_cgen_name_type_pair(&/* ? */ *p->table, name,
                                                       parent.name);

  string _struct =
      (parent.cat != compiler__compiler__TypeCategory_array &&
       parent.cat != compiler__compiler__TypeCategory_func &&
       !compiler__Table_known_type(&/* ? */ *p->table, parent.name))
          ? (tos3("struct"))
          : (tos3(""));

  compiler__Parser_gen_typedef(
      p, _STR("typedef %.*s %.*s; //type alias name=\"%.*s\" parent=`%.*s`",
              _struct.len, _struct.str, nt_pair.len, nt_pair.str, name.len,
              name.str, parent.name.len, parent.name.str));

  compiler__Table_register_type2(
      p->table,
      (compiler__Type){.name = name,
                       .parent = parent.name,
                       .mod = p->mod,
                       .cat = compiler__compiler__TypeCategory_alias,
                       .is_public = 0,
                       .fields = new_array(0, 1, sizeof(compiler__Var)),
                       .methods = new_array(0, 1, sizeof(compiler__Fn)),
                       .is_c = 0,
                       .enum_vals = new_array(0, 1, sizeof(string)),
                       .gen_types = new_array(0, 1, sizeof(string)),
                       .is_placeholder = 0,
                       .gen_str = 0});
}
compiler__Fn *compiler__Parser_interface_method(compiler__Parser *p,
                                                string field_name,
                                                string receiver) {

  compiler__Fn *method = (compiler__Fn *)memdup(
      &(compiler__Fn){.name = field_name,
                      .is_interface = 1,
                      .is_method = 1,
                      .receiver_typ = receiver,
                      .mod = tos3(""),
                      .args = new_array(0, 1, sizeof(compiler__Var)),
                      .scope_level = 0,
                      .typ = tos3(""),
                      .is_c = 0,
                      .is_public = 0,
                      .is_decl = 0,
                      .is_unsafe = 0,
                      .is_deprecated = 0,
                      .is_variadic = 0,
                      .is_generic = 0,
                      .returns_error = 0,
                      .defer_text = new_array(0, 1, sizeof(string)),
                      .type_pars = new_array(0, 1, sizeof(string)),
                      .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                      .body_idx = 0,
                      .fn_name_token_idx = 0,
                      .comptime_define = tos3(""),
                      .is_used = 0},
      sizeof(compiler__Fn));

  compiler__Parser_fn_args(p, method);

  compiler__Token prev_tok = compiler__Parser_prev_token(&/* ? */ *p);

  compiler__Token cur_tok = compiler__Parser_cur_tok(&/* ? */ *p);

  if (prev_tok.line_nr != cur_tok.line_nr) {

    method->typ = tos3("void");

  } else {

    method->typ = compiler__Parser_get_type(p);

    ;

    ;
  };

  return method;
}
compiler__TypeCategory compiler__key_to_type_cat(compiler__TokenKind tok) {

  compiler__TokenKind tmp32 = tok;

  if (tmp32 == compiler__compiler__TokenKind_key_interface) {

    return compiler__compiler__TypeCategory_interface_;

  } else if (tmp32 == compiler__compiler__TokenKind_key_struct) {

    return compiler__compiler__TypeCategory_struct_;

  } else if (tmp32 == compiler__compiler__TokenKind_key_union) {

    return compiler__compiler__TypeCategory_union_;
  };

  compiler__verror(_STR("Unknown token: %d", tok));

  return compiler__compiler__TypeCategory_builtin;
}
string compiler__Parser_check_name(compiler__Parser *p) {

  string name = p->lit;

  compiler__Parser_check(p, compiler__compiler__TokenKind_name);

  return name;
}
string compiler__Parser_check_string(compiler__Parser *p) {

  string s = p->lit;

  compiler__Parser_check(p, compiler__compiler__TokenKind_str);

  return s;
}
void compiler__Parser_check_not_reserved(compiler__Parser *p) {

  bool tmp33 = 0;
  bool tmp34 =
      map_get(/*parser.v : 699*/ compiler__Reserved_Types, p->lit, &tmp33);

  if (tmp33) {

    compiler__Parser_error(
        p, _STR("`%.*s` can\'t be used as name", p->lit.len, p->lit.str));
  };
}
string compiler__Parser_strtok(compiler__Parser *p) {

  if (p->tok == compiler__compiler__TokenKind_name) {

    return p->lit;
  };

  if (p->tok == compiler__compiler__TokenKind_str) {

    return _STR("\"%.*s\"", p->lit.len, p->lit.str);
  };

  string res = compiler__TokenKind_str(p->tok);

  if (string_eq(res, tos3(""))) {

    int n = ((int)(p->tok));

    return int_str(n);
  };

  return res;
}
void compiler__Parser_check_space(compiler__Parser *p,
                                  compiler__TokenKind expected) {

  ;

  compiler__Parser_check(p, expected);

  ;
}
void compiler__Parser_check(compiler__Parser *p, compiler__TokenKind expected) {

  if (p->tok != expected) {

    println(tos3("check()"));

    string s = _STR("expected `%.*s` but got `%.*s`",
                    compiler__TokenKind_str(expected).len,
                    compiler__TokenKind_str(expected).str,
                    compiler__Parser_strtok(&/* ? */ *p).len,
                    compiler__Parser_strtok(&/* ? */ *p).str);

    compiler__Parser_next(p);

    printf("next token = `%.*s`\n", compiler__Parser_strtok(&/* ? */ *p).len,
           compiler__Parser_strtok(&/* ? */ *p).str);

    if (p->pref->is_debug) {

      print_backtrace();
    };

    compiler__Parser_error(p, s);
  };

  compiler__Parser_next(p);
}
static inline bool compiler__Parser_first_pass(compiler__Parser *p) {

  return p->pass == compiler__compiler__Pass_decl;
}
string compiler__Parser_get_type(compiler__Parser *p) {

  bool mul = 0;

  int nr_muls = 0;

  string typ = tos3("");

  if (p->tok == compiler__compiler__TokenKind_lpar) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    array_string types = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    while (1) {

      _PUSH(&types,
            (/*typ = array_string   tmp_typ=string*/ compiler__Parser_get_type(
                p)),
            tmp35, string);

      if (p->tok != compiler__compiler__TokenKind_comma) {

        break;
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    typ = compiler__Parser_register_multi_return_stuct(p, types);

    return typ;
  };

  if (p->tok == compiler__compiler__TokenKind_key_fn) {

    compiler__Fn f =
        (compiler__Fn){.name = tos3("_"),
                       .mod = p->mod,
                       .args = new_array(0, 1, sizeof(compiler__Var)),
                       .is_interface = 0,
                       .scope_level = 0,
                       .typ = tos3(""),
                       .receiver_typ = tos3(""),
                       .is_c = 0,
                       .is_public = 0,
                       .is_method = 0,
                       .is_decl = 0,
                       .is_unsafe = 0,
                       .is_deprecated = 0,
                       .is_variadic = 0,
                       .is_generic = 0,
                       .returns_error = 0,
                       .defer_text = new_array(0, 1, sizeof(string)),
                       .type_pars = new_array(0, 1, sizeof(string)),
                       .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                       .body_idx = 0,
                       .fn_name_token_idx = 0,
                       .comptime_define = tos3(""),
                       .is_used = 0};

    compiler__Parser_next(p);

    int line_nr = p->scanner->line_nr;

    compiler__Parser_fn_args(
        p, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f);

    if (p->scanner->line_nr == line_nr) {

      if (p->tok == compiler__compiler__TokenKind_name ||
          p->tok == compiler__compiler__TokenKind_mul ||
          p->tok == compiler__compiler__TokenKind_amp ||
          p->tok == compiler__compiler__TokenKind_lsbr ||
          p->tok == compiler__compiler__TokenKind_question ||
          p->tok == compiler__compiler__TokenKind_lpar) {

        f.typ = compiler__Parser_get_type(p);

      } else {

        f.typ = tos3("void");
      };

    } else {

      f.typ = tos3("void");
    };

    compiler__Type fn_typ =
        (compiler__Type){.name = compiler__Fn_typ_str(&/* ? */ f),
                         .mod = p->mod,
                         .func = f,
                         .is_public = 0,
                         .fields = new_array(0, 1, sizeof(compiler__Var)),
                         .methods = new_array(0, 1, sizeof(compiler__Fn)),
                         .parent = tos3(""),
                         .is_c = 0,
                         .enum_vals = new_array(0, 1, sizeof(string)),
                         .gen_types = new_array(0, 1, sizeof(string)),
                         .is_placeholder = 0,
                         .gen_str = 0};

    compiler__Table_register_type2(p->table, fn_typ);

    return compiler__Fn_typ_str(&/* ? */ f);
  };

  int arr_level = 0;

  bool is_question = p->tok == compiler__compiler__TokenKind_question;

  if (is_question) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_question);
  };

  while (p->tok == compiler__compiler__TokenKind_lsbr) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

    if (p->tok == compiler__compiler__TokenKind_number) {

      typ = string_add(typ, _STR("[%.*s]", p->lit.len, p->lit.str));

      compiler__Parser_next(p);

    } else {

      arr_level++;
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);
  };

  if (!p->builtin_mod && p->tok == compiler__compiler__TokenKind_name &&
      string_eq(p->lit, tos3("map"))) {

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

    string key_type = compiler__Parser_check_name(p);

    if (string_ne(key_type, tos3("string"))) {

      compiler__Parser_error(p, tos3("maps only support string keys for now"));
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

    string val_type = compiler__Parser_get_type(p);

    typ = _STR("map_%.*s", val_type.len, val_type.str);

    compiler__Parser_register_map(p, typ);

    return typ;
  };

  bool warn = 0;

  while (p->tok == compiler__compiler__TokenKind_mul) {

    if (compiler__Parser_first_pass(&/* ? */ *p)) {

      warn = 1;
    };

    mul = 1;

    nr_muls++;

    compiler__Parser_check(p, compiler__compiler__TokenKind_mul);
  };

  if (p->tok == compiler__compiler__TokenKind_amp) {

    mul = 1;

    nr_muls++;

    compiler__Parser_check(p, compiler__compiler__TokenKind_amp);
  };

  map_string ti = p->cur_fn.dispatch_of.inst;

  if ((_IN(string, (p->lit), map_keys(&/* ? */ ti)))) {

    string tmp36 = tos3("");
    bool tmp37 = map_get(/*parser.v : 869*/ ti, p->lit, &tmp36);

    if (!tmp37)
      tmp36 = tos((byte *)"", 0);

    typ = string_add(typ, tmp36);

  } else {

    typ = string_add(typ, p->lit);
  };

  if (!p->is_struct_init) {

    ;
  };

  if (string_eq(p->lit, tos3("C")) &&
      compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_dot) {

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    typ = p->lit;

  } else {

    if (warn && string_ne(p->mod, tos3("ui"))) {

      compiler__Parser_warn(p, tos3("use `&Foo` instead of `*Foo`"));
    };

    if (compiler__Parser_peek(&/* ? */ *p) ==
        compiler__compiler__TokenKind_dot) {

      if (!p->builtin_mod &&
          compiler__ImportTable_known_alias(&/* ? */ p->import_table, typ)) {

        string mod =
            compiler__ImportTable_resolve_alias(&/* ? */ p->import_table, typ);

        if (string_contains(mod, tos3("."))) {

          typ = compiler__mod_gen_name(mod);
        };
      };

      compiler__Parser_next(p);

      compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

      typ = string_add(typ, _STR("__%.*s", p->lit.len, p->lit.str));
    };

    compiler__Type t = compiler__Table_find_type(&/* ? */ *p->table, typ);

    if (string_eq(t.name, tos3("")) && !p->builtin_mod) {

      if (!string_contains(typ, tos3("array_")) &&
          string_ne(p->mod, tos3("main")) &&
          !string_contains(typ, tos3("__")) &&
          !string_starts_with(typ, tos3("["))) {

        typ = compiler__Parser_prepend_mod(&/* ? */ *p, typ);
      };

      t = compiler__Table_find_type(&/* ? */ *p->table, typ);

      if (string_eq(t.name, tos3("")) && !p->pref->translated &&
          !compiler__Parser_first_pass(&/* ? */ *p) &&
          !string_starts_with(typ, tos3("["))) {

        println(tos3("get_type() bad type"));

        _V_MulRet_string_V_string _V_mret_t_suggest_tc_suggest =
            compiler__Table_find_misspelled_type(&/* ? */ *p->table, typ, p,
                                                 0.50);
        string t_suggest = _V_mret_t_suggest_tc_suggest.var_0;
        string tc_suggest = _V_mret_t_suggest_tc_suggest.var_1;

        if (t_suggest.len > 0) {

          t_suggest = _STR(". did you mean: (%.*s) `%.*s`", tc_suggest.len,
                           tc_suggest.str, t_suggest.len, t_suggest.str);
        };

        compiler__Parser_error(p, _STR("unknown type `%.*s`%.*s", typ.len,
                                       typ.str, t_suggest.len, t_suggest.str));
      };

    } else if (!t.is_public && string_ne(t.mod, p->mod) && !p->is_vgen &&
               string_ne(t.name, tos3("")) &&
               !compiler__Parser_first_pass(&/* ? */ *p)) {

      compiler__Parser_error(
          p, _STR("type `%.*s` is private", t.name.len, t.name.str));
    };
  };

  if (string_eq(typ, tos3("void"))) {

    compiler__Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
  };

  if (mul) {

    typ = string_add(typ, strings__repeat('*', nr_muls));
  };

  if (arr_level > 0) {

    for (int i = 0; i < arr_level; i++) {

      typ = _STR("array_%.*s", typ.len, typ.str);
    };

    compiler__Parser_register_array(p, typ);
  };

  compiler__Parser_next(p);

  if (is_question) {

    typ = _STR("Option_%.*s", typ.len, typ.str);

    compiler__Table_register_type_with_parent(p->table, typ, tos3("Option"));
  };

  if (string_eq(typ, tos3("byteptr"))) {

    return tos3("byte*");
  };

  if (string_eq(typ, tos3("voidptr"))) {

    return tos3("void*");
  };

  if (string_last_index(typ, tos3("__")) > string_index(typ, tos3("__"))) {

    compiler__Parser_error(
        p, _STR("2 __ in gettype(): typ=\"%.*s\"", typ.len, typ.str));
  };

  return typ;
}
void compiler__Parser_print_tok(compiler__Parser *p) {

  if (p->tok == compiler__compiler__TokenKind_name) {

    println(p->lit);

    return;
  };

  if (p->tok == compiler__compiler__TokenKind_str) {

    printf("\"%.*s\"\n", p->lit.len, p->lit.str);

    return;
  };

  println(compiler__TokenKind_str(p->tok));
}
string compiler__Parser_statements(compiler__Parser *p) {

  string typ = compiler__Parser_statements_no_rcbr(p);

  if (!p->inside_if_expr) {

    compiler__Parser_genln(p, tos3("}"));
  };

  return typ;
}
string compiler__Parser_statements_no_rcbr(compiler__Parser *p) {

  compiler__Parser_open_scope(p);

  if (!p->inside_if_expr) {

    compiler__Parser_genln(p, tos3(""));
  };

  int i = 0;

  string last_st_typ = tos3("");

  while (p->tok != compiler__compiler__TokenKind_rcbr &&
         p->tok != compiler__compiler__TokenKind_eof) {

    last_st_typ = compiler__Parser_statement(p, 1);

    if (!p->inside_if_expr) {

      compiler__Parser_genln(p, tos3(""));

      ;
    };

    i++;

    if (i > 50000) {

      compiler__CGen_save(p->cgen);

      compiler__Parser_error(
          p, _STR("more than 50 000 statements in function `%.*s`",
                  p->cur_fn.name.len, p->cur_fn.name.str));
    };
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

  compiler__Parser_close_scope(p);

  return last_st_typ;
}
void compiler__Parser_close_scope(compiler__Parser *p) {

  int i = p->var_idx - 1;

  for (; i >= 0; i--) {

    compiler__Var v = (*(compiler__Var *)array_get(p->local_vars, i));

    if (v.scope_level != p->cur_fn.scope_level) {

      break;
    };

    if (p->pref->autofree && v.is_alloc) {

      string free_fn = tos3("free");

      if (string_starts_with(v.typ, tos3("array_"))) {

        free_fn = tos3("v_array_free");

      } else if (string_eq(v.typ, tos3("string"))) {

        free_fn = tos3("v_string_free");

        continue;

      } else if (v.ptr || string_ends_with(v.typ, tos3("*"))) {

        free_fn = tos3("v_ptr_free");

      } else {

        continue;
      };

      if (p->returns) {

        if (!v.is_returned && string_ne(v.typ, tos3("FILE*"))) {

          string prev_line =
              (*(string *)array_get(p->cgen->lines, p->cgen->lines.len - 2));

          array_set(&/*q*/ p->cgen->lines, p->cgen->lines.len - 2,
                    &(string[]){string_add(
                        _STR("%.*s(%.*s); /* :) close_scope free %.*s */",
                             free_fn.len, free_fn.str, v.name.len, v.name.str,
                             v.typ.len, v.typ.str),
                        prev_line)});
        };

      } else {

        compiler__Parser_genln(p, _STR("%.*s(%.*s); // close_scope free",
                                       free_fn.len, free_fn.str, v.name.len,
                                       v.name.str));
      };
    };
  };

  if (string_ne(*(string *)array_last(p->cur_fn.defer_text), tos3(""))) {

    compiler__Parser_genln(p, *(string *)array_last(p->cur_fn.defer_text));
  };

  p->cur_fn.scope_level--;

  p->cur_fn.defer_text =
      array_slice2(p->cur_fn.defer_text, 0, p->cur_fn.scope_level + 1, false);

  p->var_idx = i + 1;
}
void compiler__Parser_genln(compiler__Parser *p, string s) {

  compiler__CGen_genln(p->cgen, s);
}
void compiler__Parser_gen(compiler__Parser *p, string s) {

  compiler__CGen_gen(p->cgen, s);
}
string compiler__Parser_statement(compiler__Parser *p, bool add_semi) {

  p->expected_type = tos3("");

  if (p->returns && !p->is_vweb) {

    compiler__Parser_error(p, tos3("unreachable code"));
  };

  p->cgen->is_tmp = 0;

  compiler__TokenKind tok = p->tok;

  string q = tos3("");

  compiler__TokenKind tmp44 = tok;

  if (tmp44 == compiler__compiler__TokenKind_name) {

    compiler__TokenKind next = compiler__Parser_peek(&/* ? */ *p);

    if (compiler__Parser_peek(&/* ? */ *p) ==
        compiler__compiler__TokenKind_colon) {

      ;

      string label = compiler__Parser_check_name(p);

      ;

      compiler__Parser_genln(p, string_add(label, tos3(": ;")));

      compiler__Parser_check(p, compiler__compiler__TokenKind_colon);

      return tos3("");

    } else if (compiler__Parser_peek(&/* ? */ *p) ==
                   compiler__compiler__TokenKind_decl_assign ||
               compiler__Parser_peek(&/* ? */ *p) ==
                   compiler__compiler__TokenKind_comma) {

      compiler__Parser_check_not_reserved(p);

      compiler__Parser_var_decl(p);

    } else if (string_eq(p->lit, tos3("_")) &&
               compiler__Parser_peek(&/* ? */ *p) ==
                   compiler__compiler__TokenKind_assign) {

      compiler__Parser_gen_blank_identifier_assign(p);

    } else {

      if (string_eq(p->lit, tos3("panic")) || string_eq(p->lit, tos3("exit"))) {

        p->returns = 1;
      };

      q = compiler__Parser_bool_expression(p);
    };

  } else if (tmp44 == compiler__compiler__TokenKind_key_goto) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_goto);

    ;

    string label = compiler__Parser_check_name(p);

    compiler__Parser_genln(p, _STR("goto %.*s;", label.len, label.str));

    return tos3("");

  } else if (tmp44 == compiler__compiler__TokenKind_key_defer) {

    compiler__Parser_defer_st(p);

    return tos3("");

  } else if (tmp44 == compiler__compiler__TokenKind_hash) {

    compiler__Parser_chash(p);

    return tos3("");

  } else if (tmp44 == compiler__compiler__TokenKind_key_unsafe) {

    compiler__Parser_next(p);

    p->inside_unsafe = 1;

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    compiler__Parser_genln(p, tos3("{"));

    compiler__Parser_statements(p);

    p->inside_unsafe = 0;

  } else if (tmp44 == compiler__compiler__TokenKind_dollar) {

    compiler__Parser_comp_time(p);

  } else if (tmp44 == compiler__compiler__TokenKind_key_if) {

    compiler__Parser_if_st(p, 0, 0);

  } else if (tmp44 == compiler__compiler__TokenKind_key_for) {

    compiler__Parser_for_st(p);

  } else if (tmp44 == compiler__compiler__TokenKind_key_switch) {

    compiler__Parser_switch_statement(p);

  } else if (tmp44 == compiler__compiler__TokenKind_key_match) {

    compiler__Parser_match_statement(p, 0);

  } else if ((tmp44 == compiler__compiler__TokenKind_key_mut) ||
             (tmp44 == compiler__compiler__TokenKind_key_static)) {

    compiler__Parser_var_decl(p);

  } else if (tmp44 == compiler__compiler__TokenKind_key_return) {

    compiler__Parser_return_st(p);

  } else if (tmp44 == compiler__compiler__TokenKind_lcbr) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    compiler__Parser_genln(p, tos3("{"));

    compiler__Parser_statements(p);

    return tos3("");

  } else if (tmp44 == compiler__compiler__TokenKind_key_continue) {

    if (p->for_expr_cnt == 0) {

      compiler__Parser_error(p, tos3("`continue` statement outside `for`"));
    };

    compiler__Parser_genln(p, tos3("continue"));

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_continue);

  } else if (tmp44 == compiler__compiler__TokenKind_key_break) {

    if (p->for_expr_cnt == 0) {

      compiler__Parser_error(p, tos3("`break` statement outside `for`"));
    };

    compiler__Parser_genln(p, tos3("break"));

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_break);

  } else if (tmp44 == compiler__compiler__TokenKind_key_go) {

    compiler__Parser_go_statement(p);

  } else if (tmp44 == compiler__compiler__TokenKind_key_assert) {

    compiler__Parser_assert_statement(p);

  } else // default:
  {

    string typ = compiler__Parser_expression(p);

    if (p->inside_if_expr) {

    } else {

      compiler__Parser_genln(p, tos3("; "));
    };

    return typ;
  };

  if (p->inside_if_expr && p->tok != compiler__compiler__TokenKind_rcbr) {

    compiler__Parser_gen(p, tos3(", "));
  };

  if (add_semi && !p->inside_if_expr) {

    compiler__Parser_genln(p, tos3(";"));
  };

  return q;
}
void compiler__Parser_assign_statement(compiler__Parser *p, compiler__Var v,
                                       int ph, bool is_map) {

  int errtok = compiler__Parser_cur_tok_index(&/* ? */ *p);

  bool is_vid = compiler__Parser_fileis(&/* ? */ *p, tos3("vid"));

  compiler__TokenKind tok = p->tok;

  if (!v.is_mut && !p->pref->translated && !v.is_global && !is_vid) {

    if (v.is_arg) {

      if (p->cur_fn.args.len > 0 &&
          string_eq((*(compiler__Var *)array_get(p->cur_fn.args, 0)).name,
                    v.name)) {

        printf("make the receiver `%.*s` mutable:\nfn (%.*s mut %.*s) %.*s "
               "(...) {\n\n",
               v.name.len, v.name.str, v.name.len, v.name.str, v.typ.len,
               v.typ.str, p->cur_fn.name.len, p->cur_fn.name.str);
      };
    };

    compiler__Parser_error(p,
                           _STR("`%.*s` is immutable", v.name.len, v.name.str));
  };

  if (!v.is_changed) {

    compiler__Parser_mark_var_changed(p, v);
  };

  bool is_str = string_eq(v.typ, tos3("string"));

  bool is_ustr = string_eq(v.typ, tos3("ustring"));

  compiler__TokenKind tmp47 = tok;

  if (tmp47 == compiler__compiler__TokenKind_assign) {

    if (!is_map && !p->is_empty_c_struct_init) {

      compiler__Parser_gen(p, tos3(" = "));
    };

  } else if (tmp47 == compiler__compiler__TokenKind_plus_assign) {

    if (is_str && !p->is_js) {

      compiler__Parser_gen(p,
                           _STR("= string_add(%.*s, ", v.name.len, v.name.str));

    } else if (is_ustr) {

      compiler__Parser_gen(
          p, _STR("= ustring_add(%.*s, ", v.name.len, v.name.str));

    } else {

      compiler__Parser_gen(p, tos3(" += "));
    };

  } else // default:
  {

    compiler__Parser_gen(
        p, string_add(string_add(tos3(" "), compiler__TokenKind_str(p->tok)),
                      tos3(" ")));
  };

  ;

  ;

  ;

  compiler__Parser_next(p);

  int pos = p->cgen->cur_line.len;

  string expr_type = compiler__Parser_bool_expression(p);

  if (string_eq(expr_type, tos3("void"))) {

    _V_MulRet_bool_V_string _V_mret___fn_name =
        compiler__Parser_is_expr_fn_call(p, p->token_idx - 3);
    string fn_name = _V_mret___fn_name.var_1;

    compiler__Parser_error_with_token_index(
        p,
        _STR("%.*s() %.*s", fn_name.len, fn_name.str,
             compiler__err_used_as_value.len, compiler__err_used_as_value.str),
        p->token_idx - 2);
  };

  if (string_starts_with(p->assigned_type, tos3("Option_")) &&
      string_eq(expr_type, string_substr2(p->assigned_type, tos3("Option_").len,
                                          -1, true))) {

    string expr = string_substr2(p->cgen->cur_line, pos, -1, true);

    string left = string_substr2(p->cgen->cur_line, 0, pos, false);

    string typ = string_replace(expr_type, tos3("Option_"), tos3(""));

    compiler__CGen_resetln(
        p->cgen, string_add(left, _STR("opt_ok(%.*s, sizeof(%.*s))", expr.len,
                                       expr.str, typ.len, typ.str)));

  } else if (string_at(expr_type, 0) == '[') {

    string expr = string_all_before(
        string_all_after(string_substr2(p->cgen->cur_line, pos, -1, true),
                         tos3("{")),
        tos3("}"));

    string left = string_all_before(
        string_substr2(p->cgen->cur_line, 0, pos, false), tos3("="));

    string cline_pos = string_substr2(p->cgen->cur_line, pos, -1, true);

    string etype = string_all_before(cline_pos, tos3(" {"));

    if (string_ne(p->assigned_type, p->expected_type)) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("incompatible types: %.*s != %.*s", p->assigned_type.len,
               p->assigned_type.str, p->expected_type.len,
               p->expected_type.str),
          errtok);
    };

    compiler__CGen_resetln(
        p->cgen, _STR("memcpy( (& %.*s), (%.*s{%.*s}), sizeof( %.*s ) );",
                      left.len, left.str, etype.len, etype.str, expr.len,
                      expr.str, left.len, left.str));

  } else if (tok == compiler__compiler__TokenKind_left_shift_assign ||
             tok == compiler__compiler__TokenKind_righ_shift_assign) {

    if (!compiler__is_integer_type(p->assigned_type)) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("cannot use shift operator on non-integer type `%.*s`",
               p->assigned_type.len, p->assigned_type.str),
          errtok);
    };

    if (!compiler__is_integer_type(expr_type)) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("cannot use non-integer type `%.*s` as shift argument",
               expr_type.len, expr_type.str),
          errtok);
    };

  } else if (tok == compiler__compiler__TokenKind_mod_assign) {

    if (!compiler__is_integer_type(p->assigned_type)) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("cannot use modulo operator on non-integer type `%.*s`",
               p->assigned_type.len, p->assigned_type.str),
          errtok);
    };

    if (!compiler__is_integer_type(expr_type)) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("cannot use non-integer type `%.*s` as modulo argument",
               expr_type.len, expr_type.str),
          errtok);
    };

  } else if (!p->builtin_mod && !compiler__Parser_check_types_no_throw(
                                    p, expr_type, p->assigned_type)) {

    compiler__Parser_error_with_token_index(
        p,
        _STR("cannot use type `%.*s` as type `%.*s` in assignment",
             expr_type.len, expr_type.str, p->assigned_type.len,
             p->assigned_type.str),
        errtok);
  };

  if ((is_str || is_ustr) && tok == compiler__compiler__TokenKind_plus_assign &&
      !p->is_js) {

    compiler__Parser_gen(p, tos3(")"));
  };

  p->assigned_type = tos3("");

  if (!v.is_used) {

    compiler__Parser_mark_var_used(p, v);
  };
}
void compiler__Parser_var_decl(compiler__Parser *p) {

  p->is_alloc = 0;

  bool is_mut = p->tok == compiler__compiler__TokenKind_key_mut ||
                p->prev_tok == compiler__compiler__TokenKind_key_for;

  bool is_static = p->tok == compiler__compiler__TokenKind_key_static;

  if (p->tok == compiler__compiler__TokenKind_key_mut) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_mut);

    ;
  };

  if (p->tok == compiler__compiler__TokenKind_key_static) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_static);

    ;
  };

  array_int var_token_idxs =
      new_array_from_c_array(1, 1, sizeof(int),
                             EMPTY_ARRAY_OF_ELEMS(int, 1){
                                 compiler__Parser_cur_tok_index(&/* ? */ *p)});

  array_bool var_mut = new_array_from_c_array(
      1, 1, sizeof(bool), EMPTY_ARRAY_OF_ELEMS(bool, 1){is_mut});

  array_string var_names = new_array_from_c_array(
      1, 1, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 1){compiler__Parser_check_name(p)});

  compiler__Scanner_validate_var_name(&/* ? */ *p->scanner,
                                      (*(string *)array_get(var_names, 0)));

  int new_vars = 0;

  if (string_ne((*(string *)array_get(var_names, 0)), tos3("_")) &&
      !compiler__Parser_known_var(p, (*(string *)array_get(var_names, 0)))) {

    new_vars++;
  };

  while (p->tok == compiler__compiler__TokenKind_comma) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

    if (p->tok == compiler__compiler__TokenKind_key_mut) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_key_mut);

      _PUSH(&var_mut, (/*typ = array_bool   tmp_typ=bool*/ 1), tmp68, bool);

    } else {

      _PUSH(&var_mut, (/*typ = array_bool   tmp_typ=bool*/ 0), tmp69, bool);
    };

    _PUSH(&var_token_idxs,
          (/*typ = array_int   tmp_typ=int*/ compiler__Parser_cur_tok_index(
              &/* ? */ *p)),
          tmp70, int);

    string var_name = compiler__Parser_check_name(p);

    compiler__Scanner_validate_var_name(&/* ? */ *p->scanner, var_name);

    if (string_ne(var_name, tos3("_")) &&
        !compiler__Parser_known_var(p, var_name)) {

      new_vars++;
    };

    _PUSH(&var_names, (/*typ = array_string   tmp_typ=string*/ var_name), tmp71,
          string);
  };

  bool is_assign = p->tok == compiler__compiler__TokenKind_assign;

  bool is_decl_assign = p->tok == compiler__compiler__TokenKind_decl_assign;

  if (is_assign) {

    compiler__Parser_check_space(p, compiler__compiler__TokenKind_assign);

  } else if (is_decl_assign) {

    compiler__Parser_check_space(p, compiler__compiler__TokenKind_decl_assign);

  } else {

    compiler__Parser_error(p, tos3("expected `=` or `:=`"));
  };

  if (is_decl_assign && var_names.len == 1 &&
      string_eq((*(string *)array_get(var_names, 0)), tos3("_"))) {

    compiler__Parser_error_with_token_index(p, tos3("use `=` instead of `:=`"),
                                            *(int *)array_last(var_token_idxs));
  };

  p->var_decl_name = (var_names.len > 1)
                         ? (string_add(tos3("_V_mret_"),
                                       array_string_join(var_names, tos3("_"))))
                         : ((*(string *)array_get(var_names, 0)));

  string t = compiler__Parser_gen_var_decl(p, p->var_decl_name, is_static);

  if (string_eq(t, tos3("void"))) {

    _V_MulRet_bool_V_string _V_mret___fn_name =
        compiler__Parser_is_expr_fn_call(p, p->token_idx - 3);
    string fn_name = _V_mret___fn_name.var_1;

    compiler__Parser_error_with_token_index(
        p,
        _STR("%.*s() %.*s", fn_name.len, fn_name.str,
             compiler__err_used_as_value.len, compiler__err_used_as_value.str),
        p->token_idx - 2);
  };

  array_string var_types = new_array_from_c_array(
      1, 1, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 1){t});

  if (var_names.len > 1) {

    var_types = string_split(
        string_replace(string_replace(t, tos3("_V_MulRet_"), tos3("")),
                       tos3("_PTR_"), tos3("*")),
        tos3("_V_"));
  };

  if (var_names.len != var_types.len) {

    string mr_fn = string_trim_space(
        string_find_between(p->cgen->cur_line, tos3("="), tos3("(")));

    compiler__Parser_error_with_token_index(
        p,
        _STR("assignment mismatch: %d variables but `%.*s` returns %d values",
             var_names.len, mr_fn.len, mr_fn.str, var_types.len),
        *(int *)array_last(var_token_idxs));
  };

  array_string tmp76 = var_names;
  for (int i = 0; i < tmp76.len; i++) {
    string var_name = ((string *)tmp76.data)[i];

    int var_token_idx = (*(int *)array_get(var_token_idxs, i));

    bool var_is_mut = (*(bool *)array_get(var_mut, i));

    string var_type = (*(string *)array_get(var_types, i));

    bool known_var = compiler__Parser_known_var(p, var_name);

    if (string_eq(var_name, tos3("_"))) {

      if (var_is_mut) {

        compiler__Parser_error_with_token_index(
            p, tos3("`mut` has no effect here"), var_token_idx - 1);
      };

      continue;
    };

    if (is_decl_assign && known_var) {

      compiler__Parser_error_with_token_index(
          p, _STR("redefinition of `%.*s`", var_name.len, var_name.str),
          var_token_idx);
    };

    if (known_var && var_is_mut) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("cannot specify mutability for existing var `%.*s`, only for "
               "new vars",
               var_name.len, var_name.str),
          var_token_idx);
    };

    if (is_assign && !known_var) {

      string suggested =
          compiler__Parser_find_misspelled_local_var(&/* ? */ *p, var_name, 50);

      if (string_ne(suggested, tos3(""))) {

        compiler__Parser_error_with_token_index(
            p,
            _STR("undefined: `%.*s`. did you mean:%.*s", var_name.len,
                 var_name.str, suggested.len, suggested.str),
            var_token_idx);
      };

      compiler__Parser_error_with_token_index(
          p, _STR("undefined: `%.*s`.", var_name.len, var_name.str),
          var_token_idx);
    };

    if (var_name.len > 1 && compiler__contains_capital(var_name)) {

      compiler__Parser_error_with_token_index(
          p,
          tos3("variable names cannot contain uppercase letters, use "
               "snake_case instead"),
          var_token_idx);
    };

    if (var_names.len > 1) {

      compiler__Parser_gen(p, tos3(";\n"));

      if (known_var) {

        Option_compiler__Var tmp83 =
            compiler__Parser_find_var(&/* ? */ *p, var_name);
        compiler__Var v;
        if (!tmp83.ok) {
          string err = tmp83.error;
          int errcode = tmp83.ecode;

          compiler__Parser_error_with_token_index(
              p, _STR("cannot find `%.*s`", var_name.len, var_name.str),
              var_token_idx);

          break;
        }
        v = *(compiler__Var *)tmp83.data;
        ;

        compiler__Parser_check_types_with_token_index(p, var_type, v.typ,
                                                      var_token_idx);

        if (!v.is_mut) {

          compiler__Parser_error_with_token_index(
              p, _STR("`%.*s` is immutable", v.name.len, v.name.str),
              var_token_idx);
        };

        compiler__Parser_mark_var_used(p, v);

        compiler__Parser_mark_var_changed(p, v);

        compiler__Parser_gen(p, _STR("%.*s = %.*s.var_%d", var_name.len,
                                     var_name.str, p->var_decl_name.len,
                                     p->var_decl_name.str, i));

        continue;
      };

      compiler__Parser_gen(p,
                           _STR("%.*s %.*s = %.*s.var_%d", var_type.len,
                                var_type.str, var_name.len, var_name.str,
                                p->var_decl_name.len, p->var_decl_name.str, i));
    };

    compiler__Parser_register_var(
        p,
        (compiler__Var){
            .name = var_name,
            .typ = var_type,
            .is_mut = var_is_mut,
            .is_alloc =
                p->is_alloc || string_starts_with(var_type, tos3("array_")),
            .line_nr = (*(compiler__Token *)array_get(p->tokens, var_token_idx))
                           .line_nr,
            .token_idx = var_token_idx,
            .idx = 0,
            .is_arg = 0,
            .is_const = 0,
            .args = new_array(0, 1, sizeof(compiler__Var)),
            .attr = tos3(""),
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .parent_fn = tos3(""),
            .mod = tos3(""),
            .is_global = 0,
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
            .is_for_var = 0,
            .is_public = 0});
  };

  p->var_decl_name = tos3("");

  p->is_empty_c_struct_init = 0;
}
string compiler__Parser_get_struct_type(compiler__Parser *p, string name_,
                                        bool is_c, bool is_ptr) {

  string name = name_;

  if (is_ptr) {

    name = string_add(name, tos3("*"));
  };

  if ((_IN(string, (name), compiler__reserved_type_param_names))) {

    compiler__Parser_warn(p, _STR("name `%.*s` is reserved for type parameters",
                                  name.len, name.str));
  };

  p->is_c_struct_init = is_c;

  return compiler__Parser_struct_init(p, name);
}
string compiler__Parser_get_var_type(compiler__Parser *p, string name,
                                     bool is_ptr, bool is_deref) {

  Option_compiler__Var tmp86 =
      compiler__Parser_find_var_check_new_var(&/* ? */ *p, name);
  compiler__Var v;
  if (!tmp86.ok) {
    string err = tmp86.error;
    int errcode = tmp86.ecode;

    return tos3("");
  }
  v = *(compiler__Var *)tmp86.data;
  ;

  if (string_eq(name, tos3("_"))) {

    compiler__Parser_error(p, tos3("cannot use `_` as value"));
  };

  if (is_ptr) {

    compiler__Parser_gen(p, tos3("&"));

  } else if (is_deref) {

    compiler__Parser_gen(p, tos3("*"));
  };

  if (p->pref->autofree && string_eq(v.typ, tos3("string")) && v.is_arg &&
      string_eq(p->assigned_type, tos3("string"))) {

    compiler__Parser_warn(p, string_add(tos3("setting moved "), v.typ));

    compiler__Parser_mark_arg_moved(p, v);
  };

  string typ = compiler__Parser_var_expr(p, v);

  if (is_deref) {

    if (!string_contains(typ, tos3("*")) &&
        !string_ends_with(typ, tos3("ptr"))) {

      printf("name=\"%.*s\", t=%.*s\n", name.len, name.str, v.typ.len,
             v.typ.str);

      compiler__Parser_error(
          p, _STR("dereferencing requires a pointer, but got `%.*s`", typ.len,
                  typ.str));
    };

    typ = string_replace(typ, tos3("ptr"), tos3(""));

    typ = string_replace(typ, tos3("*"), tos3(""));

  } else if (is_ptr) {

    typ = string_add(typ, tos3("*"));
  };

  if (p->inside_return_expr) {

    compiler__Parser_mark_var_returned(p, v);
  };

  return typ;
}
string compiler__Parser_get_const_type(compiler__Parser *p, string name,
                                       bool is_ptr) {

  Option_compiler__Var tmp87 =
      compiler__Table_find_const(&/* ? */ *p->table, name);
  compiler__Var c;
  if (!tmp87.ok) {
    string err = tmp87.error;
    int errcode = tmp87.ecode;

    return tos3("");
  }
  c = *(compiler__Var *)tmp87.data;
  ;

  if (is_ptr && !c.is_global) {

    compiler__Parser_error(p, _STR("cannot take the address of constant `%.*s`",
                                   c.name.len, c.name.str));

  } else if (is_ptr && c.is_global) {

    compiler__Parser_gen(p, tos3("& /*const*/ "));
  };

  if (!c.is_public && string_ne(c.mod, p->mod)) {

    compiler__Parser_warn(
        p, _STR("constant `%.*s` is private", c.name.len, c.name.str));
  };

  string typ = compiler__Parser_var_expr(p, c);

  if (is_ptr) {

    typ = string_add(typ, tos3("*"));
  };

  return typ;
}
string compiler__Parser_get_c_func_type(compiler__Parser *p, string name) {

  compiler__Fn f =
      (compiler__Fn){.name = name,
                     .is_c = 1,
                     .mod = tos3(""),
                     .args = new_array(0, 1, sizeof(compiler__Var)),
                     .is_interface = 0,
                     .scope_level = 0,
                     .typ = tos3(""),
                     .receiver_typ = tos3(""),
                     .is_public = 0,
                     .is_method = 0,
                     .is_decl = 0,
                     .is_unsafe = 0,
                     .is_deprecated = 0,
                     .is_variadic = 0,
                     .is_generic = 0,
                     .returns_error = 0,
                     .defer_text = new_array(0, 1, sizeof(string)),
                     .type_pars = new_array(0, 1, sizeof(string)),
                     .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                     .body_idx = 0,
                     .fn_name_token_idx = 0,
                     .comptime_define = tos3(""),
                     .is_used = 0};

  p->is_c_fn_call = 1;

  compiler__Parser_fn_call(p,
                           &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f,
                           0, tos3(""), tos3(""));

  p->is_c_fn_call = 0;

  Option_compiler__Fn tmp88 = compiler__Table_find_fn(&/* ? */ *p->table, name);
  compiler__Fn cfn;
  if (!tmp88.ok) {
    string err = tmp88.error;
    int errcode = tmp88.ecode;

    return tos3("void*");
  }
  cfn = *(compiler__Fn *)tmp88.data;
  ;

  return cfn.typ;
}
void compiler__Parser_undefined_error(compiler__Parser *p, string name,
                                      string orig_name) {

  string name_dotted =
      compiler__mod_gen_name_rev(string_replace(name, tos3("__"), tos3(".")));

  string suggested = compiler__Parser_identify_typo(&/* ? */ *p, name);

  if (suggested.len != 0) {

    compiler__Parser_error(p, _STR("undefined: `%.*s`. did you mean:\n%.*s\n",
                                   name_dotted.len, name_dotted.str,
                                   suggested.len, suggested.str));
  };

  if (compiler__Table_known_mod(&/* ? */ *p->table, orig_name) ||
      compiler__ImportTable_known_alias(&/* ? */ p->import_table, orig_name)) {

    compiler__Parser_error(p, _STR("undefined: `%.*s` (in module `%.*s`)",
                                   name_dotted.len, name_dotted.str,
                                   orig_name.len, orig_name.str));

  } else if ((_IN(string, (orig_name), compiler__reserved_type_param_names))) {

    compiler__Parser_error(
        p, _STR("the letter `%.*s` is reserved for type parameters",
                orig_name.len, orig_name.str));
  };

  compiler__Parser_error(
      p, _STR("undefined: `%.*s`", orig_name.len, orig_name.str));
}
string compiler__Parser_var_expr(compiler__Parser *p, compiler__Var v) {

  if (!v.is_const) {

    compiler__Parser_mark_var_used(p, v);
  };

  int fn_ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  p->expr_var = v;

  compiler__Parser_gen(
      p, compiler__Table_var_cgen_name(&/* ? */ *p->table, v.name));

  compiler__Parser_next(p);

  string typ = v.typ;

  if (string_starts_with(typ, tos3("fn ")) &&
      p->tok == compiler__compiler__TokenKind_lpar) {

    compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, typ);

    compiler__Parser_gen(p, tos3("("));

    compiler__Parser_fn_call_args(
        p, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ T.func);

    compiler__Parser_gen(p, tos3(")"));

    typ = T.func.typ;
  };

  if (p->tok == compiler__compiler__TokenKind_lsbr) {

    typ = compiler__Parser_index_expr(p, typ, fn_ph);
  };

  while (p->tok == compiler__compiler__TokenKind_dot) {

    if (compiler__Parser_peek(&/* ? */ *p) ==
        compiler__compiler__TokenKind_key_select) {

      compiler__Parser_next(p);

      return compiler__Parser_select_query(p, fn_ph);
    };

    if (string_eq(typ, tos3("pg__DB")) &&
        !compiler__Parser_fileis(&/* ? */ *p, tos3("pg.v")) &&
        compiler__Parser_peek(&/* ? */ *p) ==
            compiler__compiler__TokenKind_name) {

      compiler__Parser_next(p);

      compiler__Parser_insert_query(p, fn_ph);

      return tos3("void");
    };

    typ = compiler__Parser_dot(p, typ, fn_ph);

    if (p->tok == compiler__compiler__TokenKind_lsbr) {
    };
  };

  if (p->tok == compiler__compiler__TokenKind_inc ||
      p->tok == compiler__compiler__TokenKind_dec) {

    if (!v.is_mut && !v.is_arg && !p->pref->translated) {

      compiler__Parser_error(
          p, _STR("`%.*s` is immutable", v.name.len, v.name.str));
    };

    if (!v.is_changed) {

      compiler__Parser_mark_var_changed(p, v);
    };

    if (string_ne(typ, tos3("int"))) {

      if (!p->pref->translated && !compiler__is_number_type(typ)) {

        compiler__Parser_error(
            p, _STR("cannot ++/-- value of type `%.*s`", typ.len, typ.str));
      };
    };

    compiler__Parser_gen(p, compiler__TokenKind_str(p->tok));

    ;

    compiler__Parser_next(p);

    if (p->pref->translated) {

    } else {

      return tos3("void");
    };
  };

  typ = compiler__Parser_index_expr(p, typ, fn_ph);

  if (p->tok == compiler__compiler__TokenKind_dot) {

    while (p->tok == compiler__compiler__TokenKind_dot) {

      typ = compiler__Parser_dot(p, typ, fn_ph);
    };

    typ = compiler__Parser_index_expr(p, typ, fn_ph);
  };

  return typ;
}
string compiler__Parser_dot(compiler__Parser *p, string str_typ_,
                            int method_ph) {

  string str_typ = str_typ_;

  compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

  bool is_variadic_arg = string_starts_with(str_typ, tos3("varg_"));

  compiler__Type typ = compiler__Parser_find_type(&/* ? */ *p, str_typ);

  if (typ.name.len == 0) {

    compiler__Parser_error(
        p, _STR("dot(): cannot find type `%.*s`", str_typ.len, str_typ.str));
  };

  if (p->tok == compiler__compiler__TokenKind_dollar) {

    compiler__Parser_comptime_method_call(p, typ);

    return tos3("void");
  };

  string field_name = p->lit;

  if (string_eq(field_name, tos3("filter")) &&
      string_starts_with(str_typ, tos3("array_"))) {

    compiler__Parser_gen_array_filter(p, str_typ, method_ph);

    return str_typ;

  } else if (string_eq(field_name, tos3("map")) &&
             string_starts_with(str_typ, tos3("array_"))) {

    return compiler__Parser_gen_array_map(p, str_typ, method_ph);
  };

  int fname_tidx = compiler__Parser_cur_tok_index(&/* ? */ *p);

  ;

  bool has_field = compiler__Table_type_has_field(
      &/* ? */ *p->table,
      &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ typ,
      compiler__Table_var_cgen_name(&/* ? */ *p->table, field_name));

  bool has_method = compiler__Table_type_has_method(
      &/* ? */ *p->table,
      &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ typ, field_name);

  if (is_variadic_arg && string_eq(field_name, tos3("len"))) {

    compiler__Parser_gen(p, _STR("->%.*s", field_name.len, field_name.str));

    compiler__Parser_next(p);

    return tos3("int");
  };

  if (!has_method && string_eq(field_name, tos3("str")) &&
      string_starts_with(typ.name, tos3("array_"))) {

    compiler__Parser_gen_array_str(p, typ);

    has_method = 1;
  };

  if (!typ.is_c && !p->is_c_fn_call && !has_field && !has_method &&
      !compiler__Parser_first_pass(&/* ? */ *p)) {

    if (string_starts_with(typ.name, tos3("Option_"))) {

      string opt_type = string_substr2(typ.name, 7, -1, true);

      compiler__Parser_error(p, _STR("unhandled option type: `?%.*s`",
                                     opt_type.len, opt_type.str));
    };

    compiler__Parser_error_with_token_index(
        p,
        _STR("type `%.*s` has no field or method `%.*s`", typ.name.len,
             typ.name.str, field_name.len, field_name.str),
        fname_tidx);
  };

  string dot = tos3(".");

  if (string_ends_with(str_typ, tos3("*")) ||
      string_eq(str_typ, tos3("FT_Face"))) {

    dot = compiler__dot_ptr;
  };

  if (has_field) {

    string struct_field =
        (string_ne(typ.name, tos3("Option")))
            ? (compiler__Table_var_cgen_name(&/* ? */ *p->table, field_name))
            : (field_name);

    Option_compiler__Var tmp91 = compiler__Table_find_field(
        &/* ? */ *p->table,
        &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ typ, struct_field);
    compiler__Var field;
    if (!tmp91.ok) {
      string err = tmp91.error;
      int errcode = tmp91.ecode;

      compiler__Parser_error_with_token_index(
          p,
          _STR("missing field: %.*s in type %.*s", struct_field.len,
               struct_field.str, typ.name.len, typ.name.str),
          fname_tidx);

      v_exit(1);
    }
    field = *(compiler__Var *)tmp91.data;
    ;

    if (!field.is_mut && !p->has_immutable_field) {

      p->has_immutable_field = 1;

      p->first_immutable_field = field;
    };

    compiler__TokenKind next = compiler__Parser_peek(&/* ? */ *p);

    bool modifying = compiler__TokenKind_is_assign(next) ||
                     next == compiler__compiler__TokenKind_inc ||
                     next == compiler__compiler__TokenKind_dec ||
                     (string_starts_with(field.typ, tos3("array_")) &&
                      next == compiler__compiler__TokenKind_left_shift);

    if (!p->builtin_mod && !p->pref->translated && modifying &&
        p->has_immutable_field) {

      compiler__Var f = p->first_immutable_field;

      compiler__Parser_error_with_token_index(
          p,
          string_add(
              _STR("cannot modify immutable field `%.*s` (type `%.*s`)\n",
                   f.name.len, f.name.str, f.parent_fn.len, f.parent_fn.str),
              _STR("declare the field with `mut:`\nstruct %.*s {\n  "
                   "mut:\n	%.*s %.*s\n}\n",
                   f.parent_fn.len, f.parent_fn.str, f.name.len, f.name.str,
                   f.typ.len, f.typ.str)),
          fname_tidx);
    };

    if (field.access_mod == compiler__compiler__AccessMod_private &&
        !p->builtin_mod && !p->pref->translated && string_ne(p->mod, typ.mod) &&
        !p->is_vgen) {

      compiler__Parser_error_with_token_index(
          p,
          string_add(
              _STR("cannot refer to unexported field `%.*s` (type `%.*s`)\n",
                   struct_field.len, struct_field.str, typ.name.len,
                   typ.name.str),
              _STR("declare the field with `pub:`\nstruct %.*s {\n  "
                   "pub:\n	%.*s %.*s\n}\n",
                   typ.name.len, typ.name.str, struct_field.len,
                   struct_field.str, field.typ.len, field.typ.str)),
          fname_tidx);
    };

    compiler__Parser_gen(p, string_add(dot, struct_field));

    compiler__Parser_next(p);

    return field.typ;
  };

  Option_compiler__Fn tmp92 = compiler__Table_find_method(
      &/* ? */ *p->table,
      &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ typ, field_name);
  compiler__Fn method;
  if (!tmp92.ok) {
    string err = tmp92.error;
    int errcode = tmp92.ecode;

    compiler__Parser_error_with_token_index(
        p, _STR("could not find method `%.*s`", field_name.len, field_name.str),
        fname_tidx);

    v_exit(1);
  }
  method = *(compiler__Fn *)tmp92.data;
  ;

  compiler__Parser_fn_call(
      p, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ method, method_ph,
      tos3(""), str_typ);

  bool is_or_else = p->tok == compiler__compiler__TokenKind_key_orelse;

  if (!p->is_var_decl && is_or_else) {

    method.typ = compiler__Parser_gen_handle_option_or_else(
        p, method.typ, tos3(""), method_ph);

  } else if (!p->is_var_decl && !is_or_else && !p->inside_return_expr &&
             string_starts_with(method.typ, tos3("Option_"))) {

    string opt_type = string_substr2(method.typ, 7, -1, true);

    compiler__Parser_error(
        p, _STR("unhandled option type: `?%.*s`", opt_type.len, opt_type.str));
  };

  if (string_eq(method.typ, tos3("array")) &&
      string_starts_with(typ.name, tos3("array_"))) {

    return typ.name;
  };

  if (string_eq(method.typ, tos3("void*")) &&
      string_starts_with(typ.name, tos3("array_"))) {

    return string_substr2(typ.name, 6, -1, true);
  };

  if (string_ends_with(method.typ, tos3("*"))) {

    p->is_alloc = 1;
  };

  return method.typ;
}
compiler__IndexType compiler__get_index_type(string typ) {

  if (string_starts_with(typ, tos3("map_"))) {

    return compiler__compiler__IndexType_map;
  };

  if (string_eq(typ, tos3("string"))) {

    return compiler__compiler__IndexType_str;
  };

  if (string_starts_with(typ, tos3("array_")) ||
      string_eq(typ, tos3("array"))) {

    return compiler__compiler__IndexType_array;
  };

  if (string_eq(typ, tos3("byte*")) || string_eq(typ, tos3("byteptr")) ||
      string_contains(typ, tos3("*"))) {

    return compiler__compiler__IndexType_ptr;
  };

  if (string_at(typ, 0) == '[') {

    return compiler__compiler__IndexType_fixed_array;
  };

  return compiler__compiler__IndexType_noindex;
}
string compiler__Parser_index_expr(compiler__Parser *p, string typ_,
                                   int fn_ph) {

  string typ = typ_;

  compiler__Var v = p->expr_var;

  bool is_variadic_arg = string_starts_with(typ, tos3("varg_"));

  bool is_map = string_starts_with(typ, tos3("map_"));

  bool is_str = string_eq(typ, tos3("string"));

  bool is_arr0 = string_starts_with(typ, tos3("array_"));

  bool is_arr = is_arr0 || string_eq(typ, tos3("array"));

  bool is_ptr = string_eq(typ, tos3("byte*")) ||
                string_eq(typ, tos3("byteptr")) ||
                string_contains(typ, tos3("*"));

  bool is_slice = 0;

  bool is_indexer = p->tok == compiler__compiler__TokenKind_lsbr;

  bool close_bracket = 0;

  int index_error_tok_pos = p->token_idx;

  if (is_indexer) {

    bool is_fixed_arr = string_at(typ, 0) == '[';

    if (!is_str && !is_arr && !is_map && !is_ptr && !is_fixed_arr &&
        !is_variadic_arg) {

      compiler__Parser_error(
          p, _STR("Cant [] non-array/string/map. Got type \"%.*s\"", typ.len,
                  typ.str));
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

    if (is_str) {

      typ = tos3("byte");

      ;

      if (p->builtin_mod) {

        compiler__Parser_gen(p, tos3(".str["));

        close_bracket = 1;

      } else {

        compiler__Parser_gen(p, tos3(","));
      };
    };

    if (is_variadic_arg) {

      typ = string_substr2(typ, 5, -1, true);
    };

    if (is_fixed_arr) {

      if (string_contains(typ, tos3("]["))) {

        int pos = string_index_after(typ, tos3("["), 1);

        typ = string_substr2(typ, pos, -1, true);

      } else {

        typ = string_all_after(typ, tos3("]"));
      };

      compiler__Parser_gen(p, tos3("["));

      close_bracket = 1;

    } else if (is_ptr && !is_variadic_arg) {

      typ = string_replace(typ, tos3("*"), tos3(""));

      if (!is_arr) {

        compiler__Parser_gen(p, tos3("[/*ptr*/"));

        close_bracket = 1;
      };
    };

    if (is_arr) {

      if (is_arr0) {

        typ = string_substr2(typ, 6, -1, true);
      };

      compiler__Parser_gen_array_at(p, typ, is_arr0, fn_ph);
    };

    if (is_map) {

      typ = string_replace(typ, tos3("map_"), tos3(""));

      if (string_eq(typ, tos3("map"))) {

        typ = tos3("void*");
      };

      compiler__Parser_gen(p, tos3(","));
    };

    if (is_arr || is_str) {

      if (p->tok != compiler__compiler__TokenKind_dotdot) {

        int index_pos = p->cgen->cur_line.len;

        compiler__Type T = compiler__Table_find_type(
            &/* ? */ *p->table, compiler__Parser_expression(p));

        if (string_ne(T.parent, tos3("int")) &&
            string_ne(T.parent, tos3("u32"))) {

          compiler__Parser_check_types(p, T.name, tos3("int"));
        };

        if (v_string_int(string_replace(
                string_substr2(p->cgen->cur_line, index_pos, -1, true),
                tos3(" "), tos3(""))) < 0) {

          compiler__Parser_error(p, tos3("cannot access negative array index"));
        };

      } else {

        compiler__Parser_gen(p, tos3("0"));
      };

      if (p->tok == compiler__compiler__TokenKind_dotdot) {

        if (is_arr) {

          typ = string_add(tos3("array_"), typ);

        } else if (is_str) {

          typ = tos3("string");

        } else {

          compiler__Parser_error(
              p, tos3("slicing is supported by arrays and strings only"));
        };

        is_slice = 1;

        compiler__Parser_next(p);

        compiler__Parser_gen(p, tos3(","));

        if (p->tok != compiler__compiler__TokenKind_rsbr) {

          compiler__Parser_check_types(p, compiler__Parser_expression(p),
                                       tos3("int"));

          compiler__Parser_gen(p, tos3(", false"));

        } else {

          compiler__Parser_gen(p, tos3("-1, true"));
        };
      };

    } else {

      compiler__Type T = compiler__Table_find_type(
          &/* ? */ *p->table, compiler__Parser_expression(p));

      if (is_map && string_ne(T.parent, tos3("string"))) {

        compiler__Parser_check_types(p, T.name, tos3("string"));
      };
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

    if (close_bracket) {

      compiler__Parser_gen(p,
                           _STR("]/*r%.*s %d*/", typ.len, typ.str, v.is_mut));
    };

    p->expr_var = v;
  };

  if (is_variadic_arg) {

    if (is_indexer) {

      string l = string_trim_space(p->cgen->cur_line);

      string index_val =
          string_trim_space(string_right(l, string_last_index(l, tos3(" "))));

      compiler__CGen_resetln(p->cgen, string_substr2(l, 0, fn_ph, false));

      _PUSH(
          &p->table->varg_access,
          (/*typ = array_compiler__VargAccess   tmp_typ=compiler__VargAccess*/ (
              compiler__VargAccess){.fn_name = p->cur_fn.name,
                                    .tok_idx = index_error_tok_pos,
                                    .index = v_string_int(index_val)}),
          tmp111, compiler__VargAccess);

      compiler__CGen_set_placeholder(p->cgen, fn_ph,
                                     _STR("%.*s->args[%.*s]", v.name.len,
                                          v.name.str, index_val.len,
                                          index_val.str));

      return typ;
    };
  };

  if ((p->tok == compiler__compiler__TokenKind_assign && !p->is_sql) ||
      compiler__TokenKind_is_assign(p->tok)) {

    if (is_indexer && is_str && !p->builtin_mod) {

      compiler__Parser_error(p, tos3("strings are immutable"));
    };

    p->assigned_type = typ;

    p->expected_type = typ;

    int assign_pos = p->cgen->cur_line.len;

    bool is_cao = p->tok != compiler__compiler__TokenKind_assign;

    compiler__Parser_assign_statement(p, v, fn_ph,
                                      is_indexer && (is_map || is_arr));

    if (is_indexer && (is_map || is_arr)) {

      compiler__Parser_gen_array_set(p, typ, is_ptr, is_map, fn_ph, assign_pos,
                                     is_cao);
    };

    return typ;

  } else if ((is_map || is_arr || (is_str && !p->builtin_mod)) && is_indexer) {

    compiler__Parser_index_get(p, typ, fn_ph,
                               (compiler__IndexConfig){
                                   .is_arr = is_arr,
                                   .is_map = is_map,
                                   .is_ptr = is_ptr,
                                   .is_str = is_str,
                                   .is_slice = is_slice,
                                   .is_arr0 = 0,
                               });
  };

  return typ;
}
bool compiler__Parser_fileis(compiler__Parser *p, string s) {

  return string_contains(p->scanner->file_path, s);
}
string compiler__Parser_indot_expr(compiler__Parser *p) {

  int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = compiler__Parser_term(p);

  if (p->tok == compiler__compiler__TokenKind_dot) {

    while (p->tok == compiler__compiler__TokenKind_dot) {

      typ = compiler__Parser_dot(p, typ, ph);
    };
  };

  if (p->tok == compiler__compiler__TokenKind_key_in) {

    ;

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_in);

    p->expected_type = typ;

    if (p->tok == compiler__compiler__TokenKind_lsbr) {

      compiler__Parser_in_optimization(p, typ, ph);

      return tos3("bool");
    };

    ;

    compiler__Parser_gen(p, tos3("), "));

    string arr_typ = compiler__Parser_expression(p);

    bool is_map = string_starts_with(arr_typ, tos3("map_"));

    if (!string_starts_with(arr_typ, tos3("array_")) && !is_map) {

      compiler__Parser_error(p, tos3("`in` requires an array/map"));
    };

    compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, arr_typ);

    if (!is_map && !compiler__Type_has_method(&/* ? */ T, tos3("contains"))) {

      compiler__Parser_error(
          p, _STR("%.*s has no method `contains`", arr_typ.len, arr_typ.str));
    };

    if (is_map) {

      compiler__CGen_set_placeholder(p->cgen, ph, tos3("(_IN_MAP( ("));

    } else {

      compiler__CGen_set_placeholder(p->cgen, ph,
                                     _STR("(_IN(%.*s, (", typ.len, typ.str));
    };

    compiler__Parser_gen(p, tos3("))"));

    return tos3("bool");
  };

  return typ;
}
string compiler__Parser_assoc(compiler__Parser *p) {

  compiler__Parser_next(p);

  string name = compiler__Parser_check_name(p);

  Option_compiler__Var tmp112 = compiler__Parser_find_var(&/* ? */ *p, name);
  compiler__Var var;
  if (!tmp112.ok) {
    string err = tmp112.error;
    int errcode = tmp112.ecode;

    compiler__Parser_error(p,
                           _STR("unknown variable `%.*s`", name.len, name.str));

    v_exit(1);
  }
  var = *(compiler__Var *)tmp112.data;
  ;

  compiler__Parser_mark_var_used(p, var);

  compiler__Parser_check(p, compiler__compiler__TokenKind_pipe);

  compiler__Parser_gen(p, _STR("(%.*s){", var.typ.len, var.typ.str));

  array_string fields = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (p->tok != compiler__compiler__TokenKind_rcbr) {

    string field = compiler__Parser_check_name(p);

    _PUSH(&fields, (/*typ = array_string   tmp_typ=string*/ field), tmp113,
          string);

    compiler__Parser_gen(p, _STR(".%.*s = ", field.len, field.str));

    compiler__Parser_check(p, compiler__compiler__TokenKind_colon);

    compiler__Parser_bool_expression(p);

    compiler__Parser_gen(p, tos3(","));

    if (p->tok != compiler__compiler__TokenKind_rcbr) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
    };
  };

  compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, var.typ);

  array_compiler__Var tmp114 = T.fields;
  for (int tmp115 = 0; tmp115 < tmp114.len; tmp115++) {
    compiler__Var ffield = ((compiler__Var *)tmp114.data)[tmp115];

    string f = ffield.name;

    if ((_IN(string, (f), fields))) {

      continue;
    };

    compiler__Parser_gen(p, _STR(".%.*s = %.*s . %.*s,", f.len, f.str, name.len,
                                 name.str, f.len, f.str));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

  compiler__Parser_gen(p, tos3("}"));

  return var.typ;
}
void compiler__Parser_char_expr(compiler__Parser *p) {

  compiler__Parser_gen(p, _STR("\'%.*s\'", p->lit.len, p->lit.str));

  compiler__Parser_next(p);
}
string compiler__format_str(string _str) {

  string str = string_replace(_str, tos3("\""), tos3("\\\""));

  str = string_replace(str, tos3("\r\n"), tos3("\\n"));

  str = string_replace(str, tos3("\n"), tos3("\\n"));

  return str;
}
void compiler__Parser_string_expr(compiler__Parser *p) {

  bool is_raw = p->tok == compiler__compiler__TokenKind_name &&
                string_eq(p->lit, tos3("r"));

  if (is_raw) {

    compiler__Parser_next(p);
  };

  string str = p->lit;

  if (compiler__Parser_peek(&/* ? */ *p) !=
          compiler__compiler__TokenKind_dollar ||
      is_raw) {

    ;

    string f =
        (is_raw) ? (compiler__cescaped_path(str)) : (compiler__format_str(str));

    if ((p->calling_c && compiler__Parser_peek(&/* ? */ *p) !=
                             compiler__compiler__TokenKind_dot) ||
        (p->pref->translated && string_eq(p->mod, tos3("main")))) {

      compiler__Parser_gen(p, _STR("\"%.*s\"", f.len, f.str));

    } else if (p->is_sql) {

      compiler__Parser_gen(p, _STR("'%.*s'", str.len, str.str));

    } else if (p->is_js) {

      compiler__Parser_gen(p, _STR("tos(\"%.*s\")", f.len, f.str));

    } else {

      compiler__Parser_gen(p, _STR("tos3(\"%.*s\")", f.len, f.str));
    };

    compiler__Parser_next(p);

    return;
  };

#ifdef _VJS

  compiler__Parser_error(
      p, tos3("js backend does not support string formatting yet"));

#endif
  ;

  p->is_alloc = 1;

  string args = tos3("\"");

  string format = tos3("\"");

  ;

  bool complex_inter = 0;

  while (p->tok == compiler__compiler__TokenKind_str) {

    ;

    p->lit = string_replace(p->lit, tos3("%"), tos3("%%"));

    format = string_add(format, compiler__format_str(p->lit));

    compiler__Parser_next(p);

    if (p->tok != compiler__compiler__TokenKind_dollar) {

      continue;
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_dollar);

    if (compiler__Parser_peek(&/* ? */ *p) !=
        compiler__compiler__TokenKind_str) {

      ;

      complex_inter = 1;
    };

    compiler__CGen_start_tmp(p->cgen);

    string typ = compiler__Parser_bool_expression(p);

    string val = compiler__CGen_end_tmp(p->cgen);

    val = string_trim_space(val);

    args = string_add(args, _STR(", %.*s", val.len, val.str));

    if (string_eq(typ, tos3("string"))) {

      args = string_add(args, _STR(".len, %.*s.str", val.len, val.str));
    };

    if (string_eq(typ, tos3("ustring"))) {

      args = string_add(args, _STR(".len, %.*s.s.str", val.len, val.str));
    };

    if (string_eq(typ, tos3("bool"))) {
    };

    bool custom = p->tok == compiler__compiler__TokenKind_colon;

    if (custom) {

      string cformat = tos3("");

      compiler__Parser_next(p);

      if (p->tok == compiler__compiler__TokenKind_dot) {

        cformat = string_add(cformat, tos3("."));

        compiler__Parser_next(p);
      };

      if (p->tok == compiler__compiler__TokenKind_minus) {

        cformat = string_add(cformat, tos3("-"));

        compiler__Parser_next(p);
      };

      cformat = string_add(cformat, p->lit);

      compiler__Parser_next(p);

      string fspec = p->lit;

      cformat = string_add(cformat, fspec);

      if (string_eq(fspec, tos3("s"))) {

        if (string_ne(typ, tos3("string"))) {

          compiler__Parser_error(
              p, _STR("only V strings can be formatted with a :%.*s format, "
                      "but you have given \"%.*s\", which has type %.*s",
                      cformat.len, cformat.str, val.len, val.str, typ.len,
                      typ.str));
        };

        args = string_add(
            string_all_before_last(args, _STR("%.*s.len, %.*s.str", val.len,
                                              val.str, val.len, val.str)),
            _STR("%.*s.str", val.len, val.str));
      };

      format = string_add(format, _STR("%%%.*s", cformat.len, cformat.str));

      compiler__Parser_next(p);

    } else {

      string f = compiler__Parser_typ_to_fmt(p, typ, 0);

      if (string_eq(f, tos3(""))) {

        bool is_array = string_starts_with(typ, tos3("array_"));

        compiler__Type typ2 =
            compiler__Table_find_type(&/* ? */ *p->table, typ);

        bool has_str_method = compiler__Table_type_has_method(
            &/* ? */ *p->table,
            &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ typ2,
            tos3("str"));

        if (is_array || has_str_method) {

          if (is_array && !has_str_method) {

            compiler__Parser_gen_array_str(p, typ2);
          };

          string tmp_var = compiler__Parser_get_tmp(p);

          compiler__CGen_insert_before(
              p->cgen, _STR("string %.*s = %.*s_str(%.*s);", tmp_var.len,
                            tmp_var.str, typ.len, typ.str, val.len, val.str));

          args = string_add(string_all_before_last(args, val),
                            _STR("%.*s.len, %.*s.str", tmp_var.len, tmp_var.str,
                                 tmp_var.len, tmp_var.str));

          format = string_add(format, tos3("%.*s "));

        } else {

          compiler__Parser_error(
              p, _STR("unhandled sprintf format \"%.*s\" ", typ.len, typ.str));
        };
      };

      format = string_add(format, f);
    };
  };

  if (complex_inter) {

    ;
  };

  ;

  if (p->cgen->nogen) {

    return;
  };

#ifndef _WIN32

  string cur_line = string_trim_space(p->cgen->cur_line);

  if (string_eq(cur_line, tos3("println (")) &&
      p->tok != compiler__compiler__TokenKind_plus) {

    compiler__CGen_resetln(
        p->cgen, string_replace(cur_line, tos3("println ("), tos3("printf(")));

    compiler__Parser_gen(
        p, _STR("%.*s\\n%.*s", format.len, format.str, args.len, args.str));

    return;
  };

#endif
  ;

  if (p->tok == compiler__compiler__TokenKind_not) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_not);

    compiler__Parser_gen(p, _STR("_STR_TMP(%.*s%.*s)", format.len, format.str,
                                 args.len, args.str));

  } else {

    compiler__Parser_gen(
        p, _STR("_STR(%.*s%.*s)", format.len, format.str, args.len, args.str));
  };
}
string compiler__Parser_map_init(compiler__Parser *p) {

  string keys_gen = tos3("");

  string vals_gen = tos3("");

  string val_type = tos3("");

  if (p->tok == compiler__compiler__TokenKind_lcbr) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    int i = 0;

    while (1) {

      string key = p->lit;

      keys_gen =
          string_add(keys_gen, _STR("tos3(\"%.*s\"), ", key.len, key.str));

      compiler__Parser_check(p, compiler__compiler__TokenKind_str);

      compiler__Parser_check(p, compiler__compiler__TokenKind_colon);

      compiler__CGen_start_tmp(p->cgen);

      string t = compiler__Parser_bool_expression(p);

      if (i == 0) {

        val_type = t;
      };

      i++;

      if (string_ne(val_type, t)) {

        if (!compiler__Parser_check_types_no_throw(p, val_type, t)) {

          compiler__Parser_error(
              p, _STR("bad map element type `%.*s` instead of `%.*s`",
                      val_type.len, val_type.str, t.len, t.str));
        };
      };

      string val_expr = compiler__CGen_end_tmp(p->cgen);

      vals_gen =
          string_add(vals_gen, _STR("%.*s, ", val_expr.len, val_expr.str));

      if (p->tok == compiler__compiler__TokenKind_rcbr) {

        compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

        break;
      };

      if (p->tok == compiler__compiler__TokenKind_comma) {

        compiler__Parser_check(p, compiler__compiler__TokenKind_comma);
      };
    };

    compiler__Parser_gen(
        p, string_add(_STR("new_map_init(%d, sizeof(%.*s), ", i, val_type.len,
                           val_type.str),
                      _STR("(string[%d]){ %.*s }, (%.*s [%d]){ %.*s } )", i,
                           keys_gen.len, keys_gen.str, val_type.len,
                           val_type.str, i, vals_gen.len, vals_gen.str)));

    string typ = _STR("map_%.*s", val_type.len, val_type.str);

    compiler__Parser_register_map(p, typ);

    return typ;
  };

  compiler__Parser_next(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

  string key_type = compiler__Parser_check_name(p);

  if (string_ne(key_type, tos3("string"))) {

    compiler__Parser_error(p, tos3("only string key maps allowed for now"));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

  val_type = compiler__Parser_get_type(p);

  string typ = _STR("map_%.*s", val_type.len, val_type.str);

  compiler__Parser_register_map(p, typ);

  compiler__Parser_gen(
      p, _STR("new_map(1, sizeof(%.*s))", val_type.len, val_type.str));

  if (p->tok == compiler__compiler__TokenKind_lcbr) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

    println(string_add(_STR("warning: %.*s:%d ", p->file_name.len,
                            p->file_name.str, p->scanner->line_nr),
                       tos3("initializaing maps no longer requires `{}`")));
  };

  return typ;
}
string compiler__Parser_array_init(compiler__Parser *p) {

  p->is_alloc = 1;

  compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

  bool is_integer = p->tok == compiler__compiler__TokenKind_number;

  bool is_const_len = 0;

  if (p->tok == compiler__compiler__TokenKind_name && !p->inside_const) {

    string const_name = compiler__Parser_prepend_mod(&/* ? */ *p, p->lit);

    if (compiler__Table_known_const(&/* ? */ *p->table, const_name)) {

      Option_compiler__Var tmp116 =
          compiler__Table_find_const(&/* ? */ *p->table, const_name);
      compiler__Var c;
      if (!tmp116.ok) {
        string err = tmp116.error;
        int errcode = tmp116.ecode;

        v_exit(1);
      }
      c = *(compiler__Var *)tmp116.data;
      ;

      if (string_eq(c.typ, tos3("int")) &&
          compiler__Parser_peek(&/* ? */ *p) ==
              compiler__compiler__TokenKind_rsbr) {

        is_integer = 1;

        is_const_len = 1;

      } else {

        compiler__Parser_error(p, _STR("bad fixed size array const `%.*s`",
                                       p->lit.len, p->lit.str));
      };
    };
  };

  string lit = p->lit;

  string typ = tos3("");

  int new_arr_ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

  int i = 0;

  int pos = p->cgen->cur_line.len;

  while (p->tok != compiler__compiler__TokenKind_rsbr) {

    string val_typ = compiler__Parser_bool_expression(p);

    if (i == 0) {

      typ = val_typ;

      if (is_integer && p->tok == compiler__compiler__TokenKind_rsbr &&
          compiler__Parser_peek(&/* ? */ *p) ==
              compiler__compiler__TokenKind_name &&
          compiler__Parser_cur_tok(&/* ? */ *p).line_nr ==
              compiler__Parser_peek_token(&/* ? */ *p).line_nr) {

        if (compiler__Parser_cur_tok(&/* ? */ *p).col +
                compiler__Parser_peek_token(&/* ? */ *p).lit.len ==
            compiler__Parser_peek_token(&/* ? */ *p).col) {

          compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

          string array_elem_typ = compiler__Parser_get_type(p);

          if (!compiler__Table_known_type(&/* ? */ *p->table, array_elem_typ)) {

            compiler__Parser_error(p,
                                   _STR("bad type `%.*s`", array_elem_typ.len,
                                        array_elem_typ.str));
          };

          compiler__CGen_resetln(p->cgen, tos3(""));

          p->is_alloc = 0;

          if (is_const_len) {

            return _STR("[%.*s__%.*s]%.*s", compiler__mod_gen_name(p->mod).len,
                        compiler__mod_gen_name(p->mod).str, lit.len, lit.str,
                        array_elem_typ.len, array_elem_typ.str);
          };

          return _STR("[%.*s]%.*s", lit.len, lit.str, array_elem_typ.len,
                      array_elem_typ.str);

        } else {

          compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

          typ = compiler__Parser_get_type(p);

          compiler__Parser_error(
              p, _STR("no space allowed between [%.*s] and %.*s", lit.len,
                      lit.str, typ.len, typ.str));
        };
      };
    };

    if (string_ne(val_typ, typ)) {

      if (!compiler__Parser_check_types_no_throw(p, val_typ, typ)) {

        compiler__Parser_error(
            p, _STR("bad array element type `%.*s` instead of `%.*s`",
                    val_typ.len, val_typ.str, typ.len, typ.str));
      };
    };

    if (p->tok != compiler__compiler__TokenKind_rsbr &&
        p->tok != compiler__compiler__TokenKind_semicolon) {

      compiler__Parser_gen(p, tos3(", "));

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

      ;
    };

    i++;

    if (i == 1 && p->tok == compiler__compiler__TokenKind_semicolon) {

      compiler__Parser_warn(
          p,
          tos3(
              "`[0 ; len]` syntax was removed. Use `[0].repeat(len)` instead"));

      compiler__Parser_check_space(p, compiler__compiler__TokenKind_semicolon);

      string val = string_substr2(p->cgen->cur_line, pos, -1, true);

      compiler__CGen_resetln(p->cgen,
                             string_substr2(p->cgen->cur_line, 0, pos, false));

      compiler__Parser_gen(p, _STR("array_repeat_old(& (%.*s[]){ %.*s }, ",
                                   typ.len, typ.str, val.len, val.str));

      compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                   tos3("int"));

      compiler__Parser_gen(p, _STR(", sizeof(%.*s) )", typ.len, typ.str));

      compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

      return _STR("array_%.*s", typ.len, typ.str);
    };
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

  if (p->tok != compiler__compiler__TokenKind_name && i == 0) {

    compiler__Parser_error(p,
                           tos3("specify array type: `[]typ` instead of `[]`"));
  };

  if (p->tok == compiler__compiler__TokenKind_name && i == 0) {

    typ = compiler__Parser_get_type(p);
  };

  bool no_alloc = p->tok == compiler__compiler__TokenKind_not;

  if (no_alloc) {

    compiler__Parser_next(p);
  };

  bool is_fixed_size = p->tok == compiler__compiler__TokenKind_not;

  if (is_fixed_size) {

    compiler__Parser_next(p);

    compiler__Parser_gen(p, tos3(" }"));

    if (!compiler__Parser_first_pass(&/* ? */ *p)) {

      if (p->inside_const) {

        compiler__CGen_set_placeholder(p->cgen, new_arr_ph, tos3("{"));

      } else {

        compiler__CGen_set_placeholder(p->cgen, new_arr_ph,
                                       _STR("(%.*s[]) {", typ.len, typ.str));
      };
    };

    return _STR("[%d]%.*s", i, typ.len, typ.str);
  };

  compiler__Parser_gen_array_init(p, typ, no_alloc, new_arr_ph, i);

  typ = _STR("array_%.*s", typ.len, typ.str);

  compiler__Parser_register_array(p, typ);

  return typ;
}
string compiler__Parser_get_tmp(compiler__Parser *p) {

  p->tmp_cnt++;

  return _STR("tmp%d", p->tmp_cnt);
}
int compiler__Parser_get_tmp_counter(compiler__Parser *p) {

  p->tmp_cnt++;

  return p->tmp_cnt;
}
_V_MulRet_string_V_string compiler__Parser_tmp_expr(compiler__Parser *p) {

  compiler__CGen_start_tmp(p->cgen);

  string typ = compiler__Parser_bool_expression(p);

  string val = compiler__CGen_end_tmp(p->cgen);

  return (_V_MulRet_string_V_string){.var_0 = typ, .var_1 = val};
}
string compiler__Parser_if_st(compiler__Parser *p, bool is_expr,
                              int elif_depth) {

  if (is_expr) {

    p->inside_if_expr = 1;

    compiler__Parser_gen(p, tos3("("));

  } else {

    compiler__Parser_gen(p, tos3("if ("));

    ;
  };

  compiler__Parser_next(p);

  if (p->tok == compiler__compiler__TokenKind_name &&
      compiler__Parser_peek(&/* ? */ *p) ==
          compiler__compiler__TokenKind_decl_assign) {

    compiler__Parser_check_not_reserved(p);

    string option_tmp = compiler__Parser_get_tmp(p);

    string var_name = p->lit;

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_decl_assign);

    p->is_var_decl = 1;

    _V_MulRet_string_V_string _V_mret_option_type_expr =
        compiler__Parser_tmp_expr(p);
    string option_type = _V_mret_option_type_expr.var_0;
    string expr = _V_mret_option_type_expr.var_1;

    p->is_var_decl = 0;

    string typ = string_substr2(option_type, 7, -1, true);

    compiler__CGen_insert_before(
        p->cgen, _STR("%.*s %.*s = %.*s; ", option_type.len, option_type.str,
                      option_tmp.len, option_tmp.str, expr.len, expr.str));

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    compiler__Parser_genln(p, string_add(option_tmp, tos3(".ok) {")));

    compiler__Parser_genln(p, _STR("%.*s %.*s = *(%.*s*) %.*s . data;", typ.len,
                                   typ.str, var_name.len, var_name.str, typ.len,
                                   typ.str, option_tmp.len, option_tmp.str));

    compiler__Parser_register_var(
        p, (compiler__Var){.name = var_name,
                           .typ = typ,
                           .is_mut = 0,
                           .idx = 0,
                           .is_arg = 0,
                           .is_const = 0,
                           .args = new_array(0, 1, sizeof(compiler__Var)),
                           .attr = tos3(""),
                           .is_alloc = 0,
                           .is_returned = 0,
                           .ptr = 0,
                           .ref = 0,
                           .parent_fn = tos3(""),
                           .mod = tos3(""),
                           .is_global = 0,
                           .is_used = 0,
                           .is_changed = 0,
                           .scope_level = 0,
                           .is_c = 0,
                           .is_moved = 0,
                           .line_nr = 0,
                           .token_idx = 0,
                           .is_for_var = 0,
                           .is_public = 0});

    compiler__Parser_statements(p);

    return tos3("void");

  } else {

    compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                 tos3("bool"));
  };

  if (is_expr) {

    compiler__Parser_gen(p, tos3(") ? ("));

  } else {

    compiler__Parser_genln(p, tos3(") {"));
  };

  ;

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  string typ = tos3("");

  if (p->tok == compiler__compiler__TokenKind_key_if && p->inside_if_expr) {

    typ = compiler__Parser_factor(p);

    compiler__Parser_next(p);

  } else {

    typ = compiler__Parser_statements(p);
  };

  bool if_returns = p->returns;

  p->returns = 0;

  if (p->tok == compiler__compiler__TokenKind_key_else) {

    ;

    compiler__Parser_check(p, compiler__compiler__TokenKind_key_else);

    ;

    if (p->tok == compiler__compiler__TokenKind_key_if) {

      if (is_expr) {

        compiler__Parser_gen(p, tos3(") : ("));

        string nested = compiler__Parser_if_st(p, is_expr, elif_depth + 1);

        bool nested_returns = p->returns;

        p->returns = if_returns && nested_returns;

        return nested;

      } else {

        compiler__Parser_gen(p, tos3(" else "));

        string nested = compiler__Parser_if_st(p, is_expr, 0);

        bool nested_returns = p->returns;

        p->returns = if_returns && nested_returns;

        return nested;
      };
    };

    if (is_expr) {

      compiler__Parser_gen(p, tos3(") : ("));

    } else {

      compiler__Parser_genln(p, tos3(" else { "));
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

    string first_typ = typ;

    typ = compiler__Parser_statements(p);

    p->inside_if_expr = 0;

    if (is_expr) {

      compiler__Parser_check_types(p, first_typ, typ);

      compiler__Parser_gen(p, strings__repeat(')', elif_depth + 1));
    };

    bool else_returns = p->returns;

    p->returns = if_returns && else_returns;

    return typ;
  };

  p->inside_if_expr = 0;

  if (compiler__Parser_fileis(&/* ? */ *p, tos3("test_test"))) {

    printf("if ret typ=\"%.*s\" line=%d\n", typ.len, typ.str,
           p->scanner->line_nr);
  };

  return typ;
}
void compiler__Parser_assert_statement(compiler__Parser *p) {

  if (compiler__Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_assert);

  ;

  string tmp = compiler__Parser_get_tmp(p);

  compiler__Parser_gen(p, _STR("bool %.*s = ", tmp.len, tmp.str));

  compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                               tos3("bool"));

  int nline = p->scanner->line_nr;

  string filename = compiler__cescaped_path(p->file_path);

  string cfname = string_replace(p->cur_fn.name, tos3("main__"), tos3(""));

  string sourceline = string_replace(
      compiler__Scanner_line(*p->scanner, nline - 1), tos3("\""), tos3("\'"));

  if (!p->pref->is_test) {

    compiler__Parser_genln(
        p, _STR(";\n\n/// sline: \"%.*s\"\nif (!%.*s) {\n	"
                "g_test_fails++;\n	eprintln(tos3(\"%.*s:%d: FAILED: "
                "%.*s()\"));\n	eprintln(tos3(\"Source: %.*s\"));\n    "
                "v_panic(tos3(\"An assertion failed.\"));\n	return;\n} "
                "else {\n	g_test_oks++;\n}\n",
                sourceline.len, sourceline.str, tmp.len, tmp.str, filename.len,
                filename.str, p->scanner->line_nr, cfname.len, cfname.str,
                sourceline.len, sourceline.str));

    return;
  };

  compiler__Parser_genln(
      p, _STR(";\n\nif (!%.*s) {\n  g_test_fails++;\n  "
              "main__cb_assertion_failed(\n     tos3(\"%.*s\"),\n     %d,\n    "
              " tos3(\"%.*s\"),\n     tos3(\"%.*s()\")\n  );\n  return;\n  // "
              "TODO\n  // Maybe print all vars in a test function if it "
              "fails?\n} else {\n  g_test_oks++;\n  main__cb_assertion_ok(\n   "
              "  tos3(\"%.*s\"),\n     %d,\n     tos3(\"%.*s\"),\n     "
              "tos3(\"%.*s()\")\n  );\n}\n\n",
              tmp.len, tmp.str, filename.len, filename.str, p->scanner->line_nr,
              sourceline.len, sourceline.str, p->cur_fn.name.len,
              p->cur_fn.name.str, filename.len, filename.str,
              p->scanner->line_nr, sourceline.len, sourceline.str,
              p->cur_fn.name.len, p->cur_fn.name.str));
}
void compiler__Parser_return_st(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_return);

  ;

  string deferred_text = compiler__Parser_get_deferred_text(*p);

  bool fn_returns = string_ne(p->cur_fn.typ, tos3("void"));

  if (fn_returns) {

    if (p->tok == compiler__compiler__TokenKind_rcbr) {

      compiler__Parser_error(p, _STR("`%.*s` needs to return `%.*s`",
                                     p->cur_fn.name.len, p->cur_fn.name.str,
                                     p->cur_fn.typ.len, p->cur_fn.typ.str));
    };

    int ph = compiler__CGen_add_placeholder(&/* ? */ *p->cgen);

    p->inside_return_expr = 1;

    bool is_none = p->tok == compiler__compiler__TokenKind_key_none;

    p->expected_type = p->cur_fn.typ;

    string expr_type = compiler__Parser_bool_expression(p);

    array_string types = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    array_string mr_values = new_array_from_c_array(
        1, 1, sizeof(string),
        EMPTY_ARRAY_OF_ELEMS(string, 1){string_trim_space(
            string_substr2(p->cgen->cur_line, ph, -1, true))});

    _PUSH(&types, (/*typ = array_string   tmp_typ=string*/ expr_type), tmp125,
          string);

    while (p->tok == compiler__compiler__TokenKind_comma) {

      compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

      compiler__CGen_start_tmp(p->cgen);

      _PUSH(&types,
            (/*typ = array_string   tmp_typ=string*/
             compiler__Parser_bool_expression(p)),
            tmp126, string);

      _PUSH(&mr_values,
            (/*typ = array_string   tmp_typ=string*/ string_trim_space(
                compiler__CGen_end_tmp(p->cgen))),
            tmp127, string);
    };

    string cur_fn_typ_chk = p->cur_fn.typ;

    if (types.len > 1) {

      expr_type = array_string_join(types, tos3(","));

      cur_fn_typ_chk = string_replace(
          string_replace(
              string_replace(cur_fn_typ_chk, tos3("_V_MulRet_"), tos3("")),
              tos3("_PTR_"), tos3("*")),
          tos3("_V_"), tos3(","));

      string ret_fields = tos3("");

      array_string tmp128 = mr_values;
      for (int ret_val_idx = 0; ret_val_idx < tmp128.len; ret_val_idx++) {
        string ret_val = ((string *)tmp128.data)[ret_val_idx];

        if (ret_val_idx > 0) {

          ret_fields = string_add(ret_fields, tos3(","));
        };

        ret_fields = string_add(ret_fields, _STR(".var_%d=%.*s", ret_val_idx,
                                                 ret_val.len, ret_val.str));
      };

      compiler__CGen_resetln(p->cgen, _STR("(%.*s){%.*s}", p->cur_fn.typ.len,
                                           p->cur_fn.typ.str, ret_fields.len,
                                           ret_fields.str));
    };

    p->inside_return_expr = 0;

    if (string_ends_with(p->cur_fn.typ, expr_type) && !is_none &&
        string_starts_with(p->cur_fn.typ, tos3("Option_"))) {

      string tmp = compiler__Parser_get_tmp(p);

      string ret = string_substr2(p->cgen->cur_line, ph, -1, true);

      string typ = string_replace(expr_type, tos3("Option_"), tos3(""));

      compiler__CGen_resetln(
          p->cgen, _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);", expr_type.len,
                        expr_type.str, tmp.len, tmp.str, expr_type.len,
                        expr_type.str, ret.len, ret.str));

      compiler__Parser_genln(p, deferred_text);

      compiler__Parser_gen(p, _STR("return opt_ok(&%.*s, sizeof(%.*s))",
                                   tmp.len, tmp.str, typ.len, typ.str));

    } else {

      string ret = string_substr2(p->cgen->cur_line, ph, -1, true);

      if (string_eq(deferred_text, tos3("")) ||
          string_eq(expr_type, tos3("void*"))) {

        if (string_eq(expr_type,
                      _STR("%.*s*", p->cur_fn.typ.len, p->cur_fn.typ.str))) {

          compiler__CGen_resetln(p->cgen,
                                 _STR("return *%.*s", ret.len, ret.str));

        } else {

          compiler__CGen_resetln(p->cgen,
                                 _STR("return %.*s", ret.len, ret.str));
        };

      } else {

        string tmp = compiler__Parser_get_tmp(p);

        compiler__CGen_resetln(
            p->cgen, _STR("%.*s %.*s = %.*s;\n", expr_type.len, expr_type.str,
                          tmp.len, tmp.str, ret.len, ret.str));

        compiler__Parser_genln(p, deferred_text);

        compiler__Parser_genln(p, _STR("return %.*s;", tmp.len, tmp.str));
      };
    };

    compiler__Parser_check_types(p, expr_type, cur_fn_typ_chk);

  } else {

    if (!p->is_vweb && (p->tok == compiler__compiler__TokenKind_name ||
                        p->tok == compiler__compiler__TokenKind_number ||
                        p->tok == compiler__compiler__TokenKind_str)) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("function `%.*s` should not return a value", p->cur_fn.name.len,
               p->cur_fn.name.str),
          p->cur_fn.fn_name_token_idx);
    };

    compiler__Parser_genln(p, deferred_text);

    if (string_eq(p->cur_fn.name, tos3("main"))) {

      compiler__Parser_gen(p, tos3("return 0"));

    } else {

      compiler__Parser_gen(p, tos3("return"));
    };
  };

  p->returns = 1;
}
string compiler__Parser_get_deferred_text(compiler__Parser p) {

  string deferred_text = tos3("");

  array_string tmp133 = p.cur_fn.defer_text;
  for (int tmp134 = 0; tmp134 < tmp133.len; tmp134++) {
    string text = ((string *)tmp133.data)[tmp134];

    if (string_ne(text, tos3(""))) {

      deferred_text = string_add(text, deferred_text);
    };
  };

  return deferred_text;
}
string compiler__prepend_mod(string mod, string name) {

  return _STR("%.*s__%.*s", mod.len, mod.str, name.len, name.str);
}
string compiler__Parser_prepend_mod(compiler__Parser *p, string name) {

  return compiler__prepend_mod(compiler__mod_gen_name(p->mod), name);
}
void compiler__Parser_go_statement(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_go);

  int gotoken_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

  if (compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_dot) {

    string var_name = p->lit;

    Option_compiler__Var tmp135 =
        compiler__Parser_find_var(&/* ? */ *p, var_name);
    compiler__Var v;
    if (!tmp135.ok) {
      string err = tmp135.error;
      int errcode = tmp135.ecode;

      return;
    }
    v = *(compiler__Var *)tmp135.data;
    ;

    compiler__Parser_mark_var_used(p, v);

    gotoken_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    compiler__Type typ = compiler__Table_find_type(&/* ? */ *p->table, v.typ);

    Option_compiler__Fn tmp136 = compiler__Table_find_method(
        &/* ? */ *p->table,
        &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ typ, p->lit);
    compiler__Fn method;
    if (!tmp136.ok) {
      string err = tmp136.error;
      int errcode = tmp136.ecode;

      compiler__Parser_error_with_token_index(
          p, _STR("go method missing %.*s", var_name.len, var_name.str),
          gotoken_idx);

      return;
    }
    method = *(compiler__Fn *)tmp136.data;
    ;

    compiler__Parser_async_fn_call(p, method, 0, var_name, v.typ);

  } else {

    string f_name = p->lit;

    Option_compiler__Fn tmp137 = compiler__Table_find_fn(
        &/* ? */ *p->table, compiler__Parser_prepend_mod(&/* ? */ *p, f_name));
    compiler__Fn f;
    if (!tmp137.ok) {
      string err = tmp137.error;
      int errcode = tmp137.ecode;

      println(compiler__Table_debug_fns(&/* ? */ *p->table));

      compiler__Parser_error_with_token_index(
          p, _STR("can not find function %.*s", f_name.len, f_name.str),
          gotoken_idx);

      return;
    }
    f = *(compiler__Fn *)tmp137.data;
    ;

    if (string_eq(f.name, tos3("println")) ||
        string_eq(f.name, tos3("print"))) {

      compiler__Parser_error_with_token_index(
          p, tos3("`go` cannot be used with `println`"), gotoken_idx);
    };

    compiler__Parser_async_fn_call(p, f, 0, tos3(""), tos3(""));
  };
}
string compiler__Parser_js_decode(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_name);

  compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

  string op = compiler__Parser_check_name(p);

  int op_token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

  if (string_eq(op, tos3("decode"))) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    string typ = compiler__Parser_get_type(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_comma);

    compiler__CGen_start_tmp(p->cgen);

    compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                 tos3("string"));

    string expr = compiler__CGen_end_tmp(p->cgen);

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    string tmp = compiler__Parser_get_tmp(p);

    string cjson_tmp = compiler__Parser_get_tmp(p);

    string decl = _STR("%.*s %.*s; ", typ.len, typ.str, tmp.len, tmp.str);

    compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, typ);

    array_compiler__Var tmp138 = T.fields;
    for (int tmp139 = 0; tmp139 < tmp138.len; tmp139++) {
      compiler__Var field = ((compiler__Var *)tmp138.data)[tmp139];

      string def_val = compiler__type_default(field.typ);

      if (string_ne(def_val, tos3(""))) {

        decl = string_add(decl, _STR("%.*s . %.*s = OPTION_CAST(%.*s) %.*s;\n",
                                     tmp.len, tmp.str, field.name.len,
                                     field.name.str, field.typ.len,
                                     field.typ.str, def_val.len, def_val.str));
      };
    };

    compiler__Parser_gen_json_for_type(p, T);

    decl = string_add(decl,
                      _STR("cJSON* %.*s = json__json_parse(%.*s);",
                           cjson_tmp.len, cjson_tmp.str, expr.len, expr.str));

    compiler__CGen_insert_before(p->cgen, decl);

    compiler__Parser_gen(
        p, _STR("json__jsdecode_%.*s(%.*s, &%.*s); cJSON_Delete(%.*s);",
                typ.len, typ.str, cjson_tmp.len, cjson_tmp.str, tmp.len,
                tmp.str, cjson_tmp.len, cjson_tmp.str));

    string opt_type = _STR("Option_%.*s", typ.len, typ.str);

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "typedef Option %.*s;", opt_type.len, opt_type.str)),
          tmp140, string);

    compiler__Table_register_builtin(p->table, opt_type);

    return opt_type;

  } else if (string_eq(op, tos3("encode"))) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

    compiler__CGen_start_tmp(p->cgen);

    string typ = compiler__Parser_bool_expression(p);

    compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, typ);

    compiler__Parser_gen_json_for_type(p, T);

    string expr = compiler__CGen_end_tmp(p->cgen);

    compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

    compiler__Parser_gen(p, _STR("json__json_print(json__jsencode_%.*s(%.*s))",
                                 typ.len, typ.str, expr.len, expr.str));

    return tos3("string");

  } else {

    compiler__Parser_error_with_token_index(
        p, _STR("bad json op \"%.*s\"", op.len, op.str), op_token_idx);
  };

  return tos3("");
}
void compiler__Parser_attribute(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

  if (p->tok == compiler__compiler__TokenKind_key_if) {

    compiler__Parser_next(p);

    p->attr = string_add(tos3("if "), compiler__Parser_check_name(p));

  } else {

    p->attr = compiler__Parser_check_name(p);
  };

  int attr_token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

  if (p->tok == compiler__compiler__TokenKind_colon) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_colon);

    p->attr = string_add(string_add(p->attr, tos3(":")),
                         compiler__Parser_check_name(p));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

  if (p->tok == compiler__compiler__TokenKind_key_fn ||
      (p->tok == compiler__compiler__TokenKind_key_pub &&
       compiler__Parser_peek(&/* ? */ *p) ==
           compiler__compiler__TokenKind_key_fn)) {

    compiler__Parser_fn_decl(p);

    p->attr = tos3("");

    return;

  } else if (p->tok == compiler__compiler__TokenKind_key_struct) {

    compiler__Parser_struct_decl(p);

    p->attr = tos3("");

    return;
  };

  compiler__Parser_error_with_token_index(p, tos3("bad attribute usage"),
                                          attr_token_idx);
}
void compiler__Parser_defer_st(compiler__Parser *p) {

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_defer);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  int pos = p->cgen->lines.len;

  compiler__Parser_genln(p, tos3("{"));

  compiler__Parser_statements(p);

  *(string *)array_last(p->cur_fn.defer_text) =
      string_add(array_string_join(array_slice2(p->cgen->lines, pos, -1, true),
                                   tos3("\n")),
                 *(string *)array_last(p->cur_fn.defer_text));

  p->cgen->lines = array_slice2(p->cgen->lines, 0, pos, false);

  compiler__CGen_resetln(p->cgen, tos3(""));
}
void compiler__Parser_check_and_register_used_imported_type(compiler__Parser *p,
                                                            string typ_name) {

  int us_idx = string_index(typ_name, tos3("__"));

  if (us_idx != -1) {

    string arg_mod = string_substr2(typ_name, 0, us_idx, false);

    if (compiler__ImportTable_known_alias(&/* ? */ p->import_table, arg_mod)) {

      compiler__ImportTable_register_used_import(&/* ? */ p->import_table,
                                                 arg_mod);
    };
  };
}
void compiler__Parser_check_unused_imports(compiler__Parser *p) {

  if (p->is_vgen) {

    return;
  };

  string output = tos3("");

  map_string tmp147 = p->import_table.imports;
  array_string keys_tmp147 = map_keys(&tmp147);
  for (int l = 0; l < keys_tmp147.len; l++) {
    string alias = ((string *)keys_tmp147.data)[l];
    string mod = tos3("");
    map_get(tmp147, alias, &mod);

    if (!compiler__ImportTable_is_used_import(&/* ? */ p->import_table,
                                              alias)) {

      string mod_alias =
          (string_eq(alias, mod))
              ? (alias)
              : (_STR("%.*s (%.*s)", alias.len, alias.str, mod.len, mod.str));

      output =
          string_add(output, _STR("\n * %.*s", mod_alias.len, mod_alias.str));
    };
  };

  if (string_eq(output, tos3(""))) {

    return;
  };

  compiler__Parser_production_error_with_token_index(
      p,
      _STR("the following imports were never used: %.*s", output.len,
           output.str),
      0);
}
_V_MulRet_bool_V_string compiler__Parser_is_expr_fn_call(compiler__Parser *p,
                                                         int start_tok_idx) {

  string expr = compiler__Token_str(
      (*(compiler__Token *)array_get(p->tokens, start_tok_idx - 1)));

  bool is_fn_call =
      (*(compiler__Token *)array_get(p->tokens, start_tok_idx)).tok ==
      compiler__compiler__TokenKind_lpar;

  if (!is_fn_call) {

    int i = start_tok_idx;

    while (((*(compiler__Token *)array_get(p->tokens, i)).tok ==
                compiler__compiler__TokenKind_dot ||
            (*(compiler__Token *)array_get(p->tokens, i)).tok ==
                compiler__compiler__TokenKind_name) &&
           string_ne((*(compiler__Token *)array_get(p->tokens, i)).lit,
                     tos3("_")) &&
           i < p->tokens.len) {

      expr = string_add(
          expr,
          compiler__Token_str((*(compiler__Token *)array_get(p->tokens, i))));

      i++;
    };

    is_fn_call = (*(compiler__Token *)array_get(p->tokens, i)).tok ==
                 compiler__compiler__TokenKind_lpar;
  };

  return (_V_MulRet_bool_V_string){.var_0 = is_fn_call, .var_1 = expr};
}
compiler__Type compiler__Parser_get_type2(compiler__Parser *p) {

  bool mul = 0;

  int nr_muls = 0;

  string typ = tos3("");

  compiler__TypeCategory cat = compiler__compiler__TypeCategory_struct_;

  if (p->tok == compiler__compiler__TokenKind_key_fn) {

    compiler__Fn f =
        (compiler__Fn){.name = tos3("_"),
                       .mod = p->mod,
                       .args = new_array(0, 1, sizeof(compiler__Var)),
                       .is_interface = 0,
                       .scope_level = 0,
                       .typ = tos3(""),
                       .receiver_typ = tos3(""),
                       .is_c = 0,
                       .is_public = 0,
                       .is_method = 0,
                       .is_decl = 0,
                       .is_unsafe = 0,
                       .is_deprecated = 0,
                       .is_variadic = 0,
                       .is_generic = 0,
                       .returns_error = 0,
                       .defer_text = new_array(0, 1, sizeof(string)),
                       .type_pars = new_array(0, 1, sizeof(string)),
                       .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                       .body_idx = 0,
                       .fn_name_token_idx = 0,
                       .comptime_define = tos3(""),
                       .is_used = 0};

    compiler__Parser_next(p);

    int line_nr = p->scanner->line_nr;

    compiler__Parser_fn_args(
        p, &/*112 EXP:"compiler__Fn*" GOT:"compiler__Fn" */ f);

    if (p->scanner->line_nr == line_nr) {

      if (p->tok == compiler__compiler__TokenKind_name) {

        f.typ = compiler__Parser_get_type(p);

      } else {

        f.typ = tos3("void");
      };

    } else {

      f.typ = tos3("void");
    };

    compiler__Type fn_typ =
        (compiler__Type){.name = compiler__Fn_typ_str(&/* ? */ f),
                         .mod = p->mod,
                         .func = f,
                         .cat = compiler__compiler__TypeCategory_func,
                         .is_public = 0,
                         .fields = new_array(0, 1, sizeof(compiler__Var)),
                         .methods = new_array(0, 1, sizeof(compiler__Fn)),
                         .parent = tos3(""),
                         .is_c = 0,
                         .enum_vals = new_array(0, 1, sizeof(string)),
                         .gen_types = new_array(0, 1, sizeof(string)),
                         .is_placeholder = 0,
                         .gen_str = 0};

    compiler__Table_register_type2(p->table, fn_typ);

    return fn_typ;
  };

  bool is_arr = 0;

  bool is_arr2 = 0;

  bool is_question = p->tok == compiler__compiler__TokenKind_question;

  if (is_question) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_question);
  };

  if (p->tok == compiler__compiler__TokenKind_lsbr) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

    if (p->tok == compiler__compiler__TokenKind_number) {

      typ = _STR("[%.*s]", p->lit.len, p->lit.str);

      compiler__Parser_next(p);

    } else {

      is_arr = 1;
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

    if (p->tok == compiler__compiler__TokenKind_lsbr) {

      compiler__Parser_next(p);

      if (p->tok == compiler__compiler__TokenKind_number) {

        typ = string_add(typ, _STR("[%.*s]", p->lit.len, p->lit.str));

        compiler__Parser_check(p, compiler__compiler__TokenKind_number);

      } else {

        is_arr2 = 1;
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);
    };

    cat = compiler__compiler__TypeCategory_array;
  };

  if (!p->builtin_mod && p->tok == compiler__compiler__TokenKind_name &&
      string_eq(p->lit, tos3("map"))) {

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_lsbr);

    string key_type = compiler__Parser_check_name(p);

    if (string_ne(key_type, tos3("string"))) {

      compiler__Parser_error(p, tos3("maps only support string keys for now"));
    };

    compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);

    string val_type = compiler__Parser_get_type(p);

    typ = _STR("map_%.*s", val_type.len, val_type.str);

    compiler__Parser_register_map(p, typ);

    return (compiler__Type){.name = typ,
                            .mod = tos3(""),
                            .is_public = 0,
                            .fields = new_array(0, 1, sizeof(compiler__Var)),
                            .methods = new_array(0, 1, sizeof(compiler__Fn)),
                            .parent = tos3(""),
                            .is_c = 0,
                            .enum_vals = new_array(0, 1, sizeof(string)),
                            .gen_types = new_array(0, 1, sizeof(string)),
                            .is_placeholder = 0,
                            .gen_str = 0};
  };

  while (p->tok == compiler__compiler__TokenKind_mul) {

    if (compiler__Parser_first_pass(&/* ? */ *p)) {

      compiler__Parser_warn(p, tos3("use `&Foo` instead of `*Foo`"));
    };

    mul = 1;

    nr_muls++;

    compiler__Parser_check(p, compiler__compiler__TokenKind_mul);
  };

  if (p->tok == compiler__compiler__TokenKind_amp) {

    mul = 1;

    nr_muls++;

    compiler__Parser_check(p, compiler__compiler__TokenKind_amp);
  };

  typ = string_add(typ, p->lit);

  if (!p->is_struct_init) {

    ;
  };

  if (string_eq(p->lit, tos3("C")) &&
      compiler__Parser_peek(&/* ? */ *p) == compiler__compiler__TokenKind_dot) {

    compiler__Parser_next(p);

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    typ = p->lit;

  } else {

    if (compiler__Parser_peek(&/* ? */ *p) ==
        compiler__compiler__TokenKind_dot) {

      if (!p->builtin_mod &&
          compiler__ImportTable_known_alias(&/* ? */ p->import_table, typ)) {

        string mod =
            compiler__ImportTable_resolve_alias(&/* ? */ p->import_table, typ);

        if (string_contains(mod, tos3("."))) {

          typ = string_replace(mod, tos3("."), tos3("_dot_"));
        };
      };

      compiler__Parser_next(p);

      compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

      typ = string_add(typ, _STR("__%.*s", p->lit.len, p->lit.str));
    };

    compiler__Type t = compiler__Table_find_type(&/* ? */ *p->table, typ);

    if (string_eq(t.name, tos3("")) && !p->builtin_mod) {

      if (!string_contains(typ, tos3("array_")) &&
          string_ne(p->mod, tos3("main")) &&
          !string_contains(typ, tos3("__")) &&
          !string_starts_with(typ, tos3("["))) {

        typ = compiler__Parser_prepend_mod(&/* ? */ *p, typ);
      };

      t = compiler__Table_find_type(&/* ? */ *p->table, typ);

      if (string_eq(t.name, tos3("")) && !p->pref->translated &&
          !compiler__Parser_first_pass(&/* ? */ *p) &&
          !string_starts_with(typ, tos3("["))) {

        println(tos3("get_type() bad type"));

        compiler__Parser_error(p,
                               _STR("unknown type `%.*s`", typ.len, typ.str));
      };
    };
  };

  if (string_eq(typ, tos3("void"))) {

    compiler__Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
  };

  if (mul) {

    typ = string_add(typ, strings__repeat('*', nr_muls));
  };

  if (is_arr2) {

    typ = _STR("array_array_%.*s", typ.len, typ.str);

    compiler__Parser_register_array(p, typ);

  } else if (is_arr) {

    typ = _STR("array_%.*s", typ.len, typ.str);

    compiler__Parser_register_array(p, typ);
  };

  compiler__Parser_next(p);

  if (is_question) {

    typ = _STR("Option_%.*s", typ.len, typ.str);

    compiler__Table_register_type_with_parent(p->table, typ, tos3("Option"));
  };

  if (string_last_index(typ, tos3("__")) > string_index(typ, tos3("__"))) {

    compiler__Parser_error(
        p, _STR("2 __ in gettype(): typ=\"%.*s\"", typ.len, typ.str));
  };

  return (compiler__Type){.name = typ,
                          .cat = cat,
                          .mod = tos3(""),
                          .is_public = 0,
                          .fields = new_array(0, 1, sizeof(compiler__Var)),
                          .methods = new_array(0, 1, sizeof(compiler__Fn)),
                          .parent = tos3(""),
                          .is_c = 0,
                          .enum_vals = new_array(0, 1, sizeof(string)),
                          .gen_types = new_array(0, 1, sizeof(string)),
                          .is_placeholder = 0,
                          .gen_str = 0};
}
string compiler__sql_params2params_gen(array_string sql_params,
                                       array_string sql_types, string qprefix) {

  string params_gen = tos3("");

  array_string tmp1 = sql_params;
  for (int i = 0; i < tmp1.len; i++) {
    string mparam = ((string *)tmp1.data)[i];

    string param = string_trim_space(mparam);

    string paramtype = (*(string *)array_get(sql_types, i));

    if (byte_is_digit(string_at(param, 0))) {

      params_gen = string_add(
          params_gen, _STR("%.*sparams[%d] = int_str(%.*s).str;\n", qprefix.len,
                           qprefix.str, i, param.len, param.str));

    } else if (string_at(param, 0) == '\'') {

      string sparam = string_trim(param, tos3("\'"));

      params_gen = string_add(params_gen,
                              _STR("%.*sparams[%d] = \"%.*s\";\n", qprefix.len,
                                   qprefix.str, i, sparam.len, sparam.str));

    } else {

      if (string_eq(paramtype, tos3("int"))) {

        params_gen =
            string_add(params_gen,
                       _STR("%.*sparams[%d] = int_str( %.*s ).str;\n",
                            qprefix.len, qprefix.str, i, param.len, param.str));

      } else if (string_eq(paramtype, tos3("string"))) {

        params_gen = string_add(params_gen, _STR("%.*sparams[%d] = %.*s.str;\n",
                                                 qprefix.len, qprefix.str, i,
                                                 param.len, param.str));

      } else {

        compiler__verror(tos3("orm: only int and string variable types are "
                              "supported in queries"));
      };
    };
  };

  return params_gen;
}
string compiler__Parser_select_query(compiler__Parser *p, int fn_ph) {

  string qprefix = string_add(
      string_replace(compiler__Parser_get_tmp(p), tos3("tmp"), tos3("sql")),
      tos3("_"));

  p->sql_i = 0;

  p->sql_params = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  p->sql_types = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  string q = tos3("select ");

  compiler__Parser_check(p, compiler__compiler__TokenKind_key_select);

  string n = compiler__Parser_check_name(p);

  if (string_eq(n, tos3("count"))) {

    q = string_add(q, tos3("count(*) from "));

    compiler__Parser_check_name(p);
  };

  string table_name = compiler__Parser_check_name(p);

  compiler__Type typ =
      compiler__Table_find_type(&/* ? */ *p->table, table_name);

  if (string_eq(typ.name, tos3(""))) {

    compiler__Parser_error(
        p, _STR("unknown type `%.*s`", table_name.len, table_name.str));
  };

  array_compiler__Var fields = new_array_from_c_array(
      0, 0, sizeof(compiler__Var),
      EMPTY_ARRAY_OF_ELEMS(compiler__Var, 0){TCCSKIP(0)});

  array_compiler__Var tmp8 = typ.fields;
  for (int i = 0; i < tmp8.len; i++) {
    compiler__Var field = ((compiler__Var *)tmp8.data)[i];

    if (string_ne(field.typ, tos3("string")) &&
        string_ne(field.typ, tos3("int"))) {

      continue;
    };

    _PUSH(&fields,
          (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ field), tmp9,
          compiler__Var);
  };

  if (fields.len == 0) {

    compiler__Parser_error(p, _STR("V orm: select: empty fields in `%.*s`",
                                   table_name.len, table_name.str));
  };

  if (string_ne((*(compiler__Var *)array_get(fields, 0)).name, tos3("id"))) {

    compiler__Parser_error(
        p, _STR("V orm: `id int` must be the first field in `%.*s`",
                table_name.len, table_name.str));
  };

  if (string_eq(n, tos3("from"))) {

    array_compiler__Var tmp12 = fields;
    for (int i = 0; i < tmp12.len; i++) {
      compiler__Var field = ((compiler__Var *)tmp12.data)[i];

      q = string_add(q, field.name);

      if (i < fields.len - 1) {

        q = string_add(q, tos3(", "));
      };
    };

    q = string_add(q, tos3(" from "));
  };

  array_compiler__Var tmp13 = fields;
  for (int tmp14 = 0; tmp14 < tmp13.len; tmp14++) {
    compiler__Var field = ((compiler__Var *)tmp13.data)[tmp14];

    if (string_ne(field.typ, tos3("string")) &&
        string_ne(field.typ, tos3("int"))) {

      continue;
    };

    compiler__Parser_register_var(p, (compiler__Var){
                                         .is_used = 1,
                                         .typ = field.typ,
                                         .name = field.name,
                                         .idx = field.idx,
                                         .is_arg = field.is_arg,
                                         .is_const = field.is_const,
                                         .args = field.args,
                                         .attr = field.attr,
                                         .is_mut = field.is_mut,
                                         .is_alloc = field.is_alloc,
                                         .is_returned = field.is_returned,
                                         .ptr = field.ptr,
                                         .ref = field.ref,
                                         .parent_fn = field.parent_fn,
                                         .mod = field.mod,
                                         .access_mod = field.access_mod,
                                         .is_global = field.is_global,
                                         .is_changed = field.is_changed,
                                         .scope_level = field.scope_level,
                                         .is_c = field.is_c,
                                         .is_moved = field.is_moved,
                                         .line_nr = field.line_nr,
                                         .token_idx = field.token_idx,
                                         .is_for_var = field.is_for_var,
                                         .is_public = field.is_public,
                                     });
  };

  q = string_add(q, table_name);

  if (p->tok == compiler__compiler__TokenKind_name &&
      string_eq(p->lit, tos3("where"))) {

    compiler__Parser_next(p);

    compiler__CGen_start_tmp(p->cgen);

    p->is_sql = 1;

    compiler__Parser_bool_expression(p);

    p->is_sql = 0;

    q = string_add(
        q, string_add(tos3(" where "), compiler__CGen_end_tmp(p->cgen)));
  };

  bool query_one = 0;

  if (p->tok == compiler__compiler__TokenKind_name &&
      string_eq(p->lit, tos3("limit"))) {

    compiler__Parser_next(p);

    compiler__CGen_start_tmp(p->cgen);

    p->is_sql = 1;

    compiler__Parser_bool_expression(p);

    p->is_sql = 0;

    string limit = compiler__CGen_end_tmp(p->cgen);

    q = string_add(q, string_add(tos3(" limit "), limit));

    if (string_eq(string_trim_space(limit), tos3("1"))) {

      query_one = 1;
    };
  };

  printf("sql query=\"%.*s\"\n", q.len, q.str);

  compiler__CGen_insert_before(
      p->cgen, _STR("// DEBUG_SQL prefix: %.*s | fn_ph: %d | query: \"%.*s\" ",
                    qprefix.len, qprefix.str, fn_ph, q.len, q.str));

  if (string_eq(n, tos3("count"))) {

    compiler__CGen_set_placeholder(p->cgen, fn_ph, tos3("pg__DB_q_int("));

    compiler__Parser_gen(p, _STR(", tos2(\"%.*s\"))", q.len, q.str));

  } else {

    string tmp = compiler__Parser_get_tmp(p);

    strings__Builder obj_gen = strings__new_builder(300);

    array_compiler__Var tmp15 = fields;
    for (int i = 0; i < tmp15.len; i++) {
      compiler__Var field = ((compiler__Var *)tmp15.data)[i];

      string cast = tos3("");

      if (string_eq(field.typ, tos3("int"))) {

        cast = tos3("v_string_int");
      };

      strings__Builder_writeln(&/* ? */ obj_gen,
                               _STR("%.*s%.*s . %.*s = %.*s( "
                                    "*(string*)array_get(%.*srow.vals, %d) );",
                                    qprefix.len, qprefix.str, tmp.len, tmp.str,
                                    field.name.len, field.name.str, cast.len,
                                    cast.str, qprefix.len, qprefix.str, i));
    };

    if (query_one) {

      string params_gen =
          compiler__sql_params2params_gen(p->sql_params, p->sql_types, qprefix);

      compiler__CGen_insert_before(
          p->cgen,
          _STR("\n\nchar* %.*sparams[%d];\n%.*s\n\nOption_%.*s "
               "opt_%.*s%.*s;\nvoid* %.*sres = PQexecParams(db.conn, \"%.*s\", "
               "%d, 0, %.*sparams, 0, 0, 0)  ;\narray_pg__Row %.*srows = "
               "pg__res_to_rows ( %.*sres ) ;\nOption_pg__Row opt_%.*srow = "
               "pg__rows_first_or_empty( %.*srows );\nif (! opt_%.*srow . ok ) "
               "{\n   opt_%.*s%.*s = v_error( opt_%.*srow . error );\n}else{\n "
               "  %.*s %.*s%.*s;\n   pg__Row %.*srow = *(pg__Row*) opt_%.*srow "
               ". data;\n%.*s\n   opt_%.*s%.*s = opt_ok( & %.*s%.*s, "
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

      compiler__CGen_resetln(p->cgen, _STR("opt_%.*s%.*s", qprefix.len,
                                           qprefix.str, tmp.len, tmp.str));

    } else {

      q = string_add(q, tos3(" order by id"));

      string params_gen =
          compiler__sql_params2params_gen(p->sql_params, p->sql_types, qprefix);

      compiler__CGen_insert_before(
          p->cgen,
          _STR("char* %.*sparams[%d];\n%.*s\n\nvoid* %.*sres = "
               "PQexecParams(db.conn, \"%.*s\", %d, 0, %.*sparams, 0, 0, 0)  "
               ";\narray_pg__Row %.*srows = pg__res_to_rows(%.*sres);\n\n// "
               "TODO preallocate\narray %.*sarr_%.*s = new_array(0, 0, "
               "sizeof(%.*s));\nfor (int i = 0; i < %.*srows.len; i++) {\n    "
               "pg__Row %.*srow = *(pg__Row*)array_get(%.*srows, i);\n    %.*s "
               "%.*s%.*s;\n    %.*s\n    _PUSH(&%.*sarr_%.*s, %.*s%.*s, %.*s2, "
               "%.*s);\n}\n",
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

      compiler__CGen_resetln(p->cgen, _STR("%.*sarr_%.*s", qprefix.len,
                                           qprefix.str, tmp.len, tmp.str));
    };
  };

  if (string_eq(n, tos3("count"))) {

    return tos3("int");

  } else if (query_one) {

    string opt_type = _STR("Option_%.*s", table_name.len, table_name.str);

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "typedef Option %.*s;", opt_type.len, opt_type.str)),
          tmp16, string);

    compiler__Table_register_builtin(p->table, opt_type);

    return opt_type;

  } else {

    compiler__Parser_register_array(
        p, _STR("array_%.*s", table_name.len, table_name.str));

    return _STR("array_%.*s", table_name.len, table_name.str);
  };
}
void compiler__Parser_insert_query(compiler__Parser *p, int fn_ph) {

  compiler__Parser_check_name(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_lpar);

  string var_name = compiler__Parser_check_name(p);

  compiler__Parser_check(p, compiler__compiler__TokenKind_rpar);

  Option_compiler__Var tmp17 = compiler__Parser_find_var(&/* ? */ *p, var_name);
  compiler__Var var;
  if (!tmp17.ok) {
    string err = tmp17.error;
    int errcode = tmp17.ecode;

    return;
  }
  var = *(compiler__Var *)tmp17.data;
  ;

  compiler__Type typ = compiler__Table_find_type(&/* ? */ *p->table, var.typ);

  array_compiler__Var fields = new_array_from_c_array(
      0, 0, sizeof(compiler__Var),
      EMPTY_ARRAY_OF_ELEMS(compiler__Var, 0){TCCSKIP(0)});

  array_compiler__Var tmp18 = typ.fields;
  for (int i = 0; i < tmp18.len; i++) {
    compiler__Var field = ((compiler__Var *)tmp18.data)[i];

    if (string_ne(field.typ, tos3("string")) &&
        string_ne(field.typ, tos3("int"))) {

      continue;
    };

    _PUSH(&fields,
          (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ field), tmp19,
          compiler__Var);
  };

  if (fields.len == 0) {

    compiler__Parser_error(p, _STR("V orm: insert: empty fields in `%.*s`",
                                   var.typ.len, var.typ.str));
  };

  if (string_ne((*(compiler__Var *)array_get(fields, 0)).name, tos3("id"))) {

    compiler__Parser_error(
        p, _STR("V orm: `id int` must be the first field in `%.*s`",
                var.typ.len, var.typ.str));
  };

  string table_name = var.typ;

  string sfields = tos3("");

  string params = tos3("");

  string vals = tos3("");

  int nr_vals = 0;

  array_compiler__Var tmp22 = fields;
  for (int i = 0; i < tmp22.len; i++) {
    compiler__Var field = ((compiler__Var *)tmp22.data)[i];

    if (string_eq(field.name, tos3("id"))) {

      continue;
    };

    sfields = string_add(sfields, field.name);

    vals = string_add(vals, string_add(tos3("$"), int_str(i)));

    nr_vals++;

    params = string_add(params, _STR("params[%d] = ", i - 1));

    if (string_eq(field.typ, tos3("string"))) {

      params = string_add(params,
                          _STR("%.*s . %.*s .str;\n", var_name.len,
                               var_name.str, field.name.len, field.name.str));

    } else if (string_eq(field.typ, tos3("int"))) {

      params = string_add(params,
                          _STR("int_str(%.*s . %.*s).str;\n", var_name.len,
                               var_name.str, field.name.len, field.name.str));

    } else {

      compiler__Parser_error(p, _STR("V ORM: unsupported type `%.*s`",
                                     field.typ.len, field.typ.str));
    };

    if (i < fields.len - 1) {

      sfields = string_add(sfields, tos3(", "));

      vals = string_add(vals, tos3(", "));
    };
  };

  compiler__CGen_insert_before(
      p->cgen, string_add(_STR("char* params[%d];", nr_vals), params));

  compiler__CGen_set_placeholder(p->cgen, fn_ph, tos3("PQexecParams( "));

  compiler__Parser_genln(p, _STR(".conn, \"insert into %.*s (%.*s) values "
                                 "(%.*s)\", %d,\n0, params, 0, 0, 0)",
                                 table_name.len, table_name.str, sfields.len,
                                 sfields.str, vals.len, vals.str, nr_vals));
}
compiler__Scanner *compiler__new_scanner_file(string file_path) {

  if (!os__file_exists(file_path)) {

    compiler__verror(_STR("%.*s doesn't exist", file_path.len, file_path.str));
  };

  Option_string tmp1 = os__read_file(file_path);
  string raw_text;
  if (!tmp1.ok) {
    string err = tmp1.error;
    int errcode = tmp1.ecode;

    compiler__verror(
        _STR("scanner: failed to open %.*s", file_path.len, file_path.str));

    return 0;
  }
  raw_text = *(string *)tmp1.data;
  ;

  if (raw_text.len >= 3) {

    byte *c_text = raw_text.str;

    if (c_text[/*ptr*/ 0] /*rbyte 0*/ == 0xEF &&
        c_text[/*ptr*/ 1] /*rbyte 0*/ == 0xBB &&
        c_text[/*ptr*/ 2] /*rbyte 0*/ == 0xBF) {

      int offset_from_begin = 3;

      raw_text = tos(&/*112 EXP:"byte*" GOT:"byte" */ c_text
                         [/*ptr*/ offset_from_begin] /*rbyte 0*/,
                     vstrlen(c_text) - offset_from_begin);
    };
  };

  compiler__Scanner *s = compiler__new_scanner(raw_text);

  s->file_path = file_path;

  return s;
}
compiler__Scanner *compiler__new_scanner(string text) {

  return (compiler__Scanner *)memdup(
      &(compiler__Scanner){.text = text,
                           .fmt_out = strings__new_builder(1000),
                           .should_print_line_on_error = 1,
                           .should_print_errors_in_color = 1,
                           .should_print_relative_paths_on_error = 1,
                           .file_path = tos3(""),
                           .pos = 0,
                           .line_nr = 0,
                           .last_nl_pos = 0,
                           .inside_string = 0,
                           .inter_start = 0,
                           .inter_end = 0,
                           .debug = 0,
                           .line_comment = tos3(""),
                           .started = 0,
                           .fmt_indent = 0,
                           .fmt_line_empty = 0,
                           .fn_name = tos3(""),
                           .quote = 0,
                           .line_ends = new_array(0, 1, sizeof(int)),
                           .nlines = 0,
                           .is_vh = 0},
      sizeof(compiler__Scanner));
}
compiler__ScanRes compiler__scan_res(compiler__TokenKind tok, string lit) {

  return (compiler__ScanRes){tok, lit};
}
string compiler__Scanner_ident_name(compiler__Scanner *s) {

  int start = s->pos;

  while (1) {

    s->pos++;

    if (s->pos >= s->text.len) {

      break;
    };

    byte c = string_at(s->text, s->pos);

    if (!compiler__is_name_char(c) && !byte_is_digit(c)) {

      break;
    };
  };

  string name = string_substr2(s->text, start, s->pos, false);

  s->pos--;

  return name;
}
string compiler__Scanner_ident_hex_number(compiler__Scanner *s) {

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

  string number = string_substr2(s->text, start_pos, s->pos, false);

  s->pos--;

  return number;
}
string compiler__Scanner_ident_oct_number(compiler__Scanner *s) {

  int start_pos = s->pos;

  while (1) {

    if (s->pos >= s->text.len) {

      break;
    };

    byte c = string_at(s->text, s->pos);

    if (byte_is_digit(c)) {

      if (!byte_is_oct_digit(c)) {

        compiler__Scanner_error(&/* ? */ *s, tos3("malformed octal constant"));
      };

    } else {

      break;
    };

    s->pos++;
  };

  string number = string_substr2(s->text, start_pos, s->pos, false);

  s->pos--;

  return number;
}
string compiler__Scanner_ident_dec_number(compiler__Scanner *s) {

  int start_pos = s->pos;

  while (s->pos < s->text.len && byte_is_digit(string_at(s->text, s->pos))) {

    s->pos++;
  };

  if (compiler__Scanner_expect(&/* ? */ *s, tos3(".."), s->pos)) {

    string number = string_substr2(s->text, start_pos, s->pos, false);

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

      compiler__Scanner_error(&/* ? */ *s, tos3("no `f` is needed for floats"));
    };
  };

  bool has_exponential_part = 0;

  if (compiler__Scanner_expect(&/* ? */ *s, tos3("e+"), s->pos) ||
      compiler__Scanner_expect(&/* ? */ *s, tos3("e-"), s->pos)) {

    int exp_start_pos = s->pos += 2;

    while (s->pos < s->text.len && byte_is_digit(string_at(s->text, s->pos))) {

      s->pos++;
    };

    if (exp_start_pos == s->pos) {

      compiler__Scanner_error(&/* ? */ *s, tos3("exponent has no digits"));
    };

    has_exponential_part = 1;
  };

  if (s->pos < s->text.len && string_at(s->text, s->pos) == '.') {

    if (has_exponential_part) {

      compiler__Scanner_error(&/* ? */ *s,
                              tos3("exponential part should be integer"));

    } else {

      compiler__Scanner_error(&/* ? */ *s,
                              tos3("too many decimal points in number"));
    };
  };

  string number = string_substr2(s->text, start_pos, s->pos, false);

  s->pos--;

  return number;
}
string compiler__Scanner_ident_number(compiler__Scanner *s) {

  if (compiler__Scanner_expect(&/* ? */ *s, tos3("0x"), s->pos)) {

    return compiler__Scanner_ident_hex_number(s);
  };

  if (compiler__Scanner_expect(&/* ? */ *s, tos3("0."), s->pos) ||
      compiler__Scanner_expect(&/* ? */ *s, tos3("0e"), s->pos)) {

    return compiler__Scanner_ident_dec_number(s);
  };

  if (string_at(s->text, s->pos) == '0') {

    return compiler__Scanner_ident_oct_number(s);
  };

  return compiler__Scanner_ident_dec_number(s);
}
void compiler__Scanner_skip_whitespace(compiler__Scanner *s) {

  while (s->pos < s->text.len && byte_is_white(string_at(s->text, s->pos))) {

    if (compiler__is_nl(string_at(s->text, s->pos)) && s->is_vh) {

      return;
    };

    if (compiler__is_nl(string_at(s->text, s->pos)) &&
        !compiler__Scanner_expect(&/* ? */ *s, tos3("\r\n"), s->pos - 1)) {

      compiler__Scanner_inc_line_number(s);
    };

    s->pos++;
  };
}
compiler__ScanRes compiler__Scanner_end_of_file(compiler__Scanner *s) {

  s->pos = s->text.len;

  compiler__Scanner_inc_line_number(s);

  return compiler__scan_res(compiler__compiler__TokenKind_eof, tos3(""));
}
compiler__ScanRes compiler__Scanner_scan(compiler__Scanner *s) {

  if (s->started) {

    s->pos++;
  };

  s->started = 1;

  if (s->pos >= s->text.len) {

    return compiler__Scanner_end_of_file(s);
  };

  if (!s->inside_string) {

    compiler__Scanner_skip_whitespace(s);
  };

  if (s->inter_end) {

    if (string_at(s->text, s->pos) == s->quote) {

      s->inter_end = 0;

      return compiler__scan_res(compiler__compiler__TokenKind_str, tos3(""));
    };

    s->inter_end = 0;

    return compiler__scan_res(compiler__compiler__TokenKind_str,
                              compiler__Scanner_ident_string(s));
  };

  compiler__Scanner_skip_whitespace(s);

  if (s->pos >= s->text.len) {

    return compiler__Scanner_end_of_file(s);
  };

  byte c = string_at(s->text, s->pos);

  byte nextc = '\0';

  if (s->pos + 1 < s->text.len) {

    nextc = string_at(s->text, s->pos + 1);
  };

  if (compiler__is_name_char(c)) {

    string name = compiler__Scanner_ident_name(s);

    byte next_char =
        (s->pos + 1 < s->text.len) ? (string_at(s->text, s->pos + 1)) : ('\0');

    if (compiler__is_key(name)) {

      return compiler__scan_res(compiler__key_to_token(name), tos3(""));
    };

    if (s->inside_string) {

      if (next_char == s->quote) {

        s->inter_end = 1;

        s->inter_start = 0;

        s->inside_string = 0;
      };
    };

    if (s->inter_start && next_char != '.') {

      s->inter_end = 1;

      s->inter_start = 0;
    };

    if (s->pos == 0 && next_char == ' ') {

      s->pos++;
    };

    return compiler__scan_res(compiler__compiler__TokenKind_name, name);

  } else if (byte_is_digit(c) || (c == '.' && byte_is_digit(nextc))) {

    string num = compiler__Scanner_ident_number(s);

    return compiler__scan_res(compiler__compiler__TokenKind_number, num);
  };

  byte tmp46 = c;

  if (tmp46 == '+') {

    if (nextc == '+') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_inc, tos3(""));

    } else if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_plus_assign,
                                tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_plus, tos3(""));

  } else if (tmp46 == '-') {

    if (nextc == '-') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_dec, tos3(""));

    } else if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_minus_assign,
                                tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_minus, tos3(""));

  } else if (tmp46 == '*') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_mult_assign,
                                tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_mul, tos3(""));

  } else if (tmp46 == '^') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_xor_assign,
                                tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_xor, tos3(""));

  } else if (tmp46 == '%') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_mod_assign,
                                tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_mod, tos3(""));

  } else if (tmp46 == '?') {

    return compiler__scan_res(compiler__compiler__TokenKind_question, tos3(""));

  } else if ((tmp46 == compiler__single_quote) ||
             (tmp46 == compiler__double_quote)) {

    return compiler__scan_res(compiler__compiler__TokenKind_str,
                              compiler__Scanner_ident_string(s));

  } else if (tmp46 == '`') {

    return compiler__scan_res(compiler__compiler__TokenKind_chartoken,
                              compiler__Scanner_ident_char(s));

  } else if (tmp46 == '(') {

    return compiler__scan_res(compiler__compiler__TokenKind_lpar, tos3(""));

  } else if (tmp46 == ')') {

    return compiler__scan_res(compiler__compiler__TokenKind_rpar, tos3(""));

  } else if (tmp46 == '[') {

    return compiler__scan_res(compiler__compiler__TokenKind_lsbr, tos3(""));

  } else if (tmp46 == ']') {

    return compiler__scan_res(compiler__compiler__TokenKind_rsbr, tos3(""));

  } else if (tmp46 == '{') {

    if (s->inside_string) {

      return compiler__Scanner_scan(s);
    };

    return compiler__scan_res(compiler__compiler__TokenKind_lcbr, tos3(""));

  } else if (tmp46 == '$') {

    return compiler__scan_res(compiler__compiler__TokenKind_dollar, tos3(""));

  } else if (tmp46 == '}') {

    if (s->inside_string) {

      s->pos++;

      if (string_at(s->text, s->pos) == compiler__single_quote) {

        s->inside_string = 0;

        return compiler__scan_res(compiler__compiler__TokenKind_str, tos3(""));
      };

      return compiler__scan_res(compiler__compiler__TokenKind_str,
                                compiler__Scanner_ident_string(s));

    } else {

      return compiler__scan_res(compiler__compiler__TokenKind_rcbr, tos3(""));
    };

  } else if (tmp46 == '&') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_and_assign,
                                tos3(""));
    };

    if (nextc == '&') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_and, tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_amp, tos3(""));

  } else if (tmp46 == '|') {

    if (nextc == '|') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_logical_or,
                                tos3(""));
    };

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_or_assign,
                                tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_pipe, tos3(""));

  } else if (tmp46 == ',') {

    return compiler__scan_res(compiler__compiler__TokenKind_comma, tos3(""));

  } else if (tmp46 == '@') {

    s->pos++;

    string name = compiler__Scanner_ident_name(s);

    if (string_eq(name, tos3("FN"))) {

      return compiler__scan_res(compiler__compiler__TokenKind_str, s->fn_name);
    };

    if (string_eq(name, tos3("FILE"))) {

      return compiler__scan_res(
          compiler__compiler__TokenKind_str,
          compiler__cescaped_path(os__realpath(s->file_path)));
    };

    if (string_eq(name, tos3("LINE"))) {

      return compiler__scan_res(compiler__compiler__TokenKind_str,
                                int_str((s->line_nr + 1)));
    };

    if (string_eq(name, tos3("COLUMN"))) {

      return compiler__scan_res(
          compiler__compiler__TokenKind_str,
          int_str((compiler__Scanner_current_column(&/* ? */ *s))));
    };

    if (string_eq(name, tos3("VHASH"))) {

      return compiler__scan_res(compiler__compiler__TokenKind_str,
                                compiler__vhash());
    };

    if (!compiler__is_key(name)) {

      compiler__Scanner_error(
          &/* ? */ *s,
          tos3("@ must be used before keywords (e.g. `@type string`)"));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_name, name);

  } else if (tmp46 == '.') {

    if (nextc == '.') {

      s->pos++;

      if (string_at(s->text, s->pos + 1) == '.') {

        s->pos++;

        return compiler__scan_res(compiler__compiler__TokenKind_ellipsis,
                                  tos3(""));
      };

      return compiler__scan_res(compiler__compiler__TokenKind_dotdot, tos3(""));
    };

    return compiler__scan_res(compiler__compiler__TokenKind_dot, tos3(""));

  } else if (tmp46 == '#') {

    int start = s->pos + 1;

    compiler__Scanner_ignore_line(s);

    if (nextc == '!') {

      s->line_comment =
          string_trim_space(string_substr2(s->text, start + 1, s->pos, false));

      ;

      return compiler__Scanner_scan(s);
    };

    string hash = string_substr2(s->text, start, s->pos, false);

    return compiler__scan_res(compiler__compiler__TokenKind_hash,
                              string_trim_space(hash));

  } else if (tmp46 == '>') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_ge, tos3(""));

    } else if (nextc == '>') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return compiler__scan_res(
            compiler__compiler__TokenKind_righ_shift_assign, tos3(""));
      };

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_righ_shift,
                                tos3(""));

    } else {

      return compiler__scan_res(compiler__compiler__TokenKind_gt, tos3(""));
    };

  } else if (tmp46 == 0xE2) {

    if (nextc == 0x89 && string_at(s->text, s->pos + 2) == 0xA0) {

      s->pos += 2;

      return compiler__scan_res(compiler__compiler__TokenKind_ne, tos3(""));

    } else if (nextc == 0x89 && string_at(s->text, s->pos + 2) == 0xBD) {

      s->pos += 2;

      return compiler__scan_res(compiler__compiler__TokenKind_le, tos3(""));

    } else if (nextc == 0xA9 && string_at(s->text, s->pos + 2) == 0xBE) {

      s->pos += 2;

      return compiler__scan_res(compiler__compiler__TokenKind_ge, tos3(""));
    };

  } else if (tmp46 == '<') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_le, tos3(""));

    } else if (nextc == '<') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return compiler__scan_res(
            compiler__compiler__TokenKind_left_shift_assign, tos3(""));
      };

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_left_shift,
                                tos3(""));

    } else {

      return compiler__scan_res(compiler__compiler__TokenKind_lt, tos3(""));
    };

  } else if (tmp46 == '=') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_eq, tos3(""));

    } else if (nextc == '>') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_arrow, tos3(""));

    } else {

      return compiler__scan_res(compiler__compiler__TokenKind_assign, tos3(""));
    };

  } else if (tmp46 == ':') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_decl_assign,
                                tos3(""));

    } else {

      return compiler__scan_res(compiler__compiler__TokenKind_colon, tos3(""));
    };

  } else if (tmp46 == ';') {

    return compiler__scan_res(compiler__compiler__TokenKind_semicolon,
                              tos3(""));

  } else if (tmp46 == '!') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_ne, tos3(""));

    } else {

      return compiler__scan_res(compiler__compiler__TokenKind_not, tos3(""));
    };

  } else if (tmp46 == '~') {

    return compiler__scan_res(compiler__compiler__TokenKind_bit_not, tos3(""));

  } else if (tmp46 == '/') {

    if (nextc == '=') {

      s->pos++;

      return compiler__scan_res(compiler__compiler__TokenKind_div_assign,
                                tos3(""));
    };

    if (nextc == '/') {

      int start = s->pos + 1;

      compiler__Scanner_ignore_line(s);

      s->line_comment = string_substr2(s->text, start + 1, s->pos, false);

      s->line_comment = string_trim_space(s->line_comment);

      ;

      return compiler__Scanner_scan(s);
    };

    if (nextc == '*') {

      int start = s->pos;

      int nest_count = 1;

      while (nest_count > 0) {

        s->pos++;

        if (s->pos >= s->text.len) {

          s->line_nr--;

          compiler__Scanner_error(&/* ? */ *s, tos3("comment not terminated"));
        };

        if (string_at(s->text, s->pos) == '\n') {

          compiler__Scanner_inc_line_number(s);

          continue;
        };

        if (compiler__Scanner_expect(&/* ? */ *s, tos3("/*"), s->pos)) {

          nest_count++;

          continue;
        };

        if (compiler__Scanner_expect(&/* ? */ *s, tos3("*/"), s->pos)) {

          nest_count--;
        };
      };

      s->pos++;

      int end = s->pos + 1;

      string comm = string_substr2(s->text, start, end, false);

      ;

      return compiler__Scanner_scan(s);
    };

    return compiler__scan_res(compiler__compiler__TokenKind_div, tos3(""));
  };

#ifdef _WIN32

  if (c == '\0') {

    return compiler__Scanner_end_of_file(s);
  };

#endif
  ;

  string msg =
      _STR("invalid character `%.*s`", byte_str(c).len, byte_str(c).str);

  if (c == '"') {

    msg = string_add(msg, tos3(", use \' to denote strings"));
  };

  compiler__Scanner_error(&/* ? */ *s, msg);

  return compiler__Scanner_end_of_file(s);
}
int compiler__Scanner_current_column(compiler__Scanner *s) {

  return s->pos - s->last_nl_pos;
}
int compiler__Scanner_count_symbol_before(compiler__Scanner s, int p,
                                          byte sym) {

  int count = 0;

  for (int i = p; i >= 0; i--) {

    if (string_at(s.text, i) != sym) {

      break;
    };

    count++;
  };

  return count;
}
string compiler__Scanner_ident_string(compiler__Scanner *s) {

  byte q = string_at(s->text, s->pos);

  bool is_quote = q == compiler__single_quote || q == compiler__double_quote;

  bool is_raw = is_quote && string_at(s->text, s->pos - 1) == 'r';

  if (is_quote && !s->inside_string) {

    s->quote = q;
  };

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

    if (c == s->quote &&
        (prevc != slash ||
         (prevc == slash && string_at(s->text, s->pos - 2) == slash))) {

      break;
    };

    if (c == '\n') {

      compiler__Scanner_inc_line_number(s);
    };

    if (c == '0' && s->pos > 2 && string_at(s->text, s->pos - 1) == slash) {

      compiler__Scanner_error(&/* ? */ *s,
                              tos3("0 character in a string literal"));
    };

    if (c == '0' && s->pos > 5 &&
        compiler__Scanner_expect(&/* ? */ *s, tos3("\\x0"), s->pos - 3)) {

      compiler__Scanner_error(&/* ? */ *s,
                              tos3("0 character in a string literal"));
    };

    if (c == '{' && prevc == '$' && !is_raw &&
        compiler__Scanner_count_symbol_before(*s, s->pos - 2, slash) % 2 == 0) {

      s->inside_string = 1;

      s->pos -= 2;

      break;
    };

    if ((byte_is_letter(c) || c == '_') && prevc == '$' && !is_raw &&
        compiler__Scanner_count_symbol_before(*s, s->pos - 2, slash) % 2 == 0) {

      s->inside_string = 1;

      s->inter_start = 1;

      s->pos -= 2;

      break;
    };
  };

  string lit = tos3("");

  if (string_at(s->text, start) == s->quote) {

    start++;
  };

  int end = s->pos;

  if (s->inside_string) {

    end++;
  };

  if (start > s->pos) {

  } else {

    lit = string_substr2(s->text, start, end, false);
  };

  return lit;
}
string compiler__Scanner_ident_char(compiler__Scanner *s) {

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

    bool double_slash =
        compiler__Scanner_expect(&/* ? */ *s, tos3("\\\\"), s->pos - 2);

    if (string_at(s->text, s->pos) == '`' &&
        (string_at(s->text, s->pos - 1) != slash || double_slash)) {

      if (double_slash) {

        len++;
      };

      break;
    };
  };

  len--;

  string c = string_substr2(s->text, start + 1, s->pos, false);

  if (len != 1) {

    ustring u = string_ustring(c);

    if (u.len != 1) {

      compiler__Scanner_error(
          &/* ? */ *s,
          _STR("invalid character literal (more than one character: %d)", len));
    };
  };

  if (string_eq(c, tos3("\\`"))) {

    return tos3("`");
  };

  return (string_eq(c, tos3("\'"))) ? (string_add(tos3("\\"), c)) : (c);
}
bool compiler__Scanner_expect(compiler__Scanner *s, string want,
                              int start_pos) {

  int end_pos = start_pos + want.len;

  if (start_pos < 0 || start_pos >= s->text.len) {

    return 0;
  };

  if (end_pos < 0 || end_pos > s->text.len) {

    return 0;
  };

  int tmp97 = start_pos;
  ;
  for (int tmp98 = tmp97; tmp98 < end_pos; tmp98++) {
    int pos = tmp98;

    if (string_at(s->text, pos) != string_at(want, pos - start_pos)) {

      return 0;
    };
  };

  return 1;
}
void compiler__Scanner_debug_tokens(compiler__Scanner *s) {

  s->pos = 0;

  s->started = 0;

  s->debug = 1;

  string fname = string_all_after(s->file_path, os__path_separator);

  printf("\n===DEBUG TOKENS %.*s===\n", fname.len, fname.str);

  while (1) {

    compiler__ScanRes res = compiler__Scanner_scan(s);

    compiler__TokenKind tok = res.tok;

    string lit = res.lit;

    print(compiler__TokenKind_str(tok));

    if (string_ne(lit, tos3(""))) {

      printf(" `%.*s`\n", lit.len, lit.str);

    } else {

      println(tos3(""));
    };

    if (tok == compiler__compiler__TokenKind_eof) {

      println(tos3("============ END OF DEBUG TOKENS =================="));

      break;
    };
  };
}
void compiler__Scanner_ignore_line(compiler__Scanner *s) {

  compiler__Scanner_eat_to_end_of_line(s);

  compiler__Scanner_inc_line_number(s);
}
void compiler__Scanner_eat_to_end_of_line(compiler__Scanner *s) {

  while (s->pos < s->text.len && string_at(s->text, s->pos) != '\n') {

    s->pos++;
  };
}
void compiler__Scanner_inc_line_number(compiler__Scanner *s) {

  s->last_nl_pos = s->pos;

  s->line_nr++;

  _PUSH(&s->line_ends, (/*typ = array_int   tmp_typ=int*/ s->pos), tmp105, int);

  if (s->line_nr > s->nlines) {

    s->nlines = s->line_nr;
  };
}
string compiler__Scanner_line(compiler__Scanner s, int n) {

  string res = tos3("");

  if (n >= 0 && n < s.line_ends.len) {

    int nline_start =
        (n == 0) ? (0) : ((*(int *)array_get(s.line_ends, n - 1)));

    int nline_end = (*(int *)array_get(s.line_ends, n));

    if (nline_start <= nline_end) {

      res = string_substr2(s.text, nline_start, nline_end, false);
    };
  };

  return string_trim_left(string_trim_right(res, tos3("\r\n")), tos3("\r\n"));
}
bool compiler__is_name_char(byte c) { return byte_is_letter(c) || c == '_'; }
static inline bool compiler__is_nl(byte c) { return c == '\r' || c == '\n'; }
bool compiler__contains_capital(string s) {

  string tmp112 = s;
  array_byte bytes_tmp112 = string_bytes(tmp112);
  ;
  for (int tmp113 = 0; tmp113 < tmp112.len; tmp113++) {
    byte c = ((byte *)bytes_tmp112.data)[tmp113];

    if (c >= 'A' && c <= 'Z') {

      return 1;
    };
  };

  return 0;
}
bool compiler__good_type_name(string s) {

  if (s.len < 4) {

    return 1;
  };

  int tmp114 = 2;
  ;
  for (int tmp115 = tmp114; tmp115 < s.len; tmp115++) {
    int i = tmp115;

    if (byte_is_capital(string_at(s, i)) &&
        byte_is_capital(string_at(s, i - 1)) &&
        byte_is_capital(string_at(s, i - 2))) {

      return 0;
    };
  };

  return 1;
}
void compiler__Scanner_validate_var_name(compiler__Scanner *s, string name) {

  if (name.len > 11 && !string_contains(name, tos3("_"))) {

    compiler__Scanner_error(
        &/* ? */ *s,
        string_add(
            string_add(_STR("bad variable name `%.*s`\n", name.len, name.str),
                       tos3("looks like you have a multi-word name without "
                            "separating them with `_`")),
            tos3("\nfor example, use `registration_date` instead of "
                 "`registrationdate` ")));
  };
}
void compiler__Parser_struct_decl(compiler__Parser *p) {

  bool is_pub = p->tok == compiler__compiler__TokenKind_key_pub;

  if (is_pub) {

    compiler__Parser_next(p);
  };

  bool is_objc = string_starts_with(p->attr, tos3("objc_interface"));

  string objc_parent =
      (is_objc) ? (string_substr2(p->attr, 15, -1, true)) : (tos3(""));

  bool is_interface = p->tok == compiler__compiler__TokenKind_key_interface;

  bool is_union = p->tok == compiler__compiler__TokenKind_key_union;

  bool is_struct = p->tok == compiler__compiler__TokenKind_key_struct;

  compiler__TypeCategory cat = compiler__key_to_type_cat(p->tok);

  if (is_objc) {

    cat = compiler__compiler__TypeCategory_objc_interface;
  };

  ;

  compiler__Parser_next(p);

  string name = compiler__Parser_check_name(p);

  if (string_contains(name, tos3("_")) && !p->pref->translated) {

    compiler__Parser_error(p, tos3("type names cannot contain `_`"));
  };

  if (!p->builtin_mod && !byte_is_capital(string_at(name, 0))) {

    compiler__Parser_error(
        p, _STR("struct names must be capitalized: use `struct %.*s`",
                string_capitalize(name).len, string_capitalize(name).str));
  };

  if (is_interface && !string_ends_with(name, tos3("er"))) {

    compiler__Parser_error(p, tos3("interface names temporarily have to end "
                                   "with `er` (e.g. `Speaker`, `Reader`)"));
  };

  bool is_c =
      string_eq(name, tos3("C")) && p->tok == compiler__compiler__TokenKind_dot;

  if (is_c) {

    compiler__Parser_check(p, compiler__compiler__TokenKind_dot);

    name = compiler__Parser_check_name(p);

    cat = compiler__compiler__TypeCategory_c_struct;

    if (string_eq(p->attr, tos3("typedef"))) {

      cat = compiler__compiler__TypeCategory_c_typedef;
    };
  };

  if (name.len == 1 && !p->pref->building_v && !p->pref->is_repl) {

    compiler__Parser_warn(
        p, tos3("struct names must have more than one character"));
  };

  if (!is_c && !compiler__good_type_name(name)) {

    compiler__Parser_error(p, tos3("bad struct name, e.g. use `HttpRequest` "
                                   "instead of `HTTPRequest`"));
  };

  if (!is_c && !p->builtin_mod && string_ne(p->mod, tos3("main"))) {

    name = compiler__Parser_prepend_mod(&/* ? */ *p, name);
  };

  compiler__Type typ = compiler__Table_find_type(&/* ? */ *p->table, name);

  if (p->pass == compiler__compiler__Pass_decl &&
      compiler__Table_known_type_fast(
          &/* ? */ *p->table,
          &/*112 EXP:"compiler__Type*" GOT:"compiler__Type" */ typ)) {

    compiler__Parser_error(p,
                           _STR("type `%.*s` redeclared", name.len, name.str));
  };

  if (is_objc) {

    compiler__Parser_gen_typedef(p, _STR("@class %.*s;", name.len, name.str));

  } else if (!is_c) {

    string kind = (is_union) ? (tos3("union")) : (tos3("struct"));

    compiler__Parser_gen_typedef(p, _STR("typedef %.*s %.*s %.*s;", kind.len,
                                         kind.str, name.len, name.str, name.len,
                                         name.str));
  };

  bool is_ph = 0;

  if (typ.is_placeholder) {

    is_ph = 1;

    typ.name = name;

    typ.mod = p->mod;

    typ.is_c = is_c;

    typ.is_placeholder = 0;

    typ.cat = cat;

    typ.parent = objc_parent;

    typ.is_public = is_pub || p->is_vh;

    compiler__Table_rewrite_type(p->table, typ);

  } else {

    typ = (compiler__Type){.name = name,
                           .mod = p->mod,
                           .is_c = is_c,
                           .cat = cat,
                           .parent = objc_parent,
                           .is_public = is_pub || p->is_vh,
                           .fields = new_array(0, 1, sizeof(compiler__Var)),
                           .methods = new_array(0, 1, sizeof(compiler__Fn)),
                           .enum_vals = new_array(0, 1, sizeof(string)),
                           .gen_types = new_array(0, 1, sizeof(string)),
                           .is_placeholder = 0,
                           .gen_str = 0};
  };

  if (is_c && is_struct && p->tok != compiler__compiler__TokenKind_lcbr) {

    compiler__Table_register_type2(p->table, typ);

    return;
  };

  ;

  compiler__Parser_check(p, compiler__compiler__TokenKind_lcbr);

  bool is_pub_field = 0;

  bool is_mut = 0;

  array_string names = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (!is_ph && compiler__Parser_first_pass(&/* ? */ *p)) {

    compiler__Table_register_type2(p->table, typ);
  };

  bool did_gen_something = 0;

  while (p->tok != compiler__compiler__TokenKind_rcbr) {

    if (p->tok == compiler__compiler__TokenKind_key_pub) {

      if (is_pub_field) {

        compiler__Parser_error(p, tos3("structs can only have one `pub:`, all "
                                       "public fields have to be grouped"));
      };

      is_pub_field = 1;

      ;

      compiler__Parser_check(p, compiler__compiler__TokenKind_key_pub);

      if (p->tok != compiler__compiler__TokenKind_key_mut) {

        compiler__Parser_check(p, compiler__compiler__TokenKind_colon);
      };

      ;

      ;
    };

    if (p->tok == compiler__compiler__TokenKind_key_mut) {

      if (is_mut) {

        compiler__Parser_error(
            p, tos3("structs can only have one `mut:`, all private mutable "
                    "fields have to be grouped"));
      };

      is_mut = 1;

      ;

      compiler__Parser_check(p, compiler__compiler__TokenKind_key_mut);

      if (p->tok != compiler__compiler__TokenKind_key_mut) {

        compiler__Parser_check(p, compiler__compiler__TokenKind_colon);
      };

      ;

      ;
    };

    int field_name_token_idx = compiler__Parser_cur_tok_index(&/* ? */ *p);

    string field_name =
        (string_ne(name, tos3("Option")))
            ? (compiler__Table_var_cgen_name(&/* ? */ *p->table,
                                             compiler__Parser_check_name(p)))
            : (compiler__Parser_check_name(p));

    if ((_IN(string, (field_name), names))) {

      compiler__Parser_error(
          p, _STR("duplicate field `%.*s`", field_name.len, field_name.str));
    };

    if (!is_c && string_ne(p->mod, tos3("os")) &&
        compiler__contains_capital(field_name)) {

      compiler__Parser_error(p, tos3("struct fields cannot contain uppercase "
                                     "letters, use snake_case instead"));
    };

    _PUSH(&names, (/*typ = array_string   tmp_typ=string*/ field_name), tmp5,
          string);

    if (is_interface) {

      compiler__Fn *f = compiler__Parser_interface_method(p, field_name, name);

      if (compiler__Parser_first_pass(&/* ? */ *p)) {

        compiler__Parser_add_method(p, typ.name, *f);
      };

      continue;
    };

    compiler__AccessMod access_mod =
        (is_pub_field) ? (compiler__compiler__AccessMod_public)
                       : (compiler__compiler__AccessMod_private);

    ;

    string field_type = compiler__Parser_get_type(p);

    if (string_eq(field_type, name)) {

      compiler__Parser_error_with_token_index(
          p,
          _STR("cannot embed struct `%.*s` in itself (field `%.*s`)", name.len,
               name.str, field_name.len, field_name.str),
          field_name_token_idx);
    };

    compiler__Parser_check_and_register_used_imported_type(p, field_type);

    bool is_atomic = p->tok == compiler__compiler__TokenKind_key_atomic;

    if (is_atomic) {

      compiler__Parser_next(p);
    };

    string attr = tos3("");

    if (p->tok == compiler__compiler__TokenKind_lsbr) {

      compiler__Parser_next(p);

      attr = compiler__Parser_check_name(p);

      if (p->tok == compiler__compiler__TokenKind_colon) {

        compiler__Parser_check(p, compiler__compiler__TokenKind_colon);

        string val = tos3("");

        compiler__TokenKind tmp6 = p->tok;

        if (tmp6 == compiler__compiler__TokenKind_name) {

          val = compiler__Parser_check_name(p);

        } else if (tmp6 == compiler__compiler__TokenKind_str) {

          val = compiler__Parser_check_string(p);

        } else // default:
        {

          compiler__Parser_error(
              p, tos3("attribute value should be either name or string"));
        };

        attr = string_add(attr, string_add(tos3(":"), val));
      };

      compiler__Parser_check(p, compiler__compiler__TokenKind_rsbr);
    };

    if (string_eq(attr, tos3("raw")) && string_ne(field_type, tos3("string"))) {

      compiler__Parser_error(p,
                             _STR("struct field with attribute \"raw\" should "
                                  "be of type \"string\" but got \"%.*s\"",
                                  field_type.len, field_type.str));
    };

    did_gen_something = 1;

    if (compiler__Parser_first_pass(&/* ? */ *p)) {

      compiler__Table_add_field(p->table, typ.name, field_name, field_type,
                                is_mut, attr, access_mod);
    };

    ;
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

  if (!is_c) {

    if (!did_gen_something) {

      if (compiler__Parser_first_pass(&/* ? */ *p)) {

        compiler__Table_add_field(p->table, typ.name, tos3(""),
                                  tos3("EMPTY_STRUCT_DECLARATION"), 0, tos3(""),
                                  compiler__compiler__AccessMod_private);
      };
    };
  };

  ;
}
string compiler__Parser_struct_init(compiler__Parser *p, string typ) {

  p->is_struct_init = 1;

  compiler__Type t = compiler__Table_find_type(&/* ? */ *p->table, typ);

  if (!t.is_public && string_ne(t.mod, p->mod)) {

    compiler__Parser_warn(
        p, _STR("type `%.*s` is private", t.name.len, t.name.str));
  };

  if (compiler__Parser_gen_struct_init(p, typ, t)) {

    return typ;
  };

  strings__Builder_cut(&/* ? */ p->scanner->fmt_out, typ.len);

  bool ptr = string_contains(typ, tos3("*"));

  bool did_gen_something = 0;

  array_string inited_fields = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  compiler__TokenKind peek = compiler__Parser_peek(&/* ? */ *p);

  if (peek == compiler__compiler__TokenKind_colon ||
      p->tok == compiler__compiler__TokenKind_rcbr) {

    while (p->tok != compiler__compiler__TokenKind_rcbr) {

      string field =
          (string_ne(typ, tos3("Option")))
              ? (compiler__Table_var_cgen_name(&/* ? */ *p->table,
                                               compiler__Parser_check_name(p)))
              : (compiler__Parser_check_name(p));

      if (!compiler__Parser_first_pass(&/* ? */ *p) &&
          !compiler__Type_has_field(&/* ? */ t, field)) {

        compiler__Parser_error(p, _STR("`%.*s` has no field `%.*s`", t.name.len,
                                       t.name.str, field.len, field.str));
      };

      if ((_IN(string, (field), inited_fields))) {

        compiler__Parser_error(
            p, _STR("already initialized field `%.*s` in `%.*s`", field.len,
                    field.str, t.name.len, t.name.str));
      };

      Option_compiler__Var tmp7 = compiler__Type_find_field(&/* ? */ t, field);
      compiler__Var f;
      if (!tmp7.ok) {
        string err = tmp7.error;
        int errcode = tmp7.ecode;

        compiler__Parser_error(p, _STR("no such field: \"%.*s\" in type %.*s",
                                       field.len, field.str, typ.len, typ.str));

        break;
      }
      f = *(compiler__Var *)tmp7.data;
      ;

      _PUSH(&inited_fields, (/*typ = array_string   tmp_typ=string*/ field),
            tmp8, string);

      compiler__Parser_gen_struct_field_init(p, field);

      compiler__Parser_check(p, compiler__compiler__TokenKind_colon);

      ;

      p->expected_type = f.typ;

      compiler__Parser_check_types(p, compiler__Parser_bool_expression(p),
                                   f.typ);

      if (p->tok == compiler__compiler__TokenKind_comma) {

        compiler__Parser_next(p);
      };

      if (p->tok != compiler__compiler__TokenKind_rcbr) {

        compiler__Parser_gen(p, tos3(","));
      };

      ;

      did_gen_something = 1;
    };

    if (t.fields.len != inited_fields.len && inited_fields.len > 0) {

      compiler__Parser_gen(p, tos3(","));
    };

    array_compiler__Var tmp9 = t.fields;
    for (int i = 0; i < tmp9.len; i++) {
      compiler__Var field = ((compiler__Var *)tmp9.data)[i];

      string sanitized_name =
          (string_ne(typ, tos3("Option")))
              ? (compiler__Table_var_cgen_name(&/* ? */ *p->table, field.name))
              : (field.name);

      if ((_IN(string, (sanitized_name), inited_fields))) {

        continue;
      };

      string field_typ = field.typ;

      if (!p->builtin_mod && string_ends_with(field_typ, tos3("*")) &&
          string_contains(field_typ, tos3("Cfg"))) {

        compiler__Parser_error(
            p, _STR("pointer field `%.*s.%.*s` must be initialized", typ.len,
                    typ.str, field.name.len, field.name.str));
      };

      if (string_starts_with(field_typ, tos3("map_"))) {

        compiler__Parser_gen_struct_field_init(p, sanitized_name);

        compiler__Parser_gen_empty_map(p,
                                       string_substr2(field_typ, 4, -1, true));

        _PUSH(&inited_fields,
              (/*typ = array_string   tmp_typ=string*/ sanitized_name), tmp12,
              string);

        if (i != t.fields.len - 1) {

          compiler__Parser_gen(p, tos3(","));
        };

        did_gen_something = 1;

        continue;
      };

      string def_val = compiler__type_default(field_typ);

      if (string_ne(def_val, tos3("")) && string_ne(def_val, tos3("{0}"))) {

        compiler__Parser_gen_struct_field_init(p, sanitized_name);

        compiler__Parser_gen(p, def_val);

        if (i != t.fields.len - 1) {

          compiler__Parser_gen(p, tos3(","));
        };

        did_gen_something = 1;
      };
    };

  } else {

    compiler__Type T = compiler__Table_find_type(&/* ? */ *p->table, typ);

    if (T.fields.len == 0 && string_ne(T.parent, tos3(""))) {

      T = compiler__Table_find_type(&/* ? */ *p->table, T.parent);
    };

    array_compiler__Var tmp13 = T.fields;
    for (int i = 0; i < tmp13.len; i++) {
      compiler__Var ffield = ((compiler__Var *)tmp13.data)[i];

      string expr_typ = compiler__Parser_bool_expression(p);

      if (!compiler__Parser_check_types_no_throw(p, expr_typ, ffield.typ)) {

        compiler__Parser_error(
            p, _STR("field value #%d `%.*s` has type `%.*s`, got `%.*s` ",
                    i + 1, ffield.name.len, ffield.name.str, ffield.typ.len,
                    ffield.typ.str, expr_typ.len, expr_typ.str));
      };

      if (i < T.fields.len - 1) {

        if (p->tok != compiler__compiler__TokenKind_comma) {

          compiler__Parser_error(
              p, _STR("too few values in `%.*s` literal (%d instead of %d)",
                      typ.len, typ.str, i + 1, T.fields.len));
        };

        compiler__Parser_gen(p, tos3(","));

        compiler__Parser_next(p);
      };
    };

    if (p->tok == compiler__compiler__TokenKind_comma) {

      compiler__Parser_next(p);
    };

    if (p->tok != compiler__compiler__TokenKind_rcbr) {

      compiler__Parser_error(
          p, _STR("too many fields initialized: `%.*s` has %d field(s)",
                  typ.len, typ.str, T.fields.len));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    compiler__Parser_gen(p, tos3("EMPTY_STRUCT_INITIALIZATION"));
  };

  compiler__Parser_gen(p, tos3("}"));

  if (ptr && !p->is_js) {

    compiler__Parser_gen(p, _STR(", sizeof(%.*s))", t.name.len, t.name.str));
  };

  compiler__Parser_check(p, compiler__compiler__TokenKind_rcbr);

  p->is_struct_init = 0;

  p->is_c_struct_init = 0;

  return typ;
}
string compiler__Fn_str(compiler__Fn f) {

  compiler__Table t = (compiler__Table){
      .typesmap = new_map(1, sizeof(compiler__Type)),
      .consts = new_array(0, 1, sizeof(compiler__Var)),
      .fns = new_map(1, sizeof(compiler__Fn)),
      .obf_ids = new_map(1, sizeof(int)),
      .modules = new_array(0, 1, sizeof(string)),
      .imports = new_array(0, 1, sizeof(string)),
      .cflags = new_array(0, 1, sizeof(compiler__CFlag)),
      .fn_cnt = 0,
      .obfuscate = 0,
      .varg_access = new_array(0, 1, sizeof(compiler__VargAccess))};

  string str_args = compiler__Fn_str_args(
      &/* ? */ f, &/*112 EXP:"compiler__Table*" GOT:"compiler__Table" */ t);

  return _STR("%.*s(%.*s) %.*s", f.name.len, f.name.str, str_args.len,
              str_args.str, f.typ.len, f.typ.str);
}
string compiler__Table_debug_fns(compiler__Table *t) {

  strings__Builder s = strings__new_builder(1000);

  map_compiler__Fn tmp1 = t->fns;
  array_string keys_tmp1 = map_keys(&tmp1);
  for (int l = 0; l < keys_tmp1.len; l++) {
    string _ = ((string *)keys_tmp1.data)[l];
    compiler__Fn f = {0};
    map_get(tmp1, _, &f);

    strings__Builder_writeln(&/* ? */ s, f.name);
  };

  return strings__Builder_str(s);
}
bool compiler__is_number_type(string typ) {

  return (_IN(string, (typ), compiler__integer_types)) ||
         (_IN(string, (typ), compiler__float_types));
}
bool compiler__is_integer_type(string typ) {

  return (_IN(string, (typ), compiler__integer_types));
}
bool compiler__is_float_type(string typ) {

  return (_IN(string, (typ), compiler__float_types));
}
bool compiler__is_primitive_type(string typ) {

  return compiler__is_number_type(typ) || string_eq(typ, tos3("string"));
}
compiler__Table *compiler__new_table(bool obfuscate) {

  compiler__Table *t = (compiler__Table *)memdup(
      &(compiler__Table){.obfuscate = obfuscate,
                         .typesmap = new_map(1, sizeof(compiler__Type)),
                         .consts = new_array(0, 1, sizeof(compiler__Var)),
                         .fns = new_map(1, sizeof(compiler__Fn)),
                         .obf_ids = new_map(1, sizeof(int)),
                         .modules = new_array(0, 1, sizeof(string)),
                         .imports = new_array(0, 1, sizeof(string)),
                         .cflags = new_array(0, 1, sizeof(compiler__CFlag)),
                         .fn_cnt = 0,
                         .varg_access =
                             new_array(0, 1, sizeof(compiler__VargAccess))},
      sizeof(compiler__Table));

  compiler__Table_register_builtin(t, tos3("int"));

  compiler__Table_register_builtin(t, tos3("size_t"));

  compiler__Table_register_type_with_parent(t, tos3("i8"), tos3("int"));

  compiler__Table_register_type_with_parent(t, tos3("byte"), tos3("int"));

  compiler__Table_register_type_with_parent(t, tos3("char"), tos3("int"));

  compiler__Table_register_type_with_parent(t, tos3("i16"), tos3("int"));

  compiler__Table_register_type_with_parent(t, tos3("u16"), tos3("u32"));

  compiler__Table_register_type_with_parent(t, tos3("u32"), tos3("int"));

  compiler__Table_register_type_with_parent(t, tos3("i64"), tos3("int"));

  compiler__Table_register_type_with_parent(t, tos3("u64"), tos3("u32"));

  compiler__Table_register_builtin(t, tos3("byteptr"));

  compiler__Table_register_builtin(t, tos3("intptr"));

  compiler__Table_register_builtin(t, tos3("f32"));

  compiler__Table_register_builtin(t, tos3("f64"));

  compiler__Table_register_builtin(t, tos3("rune"));

  compiler__Table_register_builtin(t, tos3("bool"));

  compiler__Table_register_builtin(t, tos3("void"));

  compiler__Table_register_builtin(t, tos3("voidptr"));

  compiler__Table_register_builtin(t, tos3("va_list"));

  array_string tmp2 = compiler__reserved_type_param_names;
  for (int tmp3 = 0; tmp3 < tmp2.len; tmp3++) {
    string c = ((string *)tmp2.data)[tmp3];

    compiler__Table_register_builtin(t, c);
  };

  compiler__Table_register_const(t, tos3("stdin"), tos3("int"), tos3("main"),
                                 1);

  compiler__Table_register_const(t, tos3("stdout"), tos3("int"), tos3("main"),
                                 1);

  compiler__Table_register_const(t, tos3("stderr"), tos3("int"), tos3("main"),
                                 1);

  compiler__Table_register_const(t, tos3("errno"), tos3("int"), tos3("main"),
                                 1);

  compiler__Table_register_type_with_parent(t, tos3("map_string"), tos3("map"));

  compiler__Table_register_type_with_parent(t, tos3("map_int"), tos3("map"));

  return t;
}
string compiler__Table_var_cgen_name(compiler__Table *t, string name) {

  if ((_IN(string, (name), compiler__CReserved))) {

    return _STR("v_%.*s", name.len, name.str);

  } else {

    return name;
  };
}
void compiler__Table_register_module(compiler__Table *t, string mod) {

  if ((_IN(string, (mod), t->modules))) {

    return;
  };

  _PUSH(&t->modules, (/*typ = array_string   tmp_typ=string*/ mod), tmp4,
        string);
}
void compiler__Parser_register_array(compiler__Parser *p, string typ) {

  if (string_contains(typ, tos3("*"))) {

    printf("bad arr %.*s\n", typ.len, typ.str);

    return;
  };

  if (!compiler__Table_known_type(&/* ? */ *p->table, typ)) {

    compiler__Parser_register_type_with_parent(p, typ, tos3("array"));

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR("typedef array %.*s;",
                                                        typ.len, typ.str)),
          tmp5, string);
  };
}
void compiler__Parser_register_map(compiler__Parser *p, string typ) {

  if (string_contains(typ, tos3("*"))) {

    printf("bad map %.*s\n", typ.len, typ.str);

    return;
  };

  if (!compiler__Table_known_type(&/* ? */ *p->table, typ)) {

    compiler__Parser_register_type_with_parent(p, typ, tos3("map"));

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR("typedef map %.*s;",
                                                        typ.len, typ.str)),
          tmp6, string);
  };
}
bool compiler__Table_known_mod(compiler__Table *table, string mod) {

  return (_IN(string, (mod), table->modules));
}
void compiler__Table_register_const(compiler__Table *t, string name, string typ,
                                    string mod, bool is_pub) {

  _PUSH(&t->consts,
        (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ (compiler__Var){
            .name = name,
            .typ = typ,
            .is_const = 1,
            .mod = mod,
            .idx = -1,
            .is_public = is_pub,
            .is_arg = 0,
            .args = new_array(0, 1, sizeof(compiler__Var)),
            .attr = tos3(""),
            .is_mut = 0,
            .is_alloc = 0,
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .parent_fn = tos3(""),
            .is_global = 0,
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
            .line_nr = 0,
            .token_idx = 0,
            .is_for_var = 0,
        }),
        tmp7, compiler__Var);
}
void compiler__Parser_register_global(compiler__Parser *p, string name,
                                      string typ) {

  _PUSH(&p->table->consts,
        (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ (compiler__Var){
            .name = name,
            .typ = typ,
            .is_const = 1,
            .is_global = 1,
            .mod = p->mod,
            .is_mut = 1,
            .idx = -1,
            .is_arg = 0,
            .args = new_array(0, 1, sizeof(compiler__Var)),
            .attr = tos3(""),
            .is_alloc = 0,
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .parent_fn = tos3(""),
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
            .line_nr = 0,
            .token_idx = 0,
            .is_for_var = 0,
            .is_public = 0}),
        tmp8, compiler__Var);
}
void compiler__Table_register_fn(compiler__Table *t, compiler__Fn new_fn) {

  map_set(&t->fns, new_fn.name, &(compiler__Fn[]){new_fn});
}
bool compiler__Table_known_type(compiler__Table *table, string typ_) {

  string typ = typ_;

  if (string_ends_with(typ, tos3("*")) && !string_contains(typ, tos3(" "))) {

    typ = string_substr2(typ, 0, typ.len - 1, false);
  };

  compiler__Type tmp11 = {0};
  bool tmp12 = map_get(/*table.v : 339*/ table->typesmap, typ, &tmp11);

  compiler__Type t = tmp11;

  return t.name.len > 0 && !t.is_placeholder;
}
bool compiler__Table_known_type_fast(compiler__Table *table,
                                     compiler__Type *t) {

  return string_ne(t->name, tos3("")) && !t->is_placeholder;
}
Option_compiler__Fn compiler__Table_find_fn(compiler__Table *t, string name) {

  compiler__Fn tmp13 = {0};
  bool tmp14 = map_get(/*table.v : 348*/ t->fns, name, &tmp13);

  compiler__Fn f = tmp13;

  if (f.name.str != 0) {

    compiler__Fn tmp15 = OPTION_CAST(compiler__Fn)(f);
    return opt_ok(&tmp15, sizeof(compiler__Fn));
  };

  return opt_none();
}
Option_compiler__Fn compiler__Table_find_fn_is_script(compiler__Table *t,
                                                      string name,
                                                      bool is_script) {

  compiler__Fn tmp16 = {0};
  bool tmp17 = map_get(/*table.v : 356*/ t->fns, name, &tmp16);

  compiler__Fn f = tmp16;

  if (f.name.str != 0) {

    compiler__Fn tmp18 = OPTION_CAST(compiler__Fn)(f);
    return opt_ok(&tmp18, sizeof(compiler__Fn));
  };

  if (is_script) {

    printf("trying replace %.*s\n", name.len, name.str);

    compiler__Fn tmp19 = {0};
    bool tmp20 =
        map_get(/*table.v : 363*/ t->fns,
                string_replace(name, tos3("main__"), tos3("os__")), &tmp19);

    f = tmp19;

    if (f.name.str != 0) {

      compiler__Fn tmp21 = OPTION_CAST(compiler__Fn)(f);
      return opt_ok(&tmp21, sizeof(compiler__Fn));
    };
  };

  return opt_none();
}
bool compiler__Table_known_fn(compiler__Table *t, string name) {

  Option_compiler__Fn tmp22 = compiler__Table_find_fn(&/* ? */ *t, name);
  if (!tmp22.ok) {
    string err = tmp22.error;
    int errcode = tmp22.ecode;

    return 0;
  };

  return 1;
}
bool compiler__Table_known_const(compiler__Table *t, string name) {

  Option_compiler__Var tmp23 = compiler__Table_find_const(&/* ? */ *t, name);
  if (!tmp23.ok) {
    string err = tmp23.error;
    int errcode = tmp23.ecode;

    return 0;
  };

  return 1;
}
void compiler__Table_register_builtin(compiler__Table *t, string typ) {

  if (typ.len == 0) {

    return;
  };

  if ((_IN_MAP((typ), t->typesmap))) {

    return;
  };

  map_set(&t->typesmap, typ,
          &(compiler__Type[]){
              (compiler__Type){.name = typ,
                               .is_public = 1,
                               .mod = tos3(""),
                               .fields = new_array(0, 1, sizeof(compiler__Var)),
                               .methods = new_array(0, 1, sizeof(compiler__Fn)),
                               .parent = tos3(""),
                               .is_c = 0,
                               .enum_vals = new_array(0, 1, sizeof(string)),
                               .gen_types = new_array(0, 1, sizeof(string)),
                               .is_placeholder = 0,
                               .gen_str = 0}});
}
void compiler__Parser_register_type_with_parent(compiler__Parser *p,
                                                string strtyp, string parent) {

  compiler__Type typ =
      (compiler__Type){.name = strtyp,
                       .parent = parent,
                       .mod = p->mod,
                       .is_public = 1,
                       .fields = new_array(0, 1, sizeof(compiler__Var)),
                       .methods = new_array(0, 1, sizeof(compiler__Fn)),
                       .is_c = 0,
                       .enum_vals = new_array(0, 1, sizeof(string)),
                       .gen_types = new_array(0, 1, sizeof(string)),
                       .is_placeholder = 0,
                       .gen_str = 0};

  compiler__Table_register_type2(p->table, typ);
}
void compiler__Table_register_type_with_parent(compiler__Table *t, string typ,
                                               string parent) {

  if (typ.len == 0) {

    return;
  };

  map_set(&t->typesmap, typ,
          &(compiler__Type[]){
              (compiler__Type){.name = typ,
                               .parent = parent,
                               .is_public = 1,
                               .mod = tos3(""),
                               .fields = new_array(0, 1, sizeof(compiler__Var)),
                               .methods = new_array(0, 1, sizeof(compiler__Fn)),
                               .is_c = 0,
                               .enum_vals = new_array(0, 1, sizeof(string)),
                               .gen_types = new_array(0, 1, sizeof(string)),
                               .is_placeholder = 0,
                               .gen_str = 0}});
}
void compiler__Table_register_type2(compiler__Table *t, compiler__Type typ) {

  if (typ.name.len == 0) {

    return;
  };

  map_set(&t->typesmap, typ.name, &(compiler__Type[]){typ});
}
void compiler__Table_rewrite_type(compiler__Table *t, compiler__Type typ) {

  if (typ.name.len == 0) {

    return;
  };

  map_set(&t->typesmap, typ.name, &(compiler__Type[]){typ});
}
void compiler__Table_add_field(compiler__Table *table, string type_name,
                               string field_name, string field_type,
                               bool is_mut, string attr,
                               compiler__AccessMod access_mod) {

  if (string_eq(type_name, tos3(""))) {

    print_backtrace();

    compiler__verror(tos3("add_field: empty type"));
  };

  compiler__Type tmp24 = {0};
  bool tmp25 = map_get(/*table.v : 432*/ table->typesmap, type_name, &tmp24);

  compiler__Type t = tmp24;

  _PUSH(&t.fields,
        (/*typ = array_compiler__Var   tmp_typ=compiler__Var*/ (compiler__Var){
            .name = field_name,
            .typ = field_type,
            .is_mut = is_mut,
            .attr = attr,
            .parent_fn = type_name,
            .access_mod = access_mod,
            .idx = 0,
            .is_arg = 0,
            .is_const = 0,
            .args = new_array(0, 1, sizeof(compiler__Var)),
            .is_alloc = 0,
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .mod = tos3(""),
            .is_global = 0,
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
            .line_nr = 0,
            .token_idx = 0,
            .is_for_var = 0,
            .is_public = 0}),
        tmp26, compiler__Var);

  map_set(&table->typesmap, type_name, &(compiler__Type[]){t});
}
bool compiler__Type_has_field(compiler__Type *t, string name) {

  Option_compiler__Var tmp27 = compiler__Type_find_field(&/* ? */ *t, name);
  if (!tmp27.ok) {
    string err = tmp27.error;
    int errcode = tmp27.ecode;

    return 0;
  };

  return 1;
}
bool compiler__Type_has_enum_val(compiler__Type *t, string name) {

  return (_IN(string, (name), t->enum_vals));
}
Option_compiler__Var compiler__Type_find_field(compiler__Type *t, string name) {

  array_compiler__Var tmp28 = t->fields;
  for (int tmp29 = 0; tmp29 < tmp28.len; tmp29++) {
    compiler__Var field = ((compiler__Var *)tmp28.data)[tmp29];

    if (string_eq(field.name, name)) {

      compiler__Var tmp30 = OPTION_CAST(compiler__Var)(field);
      return opt_ok(&tmp30, sizeof(compiler__Var));
    };
  };

  return opt_none();
}
bool compiler__Table_type_has_field(compiler__Table *table, compiler__Type *typ,
                                    string name) {

  Option_compiler__Var tmp31 =
      compiler__Table_find_field(&/* ? */ *table, typ, name);
  if (!tmp31.ok) {
    string err = tmp31.error;
    int errcode = tmp31.ecode;

    return 0;
  };

  return 1;
}
Option_compiler__Var compiler__Table_find_field(compiler__Table *table,
                                                compiler__Type *typ,
                                                string name) {

  array_compiler__Var tmp32 = typ->fields;
  for (int tmp33 = 0; tmp33 < tmp32.len; tmp33++) {
    compiler__Var field = ((compiler__Var *)tmp32.data)[tmp33];

    if (string_eq(field.name, name)) {

      compiler__Var tmp34 = OPTION_CAST(compiler__Var)(field);
      return opt_ok(&tmp34, sizeof(compiler__Var));
    };
  };

  if (string_ne(typ->parent, tos3(""))) {

    compiler__Type parent =
        compiler__Table_find_type(&/* ? */ *table, typ->parent);

    array_compiler__Var tmp35 = parent.fields;
    for (int tmp36 = 0; tmp36 < tmp35.len; tmp36++) {
      compiler__Var field = ((compiler__Var *)tmp35.data)[tmp36];

      if (string_eq(field.name, name)) {

        compiler__Var tmp37 = OPTION_CAST(compiler__Var)(field);
        return opt_ok(&tmp37, sizeof(compiler__Var));
      };
    };
  };

  return opt_none();
}
void compiler__Parser_add_method(compiler__Parser *p, string type_name,
                                 compiler__Fn f) {

  if (!compiler__Parser_first_pass(&/* ? */ *p) &&
      string_ne(f.name, tos3("str"))) {

    return;
  };

  if (string_eq(type_name, tos3(""))) {

    print_backtrace();

    compiler__verror(tos3("add_method: empty type"));
  };

  compiler__Type tmp38 = {0};
  bool tmp39 = map_get(/*table.v : 493*/ p->table->typesmap, type_name, &tmp38);

  compiler__Type t = tmp38;

  if (string_ne(f.name, tos3("str")) && (_IN(compiler__Fn, (f), t.methods))) {

    compiler__Parser_error(p, _STR("redefinition of method `%.*s.%.*s`",
                                   type_name.len, type_name.str, f.name.len,
                                   f.name.str));
  };

  _PUSH(&t.methods, (/*typ = array_compiler__Fn   tmp_typ=compiler__Fn*/ f),
        tmp40, compiler__Fn);

  map_set(&p->table->typesmap, type_name, &(compiler__Type[]){t});
}
bool compiler__Type_has_method(compiler__Type *t, string name) {

  Option_compiler__Fn tmp41 = compiler__Type_find_method(&/* ? */ *t, name);
  if (!tmp41.ok) {
    string err = tmp41.error;
    int errcode = tmp41.ecode;

    return 0;
  };

  return 1;
}
bool compiler__Table_type_has_method(compiler__Table *table,
                                     compiler__Type *typ, string name) {

  Option_compiler__Fn tmp42 =
      compiler__Table_find_method(&/* ? */ *table, typ, name);
  if (!tmp42.ok) {
    string err = tmp42.error;
    int errcode = tmp42.ecode;

    return 0;
  };

  return 1;
}
Option_compiler__Fn compiler__Table_find_method(compiler__Table *table,
                                                compiler__Type *typ,
                                                string name) {

  compiler__Type tmp43 = {0};
  bool tmp44 = map_get(/*table.v : 512*/ table->typesmap, typ->name, &tmp43);

  compiler__Type t = tmp43;

  array_compiler__Fn tmp45 = t.methods;
  for (int tmp46 = 0; tmp46 < tmp45.len; tmp46++) {
    compiler__Fn method = ((compiler__Fn *)tmp45.data)[tmp46];

    if (string_eq(method.name, name)) {

      compiler__Fn tmp47 = OPTION_CAST(compiler__Fn)(method);
      return opt_ok(&tmp47, sizeof(compiler__Fn));
    };
  };

  if (string_ne(typ->parent, tos3(""))) {

    compiler__Type parent =
        compiler__Table_find_type(&/* ? */ *table, typ->parent);

    array_compiler__Fn tmp48 = parent.methods;
    for (int tmp49 = 0; tmp49 < tmp48.len; tmp49++) {
      compiler__Fn method = ((compiler__Fn *)tmp48.data)[tmp49];

      if (string_eq(method.name, name)) {

        compiler__Fn tmp50 = OPTION_CAST(compiler__Fn)(method);
        return opt_ok(&tmp50, sizeof(compiler__Fn));
      };
    };

    return opt_none();
  };

  return opt_none();
}
Option_compiler__Fn compiler__Type_find_method(compiler__Type *t, string name) {

  array_compiler__Fn tmp51 = t->methods;
  for (int tmp52 = 0; tmp52 < tmp51.len; tmp52++) {
    compiler__Fn method = ((compiler__Fn *)tmp51.data)[tmp52];

    if (string_eq(method.name, name)) {

      compiler__Fn tmp53 = OPTION_CAST(compiler__Fn)(method);
      return opt_ok(&tmp53, sizeof(compiler__Fn));
    };
  };

  return opt_none();
}
compiler__Type compiler__Parser_find_type(compiler__Parser *p, string name) {

  compiler__Type typ = compiler__Table_find_type(&/* ? */ *p->table, name);

  if (string_eq(typ.name, tos3(""))) {

    return compiler__Table_find_type(
        &/* ? */ *p->table, compiler__Parser_prepend_mod(&/* ? */ *p, name));
  };

  return typ;
}
compiler__Type compiler__Table_find_type(compiler__Table *t, string name_) {

  string name = name_;

  if (string_ends_with(name, tos3("*")) && !string_contains(name, tos3(" "))) {

    name = string_substr2(name, 0, name.len - 1, false);
  };

  if (!((_IN_MAP((name), t->typesmap)))) {

    return (compiler__Type){.mod = tos3(""),
                            .name = tos3(""),
                            .is_public = 0,
                            .fields = new_array(0, 1, sizeof(compiler__Var)),
                            .methods = new_array(0, 1, sizeof(compiler__Fn)),
                            .parent = tos3(""),
                            .is_c = 0,
                            .enum_vals = new_array(0, 1, sizeof(string)),
                            .gen_types = new_array(0, 1, sizeof(string)),
                            .is_placeholder = 0,
                            .gen_str = 0};
  };

  compiler__Type tmp56 = {0};
  bool tmp57 = map_get(/*table.v : 569*/ t->typesmap, name, &tmp56);

  return tmp56;
}
bool compiler__Parser_check_types2(compiler__Parser *p, string got_,
                                   string expected_, bool throw) {

  string got = got_;

  string expected = expected_;

  if (p->pref->translated) {

    return 1;
  };

  if (string_eq(got, expected)) {

    return 1;
  };

  if (string_eq(expected, tos3("_ANYTYPE_"))) {

    p->cur_fn.typ = got;

    return 1;
  };

  if (string_starts_with(expected, tos3("varg_"))) {

    expected = string_substr2(expected, 5, -1, true);
  };

  if (string_starts_with(got, tos3("varg_"))) {

    got = string_substr2(got, 5, -1, true);
  };

  if (string_eq(got, tos3("int")) && string_eq(expected, tos3("f32"))) {

    return 1;
  };

  if (string_eq(got, tos3("int")) && string_eq(expected, tos3("f64"))) {

    return 1;
  };

  if (string_eq(got, tos3("f64")) && string_eq(expected, tos3("f32"))) {

    return 1;
  };

  if (string_eq(got, tos3("f32")) && string_eq(expected, tos3("f64"))) {

    return 1;
  };

  if (string_eq(got, tos3("int")) && string_eq(expected, tos3("i64"))) {

    return 1;
  };

  if (string_eq(got, tos3("void*")) &&
      string_starts_with(expected, tos3("fn "))) {

    return 1;
  };

  if (string_starts_with(got, tos3("[")) &&
      string_eq(expected, tos3("byte*"))) {

    return 1;
  };

  if (string_eq(got, tos3("void*")) || string_eq(expected, tos3("void*"))) {

    return 1;
  };

  if (string_eq(got, tos3("int")) && string_eq(expected, tos3("byte"))) {

    return 1;
  };

  if (string_eq(got, tos3("byteptr")) && string_eq(expected, tos3("byte*"))) {

    return 1;
  };

  if (string_eq(got, tos3("byte*")) && string_eq(expected, tos3("byteptr"))) {

    return 1;
  };

  if (string_eq(got, tos3("int")) && string_eq(expected, tos3("byte*"))) {

    return 1;
  };

  if (string_eq(got, tos3("int")) && string_eq(expected, tos3("byteptr"))) {

    return 1;
  };

  if (string_eq(got, tos3("Option")) &&
      string_starts_with(expected, tos3("Option_"))) {

    return 1;
  };

  if (string_eq(got, tos3("array")) &&
      string_starts_with(expected, tos3("array_"))) {

    return 1;
  };

  if (string_starts_with(expected, tos3("Option_")) &&
      string_ends_with(expected, got)) {

    return 1;
  };

  if (string_ends_with(expected, tos3("*")) && string_eq(got, tos3("int"))) {

    return 1;
  };

  if (string_starts_with(got, tos3("fn ")) &&
      (string_ends_with(expected, tos3("fn")) ||
       string_ends_with(expected, tos3("Fn")))) {

    return 1;
  };

  if (string_eq(expected, tos3("void*")) && string_eq(got, tos3("int"))) {

    return 1;
  };

  if (compiler__is_integer_type(got) && compiler__is_number_type(expected) &&
      p->is_const_literal) {

    return 1;
  };

  if (string_eq(expected, tos3("integer"))) {

    if (compiler__is_integer_type(got)) {

      return 1;

    } else {

      compiler__Parser_error(p, _STR("expected type `%.*s`, but got `%.*s`",
                                     expected.len, expected.str, got.len,
                                     got.str));
    };
  };

  expected = string_replace(expected, tos3("*"), tos3(""));

  got = string_replace(got, tos3("*"), tos3(""));

  if (string_ne(got, expected)) {

    if (string_ends_with(expected, tos3("er"))) {

      if (compiler__Parser_satisfies_interface(p, expected, got, throw)) {

        return 1;
      };
    };

    if (!throw) {

      return 0;

    } else {

      compiler__Parser_error(p, _STR("expected type `%.*s`, but got `%.*s`",
                                     expected.len, expected.str, got.len,
                                     got.str));
    };
  };

  return 1;
}
bool compiler__Parser_check_types(compiler__Parser *p, string got,
                                  string expected) {

  if (compiler__Parser_first_pass(&/* ? */ *p)) {

    return 1;
  };

  return compiler__Parser_check_types2(p, got, expected, 1);
}
bool compiler__Parser_check_types_no_throw(compiler__Parser *p, string got,
                                           string expected) {

  return compiler__Parser_check_types2(p, got, expected, 0);
}
void compiler__Parser_check_types_with_token_index(compiler__Parser *p,
                                                   string got, string expected,
                                                   int var_token_idx) {

  if (!compiler__Parser_check_types2(p, got, expected, 0)) {

    compiler__Parser_error_with_token_index(
        p,
        _STR("expected type `%.*s`, but got `%.*s`", expected.len, expected.str,
             got.len, got.str),
        var_token_idx);
  };
}
bool compiler__Parser_satisfies_interface(compiler__Parser *p,
                                          string interface_name, string _typ,
                                          bool throw) {

  compiler__Type int_typ =
      compiler__Table_find_type(&/* ? */ *p->table, interface_name);

  compiler__Type typ = compiler__Table_find_type(&/* ? */ *p->table, _typ);

  array_compiler__Fn tmp62 = int_typ.methods;
  for (int tmp63 = 0; tmp63 < tmp62.len; tmp63++) {
    compiler__Fn method = ((compiler__Fn *)tmp62.data)[tmp63];

    if (!compiler__Type_has_method(&/* ? */ typ, method.name)) {

      compiler__Parser_error(
          p, _STR("Type \"%.*s\" doesn\'t satisfy interface \"%.*s\" (method "
                  "\"%.*s\" is not implemented)",
                  _typ.len, _typ.str, interface_name.len, interface_name.str,
                  method.name.len, method.name.str));

      return 0;
    };
  };

  return 1;
}
bool compiler__Table_is_interface(compiler__Table *table, string name) {

  if (!((_IN_MAP((name), table->typesmap)))) {

    return 0;
  };

  compiler__Type tmp64 = {0};
  bool tmp65 = map_get(/*table.v : 744*/ table->typesmap, name, &tmp64);

  compiler__Type t = tmp64;

  return t.cat == compiler__compiler__TypeCategory_interface_;
}
bool compiler__Table_main_exists(compiler__Table *t) {

  map_compiler__Fn tmp66 = t->fns;
  array_string keys_tmp66 = map_keys(&tmp66);
  for (int l = 0; l < keys_tmp66.len; l++) {
    string _ = ((string *)keys_tmp66.data)[l];
    compiler__Fn f = {0};
    map_get(tmp66, _, &f);

    if (string_eq(f.name, tos3("main__main"))) {

      return 1;
    };
  };

  return 0;
}
bool compiler__Table_has_at_least_one_test_fn(compiler__Table *t) {

  map_compiler__Fn tmp67 = t->fns;
  array_string keys_tmp67 = map_keys(&tmp67);
  for (int l = 0; l < keys_tmp67.len; l++) {
    string _ = ((string *)keys_tmp67.data)[l];
    compiler__Fn f = {0};
    map_get(tmp67, _, &f);

    if (string_starts_with(f.name, tos3("main__test_"))) {

      return 1;
    };
  };

  return 0;
}
Option_compiler__Var compiler__Table_find_const(compiler__Table *t,
                                                string name) {

  array_compiler__Var tmp68 = t->consts;
  for (int tmp69 = 0; tmp69 < tmp68.len; tmp69++) {
    compiler__Var c = ((compiler__Var *)tmp68.data)[tmp69];

    if (string_eq(c.name, name)) {

      compiler__Var tmp70 = OPTION_CAST(compiler__Var)(c);
      return opt_ok(&tmp70, sizeof(compiler__Var));
    };
  };

  return opt_none();
}
string compiler__Table_cgen_name_type_pair(compiler__Table *table, string name,
                                           string typ) {

  if (typ.len > 0 && string_at(typ, 0) == '[') {

    string tmp = string_all_after(typ, tos3("]"));

    string size = string_all_before(typ, tos3("]"));

    return _STR("%.*s %.*s  %.*s ]", tmp.len, tmp.str, name.len, name.str,
                size.len, size.str);

  } else if (string_starts_with(typ, tos3("fn ("))) {

    compiler__Type T = compiler__Table_find_type(&/* ? */ *table, typ);

    if (string_eq(T.name, tos3(""))) {

      eprintln(_STR("function type `%.*s` not found", typ.len, typ.str));

      v_exit(1);
    };

    string str_args = compiler__Fn_str_args(&/* ? */ T.func, table);

    return _STR("%.*s (*%.*s)( %.*s /*FFF*/ )", T.func.typ.len, T.func.typ.str,
                name.len, name.str, str_args.len, str_args.str);

  } else if (string_eq(typ, tos3("tm"))) {

    return _STR("struct /*TM*/ tm %.*s", name.len, name.str);
  };

  return _STR("%.*s %.*s", typ.len, typ.str, name.len, name.str);
}
bool compiler__is_valid_int_const(string val, string typ) {

  int x = v_string_int(val);

  string tmp73 = typ;

  if (string_eq(tmp73, tos3("byte"))) {

    return 0 <= x && x <= 255;

  } else if (string_eq(tmp73, tos3("u16"))) {

    return 0 <= x && x <= 65535;

  } else if (string_eq(tmp73, tos3("i8"))) {

    return -128 <= x && x <= 127;
  };

  return 1;
}
string compiler__Parser_typ_to_fmt(compiler__Parser *p, string typ, int level) {

  compiler__Type t = compiler__Table_find_type(&/* ? */ *p->table, typ);

  if (t.cat == compiler__compiler__TypeCategory_enum_) {

    return tos3("%d");
  };

  string tmp74 = typ;

  if (string_eq(tmp74, tos3("string"))) {

    return tos3("%.*s");

  } else if (string_eq(tmp74, tos3("ustring"))) {

    return tos3("%.*s");

  } else if ((string_eq(tmp74, tos3("byte"))) ||
             (string_eq(tmp74, tos3("bool"))) ||
             (string_eq(tmp74, tos3("int"))) ||
             (string_eq(tmp74, tos3("char"))) ||
             (string_eq(tmp74, tos3("byte"))) ||
             (string_eq(tmp74, tos3("i16"))) ||
             (string_eq(tmp74, tos3("i8")))) {

    return tos3("%d");

  } else if ((string_eq(tmp74, tos3("u16"))) ||
             (string_eq(tmp74, tos3("u32")))) {

    return tos3("%u");

  } else if ((string_eq(tmp74, tos3("f64"))) ||
             (string_eq(tmp74, tos3("f32")))) {

    return tos3("%f");

  } else if (string_eq(tmp74, tos3("i64"))) {

    return tos3("%lld");

  } else if (string_eq(tmp74, tos3("u64"))) {

    return tos3("%llu");

  } else if ((string_eq(tmp74, tos3("byte*"))) ||
             (string_eq(tmp74, tos3("byteptr")))) {

    return tos3("%s");

  } else if (string_eq(tmp74, tos3("void"))) {

    compiler__Parser_error(p, tos3("cannot interpolate this value"));

  } else // default:
  {

    if (string_ends_with(typ, tos3("*"))) {

      return tos3("%p");
    };
  };

  if (string_ne(t.parent, tos3("")) && level == 0) {

    return compiler__Parser_typ_to_fmt(p, t.parent, level + 1);
  };

  return tos3("");
}
string compiler__type_to_safe_str(string typ) {

  string r =
      string_replace(string_replace(string_replace(typ, tos3(" "), tos3("")),
                                    tos3("("), tos3("_")),
                     tos3(")"), tos3("_"));

  return r;
}
bool compiler__is_compile_time_const(string s_) {

  string s = string_trim_space(s_);

  if (string_eq(s, tos3(""))) {

    return 0;
  };

  if (string_contains(s, tos3("\'"))) {

    return 1;
  };

  string tmp75 = s;
  array_byte bytes_tmp75 = string_bytes(tmp75);
  ;
  for (int tmp76 = 0; tmp76 < tmp75.len; tmp76++) {
    byte c = ((byte *)bytes_tmp75.data)[tmp76];

    if (!((c >= '0' && c <= '9') || c == '.')) {

      return 0;
    };
  };

  return 1;
}
bool compiler__Type_contains_field_type(compiler__Type *t, string typ) {

  if (!byte_is_capital(string_at(t->name, 0))) {

    return 0;
  };

  array_compiler__Var tmp79 = t->fields;
  for (int tmp80 = 0; tmp80 < tmp79.len; tmp80++) {
    compiler__Var field = ((compiler__Var *)tmp79.data)[tmp80];

    if (string_eq(field.typ, typ)) {

      return 1;
    };
  };

  return 0;
}
string compiler__Parser_identify_typo(compiler__Parser *p, string name) {

  if (name.len < 2) {

    return tos3("");
  };

  string name_dotted =
      compiler__mod_gen_name_rev(string_replace(name, tos3("__"), tos3(".")));

  f32 min_match = 0.50;

  string output = tos3("");

  string n = compiler__Table_find_misspelled_imported_mod(
      &/* ? */ *p->table, name_dotted, p, min_match);

  if (n.len > 0) {

    output = string_add(output, _STR("\n  * module: `%.*s`", n.len, n.str));
  };

  n = compiler__Table_find_misspelled_const(&/* ? */ *p->table, name, p,
                                            min_match);

  if (string_ne(n, tos3(""))) {

    output = string_add(output, _STR("\n  * const: `%.*s`", n.len, n.str));
  };

  _V_MulRet_string_V_string _V_mret_typ_type_cat =
      compiler__Table_find_misspelled_type(&/* ? */ *p->table, name, p,
                                           min_match);
  string typ = _V_mret_typ_type_cat.var_0;
  string type_cat = _V_mret_typ_type_cat.var_1;

  if (typ.len > 0) {

    output = string_add(output, _STR("\n  * %.*s: `%.*s`", type_cat.len,
                                     type_cat.str, typ.len, typ.str));
  };

  n = compiler__Table_find_misspelled_fn(&/* ? */ *p->table, name, p,
                                         min_match);

  if (n.len > 0) {

    output = string_add(output, _STR("\n  * function: `%.*s`", n.len, n.str));
  };

  n = compiler__Parser_find_misspelled_local_var(&/* ? */ *p, name_dotted,
                                                 min_match);

  if (n.len > 0) {

    output = string_add(output, _STR("\n  * variable: `%.*s`", n.len, n.str));
  };

  return output;
}
f32 compiler__typo_compare_name_mod(string a, string b, string b_mod) {

  if (a.len - b.len > 2 || b.len - a.len > 2) {

    return 0;
  };

  int auidx = string_index(a, tos3("__"));

  int buidx = string_index(b, tos3("__"));

  string a_mod =
      (auidx != -1)
          ? (compiler__mod_gen_name_rev(string_substr2(a, 0, auidx, false)))
          : (tos3(""));

  string a_name =
      (auidx != -1) ? (string_substr2(a, auidx + 2, -1, true)) : (a);

  string b_name =
      (buidx != -1) ? (string_substr2(b, buidx + 2, -1, true)) : (b);

  if (a_mod.len > 0 && b_mod.len > 0 && string_ne(a_mod, b_mod)) {

    return 0;
  };

  return strings__dice_coefficient(a_name, b_name);
}
string compiler__Table_find_misspelled_fn(compiler__Table *table, string name,
                                          compiler__Parser *p, f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_fn = tos3("");

  map_compiler__Fn tmp87 = table->fns;
  array_string keys_tmp87 = map_keys(&tmp87);
  for (int l = 0; l < keys_tmp87.len; l++) {
    string _ = ((string *)keys_tmp87.data)[l];
    compiler__Fn f = {0};
    map_get(tmp87, _, &f);

    if (string_contains(f.name, tos3("__")) &&
        !compiler__Parser_is_mod_in_scope(&/* ? */ *p, f.mod)) {

      continue;
    };

    f32 c = compiler__typo_compare_name_mod(name, f.name, f.mod);

    if (f32_gt(c, closest)) {

      closest = c;

      closest_fn = compiler__mod_gen_name_rev(
          string_replace(f.name, tos3("__"), tos3(".")));
    };
  };

  return (f32_ge(closest, min_match)) ? (closest_fn) : (tos3(""));
}
string compiler__Table_find_misspelled_imported_mod(compiler__Table *table,
                                                    string name,
                                                    compiler__Parser *p,
                                                    f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_mod = tos3("");

  string n1 = (string_starts_with(name, tos3("main.")))
                  ? (string_substr2(name, 5, -1, true))
                  : (name);

  map_string tmp90 = p->import_table.imports;
  array_string keys_tmp90 = map_keys(&tmp90);
  for (int l = 0; l < keys_tmp90.len; l++) {
    string alias = ((string *)keys_tmp90.data)[l];
    string mod = tos3("");
    map_get(tmp90, alias, &mod);

    f32 c = compiler__typo_compare_name_mod(n1, alias, tos3(""));

    if (f32_gt(c, closest)) {

      closest = c;

      closest_mod =
          (string_eq(alias, mod))
              ? (alias)
              : (_STR("%.*s (%.*s)", alias.len, alias.str, mod.len, mod.str));
    };
  };

  return (f32_ge(closest, min_match)) ? (closest_mod) : (tos3(""));
}
string compiler__Table_find_misspelled_const(compiler__Table *table,
                                             string name, compiler__Parser *p,
                                             f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_const = tos3("");

  array_compiler__Var tmp91 = table->consts;
  for (int tmp92 = 0; tmp92 < tmp91.len; tmp92++) {
    compiler__Var cnst = ((compiler__Var *)tmp91.data)[tmp92];

    if (string_contains(cnst.name, tos3("__")) &&
        !compiler__Parser_is_mod_in_scope(&/* ? */ *p, cnst.mod)) {

      continue;
    };

    f32 c = compiler__typo_compare_name_mod(name, cnst.name, cnst.mod);

    if (f32_gt(c, closest)) {

      closest = c;

      closest_const = compiler__mod_gen_name_rev(
          string_replace(cnst.name, tos3("__"), tos3(".")));
    };
  };

  return (f32_ge(closest, min_match)) ? (closest_const) : (tos3(""));
}
_V_MulRet_string_V_string
compiler__Table_find_misspelled_type(compiler__Table *table, string name,
                                     compiler__Parser *p, f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_type = tos3("");

  string type_cat = tos3("");

  map_compiler__Type tmp93 = table->typesmap;
  array_string keys_tmp93 = map_keys(&tmp93);
  for (int l = 0; l < keys_tmp93.len; l++) {
    string _ = ((string *)keys_tmp93.data)[l];
    compiler__Type typ = {0};
    map_get(tmp93, _, &typ);

    if (string_contains(typ.name, tos3("__")) &&
        !compiler__Parser_is_mod_in_scope(&/* ? */ *p, typ.mod)) {

      continue;
    };

    f32 c = compiler__typo_compare_name_mod(name, typ.name, typ.mod);

    if (f32_gt(c, closest)) {

      closest = c;

      closest_type = compiler__mod_gen_name_rev(
          string_replace(typ.name, tos3("__"), tos3(".")));

      type_cat = compiler__type_cat_str(typ.cat);
    };
  };

  if (f32_ge(closest, min_match)) {

    return (_V_MulRet_string_V_string){.var_0 = closest_type,
                                       .var_1 = type_cat};
  };

  return (_V_MulRet_string_V_string){.var_0 = tos3(""), .var_1 = tos3("")};
}
string compiler__type_cat_str(compiler__TypeCategory tc) {

  compiler__TypeCategory tmp94 = tc;

  string tc_str =
      ((tmp94 == compiler__compiler__TypeCategory_builtin)
           ? (tos3("builtin"))
           : ((tmp94 == compiler__compiler__TypeCategory_struct_)
                  ? (tos3("struct"))
                  : ((tmp94 == compiler__compiler__TypeCategory_func)
                         ? (tos3("function"))
                         : ((tmp94 ==
                             compiler__compiler__TypeCategory_interface_)
                                ? (tos3("interface"))
                                : ((tmp94 ==
                                    compiler__compiler__TypeCategory_enum_)
                                       ? (tos3("enum"))
                                       : ((tmp94 ==
                                           compiler__compiler__TypeCategory_union_)
                                              ? (tos3("union"))
                                              : ((tmp94 ==
                                                  compiler__compiler__TypeCategory_c_struct)
                                                     ? (tos3("C struct"))
                                                     : ((tmp94 ==
                                                         compiler__compiler__TypeCategory_c_typedef)
                                                            ? (tos3(
                                                                  "C typedef"))
                                                            : ((tmp94 ==
                                                                compiler__compiler__TypeCategory_objc_interface)
                                                                   ? (tos3(
                                                                         "obj "
                                                                         "C "
                                                                         "inter"
                                                                         "fac"
                                                                         "e"))
                                                                   : ((tmp94 ==
                                                                       compiler__compiler__TypeCategory_array)
                                                                          ? (tos3(
                                                                                "array"))
                                                                          : ((tmp94 ==
                                                                              compiler__compiler__TypeCategory_alias)
                                                                                 ? (tos3(
                                                                                       "type alias"))
                                                                                 : (tos3(
                                                                                       "unknown")))))))))))));

  return tc_str;
}
map_int compiler__build_keys() {

  map_int res = new_map(1, sizeof(int));

  for (int t = ((int)(compiler__compiler__TokenKind_keyword_beg)) + 1;
       t < ((int)(compiler__compiler__TokenKind_keyword_end)); t++) {

    string key = (*(string *)array_get(compiler__TokenStr, t));

    map_set(&res, key, &(int[]){((int)(t))});
  };

  return res;
}
array_string compiler__build_token_str() {

  array_string s = array_repeat(
      new_array_from_c_array(1, 1, sizeof(string),
                             EMPTY_ARRAY_OF_ELEMS(string, 1){tos3("")}),
      compiler__NrTokens);

  array_set(&/*q*/ s, compiler__compiler__TokenKind_keyword_beg,
            &(string[]){tos3("")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_keyword_end,
            &(string[]){tos3("")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_eof,
            &(string[]){tos3("eof")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_name,
            &(string[]){tos3("name")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_number,
            &(string[]){tos3("number")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_str,
            &(string[]){tos3("STR")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_chartoken,
            &(string[]){tos3("char")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_plus,
            &(string[]){tos3("+")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_minus,
            &(string[]){tos3("-")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_mul,
            &(string[]){tos3("*")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_div,
            &(string[]){tos3("/")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_mod,
            &(string[]){tos3("%")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_xor,
            &(string[]){tos3("^")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_bit_not,
            &(string[]){tos3("~")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_pipe,
            &(string[]){tos3("|")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_hash,
            &(string[]){tos3("#")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_amp,
            &(string[]){tos3("&")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_inc,
            &(string[]){tos3("++")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_dec,
            &(string[]){tos3("--")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_and,
            &(string[]){tos3("&&")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_logical_or,
            &(string[]){tos3("||")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_not,
            &(string[]){tos3("!")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_dot,
            &(string[]){tos3(".")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_dotdot,
            &(string[]){tos3("..")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_ellipsis,
            &(string[]){tos3("...")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_comma,
            &(string[]){tos3(",")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_semicolon,
            &(string[]){tos3(";")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_colon,
            &(string[]){tos3(":")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_arrow,
            &(string[]){tos3("=>")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_assign,
            &(string[]){tos3("=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_decl_assign,
            &(string[]){tos3(":=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_plus_assign,
            &(string[]){tos3("+=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_minus_assign,
            &(string[]){tos3("-=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_mult_assign,
            &(string[]){tos3("*=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_div_assign,
            &(string[]){tos3("/=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_xor_assign,
            &(string[]){tos3("^=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_mod_assign,
            &(string[]){tos3("%=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_or_assign,
            &(string[]){tos3("|=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_and_assign,
            &(string[]){tos3("&=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_righ_shift_assign,
            &(string[]){tos3(">>=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_left_shift_assign,
            &(string[]){tos3("<<=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_lcbr,
            &(string[]){tos3("{")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_rcbr,
            &(string[]){tos3("}")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_lpar,
            &(string[]){tos3("(")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_rpar,
            &(string[]){tos3(")")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_lsbr,
            &(string[]){tos3("[")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_rsbr,
            &(string[]){tos3("]")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_eq,
            &(string[]){tos3("==")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_ne,
            &(string[]){tos3("!=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_gt, &(string[]){tos3(">")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_lt, &(string[]){tos3("<")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_ge,
            &(string[]){tos3(">=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_le,
            &(string[]){tos3("<=")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_question,
            &(string[]){tos3("?")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_left_shift,
            &(string[]){tos3("<<")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_righ_shift,
            &(string[]){tos3(">>")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_nl,
            &(string[]){tos3("NLL")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_dollar,
            &(string[]){tos3("$")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_assert,
            &(string[]){tos3("assert")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_struct,
            &(string[]){tos3("struct")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_if,
            &(string[]){tos3("if")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_else,
            &(string[]){tos3("else")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_return,
            &(string[]){tos3("return")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_module,
            &(string[]){tos3("module")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_sizeof,
            &(string[]){tos3("sizeof")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_go,
            &(string[]){tos3("go")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_goto,
            &(string[]){tos3("goto")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_const,
            &(string[]){tos3("const")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_mut,
            &(string[]){tos3("mut")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_type,
            &(string[]){tos3("type")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_for,
            &(string[]){tos3("for")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_switch,
            &(string[]){tos3("switch")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_fn,
            &(string[]){tos3("fn")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_true,
            &(string[]){tos3("true")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_false,
            &(string[]){tos3("false")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_continue,
            &(string[]){tos3("continue")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_break,
            &(string[]){tos3("break")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_import,
            &(string[]){tos3("import")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_embed,
            &(string[]){tos3("embed")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_unsafe,
            &(string[]){tos3("unsafe")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_enum,
            &(string[]){tos3("enum")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_interface,
            &(string[]){tos3("interface")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_pub,
            &(string[]){tos3("pub")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_import_const,
            &(string[]){tos3("import_const")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_in,
            &(string[]){tos3("in")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_atomic,
            &(string[]){tos3("atomic")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_orelse,
            &(string[]){tos3("or")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_global,
            &(string[]){tos3("__global")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_union,
            &(string[]){tos3("union")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_static,
            &(string[]){tos3("static")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_as,
            &(string[]){tos3("as")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_defer,
            &(string[]){tos3("defer")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_match,
            &(string[]){tos3("match")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_select,
            &(string[]){tos3("select")});

  array_set(&/*q*/ s, compiler__compiler__TokenKind_key_none,
            &(string[]){tos3("none")});

  return s;
}
compiler__TokenKind compiler__key_to_token(string key) {

  int tmp3 = 0;
  bool tmp4 = map_get(/*token.v : 246*/ compiler__KEYWORDS, key, &tmp3);

  compiler__TokenKind a = ((compiler__TokenKind)(tmp3));

  return a;
}
bool compiler__is_key(string key) {

  return ((int)(compiler__key_to_token(key))) > 0;
}
string compiler__TokenKind_str(compiler__TokenKind t) {

  return (*(string *)array_get(compiler__TokenStr, ((int)(t))));
}
bool compiler__TokenKind_is_decl(compiler__TokenKind t) {

  return t == compiler__compiler__TokenKind_key_enum ||
         t == compiler__compiler__TokenKind_key_interface ||
         t == compiler__compiler__TokenKind_key_fn ||
         t == compiler__compiler__TokenKind_key_struct ||
         t == compiler__compiler__TokenKind_key_type ||
         t == compiler__compiler__TokenKind_key_const ||
         t == compiler__compiler__TokenKind_key_import_const ||
         t == compiler__compiler__TokenKind_key_pub ||
         t == compiler__compiler__TokenKind_eof;
}
bool compiler__TokenKind_is_assign(compiler__TokenKind t) {

  return (_IN(compiler__TokenKind, (t), compiler__AssignTokens));
}
bool array_compiler__TokenKind_contains(array_compiler__TokenKind t,
                                        compiler__TokenKind val) {

  array_compiler__TokenKind tmp7 = t;
  for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
    compiler__TokenKind tt = ((compiler__TokenKind *)tmp7.data)[tmp8];

    if (tt == val) {

      return 1;
    };
  };

  return 0;
}
string compiler__Token_str(compiler__Token t) {

  if (t.tok == compiler__compiler__TokenKind_str) {

    return _STR("'%.*s'", t.lit.len, t.lit.str);
  };

  if (t.tok < compiler__compiler__TokenKind_plus) {

    return t.lit;
  };

  return compiler__TokenKind_str(t.tok);
}
void compiler__Scanner_fgen(compiler__Scanner *scanner, string s_) {

  string s = s_;

  if (scanner->fmt_line_empty) {

    s = string_add(strings__repeat('\t', scanner->fmt_indent), s);
  };

  strings__Builder_write(&/* ? */ scanner->fmt_out, s);

  scanner->fmt_line_empty = 0;
}
void compiler__Scanner_fgenln(compiler__Scanner *scanner, string s_) {

  string s = s_;

  if (scanner->fmt_line_empty) {

    s = string_add(strings__repeat('\t', scanner->fmt_indent), s);
  };

  strings__Builder_writeln(&/* ? */ scanner->fmt_out, s);

  scanner->fmt_line_empty = 1;
}
void compiler__Parser_fgen(compiler__Parser *p, string s) { ; }
void compiler__Parser_fspace(compiler__Parser *p) { ; }
void compiler__Parser_fgenln(compiler__Parser *p, string s) { ; }
void compiler__Parser_fmt_inc(compiler__Parser *p) { p->scanner->fmt_indent++; }
void compiler__Parser_fmt_dec(compiler__Parser *p) { p->scanner->fmt_indent--; }
void compiler__launch_tool(string tname) {

  string vexe = compiler__vexe_path();

  string vroot = os__dir(vexe);

  array_string oargs = os__args;

  array_set(&/*q*/ oargs, 0, &(string[]){vexe});

  string tool_exe = os__realpath(
      _STR("%.*s/tools/%.*s", vroot.len, vroot.str, tname.len, tname.str));

  string tool_source = os__realpath(
      _STR("%.*s/tools/%.*s.v", vroot.len, vroot.str, tname.len, tname.str));

  string tool_args = array_string_join(oargs, tos3(" "));

  string tool_command = _STR("%.*s %.*s", tool_exe.len, tool_exe.str,
                             tool_args.len, tool_args.str);

  bool tool_should_be_recompiled = 0;

  if (!os__file_exists(tool_exe)) {

    tool_should_be_recompiled = 1;

  } else {

    if (os__file_last_mod_unix(tool_exe) <= os__file_last_mod_unix(vexe)) {

      tool_should_be_recompiled = 1;
    };

    if (os__file_last_mod_unix(tool_exe) <=
        os__file_last_mod_unix(tool_source)) {

      tool_should_be_recompiled = 1;
    };
  };

  if (tool_should_be_recompiled) {

    string compilation_command =
        _STR("%.*s %.*s", vexe.len, vexe.str, tool_source.len, tool_source.str);

    Option_os__Result tmp1 = os__exec(compilation_command);
    os__Result tool_compilation;
    if (!tmp1.ok) {
      string err = tmp1.error;
      int errcode = tmp1.ecode;

      v_panic(err);
    }
    tool_compilation = *(os__Result *)tmp1.data;
    ;

    if (tool_compilation.exit_code != 0) {

      v_panic(string_add(_STR("V tool \"%.*s\" could not be compiled\n",
                              tool_source.len, tool_source.str),
                         tool_compilation.output));
    };
  };

  v_exit(os__system(tool_command));
}
string filepath__ext(string path) {

  int pos = string_last_index_byte(path, '.');

  if (pos != -1) {

    return string_substr2(path, pos, -1, true);
  };

  return tos3("");
}
bool filepath__is_abs(string path) {

#ifdef _WIN32

  return string_at(path, 0) == '/' ||
         (byte_is_letter(string_at(path, 0)) && string_at(path, 1) == ':');

#endif
  ;

  return string_at(path, 0) == '/';
}
string filepath__join(string base, varg_string *dirs) {

  strings__Builder path = strings__new_builder(50);

  strings__Builder_write(&/* ? */ path, string_trim_right(base, tos3("\\/")));

  for (int tmp12 = 0; tmp12 < dirs->len; tmp12++) {
    string d = ((string *)dirs->args)[tmp12];

    strings__Builder_write(&/* ? */ path, os__path_separator);

    strings__Builder_write(&/* ? */ path, d);
  };

  return strings__Builder_str(path);
}
void time__remove_me_when_c_bug_is_fixed() {}
time__Time time__now() {

  time_t t = time(0);

  struct /*c struct init*/

      tm *now = 0;

  now = localtime(&t);

  return time__convert_ctime(*now);
}
time__Time time__random() {

  int now_unix = time__now().uni;

  int rand_unix = rand__next(now_unix);

  return time__unix(rand_unix);
}
time__Time time__unix(int abs) {

  int d = abs / time__seconds_per_day;

  int n = d / time__days_per_400_years;

  int y = 400 * n;

  d -= time__days_per_400_years * n;

  n = d / time__days_per_100_years;

  n -= n >> 2;

  y += 100 * n;

  d -= time__days_per_100_years * n;

  n = d / time__days_per_4_years;

  y += 4 * n;

  d -= time__days_per_4_years * n;

  n = d / 365;

  n -= n >> 2;

  y += n;

  d -= 365 * n;

  int yday = ((int)(d));

  int day = yday;

  int year = abs / ((int)(3.154e+7)) + 1970;

  int hour = ((int)(abs % time__seconds_per_day)) / time__seconds_per_hour;

  int minute = ((int)(abs % time__seconds_per_hour)) / time__seconds_per_minute;

  int second = ((int)(abs % time__seconds_per_minute));

  if (time__is_leap_year(year)) {

    if (day > 31 + 29 - 1) {

      day--;

    } else if (day == 31 + 29 - 1) {

      day = 29;

      return (time__Time){.year = year,
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

  int end = ((int)((*(int *)array_get(time__days_before, month + 1))));

  if (day >= end) {

    month++;

    begin = end;

  } else {

    begin = ((int)((*(int *)array_get(time__days_before, month))));
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
                      .uni = mktime(&t)};
}
string time__Time_format_ss(time__Time t) {

  return time__Time_get_fmt_str(t, time__time__FormatDelimiter_hyphen,
                                time__time__FormatTime_hhmmss24,
                                time__time__FormatDate_yyyymmdd);
}
string time__Time_format(time__Time t) {

  return time__Time_get_fmt_str(t, time__time__FormatDelimiter_hyphen,
                                time__time__FormatTime_hhmm24,
                                time__time__FormatDate_yyyymmdd);
}
string time__Time_smonth(time__Time t) {

  int i = t.month - 1;

  return string_substr2(time__months_string, i * 3, (i + 1) * 3, false);
}
string time__Time_hhmm(time__Time t) {

  return time__Time_get_fmt_time_str(t, time__time__FormatTime_hhmm24);
}
string time__Time_hhmm12(time__Time t) {

  return time__Time_get_fmt_time_str(t, time__time__FormatTime_hhmm12);
}
string time__Time_hhmmss(time__Time t) {

  return time__Time_get_fmt_time_str(t, time__time__FormatTime_hhmmss24);
}
string time__Time_ymmdd(time__Time t) {

  return time__Time_get_fmt_date_str(t, time__time__FormatDelimiter_hyphen,
                                     time__time__FormatDate_yyyymmdd);
}
string time__Time_ddmmy(time__Time t) {

  return time__Time_get_fmt_date_str(t, time__time__FormatDelimiter_dot,
                                     time__time__FormatDate_ddmmyyyy);
}
string time__Time_md(time__Time t) {

  return time__Time_get_fmt_date_str(t, time__time__FormatDelimiter_space,
                                     time__time__FormatDate_mmmd);
}
string time__Time_clean(time__Time t) {

  time__Time nowe = time__now();

  if (t.month == nowe.month && t.year == nowe.year && t.day == nowe.day) {

    return time__Time_get_fmt_time_str(t, time__time__FormatTime_hhmm24);
  };

  if (t.year == nowe.year) {

    return time__Time_get_fmt_str(t, time__time__FormatDelimiter_space,
                                  time__time__FormatTime_hhmm24,
                                  time__time__FormatDate_mmmd);
  };

  return time__Time_format(t);
}
string time__Time_clean12(time__Time t) {

  time__Time nowe = time__now();

  if (t.month == nowe.month && t.year == nowe.year && t.day == nowe.day) {

    return time__Time_get_fmt_time_str(t, time__time__FormatTime_hhmm12);
  };

  if (t.year == nowe.year) {

    return time__Time_get_fmt_str(t, time__time__FormatDelimiter_space,
                                  time__time__FormatTime_hhmm12,
                                  time__time__FormatDate_mmmd);
  };

  return time__Time_format(t);
}
time__Time time__parse(string s) {

  int pos = string_index(s, tos3(" "));

  if (pos <= 0) {

    println(tos3("bad time format"));

    return time__now();
  };

  string symd = string_substr2(s, 0, pos, false);

  array_string ymd = string_split(symd, tos3("-"));

  if (ymd.len != 3) {

    println(tos3("bad time format"));

    return time__now();
  };

  string shms = string_substr2(s, pos, -1, true);

  array_string hms = string_split(shms, tos3(":"));

  string hour = (*(string *)array_get(hms, 0));

  string minute = (*(string *)array_get(hms, 1));

  string second = (*(string *)array_get(hms, 2));

  return time__new_time(
      (time__Time){.year = v_string_int((*(string *)array_get(ymd, 0))),
                   .month = v_string_int((*(string *)array_get(ymd, 1))),
                   .day = v_string_int((*(string *)array_get(ymd, 2))),
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

  return mktime(&tt);
}
time__Time time__Time_add_seconds(time__Time t, int seconds) {

  return time__unix(t.uni + seconds);
}
int time__since(time__Time t) { return 0; }
string time__Time_relative(time__Time t) {

  time__Time now = time__now();

  int secs = now.uni - t.uni;

  if (secs <= 30) {

    return tos3("now");
  };

  if (secs < 60) {

    return tos3("1m");
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

    return tos3("");
  };

  return time__Time_md(t);
}
int time__day_of_week(int y, int m, int d) {

  array_int t = new_array_from_c_array(
      12, 12, sizeof(int),
      EMPTY_ARRAY_OF_ELEMS(int, 12){0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4});

  int sy = y;

  if ((m < 3)) {

    sy = sy - 1;
  };

  return (sy + sy / 4 - sy / 100 + sy / 400 + (*(int *)array_get(t, m - 1)) +
          d - 1) %
             7 +
         1;
}
int time__Time_day_of_week(time__Time t) {

  return time__day_of_week(t.year, t.month, t.day);
}
string time__Time_weekday_str(time__Time t) {

  int i = time__Time_day_of_week(t) - 1;

  return string_substr2(time__days_string, i * 3, (i + 1) * 3, false);
}
i64 time__ticks() {

#ifdef _WIN32

  return GetTickCount();

#else

  struct /*c struct init*/

      timeval ts;

  gettimeofday(&ts, 0);

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

  int res = (*(int *)array_get(time__month_days, month - 1)) + extra;

  int tmp29 = OPTION_CAST(int)(res);
  return opt_ok(&tmp29, sizeof(int));
}
string time__Time_get_fmt_time_str(time__Time t, time__FormatTime fmt_time) {

  if (fmt_time == time__time__FormatTime_no_time) {

    return tos3("");
  };

  string tp = (t.hour > 11) ? (tos3("p.m.")) : (tos3("a.m."));

  int hour = (t.hour > 12) ? (t.hour - 12) : ((t.hour == 0) ? (12) : (t.hour));

  time__FormatTime tmp30 = fmt_time;

  return (
      (tmp30 == time__time__FormatTime_hhmm12)
          ? (_STR("%d:%02d %.*s", hour, t.minute, tp.len, tp.str))
          : ((tmp30 == time__time__FormatTime_hhmm24)
                 ? (_STR("%02d:%02d", t.hour, t.minute))
                 : ((tmp30 == time__time__FormatTime_hhmmss12)
                        ? (_STR("%d:%02d:%02d %.*s", hour, t.minute, t.second,
                                tp.len, tp.str))
                        : ((tmp30 == time__time__FormatTime_hhmmss24)
                               ? (_STR("%02d:%02d:%02d", t.hour, t.minute,
                                       t.second))
                               : (_STR("unknown enumeration %d", fmt_time))))));
}
string time__Time_get_fmt_date_str(time__Time t,
                                   time__FormatDelimiter fmt_dlmtr,
                                   time__FormatDate fmt_date) {

  if (fmt_date == time__time__FormatDate_no_date) {

    return tos3("");
  };

  string month =
      _STR("%.*s", time__Time_smonth(t).len, time__Time_smonth(t).str);

  string year = string_right(int_str(t.year), 2);

  time__FormatDate tmp31 = fmt_date;

  time__FormatDelimiter tmp32 = fmt_dlmtr;

  return string_replace(
      ((tmp31 == time__time__FormatDate_ddmmyy)
           ? (_STR("%02d|%02d|%.*s", t.day, t.month, year.len, year.str))
           : ((tmp31 == time__time__FormatDate_ddmmyyyy)
                  ? (_STR("%02d|%02d|%d", t.day, t.month, t.year))
                  : ((tmp31 == time__time__FormatDate_mmddyy)
                         ? (_STR("%02d|%02d|%.*s", t.month, t.day, year.len,
                                 year.str))
                         : ((tmp31 == time__time__FormatDate_mmddyyyy)
                                ? (_STR("%02d|%02d|%d", t.month, t.day, t.year))
                                : ((tmp31 == time__time__FormatDate_mmmd)
                                       ? (_STR("%.*s|%d", month.len, month.str,
                                               t.day))
                                       : ((tmp31 ==
                                           time__time__FormatDate_mmmdd)
                                              ? (_STR("%.*s|%02d", month.len,
                                                      month.str, t.day))
                                              : ((tmp31 ==
                                                  time__time__FormatDate_mmmddyyyy)
                                                     ? (_STR("%.*s|%02d|%d",
                                                             month.len,
                                                             month.str, t.day,
                                                             t.year))
                                                     : ((tmp31 ==
                                                         time__time__FormatDate_yyyymmdd)
                                                            ? (_STR("%d|%02d|%"
                                                                    "02d",
                                                                    t.year,
                                                                    t.month,
                                                                    t.day))
                                                            : (_STR(
                                                                  "unknown "
                                                                  "enumeration "
                                                                  "%d",
                                                                  fmt_date)))))))))),
      tos3("|"),
      ((tmp32 == time__time__FormatDelimiter_dot)
           ? (tos3("."))
           : ((tmp32 == time__time__FormatDelimiter_hyphen)
                  ? (tos3("-"))
                  : ((tmp32 == time__time__FormatDelimiter_slash)
                         ? (tos3("/"))
                         : ((tmp32 == time__time__FormatDelimiter_space)
                                ? (tos3(" "))
                                : (_STR("unknown enumeration %d",
                                        fmt_dlmtr)))))));
}
string time__Time_get_fmt_str(time__Time t, time__FormatDelimiter fmt_dlmtr,
                              time__FormatTime fmt_time,
                              time__FormatDate fmt_date) {

  if (fmt_date == time__time__FormatDate_no_date) {

    if (fmt_time == time__time__FormatTime_no_time) {

      return tos3("");

    } else {

      return time__Time_get_fmt_time_str(t, fmt_time);
    };

  } else {

    if (fmt_time != time__time__FormatTime_no_time) {

      return string_add(
          string_add(time__Time_get_fmt_date_str(t, fmt_dlmtr, fmt_date),
                     tos3(" ")),
          time__Time_get_fmt_time_str(t, fmt_time));

    } else {

      return time__Time_get_fmt_date_str(t, fmt_dlmtr, fmt_date);
    };
  };
}
string vweb_dot_tmpl__compile_template(string path) {

  Option_string tmp1 = os__read_file(path);
  string html;
  if (!tmp1.ok) {
    string err = tmp1.error;
    int errcode = tmp1.ecode;

    v_panic(tos3("html failed"));
  }
  html = *(string *)tmp1.data;
  ;

  string header = tos3("");

  if (os__file_exists(tos3("header.html"))) {

    Option_string tmp2 = os__read_file(tos3("header.html"));
    string h;
    if (!tmp2.ok) {
      string err = tmp2.error;
      int errcode = tmp2.ecode;

      v_panic(tos3("html failed"));
    }
    h = *(string *)tmp2.data;
    ;

    header = string_replace(h, tos3("\'"), tos3("\""));
  };

  array_string lines = string_split_into_lines(html);

  strings__Builder s = strings__new_builder(1000);

  string base = string_replace(string_all_after(path, tos3("/")), tos3(".html"),
                               tos3(""));

  strings__Builder_writeln(
      &/* ? */ s,
      _STR("module main import strings fn %.*s_view() string {   // this line "
           "will get removed becase only function body is embedded \nmut sb := "
           "strings.new_builder(%d)\nheader := \'%.*s\' \n_ = header "
           "\n//footer := \'footer\' \n",
           base.len, base.str, lines.len * 30, header.len, header.str));

  strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

  bool in_css = 1;

  array_string tmp3 = lines;
  for (int tmp4 = 0; tmp4 < tmp3.len; tmp4++) {
    string _line = ((string *)tmp3.data)[tmp4];

    string line = string_trim_space(_line);

    if (string_eq(line, tos3("<style>"))) {

      in_css = 1;

    } else if (string_eq(line, tos3("</style>"))) {
    };

    if (string_contains(line, tos3("@if "))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      int pos = string_index(line, tos3("@if"));

      strings__Builder_writeln(
          &/* ? */ s,
          string_add(
              string_add(tos3("if "), string_substr2(line, pos + 4, -1, true)),
              tos3("{")));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (string_contains(line, tos3("@end"))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      strings__Builder_writeln(&/* ? */ s, tos3("}"));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (string_contains(line, tos3("@else"))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      strings__Builder_writeln(&/* ? */ s, tos3(" } else { "));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (string_contains(line, tos3("@for"))) {

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

      int pos = string_index(line, tos3("@for"));

      strings__Builder_writeln(
          &/* ? */ s,
          string_add(
              string_add(tos3("for "), string_substr2(line, pos + 4, -1, true)),
              tos3("{")));

      strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_START);

    } else if (!in_css && string_contains(line, tos3(".")) &&
               string_ends_with(line, tos3("{"))) {

      string class = string_find_between(line, tos3("."), tos3("{"));

      strings__Builder_writeln(
          &/* ? */ s, _STR("<div class=\"%.*s\">", class.len, class.str));

    } else if (!in_css && string_eq(line, tos3("}"))) {

      strings__Builder_writeln(&/* ? */ s, tos3("</div>"));

    } else {

      strings__Builder_writeln(
          &/* ? */ s,
          string_replace(string_replace(line, tos3("@"), tos3("\x24")),
                         tos3("\'"), tos3("\"")));
    };
  };

  strings__Builder_writeln(&/* ? */ s, vweb_dot_tmpl__STR_END);

  strings__Builder_writeln(&/* ? */ s, tos3("tmpl_res := sb.str() "));

  strings__Builder_writeln(&/* ? */ s, tos3("return tmpl_res }"));

  return strings__Builder_str(s);
}
benchmark__Benchmark benchmark__new_benchmark() {

  return (benchmark__Benchmark){
      .bench_start_time = benchmark__now(),
      .verbose = 1,
      .bench_end_time = 0,
      .step_start_time = 0,
      .step_end_time = 0,
      .ntotal = 0,
      .nok = 0,
      .nfail = 0,
  };
}
void benchmark__Benchmark_stop(benchmark__Benchmark *b) {

  b->bench_end_time = benchmark__now();
}
void benchmark__Benchmark_step(benchmark__Benchmark *b) {

  b->step_start_time = benchmark__now();
}
void benchmark__Benchmark_fail(benchmark__Benchmark *b) {

  b->step_end_time = benchmark__now();

  b->ntotal++;

  b->nfail++;
}
void benchmark__Benchmark_ok(benchmark__Benchmark *b) {

  b->step_end_time = benchmark__now();

  b->ntotal++;

  b->nok++;
}
void benchmark__Benchmark_fail_many(benchmark__Benchmark *b, int n) {

  b->step_end_time = benchmark__now();

  b->ntotal += n;

  b->nfail += n;
}
void benchmark__Benchmark_ok_many(benchmark__Benchmark *b, int n) {

  b->step_end_time = benchmark__now();

  b->ntotal += n;

  b->nok += n;
}
void benchmark__Benchmark_neither_fail_nor_ok(benchmark__Benchmark *b) {

  b->step_end_time = benchmark__now();
}
string benchmark__Benchmark_step_message(benchmark__Benchmark *b, string msg) {

  return benchmark__Benchmark_tdiff_in_ms(b, msg, b->step_start_time,
                                          b->step_end_time);
}
string benchmark__Benchmark_total_message(benchmark__Benchmark *b, string msg) {

  string tmsg = string_add(
      string_add(
          string_add(
              string_add(string_add(_STR("%.*s \n ok, fail, total = ", msg.len,
                                         msg.str),
                                    term__ok_message(_STR("%5d", b->nok))),
                         tos3(", ")),
              (b->nfail > 0) ? (term__fail_message(_STR("%5d", b->nfail)))
                             : (_STR("%5d", b->nfail))),
          tos3(", ")),
      _STR("%5d", b->ntotal));

  if (b->verbose) {

    tmsg = _STR("<=== total time spent %.*s", tmsg.len, tmsg.str);
  };

  return benchmark__Benchmark_tdiff_in_ms(b, tmsg, b->bench_start_time,
                                          b->bench_end_time);
}
i64 benchmark__Benchmark_total_duration(benchmark__Benchmark *b) {

  return (b->bench_end_time - b->bench_start_time);
}
string benchmark__Benchmark_tdiff_in_ms(benchmark__Benchmark *b, string s,
                                        i64 sticks, i64 eticks) {

  if (b->verbose) {

    i64 tdiff = (eticks - sticks);

    return _STR("%6lld ms | %.*s", tdiff, s.len, s.str);
  };

  return s;
}
i64 benchmark__now() { return time__ticks(); }
void main__main() {

  array_string args = compiler__env_vflags_and_os_args();

  array_string tmp1 = new_array(0, args.len, sizeof(string));
  for (int i = 0; i < args.len; i++) {
    string it = ((string *)args.data)[i];
    if (string_starts_with(it, tos3("-")))
      array_push(&tmp1, &it);
  }
  array_string options = tmp1;

  array_string stuff_after_executable = array_slice2(os__args, 1, -1, true);

  array_string tmp4 = new_array(0, stuff_after_executable.len, sizeof(string));
  for (int i = 0; i < stuff_after_executable.len; i++) {
    string it = ((string *)stuff_after_executable.data)[i];
    if (!string_starts_with(it, tos3("-")))
      array_push(&tmp4, &it);
  }
  array_string commands = tmp4;

  if ((_IN(string, (tos3("-v")), options)) ||
      (_IN(string, (tos3("--version")), options)) ||
      (_IN(string, (tos3("version")), commands))) {

    string version_hash = compiler__vhash();

    printf("V %.*s %.*s\n", compiler__Version.len, compiler__Version.str,
           version_hash.len, version_hash.str);

    return;

  } else if ((_IN(string, (tos3("-h")), options)) ||
             (_IN(string, (tos3("--help")), options)) ||
             (_IN(string, (tos3("help")), commands))) {

    println(compiler__help_text);

    return;

  } else if ((_IN(string, (tos3("translate")), commands))) {

    println(tos3("Translating C to V will be available in V 0.3"));

    return;

  } else if ((_IN(string, (tos3("up")), commands))) {

    compiler__launch_tool(tos3("vup"));

    return;

  } else if (((_IN(string, (tos3("search")), commands))) ||
             ((_IN(string, (tos3("install")), commands))) ||
             ((_IN(string, (tos3("update")), commands))) ||
             ((_IN(string, (tos3("remove")), commands)))) {

    compiler__launch_tool(tos3("vpm"));

    return;

  } else if (((_IN(string, (tos3("get")), commands)))) {

    println(tos3("use `v install` to install modules from vpm.vlang.io "));

    return;

  } else if ((_IN(string, (tos3("symlink")), commands))) {

    compiler__create_symlink();

    return;

  } else if ((_IN(string, (tos3("fmt")), commands))) {

    compiler__vfmt(args);

    return;

  } else if ((_IN(string, (tos3("test")), commands))) {

    compiler__launch_tool(tos3("vtest"));

    return;

  } else if ((_IN(string, (tos3("runrepl")), commands)) || commands.len == 0 ||
             (args.len == 2 &&
              string_eq((*(string *)array_get(args, 1)), tos3("-")))) {

    compiler__launch_tool(tos3("vrepl"));

    return;

  } else if ((_IN(string, (tos3("doc")), commands))) {

    string vexe = os__executable();

    string vdir = os__dir(os__executable());

    os__chdir(vdir);

    string mod = *(string *)array_last(args);

    os__system(string_add(_STR("%.*s build module vlib/", vexe.len, vexe.str),
                          *(string *)array_last(args)));

    Option_string tmp7 =
        os__read_file(_STR("%.*s/vlib/%.*s.vh", compiler__v_modules_path.len,
                           compiler__v_modules_path.str, mod.len, mod.str));
    string txt;
    if (!tmp7.ok) {
      string err = tmp7.error;
      int errcode = tmp7.ecode;

      v_panic(err);
    }
    txt = *(string *)tmp7.data;
    ;

    println(txt);

    v_exit(0);

  } else {
  };

  compiler__V *v = compiler__new_v(args);

  if (v->pref->is_verbose) {

    println(array_string_str(args));
  };

  if ((_IN(string, (tos3("run")), args))) {

    compiler__V_compile(v);

    compiler__V_run_compiled_executable_and_exit(*v);
  };

  benchmark__Benchmark tmark = benchmark__new_benchmark();

  compiler__V_compile(v);

  if (v->pref->is_stats) {

    benchmark__Benchmark_stop(&/* ? */ tmark);

    println(string_add(string_add(tos3("compilation took: "),
                                  i64_str(benchmark__Benchmark_total_duration(
                                      &/* ? */ tmark))),
                       tos3("ms")));
  };

  if (v->pref->is_test) {

    compiler__V_run_compiled_executable_and_exit(*v);
  };

  compiler__V_finalize_compilation(v);
}
void init() {
  g_str_buf = malloc(1000);

  builtin__min_cap = 2 << 10;
  builtin__max_cap = 2 << 20;
  strconv__max_u64 = ((u64)(UINT64_MAX));
  os__S_IFMT = 0xF000;
  os__S_IFDIR = 0x4000;
  os__STD_INPUT_HANDLE = -10;
  os__STD_OUTPUT_HANDLE = -11;
  os__STD_ERROR_HANDLE = -12;
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
  os__INVALID_HANDLE_VALUE = -1;
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
  os__args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});
  os__path_separator = tos3("\\");
  os__FORMAT_MESSAGE_ALLOCATE_BUFFER = 0x00000100;
  os__FORMAT_MESSAGE_ARGUMENT_ARRAY = 0x00002000;
  os__FORMAT_MESSAGE_FROM_HMODULE = 0x00000800;
  os__FORMAT_MESSAGE_FROM_STRING = 0x00000400;
  os__FORMAT_MESSAGE_FROM_SYSTEM = 0x00001000;
  os__FORMAT_MESSAGE_IGNORE_INSERTS = 0x00000200;
  os__SUBLANG_NEUTRAL = 0x00;
  os__SUBLANG_DEFAULT = 0x01;
  os__LANG_NEUTRAL = (os__SUBLANG_NEUTRAL);
  compiler__CommonCHeaders = tos3(
      "\n\n#include <stdio.h>  // TODO remove all these includes, define all "
      "function signatures and types manually\n#include "
      "<stdlib.h>\n\n//#include \"fns.h\"\n#include <signal.h>\n#include "
      "<stdarg.h> // for va_list\n#include <inttypes.h>  // int64_t "
      "etc\n#include <string.h> // memcpy\n\n#ifndef _WIN32\n#include "
      "<ctype.h>\n#include <locale.h> // tolower\n#include "
      "<sys/time.h>\n#include <unistd.h> // sleep\n#else\n#if "
      "defined(__MSVCRT_VERSION__) && __MSVCRT_VERSION__ < "
      "__MSVCR90_DLL\n#error Please upgrade your MinGW distribution to use "
      "msvcr90.dll or later.\n#endif\n#endif\n\n#if defined(__CYGWIN__) && "
      "!defined(_WIN32)\n#error Cygwin is not supported, please use MinGW or "
      "Visual Studio.\n#endif\n\n\n#ifdef __linux__\n#include "
      "<sys/types.h>\n#include <sys/wait.h> // os__wait uses wait on "
      "nix\n#endif\n\n#ifdef __FreeBSD__\n#include <sys/types.h>\n#include "
      "<sys/wait.h> // os__wait uses wait on nix\n#endif\n\n#ifdef "
      "__DragonFly__\n#include <sys/types.h>\n#include <sys/wait.h> // "
      "os__wait uses wait on nix\n#endif\n\n#ifdef __OpenBSD__\n#include "
      "<sys/types.h>\n#include <sys/resource.h>\n#include <sys/wait.h> // "
      "os__wait uses wait on nix\n#endif\n\n#define "
      "EMPTY_STRUCT_DECLARATION\n#define EMPTY_STRUCT_INITIALIZATION 0\n// Due "
      "to a tcc bug, the length of an array needs to be specified, but GCC "
      "crashes if it is...\n#define EMPTY_ARRAY_OF_ELEMS(x,n) (x[])\n#define "
      "TCCSKIP(x) x\n\n#ifdef __TINYC__\n#undef "
      "EMPTY_STRUCT_INITIALIZATION\n#define "
      "EMPTY_STRUCT_INITIALIZATION\n#undef EMPTY_ARRAY_OF_ELEMS\n#define "
      "EMPTY_ARRAY_OF_ELEMS(x,n) (x[n])\n#undef TCCSKIP\n#define "
      "TCCSKIP(x)\n#endif\n\n#define OPTION_CAST(x) (x)\n\n#ifdef "
      "_WIN32\n#define WINVER 0x0600\n#define _WIN32_WINNT 0x0600\n#define "
      "WIN32_LEAN_AND_MEAN\n#define _UNICODE\n#define UNICODE\n#include "
      "<windows.h>\n\n// must be included after <windows.h>\n#ifndef "
      "__TINYC__\n#include <shellapi.h>\n#endif\n\n#include <io.h> // "
      "_waccess\n#include <fcntl.h> // _O_U8TEXT\n#include <direct.h> // "
      "_wgetcwd\n//#include <WinSock2.h>\n#ifdef _MSC_VER\n// On MSVC these "
      "are the same (as long as /volatile:ms is passed)\n#define _Atomic "
      "volatile\n\n// MSVC cannot parse some things properly\n#undef "
      "EMPTY_STRUCT_DECLARATION\n#undef OPTION_CAST\n\n#define "
      "EMPTY_STRUCT_DECLARATION int ____dummy_variable\n#define "
      "OPTION_CAST(x)\n#endif\n\n#else\n#include "
      "<pthread.h>\n#endif\n\n//================================== TYPEDEFS "
      "================================*/\n\ntypedef int64_t i64;\ntypedef "
      "int16_t i16;\ntypedef int8_t i8;\ntypedef uint64_t u64;\ntypedef "
      "uint32_t u32;\ntypedef uint16_t u16;\ntypedef uint8_t byte;\ntypedef "
      "uint32_t rune;\ntypedef float f32;\ntypedef double f64;\ntypedef "
      "unsigned char* byteptr;\ntypedef int* intptr;\ntypedef void* "
      "voidptr;\ntypedef struct array array;\ntypedef struct map map;\ntypedef "
      "array array_string;\ntypedef array array_int;\ntypedef array "
      "array_byte;\ntypedef array array_f32;\ntypedef array "
      "array_f64;\ntypedef map map_int;\ntypedef map map_string;\n#ifndef "
      "bool\n	typedef int bool;\n	#define true 1\n	#define false "
      "0\n#endif\n\n//============================== HELPER C MACROS "
      "=============================*/\n#define _PUSH(arr, val, tmp, tmp_typ) "
      "{tmp_typ tmp = (val); array_push(arr, &tmp);}\n#define _PUSH_MANY(arr, "
      "val, tmp, tmp_typ) {tmp_typ tmp = (val); array_push_many(arr, tmp.data, "
      "tmp.len);}\n#define _IN(typ, val, arr) array_##typ##_contains(arr, "
      "val)\n#define _IN_MAP(val, m) map_exists(m, val)\n#define "
      "DEFAULT_EQUAL(a, b) (a == b)\n#define DEFAULT_NOT_EQUAL(a, b) (a != "
      "b)\n#define DEFAULT_LT(a, b) (a < b)\n#define DEFAULT_LE(a, b) (a <= "
      "b)\n#define DEFAULT_GT(a, b) (a > b)\n#define DEFAULT_GE(a, b) (a >= "
      "b)\n//================================== GLOBALS "
      "=================================*/\nbyteptr g_str_buf;\nint "
      "load_so(byteptr);\nvoid reload_so();\n");
  compiler__js_headers = tos3(
      "\n\nvar array_string = function() {}\nvar array_byte = function() "
      "{}\nvar array_int = function() {}\nvar byte = function() {}\nvar double "
      "= function() {}\nvar int = function() {}\nvar f64 = function() {}\nvar "
      "f32 = function() {}\nvar i64 = function() {}\nvar i32 = function() "
      "{}\nvar i16 = function() {}\nvar u64 = function() {}\nvar u32 = "
      "function() {}\nvar u16 = function() {}\nvar i8 = function() {}\nvar "
      "bool = function() {}\nvar rune = function() {}\nvar map_string = "
      "function() {}\nvar map_int = function() {}\n\n");
  compiler__warn_match_arrow =
      string_add(tos3("=> is no longer needed in match statements, use\n"),
                 tos3("match foo {\n	1 { bar }\n	2 { baz }\n	else { "
                      "... }\n}"));
  compiler__err_used_as_value = tos3("used as value");
  compiler__and_or_error =
      string_add(tos3("use `()` to make the boolean expression clear\n"),
                 tos3("for example: `(a && b) || c` instead of `a && b || c`"));
  compiler__EmptyFn =
      (compiler__Fn){.name = tos3(""),
                     .mod = tos3(""),
                     .args = new_array(0, 1, sizeof(compiler__Var)),
                     .is_interface = 0,
                     .scope_level = 0,
                     .typ = tos3(""),
                     .receiver_typ = tos3(""),
                     .is_c = 0,
                     .is_public = 0,
                     .is_method = 0,
                     .is_decl = 0,
                     .is_unsafe = 0,
                     .is_deprecated = 0,
                     .is_variadic = 0,
                     .is_generic = 0,
                     .returns_error = 0,
                     .defer_text = new_array(0, 1, sizeof(string)),
                     .type_pars = new_array(0, 1, sizeof(string)),
                     .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                     .body_idx = 0,
                     .fn_name_token_idx = 0,
                     .comptime_define = tos3(""),
                     .is_used = 0};
  compiler__MainFn =
      (compiler__Fn){.name = tos3("main"),
                     .mod = tos3(""),
                     .args = new_array(0, 1, sizeof(compiler__Var)),
                     .is_interface = 0,
                     .scope_level = 0,
                     .typ = tos3(""),
                     .receiver_typ = tos3(""),
                     .is_c = 0,
                     .is_public = 0,
                     .is_method = 0,
                     .is_decl = 0,
                     .is_unsafe = 0,
                     .is_deprecated = 0,
                     .is_variadic = 0,
                     .is_generic = 0,
                     .returns_error = 0,
                     .defer_text = new_array(0, 1, sizeof(string)),
                     .type_pars = new_array(0, 1, sizeof(string)),
                     .type_inst = new_array(0, 1, sizeof(compiler__TypeInst)),
                     .body_idx = 0,
                     .fn_name_token_idx = 0,
                     .comptime_define = tos3(""),
                     .is_used = 0};
  compiler__dot_ptr = tos3("->");
  compiler__Version = tos3("0.1.22");
  compiler__supported_platforms = new_array_from_c_array(
      10, 10, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 10){
          tos3("windows"), tos3("mac"), tos3("linux"), tos3("freebsd"),
          tos3("openbsd"), tos3("netbsd"), tos3("dragonfly"), tos3("android"),
          tos3("js"), tos3("solaris")});
  compiler__v_modules_path = string_add(os__home_dir(), tos3(".vmodules"));
  compiler__HKEY_LOCAL_MACHINE = ((RegKey)(0x80000002));
  compiler__KEY_QUERY_VALUE = (0x0001);
  compiler__KEY_WOW64_32KEY = (0x0200);
  compiler__KEY_ENUMERATE_SUB_KEYS = (0x0008);
  compiler__Reserved_Types = new_map_init(15, sizeof(bool),
                                          (string[15]){
                                              tos3("i8"),
                                              tos3("i16"),
                                              tos3("int"),
                                              tos3("i64"),
                                              tos3("i128"),
                                              tos3("byte"),
                                              tos3("u16"),
                                              tos3("u32"),
                                              tos3("u64"),
                                              tos3("u128"),
                                              tos3("f32"),
                                              tos3("f64"),
                                              tos3("rune"),
                                              tos3("byteptr"),
                                              tos3("voidptr"),
                                          },
                                          (bool[15]){
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                              1,
                                          });
  compiler__CReserved = new_array_from_c_array(
      31, 31, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 31){
          tos3("delete"), tos3("exit"),     tos3("unix"),     tos3("error"),
          tos3("malloc"), tos3("calloc"),   tos3("free"),     tos3("panic"),
          tos3("auto"),   tos3("char"),     tos3("default"),  tos3("do"),
          tos3("double"), tos3("extern"),   tos3("float"),    tos3("inline"),
          tos3("int"),    tos3("long"),     tos3("register"), tos3("restrict"),
          tos3("short"),  tos3("signed"),   tos3("sizeof"),   tos3("static"),
          tos3("switch"), tos3("typedef"),  tos3("union"),    tos3("unsigned"),
          tos3("void"),   tos3("volatile"), tos3("while"),
      });
  compiler__integer_types = new_array_from_c_array(
      8, 8, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 8){tos3("int"), tos3("i8"), tos3("byte"),
                                      tos3("i16"), tos3("u16"), tos3("u32"),
                                      tos3("i64"), tos3("u64")});
  compiler__float_types = new_array_from_c_array(
      2, 2, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 2){tos3("f32"), tos3("f64")});
  compiler__reserved_type_param_names = new_array_from_c_array(
      5, 5, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 5){tos3("R"), tos3("S"), tos3("T"),
                                      tos3("U"), tos3("W")});
  compiler__TokenStr = compiler__build_token_str();
  compiler__KEYWORDS = compiler__build_keys();
  compiler__AssignTokens = new_array_from_c_array(
      11, 11, sizeof(compiler__TokenKind),
      EMPTY_ARRAY_OF_ELEMS(compiler__TokenKind, 11){
          compiler__compiler__TokenKind_assign,
          compiler__compiler__TokenKind_plus_assign,
          compiler__compiler__TokenKind_minus_assign,
          compiler__compiler__TokenKind_mult_assign,
          compiler__compiler__TokenKind_div_assign,
          compiler__compiler__TokenKind_xor_assign,
          compiler__compiler__TokenKind_mod_assign,
          compiler__compiler__TokenKind_or_assign,
          compiler__compiler__TokenKind_and_assign,
          compiler__compiler__TokenKind_righ_shift_assign,
          compiler__compiler__TokenKind_left_shift_assign});
  time__days_string = tos3("MonTueWedThuFriSatSun");
  time__month_days = new_array_from_c_array(
      12, 12, sizeof(int),
      EMPTY_ARRAY_OF_ELEMS(int, 12){31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
                                    31});
  time__months_string = tos3("JanFebMarAprMayJunJulAugSepOctNovDec");
  time__absolute_zero_year = ((i64)(-292277022399));
  time__seconds_per_hour = 60 * time__seconds_per_minute;
  time__seconds_per_day = 24 * time__seconds_per_hour;
  time__seconds_per_week = 7 * time__seconds_per_day;
  time__days_per_400_years = 365 * 400 + 97;
  time__days_per_100_years = 365 * 100 + 24;
  time__days_per_4_years = 365 * 4 + 1;
  time__days_before = new_array_from_c_array(
      13, 13, sizeof(int),
      EMPTY_ARRAY_OF_ELEMS(int, 13){
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
  builtin__init();
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

int main(int argc, char **argv) {
  init();
  os__args = os__init_os_args(argc, (byteptr *)argv);

  main__main();

  return 0;
}
