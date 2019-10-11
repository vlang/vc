#define V_COMMIT_HASH "2b087db"
#ifndef V_COMMIT_HASH
#define V_COMMIT_HASH "c254c98"
#endif

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
#ifndef __BIONIC__
#include <execinfo.h> // backtrace and backtrace_symbols_fd
#endif
#pragma weak backtrace
#pragma weak backtrace_symbols_fd
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
void init_consts();

int g_test_oks = 0;
int g_test_fails = 0;
#include <errno.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <sys/stat.h>
#ifndef _WIN32
#include <dirent.h>
#endif
#ifndef _WIN32
#include <unistd.h>
#endif
#include <time.h>
typedef struct array array;
typedef array array_string;
typedef array array_byte;
typedef array array_int;
typedef array array_char;
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
typedef array array_ustring;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef struct _V_MulRet_int_V_bool _V_MulRet_int_V_bool;
typedef struct os__Result os__Result;
typedef Option Option_os__Result;
typedef struct rand__Pcg32 rand__Pcg32;
typedef struct rand__Splitmix64 rand__Splitmix64;
typedef struct time__Time time__Time;
typedef Option Option_int;
typedef struct benchmark__Benchmark benchmark__Benchmark;
typedef struct CFlag CFlag;
typedef array array_CFlag;
typedef struct CGen CGen;
typedef array array_Type;
typedef struct ScannerPos ScannerPos;
typedef struct DepGraphNode DepGraphNode;
typedef struct DepGraph DepGraph;
typedef array array_DepGraphNode;
typedef struct DepSet DepSet;
typedef struct Fn Fn;
typedef array array_Var;
typedef Option Option_Var;
typedef Option Option_Var;
typedef array array_Fn;
typedef struct V V;
typedef array array_Parser;
typedef struct Preferences Preferences;
typedef Option Option_int;
typedef map map_FileImportTable;
typedef Option Option_string;
typedef struct MsvcResult MsvcResult;
typedef voidptr RegKey; // type alias name="RegKey" parent=`voidptr`
typedef Option Option_string;
typedef struct WindowsKit WindowsKit;
typedef Option Option_WindowsKit;
typedef struct VsInstallation VsInstallation;
typedef Option Option_VsInstallation;
typedef Option Option_MsvcResult;
typedef struct MsvcStringFlags MsvcStringFlags;
typedef struct Token Token;
typedef struct Parser Parser;
typedef array array_Token;
typedef struct IndexCfg IndexCfg;
typedef struct _V_MulRet_string_V_string _V_MulRet_string_V_string;
typedef struct Repl Repl;
typedef struct Scanner Scanner;
typedef struct ScanRes ScanRes;
typedef struct Table Table;
typedef map map_Type;
typedef map map_Fn;
typedef array array_GenTable;
typedef array array_VargAccess;
typedef struct VargAccess VargAccess;
typedef struct Name Name;
typedef struct GenTable GenTable;
typedef struct FileImportTable FileImportTable;
typedef struct Var Var;
typedef struct Type Type;
typedef struct TypeNode TypeNode;
typedef Option Option_Fn;
typedef Option Option_Var;
typedef Option Option_Var;
typedef Option Option_Fn;
typedef Option Option_Fn;
typedef Option Option_Var;
typedef array array_TokenKind;
typedef struct TestSession TestSession;
typedef Option Option_string;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__Result;
typedef Option Option_int;
typedef map map_DepGraphNode;
typedef map map_DepSet;
typedef Option Option_Var;
typedef Option Option_Var;
typedef int BuildMode;
typedef int OS;
typedef int Pass;
typedef Option Option_int;
typedef Option Option_string;
typedef Option Option_string;
typedef Option Option_WindowsKit;
typedef Option Option_VsInstallation;
typedef Option Option_MsvcResult;
typedef array array_bool;
typedef int IndexType;
typedef int NameCategory;
typedef int AccessMod;
typedef int TypeCategory;
typedef Option Option_Fn;
typedef Option Option_Var;
typedef Option Option_Var;
typedef Option Option_Fn;
typedef Option Option_Fn;
typedef Option Option_Var;
typedef int TokenKind;
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
  bool is_none;
};

//----
struct CFlag {
  string mod;
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

struct _V_MulRet_string_V_string {
  string var_0;
  string var_1;
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
  int fn_name_token_idx;
};

struct FileImportTable {
  string module_name;
  string file_path;
  map_string imports;
  array_string used_imports;
  map_int import_tok_idx;
};

struct IndexCfg {
  bool is_map;
  bool is_str;
  bool is_ptr;
  bool is_arr;
  bool is_arr0;
};

struct GenTable {
  string fn_name;
  array_string types;
};

struct MsvcStringFlags {
  array_string real_libs;
  array_string inc_paths;
  array_string lib_paths;
  array_string other_flags;
};

struct Name {
  NameCategory cat;
  int idx;
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
  bool is_stats;
  bool no_auto_free;
  string cflags;
  string ccompiler;
  bool building_v;
  bool autofree;
  bool compress;
  bool skip_builtin;
};

struct Repl {
  int indent;
  bool in_func;
  string line;
  array_string lines;
  array_string temp_lines;
  array_string functions_name;
  array_string functions;
};

struct ScanRes {
  TokenKind tok;
  string lit;
};

struct ScannerPos {
  int pos;
  int line_nr;
  int last_nl_pos;
};

struct _V_MulRet_int_V_bool {
  int var_0;
  bool var_1;
};

struct Table {
  map_Type typesmap;
  array_Var consts;
  map_Fn fns;
  array_GenTable generic_fns;
  map_int obf_ids;
  array_string modules;
  array_string imports;
  map_FileImportTable file_imports;
  array_CFlag cflags;
  int fn_cnt;
  bool obfuscate;
  array_VargAccess varg_access;
};

struct Token {
  TokenKind tok;
  string lit;
  int line_nr;
  int name_idx;
  int col;
};

struct VargAccess {
  string fn_name;
  int tok_idx;
  int index;
};

struct Var {
  string typ;
  string name;
  int idx;
  bool is_arg;
  bool is_const;
  array_Var args;
  string attr;
  bool is_mut;
  bool is_alloc;
  bool is_returned;
  bool ptr;
  bool ref;
  string parent_fn;
  string mod;
  AccessMod access_mod;
  bool is_global;
  bool is_used;
  bool is_changed;
  int scope_level;
  bool is_c;
  bool is_moved;
  int line_nr;
  int token_idx;
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

struct Parser {
  string id;
  string file_path;
  string file_name;
  string file_platform;
  string file_pcguard;
  V *v;
  Preferences *pref;
  Scanner *scanner;
  array_Token tokens;
  int token_idx;
  TokenKind tok;
  TokenKind prev_tok;
  TokenKind prev_tok2;
  string lit;
  CGen *cgen;
  Table *table;
  FileImportTable import_table;
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
  bool builtin_mod;
  bool inside_if_expr;
  bool inside_unwrapping_match_statement;
  bool inside_return_expr;
  bool is_struct_init;
  int if_expr_cnt;
  int for_expr_cnt;
  bool ptr_cast;
  bool calling_c;
  Fn cur_fn;
  array_Var local_vars;
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
  string cur_gen_type;
  bool is_vweb;
  bool is_sql;
  bool is_js;
  int sql_i;
  array_string sql_params;
  array_string sql_types;
  bool is_vh;
};

struct Scanner {
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
  TokenKind prev_tok;
  string fn_name;
  bool should_print_line_on_error;
  bool should_print_errors_in_color;
  bool should_print_relative_paths_on_error;
  byte quote;
  array_string file_lines;
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
  array_Parser parsers;
  strings__Builder vgen_buf;
};

struct TestSession {
  array_string files;
  string vexe;
  string vargs;
  bool failed;
  benchmark__Benchmark benchmark;
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

struct TypeNode {
  TypeNode *next;
  Type typ;
};

string _STR(const char *, ...);

string _STR_TMP(const char *, ...);

array new_array(int mylen, int cap, int elm_size);
array make(int len, int cap, int elm_size);
array new_array_from_c_array(int len, int cap, int elm_size, void *c_array);
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size,
                                      void *c_array);
array array_repeat_old(void *val, int nr_repeats, int elm_size);
array array_repeat(array a, int nr_repeats);
void array_sort_with_compare(array *a, void *compare);
void array_insert(array *a, int i, void *val);
void array_prepend(array *a, void *val);
void v_array_delete(array *a, int idx);
void *array_get(array a, int i);
void *array_first(array a);
void *array_last(array a);
array array_left(array s, int n);
array array_right(array s, int n);
array array_slice(array s, int start, int _end);
void array_set(array *a, int idx, void *val);
void array_push(array *arr, void *val);
void array_push_many(array *arr, void *val, int size);
array array_reverse(array a);
array array_clone(array a);
void v_array_free(array a);
string array_string_str(array_string a);
string array_byte_hex(array_byte b);
int copy(array_byte dst, array_byte src);
int compare_ints(int *a, int *b);
void array_int_sort(array_int *a);
int array_string_index(array_string a, string v);
int array_int_index(array_int a, int v);
int array_byte_index(array_byte a, byte v);
int array_char_index(array_char a, char v);
array_string array_string_filter(array_string a,
                                 bool (*predicate)(string p_val, int p_i,
                                                   array_string p_arr /*FFF*/));
array_int array_int_filter(array_int a,
                           bool (*predicate)(int p_val, int p_i,
                                             array_int p_arr /*FFF*/));
int array_int_reduce(array_int a, int (*iter)(int accum, int curr /*FFF*/),
                     int accum_start);
int builtin_init();
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
bool is_atty(int fd);
hashmap new_hashmap(int planned_nr_items);
void hashmap_set(hashmap *m, string key, int val);
int hashmap_get(hashmap *m, string key);
static inline f64 b_fabs(int v);
string f64_str(f64 d);
string f32_str(f32 d);
string ptr_str(void *ptr);
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
int vstrlen(byte *s);
void todo();
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
Option_string os__read_file(string path);
int os__file_size(string path);
void os__mv(string old, string new);
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
FILE *os__popen(string path);
_V_MulRet_int_V_bool os__posix_wait4_to_exit_status(int waitret);
int os__pclose(FILE *f);
Option_os__Result os__exec(string cmd);
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
void os__signal(int signum, void *handler);
int os__fork();
int os__wait();
int os__file_last_mod_unix(string path);
void os__log(string s);
void os__flush_stdout();
void os__print_backtrace();
array_string os__init_os_args(int argc, byteptr *argv);
string os__get_error_msg(int code);
array_string os__ls(string path);
bool os__dir_exists(string path);
void os__mkdir(string path);
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
void V_cc(V *v);
void V_cc_windows_cross(V *c);
void V_build_thirdparty_obj_files(V *c);
string main__find_c_compiler();
string main__find_c_compiler_default();
string main__find_c_compiler_thirdparty_options();
string main__get_cmdline_cflags(array_string args);
string CFlag_str(CFlag *c);
array_CFlag V_get_os_cflags(V *v);
array_CFlag V_get_rest_of_module_cflags(V *v, CFlag *c);
string CFlag_format(CFlag *cf);
bool Table_has_cflag(Table *table, CFlag cflag);
void Table_parse_cflag(Table *table, string cflag, string mod);
string array_CFlag_c_options_before_target(array_CFlag cflags);
string array_CFlag_c_options_after_target(array_CFlag cflags);
string array_CFlag_c_options_without_object_files(array_CFlag cflags);
string array_CFlag_c_options_only_object_files(array_CFlag cflags);
CGen *main__new_cgen(string out_name_c);
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
string V_prof_counters(V *v);
string Parser_print_prof_counters(Parser *p);
void Parser_gen_typedef(Parser *p, string s);
void Parser_gen_type_alias(Parser *p, string s);
void CGen_add_to_main(CGen *g, string s);
void main__build_thirdparty_obj_file(string path, array_CFlag moduleflags);
string main__os_name_to_ifdef(string name);
string main__platform_postfix_to_ifdefguard(string name);
string V_type_definitions(V *v);
array_Type main__sort_structs(array_Type types);
void Parser_error(Parser *p, string s);
void Parser_warn(Parser *p, string s);
void Parser_production_error_with_token_index(Parser *p, string e,
                                              int tokenindex);
void Parser_error_with_token_index(Parser *p, string s, int tokenindex);
void Parser_warn_with_token_index(Parser *p, string s, int tokenindex);
void Parser_error_with_position(Parser *p, string s, ScannerPos sp);
void Parser_warn_with_position(Parser *p, string s, ScannerPos sp);
void Scanner_error(Scanner *s, string msg);
void Scanner_warn(Scanner *s, string msg);
void Scanner_warn_with_col(Scanner *s, string msg, int col);
void Scanner_error_with_col(Scanner *s, string msg, int col);
static inline int Parser_cur_tok_index(Parser *p);
static inline int main__imax(int a, int b);
static inline int main__imin(int a, int b);
string Scanner_get_error_filepath(Scanner *s);
bool Scanner_is_color_output_on(Scanner *s);
void Parser_print_error_context(Parser *p);
string main__normalized_error(string s);
string ScannerPos_str(ScannerPos s);
ScannerPos Scanner_get_scanner_pos(Scanner *s);
void Scanner_goto_scanner_position(Scanner *s, ScannerPos scp);
ScannerPos Scanner_get_scanner_pos_of_token(Scanner *s, Token *t);
void Scanner_eat_single_newline(Scanner *s);
void Parser_comp_time(Parser *p);
void Parser_chash(Parser *p);
void Parser_comptime_method_call(Parser *p, Type typ);
void Parser_gen_array_str(Parser *p, Type typ);
void Parser_gen_struct_str(Parser *p, Type typ);
void DepSet_add(DepSet *dset, string item);
DepSet DepSet_diff(DepSet *dset, DepSet otherset);
int DepSet_size(DepSet *dset);
DepGraph *main__new_dep_graph();
void DepGraph_add(DepGraph *graph, string mod, array_string deps);
DepGraph *DepGraph_resolve(DepGraph *graph);
DepGraphNode DepGraph_last_node(DepGraph *graph);
string DepGraph_last_cycle(DepGraph *graph);
void DepGraph_display(DepGraph *graph);
Option_Var Parser_find_var(Parser *p, string name);
Option_Var Parser_find_var_check_new_var(Parser *p, string name);
void Parser_open_scope(Parser *p);
void Parser_mark_var_used(Parser *p, Var v);
void Parser_mark_var_returned(Parser *p, Var v);
void Parser_mark_var_changed(Parser *p, Var v);
void Parser_mark_arg_moved(Parser *p, Var v);
bool Parser_known_var(Parser *p, string name);
void Parser_register_var(Parser *p, Var v);
void Parser_clear_vars(Parser *p);
void Parser_fn_decl(Parser *p);
static inline void Parser_skip_fn_body(Parser *p);
void Parser_check_unused_variables(Parser *p);
void Parser_async_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                          string receiver_type);
void Parser_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                    string receiver_type);
void Parser_fn_args(Parser *p, Fn *f);
Fn *Parser_fn_call_args(Parser *p, Fn *f);
string Parser_fn_register_vargs_stuct(Parser *p, Fn *f, string typ,
                                      array_string values);
void Parser_fn_gen_caller_vargs(Parser *p, Fn *f);
string Parser_register_multi_return_stuct(Parser *p, array_string types);
string Fn_typ_str(Fn *f);
string Fn_str_args(Fn *f, Table *table);
string Parser_find_misspelled_local_var(Parser *p, string name, f32 min_match);
bool array_Fn_contains(array_Fn fns, Fn f);
string Parser_gen_var_decl(Parser *p, string name, bool is_static);
void Parser_gen_fn_decl(Parser *p, Fn f, string typ, string str_args);
void Parser_gen_blank_identifier_assign(Parser *p);
string main__types_to_c(array_Type types, Table *table);
void Parser_index_get(Parser *p, string typ, int fn_ph, IndexCfg cfg);
string Table_fn_gen_name(Table *table, Fn *f);
void Parser_gen_method_call(Parser *p, string receiver_type, string ftyp,
                            string cgen_name, Var receiver, int method_ph);
void Parser_gen_array_at(Parser *p, string typ_, bool is_arr0, int fn_ph);
void Parser_gen_for_header(Parser *p, string i, string tmp, string var_typ,
                           string val);
void Parser_gen_for_str_header(Parser *p, string i, string tmp, string var_typ,
                               string val);
void Parser_gen_for_range_header(Parser *p, string i, string range_end,
                                 string tmp, string var_type, string val);
void Parser_gen_for_map_header(Parser *p, string i, string tmp, string var_typ,
                               string val, string typ);
void Parser_gen_for_varg_header(Parser *p, string i, string varg,
                                string var_typ, string val);
void Parser_gen_array_init(Parser *p, string typ, bool no_alloc, int new_arr_ph,
                           int nr_elems);
void Parser_gen_array_set(Parser *p, string typ, bool is_ptr, bool is_map,
                          int fn_ph, int assign_pos, bool is_cao);
bool Parser_gen_struct_init(Parser *p, string typ, Type t);
void Parser_gen_struct_field_init(Parser *p, string field);
void Parser_gen_empty_map(Parser *p, string typ);
void Parser_cast(Parser *p, string typ);
string main__type_default(string typ);
void Parser_gen_array_push(Parser *p, int ph, string typ, string expr_type,
                           string tmp, string elm_type);
void Parser_gen_json_for_type(Parser *p, Type typ);
bool main__is_js_prim(string typ);
string Parser_decode_array(Parser *p, string array_type);
string main__js_enc_name(string typ);
string main__js_dec_name(string typ);
string Parser_encode_array(Parser *p, string array_type);
array_string V_generate_hotcode_reloading_compiler_flags(V *v);
void V_generate_hotcode_reloading_declarations(V *v);
void V_generate_hotcode_reloading_main_caller(V *v);
void V_generate_hot_reload_code(V *v);
void main__main();
void V_add_parser(V *v, Parser parser);
Option_int V_get_file_parser_index(V *v, string file);
int V_parse(V *v, string file, Pass pass);
void V_compile(V *v);
void V_generate_main(V *v);
void V_gen_main_start(V *v, bool add_os_args);
void V_gen_main_end(V *v, string return_statement);
string main__final_target_out_name(string out_name);
void V_run_compiled_executable_and_exit(V v);
array_string V_v_files_from_dir(V *v, string dir);
void V_add_v_files_to_compile(V *v);
array_string V_get_builtin_files(V *v);
array_string V_get_user_files(V *v);
void V_parse_lib_imports(V *v);
DepGraph *V_resolve_deps(V *v);
string main__get_arg(string joined_args, string arg, string def);
string main__get_param_after(string joined_args, string arg, string def);
void V_log(V *v, string s);
V *main__new_v(array_string args);
array_string main__env_vflags_and_os_args();
void main__update_v();
void main__vfmt(array_string args);
void main__install_v(array_string args);
void main__create_symlink();
void main__verror(string s);
string main__vhash();
string main__cescaped_path(string s);
string Fn_v_definition(Fn *f);
string main__v_type_str(string typ_);
void V_generate_vh(V *v);
void DepGraph_from_import_tables(DepGraph *graph,
                                 map_FileImportTable import_tables);
array_string DepGraph_imports(DepGraph *graph);
string V_module_path(V *v, string mod);
Option_string V_find_module_path(V *v, string mod);
Option_string main__find_windows_kit_internal(RegKey key,
                                              array_string versions);
Option_WindowsKit main__find_windows_kit_root();
Option_VsInstallation main__find_vs();
Option_MsvcResult main__find_msvc();
void V_cc_msvc(V *v);
void main__build_thirdparty_obj_file_with_msvc(string path,
                                               array_CFlag moduleflags);
MsvcStringFlags array_CFlag_msvc_string_flags(array_CFlag cflags);
void Parser_in_optimization(Parser *p, string typ, int ph);
Parser V_new_parser_from_string(V *v, string text, string id);
void V_reset_cgen_file_line_parameters(V *v);
Parser V_new_parser_from_file(V *v, string path);
Parser V_new_parser(V *v, Scanner *scanner, string id);
void Parser_scan_tokens(Parser *p);
void Parser_set_current_fn(Parser *p, Fn f);
void Parser_next(Parser *p);
TokenKind Parser_peek(Parser *p);
static inline Token Parser_prev_token(Parser *p);
static inline Token Parser_cur_tok(Parser *p);
static inline Token Parser_peek_token(Parser *p);
void Parser_log(Parser *p, string s);
void Parser_parse(Parser *p, Pass pass);
void Parser_imports(Parser *p);
void Parser_import_statement(Parser *p);
void Parser_const_decl(Parser *p);
void Parser_type_decl(Parser *p);
Fn *Parser_interface_method(Parser *p, string field_name, string receiver);
TypeCategory main__key_to_type_cat(TokenKind tok);
void Parser_struct_decl(Parser *p);
void Parser_enum_decl(Parser *p, string _enum_name);
string Parser_check_name(Parser *p);
string Parser_check_string(Parser *p);
string Parser_strtok(Parser *p);
void Parser_check_space(Parser *p, TokenKind expected);
void Parser_check(Parser *p, TokenKind expected);
static inline bool Parser_first_pass(Parser *p);
string Parser_get_type(Parser *p);
void Parser_print_tok(Parser *p);
string Parser_statements(Parser *p);
string Parser_statements_no_rcbr(Parser *p);
void Parser_close_scope(Parser *p);
void Parser_genln(Parser *p, string s);
void Parser_gen(Parser *p, string s);
string Parser_statement(Parser *p, bool add_semi);
void Parser_assign_statement(Parser *p, Var v, int ph, bool is_map);
void Parser_var_decl(Parser *p);
string Parser_bool_expression(Parser *p);
string Parser_bterm(Parser *p);
string Parser_name_expr(Parser *p);
string Parser_var_expr(Parser *p, Var v);
bool Parser_fileis(Parser *p, string s);
string Parser_dot(Parser *p, string str_typ_, int method_ph);
IndexType main__get_index_type(string typ);
string Parser_index_expr(Parser *p, string typ_, int fn_ph);
string Parser_indot_expr(Parser *p);
string Parser_expression(Parser *p);
string Parser_term(Parser *p);
string Parser_unary(Parser *p);
string Parser_factor(Parser *p);
string Parser_assoc(Parser *p);
void Parser_char_expr(Parser *p);
string main__format_str(string _str);
void Parser_string_expr(Parser *p);
string Parser_map_init(Parser *p);
string Parser_array_init(Parser *p);
string Parser_struct_init(Parser *p, string typ);
string Parser_get_tmp(Parser *p);
int Parser_get_tmp_counter(Parser *p);
_V_MulRet_string_V_string Parser_tmp_expr(Parser *p);
string Parser_if_st(Parser *p, bool is_expr, int elif_depth);
void Parser_for_st(Parser *p);
void Parser_switch_statement(Parser *p);
string Parser_match_statement(Parser *p, bool is_expr);
void Parser_assert_statement(Parser *p);
void Parser_return_st(Parser *p);
string main__prepend_mod(string mod, string name);
string Parser_prepend_mod(Parser *p, string name);
void Parser_go_statement(Parser *p);
string Parser_js_decode(Parser *p);
void Parser_attribute(Parser *p);
void Parser_defer_st(Parser *p);
void Parser_check_and_register_used_imported_type(Parser *p, string typ_name);
void Parser_check_unused_imports(Parser *p);
Type Parser_get_type2(Parser *p);
string main__sql_params2params_gen(array_string sql_params,
                                   array_string sql_types, string qprefix);
string Parser_select_query(Parser *p, int fn_ph);
void Parser_insert_query(Parser *p, int fn_ph);
bool Repl_checks(Repl *r);
bool Repl_function_call(Repl *r, string line);
void main__repl_help();
array_string main__run_repl();
Scanner *main__new_scanner_file(string file_path);
Scanner *main__new_scanner(string text);
ScanRes main__scan_res(TokenKind tok, string lit);
string Scanner_ident_name(Scanner *s);
string Scanner_ident_hex_number(Scanner *s);
string Scanner_ident_oct_number(Scanner *s);
string Scanner_ident_dec_number(Scanner *s);
string Scanner_ident_number(Scanner *s);
void Scanner_skip_whitespace(Scanner *s);
ScanRes Scanner_scan(Scanner *s);
int Scanner_current_column(Scanner *s);
int Scanner_count_symbol_before(Scanner s, int p, byte sym);
string Scanner_ident_string(Scanner *s);
string Scanner_ident_char(Scanner *s);
bool Scanner_expect(Scanner *s, string want, int start_pos);
void Scanner_debug_tokens(Scanner *s);
void Scanner_ignore_line(Scanner *s);
void Scanner_eat_to_end_of_line(Scanner *s);
void Scanner_inc_line_number(Scanner *s);
bool main__is_name_char(byte c);
bool main__is_nl(byte c);
bool main__contains_capital(string s);
bool main__good_type_name(string s);
void Scanner_validate_var_name(Scanner *s, string name);
string Fn_str(Fn f);
string Table_debug_fns(Table *t);
bool main__is_number_type(string typ);
bool main__is_float_type(string typ);
bool main__is_primitive_type(string typ);
Table *main__new_table(bool obfuscate);
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
Option_Fn Table_find_fn(Table *t, string name);
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
Option_Var Type_find_field(Type *t, string name);
bool Table_type_has_field(Table *table, Type *typ, string name);
Option_Var Table_find_field(Table *table, Type *typ, string name);
void Parser_add_method(Parser *p, string type_name, Fn f);
bool Type_has_method(Type *t, string name);
bool Table_type_has_method(Table *table, Type *typ, string name);
Option_Fn Table_find_method(Table *table, Type *typ, string name);
Option_Fn Type_find_method(Type *t, string name);
Type Parser_find_type(Parser *p, string name);
Type Table_find_type(Table *t, string name_);
bool Parser_check_types2(Parser *p, string got_, string expected_, bool throw);
bool Parser_check_types(Parser *p, string got, string expected);
bool Parser_check_types_no_throw(Parser *p, string got, string expected);
void Parser_check_types_with_token_index(Parser *p, string got, string expected,
                                         int var_token_idx);
bool Parser_satisfies_interface(Parser *p, string interface_name, string _typ,
                                bool throw);
bool Table_is_interface(Table *table, string name);
bool Table_main_exists(Table *t);
bool Table_has_at_least_one_test_fn(Table *t);
Option_Var Table_find_const(Table *t, string name);
string Table_cgen_name_type_pair(Table *table, string name, string typ);
bool main__is_valid_int_const(string val, string typ);
void Table_register_generic_fn(Table *t, string fn_name);
array_string Table_fn_gen_types(Table *t, string fn_name);
void Table_register_generic_fn_type(Table *t, string fn_name, string typ);
string Parser_typ_to_fmt(Parser *p, string typ, int level);
bool main__is_compile_time_const(string s_);
string Table_qualify_module(Table *table, string mod, string file_path);
FileImportTable Table_get_file_import_table(Table *table, string id);
FileImportTable main__new_file_import_table(string file_path);
bool FileImportTable_known_import(FileImportTable *fit, string mod);
void FileImportTable_register_import(FileImportTable *fit, string mod,
                                     int tok_idx);
void FileImportTable_register_alias(FileImportTable *fit, string alias,
                                    string mod, int tok_idx);
int FileImportTable_get_import_tok_idx(FileImportTable *fit, string mod);
bool FileImportTable_known_alias(FileImportTable *fit, string alias);
bool FileImportTable_is_aliased(FileImportTable *fit, string mod);
string FileImportTable_resolve_alias(FileImportTable *fit, string alias);
void FileImportTable_register_used_import(FileImportTable *fit, string alias);
bool FileImportTable_is_used_import(FileImportTable *fit, string alias);
bool Type_contains_field_type(Type *t, string typ);
string Parser_identify_typo(Parser *p, string name, FileImportTable *fit);
string Table_find_misspelled_fn(Table *table, string name, FileImportTable *fit,
                                f32 min_match);
string Table_find_misspelled_imported_mod(Table *table, string name,
                                          FileImportTable *fit, f32 min_match);
map_int main__build_keys();
array_string main__build_token_str();
TokenKind main__key_to_token(string key);
bool main__is_key(string key);
string TokenKind_str(TokenKind t);
bool TokenKind_is_decl(TokenKind t);
bool TokenKind_is_assign(TokenKind t);
bool array_TokenKind_contains(array_TokenKind t, TokenKind val);
void Scanner_fgen(Scanner *scanner, string s_);
void Scanner_fgenln(Scanner *scanner, string s_);
void Parser_fgen(Parser *p, string s);
void Parser_fspace(Parser *p);
void Parser_fgenln(Parser *p, string s);
void Parser_fmt_inc(Parser *p);
void Parser_fmt_dec(Parser *p);
TestSession main__new_test_sesion(string vargs);
void main__test_v();
void TestSession_test(TestSession *ts);
bool main__stable_example(string example, int index, array_string arr);
void main__v_test_v(string args_before_test);
void main__test_vget();
i64 total_m = 0; // global
int builtin__min_cap;
int builtin__max_cap;
array_int g_ustring_runes; // global
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
#define math__MaxI8 127
int math__MinI8;
#define math__MaxI16 32767
int math__MinI16;
#define math__MaxI32 2147483647
int math__MinI32;
#define math__MaxU8 255
#define math__MaxU16 65535
#define math__MaxU32 4294967295
#define math__MaxU64 18446744073709551615
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
#define vweb_dot_tmpl__STR_START tos3("sb.write(\'")
#define vweb_dot_tmpl__STR_END tos3("\' ) ")
string main__CommonCHeaders;
string main__js_headers;
#define main__MaxLocalVars 50
string main__dot_ptr;
string main__Version;
#define main__BuildMode_default_mode 0
#define main__BuildMode_build_module 1
array_string main__supported_platforms;
#define main__OS_mac 0
#define main__OS_linux 1
#define main__OS_windows 2
#define main__OS_freebsd 3
#define main__OS_openbsd 4
#define main__OS_netbsd 5
#define main__OS_dragonfly 6
#define main__OS_msvc 7
#define main__OS_js 8
#define main__OS_android 9
#define main__OS_solaris 10
#define main__Pass_imports 0
#define main__Pass_decl 1
#define main__Pass_main 2
string main__v_modules_path;
RegKey main__HKEY_LOCAL_MACHINE;
int main__KEY_QUERY_VALUE;
int main__KEY_WOW64_32KEY;
int main__KEY_ENUMERATE_SUB_KEYS;
Fn main__EmptyFn;
Fn main__MainFn;
#define main__MaxModuleDepth 4
string main__and_or_error;
#define main__IndexType_noindex 0
#define main__IndexType_str 1
#define main__IndexType_map 2
#define main__IndexType_array 3
#define main__IndexType_array0 4
#define main__IndexType_fixed_array 5
#define main__IndexType_ptr 6
#define main__single_quote '\''
#define main__double_quote '"'
#define main__error_context_before 2
#define main__error_context_after 2
#define main__NameCategory_constant 0
#define main__NameCategory_mod 1
#define main__NameCategory_var 2
#define main__NameCategory_typ 3
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
#define main__TypeCategory_objc_interface 8
#define main__TypeCategory_array 9
array_string main__CReserved;
array_string main__number_types;
array_string main__float_types;
#define main__TokenKind_eof 0
#define main__TokenKind_name 1
#define main__TokenKind_number 2
#define main__TokenKind_str 3
#define main__TokenKind_str_inter 4
#define main__TokenKind_chartoken 5
#define main__TokenKind_plus 6
#define main__TokenKind_minus 7
#define main__TokenKind_mul 8
#define main__TokenKind_div 9
#define main__TokenKind_mod 10
#define main__TokenKind_xor 11
#define main__TokenKind_pipe 12
#define main__TokenKind_inc 13
#define main__TokenKind_dec 14
#define main__TokenKind_and 15
#define main__TokenKind_logical_or 16
#define main__TokenKind_not 17
#define main__TokenKind_bit_not 18
#define main__TokenKind_question 19
#define main__TokenKind_comma 20
#define main__TokenKind_semicolon 21
#define main__TokenKind_colon 22
#define main__TokenKind_arrow 23
#define main__TokenKind_amp 24
#define main__TokenKind_hash 25
#define main__TokenKind_dollar 26
#define main__TokenKind_left_shift 27
#define main__TokenKind_righ_shift 28
#define main__TokenKind_assign 29
#define main__TokenKind_decl_assign 30
#define main__TokenKind_plus_assign 31
#define main__TokenKind_minus_assign 32
#define main__TokenKind_div_assign 33
#define main__TokenKind_mult_assign 34
#define main__TokenKind_xor_assign 35
#define main__TokenKind_mod_assign 36
#define main__TokenKind_or_assign 37
#define main__TokenKind_and_assign 38
#define main__TokenKind_righ_shift_assign 39
#define main__TokenKind_left_shift_assign 40
#define main__TokenKind_lcbr 41
#define main__TokenKind_rcbr 42
#define main__TokenKind_lpar 43
#define main__TokenKind_rpar 44
#define main__TokenKind_lsbr 45
#define main__TokenKind_rsbr 46
#define main__TokenKind_eq 47
#define main__TokenKind_ne 48
#define main__TokenKind_gt 49
#define main__TokenKind_lt 50
#define main__TokenKind_ge 51
#define main__TokenKind_le 52
#define main__TokenKind_nl 53
#define main__TokenKind_dot 54
#define main__TokenKind_dotdot 55
#define main__TokenKind_ellipsis 56
#define main__TokenKind_keyword_beg 57
#define main__TokenKind_key_as 58
#define main__TokenKind_key_assert 59
#define main__TokenKind_key_atomic 60
#define main__TokenKind_key_break 61
#define main__TokenKind_key_case 62
#define main__TokenKind_key_const 63
#define main__TokenKind_key_continue 64
#define main__TokenKind_key_default 65
#define main__TokenKind_key_defer 66
#define main__TokenKind_key_else 67
#define main__TokenKind_key_embed 68
#define main__TokenKind_key_enum 69
#define main__TokenKind_key_false 70
#define main__TokenKind_key_for 71
#define main__TokenKind_func 72
#define main__TokenKind_key_global 73
#define main__TokenKind_key_go 74
#define main__TokenKind_key_goto 75
#define main__TokenKind_key_if 76
#define main__TokenKind_key_import 77
#define main__TokenKind_key_import_const 78
#define main__TokenKind_key_in 79
#define main__TokenKind_key_interface 80
#define main__TokenKind_key_match 81
#define main__TokenKind_key_module 82
#define main__TokenKind_key_mut 83
#define main__TokenKind_key_none 84
#define main__TokenKind_key_return 85
#define main__TokenKind_key_select 86
#define main__TokenKind_key_sizeof 87
#define main__TokenKind_key_struct 88
#define main__TokenKind_key_switch 89
#define main__TokenKind_key_true 90
#define main__TokenKind_key_type 91
#define main__TokenKind_key_orelse 92
#define main__TokenKind_key_union 93
#define main__TokenKind_key_pub 94
#define main__TokenKind_key_static 95
#define main__TokenKind_keyword_end 96
#define main__NrTokens 140
array_string main__TokenStr;
map_int main__KEYWORDS;
array_TokenKind main__AssignTokens;
#define main__HelpText                                                         \
  tos3("Usage: v [options/commands] [file.v | directory]\n\n   When V is run " \
       "without any arguments, it is run in REPL mode.\n\n   When given a .v " \
       "file, it will be compiled. The executable will have the\n   same "     \
       "name as the input .v file: `v foo.v` produces `./foo` on *nix "        \
       "systems,\n  `foo.exe` on Windows.\n\n   You can use -o to specify a "  \
       "different output executable\'s name.\n\n   When given a directory, "   \
       "all .v files contained in it will be compiled as\n   part of a "       \
       "single main module.\n\n   By default the executable will have the "    \
       "same name as the directory.\n\n   To compile all V files in current "  \
       "directory, run `v .`\n\n   Any file ending in _test.v, will be "       \
       "treated as a test.\n   It will be compiled and run, evaluating the "   \
       "assert statements in every\n   function named test_xxx.\n\n   You "    \
       "can put common options inside an environment variable named VFLAGS, "  \
       "so that\n   you don\'t have to repeat them.\n\n   You can set it "     \
       "like this: `export VFLAGS=\"-cc clang -debug\"` on *nix,\n   `set "    \
       "VFLAGS=-os msvc` on Windows.\n\nOptions/commands:\n  -h, help        " \
       "  Display this information.\n  -o <file>         Write output to "     \
       "<file>.\n  -o <file>.c       Produce C source without compiling "      \
       "it.\n  -o <file>.js      Produce JavaScript source.\n  -prod         " \
       "    Build an optimized executable.\n  -v, version       Display "      \
       "compiler version and git hash of the compiler source.\n  -live       " \
       "      Enable hot code reloading (required by functions marked with "   \
       "[live]).\n  -os <OS>          Produce an executable for the selected " \
       "OS.\n                    OS can be linux, mac, windows, msvc.\n      " \
       "              Use msvc if you want to use the MSVC compiler on "       \
       "Windows.\n  -cc <ccompiler>   Specify which C compiler you want to "   \
       "use as a C backend.\n                    The C backend compiler "      \
       "should be able to handle C99 compatible C code.\n                    " \
       "Common C compilers are gcc, clang, tcc, icc, cl...\n  -cflags "        \
       "<flags>   Pass additional C flags to the C backend compiler.\n       " \
       "             Example: -cflags `sdl2-config --cflags`\n  -debug       " \
       "     Keep the generated C file for debugging in program.tmp.c even "   \
       "after compilation.\n  -shared           Build a shared library.\n  "   \
       "-stats            Show additional stats when compiling/running "       \
       "tests. Try `v -stats test .`\n  -g                Show v line "        \
       "numbers in backtraces. Implies -debug.\n  -obf              "          \
       "Obfuscate the resulting binary.\n  -show_c_cmd       Print the full "  \
       "C compilation command and how much time it took.\n  -                " \
       " Shorthand for `v runrepl`.\n\n  up                Update V. Run `v "  \
       "up` at least once per day, since V development is rapid and "          \
       "features/bugfixes are added constantly.\n  run <file.v>      Build "   \
       "and execute the V program in file.v. You can add arguments for the V " \
       "program *after* the file name.\n  build <module>    Compile a module " \
       "into an object file.\n  runrepl           Run the V REPL. If V is "    \
       "running in a tty terminal, the REPL is interactive, otherwise it "     \
       "just reads from stdin.\n  symlink           Useful on unix systems. "  \
       "Symlinks the current V executable to /usr/local/bin/v, so that V is "  \
       "globally available.\n  install <module>  Install a user module from "  \
       "https://vpm.vlang.io/.\n  test v            Run all V test files, "    \
       "and compile all V examples.\n  test folder/      Run all V test "      \
       "files located in the folder and its subfolders. You can also pass "    \
       "individual _test.v files too.\n  fmt               Run vfmt to "       \
       "format the source code. [wip]\n  doc               Run vdoc over the " \
       "source code and produce documentation. [wip]\n  translate         "    \
       "Translates C to V. [wip, will be available in V 0.3]\n")

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
array array_repeat_old(void *val, int nr_repeats, int elm_size) {

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

  array arr = (array){.len = nr_repeats,
                      .cap = nr_repeats,
                      .element_size = a.element_size,
                      .data = v_calloc(nr_repeats * a.element_size)};

  void *val = (byte *)a.data + 0;

  for (int i = 0; i < nr_repeats; i++) {

    memcpy((byte *)arr.data + i * a.element_size, val, a.element_size);
  };

  return arr;
}
void array_sort_with_compare(array *a, void *compare) {

  qsort(a->data, a->len, a->element_size, compare);
}
void array_insert(array *a, int i, void *val) {

  if (i >= a->len) {

    v_panic(tos3("array.insert: index larger than length"));
  };

  array_push(a, val);

  int size = a->element_size;

  memmove((byte *)a->data + (i + 1) * size, (byte *)a->data + i * size,
          (a->len - i) * size);

  array_set(a, i, val);
}
void array_prepend(array *a, void *val) { array_insert(a, 0, val); }
void v_array_delete(array *a, int idx) {

  int size = a->element_size;

  memmove((byte *)a->data + idx * size, (byte *)a->data + (idx + 1) * size,
          (a->len - idx) * size);

  a->len--;

  a->cap--;
}
void *array_get(array a, int i) {

  if (i < 0 || i >= a.len) {

    v_panic(_STR("array index out of range: %d/%d", i, a.len));
  };

  return (byte *)a.data + i * a.element_size;
}
void *array_first(array a) {

  if (a.len == 0) {

    v_panic(tos3("array.first: empty array"));
  };

  return (byte *)a.data + 0;
}
void *array_last(array a) {

  if (a.len == 0) {

    v_panic(tos3("array.last: empty array"));
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
void array_push(array *arr, void *val) {

  if (arr->len >= arr->cap - 1) {

    int cap = (arr->len + 1) * 2;

    if (arr->cap == 0) {

      arr->data = v_calloc(cap * arr->element_size);

    } else {

      arr->data = realloc(arr->data, cap * arr->element_size);
    };

    arr->cap = cap;
  };

  memcpy((byte *)arr->data + arr->element_size * arr->len, val,
         arr->element_size);

  arr->len++;
}
void array_push_many(array *arr, void *val, int size) {

  if (arr->len >= arr->cap - size) {

    int cap = (arr->len + size) * 2;

    if (arr->cap == 0) {

      arr->data = v_calloc(cap * arr->element_size);

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
int compare_ints(int *a, int *b) {

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
      a, &/*112 EXP:"void*" GOT:"fn (int*,int*) int" */ compare_ints);
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
array_string array_string_filter(
    array_string a,
    bool (*predicate)(string p_val, int p_i, array_string p_arr /*FFF*/)) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  for (int i = 0; i < a.len; i++) {

    if (predicate((*(string *)array_get(a, i)), i, a)) {

      _PUSH(&res,
            (/*typ = array_string   tmp_typ=string*/ (
                *(string *)array_get(a, i))),
            tmp48, string);
    };
  };

  return res;
}
array_int array_int_filter(array_int a,
                           bool (*predicate)(int p_val, int p_i,
                                             array_int p_arr /*FFF*/)) {

  array_int res = new_array_from_c_array(
      0, 0, sizeof(int), EMPTY_ARRAY_OF_ELEMS(int, 0){TCCSKIP(0)});

  for (int i = 0; i < a.len; i++) {

    if (predicate((*(int *)array_get(a, i)), i, a)) {

      _PUSH(&res, (/*typ = array_int   tmp_typ=int*/ (*(int *)array_get(a, i))),
            tmp55, int);
    };
  };

  return res;
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
int builtin_init() {

#ifdef _WIN32

  if (is_atty(0)) {

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

  return 1;
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

  if (backtrace_symbols_fd != 0) {

    byte *buffer[100];

    int nr_ptrs = backtrace(((voidptr *)(buffer)), 100);

    int nr_actual_frames = nr_ptrs - skipframes;

    array_string sframes = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    byteptr *csymbols = ((byteptr *)(backtrace_symbols(
        ((voidptr *)(&buffer[skipframes] /*rbyte* 0*/)), nr_actual_frames)));

    int tmp10 = 0;
    ;
    for (int tmp11 = tmp10; tmp11 < nr_actual_frames; tmp11++) {
      int i = tmp11;

      _PUSH(&sframes,
            (/*typ = array_string   tmp_typ=string*/ tos2(
                csymbols[/*ptr*/ i] /*rbyteptr 0*/)),
            tmp12, string);
    };

    array_string tmp13 = sframes;
    for (int tmp14 = 0; tmp14 < tmp13.len; tmp14++) {
      string sframe = ((string *)tmp13.data)[tmp14];

      string executable = string_all_before(sframe, tos3("("));

      string addr =
          string_all_before(string_all_after(sframe, tos3("[")), tos3("]"));

      string cmd = _STR("addr2line -e %.*s %.*s", executable.len,
                        executable.str, addr.len, addr.str);

      byteptr f = ((byteptr)(popen((char *)cmd.str, "r")));

      if (isnil(&/*112 EXP:"void*" GOT:"byteptr" */ f)) {

        println(sframe);

        continue;
      };

      byte buf[1000] = {0};

      string output = tos3("");

      while (fgets(buf, 1000, f) != 0) {

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

  } else {

    printf("backtrace_symbols_fd is missing, so printing backtraces is not "
           "available.\n");

    printf("Some libc implementations like musl simply do not provide it.\n");
  };

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
bool is_atty(int fd) {

#ifdef _WIN32

  int mode = 0;

  GetConsoleMode(_get_osfhandle(fd), &mode);

  return mode > 0;

#else

  return isatty(fd) != 0;

#endif
  ;
}
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
string ptr_str(void *ptr) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(((char *)(buf)), "%p", ptr);

  return tos(buf, vstrlen(buf));
}
bool f64_eq(f64 a, f64 b) { return fabs(a - b) <= DBL_EPSILON; }
bool f32_eq(f32 a, f32 b) { return fabsf(a - b) <= FLT_EPSILON; }
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

  int count = ((int)(sprintf(((char *)(hex)), "0x%llx", n)));

  return tos(hex, count);
}
bool array_byte_contains(array_byte a, byte val) {

  array_byte tmp32 = a;
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

  int tmp3 = 0;
  ;
  for (int tmp4 = tmp3; tmp4 < cap; tmp4++) {
    int i = tmp4;

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

  v_mapnode_delete(m->root, key, m->element_size);

  m->size--;
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

  map_string tmp9 = m;
  array_string keys_tmp9 = map_keys(&tmp9);
  for (int l = 0; l < keys_tmp9.len; l++) {
    string key = ((string *)keys_tmp9.data)[l];
    string val = {0};
    map_get(tmp9, key, &val);

    strings__Builder_writeln(
        &/* ? */ sb,
        _STR("  \"%.*s\" => \"%.*s\"", key.len, key.str, val.len, val.str));
  };

  strings__Builder_writeln(&/* ? */ sb, tos3("}"));

  return strings__Builder_str(sb);
}
Option opt_ok(void *data, int size) {

  if (size >= 255) {

    v_panic(
        _STR("option size too big: %d (max is 255), this is a temporary limit",
             size));
  };

  Option res = (Option){.ok = 1, .error = tos((byte *)"", 0), .is_none = 0};

  memcpy(res.data, data, size);

  return res;
}
Option opt_none() {

  return (Option){
      .is_none = 1,
      .error = tos((byte *)"", 0),
      .ok = 0,
  };
}
Option v_error(string s) { return (Option){.error = s, .ok = 0, .is_none = 0}; }
int vstrlen(byte *s) { return strlen(((char *)(s))); }
void todo() {}
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

    _PUSH(&idxs, (/*typ = array_int   tmp_typ=int*/ rstart + i), tmp7, int);

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
int v_string_int(string s) { return atoi(((char *)(s.str))); }
i64 string_i64(string s) { return atoll(((char *)(s.str))); }
f32 string_f32(string s) { return atof(((char *)(s.str))); }
f64 string_f64(string s) { return atof(((char *)(s.str))); }
u32 string_u32(string s) { return strtoul(((char *)(s.str)), 0, 0); }
u64 string_u64(string s) { return strtoull(((char *)(s.str)), 0, 0); }
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

    _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ s), tmp26, string);

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
              tmp33, string);
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

    _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ s), tmp35, string);

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

        _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ val), tmp41,
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

      _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ line), tmp47,
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

  string tmp61 = chars;
  array_byte bytes_tmp61 = string_bytes(tmp61);
  ;
  for (int tmp62 = 0; tmp62 < tmp61.len; tmp62++) {
    byte c = ((byte *)bytes_tmp61.data)[tmp62];

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

  array_string tmp85 = words;
  for (int tmp86 = 0; tmp86 < tmp85.len; tmp86++) {
    string word = ((string *)tmp85.data)[tmp86];

    _PUSH(&tit,
          (/*typ = array_string   tmp_typ=string*/ string_capitalize(word)),
          tmp87, string);
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

  array_string tmp92 = ar;
  for (int tmp93 = 0; tmp93 < tmp92.len; tmp93++) {
    string s = ((string *)tmp92.data)[tmp93];

    if (string_eq(s, val)) {

      return 1;
    };
  };

  return 0;
}
bool array_int_contains(array_int ar, int val) {

  array_int tmp94 = ar;
  for (int i = 0; i < tmp94.len; i++) {
    int s = ((int *)tmp94.data)[i];

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

    if (_IN(byte, (s.str[pos_left] /*rbyte 0*/), cs_arr)) {

      pos_left++;

      cs_match = 1;
    };

    if (_IN(byte, (s.str[pos_right] /*rbyte 0*/), cs_arr)) {

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

  while (pos <= s.len && _IN(byte, (s.str[pos] /*rbyte 0*/), cs_arr)) {

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

  while (pos >= -1 && _IN(byte, (s.str[pos] /*rbyte 0*/), cs_arr)) {

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

    _PUSH(&res.runes, (/*typ = array_int   tmp_typ=int*/ i), tmp108, int);

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

    _PUSH(&res.runes, (/*typ = array_int   tmp_typ=int*/ j), tmp117, int);

    i += char_len - 1;

    j += char_len;

    res.len++;
  };

  for (int i = 0; i < a.s.len; i++) {

    int char_len = utf8_char_len(a.s.str[/*ptr*/ i] /*rbyte 0*/);

    _PUSH(&res.runes, (/*typ = array_int   tmp_typ=int*/ j), tmp120, int);

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

  array_string tmp136 = a;
  for (int i = 0; i < tmp136.len; i++) {
    string val = ((string *)tmp136.data)[i];

    len += val.len + del.len;
  };

  len -= del.len;

  string res = tos3("");

  res.len = len;

  res.str = v_malloc(res.len + 1);

  int idx = 0;

  array_string tmp139 = a;
  for (int i = 0; i < tmp139.len; i++) {
    string val = ((string *)tmp139.data)[i];

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

    string tmp148 = s;
    array_byte bytes_tmp148 = string_bytes(tmp148);
    ;
    for (int tmp149 = 0; tmp149 < tmp148.len; tmp149++) {
      byte c = ((byte *)bytes_tmp148.data)[tmp149];

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

  int tmp152 = 0;
  ;
  for (int tmp153 = tmp152; tmp153 < count; tmp153++) {
    int i = tmp153;

    int tmp154 = 0;
    ;
    for (int tmp155 = tmp154; tmp155 < s.len; tmp155++) {
      int j = tmp155;

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
void strings__Builder_free(strings__Builder *b) { v_free(b->buf.data); }
int strings__levenshtein_distance(string a, string b) {

  array_int f =
      array_repeat(new_array_from_c_array(1, 1, sizeof(int),
                                          EMPTY_ARRAY_OF_ELEMS(int, 1){0}),
                   b.len + 1);

  string tmp2 = a;
  array_byte bytes_tmp2 = string_bytes(tmp2);
  ;
  for (int tmp3 = 0; tmp3 < tmp2.len; tmp3++) {
    byte ca = ((byte *)bytes_tmp2.data)[tmp3];

    int j = 1;

    int fj1 = (*(int *)array_get(f, 0));

    (*(int *)array_get(f, 0))++;

    string tmp10 = b;
    array_byte bytes_tmp10 = string_bytes(tmp10);
    ;
    for (int tmp11 = 0; tmp11 < tmp10.len; tmp11++) {
      byte cb = ((byte *)bytes_tmp10.data)[tmp11];

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

    string bigram = string_substr(a, i, i + 2);

    int tmp32 = 0;
    bool tmp33 = map_get(/*similarity.v : 47*/ first_bigrams, bigram, &tmp32);

    int q = (_IN_MAP((bigram), first_bigrams)) ? (tmp32 + 1) : (1);

    map_set(&first_bigrams, bigram, &(int[]){q});
  };

  int intersection_size = 0;

  for (int i = 0; i < b.len - 1; i++) {

    string bigram = string_substr(b, i, i + 2);

    int tmp38 = 0;
    bool tmp39 = map_get(/*similarity.v : 53*/ first_bigrams, bigram, &tmp38);

    int count = (_IN_MAP((bigram), first_bigrams)) ? (tmp38) : (0);

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

  string tmp5 = OPTION_CAST(string)((tos((byte *)str, fsize)));
  return opt_ok(&tmp5, sizeof(string));
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

    _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ tos_clone(buf)), tmp14,
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

  array_string tmp17 = lines;
  for (int tmp18 = 0; tmp18 < tmp17.len; tmp18++) {
    string myline = ((string *)tmp17.data)[tmp18];

    _PUSH(&ulines,
          (/*typ = array_ustring   tmp_typ=ustring*/ string_ustring(myline)),
          tmp19, ustring);
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

  os__File tmp24 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp24, sizeof(os__File));
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

  os__File tmp29 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp29, sizeof(os__File));
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

  os__File tmp34 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp34, sizeof(os__File));
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
FILE *os__popen(string path) {

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
int os__pclose(FILE *f) {

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
Option_os__Result os__exec(string cmd) {

  string pcmd = _STR("%.*s 2>&1", cmd.len, cmd.str);

  FILE *f = os__popen(pcmd);

  if (isnil(f)) {

    return v_error(_STR("exec(\"%.*s\") failed", cmd.len, cmd.str));
  };

  byte buf[1000] = {0};

  string res = tos3("");

  while (fgets(((char *)(buf)), 1000, f) != 0) {

    res = string_add(res, tos(buf, vstrlen(buf)));
  };

  res = string_trim_space(res);

  int exit_code = os__pclose(f);

  os__Result tmp46 = OPTION_CAST(os__Result)(
      (os__Result){.output = res, .exit_code = exit_code});
  return opt_ok(&tmp46, sizeof(os__Result));
}
int os__system(string cmd) {

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

  if (si == 1) { /* case */

    return tos3("SIGHUP");

  } else if (si == 2) { /* case */

    return tos3("SIGINT");

  } else if (si == 3) { /* case */

    return tos3("SIGQUIT");

  } else if (si == 4) { /* case */

    return tos3("SIGILL");

  } else if (si == 6) { /* case */

    return tos3("SIGABRT");

  } else if (si == 8) { /* case */

    return tos3("SIGFPE");

  } else if (si == 9) { /* case */

    return tos3("SIGKILL");

  } else if (si == 11) { /* case */

    return tos3("SIGSEGV");

  } else if (si == 13) { /* case */

    return tos3("SIGPIPE");

  } else if (si == 14) { /* case */

    return tos3("SIGALRM");

  } else if (si == 15) { /* case */

    return tos3("SIGTERM");
  };

#ifdef __linux__

  if (si == 30 || si == 10 || si == 16) { /* case */

    return tos3("SIGUSR1");

  } else if (si == 31 || si == 12 || si == 17) { /* case */

    return tos3("SIGUSR2");

  } else if (si == 20 || si == 17 || si == 18) { /* case */

    return tos3("SIGCHLD");

  } else if (si == 19 || si == 18 || si == 25) { /* case */

    return tos3("SIGCONT");

  } else if (si == 17 || si == 19 || si == 23) { /* case */

    return tos3("SIGSTOP");

  } else if (si == 18 || si == 20 || si == 24) { /* case */

    return tos3("SIGTSTP");

  } else if (si == 21 || si == 21 || si == 26) { /* case */

    return tos3("SIGTTIN");

  } else if (si == 22 || si == 22 || si == 27) { /* case */

    return tos3("SIGTTOU");

  } else if (si == 5) { /* case */

    return tos3("SIGTRAP");

  } else if (si == 7) { /* case */

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

  return string_right(path, pos);
}
string os__dir(string path) {

  if (string_eq(path, tos3("."))) {

    return os__getwd();
  };

  int pos = string_last_index(path, os__PathSeparator);

  if (pos == -1) {

    return tos3(".");
  };

  return string_left(path, pos);
}
string os__path_sans_ext(string path) {

  int pos = string_last_index(path, tos3("."));

  if (pos == -1) {

    return path;
  };

  return string_left(path, pos);
}
string os__basedir(string path) {

  int pos = string_last_index(path, os__PathSeparator);

  if (pos == -1) {

    return path;
  };

  return string_left(path, pos + 1);
}
string os__filename(string path) {

  return string_all_after(path, os__PathSeparator);
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

  if (is_atty(0)) {

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

    _PUSH(&inputstr, (/*typ = array_string   tmp_typ=string*/ line), tmp70,
          string);
  };

  return inputstr;
}
string os__get_lines_joined() {

  string line = tos3("");

  string inputstr = tos3("");

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

#ifdef _MSC_VER

  return tos3("windows");

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

  home = string_add(home, os__PathSeparator);

  return home;
}
void os__write_file(string path, string text) {

  Option_os__File tmp75 = os__create(path);
  if (!tmp75.ok) {
    string err = tmp75.error;

    return;
  }
  os__File f = *(os__File *)tmp75.data;
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

  return (statbuf.st_mode & os__S_IFMT) == os__S_IFDIR;

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

  res = ((int)(realpath((char *)fpath.str, (char *)fullpath)));

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

  array_string files = os__ls(path);

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string tmp105 = files;
  for (int i = 0; i < tmp105.len; i++) {
    string file = ((string *)tmp105.data)[i];

    if (string_starts_with(file, tos3("."))) {

      continue;
    };

    string p = string_add(string_add(path, os__PathSeparator), file);

    if (os__is_dir(p)) {

      _PUSH_MANY(&res,
                 (/*typ = array_string   tmp_typ=string*/ os__walk_ext(p, ext)),
                 tmp107, array_string);

    } else if (string_ends_with(file, ext)) {

      _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ p), tmp108, string);
    };
  };

  return res;
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
array_string os__init_os_args(int argc, byteptr *argv) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  for (int i = 0; i < argc; i++) {

    _PUSH(&args,
          (/*typ = array_string   tmp_typ=string*/ (
              tos2((byte *)argv[/*ptr*/ i] /*rbyteptr 0*/))),
          tmp3, string);
  };

  return args;
}
string os__get_error_msg(int code) {

  void *_ptr_text = strerror(code);

  if (_ptr_text == 0) {

    return tos3("");
  };

  return tos(_ptr_text, vstrlen(_ptr_text));
}
array_string os__ls(string path) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  void *dir = opendir((char *)path.str);

  if (isnil(dir)) {

    printf("ls() couldnt open dir \"%.*s\"\n", path.len, path.str);

    os__print_c_errno();

    return res;
  };

  struct /*c struct init*/

      dirent *ent = 0;

  while (1) {

    ent = readdir(dir);

    if (isnil(ent)) {

      break;
    };

    string name = tos_clone(((byteptr)(ent->d_name)));

    if (string_ne(name, tos3(".")) && string_ne(name, tos3("..")) &&
        string_ne(name, tos3(""))) {

      _PUSH(&res, (/*typ = array_string   tmp_typ=string*/ name), tmp9, string);
    };
  };

  closedir(dir);

  return res;
}
bool os__dir_exists(string path) {

  void *dir = opendir((char *)path.str);

  bool res = !isnil(dir);

  if (res) {

    closedir(dir);
  };

  return res;
}
void os__mkdir(string path) { mkdir((char *)path.str, 511); }
f64 math__abs(f64 a) {

  if (f64_lt(a, 0)) {

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

  array_int res = new_array_from_c_array(
      0, 0, sizeof(int), EMPTY_ARRAY_OF_ELEMS(int, 0){TCCSKIP(0)});

  while (n != 0) {

    _PUSH(&res, (/*typ = array_int   tmp_typ=int*/ (n % base) * sign), tmp4,
          int);

    n /= base;
  };

  return res;
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

  if (f64_gt(a, b)) {

    return a;
  };

  return b;
}
f64 math__min(f64 a, f64 b) {

  if (f64_lt(a, b)) {

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

  return is_atty(1) && string_ne(os__getenv(tos3("TERM")), tos3("dumb"));
}
bool term__can_show_color_on_stderr() {

  return is_atty(2) && string_ne(os__getenv(tos3("TERM")), tos3("dumb"));
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

  int end = ((int)((*(int *)array_get(time__daysBefore, month + 1))));

  if (day >= end) {

    month++;

    begin = end;

  } else {

    begin = ((int)((*(int *)array_get(time__daysBefore, month))));
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

  string am = tos3("am");

  int hour = t.hour;

  if (t.hour > 11) {

    am = tos3("pm");
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
string time__Time_ddmmy(time__Time t) {

  return _STR("%02d.%02d.%d", t.day, t.month, t.year);
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

  int pos = string_index(s, tos3(" "));

  if (pos <= 0) {

    println(tos3("bad time format"));

    return time__now();
  };

  string symd = string_left(s, pos);

  array_string ymd = string_split(symd, tos3("-"));

  if (ymd.len != 3) {

    println(tos3("bad time format"));

    return time__now();
  };

  string shms = string_right(s, pos);

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

  return string_substr(time__Days, i * 3, (i + 1) * 3);
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

  int res = (*(int *)array_get(time__MonthDays, month - 1)) + extra;

  int tmp60 = OPTION_CAST(int)(res);
  return opt_ok(&tmp60, sizeof(int));
}
string vweb_dot_tmpl__compile_template(string path) {

  Option_string tmp1 = os__read_file(path);
  if (!tmp1.ok) {
    string err = tmp1.error;

    v_panic(tos3("html failed"));
  }
  string html = *(string *)tmp1.data;
  ;

  string header = tos3("");

  if (os__file_exists(tos3("header.html"))) {

    Option_string tmp3 = os__read_file(tos3("header.html"));
    if (!tmp3.ok) {
      string err = tmp3.error;

      v_panic(tos3("html failed"));
    }
    string h = *(string *)tmp3.data;
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

  array_string tmp8 = lines;
  for (int tmp9 = 0; tmp9 < tmp8.len; tmp9++) {
    string _line = ((string *)tmp8.data)[tmp9];

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
          string_add(string_add(tos3("if "), string_right(line, pos + 4)),
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
          string_add(string_add(tos3("for "), string_right(line, pos + 4)),
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

    return _STR("%6d ms | %.*s", tdiff, s.len, s.str);
  };

  return s;
}
i64 benchmark__now() { return time__ticks(); }
void V_cc(V *v) {

  V_build_thirdparty_obj_files(&/* ? */ *v);

  if (string_ends_with(v->out_name, tos3(".c")) ||
      string_ends_with(v->out_name, tos3(".js"))) {

#ifndef _VJS

    if (string_ends_with(v->out_name, tos3(".js"))) {

      string vexe = os__executable();

      string vjs_path = string_add(vexe, tos3("js"));

      string dir = os__dir(vexe);

      if (!os__file_exists(vjs_path)) {

        println(tos3("V.js compiler not found, building..."));

        int ret = os__system(_STR("%.*s -o %.*s -os js %.*s/compiler", vexe.len,
                                  vexe.str, vjs_path.len, vjs_path.str, dir.len,
                                  dir.str));

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

  array_string a = new_array_from_c_array(
      3, 3, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 3){v->pref->cflags, tos3("-std=gnu11"),
                                      tos3("-w")});

  if (v->pref->is_so) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-shared -fPIC ")),
          tmp7, string);

    v->out_name = string_add(v->out_name, tos3(".so"));
  };

  if (v->pref->build_mode == main__BuildMode_build_module) {

    string out_dir = _STR("%.*s%.*s%.*s", main__v_modules_path.len,
                          main__v_modules_path.str, os__PathSeparator.len,
                          os__PathSeparator.str, v->dir.len, v->dir.str);

    if (!os__dir_exists(out_dir)) {

      os__mkdir(out_dir);
    };

    v->out_name = _STR("%.*s.o", out_dir.len, out_dir.str);

    printf("Building %.*s...\n", v->out_name.len, v->out_name.str);
  };

  string debug_options = tos3("");

  string optimization_options = tos3("-O2");

  if (string_contains(v->pref->ccompiler, tos3("clang"))) {

    if (v->pref->is_debuggable) {

      debug_options = tos3("-g -O0");
    };

    optimization_options = tos3("-O3 -flto");
  };

  if (string_contains(v->pref->ccompiler, tos3("gcc"))) {

    if (v->pref->is_debug) {

      debug_options = tos3("-g3");
    };

    optimization_options = tos3("-O3 -fno-strict-aliasing -flto");
  };

  if (v->pref->is_prod) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ optimization_options),
          tmp11, string);

  } else {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ debug_options), tmp12,
          string);
  };

  if (v->pref->is_debuggable && string_ne(os__user_os(), tos3("windows"))) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3(" -rdynamic ")),
          tmp13, string);
  };

  if (v->os != main__OS_msvc && v->os != main__OS_freebsd) {

    _PUSH(&a,
          (/*typ = array_string   tmp_typ=string*/ tos3(
              "-Werror=implicit-function-declaration")),
          tmp14, string);
  };

  array_string tmp15 = V_generate_hotcode_reloading_compiler_flags(&/* ? */ *v);
  for (int tmp16 = 0; tmp16 < tmp15.len; tmp16++) {
    string f = ((string *)tmp15.data)[tmp16];

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ f), tmp17, string);
  };

  string libs = tos3("");

  if (v->pref->build_mode == main__BuildMode_build_module) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-c")), tmp19,
          string);

  } else if (v->pref->is_debug) {

    string vexe = os__executable();

    string builtin_o_path =
        _STR("%.*s/vlib/builtin.o", main__v_modules_path.len,
             main__v_modules_path.str);

    if (os__file_exists(builtin_o_path)) {

      libs = builtin_o_path;

    } else {

      printf("%.*s not found... building module builtin\n", builtin_o_path.len,
             builtin_o_path.str);

      os__system(_STR("%.*s build module vlib/builtin", vexe.len, vexe.str));
    };

    array_string tmp22 = v->table->imports;
    for (int tmp23 = 0; tmp23 < tmp22.len; tmp23++) {
      string imp = ((string *)tmp22.data)[tmp23];

      if (string_eq(imp, tos3("webview"))) {

        continue;
      };

      string path = _STR("%.*s/vlib/%.*s.o", main__v_modules_path.len,
                         main__v_modules_path.str, imp.len, imp.str);

      printf("adding %.*s.o\n", imp.len, imp.str);

      if (os__file_exists(path)) {

        libs = string_add(libs, string_add(tos3(" "), path));

      } else {

        printf("%.*s not found... building module %.*s\n", path.len, path.str,
               imp.len, imp.str);

        os__system(_STR("%.*s build module vlib/%.*s", vexe.len, vexe.str,
                        imp.len, imp.str));
      };
    };
  };

  if (v->pref->sanitize) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-fsanitize=leak")),
          tmp25, string);
  };

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-o \"%.*s\"", v->out_name.len, v->out_name.str)),
        tmp26, string);

  if (os__dir_exists(v->out_name)) {

    main__verror(
        _STR("\'%.*s\' is a directory", v->out_name.len, v->out_name.str));
  };

  if (v->os == main__OS_mac) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-x objective-c")),
          tmp27, string);
  };

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "\"%.*s\"", v->out_name_c.len, v->out_name_c.str)),
        tmp28, string);

  if (v->os == main__OS_mac) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-x none")), tmp29,
          string);
  };

  if (v->os == main__OS_mac) {

    _PUSH(&a,
          (/*typ = array_string   tmp_typ=string*/ tos3(
              "-mmacosx-version-min=10.7")),
          tmp30, string);
  };

  array_CFlag cflags = V_get_os_cflags(&/* ? */ *v);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/
         array_CFlag_c_options_only_object_files(cflags)),
        tmp32, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/
         array_CFlag_c_options_without_object_files(cflags)),
        tmp33, string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ libs), tmp34, string);

  if (v->pref->build_mode != main__BuildMode_build_module &&
      (v->os == main__OS_linux || v->os == main__OS_freebsd ||
       v->os == main__OS_openbsd || v->os == main__OS_netbsd ||
       v->os == main__OS_dragonfly || v->os == main__OS_solaris)) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-lm -lpthread ")),
          tmp35, string);

    if (v->os == main__OS_linux) {

      _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3(" -ldl ")), tmp36,
            string);
    };
  };

  if (v->os == main__OS_js && string_eq(os__user_os(), tos3("linux"))) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-lm")), tmp37,
          string);
  };

  string args = array_string_join(a, tos3(" "));

  string cmd = _STR("%.*s %.*s", v->pref->ccompiler.len, v->pref->ccompiler.str,
                    args.len, args.str);

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    println(tos3("\n=========="));

    println(cmd);
  };

  i64 ticks = time__ticks();

  Option_os__Result tmp41 = os__exec(cmd);
  if (!tmp41.ok) {
    string err = tmp41.error;

    main__verror(err);

    return;
  }
  os__Result res = *(os__Result *)tmp41.data;
  ;

  if (res.exit_code != 0) {

    if (res.exit_code == 127) {

      main__verror(string_add(
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

        println(
            tos3("...\n(Use `v -debug` to print the entire error message)\n"));

      } else {

        println(tos3(""));
      };
    };

    main__verror(
        string_add(tos3("C error. This should never happen. "),
                   tos3("Please create a GitHub issue: "
                        "https://github.com/vlang/v/issues/new/choose")));
  };

  i64 diff = time__ticks() - ticks;

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    printf("%.*s took %lld ms\n", v->pref->ccompiler.len,
           v->pref->ccompiler.str, diff);

    println(tos3("=========\n"));
  };

  if (!v->pref->is_debug && string_ne(v->out_name_c, tos3("v.c"))) {

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
void V_cc_windows_cross(V *c) {

  if (!string_ends_with(c->out_name, tos3(".exe"))) {

    c->out_name = string_add(c->out_name, tos3(".exe"));
  };

  string args = _STR("-o %.*s -w -L. ", c->out_name.len, c->out_name.str);

  array_CFlag cflags = V_get_os_cflags(&/* ? */ *c);

  args = string_add(args, array_CFlag_c_options_before_target(cflags));

  string libs = tos3("");

  if (c->pref->build_mode == main__BuildMode_default_mode) {

    libs = _STR("\"%.*s/vlib/builtin.o\"", main__v_modules_path.len,
                main__v_modules_path.str);

    if (!os__file_exists(libs)) {

      printf("`%.*s` not found\n", libs.len, libs.str);

      v_exit(1);
    };

    array_string tmp49 = c->table->imports;
    for (int tmp50 = 0; tmp50 < tmp49.len; tmp50++) {
      string imp = ((string *)tmp49.data)[tmp50];

      libs = string_add(libs,
                        _STR(" \"%.*s/vlib/%.*s.o\"", main__v_modules_path.len,
                             main__v_modules_path.str, imp.len, imp.str));
    };
  };

  args = string_add(args, _STR(" %.*s ", c->out_name_c.len, c->out_name_c.str));

  args = string_add(args, array_CFlag_c_options_after_target(cflags));

  println(tos3("Cross compiling for Windows..."));

  string winroot =
      _STR("%.*s/winroot", main__v_modules_path.len, main__v_modules_path.str);

  if (!os__dir_exists(winroot)) {

    string winroot_url = tos3(
        "https://github.com/vlang/v/releases/download/v0.1.10/winroot.zip");

    printf("\"%.*s\" not found.\n", winroot.len, winroot.str);

    printf("Download it from %.*s and save it in %.*s\n", winroot_url.len,
           winroot_url.str, main__v_modules_path.len, main__v_modules_path.str);

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
           main__v_modules_path.len, main__v_modules_path.str,
           c->out_name_c.len, c->out_name_c.str);

  if (c->pref->show_c_cmd) {

    println(cmd);
  };

  if (os__system(cmd) != 0) {

    println(tos3("Cross compilation for Windows failed. Make sure you have "
                 "clang installed."));

    v_exit(1);
  };

  if (c->pref->build_mode != main__BuildMode_build_module) {

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
void V_build_thirdparty_obj_files(V *c) {

  array_CFlag tmp57 = V_get_os_cflags(&/* ? */ *c);
  for (int tmp58 = 0; tmp58 < tmp57.len; tmp58++) {
    CFlag flag = ((CFlag *)tmp57.data)[tmp58];

    if (string_ends_with(flag.value, tos3(".o"))) {

      array_CFlag rest_of_module_flags = V_get_rest_of_module_cflags(
          &/* ? */ *c, &/*112 EXP:"CFlag*" GOT:"CFlag" */ flag);

      if (c->os == main__OS_msvc) {

        main__build_thirdparty_obj_file_with_msvc(flag.value,
                                                  rest_of_module_flags);

      } else {

        main__build_thirdparty_obj_file(flag.value, rest_of_module_flags);
      };
    };
  };
}
string main__find_c_compiler() {

  string args = array_string_join(main__env_vflags_and_os_args(), tos3(" "));

  string defaultcc = main__find_c_compiler_default();

  return main__get_arg(args, tos3("cc"), defaultcc);
}
string main__find_c_compiler_default() {

#ifdef _WIN32

  return tos3("gcc");

#endif
  ;

  return tos3("cc");
}
string main__find_c_compiler_thirdparty_options() {

  array_string fullargs = main__env_vflags_and_os_args();

  string cflags = main__get_cmdline_cflags(fullargs);

#ifndef _WIN32

  cflags = string_add(cflags, tos3(" -fPIC"));

#endif
  ;

  if (_IN(string, (tos3("-m32")), fullargs)) {

    cflags = string_add(cflags, tos3(" -m32"));
  };

  return cflags;
}
string main__get_cmdline_cflags(array_string args) {

  string cflags = tos3("");

  array_string tmp65 = args;
  for (int ci = 0; ci < tmp65.len; ci++) {
    string cv = ((string *)tmp65.data)[ci];

    if (string_eq(cv, tos3("-cflags"))) {

      cflags = string_add(
          cflags, string_add((*(string *)array_get(args, ci + 1)), tos3(" ")));
    };
  };

  return cflags;
}
string CFlag_str(CFlag *c) {

  return _STR(
      "CFlag{ name: \"%.*s\" value: \"%.*s\" mod: \"%.*s\" os: \"%.*s\" }",
      c->name.len, c->name.str, c->value.len, c->value.str, c->mod.len,
      c->mod.str, c->os.len, c->os.str);
}
array_CFlag V_get_os_cflags(V *v) {

  array_CFlag flags = new_array_from_c_array(
      0, 0, sizeof(CFlag), EMPTY_ARRAY_OF_ELEMS(CFlag, 0){TCCSKIP(0)});

  array_CFlag tmp2 = v->table->cflags;
  for (int tmp3 = 0; tmp3 < tmp2.len; tmp3++) {
    CFlag flag = ((CFlag *)tmp2.data)[tmp3];

    if (string_eq(flag.os, tos3("")) ||
        (string_eq(flag.os, tos3("linux")) && v->os == main__OS_linux) ||
        (string_eq(flag.os, tos3("darwin")) && v->os == main__OS_mac) ||
        (string_eq(flag.os, tos3("freebsd")) && v->os == main__OS_freebsd) ||
        (string_eq(flag.os, tos3("windows")) &&
         (v->os == main__OS_windows || v->os == main__OS_msvc))) {

      _PUSH(&flags, (/*typ = array_CFlag   tmp_typ=CFlag*/ flag), tmp4, CFlag);
    };
  };

  return flags;
}
array_CFlag V_get_rest_of_module_cflags(V *v, CFlag *c) {

  array_CFlag flags = new_array_from_c_array(
      0, 0, sizeof(CFlag), EMPTY_ARRAY_OF_ELEMS(CFlag, 0){TCCSKIP(0)});

  array_CFlag cflags = V_get_os_cflags(&/* ? */ *v);

  array_CFlag tmp7 = cflags;
  for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
    CFlag flag = ((CFlag *)tmp7.data)[tmp8];

    if (string_eq(c->mod, flag.mod)) {

      if (string_eq(c->name, flag.name) && string_eq(c->value, flag.value) &&
          string_eq(c->os, flag.os)) {

        continue;
      };

      _PUSH(&flags, (/*typ = array_CFlag   tmp_typ=CFlag*/ flag), tmp9, CFlag);
    };
  };

  return flags;
}
string CFlag_format(CFlag *cf) {

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
bool Table_has_cflag(Table *table, CFlag cflag) {

  array_CFlag tmp11 = table->cflags;
  for (int tmp12 = 0; tmp12 < tmp11.len; tmp12++) {
    CFlag cf = ((CFlag *)tmp11.data)[tmp12];

    if (string_eq(cf.os, cflag.os) && string_eq(cf.name, cflag.name) &&
        string_eq(cf.value, cflag.value)) {

      return 1;
    };
  };

  return 0;
}
void Table_parse_cflag(Table *table, string cflag, string mod) {

  array_string allowed_flags =
      new_array_from_c_array(5, 5, sizeof(string),
                             EMPTY_ARRAY_OF_ELEMS(string, 5){
                                 tos3("framework"),
                                 tos3("library"),
                                 tos3("I"),
                                 tos3("l"),
                                 tos3("L"),
                             });

  string flag = string_trim_space(cflag);

  if (string_eq(flag, tos3(""))) {

    return;
  };

  string fos = tos3("");

  string name = tos3("");

  if (string_starts_with(flag, tos3("linux")) ||
      string_starts_with(flag, tos3("darwin")) ||
      string_starts_with(flag, tos3("freebsd")) ||
      string_starts_with(flag, tos3("windows"))) {

    int pos = string_index(flag, tos3(" "));

    fos = string_trim_space(string_left(flag, pos));

    flag = string_trim_space(string_right(flag, pos));
  };

  while (1) {

    int index = -1;

    string value = tos3("");

    if (string_at(flag, 0) == '-') {

      array_string tmp22 = allowed_flags;
      for (int tmp23 = 0; tmp23 < tmp22.len; tmp23++) {
        string f = ((string *)tmp22.data)[tmp23];

        int i = 1 + f.len;

        if (i < flag.len && string_eq(f, string_substr(flag, 1, i))) {

          name = string_trim_space(string_left(flag, i));

          flag = string_trim_space(string_right(flag, i));

          break;
        };
      };
    };

    array_int tmp25 = new_array_from_c_array(
        2, 2, sizeof(int),
        EMPTY_ARRAY_OF_ELEMS(int, 2){string_index(flag, tos3(" ")),
                                     string_index(flag, tos3(","))});
    for (int tmp26 = 0; tmp26 < tmp25.len; tmp26++) {
      int i = ((int *)tmp25.data)[tmp26];

      if (index == -1 || (i != -1 && i < index)) {

        index = i;
      };
    };

    if (index != -1 && string_at(flag, index) == ' ' &&
        string_at(flag, index + 1) == '-') {

      array_string tmp31 = allowed_flags;
      for (int tmp32 = 0; tmp32 < tmp31.len; tmp32++) {
        string f = ((string *)tmp31.data)[tmp32];

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

    CFlag cf = (CFlag){.mod = mod, .os = fos, .name = name, .value = value};

    if (!Table_has_cflag(&/* ? */ *table, cf)) {

      _PUSH(&table->cflags, (/*typ = array_CFlag   tmp_typ=CFlag*/ cf), tmp37,
            CFlag);
    };

    if (index == -1) {

      break;
    };
  };
}
string array_CFlag_c_options_before_target(array_CFlag cflags) {

#ifdef _MSC_VER

  return tos3("");

#endif
  ;

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_CFlag tmp39 = cflags;
  for (int tmp40 = 0; tmp40 < tmp39.len; tmp40++) {
    CFlag flag = ((CFlag *)tmp39.data)[tmp40];

    if (string_ne(flag.name, tos3("-l"))) {

      _PUSH(
          &args,
          (/*typ = array_string   tmp_typ=string*/ CFlag_format(&/* ? */ flag)),
          tmp41, string);
    };
  };

  return array_string_join(args, tos3(" "));
}
string array_CFlag_c_options_after_target(array_CFlag cflags) {

#ifdef _MSC_VER

  return tos3("");

#endif
  ;

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_CFlag tmp43 = cflags;
  for (int tmp44 = 0; tmp44 < tmp43.len; tmp44++) {
    CFlag flag = ((CFlag *)tmp43.data)[tmp44];

    if (string_eq(flag.name, tos3("-l"))) {

      _PUSH(
          &args,
          (/*typ = array_string   tmp_typ=string*/ CFlag_format(&/* ? */ flag)),
          tmp45, string);
    };
  };

  return array_string_join(args, tos3(" "));
}
string array_CFlag_c_options_without_object_files(array_CFlag cflags) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_CFlag tmp47 = cflags;
  for (int tmp48 = 0; tmp48 < tmp47.len; tmp48++) {
    CFlag flag = ((CFlag *)tmp47.data)[tmp48];

    if (string_ends_with(flag.value, tos3(".o")) ||
        string_ends_with(flag.value, tos3(".obj"))) {

      continue;
    };

    _PUSH(&args,
          (/*typ = array_string   tmp_typ=string*/ CFlag_format(&/* ? */ flag)),
          tmp49, string);
  };

  return array_string_join(args, tos3(" "));
}
string array_CFlag_c_options_only_object_files(array_CFlag cflags) {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_CFlag tmp51 = cflags;
  for (int tmp52 = 0; tmp52 < tmp51.len; tmp52++) {
    CFlag flag = ((CFlag *)tmp51.data)[tmp52];

    if (string_ends_with(flag.value, tos3(".o")) ||
        string_ends_with(flag.value, tos3(".obj"))) {

      _PUSH(
          &args,
          (/*typ = array_string   tmp_typ=string*/ CFlag_format(&/* ? */ flag)),
          tmp53, string);
    };
  };

  return array_string_join(args, tos3(" "));
}
CGen *main__new_cgen(string out_name_c) {

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

  if (string_ne(g->cur_line, tos3(""))) {

    if (g->line_directives &&
        string_ne(string_trim_space(g->cur_line), tos3(""))) {

      if (g->file.len > 0 && g->line > 0) {

        _PUSH(&g->lines,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "\n#line %d \"%.*s\"", g->line, g->file.len, g->file.str)),
              tmp4, string);
      };
    };

    _PUSH(&g->lines, (/*typ = array_string   tmp_typ=string*/ g->cur_line),
          tmp5, string);

    g->prev_line = g->cur_line;

    g->cur_line = tos3("");
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

  string s = array_string_join(g->lines, tos3("\n"));

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

  g->tmp_line = tos3("");

  g->is_tmp = 1;
}
string CGen_end_tmp(CGen *g) {

  g->is_tmp = 0;

  string res = g->tmp_line;

  g->tmp_line = tos3("");

  return res;
}
int CGen_add_placeholder(CGen *g) {

  if (g->is_tmp) {

    return g->tmp_line.len;
  };

  return g->cur_line.len;
}
void CGen_start_cut(CGen *g) { g->cut_pos = CGen_add_placeholder(&/* ? */ *g); }
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

  if (g->nogen) {

    return;
  };

  string prev = (*(string *)array_get(g->lines, g->lines.len - 1));

  array_set(&/*q*/ g->lines, g->lines.len - 1,
            &(string[]){
                _STR("%.*s \n %.*s \n", prev.len, prev.str, val.len, val.str)});
}
void CGen_register_thread_fn(CGen *g, string wrapper_name, string wrapper_text,
                             string struct_text) {

  array_string tmp18 = g->thread_args;
  for (int tmp19 = 0; tmp19 < tmp18.len; tmp19++) {
    string arg = ((string *)tmp18.data)[tmp19];

    if (string_contains(arg, wrapper_name)) {

      return;
    };
  };

  _PUSH(&g->thread_args, (/*typ = array_string   tmp_typ=string*/ struct_text),
        tmp20, string);

  _PUSH(&g->thread_args, (/*typ = array_string   tmp_typ=string*/ wrapper_text),
        tmp21, string);
}
string V_prof_counters(V *v) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  return array_string_join(res, tos3(";\n"));
}
string Parser_print_prof_counters(Parser *p) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  return array_string_join(res, tos3(";\n"));
}
void Parser_gen_typedef(Parser *p, string s) {

  if (!Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->typedefs, (/*typ = array_string   tmp_typ=string*/ s), tmp24,
        string);
}
void Parser_gen_type_alias(Parser *p, string s) {

  if (!Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->type_aliases, (/*typ = array_string   tmp_typ=string*/ s),
        tmp25, string);
}
void CGen_add_to_main(CGen *g, string s) {

  g->fn_main = string_add(g->fn_main, s);
}
void main__build_thirdparty_obj_file(string path, array_CFlag moduleflags) {

  string obj_path = os__realpath(path);

  if (os__file_exists(obj_path)) {

    return;
  };

  printf("%.*s not found, building it...\n", obj_path.len, obj_path.str);

  string parent = os__dir(obj_path);

  array_string files = os__ls(parent);

  string cfiles = tos3("");

  array_string tmp30 = files;
  for (int tmp31 = 0; tmp31 < tmp30.len; tmp31++) {
    string file = ((string *)tmp30.data)[tmp31];

    if (string_ends_with(file, tos3(".c"))) {

      cfiles = string_add(
          cfiles,
          string_add(
              string_add(tos3("\""),
                         os__realpath(string_add(
                             string_add(parent, os__PathSeparator), file))),
              tos3("\" ")));
    };
  };

  string cc = main__find_c_compiler();

  string cc_thirdparty_options = main__find_c_compiler_thirdparty_options();

  string btarget = array_CFlag_c_options_before_target(moduleflags);

  string atarget = array_CFlag_c_options_after_target(moduleflags);

  string cmd = _STR("%.*s %.*s %.*s -c -o \"%.*s\" %.*s %.*s ", cc.len, cc.str,
                    cc_thirdparty_options.len, cc_thirdparty_options.str,
                    btarget.len, btarget.str, obj_path.len, obj_path.str,
                    cfiles.len, cfiles.str, atarget.len, atarget.str);

  Option_os__Result tmp37 = os__exec(cmd);
  if (!tmp37.ok) {
    string err = tmp37.error;

    printf("failed thirdparty object build cmd: %.*s\n", cmd.len, cmd.str);

    main__verror(err);

    return;
  }
  os__Result res = *(os__Result *)tmp37.data;
  ;

  println(res.output);
}
string main__os_name_to_ifdef(string name) {

  if (string_eq(name, tos3("windows"))) { /* case */

    return tos3("_WIN32");

  } else if (string_eq(name, tos3("mac"))) { /* case */

    return tos3("__APPLE__");

  } else if (string_eq(name, tos3("linux"))) { /* case */

    return tos3("__linux__");

  } else if (string_eq(name, tos3("freebsd"))) { /* case */

    return tos3("__FreeBSD__");

  } else if (string_eq(name, tos3("openbsd"))) { /* case */

    return tos3("__OpenBSD__");

  } else if (string_eq(name, tos3("netbsd"))) { /* case */

    return tos3("__NetBSD__");

  } else if (string_eq(name, tos3("dragonfly"))) { /* case */

    return tos3("__DragonFly__");

  } else if (string_eq(name, tos3("msvc"))) { /* case */

    return tos3("_MSC_VER");

  } else if (string_eq(name, tos3("android"))) { /* case */

    return tos3("__BIONIC__");

  } else if (string_eq(name, tos3("js"))) { /* case */

    return tos3("_VJS");

  } else if (string_eq(name, tos3("solaris"))) { /* case */

    return tos3("__sun");
  };

  main__verror(_STR("bad os ifdef name \"%.*s\"", name.len, name.str));

  return tos3("");
}
string main__platform_postfix_to_ifdefguard(string name) {

  if (string_eq(name, tos3(".v"))) { /* case */

    return tos3("");

  } else if (string_eq(name, tos3("_win.v"))) { /* case */

    return tos3("#ifdef _WIN32");

  } else if (string_eq(name, tos3("_nix.v"))) { /* case */

    return tos3("#ifndef _WIN32");

  } else if (string_eq(name, tos3("_lin.v"))) { /* case */

    return tos3("#ifdef __linux__");

  } else if (string_eq(name, tos3("_mac.v"))) { /* case */

    return tos3("#ifdef __APPLE__");

  } else if (string_eq(name, tos3("_solaris.v"))) { /* case */

    return tos3("#ifdef __sun");
  };

  main__verror(_STR("bad platform_postfix \"%.*s\"", name.len, name.str));

  return tos3("");
}
string V_type_definitions(V *v) {

  array_Type types = new_array_from_c_array(
      0, 0, sizeof(Type), EMPTY_ARRAY_OF_ELEMS(Type, 0){TCCSKIP(0)});

  array_Type builtin_types = new_array_from_c_array(
      0, 0, sizeof(Type), EMPTY_ARRAY_OF_ELEMS(Type, 0){TCCSKIP(0)});

  array_string builtins = new_array_from_c_array(
      4, 4, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 4){tos3("string"), tos3("array"),
                                      tos3("map"), tos3("Option")});

  array_string tmp41 = builtins;
  for (int tmp42 = 0; tmp42 < tmp41.len; tmp42++) {
    string builtin = ((string *)tmp41.data)[tmp42];

    Type tmp43 = {0};
    bool tmp44 = map_get(/*cgen.v : 313*/ v->table->typesmap, builtin, &tmp43);

    Type typ = tmp43;

    _PUSH(&builtin_types, (/*typ = array_Type   tmp_typ=Type*/ typ), tmp46,
          Type);
  };

  map_Type tmp47 = v->table->typesmap;
  array_string keys_tmp47 = map_keys(&tmp47);
  for (int l = 0; l < keys_tmp47.len; l++) {
    string t_name = ((string *)keys_tmp47.data)[l];
    Type t = {0};
    map_get(tmp47, t_name, &t);

    if (_IN(string, (t_name), builtins)) {

      continue;
    };

    _PUSH(&types, (/*typ = array_Type   tmp_typ=Type*/ t), tmp48, Type);
  };

  array_Type types_sorted = main__sort_structs(types);

  string res = string_add(
      string_add(main__types_to_c(builtin_types, v->table), tos3("\n//----\n")),
      main__types_to_c(types_sorted, v->table));

  return res;
}
array_Type main__sort_structs(array_Type types) {

  DepGraph *dep_graph = main__new_dep_graph();

  array_string type_names = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_Type tmp53 = types;
  for (int tmp54 = 0; tmp54 < tmp53.len; tmp54++) {
    Type t = ((Type *)tmp53.data)[tmp54];

    _PUSH(&type_names, (/*typ = array_string   tmp_typ=string*/ t.name), tmp55,
          string);
  };

  array_Type tmp56 = types;
  for (int tmp57 = 0; tmp57 < tmp56.len; tmp57++) {
    Type t = ((Type *)tmp56.data)[tmp57];

    array_string field_deps = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    array_Var tmp59 = t.fields;
    for (int tmp60 = 0; tmp60 < tmp59.len; tmp60++) {
      Var field = ((Var *)tmp59.data)[tmp60];

      if (!(_IN(string, (field.typ), type_names)) ||
          _IN(string, (field.typ), field_deps)) {

        continue;
      };

      _PUSH(&field_deps, (/*typ = array_string   tmp_typ=string*/ field.typ),
            tmp61, string);
    };

    DepGraph_add(dep_graph, t.name, field_deps);
  };

  DepGraph *dep_graph_sorted = DepGraph_resolve(&/* ? */ *dep_graph);

  if (!dep_graph_sorted->acyclic) {

    main__verror(tos3(
        "error: cgen.sort_structs() DGNAC.\nplease create a new issue here: "
        "https://github.com/vlang/v/issues and tag @joe-conigliaro"));
  };

  array_Type types_sorted = new_array_from_c_array(
      0, 0, sizeof(Type), EMPTY_ARRAY_OF_ELEMS(Type, 0){TCCSKIP(0)});

  array_DepGraphNode tmp64 = dep_graph_sorted->nodes;
  for (int tmp65 = 0; tmp65 < tmp64.len; tmp65++) {
    DepGraphNode node = ((DepGraphNode *)tmp64.data)[tmp65];

    array_Type tmp66 = types;
    for (int tmp67 = 0; tmp67 < tmp66.len; tmp67++) {
      Type t = ((Type *)tmp66.data)[tmp67];

      if (string_eq(t.name, node.name)) {

        _PUSH(&types_sorted, (/*typ = array_Type   tmp_typ=Type*/ t), tmp68,
              Type);

        continue;
      };
    };
  };

  return types_sorted;
}
void Parser_error(Parser *p, string s) {

  Parser_error_with_token_index(p, s, p->token_idx - 1);
}
void Parser_warn(Parser *p, string s) {

  Parser_warn_with_token_index(p, s, p->token_idx - 1);
}
void Parser_production_error_with_token_index(Parser *p, string e,
                                              int tokenindex) {

  if (p->pref->is_prod) {

    Parser_error_with_token_index(p, e, tokenindex);

  } else {

    Parser_warn_with_token_index(p, e, tokenindex);
  };
}
void Parser_error_with_token_index(Parser *p, string s, int tokenindex) {

  Parser_error_with_position(
      p, s,
      Scanner_get_scanner_pos_of_token(
          p->scanner, &/*112 EXP:"Token*" GOT:"Token" */ (
                          *(Token *)array_get(p->tokens, tokenindex))));
}
void Parser_warn_with_token_index(Parser *p, string s, int tokenindex) {

  Parser_warn_with_position(
      p, s,
      Scanner_get_scanner_pos_of_token(
          p->scanner, &/*112 EXP:"Token*" GOT:"Token" */ (
                          *(Token *)array_get(p->tokens, tokenindex))));
}
void Parser_error_with_position(Parser *p, string s, ScannerPos sp) {

  Parser_print_error_context(p);

  string e = main__normalized_error(s);

  Scanner_goto_scanner_position(p->scanner, sp);

  Scanner_error_with_col(&/* ? */ *p->scanner, e, sp.pos - sp.last_nl_pos);
}
void Parser_warn_with_position(Parser *p, string s, ScannerPos sp) {

  ScannerPos cpos = Scanner_get_scanner_pos(&/* ? */ *p->scanner);

  string e = main__normalized_error(s);

  Scanner_goto_scanner_position(p->scanner, sp);

  Scanner_warn_with_col(&/* ? */ *p->scanner, e, sp.pos - sp.last_nl_pos);

  Scanner_goto_scanner_position(p->scanner, cpos);
}
void Scanner_error(Scanner *s, string msg) {

  Scanner_error_with_col(&/* ? */ *s, msg, 0);
}
void Scanner_warn(Scanner *s, string msg) {

  Scanner_warn_with_col(&/* ? */ *s, msg, 0);
}
void Scanner_warn_with_col(Scanner *s, string msg, int col) {

  string fullpath = Scanner_get_error_filepath(&/* ? */ *s);

  bool color_on = Scanner_is_color_output_on(&/* ? */ *s);

  string final_message =
      (color_on) ? (term__bold(term__bright_blue(msg))) : (msg);

  eprintln(_STR("warning: %.*s:%d:%d: %.*s", fullpath.len, fullpath.str,
                s->line_nr + 1, col, final_message.len, final_message.str));
}
void Scanner_error_with_col(Scanner *s, string msg, int col) {

  string fullpath = Scanner_get_error_filepath(&/* ? */ *s);

  bool color_on = Scanner_is_color_output_on(&/* ? */ *s);

  string final_message = (color_on) ? (term__red(term__bold(msg))) : (msg);

  eprintln(_STR("%.*s:%d:%d: %.*s", fullpath.len, fullpath.str, s->line_nr + 1,
                col, final_message.len, final_message.str));

  if (s->should_print_line_on_error && s->file_lines.len > 0) {

    int context_start_line =
        main__imax(0, (s->line_nr - main__error_context_before + 1));

    int context_end_line = main__imin(
        s->file_lines.len, (s->line_nr + main__error_context_after + 1));

    for (int cline = context_start_line; cline < context_end_line; cline++) {

      string line = string_add(_STR("%5d| ", (cline + 1)),
                               (*(string *)array_get(s->file_lines, cline)));

      string coloredline =
          (cline == s->line_nr && color_on) ? (term__red(line)) : (line);

      eprintln(coloredline);

      if (cline != s->line_nr) {

        continue;
      };

      array_string pointerline = new_array_from_c_array(
          0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

      string tmp22 = line;
      array_byte bytes_tmp22 = string_bytes(tmp22);
      ;
      for (int i = 0; i < tmp22.len; i++) {
        byte c = ((byte *)bytes_tmp22.data)[i];

        if (i < col) {

          byte x = (byte_is_space(c)) ? (c) : (' ');

          _PUSH(&pointerline,
                (/*typ = array_string   tmp_typ=string*/ byte_str(x)), tmp24,
                string);

          continue;
        };

        _PUSH(&pointerline,
              (/*typ = array_string   tmp_typ=string*/ (color_on)
                   ? (term__bold(term__blue(tos3("^"))))
                   : (tos3("^"))),
              tmp25, string);

        break;
      };

      eprintln(
          string_add(tos3("      "), array_string_join(pointerline, tos3(""))));
    };
  };

  v_exit(1);
}
static inline int Parser_cur_tok_index(Parser *p) { return p->token_idx - 1; }
static inline int main__imax(int a, int b) { return (a > b) ? (a) : (b); }
static inline int main__imin(int a, int b) { return (a < b) ? (a) : (b); }
string Scanner_get_error_filepath(Scanner *s) {

  if (s->should_print_relative_paths_on_error) {

    return s->file_path;
  };

  return os__realpath(s->file_path);
}
bool Scanner_is_color_output_on(Scanner *s) {

  return s->should_print_errors_in_color && term__can_show_color_on_stderr();
}
void Parser_print_error_context(Parser *p) {

  if (p->pref->is_debug) {

    os__write_file(tos3("fns.txt"), Table_debug_fns(&/* ? */ *p->table));
  };

  if (p->pref->is_verbose || p->pref->is_debug) {

    printf("pass=%d fn=`%.*s`\n\n", p->pass, p->cur_fn.name.len,
           p->cur_fn.name.str);
  };

  CGen_save(p->cgen);

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
string main__normalized_error(string s) {

  return string_replace(
      string_replace(
          string_replace(string_replace(s, tos3("array_"), tos3("[]")),
                         tos3("__"), tos3(".")),
          tos3("Option_"), tos3("?")),
      tos3("main."), tos3(""));
}
string ScannerPos_str(ScannerPos s) {

  return _STR("ScannerPos{ %5d , %5d , %5d }", s.pos, s.line_nr, s.last_nl_pos);
}
ScannerPos Scanner_get_scanner_pos(Scanner *s) {

  return (ScannerPos){
      .pos = s->pos, .line_nr = s->line_nr, .last_nl_pos = s->last_nl_pos};
}
void Scanner_goto_scanner_position(Scanner *s, ScannerPos scp) {

  s->pos = scp.pos;

  s->line_nr = scp.line_nr;

  s->last_nl_pos = scp.last_nl_pos;
}
ScannerPos Scanner_get_scanner_pos_of_token(Scanner *s, Token *t) {

  int tline = t->line_nr;

  int tcol = (t->line_nr == 0) ? (t->col + 1) : (t->col - 1);

  ScannerPos cpos = Scanner_get_scanner_pos(&/* ? */ *s);

  ScannerPos sptoken = (ScannerPos){.pos = 0, .line_nr = 0, .last_nl_pos = 0};

  Scanner_goto_scanner_position(
      s, (ScannerPos){.pos = 0, .line_nr = 0, .last_nl_pos = 0});

  s->file_lines = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  int prevlinepos = 0;

  int ate = 0;

  ate++;

  while (1) {

    prevlinepos = s->pos;

    if (s->pos >= s->text.len) {

      break;
    };

    if (s->line_nr > tline + 10) {

      break;
    };

    if (tline == s->line_nr) {

      sptoken = Scanner_get_scanner_pos(&/* ? */ *s);

      sptoken.pos += tcol;
    };

    Scanner_ignore_line(s);

    Scanner_eat_single_newline(s);

    string sline = string_substr(s->text, prevlinepos, s->pos);

    _PUSH(&s->file_lines, (/*typ = array_string   tmp_typ=string*/ sline),
          tmp34, string);
  };

  Scanner_goto_scanner_position(s, cpos);

  return sptoken;
}
void Scanner_eat_single_newline(Scanner *s) {

  if (s->pos >= s->text.len) {

    return;
  };

  if (Scanner_expect(&/* ? */ *s, tos3("\r\n"), s->pos)) {

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
void Parser_comp_time(Parser *p) {

  Parser_check(p, main__TokenKind_dollar);

  if (p->tok == main__TokenKind_key_if) {

    Parser_check(p, main__TokenKind_key_if);

    Parser_fspace(p);

    bool not = p->tok == main__TokenKind_not;

    if (not) {

      Parser_check(p, main__TokenKind_not);
    };

    string name = Parser_check_name(p);

    Parser_fspace(p);

    if (_IN(string, (name), main__supported_platforms)) {

      string ifdef_name = main__os_name_to_ifdef(name);

      if (not) {

        Parser_genln(p, _STR("#ifndef %.*s", ifdef_name.len, ifdef_name.str));

      } else {

        Parser_genln(p, _STR("#ifdef %.*s", ifdef_name.len, ifdef_name.str));
      };

      Parser_check(p, main__TokenKind_lcbr);

      Parser_statements_no_rcbr(p);

      if (!(p->tok == main__TokenKind_dollar &&
            Parser_peek(&/* ? */ *p) == main__TokenKind_key_else)) {

        Parser_genln(p, tos3("#endif"));
      };

    } else if (string_eq(name, tos3("debug"))) {

      Parser_genln(p, tos3("#ifdef VDEBUG"));

      Parser_check(p, main__TokenKind_lcbr);

      Parser_statements_no_rcbr(p);

      Parser_genln(p, tos3("#endif"));

    } else if (string_eq(name, tos3("tinyc"))) {

      Parser_genln(p, tos3("#ifdef __TINYC__"));

      Parser_check(p, main__TokenKind_lcbr);

      Parser_statements_no_rcbr(p);

      Parser_genln(p, tos3("#endif"));

    } else {

      println(tos3("Supported platforms:"));

      println(array_string_str(main__supported_platforms));

      Parser_error(p, _STR("unknown platform `%.*s`", name.len, name.str));
    };

    bool if_returns = p->returns;

    p->returns = 0;

    if (p->tok == main__TokenKind_dollar &&
        Parser_peek(&/* ? */ *p) == main__TokenKind_key_else) {

      Parser_next(p);

      Parser_next(p);

      Parser_check(p, main__TokenKind_lcbr);

      Parser_genln(p, tos3("#else"));

      Parser_statements_no_rcbr(p);

      Parser_genln(p, tos3("#endif"));

      bool else_returns = p->returns;

      p->returns = if_returns && else_returns;
    };

  } else if (p->tok == main__TokenKind_key_for) {

    Parser_next(p);

    string name = Parser_check_name(p);

    if (string_ne(name, tos3("field"))) {

      Parser_error(p, tos3("for field only"));
    };

    Parser_check(p, main__TokenKind_key_in);

    Parser_check_name(p);

    Parser_check(p, main__TokenKind_dot);

    Parser_check_name(p);

    Parser_check(p, main__TokenKind_lcbr);

    string res_name = Parser_check_name(p);

    println(res_name);

    Parser_check(p, main__TokenKind_dot);

    Parser_check(p, main__TokenKind_dollar);

    Parser_check(p, main__TokenKind_name);

    Parser_check(p, main__TokenKind_assign);

    CGen_start_tmp(p->cgen);

    Parser_bool_expression(p);

    string val = CGen_end_tmp(p->cgen);

    println(val);

    Parser_check(p, main__TokenKind_rcbr);

  } else if (p->tok == main__TokenKind_name &&
             string_eq(p->lit, tos3("vweb"))) {

    string path = string_add(p->cur_fn.name, tos3(".html"));

    if (p->pref->is_debug) {

      printf("compiling tmpl %.*s\n", path.len, path.str);
    };

    if (!os__file_exists(path)) {

      path = string_add(string_add(os__dir(p->scanner->file_path), tos3("/")),
                        path);

      if (!os__file_exists(path)) {

        Parser_error(p, _STR("vweb HTML template \"%.*s\" not found", path.len,
                             path.str));
      };
    };

    Parser_check(p, main__TokenKind_name);

    Parser_check(p, main__TokenKind_dot);

    Parser_check(p, main__TokenKind_name);

    Parser_check(p, main__TokenKind_lpar);

    Parser_check(p, main__TokenKind_rpar);

    string v_code = vweb_dot_tmpl__compile_template(path);

    if (os__file_exists(tos3(".vwebtmpl.v"))) {

      os__rm(tos3(".vwebtmpl.v"));
    };

    os__write_file(tos3(".vwebtmpl.v"), string_clone(v_code));

    Parser_genln(p, tos3(""));

    int pos = p->cgen->lines.len - 1;

    Parser pp = V_new_parser_from_file(p->v, tos3(".vwebtmpl.v"));

    if (!p->pref->is_debug) {

      os__rm(tos3(".vwebtmpl.v"));
    };

    pp.is_vweb = 1;

    Parser_set_current_fn(&/* ? */ pp, p->cur_fn);

    Parser_parse(&/* ? */ pp, main__Pass_main);

    V_add_parser(pp.v, pp);

    string tmpl_fn_body = string_clone(array_string_join(
        array_slice(p->cgen->lines, pos + 2, p->cgen->lines.len), tos3("\n")));

    int end_pos =
        string_last_index(tmpl_fn_body, tos3("Builder_str( sb )")) + 19;

    p->cgen->lines = array_left(p->cgen->lines, pos);

    Parser_genln(p, tos3("/////////////////// tmpl start"));

    Parser_genln(p, string_left(tmpl_fn_body, end_pos));

    Parser_genln(p, tos3("/////////////////// tmpl end"));

    Var receiver = (*(Var *)array_get(p->cur_fn.args, 0));

    string dot = (receiver.is_mut) ? (tos3("->")) : (tos3("."));

    Parser_genln(p,
                 _STR("vweb__Context_html(%.*s %.*s vweb, tmpl_res)",
                      receiver.name.len, receiver.name.str, dot.len, dot.str));

  } else {

    Parser_error(p, tos3("bad comptime expr"));
  };
}
void Parser_chash(Parser *p) {

  string hash = string_trim_space(p->lit);

  Parser_next(p);

  if (string_starts_with(hash, tos3("flag "))) {

    string flag = string_right(hash, 5);

    flag = string_replace(flag, tos3("@VROOT"), p->vroot);

    flag = string_replace(flag, tos3("@VMOD"), main__v_modules_path);

    Table_parse_cflag(p->table, flag, p->mod);

    return;
  };

  if (string_starts_with(hash, tos3("include"))) {

    if (Parser_first_pass(&/* ? */ *p) && !p->is_vh) {

      if (p->file_pcguard.len != 0) {

        _PUSH(&p->cgen->includes,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "%.*s\n#%.*s\n#endif", p->file_pcguard.len,
                  p->file_pcguard.str, hash.len, hash.str)),
              tmp21, string);

        return;
      };

      _PUSH(&p->cgen->includes,
            (/*typ = array_string   tmp_typ=string*/ _STR("#%.*s", hash.len,
                                                          hash.str)),
            tmp22, string);

      return;
    };

  } else if (string_contains(hash, tos3("embed"))) {

    int pos = string_index(hash, tos3("embed")) + 5;

    string file = string_right(hash, pos);

    if (p->pref->build_mode != main__BuildMode_default_mode) {

      Parser_genln(p, _STR("#include %.*s", file.len, file.str));
    };

  } else if (string_contains(hash, tos3("define"))) {

    _PUSH(&p->cgen->includes,
          (/*typ = array_string   tmp_typ=string*/ _STR("#%.*s", hash.len,
                                                        hash.str)),
          tmp25, string);

  } else if (string_eq(hash, tos3("v"))) {

    println(tos3("v script"));

  } else if (string_eq(hash, tos3("-js"))) {

#ifdef _VJS

    while (p->tok != main__TokenKind_eof) {

      Parser_next(p);
    };

#else

    Parser_next(p);

#endif
    ;

  } else {

#ifndef _VJS

    if (!p->can_chash) {

      printf("hash=\"%.*s\"\n", hash.len, hash.str);

      /*opt*/ printf("%d\n", string_starts_with(hash, tos3("include")));

      Parser_error(
          p, tos3("bad token `#` (embedding C code is no longer supported)"));
    };

#endif
    ;

    Parser_genln(p, hash);
  };
}
void Parser_comptime_method_call(Parser *p, Type typ) {

  p->cgen->cur_line = tos3("");

  Parser_check(p, main__TokenKind_dollar);

  string var = Parser_check_name(p);

  array_Fn tmp27 = typ.methods;
  for (int i = 0; i < tmp27.len; i++) {
    Fn method = ((Fn *)tmp27.data)[i];

    if (string_ne(method.typ, tos3("void"))) {

      continue;
    };

    Var receiver = (*(Var *)array_get(method.args, 0));

    string amp = (receiver.is_mut) ? (tos3("&")) : (tos3(""));

    if (i > 0) {

      Parser_gen(p, tos3(" else "));
    };

    Parser_gen(
        p, _STR("if ( string_eq(%.*s, _STR(\"%.*s\")) ) %.*s_%.*s(%.*s %.*s);",
                var.len, var.str, method.name.len, method.name.str,
                typ.name.len, typ.name.str, method.name.len, method.name.str,
                amp.len, amp.str, p->expr_var.name.len, p->expr_var.name.str));
  };

  Parser_check(p, main__TokenKind_lpar);

  Parser_check(p, main__TokenKind_rpar);

  if (p->tok == main__TokenKind_key_orelse) {

    Parser_check(p, main__TokenKind_key_orelse);

    Parser_genln(p, tos3("else {"));

    Parser_check(p, main__TokenKind_lcbr);

    Parser_statements(p);
  };
}
void Parser_gen_array_str(Parser *p, Type typ) {

  Parser_add_method(p, typ.name,
                    (Fn){.name = tos3("str"),
                         .typ = tos3("string"),
                         .args = new_array_from_c_array(
                             1, 1, sizeof(Var),
                             EMPTY_ARRAY_OF_ELEMS(Var, 1){
                                 (Var){.typ = typ.name,
                                       .is_arg = 1,
                                       .name = tos((byte *)"", 0),
                                       .idx = 0,
                                       .is_const = 0,
                                       .args = new_array(0, 1, sizeof(Var)),
                                       .attr = tos((byte *)"", 0),
                                       .is_mut = 0,
                                       .is_alloc = 0,
                                       .is_returned = 0,
                                       .ptr = 0,
                                       .ref = 0,
                                       .parent_fn = tos((byte *)"", 0),
                                       .mod = tos((byte *)"", 0),
                                       .is_global = 0,
                                       .is_used = 0,
                                       .is_changed = 0,
                                       .scope_level = 0,
                                       .is_c = 0,
                                       .is_moved = 0,
                                       .line_nr = 0,
                                       .token_idx = 0}}),
                         .is_method = 1,
                         .is_public = 1,
                         .receiver_typ = typ.name,
                         .mod = tos((byte *)"", 0),
                         .is_interface = 0,
                         .scope_level = 0,
                         .is_c = 0,
                         .returns_error = 0,
                         .is_decl = 0,
                         .defer_text = new_array(0, 1, sizeof(string)),
                         .fn_name_token_idx = 0});

  string elm_type = string_right(typ.name, 6);

  Type elm_type2 = Table_find_type(&/* ? */ *p->table, elm_type);

  if (string_eq(Parser_typ_to_fmt(p, elm_type, 0), tos3("")) &&
      !Table_type_has_method(&/* ? */ *p->table,
                             &/*112 EXP:"Type*" GOT:"Type" */ elm_type2,
                             tos3("str"))) {

    Parser_error(p,
                 _STR("cant print %.*s[], unhandled print of %.*s",
                      elm_type.len, elm_type.str, elm_type.len, elm_type.str));
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
        tmp34, string);
}
void Parser_gen_struct_str(Parser *p, Type typ) {

  Parser_add_method(p, typ.name,
                    (Fn){.name = tos3("str"),
                         .typ = tos3("string"),
                         .args = new_array_from_c_array(
                             1, 1, sizeof(Var),
                             EMPTY_ARRAY_OF_ELEMS(Var, 1){
                                 (Var){.typ = typ.name,
                                       .is_arg = 1,
                                       .name = tos((byte *)"", 0),
                                       .idx = 0,
                                       .is_const = 0,
                                       .args = new_array(0, 1, sizeof(Var)),
                                       .attr = tos((byte *)"", 0),
                                       .is_mut = 0,
                                       .is_alloc = 0,
                                       .is_returned = 0,
                                       .ptr = 0,
                                       .ref = 0,
                                       .parent_fn = tos((byte *)"", 0),
                                       .mod = tos((byte *)"", 0),
                                       .is_global = 0,
                                       .is_used = 0,
                                       .is_changed = 0,
                                       .scope_level = 0,
                                       .is_c = 0,
                                       .is_moved = 0,
                                       .line_nr = 0,
                                       .token_idx = 0}}),
                         .is_method = 1,
                         .is_public = 1,
                         .receiver_typ = typ.name,
                         .mod = tos((byte *)"", 0),
                         .is_interface = 0,
                         .scope_level = 0,
                         .is_c = 0,
                         .returns_error = 0,
                         .is_decl = 0,
                         .defer_text = new_array(0, 1, sizeof(string)),
                         .fn_name_token_idx = 0});

  strings__Builder sb = strings__new_builder(typ.fields.len * 20);

  strings__Builder_writeln(
      &/* ? */ sb,
      _STR("fn (a %.*s) str() string {\nreturn", typ.name.len, typ.name.str));

  strings__Builder_writeln(&/* ? */ sb, tos3("'{"));

  array_Var tmp36 = typ.fields;
  for (int tmp37 = 0; tmp37 < tmp36.len; tmp37++) {
    Var field = ((Var *)tmp36.data)[tmp37];

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
        tmp38, string);
}
void DepSet_add(DepSet *dset, string item) {

  _PUSH(&dset->items, (/*typ = array_string   tmp_typ=string*/ item), tmp1,
        string);
}
DepSet DepSet_diff(DepSet *dset, DepSet otherset) {

  DepSet diff = (DepSet){.items = new_array(0, 1, sizeof(string))};

  array_string tmp3 = dset->items;
  for (int tmp4 = 0; tmp4 < tmp3.len; tmp4++) {
    string item = ((string *)tmp3.data)[tmp4];

    if (!_IN(string, (item), otherset.items)) {

      _PUSH(&diff.items, (/*typ = array_string   tmp_typ=string*/ item), tmp5,
            string);
    };
  };

  return diff;
}
int DepSet_size(DepSet *dset) { return dset->items.len; }
DepGraph *main__new_dep_graph() {

  return (DepGraph *)memdup(
      &(DepGraph){.acyclic = 1, .nodes = new_array(0, 1, sizeof(DepGraphNode))},
      sizeof(DepGraph));
}
void DepGraph_add(DepGraph *graph, string mod, array_string deps) {

  _PUSH(&graph->nodes,
        (/*typ = array_DepGraphNode   tmp_typ=DepGraphNode*/ (DepGraphNode){
            .name = mod,
            .deps = array_clone(deps),
            .last_cycle = tos((byte *)"", 0)}),
        tmp6, DepGraphNode);
}
DepGraph *DepGraph_resolve(DepGraph *graph) {

  map_DepGraphNode node_names = new_map(1, sizeof(DepGraphNode));

  map_DepSet node_deps = new_map(1, sizeof(DepSet));

  array_DepGraphNode tmp9 = graph->nodes;
  for (int _ = 0; _ < tmp9.len; _++) {
    DepGraphNode node = ((DepGraphNode *)tmp9.data)[_];

    map_set(&node_names, node.name, &(DepGraphNode[]){node});

    DepSet dep_set = (DepSet){.items = new_array(0, 1, sizeof(string))};

    array_string tmp11 = node.deps;
    for (int _ = 0; _ < tmp11.len; _++) {
      string dep = ((string *)tmp11.data)[_];

      DepSet_add(&/* ? */ dep_set, dep);
    };

    map_set(&node_deps, node.name, &(DepSet[]){dep_set});
  };

  DepGraph *resolved = main__new_dep_graph();

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

      DepGraph *g = main__new_dep_graph();

      g->acyclic = 0;

      array_string ndk = map_keys(&/* ? */ node_deps);

      map_DepSet tmp17 = node_deps;
      array_string keys_tmp17 = map_keys(&tmp17);
      for (int l = 0; l < keys_tmp17.len; l++) {
        string name = ((string *)keys_tmp17.data)[l];

        DepGraphNode tmp18 = {0};
        bool tmp19 = map_get(/*depgraph.v : 89*/ node_names, name, &tmp18);

        DepGraphNode node = tmp18;

        if (string_eq(name, (*(string *)array_get(ndk, node_deps.size - 1)))) {

          DepSet tmp23 = {0};
          bool tmp24 = map_get(/*depgraph.v : 90*/ node_deps, name, &tmp23);

          DepSet tmp25 = {0};
          bool tmp26 = map_get(/*depgraph.v : 90*/ node_deps, name, &tmp25);

          node.last_cycle =
              (*(string *)array_get(tmp23.items, tmp25.items.len - 1));
        };

        _PUSH(&g->nodes,
              (/*typ = array_DepGraphNode   tmp_typ=DepGraphNode*/ node), tmp29,
              DepGraphNode);
      };

      return g;
    };

    array_string tmp30 = ready_set.items;
    for (int tmp31 = 0; tmp31 < tmp30.len; tmp31++) {
      string name = ((string *)tmp30.data)[tmp31];

      v_map_delete(&/* ? */ node_deps, name);

      DepGraphNode tmp33 = {0};
      bool tmp34 = map_get(/*depgraph.v : 100*/ node_names, name, &tmp33);

      _PUSH(&resolved->nodes,
            (/*typ = array_DepGraphNode   tmp_typ=DepGraphNode*/ tmp33), tmp32,
            DepGraphNode);
    };

    map_DepSet tmp35 = node_deps;
    array_string keys_tmp35 = map_keys(&tmp35);
    for (int l = 0; l < keys_tmp35.len; l++) {
      string name = ((string *)keys_tmp35.data)[l];
      DepSet deps = {0};
      map_get(tmp35, name, &deps);

      map_set(&node_deps, name,
              &(DepSet[]){DepSet_diff(&/* ? */ deps, ready_set)});
    };
  };

  return resolved;
}
DepGraphNode DepGraph_last_node(DepGraph *graph) {

  return (*(DepGraphNode *)array_get(graph->nodes, graph->nodes.len - 1));
}
string DepGraph_last_cycle(DepGraph *graph) {

  return DepGraph_last_node(&/* ? */ *graph).last_cycle;
}
void DepGraph_display(DepGraph *graph) {

  for (int i = 0; i < graph->nodes.len; i++) {

    DepGraphNode node = (*(DepGraphNode *)array_get(graph->nodes, i));

    array_string tmp42 = node.deps;
    for (int tmp43 = 0; tmp43 < tmp42.len; tmp43++) {
      string dep = ((string *)tmp42.data)[tmp43];

      string out = _STR(" * %.*s -> %.*s", node.name.len, node.name.str,
                        dep.len, dep.str);

      if (!graph->acyclic && i == graph->nodes.len - 1 &&
          string_eq(dep, node.last_cycle)) {

        out = string_add(out, tos3(" <-- last cycle"));
      };

      println(out);
    };
  };
}
Option_Var Parser_find_var(Parser *p, string name) {

  int tmp1 = 0;
  ;
  for (int tmp2 = tmp1; tmp2 < p->var_idx; tmp2++) {
    int i = tmp2;

    if (string_eq((*(Var *)array_get(p->local_vars, i)).name, name)) {

      Var tmp7 = OPTION_CAST(Var)((*(Var *)array_get(p->local_vars, i)));
      return opt_ok(&tmp7, sizeof(Var));
    };
  };

  return opt_none();
}
Option_Var Parser_find_var_check_new_var(Parser *p, string name) {

  int tmp8 = 0;
  ;
  for (int tmp9 = tmp8; tmp9 < p->var_idx; tmp9++) {
    int i = tmp9;

    if (string_eq((*(Var *)array_get(p->local_vars, i)).name, name)) {

      Var tmp14 = OPTION_CAST(Var)((*(Var *)array_get(p->local_vars, i)));
      return opt_ok(&tmp14, sizeof(Var));
    };
  };

  if (string_eq(name, string_add(tos3("main__"), p->var_decl_name))) {

    Var tmp15 = OPTION_CAST(Var)((Var){.name = p->var_decl_name,
                                       .typ = tos3("voidptr"),
                                       .is_mut = 1,
                                       .idx = 0,
                                       .is_arg = 0,
                                       .is_const = 0,
                                       .args = new_array(0, 1, sizeof(Var)),
                                       .attr = tos((byte *)"", 0),
                                       .is_alloc = 0,
                                       .is_returned = 0,
                                       .ptr = 0,
                                       .ref = 0,
                                       .parent_fn = tos((byte *)"", 0),
                                       .mod = tos((byte *)"", 0),
                                       .is_global = 0,
                                       .is_used = 0,
                                       .is_changed = 0,
                                       .scope_level = 0,
                                       .is_c = 0,
                                       .is_moved = 0,
                                       .line_nr = 0,
                                       .token_idx = 0});
    return opt_ok(&tmp15, sizeof(Var));
  };

  return opt_none();
}
void Parser_open_scope(Parser *p) {

  _PUSH(&p->cur_fn.defer_text,
        (/*typ = array_string   tmp_typ=string*/ tos3("")), tmp16, string);

  p->cur_fn.scope_level++;
}
void Parser_mark_var_used(Parser *p, Var v) {

  if (v.idx == -1 || v.idx >= p->local_vars.len) {

    return;
  };

  (*(Var *)array_get(p->local_vars, v.idx)).is_used = 1;
}
void Parser_mark_var_returned(Parser *p, Var v) {

  if (v.idx == -1 || v.idx >= p->local_vars.len) {

    return;
  };

  (*(Var *)array_get(p->local_vars, v.idx)).is_returned = 1;
}
void Parser_mark_var_changed(Parser *p, Var v) {

  if (v.idx == -1 || v.idx >= p->local_vars.len) {

    return;
  };

  (*(Var *)array_get(p->local_vars, v.idx)).is_changed = 1;
}
void Parser_mark_arg_moved(Parser *p, Var v) {

  array_Var tmp23 = p->cur_fn.args;
  for (int i = 0; i < tmp23.len; i++) {
    Var arg = ((Var *)tmp23.data)[i];

    if (string_eq(arg.name, v.name)) {

      (*(Var *)array_get(p->cur_fn.args, i)).is_moved = 1;

      break;
    };
  };

  map_set(&p->table->fns, p->cur_fn.name, &(Fn[]){p->cur_fn});
}
bool Parser_known_var(Parser *p, string name) {

  Option_Var tmp26 = Parser_find_var(&/* ? */ *p, name);
  if (!tmp26.ok) {
    string err = tmp26.error;

    return 0;
  };

  return 1;
}
void Parser_register_var(Parser *p, Var v) {

  Var new_var = (Var){
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
  };

  if (v.line_nr == 0) {

    new_var.token_idx = Parser_cur_tok_index(&/* ? */ *p);

    new_var.line_nr = Parser_cur_tok(&/* ? */ *p).line_nr;
  };

  if (p->var_idx >= p->local_vars.len) {

    _PUSH(&p->local_vars, (/*typ = array_Var   tmp_typ=Var*/ new_var), tmp28,
          Var);

  } else {

    array_set(&/*q*/ p->local_vars, p->var_idx, &(Var[]){new_var});
  };

  p->var_idx++;
}
void Parser_clear_vars(Parser *p) {

  p->var_idx = 0;

  if (p->local_vars.len > 0) {

    if (p->pref->autofree) {

      v_array_free(p->local_vars);
    };

    p->local_vars = new_array_from_c_array(
        0, 0, sizeof(Var), EMPTY_ARRAY_OF_ELEMS(Var, 0){TCCSKIP(0)});
  };
}
void Parser_fn_decl(Parser *p) {

  Parser_clear_vars(p);

  Parser_fgen(p, tos3("fn "));

  Fn f = (Fn){.mod = p->mod,
              .is_public = p->tok == main__TokenKind_key_pub,
              .name = tos((byte *)"", 0),
              .args = new_array(0, 1, sizeof(Var)),
              .is_interface = 0,
              .scope_level = 0,
              .typ = tos((byte *)"", 0),
              .is_c = 0,
              .receiver_typ = tos((byte *)"", 0),
              .is_method = 0,
              .returns_error = 0,
              .is_decl = 0,
              .defer_text = new_array(0, 1, sizeof(string)),
              .fn_name_token_idx = 0};

  bool is_live =
      string_eq(p->attr, tos3("live")) && !p->pref->is_so && p->pref->is_live;

  if (string_eq(p->attr, tos3("live")) && Parser_first_pass(&/* ? */ *p) &&
      !p->pref->is_live && !p->pref->is_so) {

    println(tos3(
        "INFO: run `v -live program.v` if you want to use [live] functions"));
  };

  if (f.is_public) {

    Parser_next(p);
  };

  p->returns = 0;

  Parser_next(p);

  string receiver_typ = tos3("");

  if (p->tok == main__TokenKind_lpar) {

    f.is_method = 1;

    Parser_check(p, main__TokenKind_lpar);

    string receiver_name = Parser_check_name(p);

    bool is_mut = p->tok == main__TokenKind_key_mut;

    bool is_amp = p->tok == main__TokenKind_amp;

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
        string_ne(T.mod, p->mod) && string_ne(p->id, tos3("vgen"))) {

      printf("T.mod=%.*s\n", T.mod.len, T.mod.str);

      printf("p.mod=%.*s\n", p->mod.len, p->mod.str);

      Parser_error(p, _STR("cannot define new methods on non-local type `%.*s`",
                           receiver_typ.len, receiver_typ.str));
    };

    if (string_ends_with(receiver_typ, tos3("*"))) {

      string t = string_replace(receiver_typ, tos3("*"), tos3(""));

      Parser_error(p, _STR("use `(%.*s mut %.*s)` instead of `(%.*s *%.*s)`",
                           receiver_name.len, receiver_name.str, t.len, t.str,
                           receiver_name.len, receiver_name.str, t.len, t.str));
    };

    f.receiver_typ = receiver_typ;

    if (is_mut || is_amp) {

      receiver_typ = string_add(receiver_typ, tos3("*"));
    };

    Parser_check(p, main__TokenKind_rpar);

    Parser_fspace(p);

    Var receiver = (Var){
        .name = receiver_name,
        .is_arg = 1,
        .typ = receiver_typ,
        .is_mut = is_mut,
        .ref = is_amp,
        .ptr = is_mut,
        .line_nr = p->scanner->line_nr,
        .token_idx = Parser_cur_tok_index(&/* ? */ *p),
        .idx = 0,
        .is_const = 0,
        .args = new_array(0, 1, sizeof(Var)),
        .attr = tos((byte *)"", 0),
        .is_alloc = 0,
        .is_returned = 0,
        .parent_fn = tos((byte *)"", 0),
        .mod = tos((byte *)"", 0),
        .is_global = 0,
        .is_used = 0,
        .is_changed = 0,
        .scope_level = 0,
        .is_c = 0,
        .is_moved = 0,
    };

    _PUSH(&f.args, (/*typ = array_Var   tmp_typ=Var*/ receiver), tmp38, Var);

    Parser_register_var(p, receiver);
  };

  if (p->tok == main__TokenKind_plus || p->tok == main__TokenKind_minus ||
      p->tok == main__TokenKind_mul) {

    f.name = TokenKind_str(p->tok);

    Parser_next(p);

  } else {

    f.name = Parser_check_name(p);
  };

  f.fn_name_token_idx = Parser_cur_tok_index(&/* ? */ *p);

  bool is_c = string_eq(f.name, tos3("C")) && p->tok == main__TokenKind_dot;

  if (p->pref->build_mode == main__BuildMode_build_module) {
  };

  if (is_c) {

    Parser_check(p, main__TokenKind_dot);

    f.name = Parser_check_name(p);

    f.is_c = 1;

  } else if (!p->pref->translated) {

    if (main__contains_capital(f.name) &&
        !Parser_fileis(&/* ? */ *p, tos3("view.v"))) {

      Parser_error(p, tos3("function names cannot contain uppercase letters, "
                           "use snake_case instead"));
    };

    if (string_at(f.name, 0) == '_') {

      Parser_warn(p, tos3("function names cannot start with `_`"));
    };

    if (string_contains(f.name, tos3("__"))) {

      Parser_error(p, tos3("function names cannot contain double underscores, "
                           "use single underscores instead"));
    };
  };

  bool has_receiver = receiver_typ.len > 0;

  if (string_ne(receiver_typ, tos3(""))) {
  };

  if (!is_c && !p->builtin_mod && receiver_typ.len == 0) {

    f.name = Parser_prepend_mod(&/* ? */ *p, f.name);
  };

  if (Parser_first_pass(&/* ? */ *p) && receiver_typ.len == 0) {

    while (1) {

      Option_Fn tmp43 = Table_find_fn(&/* ? */ *p->table, f.name);
      if (!tmp43.ok) {
        string err = tmp43.error;

        break;
      }
      Fn existing_fn = *(Fn *)tmp43.data;
      ;

      if (!existing_fn.is_decl) {

        Parser_error(p, _STR("redefinition of `%.*s`", f.name.len, f.name.str));
      };

      break;
    };
  };

  bool is_generic = 0;

  if (p->tok == main__TokenKind_lt) {

    is_generic = 1;

    Parser_next(p);

    string gen_type = Parser_check_name(p);

    if (string_ne(gen_type, tos3("T"))) {

      Parser_error(p, tos3("only `T` is allowed as a generic type for now"));
    };

    Parser_check(p, main__TokenKind_gt);

    if (Parser_first_pass(&/* ? */ *p)) {

      Table_register_generic_fn(p->table, f.name);

    } else {
    };
  };

  Parser_fn_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  if (p->tok == main__TokenKind_not) {

    Parser_next(p);

    f.returns_error = 1;
  };

  string typ = tos3("void");

  if (p->tok == main__TokenKind_name || p->tok == main__TokenKind_mul ||
      p->tok == main__TokenKind_amp || p->tok == main__TokenKind_lsbr ||
      p->tok == main__TokenKind_question || p->tok == main__TokenKind_lpar) {

    Parser_fgen(p, tos3(" "));

    typ = Parser_get_type(p);
  };

  bool is_fn_header = !is_c && !p->is_vh &&
                      (p->pref->translated || p->pref->is_test || p->is_vh) &&
                      p->tok != main__TokenKind_lcbr;

  if (is_fn_header) {

    f.is_decl = 1;
  };

  if (!is_c && !p->is_vh && !is_fn_header) {

    Parser_fgen(p, tos3(" "));

    Parser_check(p, main__TokenKind_lcbr);
  };

  if (string_starts_with(typ, tos3("Option_"))) {

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR("typedef Option %.*s;",
                                                        typ.len, typ.str)),
          tmp48, string);
  };

  f.typ = typ;

  string str_args = Fn_str_args(&/* ? */ f, p->table);

  if (string_eq(f.name, tos3("main__main")) && !has_receiver) {

    if (string_ne(str_args, tos3("")) || string_ne(typ, tos3("void"))) {

      Parser_error_with_token_index(
          p, tos3("fn main must have no arguments and no return values"),
          f.fn_name_token_idx);
    };
  };

  string dll_export_linkage =
      (p->os == main__OS_msvc && string_eq(p->attr, tos3("live")) &&
       p->pref->is_so)
          ? (tos3("__declspec(dllexport) "))
          : ((string_eq(p->attr, tos3("inline"))) ? (tos3("static inline "))
                                                  : (tos3("")));

  if (!p->is_vweb) {

    Parser_set_current_fn(p, f);
  };

  string fn_name_cgen =
      Table_fn_gen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  bool skip_main_in_test = 0;

  if (!is_c && !is_live && !p->is_vh && !is_fn_header && !skip_main_in_test) {

    if (p->pref->obfuscate) {

      Parser_genln(p, _STR("; // %.*s", f.name.len, f.name.str));
    };

    if (is_generic) {

      array_string gen_types = Table_fn_gen_types(&/* ? */ *p->table, f.name);

      int cur_pos = p->scanner->pos;

      TokenKind cur_tok = p->tok;

      string cur_lit = p->lit;

      array_string tmp57 = gen_types;
      for (int tmp58 = 0; tmp58 < tmp57.len; tmp58++) {
        string gen_type = ((string *)tmp57.data)[tmp58];

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

      Parser_gen_fn_decl(p, f, typ, str_args);
    };
  };

  if (is_fn_header) {

    Parser_genln(p, _STR("%.*s %.*s(%.*s);", typ.len, typ.str, fn_name_cgen.len,
                         fn_name_cgen.str, str_args.len, str_args.str));

    Parser_fgenln(p, tos3(""));
  };

  if (is_c) {

    Parser_fgenln(p, tos3("\n"));
  };

  if (string_ne(receiver_typ, tos3(""))) {

    Type receiver_t = Table_find_type(&/* ? */ *p->table, receiver_typ);

    if (Parser_first_pass(&/* ? */ *p) &&
        string_eq(receiver_t.name, tos3(""))) {

      receiver_t =
          (Type){.name = string_replace(receiver_typ, tos3("*"), tos3("")),
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

    Parser_add_method(p, receiver_t.name, f);

  } else if (Parser_first_pass(&/* ? */ *p)) {

    Table_register_fn(p->table, f);
  };

  if (p->is_vh || Parser_first_pass(&/* ? */ *p) || is_live || is_fn_header ||
      skip_main_in_test) {

    if (!p->is_vh && !is_fn_header) {

      Parser_skip_fn_body(p);
    };

    if (is_live && Parser_first_pass(&/* ? */ *p) &&
        string_eq(p->mod, tos3("main"))) {

      _PUSH(&p->cgen->so_fns,
            (/*typ = array_string   tmp_typ=string*/ fn_name_cgen), tmp60,
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

    if (!is_c && Parser_first_pass(&/* ? */ *p)) {

      _PUSH(&p->cgen->fns,
            (/*typ = array_string   tmp_typ=string*/ string_add(fn_decl,
                                                                tos3(";"))),
            tmp62, string);
    };

    return;
  };

  if (string_eq(p->attr, tos3("live")) && p->pref->is_so) {

    Parser_genln(p, tos3("pthread_mutex_lock(&live_fn_mutex);"));
  };

  if (string_eq(f.name, tos3("main__main")) ||
      string_eq(f.name, tos3("main")) || string_eq(f.name, tos3("WinMain"))) {

    if (p->pref->is_test) {

      Parser_error_with_token_index(
          p, tos3("tests cannot have function `main`"), f.fn_name_token_idx);
    };
  };

  if (is_c || p->is_vh || is_fn_header) {

    return;
  };

  if (p->pref->is_prof && string_ne(f.name, tos3("time__ticks"))) {

    Parser_genln(p, _STR("double _PROF_START = time__ticks();//%.*s",
                         f.name.len, f.name.str));

    string cgen_name =
        Table_fn_gen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

    if (f.defer_text.len > f.scope_level) {

      array_set(&/*q*/ f.defer_text, f.scope_level,
                &(string[]){_STR("  %.*s_time += time__ticks() - _PROF_START;",
                                 cgen_name.len, cgen_name.str)});
    };
  };

  if (is_generic) {

    p->cgen->nogen = 1;
  };

  Parser_statements_no_rcbr(p);

  if (p->pref->is_prof && string_eq(f.name, tos3("main"))) {

    Parser_genln(p, Parser_print_prof_counters(&/* ? */ *p));
  };

  if (!p->is_vweb) {

    if (f.defer_text.len > f.scope_level) {

      Parser_genln(p, (*(string *)array_get(f.defer_text, f.scope_level)));
    };
  };

  if (string_ne(typ, tos3("void")) && !p->returns) {

    Parser_error_with_token_index(p,
                                  _STR("%.*s must return \"%.*s\"", f.name.len,
                                       f.name.str, typ.len, typ.str),
                                  f.fn_name_token_idx);
  };

  if (string_eq(p->attr, tos3("live")) && p->pref->is_so) {

    Parser_genln(p, tos3("pthread_mutex_unlock(&live_fn_mutex);"));
  };

  if (string_eq(p->mod, tos3("main"))) {
  };

  if (p->cur_fn.scope_level > 2) {
  };

  if (string_ne(p->mod, tos3("main"))) {

    if (!is_generic) {

      Parser_genln(p, tos3("}"));
    };

    return;
  };

  Parser_check_unused_variables(p);

  Parser_set_current_fn(p, main__EmptyFn);

  p->returns = 0;

  if (!is_generic) {

    Parser_genln(p, tos3("}"));
  };
}
static inline void Parser_skip_fn_body(Parser *p) {

  int opened_scopes = 0;

  int closed_scopes = 0;

  while (1) {

    if (p->tok == main__TokenKind_lcbr) {

      opened_scopes++;
    };

    if (p->tok == main__TokenKind_rcbr) {

      closed_scopes++;
    };

    if (TokenKind_is_decl(p->tok)) {

      break;
    };

    if (closed_scopes > opened_scopes && p->prev_tok == main__TokenKind_rcbr) {

      if (p->tok == main__TokenKind_lsbr) {

        break;
      };
    };

    Parser_next(p);
  };
}
void Parser_check_unused_variables(Parser *p) {

  array_Var tmp68 = p->local_vars;
  for (int tmp69 = 0; tmp69 < tmp68.len; tmp69++) {
    Var var = ((Var *)tmp68.data)[tmp69];

    if (string_eq(var.name, tos3(""))) {

      break;
    };

    if (!var.is_used && !p->pref->is_repl && !var.is_arg &&
        !p->pref->translated) {

      Parser_production_error_with_token_index(
          p, _STR("`%.*s` declared and not used", var.name.len, var.name.str),
          var.token_idx);
    };

    if (!var.is_changed && var.is_mut && !p->pref->is_repl &&
        !p->pref->translated) {

      Parser_error_with_token_index(
          p,
          _STR("`%.*s` is declared as mutable, but it was never changed",
               var.name.len, var.name.str),
          var.token_idx);
    };
  };
}
void Parser_async_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
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

  string tmp_struct = Parser_get_tmp(p);

  Parser_genln(p,
               _STR("%.*s * %.*s = malloc(sizeof(%.*s));", arg_struct_name.len,
                    arg_struct_name.str, tmp_struct.len, tmp_struct.str,
                    arg_struct_name.len, arg_struct_name.str));

  string arg_struct = _STR("typedef struct  %.*s   { ", arg_struct_name.len,
                           arg_struct_name.str);

  Parser_next(p);

  Parser_check(p, main__TokenKind_lpar);

  string str_args = tos3("");

  bool did_gen_something = 0;

  array_Var tmp77 = f.args;
  for (int i = 0; i < tmp77.len; i++) {
    Var arg = ((Var *)tmp77.data)[i];

    arg_struct =
        string_add(arg_struct, _STR("%.*s %.*s ;", arg.typ.len, arg.typ.str,
                                    arg.name.len, arg.name.str));

    str_args = string_add(str_args,
                          _STR("arg %.*s %.*s", main__dot_ptr.len,
                               main__dot_ptr.str, arg.name.len, arg.name.str));

    if (i == 0 && f.is_method) {

      Parser_genln(p, _STR("%.*s %.*s %.*s =  %.*s ;", tmp_struct.len,
                           tmp_struct.str, main__dot_ptr.len, main__dot_ptr.str,
                           arg.name.len, arg.name.str, receiver_var.len,
                           receiver_var.str));

      if (i < f.args.len - 1) {

        str_args = string_add(str_args, tos3(","));
      };

      did_gen_something = 1;

      continue;
    };

    Parser_genln(p, _STR("%.*s %.*s %.*s =  ", tmp_struct.len, tmp_struct.str,
                         main__dot_ptr.len, main__dot_ptr.str, arg.name.len,
                         arg.name.str));

    Parser_expression(p);

    Parser_genln(p, tos3(";"));

    if (i < f.args.len - 1) {

      Parser_check(p, main__TokenKind_comma);

      str_args = string_add(str_args, tos3(","));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    arg_struct = string_add(arg_struct, tos3("EMPTY_STRUCT_DECLARATION;"));
  };

  arg_struct = string_add(
      arg_struct, _STR("} %.*s ;", arg_struct_name.len, arg_struct_name.str));

  fn_name = Table_fn_gen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

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

  string parg = tos3("NULL");

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

  Parser_check(p, main__TokenKind_rpar);
}
void Parser_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                    string receiver_type) {

  if (!f.is_public && !f.is_c && !p->pref->is_test && !f.is_interface &&
      string_ne(f.mod, p->mod)) {

    if (string_eq(f.name, tos3("contains"))) {

      println(
          tos3("use `value in numbers` instead of `numbers.contains(value)`"));
    };

    Parser_error(p, _STR("function `%.*s` is private", f.name.len, f.name.str));
  };

  p->calling_c = f.is_c;

  if (f.is_c && !p->builtin_mod) {

    if (string_eq(f.name, tos3("free"))) {

      Parser_error(p, tos3("use `free()` instead of `C.free()`"));

    } else if (string_eq(f.name, tos3("malloc"))) {

      Parser_error(p, tos3("use `malloc()` instead of `C.malloc()`"));
    };
  };

  string cgen_name =
      Table_fn_gen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  Parser_next(p);

  string gen_type = tos3("");

  if (p->tok == main__TokenKind_lt) {

    Parser_check(p, main__TokenKind_lt);

    gen_type = Parser_check_name(p);

    if (string_eq(gen_type, tos3("T")) &&
        string_ne(p->cur_gen_type, tos3(""))) {

      gen_type = p->cur_gen_type;
    };

    if (Parser_first_pass(&/* ? */ *p)) {

      printf("registering %.*s in %.*s fname=%.*s\n", gen_type.len,
             gen_type.str, f.name.len, f.name.str, f.name.len, f.name.str);

      Table_register_generic_fn_type(p->table, f.name, gen_type);

      return;
    };

    cgen_name = string_add(cgen_name, string_add(tos3("_"), gen_type));

    Parser_check(p, main__TokenKind_gt);
  };

  if (!f.is_method) {

    Parser_gen(p, cgen_name);

    Parser_gen(p, tos3("("));

  } else {

    Var receiver = *(Var *)array_first(f.args);

    if (receiver.is_mut && !p->expr_var.is_mut) {

      Parser_error(p, _STR("`%.*s` is immutable, declare it with `mut`",
                           p->expr_var.name.len, p->expr_var.name.str));
    };

    if (!p->expr_var.is_changed) {

      Parser_mark_var_changed(p, p->expr_var);
    };

    Parser_gen_method_call(p, receiver_type, f.typ, cgen_name, receiver,
                           method_ph);
  };

  Parser_fn_call_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  Parser_gen(p, tos3(")"));

  p->calling_c = 0;
}
void Parser_fn_args(Parser *p, Fn *f) {

  Parser_check(p, main__TokenKind_lpar);

  if (f->is_interface) {

    Var int_arg = (Var){
        .typ = f->receiver_typ,
        .token_idx = Parser_cur_tok_index(&/* ? */ *p),
        .name = tos((byte *)"", 0),
        .idx = 0,
        .is_arg = 0,
        .is_const = 0,
        .args = new_array(0, 1, sizeof(Var)),
        .attr = tos((byte *)"", 0),
        .is_mut = 0,
        .is_alloc = 0,
        .is_returned = 0,
        .ptr = 0,
        .ref = 0,
        .parent_fn = tos((byte *)"", 0),
        .mod = tos((byte *)"", 0),
        .is_global = 0,
        .is_used = 0,
        .is_changed = 0,
        .scope_level = 0,
        .is_c = 0,
        .is_moved = 0,
        .line_nr = 0,
    };

    _PUSH(&f->args, (/*typ = array_Var   tmp_typ=Var*/ int_arg), tmp87, Var);
  };

  bool types_only = p->tok == main__TokenKind_mul ||
                    p->tok == main__TokenKind_amp ||
                    (Parser_peek(&/* ? */ *p) == main__TokenKind_comma &&
                     Table_known_type(&/* ? */ *p->table, p->lit)) ||
                    Parser_peek(&/* ? */ *p) == main__TokenKind_rpar;

  if (types_only) {

    while (p->tok != main__TokenKind_rpar) {

      string typ = Parser_get_type(p);

      Parser_check_and_register_used_imported_type(p, typ);

      Var v = (Var){
          .typ = typ,
          .is_arg = 1,
          .line_nr = p->scanner->line_nr,
          .token_idx = Parser_cur_tok_index(&/* ? */ *p),
          .name = tos((byte *)"", 0),
          .idx = 0,
          .is_const = 0,
          .args = new_array(0, 1, sizeof(Var)),
          .attr = tos((byte *)"", 0),
          .is_mut = 0,
          .is_alloc = 0,
          .is_returned = 0,
          .ptr = 0,
          .ref = 0,
          .parent_fn = tos((byte *)"", 0),
          .mod = tos((byte *)"", 0),
          .is_global = 0,
          .is_used = 0,
          .is_changed = 0,
          .scope_level = 0,
          .is_c = 0,
          .is_moved = 0,
      };

      _PUSH(&f->args, (/*typ = array_Var   tmp_typ=Var*/ v), tmp91, Var);

      if (p->tok == main__TokenKind_comma) {

        Parser_next(p);
      };
    };
  };

  while (p->tok != main__TokenKind_rpar) {

    array_string names = new_array_from_c_array(
        1, 1, sizeof(string),
        EMPTY_ARRAY_OF_ELEMS(string, 1){Parser_check_name(p)});

    while (p->tok == main__TokenKind_comma) {

      Parser_check(p, main__TokenKind_comma);

      Parser_fspace(p);

      _PUSH(&names,
            (/*typ = array_string   tmp_typ=string*/ Parser_check_name(p)),
            tmp93, string);
    };

    Parser_fspace(p);

    bool is_mut = p->tok == main__TokenKind_key_mut;

    if (is_mut) {

      Parser_next(p);
    };

    string typ = tos3("");

    if (p->tok == main__TokenKind_ellipsis) {

      Parser_check(p, main__TokenKind_ellipsis);

      if (p->tok == main__TokenKind_rpar) {

        Parser_error(p,
                     tos3("you must provide a type for vargs: eg `...string`. "
                          "multiple types `...` are not supported yet."));
      };

      string t = Parser_get_type(p);

      string vargs_struct = Parser_fn_register_vargs_stuct(
          p, f, t,
          new_array_from_c_array(0, 0, sizeof(string),
                                 EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)}));

      _PUSH(&p->cgen->typedefs,
            (/*typ = array_string   tmp_typ=string*/ _STR(
                "typedef struct %.*s %.*s;\n", vargs_struct.len,
                vargs_struct.str, vargs_struct.len, vargs_struct.str)),
            tmp98, string);

      typ = _STR("...%.*s", t.len, t.str);

    } else {

      typ = Parser_get_type(p);
    };

    Parser_check_and_register_used_imported_type(p, typ);

    if (is_mut && main__is_primitive_type(typ)) {

      Parser_error(p, string_add(tos3("mutable arguments are only allowed for "
                                      "arrays, maps, and structs."),
                                 tos3("\nreturn values instead: `foo(n mut "
                                      "int)` => `foo(n int) int`")));
    };

    array_string tmp99 = names;
    for (int tmp100 = 0; tmp100 < tmp99.len; tmp100++) {
      string name = ((string *)tmp99.data)[tmp100];

      if (!Parser_first_pass(&/* ? */ *p) &&
          !Table_known_type(&/* ? */ *p->table, typ)) {

        Parser_error(p, _STR("fn_args: unknown type %.*s", typ.len, typ.str));
      };

      if (is_mut) {

        typ = string_add(typ, tos3("*"));
      };

      Var v = (Var){
          .name = name,
          .typ = typ,
          .is_arg = 1,
          .is_mut = is_mut,
          .ptr = is_mut,
          .line_nr = p->scanner->line_nr,
          .token_idx = Parser_cur_tok_index(&/* ? */ *p),
          .idx = 0,
          .is_const = 0,
          .args = new_array(0, 1, sizeof(Var)),
          .attr = tos((byte *)"", 0),
          .is_alloc = 0,
          .is_returned = 0,
          .ref = 0,
          .parent_fn = tos((byte *)"", 0),
          .mod = tos((byte *)"", 0),
          .is_global = 0,
          .is_used = 0,
          .is_changed = 0,
          .scope_level = 0,
          .is_c = 0,
          .is_moved = 0,
      };

      Parser_register_var(p, v);

      _PUSH(&f->args, (/*typ = array_Var   tmp_typ=Var*/ v), tmp102, Var);
    };

    if (p->tok == main__TokenKind_comma) {

      Parser_next(p);
    };

    if (p->tok == main__TokenKind_ellipsis) {

      if (!f->is_c) {

        Parser_error(p, tos3("variadic argument syntax must be `arg_name "
                             "...type` eg `argname ...string`."));
      };

      _PUSH(&f->args,
            (/*typ = array_Var   tmp_typ=Var*/ (Var){
                .typ = tos3("..."),
                .name = tos((byte *)"", 0),
                .idx = 0,
                .is_arg = 0,
                .is_const = 0,
                .args = new_array(0, 1, sizeof(Var)),
                .attr = tos((byte *)"", 0),
                .is_mut = 0,
                .is_alloc = 0,
                .is_returned = 0,
                .ptr = 0,
                .ref = 0,
                .parent_fn = tos((byte *)"", 0),
                .mod = tos((byte *)"", 0),
                .is_global = 0,
                .is_used = 0,
                .is_changed = 0,
                .scope_level = 0,
                .is_c = 0,
                .is_moved = 0,
                .line_nr = 0,
                .token_idx = 0}),
            tmp103, Var);

      Parser_next(p);
    };
  };

  { Parser_check(p, main__TokenKind_rpar); }
}
Fn *Parser_fn_call_args(Parser *p, Fn *f) {

  Parser_check(p, main__TokenKind_lpar);

  bool is_variadic = 0;

  if (f->args.len > 0) {

    Var last_arg = *(Var *)array_last(f->args);

    is_variadic = string_starts_with(last_arg.typ, tos3("..."));
  };

  if (f->is_c) {

    while (p->tok != main__TokenKind_rpar) {

      p->calling_c = 1;

      int ph = CGen_add_placeholder(&/* ? */ *p->cgen);

      string typ = Parser_bool_expression(p);

      if (string_eq(typ, tos3("byte*"))) {

        CGen_set_placeholder(p->cgen, ph, tos3("(char*)"));
      };

      if (p->tok == main__TokenKind_comma) {

        Parser_gen(p, tos3(", "));

        Parser_check(p, main__TokenKind_comma);
      };
    };

    Parser_check(p, main__TokenKind_rpar);

    return f;
  };

  if (p->v->pref->is_debug && string_eq(f->name, tos3("panic")) && !p->is_js) {

    string mod_name = string_replace(p->mod, tos3("_dot_"), tos3("."));

    string fn_name = string_replace(
        p->cur_fn.name, _STR("%.*s__", p->mod.len, p->mod.str), tos3(""));

    string file_path = main__cescaped_path(p->file_path);

    CGen_resetln(p->cgen,
                 string_replace(p->cgen->cur_line, tos3("v_panic ("),
                                _STR("panic_debug (%d, tos3(\"%.*s\"), "
                                     "tos3(\"%.*s\"), tos2((byte *)\"%.*s\"), ",
                                     p->scanner->line_nr, file_path.len,
                                     file_path.str, mod_name.len, mod_name.str,
                                     fn_name.len, fn_name.str)));
  };

  array_Var tmp111 = f->args;
  for (int i = 0; i < tmp111.len; i++) {
    Var arg = ((Var *)tmp111.data)[i];

    if (i == 0 && f->is_method) {

      if (f->args.len > 1 && !p->is_js) {

        Parser_gen(p, tos3(","));
      };

      continue;
    };

    if (i == f->args.len - 1 && string_starts_with(arg.typ, tos3("..."))) {

      break;
    };

    int ph = CGen_add_placeholder(&/* ? */ *p->cgen);

    if (p->tok == main__TokenKind_rpar) {

      string str_args = Fn_str_args(&/* ? */ *f, p->table);

      Parser_error(p,
                   _STR("not enough arguments in call to `%.*s (%.*s)`",
                        f->name.len, f->name.str, str_args.len, str_args.str));
    };

    if (arg.is_mut) {

      if (p->tok != main__TokenKind_key_mut && p->tok == main__TokenKind_name) {

        string dots_example = _STR("mut %.*s", p->lit.len, p->lit.str);

        if (i > 0) {

          dots_example = string_add(tos3(".., "), dots_example);
        };

        if (i < f->args.len - 1) {

          dots_example = string_add(dots_example, tos3(",.."));
        };

        Parser_error(p, _STR("`%.*s` is a mutable argument, you need to "
                             "provide `mut`: `%.*s(%.*s)`",
                             arg.name.len, arg.name.str, f->name.len,
                             f->name.str, dots_example.len, dots_example.str));
      };

      if (Parser_peek(&/* ? */ *p) != main__TokenKind_name) {

        Parser_error(
            p, _STR("`%.*s` is a mutable argument, you need to provide a "
                    "variable to modify: `%.*s(... mut a...)`",
                    arg.name.len, arg.name.str, f->name.len, f->name.str));
      };

      Parser_check(p, main__TokenKind_key_mut);

      string var_name = p->lit;

      Option_Var tmp116 = Parser_find_var(&/* ? */ *p, var_name);
      if (!tmp116.ok) {
        string err = tmp116.error;

        Parser_error(
            p, _STR("`%.*s` is a mutable argument, you need to provide a "
                    "variable to modify: `%.*s(... mut a...)`",
                    arg.name.len, arg.name.str, f->name.len, f->name.str));

        v_exit(1);
      }
      Var v = *(Var *)tmp116.data;
      ;

      if (!v.is_changed) {

        Parser_mark_var_changed(p, v);
      };
    };

    p->expected_type = arg.typ;

    bool clone = p->pref->autofree && string_eq(arg.typ, tos3("string")) &&
                 arg.is_moved && string_ne(p->mod, tos3("builtin"));

    if (clone) {

      Parser_gen(p, _STR("/*YY f=%.*s arg=%.*s is_moved=%d*/string_clone(",
                         f->name.len, f->name.str, arg.name.len, arg.name.str,
                         arg.is_moved));
    };

    string typ = Parser_bool_expression(p);

    if (string_starts_with(typ, tos3("..."))) {

      typ = string_right(typ, 3);
    };

    if (clone) {

      Parser_gen(p, tos3(")"));
    };

    if (i == 0 &&
        (string_eq(f->name, tos3("println")) ||
         string_eq(f->name, tos3("print"))) &&
        string_eq(typ, tos3("ustring"))) {

      if (string_eq(typ, tos3("ustring"))) {

        Parser_gen(p, tos3(".s"));
      };

      typ = tos3("string");
    };

    if (i == 0 &&
        (string_eq(f->name, tos3("println")) ||
         string_eq(f->name, tos3("print"))) &&
        string_ne(typ, tos3("string")) && string_ne(typ, tos3("ustring")) &&
        string_ne(typ, tos3("void"))) {

      Type T = Table_find_type(&/* ? */ *p->table, typ);

#ifndef _WIN32

#ifndef _VJS

      string fmt = Parser_typ_to_fmt(p, typ, 0);

      if (string_ne(fmt, tos3(""))) {

        string nl =
            (string_eq(f->name, tos3("println"))) ? (tos3("\\n")) : (tos3(""));

        CGen_resetln(p->cgen,
                     string_replace(
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

        CGen_set_placeholder(p->cgen, ph, tos3("ptr_str("));

        Parser_gen(p, tos3(")"));

        continue;
      };

#ifndef _VJS

      if (!Type_has_method(&/* ? */ T, tos3("str"))) {

        if (string_starts_with(T.name, tos3("array_"))) {

          Parser_gen_array_str(p, T);

          CGen_set_placeholder(p->cgen, ph,
                               _STR("%.*s_str(", typ.len, typ.str));

          Parser_gen(p, tos3(")"));

          continue;

        } else if (T.cat == main__TypeCategory_struct_) {

          Parser_gen_struct_str(p, T);

          CGen_set_placeholder(p->cgen, ph,
                               _STR("%.*s_str(", typ.len, typ.str));

          Parser_gen(p, tos3(")"));

          continue;
        };

        string error_msg =
            (_STR("`%.*s` needs to have method `str() string` to be printable",
                  typ.len, typ.str));

        Parser_error(p, error_msg);
      };

      CGen_set_placeholder(p->cgen, ph, _STR("%.*s_str(", typ.len, typ.str));

      Parser_gen(p, tos3(")"));

#endif
      ;

      continue;
    };

    string got = typ;

    string expected = arg.typ;

    bool got_ptr = string_ends_with(got, tos3("*"));

    bool exp_ptr = string_ends_with(expected, tos3("*"));

    if (!Parser_check_types_no_throw(p, got, expected)) {

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

      Parser_error(
          p, string_add(
                 _STR("cannot use type `%.*s` as type `%.*s` in %.*s ", typ.len,
                      typ.str, arg.typ.len, arg.typ.str, nr.len, nr.str),
                 _STR("argument to `%.*s()`", f->name.len, f->name.str)));
    };

    bool is_interface = Table_is_interface(&/* ? */ *p->table, arg.typ);

    if (!is_interface) {

      if (got_ptr && !exp_ptr) {

        CGen_set_placeholder(p->cgen, ph, tos3("*"));
      };

      if (!got_ptr && exp_ptr && string_ne(got, tos3("voidptr"))) {

        if (string_starts_with(expected, tos3("array_")) && exp_ptr) {

          CGen_set_placeholder(p->cgen, ph, tos3("& /*111*/ (array[]){"));

          Parser_gen(p, tos3("}[0] "));

        } else if (!(string_eq(expected, tos3("void*")) &&
                     string_eq(got, tos3("int"))) &&
                   !(string_eq(expected, tos3("byte*")) &&
                     string_contains(got, tos3("]byte"))) &&
                   !(string_eq(expected, tos3("byte*")) &&
                     string_eq(got, tos3("string"))) &&
                   !(string_eq(expected, tos3("byte*")) &&
                     string_eq(got, tos3("byteptr")))) {

          CGen_set_placeholder(p->cgen, ph,
                               _STR("& /*112 EXP:\"%.*s\" GOT:\"%.*s\" */",
                                    expected.len, expected.str, got.len,
                                    got.str));
        };
      };

    } else if (is_interface) {

      if (!got_ptr) {

        CGen_set_placeholder(p->cgen, ph, tos3("&"));
      };

      Type interface_type = Table_find_type(&/* ? */ *p->table, arg.typ);

      array_Fn tmp131 = interface_type.methods;
      for (int tmp132 = 0; tmp132 < tmp131.len; tmp132++) {
        Fn method = ((Fn *)tmp131.data)[tmp132];

        Parser_gen(p, _STR(", %.*s_%.*s ", typ.len, typ.str, method.name.len,
                           method.name.str));
      };
    };

    if (i < f->args.len - 1) {

      if (p->tok != main__TokenKind_comma && !is_variadic) {

        Parser_error(p, _STR("wrong number of arguments for %d,%.*s fn `%.*s`: "
                             "expected %d, but got less",
                             i, arg.name.len, arg.name.str, f->name.len,
                             f->name.str, f->args.len));
      };

      if (p->tok == main__TokenKind_comma) {

        Parser_fgen(p, tos3(", "));
      };

      if (!is_variadic) {

        Parser_next(p);

        Parser_gen(p, tos3(","));
      };
    };
  };

  if (!Parser_first_pass(&/* ? */ *p) && is_variadic) {

    Parser_fn_gen_caller_vargs(p, f);
  };

  if (p->tok == main__TokenKind_comma) {

    Parser_error(p, _STR("wrong number of arguments for fn `%.*s`: expected "
                         "%d, but got more",
                         f->name.len, f->name.str, f->args.len));
  };

  Parser_check(p, main__TokenKind_rpar);

  return f;
}
string Parser_fn_register_vargs_stuct(Parser *p, Fn *f, string typ,
                                      array_string values) {

  string vargs_struct = _STR("_V_FnVargs_%.*s", f->name.len, f->name.str);

  Type varg_type = (Type){.cat = main__TypeCategory_struct_,
                          .name = vargs_struct,
                          .mod = p->mod,
                          .fields = new_array(0, 1, sizeof(Var)),
                          .methods = new_array(0, 1, sizeof(Fn)),
                          .parent = tos((byte *)"", 0),
                          .is_c = 0,
                          .enum_vals = new_array(0, 1, sizeof(string)),
                          .gen_types = new_array(0, 1, sizeof(string)),
                          .is_placeholder = 0,
                          .gen_str = 0};

  if (values.len > 0) {

    Table_rewrite_type(p->table, varg_type);

  } else {

    Table_register_type2(p->table, varg_type);
  };

  Table_add_field(p->table, vargs_struct, tos3("len"), tos3("int"), 0, tos3(""),
                  main__AccessMod_public);

  Table_add_field(p->table, vargs_struct, _STR("args[%d]", values.len), typ, 0,
                  tos3(""), main__AccessMod_public);

  return vargs_struct;
}
void Parser_fn_gen_caller_vargs(Parser *p, Fn *f) {

  Var last_arg = *(Var *)array_last(f->args);

  string varg_def_type = string_right(last_arg.typ, 3);

  array_string values = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (p->tok != main__TokenKind_rpar) {

    if (p->tok == main__TokenKind_comma) {

      Parser_check(p, main__TokenKind_comma);
    };

    CGen_start_tmp(p->cgen);

    string varg_type = Parser_bool_expression(p);

    string varg_value = CGen_end_tmp(p->cgen);

    Parser_check_types(p, last_arg.typ, varg_type);

    string ref_deref = (string_ends_with(last_arg.typ, tos3("*")) &&
                        !string_ends_with(varg_type, tos3("*")))
                           ? (tos3("&"))
                           : ((!string_ends_with(last_arg.typ, tos3("*")) &&
                               string_ends_with(varg_type, tos3("*")))
                                  ? (tos3("*"))
                                  : (tos3("")));

    _PUSH(&values,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "%.*s%.*s", ref_deref.len, ref_deref.str, varg_value.len,
              varg_value.str)),
          tmp141, string);
  };

  array_VargAccess tmp142 = p->table->varg_access;
  for (int tmp143 = 0; tmp143 < tmp142.len; tmp143++) {
    VargAccess va = ((VargAccess *)tmp142.data)[tmp143];

    if (string_ne(va.fn_name, f->name)) {

      continue;
    };

    if (va.index >= values.len) {

      Parser_error_with_token_index(
          p,
          _STR("variadic arg index out of range: %d/%d, vargs are 0 indexed",
               va.index, values.len - 1),
          va.tok_idx);
    };
  };

  if (f->args.len > 1) {

    CGen_gen(p->cgen, tos3(","));
  };

  string vargs_struct =
      Parser_fn_register_vargs_stuct(p, f, varg_def_type, values);

  CGen_gen(p->cgen, string_add(string_add(_STR("&(%.*s){.len=%d,.args={",
                                               vargs_struct.len,
                                               vargs_struct.str, values.len),
                                          array_string_join(values, tos3(","))),
                               tos3("}}")));
}
string Parser_register_multi_return_stuct(Parser *p, array_string types) {

  string typ = string_add(tos3("_V_MulRet_"),
                          string_replace(array_string_join(types, tos3("_V_")),
                                         tos3("*"), tos3("_PTR_")));

  if (Table_known_type(&/* ? */ *p->table, typ)) {

    return typ;
  };

  Table_register_type2(p->table,
                       (Type){.cat = main__TypeCategory_struct_,
                              .name = typ,
                              .mod = p->mod,
                              .fields = new_array(0, 1, sizeof(Var)),
                              .methods = new_array(0, 1, sizeof(Fn)),
                              .parent = tos((byte *)"", 0),
                              .is_c = 0,
                              .enum_vals = new_array(0, 1, sizeof(string)),
                              .gen_types = new_array(0, 1, sizeof(string)),
                              .is_placeholder = 0,
                              .gen_str = 0});

  array_string tmp146 = string_split(
      string_replace(string_replace(typ, tos3("_V_MulRet_"), tos3("")),
                     tos3("_PTR_"), tos3("*")),
      tos3("_V_"));
  for (int i = 0; i < tmp146.len; i++) {
    string t = ((string *)tmp146.data)[i];

    Table_add_field(p->table, typ, _STR("var_%d", i), t, 0, tos3(""),
                    main__AccessMod_public);
  };

  _PUSH(&p->cgen->typedefs,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "typedef struct %.*s %.*s;", typ.len, typ.str, typ.len, typ.str)),
        tmp147, string);

  return typ;
}
string Fn_typ_str(Fn *f) {

  strings__Builder sb = strings__new_builder(50);

  strings__Builder_write(&/* ? */ sb, tos3("fn ("));

  array_Var tmp149 = f->args;
  for (int i = 0; i < tmp149.len; i++) {
    Var arg = ((Var *)tmp149.data)[i];

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
string Fn_str_args(Fn *f, Table *table) {

  string s = tos3("");

  array_Var tmp151 = f->args;
  for (int i = 0; i < tmp151.len; i++) {
    Var arg = ((Var *)tmp151.data)[i];

    if (Table_is_interface(&/* ? */ *table, arg.typ)) {

      s = string_add(s, _STR(" void* %.*s", arg.name.len, arg.name.str));

      Type interface_type = Table_find_type(&/* ? */ *table, arg.typ);

      array_Fn tmp153 = interface_type.methods;
      for (int tmp154 = 0; tmp154 < tmp153.len; tmp154++) {
        Fn method = ((Fn *)tmp153.data)[tmp154];

        s = string_add(s, _STR(", %.*s (*%.*s_%.*s)(void*", method.typ.len,
                               method.typ.str, arg.typ.len, arg.typ.str,
                               method.name.len, method.name.str));

        if (method.args.len > 1) {

          array_Var tmp155 = array_right(method.args, 1);
          for (int tmp156 = 0; tmp156 < tmp155.len; tmp156++) {
            Var a = ((Var *)tmp155.data)[tmp156];

            s = string_add(s, _STR(", %.*s", a.typ.len, a.typ.str));
          };
        };

        s = string_add(s, tos3(")"));
      };

    } else if (string_starts_with(arg.typ, tos3("..."))) {

      s = string_add(s, _STR("_V_FnVargs_%.*s *%.*s", f->name.len, f->name.str,
                             arg.name.len, arg.name.str));

    } else {

      s = string_add(
          s, Table_cgen_name_type_pair(&/* ? */ *table, arg.name, arg.typ));
    };

    if (i < f->args.len - 1) {

      s = string_add(s, tos3(", "));
    };
  };

  return s;
}
string Parser_find_misspelled_local_var(Parser *p, string name, f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_var = tos3("");

  array_Var tmp159 = p->local_vars;
  for (int tmp160 = 0; tmp160 < tmp159.len; tmp160++) {
    Var var = ((Var *)tmp159.data)[tmp160];

    if (var.scope_level > p->cur_fn.scope_level) {

      continue;
    };

    string n = string_all_after(name, tos3("."));

    if (string_eq(var.name, tos3("")) ||
        (n.len - var.name.len > 2 || var.name.len - n.len > 2)) {

      continue;
    };

    f32 coeff = strings__dice_coefficient(var.name, n);

    if (f32_gt(coeff, closest)) {

      closest = coeff;

      closest_var = var.name;
    };
  };

  return (f32_ge(closest, min_match)) ? (closest_var) : (tos3(""));
}
bool array_Fn_contains(array_Fn fns, Fn f) {

  array_Fn tmp163 = fns;
  for (int tmp164 = 0; tmp164 < tmp163.len; tmp164++) {
    Fn ff = ((Fn *)tmp163.data)[tmp164];

    if (string_eq(ff.name, f.name)) {

      return 1;
    };
  };

  return 0;
}
string Parser_gen_var_decl(Parser *p, string name, bool is_static) {

  int pos = CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = Parser_bool_expression(p);

  if (string_starts_with(typ, tos3("..."))) {

    typ = string_right(typ, 3);
  };

  bool or_else = p->tok == main__TokenKind_key_orelse;

  string tmp = Parser_get_tmp(p);

  if (or_else) {

    CGen_set_placeholder(
        p->cgen, pos, _STR("%.*s %.*s = ", typ.len, typ.str, tmp.len, tmp.str));

    Parser_genln(p, tos3(";"));

    typ = string_replace(typ, tos3("Option_"), tos3(""));

    Parser_next(p);

    Parser_check(p, main__TokenKind_lcbr);

    Parser_genln(p, _STR("if (!%.*s .ok) {", tmp.len, tmp.str));

    Parser_register_var(p, (Var){.name = tos3("err"),
                                 .typ = tos3("string"),
                                 .is_mut = 0,
                                 .is_used = 1,
                                 .idx = 0,
                                 .is_arg = 0,
                                 .is_const = 0,
                                 .args = new_array(0, 1, sizeof(Var)),
                                 .attr = tos((byte *)"", 0),
                                 .is_alloc = 0,
                                 .is_returned = 0,
                                 .ptr = 0,
                                 .ref = 0,
                                 .parent_fn = tos((byte *)"", 0),
                                 .mod = tos((byte *)"", 0),
                                 .is_global = 0,
                                 .is_changed = 0,
                                 .scope_level = 0,
                                 .is_c = 0,
                                 .is_moved = 0,
                                 .line_nr = 0,
                                 .token_idx = 0});

    Parser_genln(p, _STR("string err = %.*s . error;", tmp.len, tmp.str));

    Parser_statements(p);

    Parser_genln(p,
                 _STR("%.*s %.*s = *(%.*s*) %.*s . data;", typ.len, typ.str,
                      name.len, name.str, typ.len, typ.str, tmp.len, tmp.str));

    if (!p->returns && p->prev_tok2 != main__TokenKind_key_continue &&
        p->prev_tok2 != main__TokenKind_key_break) {

      Parser_error(p, tos3("`or` block must return/exit/continue/break/panic"));
    };

    p->returns = 0;

    return typ;
  };

  string gen_name = Table_var_cgen_name(&/* ? */ *p->table, name);

  string nt_gen = Table_cgen_name_type_pair(&/* ? */ *p->table, gen_name, typ);

  if (!p->is_empty_c_struct_init && !string_starts_with(typ, tos3("["))) {

    nt_gen = string_add(nt_gen, tos3("="));

  } else if (string_starts_with(typ, tos3("[")) &&
             string_at(typ, typ.len - 1) != '*') {

    string initializer = string_right(p->cgen->cur_line, pos);

    if (initializer.len > 0) {

      CGen_resetln(
          p->cgen,
          string_add(tos3(" = {"), string_all_after(initializer, tos3("{"))));

    } else if (initializer.len == 0) {

      CGen_resetln(p->cgen, tos3(" = { 0 }"));
    };
  };

  if (is_static) {

    nt_gen = _STR("static %.*s", nt_gen.len, nt_gen.str);
  };

  CGen_set_placeholder(p->cgen, pos, nt_gen);

  return typ;
}
void Parser_gen_fn_decl(Parser *p, Fn f, string typ, string str_args) {

  string dll_export_linkage =
      (p->os == main__OS_msvc && string_eq(p->attr, tos3("live")) &&
       p->pref->is_so)
          ? (tos3("__declspec(dllexport) "))
          : ((string_eq(p->attr, tos3("inline"))) ? (tos3("static inline "))
                                                  : (tos3("")));

  string fn_name_cgen =
      Table_fn_gen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

  Parser_genln(p,
               _STR("%.*s%.*s %.*s(%.*s) {", dll_export_linkage.len,
                    dll_export_linkage.str, typ.len, typ.str, fn_name_cgen.len,
                    fn_name_cgen.str, str_args.len, str_args.str));
}
void Parser_gen_blank_identifier_assign(Parser *p) {

  int assign_error_tok_idx = p->token_idx;

  Parser_check_name(p);

  Parser_check_space(p, main__TokenKind_assign);

  string expr = p->lit;

  bool is_indexer = Parser_peek(&/* ? */ *p) == main__TokenKind_lsbr;

  bool is_fn_call = Parser_peek(&/* ? */ *p) == main__TokenKind_lpar ||
                    (Parser_peek(&/* ? */ *p) == main__TokenKind_dot &&
                     (*(Token *)array_get(p->tokens, p->token_idx + 2)).tok ==
                         main__TokenKind_lpar);

  if (!is_indexer && !is_fn_call) {

    Parser_error_with_token_index(
        p, _STR("assigning `%.*s` to `_` is redundant", expr.len, expr.str),
        assign_error_tok_idx);
  };

  int pos = CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = Parser_bool_expression(p);

  string tmp = Parser_get_tmp(p);

  if (p->tok == main__TokenKind_key_orelse) {

    CGen_set_placeholder(
        p->cgen, pos, _STR("%.*s %.*s = ", typ.len, typ.str, tmp.len, tmp.str));

    Parser_genln(p, tos3(";"));

    typ = string_replace(typ, tos3("Option_"), tos3(""));

    Parser_next(p);

    Parser_check(p, main__TokenKind_lcbr);

    Parser_genln(p, _STR("if (!%.*s .ok) {", tmp.len, tmp.str));

    Parser_register_var(p, (Var){.name = tos3("err"),
                                 .typ = tos3("string"),
                                 .is_mut = 0,
                                 .is_used = 1,
                                 .idx = 0,
                                 .is_arg = 0,
                                 .is_const = 0,
                                 .args = new_array(0, 1, sizeof(Var)),
                                 .attr = tos((byte *)"", 0),
                                 .is_alloc = 0,
                                 .is_returned = 0,
                                 .ptr = 0,
                                 .ref = 0,
                                 .parent_fn = tos((byte *)"", 0),
                                 .mod = tos((byte *)"", 0),
                                 .is_global = 0,
                                 .is_changed = 0,
                                 .scope_level = 0,
                                 .is_c = 0,
                                 .is_moved = 0,
                                 .line_nr = 0,
                                 .token_idx = 0});

    Parser_genln(p, _STR("string err = %.*s . error;", tmp.len, tmp.str));

    Parser_statements(p);

    p->returns = 0;

  } else {

    if (is_fn_call) {

      Parser_gen(p, tos3(";"));

    } else {

      CGen_resetln(p->cgen, _STR("{%.*s _ = %.*s;}", typ.len, typ.str,
                                 p->cgen->cur_line.len, p->cgen->cur_line.str));
    };
  };
}
string main__types_to_c(array_Type types, Table *table) {

  strings__Builder sb = strings__new_builder(10);

  array_Type tmp22 = types;
  for (int tmp23 = 0; tmp23 < tmp22.len; tmp23++) {
    Type t = ((Type *)tmp22.data)[tmp23];

    if (t.cat != main__TypeCategory_union_ &&
        t.cat != main__TypeCategory_struct_ &&
        t.cat != main__TypeCategory_objc_interface) {

      continue;
    };

    if (t.cat == main__TypeCategory_objc_interface) {

      strings__Builder_writeln(
          &/* ? */ sb, _STR("@interface %.*s : %.*s { @public", t.name.len,
                            t.name.str, t.parent.len, t.parent.str));

    } else {

      string kind = (t.cat == main__TypeCategory_union_) ? (tos3("union"))
                                                         : (tos3("struct"));

      strings__Builder_writeln(
          &/* ? */ sb,
          _STR("%.*s %.*s {", kind.len, kind.str, t.name.len, t.name.str));
    };

    array_Var tmp25 = t.fields;
    for (int tmp26 = 0; tmp26 < tmp25.len; tmp26++) {
      Var field = ((Var *)tmp25.data)[tmp26];

      strings__Builder_write(&/* ? */ sb, tos3("\t"));

      strings__Builder_writeln(
          &/* ? */ sb, string_add(Table_cgen_name_type_pair(
                                      &/* ? */ *table, field.name, field.typ),
                                  tos3(";")));
    };

    strings__Builder_writeln(&/* ? */ sb, tos3("};\n"));

    if (t.cat == main__TypeCategory_objc_interface) {

      strings__Builder_writeln(&/* ? */ sb, tos3("@end"));
    };
  };

  return strings__Builder_str(sb);
}
void Parser_index_get(Parser *p, string typ, int fn_ph, IndexCfg cfg) {

  string index_expr = tos3("");

  if (p->cgen->is_tmp) {

    index_expr = string_right(p->cgen->tmp_line, fn_ph);

    CGen_resetln(p->cgen, string_left(p->cgen->tmp_line, fn_ph));

  } else {

    index_expr = string_right(p->cgen->cur_line, fn_ph);

    CGen_resetln(p->cgen, string_left(p->cgen->cur_line, fn_ph));
  };

  string tmp = Parser_get_tmp(p);

  string tmp_ok = Parser_get_tmp(p);

  if (cfg.is_map) {

    Parser_gen(p, _STR("%.*s", tmp.len, tmp.str));

    string def = main__type_default(typ);

    CGen_insert_before(
        p->cgen,
        string_add(_STR("%.*s %.*s = %.*s; ", typ.len, typ.str, tmp.len,
                        tmp.str, def.len, def.str),
                   _STR("bool %.*s = map_get(/*%.*s : %d*/%.*s, & %.*s);",
                        tmp_ok.len, tmp_ok.str, p->file_name.len,
                        p->file_name.str, p->scanner->line_nr, index_expr.len,
                        index_expr.str, tmp.len, tmp.str)));

  } else if (cfg.is_arr) {

    if (p->pref->translated && !p->builtin_mod) {

      Parser_gen(p, _STR("%.*s ]", index_expr.len, index_expr.str));

    } else {

      if (cfg.is_ptr) {

        Parser_gen(p, _STR("( *(%.*s*) array_get(* %.*s) )", typ.len, typ.str,
                           index_expr.len, index_expr.str));

      } else {

        Parser_gen(p, _STR("( *(%.*s*) array_get(%.*s) )", typ.len, typ.str,
                           index_expr.len, index_expr.str));
      };
    };

  } else if (cfg.is_str && !p->builtin_mod) {

    Parser_gen(p, _STR("string_at(%.*s)", index_expr.len, index_expr.str));
  };

  if (cfg.is_map && string_eq(typ, tos3("string"))) {

    CGen_insert_before(p->cgen, _STR("if (!%.*s) %.*s = tos((byte *)\"\", 0);",
                                     tmp_ok.len, tmp_ok.str, tmp.len, tmp.str));
  };
}
string Table_fn_gen_name(Table *table, Fn *f) {

  string name = f->name;

  if (f->is_method) {

    name = _STR("%.*s_%.*s", f->receiver_typ.len, f->receiver_typ.str,
                f->name.len, f->name.str);

    name = string_replace(name, tos3(" "), tos3(""));

    name = string_replace(name, tos3("*"), tos3(""));

    name = string_replace(name, tos3("+"), tos3("plus"));

    name = string_replace(name, tos3("-"), tos3("minus"));
  };

  if (string_eq(f->mod, tos3("builtin")) &&
      _IN(string, (f->name), main__CReserved)) {

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
      !string_contains(f->name, tos3("window_proc")) &&
      !string_ends_with(name, tos3("_str")) &&
      !string_contains(name, tos3("contains"))) {

    int tmp32 = 0;
    bool tmp33 = map_get(/*gen_c.v : 234*/ table->obf_ids, name, &tmp32);

    int idx = tmp32;

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
void Parser_gen_method_call(Parser *p, string receiver_type, string ftyp,
                            string cgen_name, Var receiver, int method_ph) {

  string method_call = string_add(cgen_name, tos3("("));

  if (receiver.ref ||
      (receiver.is_mut && !string_contains(receiver_type, tos3("*")))) {

    method_call = string_add(method_call, tos3("& /* ? */"));
  };

  if (!receiver.is_mut && string_contains(receiver_type, tos3("*"))) {

    method_call = string_add(method_call, tos3("*"));
  };

  string cast = tos3("");

  if (string_eq(ftyp, tos3("void*"))) {

    if (string_starts_with(receiver_type, tos3("array_"))) {

      cast = string_all_after(receiver_type, tos3("_"));

      cast = _STR("*(%.*s*) ", cast.len, cast.str);

    } else {

      cast = tos3("(voidptr) ");
    };
  };

  CGen_set_placeholder(
      p->cgen, method_ph,
      _STR("%.*s %.*s", cast.len, cast.str, method_call.len, method_call.str));
}
void Parser_gen_array_at(Parser *p, string typ_, bool is_arr0, int fn_ph) {

  string typ = typ_;

  if (is_arr0) {

    typ = string_right(typ, 6);
  };

  if (string_eq(typ, tos3("array"))) {

    typ = tos3("void*");
  };

  if (p->pref->translated && !p->builtin_mod) {

    CGen_set_placeholder(p->cgen, fn_ph, _STR("((%.*s*)(", typ.len, typ.str));

    Parser_gen(p, tos3(".data))["));

  } else {

    Parser_gen(p, tos3(","));
  };
}
void Parser_gen_for_header(Parser *p, string i, string tmp, string var_typ,
                           string val) {

  Parser_genln(p, _STR("for (int %.*s = 0; %.*s < %.*s.len; %.*s++) {", i.len,
                       i.str, i.len, i.str, tmp.len, tmp.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  Parser_genln(p, _STR("%.*s %.*s = ((%.*s *) %.*s . data)[%.*s];", var_typ.len,
                       var_typ.str, val.len, val.str, var_typ.len, var_typ.str,
                       tmp.len, tmp.str, i.len, i.str));
}
void Parser_gen_for_str_header(Parser *p, string i, string tmp, string var_typ,
                               string val) {

  Parser_genln(p, _STR("array_byte bytes_%.*s = string_bytes( %.*s );", tmp.len,
                       tmp.str, tmp.len, tmp.str));

  Parser_genln(p,
               _STR(";\nfor (int %.*s = 0; %.*s < %.*s .len; %.*s ++) {", i.len,
                    i.str, i.len, i.str, tmp.len, tmp.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  Parser_genln(p, _STR("%.*s %.*s = ((%.*s *) bytes_%.*s . data)[%.*s];",
                       var_typ.len, var_typ.str, val.len, val.str, var_typ.len,
                       var_typ.str, tmp.len, tmp.str, i.len, i.str));
}
void Parser_gen_for_range_header(Parser *p, string i, string range_end,
                                 string tmp, string var_type, string val) {

  Parser_genln(p, _STR(";\nfor (int %.*s = %.*s; %.*s < %.*s; %.*s++) {", i.len,
                       i.str, tmp.len, tmp.str, i.len, i.str, range_end.len,
                       range_end.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  Parser_genln(p, _STR("%.*s %.*s = %.*s;", var_type.len, var_type.str, val.len,
                       val.str, i.len, i.str));
}
void Parser_gen_for_map_header(Parser *p, string i, string tmp, string var_typ,
                               string val, string typ) {

  string def = main__type_default(typ);

  Parser_genln(p, _STR("array_string keys_%.*s = map_keys(& %.*s ); ", tmp.len,
                       tmp.str, tmp.len, tmp.str));

  Parser_genln(
      p, _STR("for (int l = 0; l < keys_%.*s .len; l++) {", tmp.len, tmp.str));

  Parser_genln(p, _STR("string %.*s = ((string*)keys_%.*s .data)[l];", i.len,
                       i.str, tmp.len, tmp.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  Parser_genln(p,
               _STR("%.*s %.*s = %.*s; map_get(%.*s, %.*s, & %.*s);",
                    var_typ.len, var_typ.str, val.len, val.str, def.len,
                    def.str, tmp.len, tmp.str, i.len, i.str, val.len, val.str));
}
void Parser_gen_for_varg_header(Parser *p, string i, string varg,
                                string var_typ, string val) {

  Parser_genln(p, _STR("for (int %.*s = 0; %.*s < %.*s->len; %.*s++) {", i.len,
                       i.str, i.len, i.str, varg.len, varg.str, i.len, i.str));

  if (string_eq(val, tos3("_"))) {

    return;
  };

  Parser_genln(p, _STR("%.*s %.*s = ((%.*s *) %.*s->args)[%.*s];", var_typ.len,
                       var_typ.str, val.len, val.str, var_typ.len, var_typ.str,
                       varg.len, varg.str, i.len, i.str));
}
void Parser_gen_array_init(Parser *p, string typ, bool no_alloc, int new_arr_ph,
                           int nr_elems) {

  string new_arr = tos3("new_array_from_c_array");

  if (no_alloc) {

    new_arr = string_add(new_arr, tos3("_no_alloc"));
  };

  if (nr_elems == 0) {

    Parser_gen(p, tos3(" TCCSKIP(0) })"));

  } else {

    Parser_gen(p, tos3(" })"));
  };

  if (!Parser_first_pass(&/* ? */ *p)) {

    CGen_set_placeholder(
        p->cgen, new_arr_ph,
        _STR("%.*s(%d, %d, sizeof(%.*s), EMPTY_ARRAY_OF_ELEMS( %.*s, %d ) { ",
             new_arr.len, new_arr.str, nr_elems, nr_elems, typ.len, typ.str,
             typ.len, typ.str, nr_elems));
  };
}
void Parser_gen_array_set(Parser *p, string typ, bool is_ptr, bool is_map,
                          int fn_ph, int assign_pos, bool is_cao) {

  string val = string_right(p->cgen->cur_line, assign_pos);

  CGen_resetln(p->cgen, string_left(p->cgen->cur_line, assign_pos));

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

  CGen_set_placeholder(p->cgen, fn_ph, func);

  if (is_cao) {

    val = string_add(string_add(cao_tmp, string_all_before(val, tos3("="))),
                     string_all_after(val, tos3("=")));
  };

  Parser_gen(
      p, _STR(", & (%.*s []) { %.*s })", typ.len, typ.str, val.len, val.str));
}
bool Parser_gen_struct_init(Parser *p, string typ, Type t) {

  if (p->is_c_struct_init) {

    if (t.cat != main__TypeCategory_c_typedef) {

      CGen_insert_before(p->cgen, tos3("struct /*c struct init*/"));
    };
  };

  if (string_eq(typ, tos3("tm"))) {

    array_set(&/*q*/ p->cgen->lines, p->cgen->lines.len - 1,
              &(string[]){tos3("")});
  };

  Parser_next(p);

  Parser_check(p, main__TokenKind_lcbr);

  bool ptr = string_contains(typ, tos3("*"));

  if (!ptr) {

    if (p->is_c_struct_init) {

      if (p->tok == main__TokenKind_rcbr) {

        p->is_empty_c_struct_init = 1;

        Parser_check(p, main__TokenKind_rcbr);

        return 1;
      };

      Parser_gen(p, _STR("(struct %.*s) {", typ.len, typ.str));

      p->is_c_struct_init = 0;

    } else {

      Parser_gen(p, _STR("(%.*s) {", typ.len, typ.str));
    };

  } else {

    if (p->tok == main__TokenKind_not) {

      Parser_next(p);

      Parser_gen(p, tos3("0"));

      Parser_check(p, main__TokenKind_rcbr);

      return 1;
    };

    Parser_gen(p, _STR("(%.*s*)memdup(&(%.*s)  {", t.name.len, t.name.str,
                       t.name.len, t.name.str));
  };

  return 0;
}
void Parser_gen_struct_field_init(Parser *p, string field) {

  Parser_gen(p, _STR(".%.*s = ", field.len, field.str));
}
void Parser_gen_empty_map(Parser *p, string typ) {

  Parser_gen(p, _STR("new_map(1, sizeof(%.*s))", typ.len, typ.str));
}
void Parser_cast(Parser *p, string typ) {

  Parser_next(p);

  int pos = CGen_add_placeholder(&/* ? */ *p->cgen);

  if (p->tok == main__TokenKind_rpar) {

    p->ptr_cast = 1;

    Parser_next(p);
  };

  Parser_check(p, main__TokenKind_lpar);

  p->expected_type = typ;

  string expr_typ = Parser_bool_expression(p);

  bool casting_voidptr_to_value =
      string_eq(expr_typ, tos3("void*")) && string_ne(typ, tos3("int")) &&
      string_ne(typ, tos3("byteptr")) && !string_ends_with(typ, tos3("*"));

  p->expected_type = tos3("");

  bool is_byteptr = string_eq(expr_typ, tos3("byte*")) ||
                    string_eq(expr_typ, tos3("byteptr"));

  bool is_bytearr = string_eq(expr_typ, tos3("array_byte"));

  if (string_eq(typ, tos3("string"))) {

    if (is_byteptr || is_bytearr) {

      if (p->tok == main__TokenKind_comma) {

        Parser_check(p, main__TokenKind_comma);

        CGen_set_placeholder(p->cgen, pos, tos3("tos((byte *)"));

        if (is_bytearr) {

          Parser_gen(p, tos3(".data"));
        };

        Parser_gen(p, tos3(", "));

        Parser_check_types(p, Parser_expression(p), tos3("int"));

      } else {

        if (is_bytearr) {

          Parser_gen(p, tos3(".data"));
        };

        CGen_set_placeholder(p->cgen, pos, tos3("tos2((byte *)"));
      };

    } else if (string_eq(expr_typ, tos3("int"))) {

      Parser_error(
          p, _STR("cannot cast `%.*s` to `%.*s`, use `str()` method instead",
                  expr_typ.len, expr_typ.str, typ.len, typ.str));

    } else {

      Parser_error(p, _STR("cannot cast `%.*s` to `%.*s`", expr_typ.len,
                           expr_typ.str, typ.len, typ.str));
    };

  } else if (string_eq(typ, tos3("byte")) &&
             string_eq(expr_typ, tos3("string"))) {

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

  Parser_check(p, main__TokenKind_rpar);

  Parser_gen(p, tos3(")"));
}
string main__type_default(string typ) {

  if (string_starts_with(typ, tos3("array_"))) {

    return _STR("new_array(0, 1, sizeof( %.*s ))", string_right(typ, 6).len,
                string_right(typ, 6).str);
  };

  if (string_ends_with(typ, tos3("*"))) {

    return tos3("0");
  };

  if (string_contains(typ, tos3("__"))) {

    return tos3("{0}");
  };

  if (string_eq(typ, tos3("bool"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("string"))) { /* case */

    return tos3("tos((byte *)\"\", 0)");

  } else if (string_eq(typ, tos3("i8"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("i16"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("i64"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("u16"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("u32"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("u64"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("byte"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("int"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("rune"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("f32"))) { /* case */

    return tos3("0.0");

  } else if (string_eq(typ, tos3("f64"))) { /* case */

    return tos3("0.0");

  } else if (string_eq(typ, tos3("byteptr"))) { /* case */

    return tos3("0");

  } else if (string_eq(typ, tos3("voidptr"))) { /* case */

    return tos3("0");
  };

  return tos3("{0}");
}
void Parser_gen_array_push(Parser *p, int ph, string typ, string expr_type,
                           string tmp, string elm_type) {

  bool push_array = string_eq(typ, expr_type);

  if (push_array) {

    CGen_set_placeholder(p->cgen, ph, tos3("_PUSH_MANY(&"));

    Parser_gen(p, _STR("), %.*s, %.*s)", tmp.len, tmp.str, typ.len, typ.str));

  } else {

    Parser_check_types(p, expr_type, elm_type);

    string push_call = (string_contains(typ, tos3("*"))) ? (tos3("_PUSH("))
                                                         : (tos3("_PUSH(&"));

    CGen_set_placeholder(p->cgen, ph, push_call);

    if (string_ends_with(elm_type, tos3("*"))) {

      Parser_gen(p, _STR("), %.*s, %.*s)", tmp.len, tmp.str,
                         string_left(elm_type, elm_type.len - 1).len,
                         string_left(elm_type, elm_type.len - 1).str));

    } else {

      Parser_gen(p, _STR("), %.*s, %.*s)", tmp.len, tmp.str, elm_type.len,
                         elm_type.str));
    };
  };
}
void Parser_gen_json_for_type(Parser *p, Type typ) {

  string dec = tos3("");

  string enc = tos3("");

  string t = typ.name;

  if (string_eq(t, tos3("int")) || string_eq(t, tos3("string")) ||
      string_eq(t, tos3("bool"))) {

    return;
  };

  if (Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  Fn dec_fn = (Fn){.mod = p->mod,
                   .typ = _STR("Option_%.*s", typ.name.len, typ.name.str),
                   .name = main__js_dec_name(t),
                   .args = new_array(0, 1, sizeof(Var)),
                   .is_interface = 0,
                   .scope_level = 0,
                   .is_c = 0,
                   .receiver_typ = tos((byte *)"", 0),
                   .is_public = 0,
                   .is_method = 0,
                   .returns_error = 0,
                   .is_decl = 0,
                   .defer_text = new_array(0, 1, sizeof(string)),
                   .fn_name_token_idx = 0};

  if (Table_known_fn(&/* ? */ *p->table, dec_fn.name)) {

    return;
  };

  Var arg = (Var){.typ = tos3("cJSON*"),
                  .name = tos((byte *)"", 0),
                  .idx = 0,
                  .is_arg = 0,
                  .is_const = 0,
                  .args = new_array(0, 1, sizeof(Var)),
                  .attr = tos((byte *)"", 0),
                  .is_mut = 0,
                  .is_alloc = 0,
                  .is_returned = 0,
                  .ptr = 0,
                  .ref = 0,
                  .parent_fn = tos((byte *)"", 0),
                  .mod = tos((byte *)"", 0),
                  .is_global = 0,
                  .is_used = 0,
                  .is_changed = 0,
                  .scope_level = 0,
                  .is_c = 0,
                  .is_moved = 0,
                  .line_nr = 0,
                  .token_idx = 0};

  _PUSH(&dec_fn.args, (/*typ = array_Var   tmp_typ=Var*/ arg), tmp6, Var);

  Table_register_fn(p->table, dec_fn);

  Fn enc_fn = (Fn){.mod = p->mod,
                   .typ = tos3("cJSON*"),
                   .name = main__js_enc_name(t),
                   .args = new_array(0, 1, sizeof(Var)),
                   .is_interface = 0,
                   .scope_level = 0,
                   .is_c = 0,
                   .receiver_typ = tos((byte *)"", 0),
                   .is_public = 0,
                   .is_method = 0,
                   .returns_error = 0,
                   .is_decl = 0,
                   .defer_text = new_array(0, 1, sizeof(string)),
                   .fn_name_token_idx = 0};

  Var enc_arg = (Var){.typ = t,
                      .name = tos((byte *)"", 0),
                      .idx = 0,
                      .is_arg = 0,
                      .is_const = 0,
                      .args = new_array(0, 1, sizeof(Var)),
                      .attr = tos((byte *)"", 0),
                      .is_mut = 0,
                      .is_alloc = 0,
                      .is_returned = 0,
                      .ptr = 0,
                      .ref = 0,
                      .parent_fn = tos((byte *)"", 0),
                      .mod = tos((byte *)"", 0),
                      .is_global = 0,
                      .is_used = 0,
                      .is_changed = 0,
                      .scope_level = 0,
                      .is_c = 0,
                      .is_moved = 0,
                      .line_nr = 0,
                      .token_idx = 0};

  _PUSH(&enc_fn.args, (/*typ = array_Var   tmp_typ=Var*/ enc_arg), tmp9, Var);

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

  if (string_starts_with(t, tos3("array_"))) {

    dec = string_add(dec, Parser_decode_array(p, t));

    enc = string_add(enc, Parser_encode_array(&/* ? */ *p, t));
  };

  array_Var tmp10 = typ.fields;
  for (int tmp11 = 0; tmp11 < tmp10.len; tmp11++) {
    Var field = ((Var *)tmp10.data)[tmp11];

    if (string_eq(field.attr, tos3("skip"))) {

      continue;
    };

    string name = (string_starts_with(field.attr, tos3("json:")))
                      ? (string_right(field.attr, 5))
                      : (field.name);

    Type field_type = Table_find_type(&/* ? */ *p->table, field.typ);

    string _typ = string_replace(field.typ, tos3("*"), tos3(""));

    string enc_name = main__js_enc_name(_typ);

    if (string_eq(field.attr, tos3("raw"))) {

      dec = string_add(
          dec,
          string_add(_STR(" res->%.*s = tos2(cJSON_PrintUnformatted(",
                          field.name.len, field.name.str),
                     _STR("js_get(root, \"%.*s\")));\n", name.len, name.str)));

    } else {

      Parser_gen_json_for_type(p, field_type);

      string dec_name = main__js_dec_name(_typ);

      if (main__is_js_prim(_typ)) {

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
        tmp17, string);

  _PUSH(&p->cgen->fns,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/*enc start*/ %.*s return o;}", enc.len, enc.str)),
        tmp18, string);
}
bool main__is_js_prim(string typ) {

  return string_eq(typ, tos3("int")) || string_eq(typ, tos3("string")) ||
         string_eq(typ, tos3("bool")) || string_eq(typ, tos3("f32")) ||
         string_eq(typ, tos3("f64")) || string_eq(typ, tos3("i8")) ||
         string_eq(typ, tos3("i16")) || string_eq(typ, tos3("i64")) ||
         string_eq(typ, tos3("u16")) || string_eq(typ, tos3("u32")) ||
         string_eq(typ, tos3("u64"));
}
string Parser_decode_array(Parser *p, string array_type) {

  string typ = string_replace(array_type, tos3("array_"), tos3(""));

  Type t = Table_find_type(&/* ? */ *p->table, typ);

  string fn_name = main__js_dec_name(typ);

  Parser_gen_json_for_type(p, t);

  string s = tos3("");

  if (main__is_js_prim(typ)) {

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
string main__js_enc_name(string typ) {

  string name = _STR("json__jsencode_%.*s", typ.len, typ.str);

  return name;
}
string main__js_dec_name(string typ) {

  string name = _STR("json__jsdecode_%.*s", typ.len, typ.str);

  return name;
}
string Parser_encode_array(Parser *p, string array_type) {

  string typ = string_replace(array_type, tos3("array_"), tos3(""));

  string fn_name = main__js_enc_name(typ);

  return _STR(
      "\no = cJSON_CreateArray();\nfor (int i = 0; i < val.len; i++){\n  "
      "cJSON_AddItemToArray(o, %.*s(  ((%.*s*)val.data)[i]  ));\n}\n",
      fn_name.len, fn_name.str, typ.len, typ.str);
}
array_string V_generate_hotcode_reloading_compiler_flags(V *v) {

  array_string a = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (v->pref->is_live || v->pref->is_so) {

    if ((v->os == main__OS_linux || string_eq(os__user_os(), tos3("linux")))) {

      _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("-rdynamic")),
            tmp2, string);
    };

    if ((v->os == main__OS_mac || string_eq(os__user_os(), tos3("mac")))) {

      _PUSH(&a,
            (/*typ = array_string   tmp_typ=string*/ tos3("-flat_namespace")),
            tmp3, string);
    };
  };

  return a;
}
void V_generate_hotcode_reloading_declarations(V *v) {

  CGen *cgen = v->cgen;

  if (v->os != main__OS_windows && v->os != main__OS_msvc) {

    if (v->pref->is_so) {

      CGen_genln(cgen, tos3("pthread_mutex_t live_fn_mutex;"));
    };

    if (v->pref->is_live) {

      CGen_genln(
          cgen,
          tos3("pthread_mutex_t live_fn_mutex = PTHREAD_MUTEX_INITIALIZER;"));
    };

  } else {

    if (v->pref->is_so) {

      CGen_genln(cgen, tos3("HANDLE live_fn_mutex;"));
    };

    if (v->pref->is_live) {

      CGen_genln(cgen, tos3("HANDLE live_fn_mutex = 0;"));
    };
  };
}
void V_generate_hotcode_reloading_main_caller(V *v) {

  if (!v->pref->is_live) {

    return;
  };

  CGen *cgen = v->cgen;

  CGen_genln(cgen, tos3(""));

  string file_base = string_replace(os__filename(v->dir), tos3(".v"), tos3(""));

  if (!(v->os == main__OS_windows || v->os == main__OS_msvc)) {

    string so_name = string_add(file_base, tos3(".so"));

    CGen_genln(cgen, _STR("  char *live_library_name = \"%.*s\";", so_name.len,
                          so_name.str));

    CGen_genln(cgen, tos3("  load_so(live_library_name);"));

    CGen_genln(cgen, tos3("  pthread_t _thread_so;"));

    CGen_genln(cgen, tos3("  pthread_create(&_thread_so , NULL, &reload_so, "
                          "live_library_name);"));

  } else {

    string so_name = string_add(
        file_base, (v->os == main__OS_msvc) ? (tos3(".dll")) : (tos3(".so")));

    CGen_genln(cgen, _STR("  char *live_library_name = \"%.*s\";", so_name.len,
                          so_name.str));

    CGen_genln(cgen, tos3("  live_fn_mutex = CreateMutexA(0, 0, 0);"));

    CGen_genln(cgen, tos3("  load_so(live_library_name);"));

    CGen_genln(cgen, tos3("  unsigned long _thread_so;"));

    CGen_genln(cgen, tos3("  _thread_so = CreateThread(0, 0, "
                          "(LPTHREAD_START_ROUTINE)&reload_so, 0, 0, 0);"));
  };
}
void V_generate_hot_reload_code(V *v) {

  CGen *cgen = v->cgen;

  if (v->pref->is_live) {

    string file = os__realpath(v->dir);

    string file_base = string_replace(os__filename(file), tos3(".v"), tos3(""));

    string so_name = string_add(file_base, tos3(".so"));

    string vexe = (*(string *)array_get(os__args, 0));

    if (string_eq(os__user_os(), tos3("windows"))) {

      vexe = main__cescaped_path(vexe);

      file = main__cescaped_path(file);
    };

    string msvc = tos3("");

    if (v->os == main__OS_msvc) {

      msvc = tos3("-os msvc");
    };

    string debug = tos3("");

    if (v->pref->is_debug) {

      debug = tos3("-debug");
    };

    string cmd_compile_shared_library =
        _STR("%.*s %.*s %.*s -o %.*s -shared %.*s", vexe.len, vexe.str,
             msvc.len, msvc.str, debug.len, debug.str, file_base.len,
             file_base.str, file.len, file.str);

    if (v->pref->show_c_cmd) {

      println(cmd_compile_shared_library);
    };

    i64 ticks = time__ticks();

    os__system(cmd_compile_shared_library);

    i64 diff = time__ticks() - ticks;

    printf("compiling shared library took %lld ms\n", diff);

    println(tos3("=========\n"));

    CGen_genln(
        cgen, tos3("\n\nvoid lfnmutex_print(char *s){\n	if(0){\n	"
                   "	fflush(stderr);\n		fprintf(stderr,\">> "
                   "live_fn_mutex: %p | %s\\n\", &live_fn_mutex, s);\n	"
                   "	fflush(stderr);\n	}\n}\n"));

    if (v->os != main__OS_windows && v->os != main__OS_msvc) {

      CGen_genln(
          cgen,
          tos3(
              "\n#include <dlfcn.h>\nvoid* live_lib=0;\nint load_so(byteptr "
              "path) {\n	char cpath[1024];\n	"
              "sprintf(cpath,\"./%s\", path);\n	//printf(\"load_so %s\\n\", "
              "cpath);\n	if (live_lib) dlclose(live_lib);\n	"
              "live_lib = dlopen(cpath, RTLD_LAZY);\n	if (!live_lib) "
              "{\n		puts(\"open failed\");\n		"
              "exit(1);\n		return 0;\n	}\n"));

      array_string tmp21 = cgen->so_fns;
      for (int tmp22 = 0; tmp22 < tmp21.len; tmp22++) {
        string so_fn = ((string *)tmp21.data)[tmp22];

        CGen_genln(cgen, _STR("%.*s = dlsym(live_lib, \"%.*s\");  ", so_fn.len,
                              so_fn.str, so_fn.len, so_fn.str));
      };

    } else {

      CGen_genln(
          cgen,
          tos3("\nvoid* live_lib=0;\nint load_so(byteptr path) {\n	char "
               "cpath[1024];\n	sprintf(cpath, \"./%s\", path);\n	if "
               "(live_lib) FreeLibrary(live_lib);\n	live_lib = "
               "LoadLibraryA(cpath);\n	if (!live_lib) {\n		"
               "puts(\"open failed\");\n		exit(1);\n	"
               "	return 0;\n	}\n"));

      array_string tmp23 = cgen->so_fns;
      for (int tmp24 = 0; tmp24 < tmp23.len; tmp24++) {
        string so_fn = ((string *)tmp23.data)[tmp24];

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

    CGen_genln(cgen, tos3(" int load_so(byteptr path) { return 0; }"));
  };
}
void main__main() {

  array_string args = main__env_vflags_and_os_args();

  if (_IN(string, (tos3("-v")), args) ||
      _IN(string, (tos3("--version")), args) ||
      _IN(string, (tos3("version")), args)) {

    string version_hash = main__vhash();

    printf("V %.*s %.*s\n", main__Version.len, main__Version.str,
           version_hash.len, version_hash.str);

    return;
  };

  if (_IN(string, (tos3("-h")), args) || _IN(string, (tos3("--help")), args) ||
      _IN(string, (tos3("help")), args)) {

    println(main__HelpText);

    return;
  };

  if (_IN(string, (tos3("translate")), args)) {

    println(tos3("Translating C to V will be available in V 0.3"));

    return;
  };

  if (_IN(string, (tos3("up")), args)) {

    main__update_v();

    return;
  };

  if (_IN(string, (tos3("get")), args)) {

    println(tos3("use `v install` to install modules from vpm.vlang.io "));

    return;
  };

  if (_IN(string, (tos3("symlink")), args)) {

    main__create_symlink();

    return;
  };

  if (_IN(string, (tos3("install")), args)) {

    main__install_v(args);

    return;
  };

  if (_IN(string, (tos3("fmt")), args)) {

    main__vfmt(args);

    return;
  };

  if (_IN(string, (tos3("test")), args)) {

    main__test_v();

    return;
  };

  V *v = main__new_v(args);

  if (v->pref->is_verbose) {

    println(array_string_str(args));
  };

  if (_IN(string, (tos3("doc")), args)) {

    v_exit(0);
  };

  if (_IN(string, (tos3("run")), args)) {

    V_compile(v);

    V_run_compiled_executable_and_exit(*v);
  };

  if (args.len < 2 ||
      (args.len == 2 &&
       string_eq((*(string *)array_get(args, 1)), tos3("-"))) ||
      _IN(string, (tos3("runrepl")), args)) {

    main__run_repl();

    return;
  };

  benchmark__Benchmark tmark = benchmark__new_benchmark();

  V_compile(v);

  if (v->pref->is_stats) {

    benchmark__Benchmark_stop(&/* ? */ tmark);

    println(string_add(string_add(tos3("compilation took: "),
                                  i64_str(benchmark__Benchmark_total_duration(
                                      &/* ? */ tmark))),
                       tos3("ms")));
  };

  if (v->pref->is_test) {

    V_run_compiled_executable_and_exit(*v);
  };

  if (v->pref->autofree) {

    println(tos3("started freeing v struct"));

    v_map_free(&/* ? */ v->table->typesmap);

    v_map_free(&/* ? */ v->table->obf_ids);

    v_array_free(v->cgen->lines);

    v_free(v->cgen);

    map_Fn tmp7 = v->table->fns;
    array_string keys_tmp7 = map_keys(&tmp7);
    for (int l = 0; l < keys_tmp7.len; l++) {
      string _ = ((string *)keys_tmp7.data)[l];
      Fn f = {0};
      map_get(tmp7, _, &f);

      v_array_free(f.args);
    };

    v_map_free(&/* ? */ v->table->fns);

    v_free(v->table);

    println(tos3("done!"));
  };
}
void V_add_parser(V *v, Parser parser) {

  _PUSH(&v->parsers, (/*typ = array_Parser   tmp_typ=Parser*/ parser), tmp8,
        Parser);
}
Option_int V_get_file_parser_index(V *v, string file) {

  array_Parser tmp9 = v->parsers;
  for (int i = 0; i < tmp9.len; i++) {
    Parser p = ((Parser *)tmp9.data)[i];

    if (string_eq(os__realpath(p.file_path), os__realpath(file))) {

      int tmp10 = OPTION_CAST(int)(i);
      return opt_ok(&tmp10, sizeof(int));
    };
  };

  return v_error(_STR("parser for \"%.*s\" not found", file.len, file.str));
}
int V_parse(V *v, string file, Pass pass) {

  Option_int tmp11 = V_get_file_parser_index(&/* ? */ *v, file);
  if (!tmp11.ok) {
    string err = tmp11.error;

    Parser p = V_new_parser_from_file(v, file);

    Parser_parse(&/* ? */ p, pass);

    V_add_parser(v, p);

    return v->parsers.len - 1;
  }
  int pidx = *(int *)tmp11.data;
  ;

  Parser_parse(&/* ? */ (*(Parser *)array_get(v->parsers, pidx)), pass);

  return pidx;
}
void V_compile(V *v) {

  if (string_ne(os__user_os(), tos3("windows")) && v->os == main__OS_msvc) {

    main__verror(_STR("Cannot build with msvc on %.*s", os__user_os().len,
                      os__user_os().str));
  };

  CGen *cgen = v->cgen;

  CGen_genln(cgen, tos3("// Generated by V"));

  if (v->pref->is_verbose) {

    println(tos3("all .v files before:"));

    println(array_string_str(v->files));
  };

  V_add_v_files_to_compile(v);

  if (v->pref->is_verbose || v->pref->is_debug) {

    println(tos3("all .v files:"));

    println(array_string_str(v->files));
  };

  array_string tmp16 = v->files;
  for (int tmp17 = 0; tmp17 < tmp16.len; tmp17++) {
    string file = ((string *)tmp16.data)[tmp17];

    V_parse(v, file, main__Pass_decl);
  };

  cgen->pass = main__Pass_main;

  if (v->pref->is_debug) {

#ifdef _VJS

    CGen_genln(cgen, tos3("const VDEBUG = 1;\n"));

#else

    CGen_genln(cgen, tos3("#define VDEBUG (1)"));

#endif
    ;
  };

  if (v->os == main__OS_js) {

    CGen_genln(cgen, tos3("#define _VJS (1) "));
  };

  if (v->pref->building_v) {

    CGen_genln(cgen, tos3("#ifndef V_COMMIT_HASH"));

    CGen_genln(cgen, string_add(string_add(tos3("#define V_COMMIT_HASH \""),
                                           main__vhash()),
                                tos3("\"")));

    CGen_genln(cgen, tos3("#endif"));
  };

  bool q = cgen->nogen;

  cgen->nogen = 0;

#ifdef _VJS

  CGen_genln(cgen, main__js_headers);

#else

  CGen_genln(cgen, main__CommonCHeaders);

#endif
  ;

  V_generate_hotcode_reloading_declarations(&/* ? */ *v);

  bool imports_json = _IN(string, (tos3("json")), v->table->imports);

  if (v->pref->build_mode == main__BuildMode_default_mode) {

    if (imports_json) {

      CGen_genln(cgen, tos3("#include \"cJSON.h\""));
    };
  };

  if (v->pref->build_mode == main__BuildMode_default_mode) {

#ifndef _VJS

    CGen_genln(cgen, tos3("int g_test_oks = 0;"));

    CGen_genln(cgen, tos3("int g_test_fails = 0;"));

#endif
    ;

    if (imports_json) {

      CGen_genln(cgen,
                 tos3("\n#define js_get(object, key) "
                      "cJSON_GetObjectItemCaseSensitive((object), (key))\n"));
    };
  };

  if (_IN(string, (tos3("-debug_alloc")), os__args)) {

    CGen_genln(cgen, tos3("#define DEBUG_ALLOC 1"));
  };

  CGen_genln(cgen, tos3("this line will be replaced with definitions"));

  int defs_pos = cgen->lines.len - 1;

  if (defs_pos == -1) {

    defs_pos = 0;
  };

  cgen->nogen = q;

  array_string tmp21 = v->files;
  for (int tmp22 = 0; tmp22 < tmp21.len; tmp22++) {
    string file = ((string *)tmp21.data)[tmp22];

    V_parse(v, file, main__Pass_main);

    if (!v->pref->nofmt && !string_contains(file, tos3("/vlib/"))) {
    };
  };

  if (v->pref->build_mode == main__BuildMode_build_module) {

    V_generate_vh(&/* ? */ *v);
  };

  Parser vgen_parser = V_new_parser_from_string(
      v, strings__Builder_str(v->vgen_buf), tos3("vgen"));

  strings__Builder_free(&/* ? */ v->vgen_buf);

  Parser_parse(&/* ? */ vgen_parser, main__Pass_main);

  V_log(&/* ? */ *v, tos3("Done parsing."));

  strings__Builder def = strings__new_builder(10000);

#ifndef _VJS

  strings__Builder_writeln(&/* ? */ def,
                           array_string_join_lines(cgen->includes));

  strings__Builder_writeln(&/* ? */ def,
                           array_string_join_lines(cgen->typedefs));

  strings__Builder_writeln(&/* ? */ def, V_type_definitions(&/* ? */ *v));

  strings__Builder_writeln(&/* ? */ def,
                           tos3("\nstring _STR(const char*, ...);\n"));

  strings__Builder_writeln(&/* ? */ def,
                           tos3("\nstring _STR_TMP(const char*, ...);\n"));

  strings__Builder_writeln(&/* ? */ def, array_string_join_lines(cgen->fns));

#else

  strings__Builder_writeln(&/* ? */ def, V_type_definitions(&/* ? */ *v));

#endif
  ;

  strings__Builder_writeln(&/* ? */ def, array_string_join_lines(cgen->consts));

  strings__Builder_writeln(&/* ? */ def,
                           array_string_join_lines(cgen->thread_args));

  if (v->pref->is_prof) {

    strings__Builder_writeln(&/* ? */ def, tos3("; // Prof counters:"));

    strings__Builder_writeln(&/* ? */ def, V_prof_counters(&/* ? */ *v));
  };

  array_set(&/*q*/ cgen->lines, defs_pos,
            &(string[]){strings__Builder_str(def)});

  V_generate_main(v);

  V_generate_hot_reload_code(&/* ? */ *v);

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos3("flags="));

    array_CFlag tmp25 = V_get_os_cflags(&/* ? */ *v);
    for (int tmp26 = 0; tmp26 < tmp25.len; tmp26++) {
      CFlag flag = ((CFlag *)tmp25.data)[tmp26];

      println(string_add(tos3(" * "), CFlag_format(&/* ? */ flag)));
    };
  };

#ifdef _VJS

  CGen_genln(cgen, tos3("main__main();"));

#endif
  ;

  CGen_save(cgen);

  V_cc(v);
}
void V_generate_main(V *v) {

  CGen *cgen = v->cgen;

#ifdef _VJS

  return;

#endif
  ;

  int lines_so_far =
      string_count(array_string_join(cgen->lines, tos3("\n")), tos3("\n")) + 5;

  CGen_genln(cgen, tos3(""));

  CGen_genln(cgen,
             tos3("////////////////// Reset the file/line numbers //////////"));

  _PUSH(&cgen->lines,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "#line %d \"%.*s\"", lines_so_far,
            main__cescaped_path(os__realpath(cgen->out_path)).len,
            main__cescaped_path(os__realpath(cgen->out_path)).str)),
        tmp29, string);

  CGen_genln(cgen, tos3(""));

  if (v->pref->build_mode == main__BuildMode_default_mode) {

    string consts_init_body = array_string_join_lines(cgen->consts_init);

    CGen_genln(cgen,
               _STR("void init_consts() {\ng_str_buf=malloc(1000);\n%.*s\n}",
                    consts_init_body.len, consts_init_body.str));

    CGen_genln(
        cgen,
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

  if (v->pref->build_mode != main__BuildMode_build_module) {

    if (!Table_main_exists(&/* ? */ *v->table) && !v->pref->is_test) {

      if (v->pref->is_script) {

        V_gen_main_start(v, 1);

        CGen_genln(cgen, _STR("%.*s;", cgen->fn_main.len, cgen->fn_main.str));

        V_gen_main_end(v, tos3("return 0"));

      } else {

        main__verror(
            tos3("function `main` is not declared in the main module"));
      };

    } else if (v->pref->is_test) {

      if (Table_main_exists(&/* ? */ *v->table)) {

        main__verror(tos3("test files cannot have function `main`"));
      };

      if (!Table_has_at_least_one_test_fn(&/* ? */ *v->table)) {

        main__verror(
            tos3("test files need to have at least one test function"));
      };

      V_gen_main_start(v, 0);

      if (v->pref->is_stats) {

        CGen_genln(cgen, tos3("BenchedTests bt = main__start_testing();"));
      };

      map_Fn tmp31 = v->table->fns;
      array_string keys_tmp31 = map_keys(&tmp31);
      for (int l = 0; l < keys_tmp31.len; l++) {
        string _ = ((string *)keys_tmp31.data)[l];
        Fn f = {0};
        map_get(tmp31, _, &f);

        if (string_starts_with(f.name, tos3("main__test_"))) {

          if (v->pref->is_stats) {

            CGen_genln(
                cgen,
                _STR("BenchedTests_testing_step_start(&bt, tos3(\"%.*s\"));",
                     f.name.len, f.name.str));
          };

          CGen_genln(cgen, _STR("%.*s();", f.name.len, f.name.str));

          if (v->pref->is_stats) {

            CGen_genln(cgen, tos3("BenchedTests_testing_step_end(&bt);"));
          };
        };
      };

      if (v->pref->is_stats) {

        CGen_genln(cgen, tos3("BenchedTests_end_testing(&bt);"));
      };

      V_gen_main_end(v, tos3("return g_test_fails > 0"));

    } else if (Table_main_exists(&/* ? */ *v->table)) {

      V_gen_main_start(v, 1);

      CGen_genln(cgen, tos3("  main__main();"));

      V_gen_main_end(v, tos3("return 0"));
    };
  };
}
void V_gen_main_start(V *v, bool add_os_args) {

  CGen_genln(v->cgen, tos3("int main(int argc, char** argv) { "));

  CGen_genln(v->cgen, tos3("  init_consts();"));

  if (add_os_args && _IN(string, (tos3("os")), v->table->imports)) {

    CGen_genln(v->cgen,
               tos3("  os__args = os__init_os_args(argc, (byteptr*)argv);"));
  };

  V_generate_hotcode_reloading_main_caller(&/* ? */ *v);

  CGen_genln(v->cgen, tos3(""));
}
void V_gen_main_end(V *v, string return_statement) {

  CGen_genln(v->cgen, tos3(""));

  CGen_genln(v->cgen,
             _STR("  %.*s;", return_statement.len, return_statement.str));

  CGen_genln(v->cgen, tos3("}"));
}
string main__final_target_out_name(string out_name) {

  string cmd = (string_starts_with(out_name, tos3("/")))
                   ? (out_name)
                   : (string_add(tos3("./"), out_name));

#ifdef _WIN32

  cmd = out_name;

  cmd = string_replace(cmd, tos3("/"), tos3("\\"));

  cmd = string_add(cmd, tos3(".exe"));

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
      string_add(tos3("\""),
                 string_replace(main__final_target_out_name(v.out_name),
                                tos3(".exe"), tos3(""))),
      tos3("\""));

  if (os__args.len > 3) {

    cmd = string_add(
        cmd, string_add(tos3(" "), array_string_join(array_right(os__args, 3),
                                                     tos3(" "))));
  };

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
array_string V_v_files_from_dir(V *v, string dir) {

  array_string res = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (!os__file_exists(dir)) {

    main__verror(_STR("%.*s doesn\'t exist", dir.len, dir.str));

  } else if (!os__dir_exists(dir)) {

    main__verror(_STR("%.*s isn\'t a directory", dir.len, dir.str));
  };

  array_string files = os__ls(dir);

  if (v->pref->is_verbose) {

    printf("v_files_from_dir (\"%.*s\")\n", dir.len, dir.str);
  };

  array_string_sort(&/* ? */ files);

  array_string tmp38 = files;
  for (int tmp39 = 0; tmp39 < tmp38.len; tmp39++) {
    string file = ((string *)tmp38.data)[tmp39];

    if (!string_ends_with(file, tos3(".v")) &&
        !string_ends_with(file, tos3(".vh"))) {

      continue;
    };

    if (string_ends_with(file, tos3("_test.v"))) {

      continue;
    };

    if (string_ends_with(file, tos3("_win.v")) &&
        (v->os != main__OS_windows && v->os != main__OS_msvc)) {

      continue;
    };

    if (string_ends_with(file, tos3("_lin.v")) && v->os != main__OS_linux) {

      continue;
    };

    if (string_ends_with(file, tos3("_mac.v")) && v->os != main__OS_mac) {

      continue;
    };

    if (string_ends_with(file, tos3("_nix.v")) &&
        (v->os == main__OS_windows || v->os == main__OS_msvc)) {

      continue;
    };

    if (string_ends_with(file, tos3("_js.v")) && v->os != main__OS_js) {

      continue;
    };

    if (string_ends_with(file, tos3("_c.v")) && v->os == main__OS_js) {

      continue;
    };

    _PUSH(&res,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "%.*s%.*s%.*s", dir.len, dir.str, os__PathSeparator.len,
              os__PathSeparator.str, file.len, file.str)),
          tmp40, string);
  };

  return res;
}
void V_add_v_files_to_compile(V *v) {

  array_string builtin_files = V_get_builtin_files(&/* ? */ *v);

  string builtin_vh = _STR("%.*s/builtin.vh", main__v_modules_path.len,
                           main__v_modules_path.str);

  if (v->pref->is_debug && os__file_exists(builtin_vh)) {

    builtin_files = new_array_from_c_array(
        1, 1, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 1){builtin_vh});
  };

  array_string tmp43 = builtin_files;
  for (int tmp44 = 0; tmp44 < tmp43.len; tmp44++) {
    string file = ((string *)tmp43.data)[tmp44];

    _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ file), tmp45,
          string);

    Parser p = V_new_parser_from_file(v, file);

    Parser_parse(&/* ? */ p, main__Pass_imports);

    V_add_parser(v, p);
  };

  array_string tmp47 = V_get_user_files(&/* ? */ *v);
  for (int tmp48 = 0; tmp48 < tmp47.len; tmp48++) {
    string file = ((string *)tmp47.data)[tmp48];

    Parser p = V_new_parser_from_file(v, file);

    Parser_parse(&/* ? */ p, main__Pass_imports);

    V_add_parser(v, p);
  };

  V_parse_lib_imports(v);

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos3("imports:"));

    println(array_string_str(v->table->imports));
  };

  array_string imported_mods =
      DepGraph_imports(&/* ? */ *V_resolve_deps(&/* ? */ *v));

  array_string tmp51 = imported_mods;
  for (int tmp52 = 0; tmp52 < tmp51.len; tmp52++) {
    string mod = ((string *)tmp51.data)[tmp52];

    if (string_eq(mod, tos3("builtin")) || string_eq(mod, tos3("main"))) {

      continue;
    };

    if (v->pref->build_mode != main__BuildMode_build_module) {

      string vh_path = _STR("%.*s/%.*s.vh", main__v_modules_path.len,
                            main__v_modules_path.str, mod.len, mod.str);

      if (v->pref->is_debug && os__file_exists(vh_path)) {

        printf("using cached module `%.*s`: %.*s\n", mod.len, mod.str,
               vh_path.len, vh_path.str);

        _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ vh_path),
              tmp54, string);

        continue;
      };
    };

    Option_string tmp55 = V_find_module_path(&/* ? */ *v, mod);
    if (!tmp55.ok) {
      string err = tmp55.error;

      main__verror(err);

      break;
    }
    string mod_path = *(string *)tmp55.data;
    ;

    array_string vfiles = V_v_files_from_dir(&/* ? */ *v, mod_path);

    array_string tmp57 = vfiles;
    for (int tmp58 = 0; tmp58 < tmp57.len; tmp58++) {
      string file = ((string *)tmp57.data)[tmp58];

      _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ file), tmp59,
            string);
    };
  };

  map_FileImportTable tmp60 = v->table->file_imports;
  array_string keys_tmp60 = map_keys(&tmp60);
  for (int l = 0; l < keys_tmp60.len; l++) {
    string _ = ((string *)keys_tmp60.data)[l];
    FileImportTable fit = {0};
    map_get(tmp60, _, &fit);

    if (string_ne(fit.module_name, tos3("main"))) {

      continue;
    };

    _PUSH(&v->files, (/*typ = array_string   tmp_typ=string*/ fit.file_path),
          tmp61, string);
  };
}
array_string V_get_builtin_files(V *v) {

#ifdef _VJS

  return V_v_files_from_dir(&/* ? */ *v,
                            _STR("%.*s%.*svlib%.*sbuiltin%.*sjs", v->vroot.len,
                                 v->vroot.str, os__PathSeparator.len,
                                 os__PathSeparator.str, os__PathSeparator.len,
                                 os__PathSeparator.str, os__PathSeparator.len,
                                 os__PathSeparator.str));

#endif
  ;

  return V_v_files_from_dir(
      &/* ? */ *v, _STR("%.*s%.*svlib%.*sbuiltin", v->vroot.len, v->vroot.str,
                        os__PathSeparator.len, os__PathSeparator.str,
                        os__PathSeparator.len, os__PathSeparator.str));
}
array_string V_get_user_files(V *v) {

  string dir = v->dir;

  V_log(&/* ? */ *v, _STR("get_v_files(%.*s)", dir.len, dir.str));

  array_string user_files = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (v->pref->is_test && v->pref->is_stats) {

    _PUSH(&user_files,
          (/*typ = array_string   tmp_typ=string*/ array_string_join(
              new_array_from_c_array(5, 5, sizeof(string),
                                     EMPTY_ARRAY_OF_ELEMS(string, 5){
                                         v->vroot, tos3("vlib"),
                                         tos3("benchmark"), tos3("tests"),
                                         tos3("always_imported.v")}),
              os__PathSeparator)),
          tmp64, string);
  };

  bool is_test_with_imports =
      string_ends_with(dir, tos3("_test.v")) &&
      (string_contains(dir, _STR("%.*svolt", os__PathSeparator.len,
                                 os__PathSeparator.str)) ||
       string_contains(dir, _STR("%.*sc2volt", os__PathSeparator.len,
                                 os__PathSeparator.str)));

  if (is_test_with_imports) {

    _PUSH(&user_files, (/*typ = array_string   tmp_typ=string*/ dir), tmp66,
          string);

    int pos = string_last_index(dir, os__PathSeparator);

    dir = string_add(string_left(dir, pos), os__PathSeparator);
  };

  if (string_ends_with(dir, tos3(".v"))) {

    _PUSH(&user_files, (/*typ = array_string   tmp_typ=string*/ dir), tmp68,
          string);

    dir = string_all_before(
        dir, _STR("%.*s", os__PathSeparator.len, os__PathSeparator.str));

  } else {

    array_string files = V_v_files_from_dir(&/* ? */ *v, dir);

    array_string tmp70 = files;
    for (int tmp71 = 0; tmp71 < tmp70.len; tmp71++) {
      string file = ((string *)tmp70.data)[tmp71];

      _PUSH(&user_files, (/*typ = array_string   tmp_typ=string*/ file), tmp72,
            string);
    };
  };

  if (user_files.len == 0) {

    println(tos3("No input .v files"));

    v_exit(1);
  };

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos3("user_files:"));

    println(array_string_str(user_files));
  };

  return user_files;
}
void V_parse_lib_imports(V *v) {

  array_string done_fits = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string done_imports = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (1) {

    map_FileImportTable tmp75 = v->table->file_imports;
    array_string keys_tmp75 = map_keys(&tmp75);
    for (int l = 0; l < keys_tmp75.len; l++) {
      string _ = ((string *)keys_tmp75.data)[l];
      FileImportTable fit = {0};
      map_get(tmp75, _, &fit);

      if (_IN(string, (fit.file_path), done_fits)) {

        continue;
      };

      map_string tmp76 = fit.imports;
      array_string keys_tmp76 = map_keys(&tmp76);
      for (int l = 0; l < keys_tmp76.len; l++) {
        string _ = ((string *)keys_tmp76.data)[l];
        string mod = {0};
        map_get(tmp76, _, &mod);

        Option_string tmp77 = V_find_module_path(&/* ? */ *v, mod);
        if (!tmp77.ok) {
          string err = tmp77.error;

          Option_int tmp78 =
              V_get_file_parser_index(&/* ? */ *v, fit.file_path);
          if (!tmp78.ok) {
            string err = tmp78.error;

            main__verror(err);

            break;
          }
          int pidx = *(int *)tmp78.data;
          ;

          Parser_error_with_token_index(
              &/* ? */ (*(Parser *)array_get(v->parsers, pidx)),
              _STR("cannot import module \"%.*s\" (not found)", mod.len,
                   mod.str),
              FileImportTable_get_import_tok_idx(&/* ? */ fit, mod));

          break;
        }
        string import_path = *(string *)tmp77.data;
        ;

        array_string vfiles = V_v_files_from_dir(&/* ? */ *v, import_path);

        if (vfiles.len == 0) {

          Option_int tmp82 =
              V_get_file_parser_index(&/* ? */ *v, fit.file_path);
          if (!tmp82.ok) {
            string err = tmp82.error;

            main__verror(err);

            break;
          }
          int pidx = *(int *)tmp82.data;
          ;

          Parser_error_with_token_index(
              &/* ? */ (*(Parser *)array_get(v->parsers, pidx)),
              _STR("cannot import module \"%.*s\" (no .v files in \"%.*s\")",
                   mod.len, mod.str, import_path.len, import_path.str),
              FileImportTable_get_import_tok_idx(&/* ? */ fit, mod));
        };

        array_string tmp85 = vfiles;
        for (int tmp86 = 0; tmp86 < tmp85.len; tmp86++) {
          string file = ((string *)tmp85.data)[tmp86];

          if (_IN(string, (file), done_imports)) {

            continue;
          };

          int pid = V_parse(v, file, main__Pass_imports);

          _PUSH(&done_imports, (/*typ = array_string   tmp_typ=string*/ file),
                tmp88, string);

          string p_mod =
              (*(Parser *)array_get(v->parsers, pid)).import_table.module_name;

          if (string_ne(p_mod, mod)) {

            Parser_error_with_token_index(
                &/* ? */ (*(Parser *)array_get(v->parsers, pid)),
                _STR("bad module definition: %.*s imports module \"%.*s\" but "
                     "%.*s is defined as module `%.*s`",
                     fit.file_path.len, fit.file_path.str, mod.len, mod.str,
                     file.len, file.str, p_mod.len, p_mod.str),
                1);
          };
        };
      };

      _PUSH(&done_fits, (/*typ = array_string   tmp_typ=string*/ fit.file_path),
            tmp94, string);
    };

    if (v->table->file_imports.size == done_fits.len) {

      break;
    };
  };
}
DepGraph *V_resolve_deps(V *v) {

  DepGraph *dep_graph = main__new_dep_graph();

  DepGraph_from_import_tables(dep_graph, v->table->file_imports);

  DepGraph *deps_resolved = DepGraph_resolve(&/* ? */ *dep_graph);

  if (!deps_resolved->acyclic) {

    DepGraph_display(&/* ? */ *deps_resolved);

    main__verror(tos3("import cycle detected"));
  };

  return deps_resolved;
}
string main__get_arg(string joined_args, string arg, string def) {

  return main__get_param_after(joined_args, _STR("-%.*s", arg.len, arg.str),
                               def);
}
string main__get_param_after(string joined_args, string arg, string def) {

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

  string res = string_substr(joined_args, pos, space);

  return res;
}
void V_log(V *v, string s) {

  if (!v->pref->is_verbose) {

    return;
  };

  println(s);
}
V *main__new_v(array_string args) {

  strings__Builder vgen_buf = strings__new_builder(1000);

  strings__Builder_writeln(&/* ? */ vgen_buf,
                           tos3("module main\nimport strings"));

  string joined_args = array_string_join(args, tos3(" "));

  string target_os = main__get_arg(joined_args, tos3("os"), tos3(""));

  string out_name = main__get_arg(joined_args, tos3("o"), tos3("a.out"));

  string dir = *(string *)array_last(args);

  if (_IN(string, (tos3("run")), args)) {

    dir = main__get_param_after(joined_args, tos3("run"), tos3(""));
  };

  if (string_ends_with(dir, os__PathSeparator)) {

    dir = string_all_before_last(dir, os__PathSeparator);
  };

  string adir = os__realpath(dir);

  if (args.len < 2) {

    dir = tos3("");
  };

  BuildMode build_mode = main__BuildMode_default_mode;

  string mod = tos3("");

  if (string_contains(joined_args, tos3("build module "))) {

    build_mode = main__BuildMode_build_module;

    mod = (string_contains(adir, os__PathSeparator))
              ? (string_all_after(adir, os__PathSeparator))
              : (adir);

    printf("Building module \"%.*s\" (dir=\"%.*s\")...\n", mod.len, mod.str,
           dir.len, dir.str);

    out_name = string_add(mod, tos3(".o"));

    printf("%.*s\n", out_name.len, out_name.str);
  };

  bool is_test = string_ends_with(dir, tos3("_test.v"));

  bool is_script = string_ends_with(dir, tos3(".v"));

  if (is_script && !os__file_exists(dir)) {

    printf("`%.*s` does not exist\n", dir.len, dir.str);

    v_exit(1);
  };

  if (string_eq(out_name, tos3("a.out")) && string_ends_with(dir, tos3(".v"))) {

    out_name = string_left(dir, dir.len - 2);
  };

  if (string_eq(dir, tos3(".")) && string_eq(out_name, tos3("a.out"))) {

    string base = string_all_after(os__getwd(), os__PathSeparator);

    out_name = string_trim_space(base);
  };

  OS _os = main__OS_mac;

  if (string_eq(target_os, tos3(""))) {

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

#ifdef __sun

    _os = main__OS_solaris;

#endif
    ;

  } else {

    if (string_eq(target_os, tos3("linux"))) { /* case */

      _os = main__OS_linux;

    } else if (string_eq(target_os, tos3("windows"))) { /* case */

      _os = main__OS_windows;

    } else if (string_eq(target_os, tos3("mac"))) { /* case */

      _os = main__OS_mac;

    } else if (string_eq(target_os, tos3("freebsd"))) { /* case */

      _os = main__OS_freebsd;

    } else if (string_eq(target_os, tos3("openbsd"))) { /* case */

      _os = main__OS_openbsd;

    } else if (string_eq(target_os, tos3("netbsd"))) { /* case */

      _os = main__OS_netbsd;

    } else if (string_eq(target_os, tos3("dragonfly"))) { /* case */

      _os = main__OS_dragonfly;

    } else if (string_eq(target_os, tos3("msvc"))) { /* case */

      _os = main__OS_msvc;

    } else if (string_eq(target_os, tos3("js"))) { /* case */

      _os = main__OS_js;

    } else if (string_eq(target_os, tos3("solaris"))) { /* case */

      _os = main__OS_solaris;
    };
  };

  string vroot = os__dir(os__executable());

  if (!os__dir_exists(vroot) ||
      !os__dir_exists(string_add(vroot, tos3("/vlib/builtin")))) {

    println(tos3("vlib not found, downloading it..."));

    println(tos3("vlib not found. It should be next to the V executable. "));

    println(tos3("Go to https://vlang.io to install V."));

    v_exit(1);
  };

  string out_name_c =
      os__realpath(_STR("%.*s.tmp.c", out_name.len, out_name.str));

  string cflags = main__get_cmdline_cflags(args);

  string rdir = os__realpath(dir);

  string rdir_name = os__filename(rdir);

  bool obfuscate = _IN(string, (tos3("-obf")), args);

  bool is_repl = _IN(string, (tos3("-repl")), args);

  Preferences *pref = (Preferences *)memdup(
      &(Preferences){.is_test = is_test,
                     .is_script = is_script,
                     .is_so = _IN(string, (tos3("-shared")), args),
                     .is_prod = _IN(string, (tos3("-prod")), args),
                     .is_verbose = _IN(string, (tos3("-verbose")), args) ||
                                   _IN(string, (tos3("--verbose")), args),
                     .is_debuggable = _IN(string, (tos3("-g")), args),
                     .is_debug = _IN(string, (tos3("-debug")), args) ||
                                 _IN(string, (tos3("-g")), args),
                     .is_stats = _IN(string, (tos3("-stats")), args),
                     .obfuscate = obfuscate,
                     .is_prof = _IN(string, (tos3("-prof")), args),
                     .is_live = _IN(string, (tos3("-live")), args),
                     .sanitize = _IN(string, (tos3("-sanitize")), args),
                     .nofmt = _IN(string, (tos3("-nofmt")), args),
                     .show_c_cmd = _IN(string, (tos3("-show_c_cmd")), args),
                     .translated = _IN(string, (tos3("translated")), args),
                     .is_run = _IN(string, (tos3("run")), args),
                     .autofree = _IN(string, (tos3("-autofree")), args),
                     .compress = _IN(string, (tos3("-compress")), args),
                     .is_repl = is_repl,
                     .build_mode = build_mode,
                     .cflags = cflags,
                     .ccompiler = main__find_c_compiler(),
                     .building_v =
                         !is_repl && (string_eq(rdir_name, tos3("compiler")) ||
                                      string_contains(dir, tos3("vlib"))),
                     .no_auto_free = 0,
                     .skip_builtin = 0},
      sizeof(Preferences));

  if (pref->is_verbose || pref->is_debug) {

    printf("C compiler=%.*s\n", pref->ccompiler.len, pref->ccompiler.str);
  };

  if (pref->is_so) {

    out_name_c = string_add(string_all_after(out_name, os__PathSeparator),
                            tos3("_shared_lib.c"));
  };

  return (V *)memdup(
      &(V){
          .os = _os,
          .out_name = out_name,
          .dir = dir,
          .lang_dir = vroot,
          .table = main__new_table(obfuscate),
          .out_name_c = out_name_c,
          .cgen = main__new_cgen(out_name_c),
          .vroot = vroot,
          .pref = pref,
          .mod = mod,
          .vgen_buf = vgen_buf,
          .files = new_array(0, 1, sizeof(string)),
          .parsers = new_array(0, 1, sizeof(Parser)),
      },
      sizeof(V));
}
array_string main__env_vflags_and_os_args() {

  array_string args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  string vflags = os__getenv(tos3("VFLAGS"));

  if (string_ne(tos3(""), vflags)) {

    _PUSH(&args,
          (/*typ = array_string   tmp_typ=string*/ (
              *(string *)array_get(os__args, 0))),
          tmp123, string);

    _PUSH_MANY(&args,
               (/*typ = array_string   tmp_typ=string*/ string_split(
                   vflags, tos3(" "))),
               tmp126, array_string);

    if (os__args.len > 1) {

      _PUSH_MANY(
          &args,
          (/*typ = array_string   tmp_typ=string*/ array_right(os__args, 1)),
          tmp127, array_string);
    };

  } else {

    _PUSH_MANY(&args, (/*typ = array_string   tmp_typ=string*/ os__args),
               tmp128, array_string);
  };

  return args;
}
void main__update_v() {

  println(tos3("Updating V..."));

  string vroot = os__dir(os__executable());

  Option_os__Result tmp130 = os__exec(_STR(
      "git -C \"%.*s\" pull --rebase origin master", vroot.len, vroot.str));
  if (!tmp130.ok) {
    string err = tmp130.error;

    main__verror(err);

    return;
  }
  os__Result s = *(os__Result *)tmp130.data;
  ;

  println(s.output);

#ifdef _WIN32

  string v_backup_file = _STR("%.*s/v_old.exe", vroot.len, vroot.str);

  if (os__file_exists(v_backup_file)) {

    os__rm(v_backup_file);
  };

  os__mv(_STR("%.*s/v.exe", vroot.len, vroot.str), v_backup_file);

  Option_os__Result tmp132 =
      os__exec(_STR("\"%.*s/make.bat\"", vroot.len, vroot.str));
  if (!tmp132.ok) {
    string err = tmp132.error;

    main__verror(err);

    return;
  }
  os__Result s2 = *(os__Result *)tmp132.data;
  ;

  println(s2.output);

#else

  Option_os__Result tmp133 =
      os__exec(_STR("make -C \"%.*s\"", vroot.len, vroot.str));
  if (!tmp133.ok) {
    string err = tmp133.error;

    main__verror(err);

    return;
  }
  os__Result s2 = *(os__Result *)tmp133.data;
  ;

  println(s2.output);

#endif
  ;
}
void main__vfmt(array_string args) {

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
void main__install_v(array_string args) {

  if (args.len < 3) {

    println(tos3("usage: v install [module] [module] [...]"));

    return;
  };

  array_string names = array_slice(args, 2, args.len);

  string vexec = os__executable();

  string vroot = os__dir(vexec);

  string vget = _STR("%.*s/tools/vget", vroot.len, vroot.str);

  if (1) {

    os__chdir(string_add(vroot, tos3("/tools")));

    Option_os__Result tmp139 = os__exec(
        _STR("%.*s -o %.*s vget.v", vexec.len, vexec.str, vget.len, vget.str));
    if (!tmp139.ok) {
      string err = tmp139.error;

      main__verror(err);

      return;
    }
    os__Result vget_compilation = *(os__Result *)tmp139.data;
    ;

    if (vget_compilation.exit_code != 0) {

      main__verror(vget_compilation.output);

      return;
    };
  };

  Option_os__Result tmp140 = os__exec(string_add(
      _STR("%.*s ", vget.len, vget.str), array_string_join(names, tos3(" "))));
  if (!tmp140.ok) {
    string err = tmp140.error;

    main__verror(err);

    return;
  }
  os__Result vgetresult = *(os__Result *)tmp140.data;
  ;

  if (vgetresult.exit_code != 0) {

    main__verror(vgetresult.output);

    return;
  };
}
void main__create_symlink() {

  string vexe = os__executable();

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
void main__verror(string s) {

  printf("V error: %.*s\n", s.len, s.str);

  os__flush_stdout();

  v_exit(1);
}
string main__vhash() {

  byte buf[50] = {0};

  buf[0] /*rbyte 1*/ = 0;

  snprintf(((char *)(buf)), 50, "%s", V_COMMIT_HASH);

  return tos_clone(buf);
}
string main__cescaped_path(string s) {

  return string_replace(s, tos3("\\"), tos3("\\\\"));
}
string Fn_v_definition(Fn *f) {

  strings__Builder sb = strings__new_builder(100);

  if (f->is_public) {

    strings__Builder_write(&/* ? */ sb, tos3("pub "));
  };

  strings__Builder_write(&/* ? */ sb, tos3("fn "));

  if (f->is_c) {

    strings__Builder_write(&/* ? */ sb, tos3("C."));
  };

  if (f->is_method) {

    Var recv = (*(Var *)array_get(f->args, 0));

    string typ =
        string_replace(main__v_type_str(recv.typ), tos3("*"), tos3(""));

    string mu = (recv.is_mut) ? (tos3("mut")) : (tos3(""));

    if (recv.ref) {

      mu = tos3("&");
    };

    strings__Builder_write(&/* ? */ sb, _STR("(%.*s %.*s %.*s) ", recv.name.len,
                                             recv.name.str, mu.len, mu.str,
                                             typ.len, typ.str));
  };

  if (string_contains(f->name, tos3("__"))) {

    strings__Builder_write(
        &/* ? */ sb,
        string_add(string_all_after(f->name, tos3("__")), tos3("(")));

  } else {

    strings__Builder_write(&/* ? */ sb,
                           _STR("%.*s(", f->name.len, f->name.str));
  };

  array_Var tmp7 = f->args;
  for (int i = 0; i < tmp7.len; i++) {
    Var arg = ((Var *)tmp7.data)[i];

    if (i == 0 && f->is_method) {

      continue;
    };

    string typ =
        string_replace(main__v_type_str(arg.typ), tos3("*"), tos3("&"));

    if (string_eq(arg.name, tos3(""))) {

      strings__Builder_write(&/* ? */ sb, typ);

    } else {

      strings__Builder_write(&/* ? */ sb, _STR("%.*s %.*s", arg.name.len,
                                               arg.name.str, typ.len, typ.str));
    };

    if (i != f->args.len - 1) {

      strings__Builder_write(&/* ? */ sb, tos3(", "));
    };
  };

  strings__Builder_write(&/* ? */ sb, tos3(")"));

  if (string_ne(f->typ, tos3("void"))) {

    string typ = string_replace(main__v_type_str(f->typ), tos3("*"), tos3("&"));

    strings__Builder_write(&/* ? */ sb, tos3(" "));

    strings__Builder_write(&/* ? */ sb, typ);

    strings__Builder_writeln(&/* ? */ sb, tos3(" "));
  };

  return strings__Builder_str(sb);
}
string main__v_type_str(string typ_) {

  string typ = (string_ends_with(typ_, tos3("*")))
                   ? (string_add(tos3("*"), string_left(typ_, typ_.len - 1)))
                   : (typ_);

  typ = string_replace(typ, tos3("Option_"), tos3("?"));

  if (string_contains(typ, tos3("_V_MulRet"))) {

    array_string words = string_split(
        string_replace(typ, tos3("_V_MulRet_"), tos3("")), tos3("_V_"));

    typ = tos3("(");

    int tmp12 = 0;
    ;
    for (int tmp13 = tmp12; tmp13 < words.len; tmp13++) {
      int i = tmp13;

      typ = string_add(typ, (*(string *)array_get(words, i)));

      if (i != words.len - 1) {

        typ = string_add(typ, tos3(","));
      };
    };

    typ = string_add(typ, tos3(")"));

    return typ;
  };

  if (string_eq(typ, tos3("*void"))) {

    return tos3("voidptr");
  };

  if (string_eq(typ, tos3("*byte"))) {

    return tos3("byteptr");
  };

  if (string_starts_with(typ, tos3("array_"))) {

    return string_add(tos3("[]"), string_right(typ, 6));
  };

  if (string_contains(typ, tos3("__"))) {

    bool opt = string_starts_with(typ, tos3("?"));

    typ = string_all_after(typ, tos3("__"));

    if (opt) {

      typ = string_add(tos3("?"), typ);
    };
  };

  return typ;
}
void V_generate_vh(V *v) {

  printf("\n\n\n\nGenerating a V header file for module `%.*s`\n", v->mod.len,
         v->mod.str);

  string dir = _STR("%.*s%.*s%.*s", main__v_modules_path.len,
                    main__v_modules_path.str, os__PathSeparator.len,
                    os__PathSeparator.str, v->mod.len, v->mod.str);

  string path = string_add(dir, tos3(".vh"));

  if (!os__dir_exists(dir)) {

    os__mkdir(dir);
  };

  println(path);

  Option_os__File tmp19 = os__create(path);
  if (!tmp19.ok) {
    string err = tmp19.error;

    v_panic(err);
  }
  os__File file = *(os__File *)tmp19.data;
  ;

  os__File_writeln(file,
                   _STR("// %.*s module header \n", v->mod.len, v->mod.str));

  os__File_writeln(file, _STR("module %.*s", v->mod.len, v->mod.str));

  os__File_writeln(file, tos3("// Consts"));

  if (v->table->consts.len > 0) {

    os__File_writeln(file, tos3("const ("));

    array_Var tmp20 = v->table->consts;
    for (int i = 0; i < tmp20.len; i++) {
      Var c = ((Var *)tmp20.data)[i];

      if (string_ne(c.mod, v->mod)) {

        continue;
      };

      printf("%d %.*s\n", i, c.name.len, c.name.str);

      string name = string_all_after(c.name, tos3("__"));

      string typ = main__v_type_str(c.typ);

      os__File_writeln(
          file, _STR("\t%.*s %.*s", name.len, name.str, typ.len, typ.str));
    };

    os__File_writeln(file, tos3(")\n"));

    array_Var tmp23 = v->table->consts;
    for (int tmp24 = 0; tmp24 < tmp23.len; tmp24++) {
      Var var = ((Var *)tmp23.data)[tmp24];

      if (string_ne(var.mod, v->mod)) {

        continue;
      };

      if (!var.is_global) {

        continue;
      };

      string name = string_all_after(var.name, tos3("__"));

      string typ = main__v_type_str(var.typ);

      os__File_writeln(file, _STR("__global %.*s %.*s", name.len, name.str,
                                  typ.len, typ.str));
    };

    os__File_writeln(file, tos3("\n"));
  };

  os__File_writeln(file, tos3("// Types"));

  map_Type tmp27 = v->table->typesmap;
  array_string keys_tmp27 = map_keys(&tmp27);
  for (int l = 0; l < keys_tmp27.len; l++) {
    string _ = ((string *)keys_tmp27.data)[l];
    Type typ = {0};
    map_get(tmp27, _, &typ);

    if (string_ne(typ.mod, v->mod) && string_ne(typ.mod, tos3(""))) {

      continue;
    };

    if (string_contains(typ.name, tos3("_V_MulRet"))) {

      continue;
    };

    string name = typ.name;

    if (string_contains(typ.name, tos3("__"))) {

      name = string_all_after(typ.name, tos3("__"));
    };

    if (typ.cat == main__TypeCategory_struct_ ||
        typ.cat == main__TypeCategory_c_struct) {

      string c = (typ.is_c) ? (tos3("C.")) : (tos3(""));

      os__File_writeln(
          file, _STR("struct %.*s%.*s {", c.len, c.str, name.len, name.str));

      array_Var tmp30 = typ.fields;
      for (int tmp31 = 0; tmp31 < tmp30.len; tmp31++) {
        Var field = ((Var *)tmp30.data)[tmp31];

        if (field.access_mod == main__AccessMod_public) {

          continue;
        };

        string field_type =
            string_replace(main__v_type_str(field.typ), tos3("*"), tos3("&"));

        os__File_writeln(file,
                         _STR("\t%.*s %.*s", field.name.len, field.name.str,
                              field_type.len, field_type.str));
      };

      string public_str = tos3("");

      array_Var tmp34 = typ.fields;
      for (int tmp35 = 0; tmp35 < tmp34.len; tmp35++) {
        Var field = ((Var *)tmp34.data)[tmp35];

        if (field.access_mod == main__AccessMod_private) {

          continue;
        };

        string field_type =
            string_replace(main__v_type_str(field.typ), tos3("*"), tos3("&"));

        public_str = string_add(
            public_str, _STR("\t%.*s %.*s\n", field.name.len, field.name.str,
                             field_type.len, field_type.str));
      };

      if (string_ne(public_str, tos3(""))) {

        os__File_writeln(file, string_add(tos3("pub:"), public_str));
      };

      os__File_writeln(file, tos3("}\n"));
    };
  };

  os__File_writeln(file, tos3("// Functions"));

  array_Fn fns = new_array_from_c_array(
      0, 0, sizeof(Fn), EMPTY_ARRAY_OF_ELEMS(Fn, 0){TCCSKIP(0)});

  map_Fn tmp38 = v->table->fns;
  array_string keys_tmp38 = map_keys(&tmp38);
  for (int l = 0; l < keys_tmp38.len; l++) {
    string _ = ((string *)keys_tmp38.data)[l];
    Fn f = {0};
    map_get(tmp38, _, &f);

    if (string_eq(f.mod, v->mod) || string_eq(f.mod, tos3(""))) {

      _PUSH(&fns, (/*typ = array_Fn   tmp_typ=Fn*/ f), tmp39, Fn);

    } else {
    };
  };

  array_Fn tmp40 = fns;
  for (int _ = 0; _ < tmp40.len; _++) {
    Fn f = ((Fn *)tmp40.data)[_];

    if (!f.is_public) {

      continue;
    };

    os__File_writeln(file, Fn_v_definition(&/* ? */ f));
  };

  array_Fn tmp41 = fns;
  for (int _ = 0; _ < tmp41.len; _++) {
    Fn f = ((Fn *)tmp41.data)[_];

    if (f.is_public) {

      continue;
    };

    os__File_writeln(file, Fn_v_definition(&/* ? */ f));
  };

  os__File_writeln(file, tos3("\n// Methods //////////////////"));

  map_Type tmp42 = v->table->typesmap;
  array_string keys_tmp42 = map_keys(&tmp42);
  for (int l = 0; l < keys_tmp42.len; l++) {
    string _ = ((string *)keys_tmp42.data)[l];
    Type typ = {0};
    map_get(tmp42, _, &typ);

    if (string_ne(typ.mod, v->mod) &&
        !(string_eq(v->mod, tos3("builtin")) && string_eq(typ.mod, tos3("")))) {

      printf("skipping method typ %.*s mod=%.*s\n", typ.name.len, typ.name.str,
             typ.mod.len, typ.mod.str);

      continue;
    };

    array_Fn tmp43 = typ.methods;
    for (int tmp44 = 0; tmp44 < tmp43.len; tmp44++) {
      Fn method = ((Fn *)tmp43.data)[tmp44];

      os__File_writeln(file, Fn_v_definition(&/* ? */ method));
    };
  };

  os__File_close(file);
}
void DepGraph_from_import_tables(DepGraph *graph,
                                 map_FileImportTable import_tables) {

  map_FileImportTable tmp1 = import_tables;
  array_string keys_tmp1 = map_keys(&tmp1);
  for (int l = 0; l < keys_tmp1.len; l++) {
    string _ = ((string *)keys_tmp1.data)[l];
    FileImportTable fit = {0};
    map_get(tmp1, _, &fit);

    array_string deps = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    map_string tmp3 = fit.imports;
    array_string keys_tmp3 = map_keys(&tmp3);
    for (int l = 0; l < keys_tmp3.len; l++) {
      string _ = ((string *)keys_tmp3.data)[l];
      string m = {0};
      map_get(tmp3, _, &m);

      _PUSH(&deps, (/*typ = array_string   tmp_typ=string*/ m), tmp4, string);
    };

    DepGraph_add(graph, fit.module_name, deps);
  };
}
array_string DepGraph_imports(DepGraph *graph) {

  array_string mods = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_DepGraphNode tmp6 = graph->nodes;
  for (int tmp7 = 0; tmp7 < tmp6.len; tmp7++) {
    DepGraphNode node = ((DepGraphNode *)tmp6.data)[tmp7];

    _PUSH(&mods, (/*typ = array_string   tmp_typ=string*/ node.name), tmp8,
          string);
  };

  return mods;
}
string V_module_path(V *v, string mod) {

  if (string_contains(mod, tos3("."))) {

    return string_replace(mod, tos3("."), os__PathSeparator);
  };

  return mod;
}
Option_string V_find_module_path(V *v, string mod) {

  string mod_path = V_module_path(&/* ? */ *v, mod);

  string import_path = string_add(
      os__getwd(), _STR("%.*s%.*s", os__PathSeparator.len,
                        os__PathSeparator.str, mod_path.len, mod_path.str));

  if (!os__dir_exists(import_path)) {

    import_path = _STR("%.*s%.*svlib%.*s%.*s", v->lang_dir.len, v->lang_dir.str,
                       os__PathSeparator.len, os__PathSeparator.str,
                       os__PathSeparator.len, os__PathSeparator.str,
                       mod_path.len, mod_path.str);
  };

  if (!os__dir_exists(import_path)) {

    import_path = _STR("%.*s%.*s%.*s", main__v_modules_path.len,
                       main__v_modules_path.str, os__PathSeparator.len,
                       os__PathSeparator.str, mod_path.len, mod_path.str);

    if (!os__dir_exists(import_path)) {

      return v_error(_STR("module \"%.*s\" not found", mod.len, mod.str));
    };
  };

  string tmp11 = OPTION_CAST(string)(import_path);
  return opt_ok(&tmp11, sizeof(string));
}
Option_string main__find_windows_kit_internal(RegKey key,
                                              array_string versions) {

#ifdef _WIN32

  array_string tmp1 = versions;
  for (int tmp2 = 0; tmp2 < tmp1.len; tmp2++) {
    string version = ((string *)tmp1.data)[tmp2];

    int required_bytes = 0;

    void *result = RegQueryValueExW(key, string_to_wide(version), 0, 0, 0,
                                    &required_bytes);

    int length = required_bytes / 2;

    if (result != 0) {

      continue;
    };

    int alloc_length = (required_bytes + 2);

    u16 *value = ((u16 *)(v_malloc(alloc_length)));

    if (isnil(value)) {

      continue;
    };

    void *result2 = RegQueryValueExW(key, string_to_wide(version), 0, 0, value,
                                     &alloc_length);

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

  return v_error(tos3("windows kit not found"));
}
Option_WindowsKit main__find_windows_kit_root() {

#ifdef _WIN32

  RegKey root_key = ((RegKey)(0));

  void *rc =
      RegOpenKeyExA(main__HKEY_LOCAL_MACHINE,
                    "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots", 0,
                    main__KEY_QUERY_VALUE | main__KEY_WOW64_32KEY |
                        main__KEY_ENUMERATE_SUB_KEYS,
                    &root_key);

  if (rc != 0) {

    Option tmp12 = v_error(tos3("Unable to open root key"));
    { RegCloseKey(root_key); }
    return tmp12;
    ;
  };

  Option_string tmp13 = main__find_windows_kit_internal(
      root_key,
      new_array_from_c_array(2, 2, sizeof(string),
                             EMPTY_ARRAY_OF_ELEMS(string, 2){
                                 tos3("KitsRoot10"), tos3("KitsRoot81")}));
  if (!tmp13.ok) {
    string err = tmp13.error;

    Option tmp14 = v_error(tos3("Unable to find a windows kit"));
    { RegCloseKey(root_key); }
    return tmp14;
    ;
  }
  string kit_root = *(string *)tmp13.data;
  ;

  string kit_lib = string_add(kit_root, tos3("Lib"));

  array_string files = os__ls(kit_lib);

  string highest_path = tos3("");

  int highest_int = 0;

  array_string tmp19 = files;
  for (int tmp20 = 0; tmp20 < tmp19.len; tmp20++) {
    string f = ((string *)tmp19.data)[tmp20];

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

  WindowsKit tmp25 = OPTION_CAST(WindowsKit)((WindowsKit){
      .um_lib_path = string_add(kit_lib_highest, tos3("\\um\\x64")),
      .ucrt_lib_path = string_add(kit_lib_highest, tos3("\\ucrt\\x64")),
      .um_include_path = string_add(kit_include_highest, tos3("\\um")),
      .ucrt_include_path = string_add(kit_include_highest, tos3("\\ucrt")),
      .shared_include_path =
          string_add(kit_include_highest, tos3("\\shared"))});
  return opt_ok(&tmp25, sizeof(WindowsKit));

  {

    RegCloseKey(root_key);
  }
#endif
  ;

  return v_error(tos3("Host OS does not support funding a windows kit"));
}
Option_VsInstallation main__find_vs() {

#ifndef _WIN32

  return v_error(tos3("Host OS does not support finding a Vs installation"));

#endif
  ;

  Option_os__Result tmp26 = os__exec(
      tos3("\"\"%ProgramFiles(x86)%\\Microsoft Visual "
           "Studio\\Installer\\vswhere.exe\" -latest -prerelease -products * "
           "-requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 "
           "-property installationPath\""));
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

    println(tos3("Unable to find msvc version"));

    return v_error(tos3("Unable to find vs installation"));
  }
  string version = *(string *)tmp27.data;
  ;

  string v = (string_ends_with(version, tos3("\n")))
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

  return v_error(tos3("Unable to find vs exe folder"));
}
Option_MsvcResult main__find_msvc() {

#ifdef _WIN32

  Option_WindowsKit tmp33 = main__find_windows_kit_root();
  if (!tmp33.ok) {
    string err = tmp33.error;

    return v_error(tos3("Unable to find windows sdk"));
  }
  WindowsKit wk = *(WindowsKit *)tmp33.data;
  ;

  Option_VsInstallation tmp34 = main__find_vs();
  if (!tmp34.ok) {
    string err = tmp34.error;

    return v_error(tos3("Unable to find visual studio"));
  }
  VsInstallation vs = *(VsInstallation *)tmp34.data;
  ;

  MsvcResult tmp35 = OPTION_CAST(MsvcResult)((MsvcResult){
      .full_cl_exe_path = os__realpath(string_add(
          string_add(vs.exe_path, os__PathSeparator), tos3("cl.exe"))),
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

  main__verror(tos3("Cannot find msvc on this OS"));

  return v_error(tos3("msvc not found"));

#endif
  ;
}
void V_cc_msvc(V *v) {

  Option_MsvcResult tmp36 = main__find_msvc();
  if (!tmp36.ok) {
    string err = tmp36.error;

    if (!v->pref->is_debug && string_ne(v->out_name_c, tos3("v.c")) &&
        string_ne(v->out_name_c, tos3("v_macos.c"))) {

      os__rm(v->out_name_c);
    };

    main__verror(tos3("Cannot find MSVC on this OS"));

    return;
  }
  MsvcResult r = *(MsvcResult *)tmp36.data;
  ;

  string out_name_obj = os__realpath(string_add(v->out_name_c, tos3(".obj")));

  array_string a = new_array_from_c_array(
      4, 4, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 4){
          tos3("-w"), tos3("/we4013"), tos3("/volatile:ms"),
          _STR("/Fo\"%.*s\"", out_name_obj.len, out_name_obj.str)});

  if (v->pref->is_prod) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/O2")), tmp39,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/MD")), tmp40,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/Zi")), tmp41,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/DNDEBUG")), tmp42,
          string);

  } else {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/Zi")), tmp43,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/MDd")), tmp44,
          string);
  };

  if (v->pref->is_so) {

    if (!string_ends_with(v->out_name, tos3(".dll"))) {

      v->out_name = string_add(v->out_name, tos3(".dll"));
    };

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/LD")), tmp45,
          string);

  } else if (!string_ends_with(v->out_name, tos3(".exe"))) {

    v->out_name = string_add(v->out_name, tos3(".exe"));
  };

  v->out_name = os__realpath(v->out_name);

  if (v->pref->build_mode == main__BuildMode_build_module) {

  } else if (v->pref->build_mode == main__BuildMode_default_mode) {
  };

  if (v->pref->sanitize) {

    println(tos3("Sanitize not supported on msvc."));
  };

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ string_add(
            string_add(tos3("\""), os__realpath(v->out_name_c)), tos3("\""))),
        tmp46, string);

  array_string real_libs = new_array_from_c_array(
      12, 12, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 12){
          tos3("kernel32.lib"), tos3("user32.lib"), tos3("gdi32.lib"),
          tos3("winspool.lib"), tos3("comdlg32.lib"), tos3("advapi32.lib"),
          tos3("shell32.lib"), tos3("ole32.lib"), tos3("oleaut32.lib"),
          tos3("uuid.lib"), tos3("odbc32.lib"), tos3("odbccp32.lib")});

  MsvcStringFlags sflags =
      array_CFlag_msvc_string_flags(V_get_os_cflags(&/* ? */ *v));

  _PUSH_MANY(&real_libs,
             (/*typ = array_string   tmp_typ=string*/ sflags.real_libs), tmp49,
             array_string);

  array_string inc_paths = sflags.inc_paths;

  array_string lib_paths = sflags.lib_paths;

  array_string other_flags = sflags.other_flags;

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-I \"%.*s\"", r.ucrt_include_path.len, r.ucrt_include_path.str)),
        tmp53, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-I \"%.*s\"", r.vs_include_path.len, r.vs_include_path.str)),
        tmp54, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "-I \"%.*s\"", r.um_include_path.len, r.um_include_path.str)),
        tmp55, string);

  _PUSH(
      &a,
      (/*typ = array_string   tmp_typ=string*/ _STR(
          "-I \"%.*s\"", r.shared_include_path.len, r.shared_include_path.str)),
      tmp56, string);

  _PUSH_MANY(&a, (/*typ = array_string   tmp_typ=string*/ inc_paths), tmp57,
             array_string);

  _PUSH_MANY(&a, (/*typ = array_string   tmp_typ=string*/ other_flags), tmp58,
             array_string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ array_string_join(real_libs,
                                                                   tos3(" "))),
        tmp59, string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/link")), tmp60,
        string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/NOLOGO")), tmp61,
        string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/OUT:\"%.*s\"", v->out_name.len, v->out_name.str)),
        tmp62, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/LIBPATH:\"%.*s\"", r.ucrt_lib_path.len, r.ucrt_lib_path.str)),
        tmp63, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/LIBPATH:\"%.*s\"", r.um_lib_path.len, r.um_lib_path.str)),
        tmp64, string);

  _PUSH(&a,
        (/*typ = array_string   tmp_typ=string*/ _STR(
            "/LIBPATH:\"%.*s\"", r.vs_lib_path.len, r.vs_lib_path.str)),
        tmp65, string);

  _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/DEBUG:FULL")),
        tmp66, string);

  if (v->pref->is_prod) {

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/INCREMENTAL:NO")),
          tmp67, string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/OPT:REF")), tmp68,
          string);

    _PUSH(&a, (/*typ = array_string   tmp_typ=string*/ tos3("/OPT:ICF")), tmp69,
          string);
  };

  _PUSH_MANY(&a, (/*typ = array_string   tmp_typ=string*/ lib_paths), tmp70,
             array_string);

  string args = array_string_join(a, tos3(" "));

  string cmd = _STR("\"\"%.*s\" %.*s\"", r.full_cl_exe_path.len,
                    r.full_cl_exe_path.str, args.len, args.str);

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    println(tos3("\n========== cl cmd line:"));

    println(cmd);

    println(tos3("==========\n"));
  };

  Option_os__Result tmp73 = os__exec(cmd);
  if (!tmp73.ok) {
    string err = tmp73.error;

    println(err);

    main__verror(tos3("msvc error"));

    return;
  }
  os__Result res = *(os__Result *)tmp73.data;
  ;

  if (res.exit_code != 0) {

    main__verror(res.output);
  };

  if (!v->pref->is_debug && string_ne(v->out_name_c, tos3("v.c")) &&
      string_ne(v->out_name_c, tos3("v_macos.c"))) {

    os__rm(v->out_name_c);
  };

  os__rm(out_name_obj);
}
void main__build_thirdparty_obj_file_with_msvc(string path,
                                               array_CFlag moduleflags) {

  Option_MsvcResult tmp74 = main__find_msvc();
  if (!tmp74.ok) {
    string err = tmp74.error;

    println(tos3("Could not find visual studio"));

    return;
  }
  MsvcResult msvc = *(MsvcResult *)tmp74.data;
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

  string cfiles = tos3("");

  array_string tmp79 = files;
  for (int tmp80 = 0; tmp80 < tmp79.len; tmp80++) {
    string file = ((string *)tmp79.data)[tmp80];

    if (string_ends_with(file, tos3(".c"))) {

      cfiles = string_add(
          cfiles,
          string_add(
              string_add(tos3("\""),
                         os__realpath(string_add(
                             string_add(parent, os__PathSeparator), file))),
              tos3("\" ")));
    };
  };

  string include_string =
      _STR("-I \"%.*s\" -I \"%.*s\" -I \"%.*s\" -I \"%.*s\"",
           msvc.ucrt_include_path.len, msvc.ucrt_include_path.str,
           msvc.vs_include_path.len, msvc.vs_include_path.str,
           msvc.um_include_path.len, msvc.um_include_path.str,
           msvc.shared_include_path.len, msvc.shared_include_path.str);

  string btarget = array_CFlag_c_options_before_target(moduleflags);

  string atarget = array_CFlag_c_options_after_target(moduleflags);

  string cmd = _STR("\"\"%.*s\" /volatile:ms /Zi /DNDEBUG %.*s /c %.*s %.*s "
                    "%.*s /Fo\"%.*s\"\"",
                    msvc.full_cl_exe_path.len, msvc.full_cl_exe_path.str,
                    include_string.len, include_string.str, btarget.len,
                    btarget.str, cfiles.len, cfiles.str, atarget.len,
                    atarget.str, obj_path.len, obj_path.str);

  printf("thirdparty cmd line: %.*s\n", cmd.len, cmd.str);

  Option_os__Result tmp85 = os__exec(cmd);
  if (!tmp85.ok) {
    string err = tmp85.error;

    main__verror(err);

    return;
  }
  os__Result res = *(os__Result *)tmp85.data;
  ;

  println(res.output);
}
MsvcStringFlags array_CFlag_msvc_string_flags(array_CFlag cflags) {

  array_string real_libs = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string inc_paths = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string lib_paths = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string other_flags = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_CFlag tmp90 = cflags;
  for (int tmp91 = 0; tmp91 < tmp90.len; tmp91++) {
    CFlag flag = ((CFlag *)tmp90.data)[tmp91];

    if (string_eq(flag.name, tos3("-l"))) {

      if (string_ends_with(flag.value, tos3(".dll"))) {

        main__verror(_STR("MSVC cannot link against a dll (`#flag -l %.*s`)",
                          flag.value.len, flag.value.str));
      };

      string lib_lib = string_add(flag.value, tos3(".lib"));

      _PUSH(&real_libs, (/*typ = array_string   tmp_typ=string*/ lib_lib),
            tmp93, string);

    } else if (string_eq(flag.name, tos3("-I"))) {

      _PUSH(
          &inc_paths,
          (/*typ = array_string   tmp_typ=string*/ CFlag_format(&/* ? */ flag)),
          tmp94, string);

    } else if (string_eq(flag.name, tos3("-L"))) {

      _PUSH(&lib_paths, (/*typ = array_string   tmp_typ=string*/ flag.value),
            tmp95, string);

      _PUSH(&lib_paths,
            (/*typ = array_string   tmp_typ=string*/ string_add(
                string_add(flag.value, os__PathSeparator), tos3("msvc"))),
            tmp96, string);

    } else if (string_ends_with(flag.value, tos3(".o"))) {

      _PUSH(&other_flags,
            (/*typ = array_string   tmp_typ=string*/ _STR(
                "\"%.*sbj\"", flag.value.len, flag.value.str)),
            tmp97, string);

    } else {

      _PUSH(&other_flags, (/*typ = array_string   tmp_typ=string*/ flag.value),
            tmp98, string);
    };
  };

  array_string lpaths = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  array_string tmp100 = lib_paths;
  for (int tmp101 = 0; tmp101 < tmp100.len; tmp101++) {
    string l = ((string *)tmp100.data)[tmp101];

    _PUSH(&lpaths,
          (/*typ = array_string   tmp_typ=string*/ string_add(
              string_add(tos3("/LIBPATH:\""), os__realpath(l)), tos3("\""))),
          tmp102, string);
  };

  return (MsvcStringFlags){real_libs, inc_paths, lpaths, other_flags};
}
void Parser_in_optimization(Parser *p, string typ, int ph) {

  Parser_check(p, main__TokenKind_lsbr);

  int i = 0;

  string expr = string_right(p->cgen->cur_line, ph);

  bool is_str = string_eq(typ, tos3("string"));

  while (p->tok != main__TokenKind_rsbr && p->tok != main__TokenKind_eof) {

    if (i > 0) {

      if (is_str) {

        Parser_gen(p, _STR(" || string_eq(%.*s, ", expr.len, expr.str));

      } else {

        Parser_gen(p, _STR(" || %.*s == ", expr.len, expr.str));
      };
    };

    if (i == 0) {

      if (is_str) {

        CGen_set_placeholder(p->cgen, ph, tos3(" string_eq("));

        Parser_gen(p, tos3(", "));

      } else {

        Parser_gen(p, tos3(" =="));
      };
    };

    Parser_check_types(p, Parser_bool_expression(p), typ);

    if (is_str) {

      Parser_gen(p, tos3(")"));
    };

    if (p->tok != main__TokenKind_rsbr) {

      Parser_check(p, main__TokenKind_comma);
    };

    i++;
  };

  Parser_check(p, main__TokenKind_rsbr);
}
Parser V_new_parser_from_string(V *v, string text, string id) {

  Parser p = V_new_parser(v, main__new_scanner(text), id);

  Parser_scan_tokens(&/* ? */ p);

  return p;
}
void V_reset_cgen_file_line_parameters(V *v) {

  v->cgen->line = 0;

  v->cgen->file = tos3("");

  v->cgen->line_directives = v->pref->is_debuggable;
}
Parser V_new_parser_from_file(V *v, string path) {

  V_reset_cgen_file_line_parameters(v);

  string path_pcguard = tos3("");

  string path_platform = tos3(".v");

  array_string tmp4 = new_array_from_c_array(
      4, 4, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 4){tos3("_lin.v"), tos3("_mac.v"),
                                      tos3("_win.v"), tos3("_nix.v")});
  for (int tmp5 = 0; tmp5 < tmp4.len; tmp5++) {
    string path_ending = ((string *)tmp4.data)[tmp5];

    if (string_ends_with(path, path_ending)) {

      path_platform = path_ending;

      path_pcguard = main__platform_postfix_to_ifdefguard(path_ending);

      break;
    };
  };

  Parser p = V_new_parser(v, main__new_scanner_file(path), path);

  p = (Parser){
      .file_path = path,
      .file_name = string_all_after(path, os__PathSeparator),
      .file_platform = path_platform,
      .file_pcguard = path_pcguard,
      .is_script = (v->pref->is_script &&
                    string_eq(os__realpath(path), os__realpath(path))),
      .is_vh = string_ends_with(path, tos3(".vh")),
      .id = p.id,
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
      .mod = p.mod,
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
      .is_struct_init = p.is_struct_init,
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
      .v_script = p.v_script,
      .var_decl_name = p.var_decl_name,
      .is_alloc = p.is_alloc,
      .is_const_literal = p.is_const_literal,
      .cur_gen_type = p.cur_gen_type,
      .is_vweb = p.is_vweb,
      .is_sql = p.is_sql,
      .is_js = p.is_js,
      .sql_i = p.sql_i,
      .sql_params = p.sql_params,
      .sql_types = p.sql_types,
  };

  if (p.pref->building_v) {

    p.scanner->should_print_relative_paths_on_error = 1;
  };

  Parser_scan_tokens(&/* ? */ p);

  return p;
}
Parser V_new_parser(V *v, Scanner *scanner, string id) {

  V_reset_cgen_file_line_parameters(v);

  Parser p = (Parser){
      .id = id,
      .scanner = scanner,
      .v = v,
      .table = v->table,
      .cur_fn = main__EmptyFn,
      .cgen = v->cgen,
      .is_script = 0,
      .pref = v->pref,
      .os = v->os,
      .vroot = v->vroot,
      .local_vars = array_repeat(
          new_array_from_c_array(1, 1, sizeof(Var),
                                 EMPTY_ARRAY_OF_ELEMS(Var, 1){
                                     (Var){.typ = tos((byte *)"", 0),
                                           .name = tos((byte *)"", 0),
                                           .idx = 0,
                                           .is_arg = 0,
                                           .is_const = 0,
                                           .args = new_array(0, 1, sizeof(Var)),
                                           .attr = tos((byte *)"", 0),
                                           .is_mut = 0,
                                           .is_alloc = 0,
                                           .is_returned = 0,
                                           .ptr = 0,
                                           .ref = 0,
                                           .parent_fn = tos((byte *)"", 0),
                                           .mod = tos((byte *)"", 0),
                                           .is_global = 0,
                                           .is_used = 0,
                                           .is_changed = 0,
                                           .scope_level = 0,
                                           .is_c = 0,
                                           .is_moved = 0,
                                           .line_nr = 0,
                                           .token_idx = 0}}),
          main__MaxLocalVars),
      .import_table = Table_get_file_import_table(&/* ? */ *v->table, id),
      .file_path = tos((byte *)"", 0),
      .file_name = tos((byte *)"", 0),
      .file_platform = tos((byte *)"", 0),
      .file_pcguard = tos((byte *)"", 0),
      .tokens = new_array(0, 1, sizeof(Token)),
      .token_idx = 0,
      .lit = tos((byte *)"", 0),
      .mod = tos((byte *)"", 0),
      .inside_const = 0,
      .has_immutable_field = 0,
      .assigned_type = tos((byte *)"", 0),
      .expected_type = tos((byte *)"", 0),
      .tmp_cnt = 0,
      .builtin_mod = 0,
      .inside_if_expr = 0,
      .inside_unwrapping_match_statement = 0,
      .inside_return_expr = 0,
      .is_struct_init = 0,
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
      .attr = tos((byte *)"", 0),
      .v_script = 0,
      .var_decl_name = tos((byte *)"", 0),
      .is_alloc = 0,
      .is_const_literal = 0,
      .cur_gen_type = tos((byte *)"", 0),
      .is_vweb = 0,
      .is_sql = 0,
      .is_js = 0,
      .sql_i = 0,
      .sql_params = new_array(0, 1, sizeof(string)),
      .sql_types = new_array(0, 1, sizeof(string)),
      .is_vh = 0};

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
void Parser_scan_tokens(Parser *p) {

  while (1) {

    ScanRes res = Scanner_scan(p->scanner);

    _PUSH(&p->tokens,
          (/*typ = array_Token   tmp_typ=Token*/ (Token){
              .tok = res.tok,
              .lit = res.lit,
              .line_nr = p->scanner->line_nr,
              .col = p->scanner->pos - p->scanner->last_nl_pos,
              .name_idx = 0,
          }),
          tmp9, Token);

    if (res.tok == main__TokenKind_eof) {

      break;
    };
  };
}
void Parser_set_current_fn(Parser *p, Fn f) {

  p->cur_fn = f;

  p->scanner->fn_name =
      _STR("%.*s.%.*s", f.mod.len, f.mod.str, f.name.len, f.name.str);
}
void Parser_next(Parser *p) {

  p->prev_tok2 = p->prev_tok;

  p->prev_tok = p->tok;

  p->scanner->prev_tok = p->tok;

  if (p->token_idx >= p->tokens.len) {

    p->tok = main__TokenKind_eof;

    p->lit = tos3("");

    return;
  };

  Token res = (*(Token *)array_get(p->tokens, p->token_idx));

  p->token_idx++;

  p->tok = res.tok;

  p->lit = res.lit;

  p->scanner->line_nr = res.line_nr;

  p->cgen->line = res.line_nr;
}
TokenKind Parser_peek(Parser *p) {

  if (p->token_idx >= p->tokens.len - 2) {

    return main__TokenKind_eof;
  };

  Token tok = (*(Token *)array_get(p->tokens, p->token_idx));

  return tok.tok;
}
static inline Token Parser_prev_token(Parser *p) {

  return (*(Token *)array_get(p->tokens, p->token_idx - 2));
}
static inline Token Parser_cur_tok(Parser *p) {

  return (*(Token *)array_get(p->tokens, p->token_idx - 1));
}
static inline Token Parser_peek_token(Parser *p) {

  if (p->token_idx >= p->tokens.len - 2) {

    return (Token){.tok = main__TokenKind_eof,
                   .lit = tos((byte *)"", 0),
                   .line_nr = 0,
                   .name_idx = 0,
                   .col = 0};
  };

  return (*(Token *)array_get(p->tokens, p->token_idx));
}
void Parser_log(Parser *p, string s) {}
void Parser_parse(Parser *p, Pass pass) {

  p->cgen->line = 0;

  p->cgen->file = main__cescaped_path(os__realpath(p->file_path));

  p->pass = pass;

  p->token_idx = 0;

  Parser_next(p);

  if (p->is_script || p->pref->is_test) {

    p->mod = tos3("main");

    if (p->tok == main__TokenKind_key_module) {

      Parser_next(p);

      Parser_fgen(p, tos3("module "));

      p->mod = Parser_check_name(p);
    };

  } else {

    Parser_check(p, main__TokenKind_key_module);

    Parser_fspace(p);

    p->mod = Parser_check_name(p);
  };

  p->cgen->nogen = 0;

  if (p->pref->build_mode == main__BuildMode_build_module &&
      string_ne(p->mod, p->v->mod)) {

    p->cgen->nogen = 1;
  };

  Parser_fgenln(p, tos3("\n"));

  p->builtin_mod = string_eq(p->mod, tos3("builtin"));

  p->can_chash =
      string_eq(p->mod, tos3("ui")) || string_eq(p->mod, tos3("darwin"));

  string fq_mod =
      Table_qualify_module(&/* ? */ *p->table, p->mod, p->file_path);

  p->import_table.module_name = fq_mod;

  Table_register_module(p->table, fq_mod);

  p->mod = string_replace(fq_mod, tos3("."), tos3("_dot_"));

  if (p->pass == main__Pass_imports) {

    while (p->tok == main__TokenKind_key_import &&
           Parser_peek(&/* ? */ *p) != main__TokenKind_key_const) {

      Parser_imports(p);
    };

    if (_IN(string, (tos3("builtin")), p->table->imports)) {

      Parser_error(p, tos3("module `builtin` cannot be imported"));
    };

    map_set(&p->table->file_imports, p->id,
            &(FileImportTable[]){p->import_table});

    return;
  };

  while (1) {

    if (p->tok == main__TokenKind_key_import) { /* case */

      if (Parser_peek(&/* ? */ *p) == main__TokenKind_key_const) {

        Parser_const_decl(p);

      } else {

        Parser_imports(p);

        if (p->tok != main__TokenKind_key_import) {

          Parser_fgenln(p, tos3(""));
        };
      };

    } else if (p->tok == main__TokenKind_key_enum) { /* case */

      Parser_next(p);

      if (p->tok == main__TokenKind_name) {

        Parser_fgen(p, tos3("enum "));

        string name = Parser_check_name(p);

        Parser_fgen(p, tos3(" "));

        Parser_enum_decl(p, name);

      } else if (p->pref->translated) {

        Parser_enum_decl(p, tos3("int"));

      } else {

        Parser_check(p, main__TokenKind_name);
      };

    } else if (p->tok == main__TokenKind_key_pub) { /* case */

      if (Parser_peek(&/* ? */ *p) == main__TokenKind_func) {

        Parser_fn_decl(p);

      } else if (Parser_peek(&/* ? */ *p) == main__TokenKind_key_struct) {

        Parser_error(p, tos3("structs can\'t be declared public *yet*"));

      } else {

        Parser_error(p, tos3("wrong pub keyword usage"));
      };

    } else if (p->tok == main__TokenKind_func) { /* case */

      Parser_fn_decl(p);

    } else if (p->tok == main__TokenKind_key_type) { /* case */

      Parser_type_decl(p);

    } else if (p->tok == main__TokenKind_lsbr) { /* case */

      Parser_attribute(p);

    } else if (p->tok == main__TokenKind_key_struct ||
               p->tok == main__TokenKind_key_interface ||
               p->tok == main__TokenKind_key_union ||
               p->tok == main__TokenKind_lsbr) { /* case */

      Parser_struct_decl(p);

    } else if (p->tok == main__TokenKind_key_const) { /* case */

      Parser_const_decl(p);

    } else if (p->tok == main__TokenKind_hash) { /* case */

      Parser_chash(p);

    } else if (p->tok == main__TokenKind_dollar) { /* case */

      Parser_comp_time(p);

    } else if (p->tok == main__TokenKind_key_global) { /* case */

      if (!p->pref->translated && !p->pref->is_live && !p->builtin_mod &&
          !p->pref->building_v &&
          !string_contains(os__getwd(), tos3("/volt"))) {

        Parser_error(p, tos3("__global is only allowed in translated code"));
      };

      Parser_next(p);

      string name = Parser_check_name(p);

      string typ = Parser_get_type(p);

      Parser_register_global(p, name, typ);

      string g = Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ);

      if (p->tok == main__TokenKind_assign) {

        Parser_next(p);

        g = string_add(g, tos3(" = "));

        _V_MulRet_string_V_string _V_mret___expr = Parser_tmp_expr(p);
        string expr = _V_mret___expr.var_1;

        g = string_add(g, expr);
      };

      g = string_add(g, tos3("; // global"));

      if (!p->cgen->nogen) {

        _PUSH(&p->cgen->consts, (/*typ = array_string   tmp_typ=string*/ g),
              tmp28, string);
      };

    } else if (p->tok == main__TokenKind_eof) { /* case */

      if (!Parser_first_pass(&/* ? */ *p) && !p->pref->is_repl) {

        Parser_check_unused_imports(p);
      };

      if (0 && !Parser_first_pass(&/* ? */ *p) &&
          Parser_fileis(&/* ? */ *p, tos3("main.v"))) {

        Option_os__File tmp29 = os__create(tos3("/var/tmp/fmt.v"));
        if (!tmp29.ok) {
          string err = tmp29.error;

          main__verror(tos3("failed to create fmt.v"));

          return;
        }
        os__File out = *(os__File *)tmp29.data;
        ;

        os__File_writeln(out, strings__Builder_str(p->scanner->fmt_out));

        os__File_close(out);
      };

      return;

    } else { // default:

      if (p->is_script && !p->pref->is_test) {

        if (Parser_first_pass(&/* ? */ *p)) {

          if (string_eq(p->cur_fn.name, tos3(""))) {

            Parser_set_current_fn(p, main__MainFn);
          };

          return;
        };

        if (string_eq(p->cur_fn.name, tos3(""))) {

          Parser_set_current_fn(p, main__MainFn);

          if (p->pref->is_repl) {

            Parser_clear_vars(p);
          };
        };

        int start = p->cgen->lines.len;

        Parser_statement(p, 1);

        if (string_ne((*(string *)array_get(p->cgen->lines, start - 1)),
                      tos3("")) &&
            string_ne(p->cgen->fn_main, tos3(""))) {

          start--;
        };

        Parser_genln(p, tos3(""));

        int end = p->cgen->lines.len;

        array_string lines = array_slice(p->cgen->lines, start, end);

        p->cgen->fn_main =
            string_add(p->cgen->fn_main, array_string_join(lines, tos3("\n")));

        CGen_resetln(p->cgen, tos3(""));

        for (int i = start; i < end; i++) {

          array_set(&/*q*/ p->cgen->lines, i, &(string[]){tos3("")});
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

  Parser_check(p, main__TokenKind_key_import);

  if (p->tok == main__TokenKind_lpar) {

    Parser_check(p, main__TokenKind_lpar);

    while (p->tok != main__TokenKind_rpar && p->tok != main__TokenKind_eof) {

      Parser_import_statement(p);
    };

    Parser_check(p, main__TokenKind_rpar);

    return;
  };

  Parser_import_statement(p);
}
void Parser_import_statement(Parser *p) {

  if (p->tok != main__TokenKind_name) {

    Parser_error(p, tos3("bad import format"));
  };

  if (Parser_peek(&/* ? */ *p) == main__TokenKind_number) {

    Parser_error(p, tos3("bad import format. module/submodule names cannot "
                         "begin with a number"));
  };

  int import_tok_idx = p->token_idx - 1;

  string mod = string_trim_space(Parser_check_name(p));

  string mod_alias = mod;

  int depth = 1;

  while (p->tok == main__TokenKind_dot) {

    Parser_check(p, main__TokenKind_dot);

    string submodule = Parser_check_name(p);

    mod_alias = submodule;

    mod = string_add(mod, string_add(tos3("."), submodule));

    depth++;

    if (depth > main__MaxModuleDepth) {

      Parser_error(p, _STR("module depth of %d exceeded: %.*s",
                           main__MaxModuleDepth, mod.len, mod.str));
    };
  };

  if (p->tok == main__TokenKind_key_as &&
      Parser_peek(&/* ? */ *p) == main__TokenKind_name) {

    Parser_check(p, main__TokenKind_key_as);

    mod_alias = Parser_check_name(p);
  };

  FileImportTable_register_alias(&/* ? */ p->import_table, mod_alias, mod,
                                 import_tok_idx);

  if (_IN(string, (mod), p->table->imports)) {

    return;
  };

  _PUSH(&p->table->imports, (/*typ = array_string   tmp_typ=string*/ mod),
        tmp41, string);

  Table_register_module(p->table, mod);

  Parser_fgenln(p, string_add(tos3(" "), mod));
}
void Parser_const_decl(Parser *p) {

  if (p->tok == main__TokenKind_key_import) {

    Parser_error_with_token_index(
        p,
        string_add(
            string_add(tos3("`import const` was removed from the language, "),
                       tos3("because predeclaring C constants is not needed "
                            "anymore. ")),
            tos3("You can use them directly with C.CONST_NAME")),
        Parser_cur_tok_index(&/* ? */ *p));
  };

  p->inside_const = 1;

  Parser_check(p, main__TokenKind_key_const);

  Parser_fspace(p);

  Parser_check(p, main__TokenKind_lpar);

  Parser_fgenln(p, tos3(""));

  Parser_fmt_inc(p);

  while (p->tok == main__TokenKind_name) {

    if (string_eq(p->lit, tos3("_")) &&
        Parser_peek(&/* ? */ *p) == main__TokenKind_assign && !p->cgen->nogen) {

      Parser_gen_blank_identifier_assign(p);

      _PUSH(&p->cgen->consts_init,
            (/*typ = array_string   tmp_typ=string*/ string_trim_space(
                p->cgen->cur_line)),
            tmp42, string);

      CGen_resetln(p->cgen, tos3(""));

      continue;
    };

    string name = Parser_check_name(p);

    name = Parser_prepend_mod(&/* ? */ *p, name);

    string typ = tos3("");

    if (p->is_vh) {

      typ = Parser_get_type(p);

      Table_register_const(p->table, name, typ, p->mod);

      _PUSH(
          &p->cgen->consts,
          (/*typ = array_string   tmp_typ=string*/ string_add(
              (string_add(tos3("extern "), Table_cgen_name_type_pair(
                                               &/* ? */ *p->table, name, typ))),
              tos3(";"))),
          tmp45, string);

      continue;

    } else {

      Parser_check_space(p, main__TokenKind_assign);

      typ = Parser_expression(p);
    };

    if (Parser_first_pass(&/* ? */ *p) &&
        Table_known_const(&/* ? */ *p->table, name)) {

      Parser_error(p, _STR("redefinition of `%.*s`", name.len, name.str));
    };

    if (Parser_first_pass(&/* ? */ *p)) {

      Table_register_const(p->table, name, typ, p->mod);
    };

    if (p->pass == main__Pass_main && !p->cgen->nogen) {

      if (p->pref->build_mode != main__BuildMode_build_module &&
          main__is_compile_time_const(p->cgen->cur_line)) {

        _PUSH(&p->cgen->consts,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "#define %.*s %.*s", name.len, name.str,
                  p->cgen->cur_line.len, p->cgen->cur_line.str)),
              tmp46, string);

        CGen_resetln(p->cgen, tos3(""));

        Parser_fgenln(p, tos3(""));

        continue;
      };

      if (string_starts_with(typ, tos3("["))) {

        _PUSH(&p->cgen->consts,
              (/*typ = array_string   tmp_typ=string*/ string_add(
                  Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ),
                  _STR(" = %.*s;", p->cgen->cur_line.len,
                       p->cgen->cur_line.str))),
              tmp47, string);

      } else {

        _PUSH(&p->cgen->consts,
              (/*typ = array_string   tmp_typ=string*/ string_add(
                  Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ),
                  tos3(";"))),
              tmp48, string);

        _PUSH(&p->cgen->consts_init,
              (/*typ = array_string   tmp_typ=string*/ _STR(
                  "%.*s = %.*s;", name.len, name.str, p->cgen->cur_line.len,
                  p->cgen->cur_line.str)),
              tmp49, string);
      };

      CGen_resetln(p->cgen, tos3(""));
    };

    Parser_fgenln(p, tos3(""));
  };

  Parser_fmt_dec(p);

  Parser_check(p, main__TokenKind_rpar);

  Parser_fgenln(p, tos3("\n"));

  p->inside_const = 0;
}
void Parser_type_decl(Parser *p) {

  Parser_check(p, main__TokenKind_key_type);

  string name = Parser_check_name(p);

  if (p->tok == main__TokenKind_key_struct) {

    Parser_error(p, _STR("use `struct %.*s {` instead of `type %.*s struct {`",
                         name.len, name.str, name.len, name.str));
  };

  Type parent = Parser_get_type2(p);

  string nt_pair =
      Table_cgen_name_type_pair(&/* ? */ *p->table, name, parent.name);

  string _struct = (parent.cat != main__TypeCategory_array &&
                    parent.cat != main__TypeCategory_func &&
                    !Table_known_type(&/* ? */ *p->table, parent.name))
                       ? (tos3("struct"))
                       : (tos3(""));

  Parser_gen_typedef(
      p, _STR("typedef %.*s %.*s; //type alias name=\"%.*s\" parent=`%.*s`",
              _struct.len, _struct.str, nt_pair.len, nt_pair.str, name.len,
              name.str, parent.name.len, parent.name.str));

  Parser_register_type_with_parent(p, name, parent.name);
}
Fn *Parser_interface_method(Parser *p, string field_name, string receiver) {

  Fn *method = (Fn *)memdup(&(Fn){.name = field_name,
                                  .is_interface = 1,
                                  .is_method = 1,
                                  .receiver_typ = receiver,
                                  .mod = tos((byte *)"", 0),
                                  .args = new_array(0, 1, sizeof(Var)),
                                  .scope_level = 0,
                                  .typ = tos((byte *)"", 0),
                                  .is_c = 0,
                                  .is_public = 0,
                                  .returns_error = 0,
                                  .is_decl = 0,
                                  .defer_text = new_array(0, 1, sizeof(string)),
                                  .fn_name_token_idx = 0},
                            sizeof(Fn));

  Parser_fn_args(p, method);

  Token prev_tok = Parser_prev_token(&/* ? */ *p);

  Token cur_tok = Parser_cur_tok(&/* ? */ *p);

  if (prev_tok.line_nr != cur_tok.line_nr) {

    method->typ = tos3("void");

  } else {

    method->typ = Parser_get_type(p);

    Parser_fspace(p);

    Parser_fgenln(p, tos3(""));
  };

  return method;
}
TypeCategory main__key_to_type_cat(TokenKind tok) {

  if (tok == main__TokenKind_key_interface) { /* case */

    return main__TypeCategory_interface_;

  } else if (tok == main__TokenKind_key_struct) { /* case */

    return main__TypeCategory_struct_;

  } else if (tok == main__TokenKind_key_union) { /* case */

    return main__TypeCategory_union_;
  };

  main__verror(_STR("Unknown token: %d", tok));

  return main__TypeCategory_builtin;
}
void Parser_struct_decl(Parser *p) {

  bool is_objc = string_starts_with(p->attr, tos3("objc_interface"));

  string objc_parent = (is_objc) ? (string_right(p->attr, 15)) : (tos3(""));

  bool is_interface = p->tok == main__TokenKind_key_interface;

  bool is_union = p->tok == main__TokenKind_key_union;

  bool is_struct = p->tok == main__TokenKind_key_struct;

  TypeCategory cat = main__key_to_type_cat(p->tok);

  if (is_objc) {

    cat = main__TypeCategory_objc_interface;
  };

  Parser_fgen(p, string_add(TokenKind_str(p->tok), tos3(" ")));

  Parser_next(p);

  string name = Parser_check_name(p);

  if (string_contains(name, tos3("_")) && !p->pref->translated) {

    Parser_error(p, tos3("type names cannot contain `_`"));
  };

  if (!p->builtin_mod && !byte_is_capital(string_at(name, 0))) {

    Parser_error(p, _STR("struct names must be capitalized: use `struct %.*s`",
                         string_capitalize(name).len,
                         string_capitalize(name).str));
  };

  if (is_interface && !string_ends_with(name, tos3("er"))) {

    Parser_error(p, tos3("interface names temporarily have to end with `er` "
                         "(e.g. `Speaker`, `Reader`)"));
  };

  bool is_c = string_eq(name, tos3("C")) && p->tok == main__TokenKind_dot;

  if (is_c) {

    Parser_check(p, main__TokenKind_dot);

    name = Parser_check_name(p);

    cat = main__TypeCategory_c_struct;

    if (string_eq(p->attr, tos3("typedef"))) {

      cat = main__TypeCategory_c_typedef;
    };
  };

  if (!is_c && !main__good_type_name(name)) {

    Parser_error(p, tos3("bad struct name, e.g. use `HttpRequest` instead of "
                         "`HTTPRequest`"));
  };

  if (!is_c && !p->builtin_mod && string_ne(p->mod, tos3("main"))) {

    name = Parser_prepend_mod(&/* ? */ *p, name);
  };

  Type typ = Table_find_type(&/* ? */ *p->table, name);

  if (p->pass == main__Pass_decl &&
      Table_known_type_fast(&/* ? */ *p->table,
                            &/*112 EXP:"Type*" GOT:"Type" */ typ)) {

    Parser_error(p, _STR("`%.*s` redeclared", name.len, name.str));
  };

  if (is_objc) {

    Parser_gen_typedef(p, _STR("@class %.*s;", name.len, name.str));

  } else if (!is_c) {

    string kind = (is_union) ? (tos3("union")) : (tos3("struct"));

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

    typ.parent = objc_parent;

    Table_rewrite_type(p->table, typ);

  } else {

    typ = (Type){.name = name,
                 .mod = p->mod,
                 .is_c = is_c,
                 .cat = cat,
                 .parent = objc_parent,
                 .fields = new_array(0, 1, sizeof(Var)),
                 .methods = new_array(0, 1, sizeof(Fn)),
                 .enum_vals = new_array(0, 1, sizeof(string)),
                 .gen_types = new_array(0, 1, sizeof(string)),
                 .is_placeholder = 0,
                 .gen_str = 0};
  };

  if (is_c && is_struct && p->tok != main__TokenKind_lcbr) {

    Table_register_type2(p->table, typ);

    return;
  };

  Parser_fgen(p, tos3(" "));

  Parser_check(p, main__TokenKind_lcbr);

  bool is_pub = 0;

  bool is_mut = 0;

  array_string names = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  if (!is_ph && Parser_first_pass(&/* ? */ *p)) {

    Table_register_type2(p->table, typ);
  };

  bool did_gen_something = 0;

  while (p->tok != main__TokenKind_rcbr) {

    if (p->tok == main__TokenKind_key_pub) {

      if (is_pub) {

        Parser_error(p, tos3("structs can only have one `pub:`, all public "
                             "fields have to be grouped"));
      };

      is_pub = 1;

      Parser_fmt_dec(p);

      Parser_check(p, main__TokenKind_key_pub);

      if (p->tok != main__TokenKind_key_mut) {

        Parser_check(p, main__TokenKind_colon);
      };

      Parser_fmt_inc(p);

      Parser_fgenln(p, tos3(""));
    };

    if (p->tok == main__TokenKind_key_mut) {

      if (is_mut) {

        Parser_error(p, tos3("structs can only have one `mut:`, all private "
                             "key_mut fields have to be grouped"));
      };

      is_mut = 1;

      Parser_fmt_dec(p);

      Parser_check(p, main__TokenKind_key_mut);

      if (p->tok != main__TokenKind_key_mut) {

        Parser_check(p, main__TokenKind_colon);
      };

      Parser_fmt_inc(p);

      Parser_fgenln(p, tos3(""));
    };

    int field_name_token_idx = Parser_cur_tok_index(&/* ? */ *p);

    string field_name =
        (string_ne(name, tos3("Option")))
            ? (Table_var_cgen_name(&/* ? */ *p->table, Parser_check_name(p)))
            : (Parser_check_name(p));

    if (_IN(string, (field_name), names)) {

      Parser_error(
          p, _STR("duplicate field `%.*s`", field_name.len, field_name.str));
    };

    if (!is_c && string_ne(p->mod, tos3("os")) &&
        main__contains_capital(field_name)) {

      Parser_error(p, tos3("struct fields cannot contain uppercase letters, "
                           "use snake_case instead"));
    };

    _PUSH(&names, (/*typ = array_string   tmp_typ=string*/ field_name), tmp76,
          string);

    if (is_interface) {

      Fn *f = Parser_interface_method(p, field_name, name);

      if (Parser_first_pass(&/* ? */ *p)) {

        Parser_add_method(p, typ.name, *f);
      };

      continue;
    };

    AccessMod access_mod =
        (is_pub) ? (main__AccessMod_public) : (main__AccessMod_private);

    Parser_fgen(p, tos3(" "));

    string field_type = Parser_get_type(p);

    if (string_eq(field_type, name)) {

      Parser_error_with_token_index(
          p,
          _STR("cannot embed struct `%.*s` in itself (field `%.*s`)", name.len,
               name.str, field_name.len, field_name.str),
          field_name_token_idx);
    };

    Parser_check_and_register_used_imported_type(p, field_type);

    bool is_atomic = p->tok == main__TokenKind_key_atomic;

    if (is_atomic) {

      Parser_next(p);
    };

    string attr = tos3("");

    if (p->tok == main__TokenKind_lsbr) {

      Parser_next(p);

      attr = Parser_check_name(p);

      if (p->tok == main__TokenKind_colon) {

        Parser_check(p, main__TokenKind_colon);

        attr = string_add(attr, string_add(tos3(":"), Parser_check_name(p)));
      };

      Parser_check(p, main__TokenKind_rsbr);
    };

    if (string_eq(attr, tos3("raw")) && string_ne(field_type, tos3("string"))) {

      Parser_error(p, _STR("struct field with attribute \"raw\" should be of "
                           "type \"string\" but got \"%.*s\"",
                           field_type.len, field_type.str));
    };

    did_gen_something = 1;

    if (Parser_first_pass(&/* ? */ *p)) {

      Table_add_field(p->table, typ.name, field_name, field_type, is_mut, attr,
                      access_mod);
    };

    Parser_fgenln(p, tos3(""));
  };

  Parser_check(p, main__TokenKind_rcbr);

  if (!is_c) {

    if (!did_gen_something) {

      if (Parser_first_pass(&/* ? */ *p)) {

        Table_add_field(p->table, typ.name, tos3(""),
                        tos3("EMPTY_STRUCT_DECLARATION"), 0, tos3(""),
                        main__AccessMod_private);
      };
    };
  };

  Parser_fgenln(p, tos3("\n"));
}
void Parser_enum_decl(Parser *p, string _enum_name) {

  string enum_name = _enum_name;

  if (!p->builtin_mod && string_ne(p->mod, tos3("main"))) {

    enum_name = Parser_prepend_mod(&/* ? */ *p, enum_name);
  };

  if (string_ne(enum_name, tos3("int")) && !Parser_first_pass(&/* ? */ *p)) {

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "typedef int %.*s;", enum_name.len, enum_name.str)),
          tmp83, string);
  };

  Parser_check(p, main__TokenKind_lcbr);

  int val = 0;

  array_string fields = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (p->tok == main__TokenKind_name) {

    string field = Parser_check_name(p);

    _PUSH(&fields, (/*typ = array_string   tmp_typ=string*/ field), tmp87,
          string);

    Parser_fgenln(p, tos3(""));

    string name = _STR("%.*s__%.*s_%.*s", p->mod.len, p->mod.str, enum_name.len,
                       enum_name.str, field.len, field.str);

    if (p->pass == main__Pass_main) {

      _PUSH(&p->cgen->consts,
            (/*typ = array_string   tmp_typ=string*/ _STR(
                "#define %.*s %d", name.len, name.str, val)),
            tmp89, string);
    };

    if (p->tok == main__TokenKind_comma) {

      Parser_next(p);
    };

    Table_register_const(p->table, name, enum_name, p->mod);

    val++;
  };

  Table_register_type2(p->table,
                       (Type){.name = enum_name,
                              .mod = p->mod,
                              .parent = tos3("int"),
                              .cat = main__TypeCategory_enum_,
                              .enum_vals = array_clone(fields),
                              .fields = new_array(0, 1, sizeof(Var)),
                              .methods = new_array(0, 1, sizeof(Fn)),
                              .is_c = 0,
                              .gen_types = new_array(0, 1, sizeof(string)),
                              .is_placeholder = 0,
                              .gen_str = 0});

  Parser_check(p, main__TokenKind_rcbr);

  Parser_fgenln(p, tos3("\n"));
}
string Parser_check_name(Parser *p) {

  string name = p->lit;

  Parser_check(p, main__TokenKind_name);

  return name;
}
string Parser_check_string(Parser *p) {

  string s = p->lit;

  Parser_check(p, main__TokenKind_str);

  return s;
}
string Parser_strtok(Parser *p) {

  if (p->tok == main__TokenKind_name) {

    return p->lit;
  };

  if (p->tok == main__TokenKind_str) {

    return _STR("\"%.*s\"", p->lit.len, p->lit.str);
  };

  string res = TokenKind_str(p->tok);

  if (string_eq(res, tos3(""))) {

    int n = ((int)(p->tok));

    return int_str(n);
  };

  return res;
}
void Parser_check_space(Parser *p, TokenKind expected) {

  Parser_fspace(p);

  Parser_check(p, expected);

  Parser_fspace(p);
}
void Parser_check(Parser *p, TokenKind expected) {

  if (p->tok != expected) {

    println(tos3("check()"));

    string s =
        _STR("expected `%.*s` but got `%.*s`", TokenKind_str(expected).len,
             TokenKind_str(expected).str, Parser_strtok(&/* ? */ *p).len,
             Parser_strtok(&/* ? */ *p).str);

    Parser_next(p);

    printf("next token = `%.*s`\n", Parser_strtok(&/* ? */ *p).len,
           Parser_strtok(&/* ? */ *p).str);

    print_backtrace();

    Parser_error(p, s);
  };

  Parser_next(p);

  if (string_ne(p->scanner->line_comment, tos3(""))) {
  };
}
static inline bool Parser_first_pass(Parser *p) {

  return p->pass == main__Pass_decl;
}
string Parser_get_type(Parser *p) {

  bool mul = 0;

  int nr_muls = 0;

  string typ = tos3("");

  if (p->tok == main__TokenKind_lpar) {

    Parser_check(p, main__TokenKind_lpar);

    array_string types = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    while (1) {

      _PUSH(&types,
            (/*typ = array_string   tmp_typ=string*/ Parser_get_type(p)), tmp99,
            string);

      if (p->tok != main__TokenKind_comma) {

        break;
      };

      Parser_check(p, main__TokenKind_comma);
    };

    Parser_check(p, main__TokenKind_rpar);

    typ = Parser_register_multi_return_stuct(p, types);

    return typ;
  };

  if (p->tok == main__TokenKind_func) {

    Fn f = (Fn){.name = tos3("_"),
                .mod = p->mod,
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
                .defer_text = new_array(0, 1, sizeof(string)),
                .fn_name_token_idx = 0};

    Parser_next(p);

    int line_nr = p->scanner->line_nr;

    Parser_fn_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

    if (p->scanner->line_nr == line_nr) {

      if (p->tok == main__TokenKind_name || p->tok == main__TokenKind_mul ||
          p->tok == main__TokenKind_amp || p->tok == main__TokenKind_lsbr ||
          p->tok == main__TokenKind_question ||
          p->tok == main__TokenKind_lpar) {

        f.typ = Parser_get_type(p);

      } else {

        f.typ = tos3("void");
      };

    } else {

      f.typ = tos3("void");
    };

    Type fn_typ = (Type){.name = Fn_typ_str(&/* ? */ f),
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

    return Fn_typ_str(&/* ? */ f);
  };

  bool is_arr = 0;

  bool is_arr2 = 0;

  bool is_question = p->tok == main__TokenKind_question;

  if (is_question) {

    Parser_check(p, main__TokenKind_question);
  };

  if (p->tok == main__TokenKind_lsbr) {

    Parser_check(p, main__TokenKind_lsbr);

    if (p->tok == main__TokenKind_number) {

      typ = _STR("[%.*s]", p->lit.len, p->lit.str);

      Parser_next(p);

    } else {

      is_arr = 1;
    };

    Parser_check(p, main__TokenKind_rsbr);

    if (p->tok == main__TokenKind_lsbr) {

      Parser_next(p);

      if (p->tok == main__TokenKind_number) {

        typ = string_add(typ, _STR("[%.*s]", p->lit.len, p->lit.str));

        Parser_check(p, main__TokenKind_number);

      } else {

        is_arr2 = 1;
      };

      Parser_check(p, main__TokenKind_rsbr);
    };
  };

  if (!p->builtin_mod && p->tok == main__TokenKind_name &&
      string_eq(p->lit, tos3("map"))) {

    Parser_next(p);

    Parser_check(p, main__TokenKind_lsbr);

    string key_type = Parser_check_name(p);

    if (string_ne(key_type, tos3("string"))) {

      Parser_error(p, tos3("maps only support string keys for now"));
    };

    Parser_check(p, main__TokenKind_rsbr);

    string val_type = Parser_get_type(p);

    typ = _STR("map_%.*s", val_type.len, val_type.str);

    Parser_register_map(p, typ);

    return typ;
  };

  bool warn = 0;

  while (p->tok == main__TokenKind_mul) {

    if (Parser_first_pass(&/* ? */ *p)) {

      warn = 1;
    };

    mul = 1;

    nr_muls++;

    Parser_check(p, main__TokenKind_mul);
  };

  if (p->tok == main__TokenKind_amp) {

    mul = 1;

    nr_muls++;

    Parser_check(p, main__TokenKind_amp);
  };

  typ = string_add(typ, p->lit);

  if (!p->is_struct_init) {

    Parser_fgen(p, p->lit);
  };

  if (string_eq(p->lit, tos3("C")) &&
      Parser_peek(&/* ? */ *p) == main__TokenKind_dot) {

    Parser_next(p);

    Parser_check(p, main__TokenKind_dot);

    typ = p->lit;

  } else {

    if (warn && string_ne(p->mod, tos3("ui"))) {

      Parser_warn(p, tos3("use `&Foo` instead of `*Foo`"));
    };

    if (Parser_peek(&/* ? */ *p) == main__TokenKind_dot) {

      if (!p->builtin_mod &&
          FileImportTable_known_alias(&/* ? */ p->import_table, typ)) {

        string mod =
            FileImportTable_resolve_alias(&/* ? */ p->import_table, typ);

        if (string_contains(mod, tos3("."))) {

          typ = string_replace(mod, tos3("."), tos3("_dot_"));
        };
      };

      Parser_next(p);

      Parser_check(p, main__TokenKind_dot);

      typ = string_add(typ, _STR("__%.*s", p->lit.len, p->lit.str));
    };

    Type t = Table_find_type(&/* ? */ *p->table, typ);

    if (string_eq(t.name, tos3("")) && !p->builtin_mod) {

      if (!string_contains(typ, tos3("array_")) &&
          string_ne(p->mod, tos3("main")) &&
          !string_contains(typ, tos3("__")) &&
          !string_starts_with(typ, tos3("["))) {

        typ = Parser_prepend_mod(&/* ? */ *p, typ);
      };

      t = Table_find_type(&/* ? */ *p->table, typ);

      if (string_eq(t.name, tos3("")) && !p->pref->translated &&
          !Parser_first_pass(&/* ? */ *p) &&
          !string_starts_with(typ, tos3("["))) {

        println(tos3("get_type() bad type"));

        Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
      };
    };
  };

  if (string_eq(typ, tos3("void"))) {

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

  if (is_question) {

    typ = _STR("Option_%.*s", typ.len, typ.str);

    Table_register_type_with_parent(p->table, typ, tos3("Option"));
  };

  if (string_eq(typ, tos3("byteptr"))) {

    return tos3("byte*");
  };

  if (string_eq(typ, tos3("voidptr"))) {

    return tos3("void*");
  };

  if (string_last_index(typ, tos3("__")) > string_index(typ, tos3("__"))) {

    Parser_error(p, _STR("2 __ in gettype(): typ=\"%.*s\"", typ.len, typ.str));
  };

  return typ;
}
void Parser_print_tok(Parser *p) {

  if (p->tok == main__TokenKind_name) {

    println(p->lit);

    return;
  };

  if (p->tok == main__TokenKind_str) {

    printf("\"%.*s\"\n", p->lit.len, p->lit.str);

    return;
  };

  println(TokenKind_str(p->tok));
}
string Parser_statements(Parser *p) {

  string typ = Parser_statements_no_rcbr(p);

  if (!p->inside_if_expr) {

    Parser_genln(p, tos3("}"));
  };

  return typ;
}
string Parser_statements_no_rcbr(Parser *p) {

  Parser_open_scope(p);

  if (!p->inside_if_expr) {

    Parser_genln(p, tos3(""));
  };

  int i = 0;

  string last_st_typ = tos3("");

  while (p->tok != main__TokenKind_rcbr && p->tok != main__TokenKind_eof &&
         p->tok != main__TokenKind_key_case &&
         p->tok != main__TokenKind_key_default &&
         Parser_peek(&/* ? */ *p) != main__TokenKind_arrow) {

    last_st_typ = Parser_statement(p, 1);

    if (!p->inside_if_expr) {

      Parser_genln(p, tos3(""));

      Parser_fgenln(p, tos3(""));
    };

    i++;

    if (i > 50000) {

      CGen_save(p->cgen);

      Parser_error(p, _STR("more than 50 000 statements in function `%.*s`",
                           p->cur_fn.name.len, p->cur_fn.name.str));
    };
  };

  if (p->tok != main__TokenKind_key_case &&
      p->tok != main__TokenKind_key_default &&
      Parser_peek(&/* ? */ *p) != main__TokenKind_arrow) {

    Parser_check(p, main__TokenKind_rcbr);

  } else {
  };

  Parser_close_scope(p);

  return last_st_typ;
}
void Parser_close_scope(Parser *p) {

  int i = p->var_idx - 1;

  for (; i >= 0; i--) {

    Var v = (*(Var *)array_get(p->local_vars, i));

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

        Parser_genln(p, _STR("%.*s(%.*s); // close_scope free", free_fn.len,
                             free_fn.str, v.name.len, v.name.str));
      };
    };
  };

  if (string_ne(*(string *)array_last(p->cur_fn.defer_text), tos3(""))) {

    Parser_genln(p, *(string *)array_last(p->cur_fn.defer_text));
  };

  p->cur_fn.scope_level--;

  p->cur_fn.defer_text =
      array_left(p->cur_fn.defer_text, p->cur_fn.scope_level + 1);

  p->var_idx = i + 1;
}
void Parser_genln(Parser *p, string s) { CGen_genln(p->cgen, s); }
void Parser_gen(Parser *p, string s) { CGen_gen(p->cgen, s); }
string Parser_statement(Parser *p, bool add_semi) {

  if (p->returns && !p->is_vweb) {

    Parser_error(p, tos3("unreachable code"));
  };

  p->cgen->is_tmp = 0;

  TokenKind tok = p->tok;

  string q = tos3("");

  if (tok == main__TokenKind_name) { /* case */

    TokenKind next = Parser_peek(&/* ? */ *p);

    if (Parser_peek(&/* ? */ *p) == main__TokenKind_colon) {

      Parser_fmt_dec(p);

      string label = Parser_check_name(p);

      Parser_fmt_inc(p);

      Parser_genln(p, string_add(label, tos3(":")));

      Parser_check(p, main__TokenKind_colon);

      return tos3("");

    } else if (Parser_peek(&/* ? */ *p) == main__TokenKind_decl_assign ||
               Parser_peek(&/* ? */ *p) == main__TokenKind_comma) {

      Parser_var_decl(p);

    } else if (string_eq(p->lit, tos3("_")) &&
               Parser_peek(&/* ? */ *p) == main__TokenKind_assign) {

      Parser_gen_blank_identifier_assign(p);

    } else {

      if (string_eq(p->lit, tos3("panic")) || string_eq(p->lit, tos3("exit"))) {

        p->returns = 1;
      };

      q = Parser_bool_expression(p);
    };

  } else if (tok == main__TokenKind_key_goto) { /* case */

    Parser_check(p, main__TokenKind_key_goto);

    Parser_fgen(p, tos3(" "));

    string label = Parser_check_name(p);

    Parser_genln(p, _STR("goto %.*s;", label.len, label.str));

    return tos3("");

  } else if (tok == main__TokenKind_key_defer) { /* case */

    Parser_defer_st(p);

    return tos3("");

  } else if (tok == main__TokenKind_hash) { /* case */

    Parser_chash(p);

    return tos3("");

  } else if (tok == main__TokenKind_dollar) { /* case */

    Parser_comp_time(p);

  } else if (tok == main__TokenKind_key_if) { /* case */

    Parser_if_st(p, 0, 0);

  } else if (tok == main__TokenKind_key_for) { /* case */

    Parser_for_st(p);

  } else if (tok == main__TokenKind_key_switch) { /* case */

    Parser_switch_statement(p);

  } else if (tok == main__TokenKind_key_match) { /* case */

    Parser_match_statement(p, 0);

  } else if (tok == main__TokenKind_key_mut ||
             tok == main__TokenKind_key_static) { /* case */

    Parser_var_decl(p);

  } else if (tok == main__TokenKind_key_return) { /* case */

    Parser_return_st(p);

  } else if (tok == main__TokenKind_lcbr) { /* case */

    Parser_check(p, main__TokenKind_lcbr);

    Parser_genln(p, tos3("{"));

    Parser_statements(p);

    return tos3("");

  } else if (tok == main__TokenKind_key_continue) { /* case */

    if (p->for_expr_cnt == 0) {

      Parser_error(p, tos3("`continue` statement outside `for`"));
    };

    Parser_genln(p, tos3("continue"));

    Parser_check(p, main__TokenKind_key_continue);

  } else if (tok == main__TokenKind_key_break) { /* case */

    if (p->for_expr_cnt == 0) {

      Parser_error(p, tos3("`break` statement outside `for`"));
    };

    Parser_genln(p, tos3("break"));

    Parser_check(p, main__TokenKind_key_break);

  } else if (tok == main__TokenKind_key_go) { /* case */

    Parser_go_statement(p);

  } else if (tok == main__TokenKind_key_assert) { /* case */

    Parser_assert_statement(p);

  } else { // default:

    string typ = Parser_expression(p);

    if (p->inside_if_expr) {

    } else {

      Parser_genln(p, tos3("; "));
    };

    return typ;
  };

  if (p->inside_if_expr && p->tok != main__TokenKind_rcbr) {

    Parser_gen(p, tos3(", "));
  };

  if (add_semi && !p->inside_if_expr) {

    Parser_genln(p, tos3(";"));
  };

  return q;
}
void Parser_assign_statement(Parser *p, Var v, int ph, bool is_map) {

  int errtok = Parser_cur_tok_index(&/* ? */ *p);

  bool is_vid = Parser_fileis(&/* ? */ *p, tos3("vid"));

  TokenKind tok = p->tok;

  if (!v.is_mut && !p->pref->translated && !v.is_global && !is_vid) {

    if (v.is_arg) {

      if (p->cur_fn.args.len > 0 &&
          string_eq((*(Var *)array_get(p->cur_fn.args, 0)).name, v.name)) {

        printf("make the receiver `%.*s` mutable:\nfn (%.*s mut %.*s) %.*s "
               "(...) {\n\n",
               v.name.len, v.name.str, v.name.len, v.name.str, v.typ.len,
               v.typ.str, p->cur_fn.name.len, p->cur_fn.name.str);
      };
    };

    Parser_error(p, _STR("`%.*s` is immutable", v.name.len, v.name.str));
  };

  if (!v.is_changed) {

    Parser_mark_var_changed(p, v);
  };

  bool is_str = string_eq(v.typ, tos3("string"));

  bool is_ustr = string_eq(v.typ, tos3("ustring"));

  if (tok == main__TokenKind_assign) { /* case */

    if (!is_map && !p->is_empty_c_struct_init) {

      Parser_gen(p, tos3(" = "));
    };

  } else if (tok == main__TokenKind_plus_assign) { /* case */

    if (is_str && !p->is_js) {

      Parser_gen(p, _STR("= string_add(%.*s, ", v.name.len, v.name.str));

    } else if (is_ustr) {

      Parser_gen(p, _STR("= ustring_add(%.*s, ", v.name.len, v.name.str));

    } else {

      Parser_gen(p, tos3(" += "));
    };

  } else { // default:

    Parser_gen(
        p, string_add(string_add(tos3(" "), TokenKind_str(p->tok)), tos3(" ")));
  };

  Parser_fspace(p);

  Parser_fgen(p, TokenKind_str(tok));

  Parser_fspace(p);

  Parser_next(p);

  int pos = p->cgen->cur_line.len;

  string expr_type = Parser_bool_expression(p);

  if (string_starts_with(p->assigned_type, tos3("Option_")) &&
      string_eq(expr_type,
                string_right(p->assigned_type, tos3("Option_").len))) {

    string expr = string_right(p->cgen->cur_line, pos);

    string left = string_left(p->cgen->cur_line, pos);

    string typ = string_replace(expr_type, tos3("Option_"), tos3(""));

    CGen_resetln(p->cgen,
                 string_add(left, _STR("opt_ok(%.*s, sizeof(%.*s))", expr.len,
                                       expr.str, typ.len, typ.str)));

  } else if (string_at(expr_type, 0) == '[') {

    string expr = string_all_before(
        string_all_after(string_right(p->cgen->cur_line, pos), tos3("{")),
        tos3("}"));

    string left =
        string_all_before(string_left(p->cgen->cur_line, pos), tos3("="));

    string cline_pos = string_right(p->cgen->cur_line, pos);

    string etype = string_all_before(cline_pos, tos3(" {"));

    if (string_ne(p->assigned_type, p->expected_type)) {

      Parser_error_with_token_index(
          p,
          _STR("incompatible types: %.*s != %.*s", p->assigned_type.len,
               p->assigned_type.str, p->expected_type.len,
               p->expected_type.str),
          errtok);
    };

    CGen_resetln(p->cgen, _STR("memcpy(& %.*s, %.*s{%.*s}, sizeof( %.*s ) );",
                               left.len, left.str, etype.len, etype.str,
                               expr.len, expr.str, left.len, left.str));

  } else if (!p->builtin_mod &&
             !Parser_check_types_no_throw(p, expr_type, p->assigned_type)) {

    Parser_error_with_token_index(
        p,
        _STR("cannot use type `%.*s` as type `%.*s` in assignment",
             expr_type.len, expr_type.str, p->assigned_type.len,
             p->assigned_type.str),
        errtok);
  };

  if ((is_str || is_ustr) && tok == main__TokenKind_plus_assign && !p->is_js) {

    Parser_gen(p, tos3(")"));
  };

  p->assigned_type = tos3("");

  if (!v.is_used) {

    Parser_mark_var_used(p, v);
  };
}
void Parser_var_decl(Parser *p) {

  p->is_alloc = 0;

  bool is_mut = p->tok == main__TokenKind_key_mut ||
                p->prev_tok == main__TokenKind_key_for;

  bool is_static = p->tok == main__TokenKind_key_static;

  if (p->tok == main__TokenKind_key_mut) {

    Parser_check(p, main__TokenKind_key_mut);

    Parser_fspace(p);
  };

  if (p->tok == main__TokenKind_key_static) {

    Parser_check(p, main__TokenKind_key_static);

    Parser_fspace(p);
  };

  array_int var_token_idxs = new_array_from_c_array(
      1, 1, sizeof(int),
      EMPTY_ARRAY_OF_ELEMS(int, 1){Parser_cur_tok_index(&/* ? */ *p)});

  array_bool var_mut = new_array_from_c_array(
      1, 1, sizeof(bool), EMPTY_ARRAY_OF_ELEMS(bool, 1){is_mut});

  array_string var_names = new_array_from_c_array(
      1, 1, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 1){Parser_check_name(p)});

  Scanner_validate_var_name(&/* ? */ *p->scanner,
                            (*(string *)array_get(var_names, 0)));

  int new_vars = 0;

  if (string_ne((*(string *)array_get(var_names, 0)), tos3("_")) &&
      !Parser_known_var(p, (*(string *)array_get(var_names, 0)))) {

    new_vars++;
  };

  while (p->tok == main__TokenKind_comma) {

    Parser_check(p, main__TokenKind_comma);

    if (p->tok == main__TokenKind_key_mut) {

      Parser_check(p, main__TokenKind_key_mut);

      _PUSH(&var_mut, (/*typ = array_bool   tmp_typ=bool*/ 1), tmp158, bool);

    } else {

      _PUSH(&var_mut, (/*typ = array_bool   tmp_typ=bool*/ 0), tmp159, bool);
    };

    _PUSH(&var_token_idxs,
          (/*typ = array_int   tmp_typ=int*/ Parser_cur_tok_index(&/* ? */ *p)),
          tmp160, int);

    string var_name = Parser_check_name(p);

    Scanner_validate_var_name(&/* ? */ *p->scanner, var_name);

    if (string_ne(var_name, tos3("_")) && !Parser_known_var(p, var_name)) {

      new_vars++;
    };

    _PUSH(&var_names, (/*typ = array_string   tmp_typ=string*/ var_name),
          tmp162, string);
  };

  bool is_assign = p->tok == main__TokenKind_assign;

  bool is_decl_assign = p->tok == main__TokenKind_decl_assign;

  if (is_assign) {

    Parser_check_space(p, main__TokenKind_assign);

  } else if (is_decl_assign) {

    Parser_check_space(p, main__TokenKind_decl_assign);

  } else {

    Parser_error(p, tos3("expected `=` or `:=`"));
  };

  if (is_decl_assign && var_names.len == 1 &&
      string_eq((*(string *)array_get(var_names, 0)), tos3("_"))) {

    Parser_error_with_token_index(p, tos3("use `=` instead of `:=`"),
                                  *(int *)array_last(var_token_idxs));
  };

  p->var_decl_name = (var_names.len > 1)
                         ? (string_add(tos3("_V_mret_"),
                                       array_string_join(var_names, tos3("_"))))
                         : ((*(string *)array_get(var_names, 0)));

  string t = Parser_gen_var_decl(p, p->var_decl_name, is_static);

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

    Parser_error_with_token_index(
        p,
        _STR("assignment mismatch: %d variables but `%.*s` returns %d values",
             var_names.len, mr_fn.len, mr_fn.str, var_types.len),
        *(int *)array_last(var_token_idxs));
  };

  array_string tmp172 = var_names;
  for (int i = 0; i < tmp172.len; i++) {
    string var_name = ((string *)tmp172.data)[i];

    int var_token_idx = (*(int *)array_get(var_token_idxs, i));

    bool var_is_mut = (*(bool *)array_get(var_mut, i));

    string var_type = (*(string *)array_get(var_types, i));

    bool known_var = Parser_known_var(p, var_name);

    if (string_eq(var_name, tos3("_"))) {

      if (var_is_mut) {

        Parser_error_with_token_index(p, tos3("`mut` has no effect here"),
                                      var_token_idx - 1);
      };

      continue;
    };

    if (is_decl_assign && known_var) {

      Parser_error_with_token_index(
          p, _STR("redefinition of `%.*s`", var_name.len, var_name.str),
          var_token_idx);
    };

    if (known_var && var_is_mut) {

      Parser_error_with_token_index(
          p,
          _STR("cannot specify mutability for existing var `%.*s`, only for "
               "new vars",
               var_name.len, var_name.str),
          var_token_idx);
    };

    if (is_assign && !known_var) {

      string suggested =
          Parser_find_misspelled_local_var(&/* ? */ *p, var_name, 50);

      if (string_ne(suggested, tos3(""))) {

        Parser_error_with_token_index(
            p,
            _STR("undefined: `%.*s`. did you mean:%.*s", var_name.len,
                 var_name.str, suggested.len, suggested.str),
            var_token_idx);
      };

      Parser_error_with_token_index(
          p, _STR("undefined: `%.*s`.", var_name.len, var_name.str),
          var_token_idx);
    };

    if (var_name.len > 1 && main__contains_capital(var_name)) {

      Parser_error_with_token_index(
          p,
          tos3("variable names cannot contain uppercase letters, use "
               "snake_case instead"),
          var_token_idx);
    };

    if (var_names.len > 1) {

      Parser_gen(p, tos3(";\n"));

      if (known_var) {

        Option_Var tmp184 = Parser_find_var(&/* ? */ *p, var_name);
        if (!tmp184.ok) {
          string err = tmp184.error;

          Parser_error_with_token_index(
              p, _STR("cannot find `%.*s`", var_name.len, var_name.str),
              var_token_idx);

          break;
        }
        Var v = *(Var *)tmp184.data;
        ;

        Parser_check_types_with_token_index(p, var_type, v.typ, var_token_idx);

        if (!v.is_mut) {

          Parser_error_with_token_index(
              p, _STR("`%.*s` is immutable", v.name.len, v.name.str),
              var_token_idx);
        };

        Parser_mark_var_used(p, v);

        Parser_mark_var_changed(p, v);

        Parser_gen(p, _STR("%.*s = %.*s.var_%d", var_name.len, var_name.str,
                           p->var_decl_name.len, p->var_decl_name.str, i));

        continue;
      };

      Parser_gen(p, _STR("%.*s %.*s = %.*s.var_%d", var_type.len, var_type.str,
                         var_name.len, var_name.str, p->var_decl_name.len,
                         p->var_decl_name.str, i));
    };

    Parser_register_var(
        p,
        (Var){
            .name = var_name,
            .typ = var_type,
            .is_mut = var_is_mut,
            .is_alloc =
                p->is_alloc || string_starts_with(var_type, tos3("array_")),
            .line_nr = (*(Token *)array_get(p->tokens, var_token_idx)).line_nr,
            .token_idx = var_token_idx,
            .idx = 0,
            .is_arg = 0,
            .is_const = 0,
            .args = new_array(0, 1, sizeof(Var)),
            .attr = tos((byte *)"", 0),
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .parent_fn = tos((byte *)"", 0),
            .mod = tos((byte *)"", 0),
            .is_global = 0,
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
        });
  };

  p->var_decl_name = tos3("");

  p->is_empty_c_struct_init = 0;
}
string Parser_bool_expression(Parser *p) {

  TokenKind tok = p->tok;

  string typ = Parser_bterm(p);

  bool got_and = 0;

  bool got_or = 0;

  while (p->tok == main__TokenKind_and ||
         p->tok == main__TokenKind_logical_or) {

    if (p->tok == main__TokenKind_and) {

      got_and = 1;

      if (got_or) {

        Parser_error(p, main__and_or_error);
      };
    };

    if (p->tok == main__TokenKind_logical_or) {

      got_or = 1;

      if (got_and) {

        Parser_error(p, main__and_or_error);
      };
    };

    if (p->is_sql) {

      if (p->tok == main__TokenKind_and) {

        Parser_gen(p, tos3(" and "));

      } else if (p->tok == main__TokenKind_logical_or) {

        Parser_gen(p, tos3(" or "));
      };

    } else {

      Parser_gen(p, _STR(" %.*s ", TokenKind_str(p->tok).len,
                         TokenKind_str(p->tok).str));
    };

    Parser_check_space(p, p->tok);

    Parser_check_types(p, Parser_bterm(p), typ);
  };

  if (string_eq(typ, tos3(""))) {

    println(tos3("curline:"));

    println(p->cgen->cur_line);

    println(TokenKind_str(tok));

    Parser_error(p, tos3("expr() returns empty type"));
  };

  return typ;
}
string Parser_bterm(Parser *p) {

  int ph = CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = Parser_expression(p);

  p->expected_type = typ;

  bool is_str = string_eq(typ, tos3("string")) && !p->is_sql;

  bool is_ustr = string_eq(typ, tos3("ustring"));

  bool is_float = string_eq(typ, tos3("f64")) || string_eq(typ, tos3("f32"));

  string expr_type = typ;

  TokenKind tok = p->tok;

  if (tok == main__TokenKind_eq || tok == main__TokenKind_gt ||
      tok == main__TokenKind_lt || tok == main__TokenKind_le ||
      tok == main__TokenKind_ge || tok == main__TokenKind_ne) {

    Parser_fgen(p, _STR(" %.*s ", TokenKind_str(p->tok).len,
                        TokenKind_str(p->tok).str));

    if ((is_float || is_str || is_ustr) && !p->is_js) {

      Parser_gen(p, tos3(","));

    } else if (p->is_sql && tok == main__TokenKind_eq) {

      Parser_gen(p, tos3("="));

    } else {

      Parser_gen(p, TokenKind_str(tok));
    };

    Parser_next(p);

    if (p->is_sql) {

      p->sql_i++;

      Parser_gen(p, string_add(tos3("$"), int_str(p->sql_i)));

      CGen_start_cut(p->cgen);

      Parser_check_types(p, Parser_expression(p), typ);

      string sql_param = CGen_cut(p->cgen);

      _PUSH(&p->sql_params, (/*typ = array_string   tmp_typ=string*/ sql_param),
            tmp199, string);

      _PUSH(&p->sql_types, (/*typ = array_string   tmp_typ=string*/ typ),
            tmp200, string);

    } else {

      Parser_check_types(p, Parser_expression(p), typ);
    };

    typ = tos3("bool");

    if (is_str && !p->is_js) {

      Parser_gen(p, tos3(")"));

      if (tok == main__TokenKind_eq) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("string_eq("));

      } else if (tok == main__TokenKind_ne) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("string_ne("));

      } else if (tok == main__TokenKind_le) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("string_le("));

      } else if (tok == main__TokenKind_ge) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("string_ge("));

      } else if (tok == main__TokenKind_gt) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("string_gt("));

      } else if (tok == main__TokenKind_lt) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("string_lt("));
      };
    };

    if (is_ustr) {

      Parser_gen(p, tos3(")"));

      if (tok == main__TokenKind_eq) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("ustring_eq("));

      } else if (tok == main__TokenKind_ne) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("ustring_ne("));

      } else if (tok == main__TokenKind_le) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("ustring_le("));

      } else if (tok == main__TokenKind_ge) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("ustring_ge("));

      } else if (tok == main__TokenKind_gt) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("ustring_gt("));

      } else if (tok == main__TokenKind_lt) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos3("ustring_lt("));
      };
    };

    if (is_float) {

      Parser_gen(p, tos3(")"));

      if (tok == main__TokenKind_eq) { /* case */

        CGen_set_placeholder(p->cgen, ph,
                             _STR("%.*s_eq(", expr_type.len, expr_type.str));

      } else if (tok == main__TokenKind_ne) { /* case */

        CGen_set_placeholder(p->cgen, ph,
                             _STR("%.*s_ne(", expr_type.len, expr_type.str));

      } else if (tok == main__TokenKind_le) { /* case */

        CGen_set_placeholder(p->cgen, ph,
                             _STR("%.*s_le(", expr_type.len, expr_type.str));

      } else if (tok == main__TokenKind_ge) { /* case */

        CGen_set_placeholder(p->cgen, ph,
                             _STR("%.*s_ge(", expr_type.len, expr_type.str));

      } else if (tok == main__TokenKind_gt) { /* case */

        CGen_set_placeholder(p->cgen, ph,
                             _STR("%.*s_gt(", expr_type.len, expr_type.str));

      } else if (tok == main__TokenKind_lt) { /* case */

        CGen_set_placeholder(p->cgen, ph,
                             _STR("%.*s_lt(", expr_type.len, expr_type.str));
      };
    };
  };

  return typ;
}
string Parser_name_expr(Parser *p) {

  p->has_immutable_field = 0;

  p->is_const_literal = 0;

  int ph = CGen_add_placeholder(&/* ? */ *p->cgen);

  bool ptr = p->tok == main__TokenKind_amp;

  bool deref = p->tok == main__TokenKind_mul;

  if (ptr || deref) {

    Parser_next(p);
  };

  string name = p->lit;

  if (string_eq(name, tos3("r")) &&
      Parser_peek(&/* ? */ *p) == main__TokenKind_str) {

    Parser_string_expr(p);

    return tos3("string");
  };

  Parser_fgen(p, name);

  string orig_name = name;

  bool is_c = string_eq(name, tos3("C")) &&
              Parser_peek(&/* ? */ *p) == main__TokenKind_dot;

  bool is_c_struct_init = is_c && ptr;

  if (is_c) {

    Parser_next(p);

    Parser_check(p, main__TokenKind_dot);

    name = p->lit;

    Parser_fgen(p, name);

    if (!is_c_struct_init && Parser_peek(&/* ? */ *p) == main__TokenKind_lcbr) {

      is_c_struct_init = 1;
    };
  };

  if (p->tok == main__TokenKind_dot) {

    Type T = Parser_find_type(&/* ? */ *p, p->expected_type);

    if (T.cat == main__TypeCategory_enum_) {

      Parser_check(p, main__TokenKind_dot);

      string val = Parser_check_name(p);

      if (!Type_has_enum_val(&/* ? */ T, val)) {

        Parser_error(p, _STR("enum `%.*s` does not have value `%.*s`",
                             T.name.len, T.name.str, val.len, val.str));
      };

      Parser_gen(p,
                 string_add(string_add(string_add(string_add(T.mod, tos3("__")),
                                                  p->expected_type),
                                       tos3("_")),
                            val));
    };

    return p->expected_type;
  };

  while (1) {

    Option_Var tmp210 = Parser_find_var_check_new_var(&/* ? */ *p, name);
    if (!tmp210.ok) {
      string err = tmp210.error;

      break;
    }
    Var v = *(Var *)tmp210.data;
    ;

    if (string_eq(name, tos3("_"))) {

      Parser_error(p, tos3("cannot use `_` as value"));
    };

    if (ptr) {

      Parser_gen(p, tos3("&"));

    } else if (deref) {

      Parser_gen(p, tos3("*"));
    };

    if (p->pref->autofree && string_eq(v.typ, tos3("string")) && v.is_arg &&
        string_eq(p->assigned_type, tos3("string"))) {

      Parser_warn(p, string_add(tos3("setting moved "), v.typ));

      Parser_mark_arg_moved(p, v);
    };

    string typ = Parser_var_expr(p, v);

    if (deref) {

      if (!string_contains(typ, tos3("*")) &&
          !string_ends_with(typ, tos3("ptr"))) {

        printf("name=\"%.*s\", t=%.*s\n", name.len, name.str, v.typ.len,
               v.typ.str);

        Parser_error(p, _STR("dereferencing requires a pointer, but got `%.*s`",
                             typ.len, typ.str));
      };

      typ = string_replace(typ, tos3("ptr"), tos3(""));

      typ = string_replace(typ, tos3("*"), tos3(""));

    } else if (ptr) {

      typ = string_add(typ, tos3("*"));
    };

    if (p->inside_return_expr) {

      Parser_mark_var_returned(p, v);
    };

    return typ;
  };

  if (Parser_peek(&/* ? */ *p) == main__TokenKind_dot &&
      ((string_eq(name, p->mod) && Table_known_mod(&/* ? */ *p->table, name)) ||
       FileImportTable_known_alias(&/* ? */ p->import_table, name)) &&
      !is_c) {

    string mod = name;

    if (string_ne(name, p->mod) &&
        FileImportTable_known_alias(&/* ? */ p->import_table, name)) {

      FileImportTable_register_used_import(&/* ? */ p->import_table, name);

      mod = string_replace(
          FileImportTable_resolve_alias(&/* ? */ p->import_table, name),
          tos3("."), tos3("_dot_"));
    };

    Parser_next(p);

    Parser_check(p, main__TokenKind_dot);

    name = p->lit;

    Parser_fgen(p, name);

    name = main__prepend_mod(mod, name);

  } else if (!Table_known_type(&/* ? */ *p->table, name) &&
             !Table_known_fn(&/* ? */ *p->table, name) &&
             !Table_known_const(&/* ? */ *p->table, name) && !is_c) {

    name = Parser_prepend_mod(&/* ? */ *p, name);
  };

  while (1) {

    Option_Var tmp213 = Parser_find_var_check_new_var(&/* ? */ *p, name);
    if (!tmp213.ok) {
      string err = tmp213.error;

      break;
    }
    Var v = *(Var *)tmp213.data;
    ;

    if (string_eq(name, tos3("_"))) {

      Parser_error(p, tos3("cannot use `_` as value"));
    };

    if (ptr) {

      Parser_gen(p, tos3("&"));

    } else if (deref) {

      Parser_gen(p, tos3("*"));
    };

    if (p->pref->autofree && string_eq(v.typ, tos3("string")) && v.is_arg &&
        string_eq(p->assigned_type, tos3("string"))) {

      Parser_warn(p, string_add(tos3("setting moved "), v.typ));

      Parser_mark_arg_moved(p, v);
    };

    string typ = Parser_var_expr(p, v);

    if (deref) {

      if (!string_contains(typ, tos3("*")) &&
          !string_ends_with(typ, tos3("ptr"))) {

        printf("name=\"%.*s\", t=%.*s\n", name.len, name.str, v.typ.len,
               v.typ.str);

        Parser_error(p, _STR("dereferencing requires a pointer, but got `%.*s`",
                             typ.len, typ.str));
      };

      typ = string_replace(typ, tos3("ptr"), tos3(""));

      typ = string_replace(typ, tos3("*"), tos3(""));

    } else if (ptr) {

      typ = string_add(typ, tos3("*"));
    };

    if (p->inside_return_expr) {

      Parser_mark_var_returned(p, v);
    };

    return typ;
  };

  if (Table_known_type(&/* ? */ *p->table, name)) {

    if (!is_c &&
        (Parser_peek(&/* ? */ *p) == main__TokenKind_lpar ||
         (deref && Parser_peek(&/* ? */ *p) == main__TokenKind_rpar))) {

      if (deref) {

        name = string_add(name, tos3("*"));

      } else if (ptr) {

        name = string_add(name, tos3("*"));
      };

      Parser_gen(p, tos3("("));

      string typ = name;

      Parser_cast(p, name);

      Parser_gen(p, tos3(")"));

      while (p->tok == main__TokenKind_dot) {

        typ = Parser_dot(p, typ, ph);
      };

      return typ;

    } else if (Parser_peek(&/* ? */ *p) == main__TokenKind_dot) {

      Type enum_type = Table_find_type(&/* ? */ *p->table, name);

      if (enum_type.cat != main__TypeCategory_enum_) {

        Parser_error(p, _STR("`%.*s` is not an enum", name.len, name.str));
      };

      Parser_next(p);

      Parser_check(p, main__TokenKind_dot);

      string val = p->lit;

      Parser_gen(p, string_add(string_add(string_add(string_add(enum_type.mod,
                                                                tos3("__")),
                                                     enum_type.name),
                                          tos3("_")),
                               val));

      Parser_next(p);

      return enum_type.name;

    } else if (Parser_peek(&/* ? */ *p) == main__TokenKind_lcbr) {

      if (ptr) {

        name = string_add(name, tos3("*"));
      };

      if (string_eq(name, tos3("T"))) {

        name = p->cur_gen_type;
      };

      p->is_c_struct_init = is_c_struct_init;

      return Parser_struct_init(p, name);
    };
  };

  if (is_c) {

    if (Parser_peek(&/* ? */ *p) != main__TokenKind_lpar) {

      Parser_gen(p, name);

      Parser_next(p);

      return tos3("int");
    };

    Fn f = (Fn){.name = name,
                .is_c = 1,
                .mod = tos((byte *)"", 0),
                .args = new_array(0, 1, sizeof(Var)),
                .is_interface = 0,
                .scope_level = 0,
                .typ = tos((byte *)"", 0),
                .receiver_typ = tos((byte *)"", 0),
                .is_public = 0,
                .is_method = 0,
                .returns_error = 0,
                .is_decl = 0,
                .defer_text = new_array(0, 1, sizeof(string)),
                .fn_name_token_idx = 0};

    p->is_c_fn_call = 1;

    Parser_fn_call(p, f, 0, tos3(""), tos3(""));

    p->is_c_fn_call = 0;

    Option_Fn tmp219 = Table_find_fn(&/* ? */ *p->table, name);
    if (!tmp219.ok) {
      string err = tmp219.error;

      if (0) {

        Parser_warn(p, string_add(tos3("\ndefine imported C function with "),
                                  _STR("`fn C.%.*s([args]) [return_type]`\n",
                                       name.len, name.str)));
      };

      return tos3("void*");
    }
    Fn cfn = *(Fn *)tmp219.data;
    ;

    return cfn.typ;
  };

  while (1) {

    Option_Var tmp220 = Table_find_const(&/* ? */ *p->table, name);
    if (!tmp220.ok) {
      string err = tmp220.error;

      break;
    }
    Var c = *(Var *)tmp220.data;
    ;

    if (ptr && !c.is_global) {

      Parser_error(p, _STR("cannot take the address of constant `%.*s`",
                           c.name.len, c.name.str));

    } else if (ptr && c.is_global) {

      Parser_gen(p, tos3("& /*const*/ "));
    };

    string typ = Parser_var_expr(p, c);

    if (ptr) {

      typ = string_add(typ, tos3("*"));
    };

    return typ;
  };

  Option_Fn tmp222 = Table_find_fn(&/* ? */ *p->table, name);
  if (!tmp222.ok) {
    string err = tmp222.error;

    if (!Parser_first_pass(&/* ? */ *p)) {

      if (p->v_script) {
      };

      string suggested = Parser_identify_typo(
          &/* ? */ *p, name,
          &/*112 EXP:"FileImportTable*" GOT:"FileImportTable" */ p
               ->import_table);

      if (string_ne(suggested, tos3(""))) {

        Parser_error(p, _STR("undefined: `%.*s`. did you mean:%.*s", name.len,
                             name.str, suggested.len, suggested.str));
      };

      if (Table_known_mod(&/* ? */ *p->table, orig_name) ||
          FileImportTable_known_alias(&/* ? */ p->import_table, orig_name)) {

        name = string_replace(string_replace(name, tos3("__"), tos3(".")),
                              tos3("_dot_"), tos3("."));

        Parser_error(p, _STR("undefined: `%.*s`", name.len, name.str));

      } else {

        Parser_error(p,
                     _STR("undefined: `%.*s`", orig_name.len, orig_name.str));
      };

    } else {

      Parser_next(p);

      return tos3("void");
    };

    return tos3("void");
  }
  Fn f = *(Fn *)tmp222.data;
  ;

  TokenKind peek = Parser_peek(&/* ? */ *p);

  if (peek != main__TokenKind_lpar && peek != main__TokenKind_lt) {

    Type fn_typ = (Type){.name = Fn_typ_str(&/* ? */ f),
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

    Parser_gen(p, Table_fn_gen_name(p->table, &/*112 EXP:"Fn*" GOT:"Fn" */ f));

    Parser_next(p);

    return Fn_typ_str(&/* ? */ f);
  };

  if (string_eq(f.typ, tos3("void")) && !p->inside_if_expr) {
  };

  Parser_fn_call(p, f, 0, tos3(""), tos3(""));

  if (p->tok == main__TokenKind_dot) {

    string typ = tos3("");

    while (p->tok == main__TokenKind_dot) {

      typ = Parser_dot(p, f.typ, ph);
    };

    return typ;
  };

  if (string_ends_with(f.typ, tos3("*"))) {

    p->is_alloc = 1;
  };

  return f.typ;
}
string Parser_var_expr(Parser *p, Var v) {

  if (!v.is_const) {

    Parser_mark_var_used(p, v);
  };

  int fn_ph = CGen_add_placeholder(&/* ? */ *p->cgen);

  p->expr_var = v;

  Parser_gen(p, Table_var_cgen_name(&/* ? */ *p->table, v.name));

  Parser_next(p);

  string typ = v.typ;

  if (string_starts_with(typ, tos3("fn ")) && p->tok == main__TokenKind_lpar) {

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    Parser_gen(p, tos3("("));

    Parser_fn_call_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ T.func);

    Parser_gen(p, tos3(")"));

    typ = T.func.typ;
  };

  if (p->tok == main__TokenKind_lsbr) {

    typ = Parser_index_expr(p, typ, fn_ph);
  };

  while (p->tok == main__TokenKind_dot) {

    if (Parser_peek(&/* ? */ *p) == main__TokenKind_key_select) {

      Parser_next(p);

      return Parser_select_query(p, fn_ph);
    };

    if (string_eq(typ, tos3("pg__DB")) &&
        !Parser_fileis(&/* ? */ *p, tos3("pg.v")) &&
        Parser_peek(&/* ? */ *p) == main__TokenKind_name) {

      Parser_next(p);

      Parser_insert_query(p, fn_ph);

      return tos3("void");
    };

    typ = Parser_dot(p, typ, fn_ph);

    if (p->tok == main__TokenKind_lsbr) {
    };
  };

  if (p->tok == main__TokenKind_inc || p->tok == main__TokenKind_dec) {

    if (!v.is_mut && !v.is_arg && !p->pref->translated) {

      Parser_error(p, _STR("`%.*s` is immutable", v.name.len, v.name.str));
    };

    if (!v.is_changed) {

      Parser_mark_var_changed(p, v);
    };

    if (string_ne(typ, tos3("int"))) {

      if (!p->pref->translated && !main__is_number_type(typ)) {

        Parser_error(
            p, _STR("cannot ++/-- value of type `%.*s`", typ.len, typ.str));
      };
    };

    Parser_gen(p, TokenKind_str(p->tok));

    Parser_fgen(p, TokenKind_str(p->tok));

    Parser_next(p);

    if (p->pref->translated) {

    } else {

      return tos3("void");
    };
  };

  typ = Parser_index_expr(p, typ, fn_ph);

  if (p->tok == main__TokenKind_dot) {

    while (p->tok == main__TokenKind_dot) {

      typ = Parser_dot(p, typ, fn_ph);
    };

    typ = Parser_index_expr(p, typ, fn_ph);
  };

  return typ;
}
bool Parser_fileis(Parser *p, string s) {

  return string_contains(p->scanner->file_path, s);
}
string Parser_dot(Parser *p, string str_typ_, int method_ph) {

  string str_typ = str_typ_;

  Parser_check(p, main__TokenKind_dot);

  bool is_variadic_arg = string_starts_with(str_typ, tos3("..."));

  if (is_variadic_arg) {

    str_typ = string_right(str_typ, 3);
  };

  Type typ = Parser_find_type(&/* ? */ *p, str_typ);

  if (typ.name.len == 0) {

    Parser_error(
        p, _STR("dot(): cannot find type `%.*s`", str_typ.len, str_typ.str));
  };

  if (p->tok == main__TokenKind_dollar) {

    Parser_comptime_method_call(p, typ);

    return tos3("void");
  };

  string field_name = p->lit;

  int fname_tidx = Parser_cur_tok_index(&/* ? */ *p);

  Parser_fgen(p, field_name);

  bool has_field = Table_type_has_field(
      &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ,
      Table_var_cgen_name(&/* ? */ *p->table, field_name));

  bool has_method = Table_type_has_method(
      &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ, field_name);

  if (is_variadic_arg && string_eq(field_name, tos3("len"))) {

    Parser_gen(p, _STR("->%.*s", field_name.len, field_name.str));

    Parser_next(p);

    return tos3("int");
  };

  if (!has_method && string_eq(field_name, tos3("str")) &&
      string_starts_with(typ.name, tos3("array_"))) {

    Parser_gen_array_str(p, typ);

    has_method = 1;
  };

  if (!typ.is_c && !p->is_c_fn_call && !has_field && !has_method &&
      !Parser_first_pass(&/* ? */ *p)) {

    if (string_starts_with(typ.name, tos3("Option_"))) {

      string opt_type = string_right(typ.name, 7);

      Parser_error(p, _STR("unhandled option type: `?%.*s`", opt_type.len,
                           opt_type.str));
    };

    Parser_error_with_token_index(
        p,
        _STR("type `%.*s` has no field or method `%.*s`", typ.name.len,
             typ.name.str, field_name.len, field_name.str),
        fname_tidx);
  };

  string dot = tos3(".");

  if (string_ends_with(str_typ, tos3("*")) ||
      string_eq(str_typ, tos3("FT_Face"))) {

    dot = main__dot_ptr;
  };

  if (has_field) {

    string struct_field =
        (string_ne(typ.name, tos3("Option")))
            ? (Table_var_cgen_name(&/* ? */ *p->table, field_name))
            : (field_name);

    Option_Var tmp240 = Table_find_field(
        &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ, struct_field);
    if (!tmp240.ok) {
      string err = tmp240.error;

      Parser_error_with_token_index(p,
                                    _STR("missing field: %.*s in type %.*s",
                                         struct_field.len, struct_field.str,
                                         typ.name.len, typ.name.str),
                                    fname_tidx);

      v_exit(1);
    }
    Var field = *(Var *)tmp240.data;
    ;

    if (!field.is_mut && !p->has_immutable_field) {

      p->has_immutable_field = 1;

      p->first_immutable_field = field;
    };

    TokenKind next = Parser_peek(&/* ? */ *p);

    bool modifying = TokenKind_is_assign(next) || next == main__TokenKind_inc ||
                     next == main__TokenKind_dec ||
                     (string_starts_with(field.typ, tos3("array_")) &&
                      next == main__TokenKind_left_shift);

    bool is_vi = Parser_fileis(&/* ? */ *p, tos3("vid"));

    if (!p->builtin_mod && !p->pref->translated && modifying && !is_vi &&
        p->has_immutable_field) {

      Var f = p->first_immutable_field;

      Parser_error_with_token_index(
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

    if (!p->builtin_mod && string_ne(p->mod, typ.mod)) {
    };

    if (field.access_mod == main__AccessMod_private && !p->builtin_mod &&
        !p->pref->translated && string_ne(p->mod, typ.mod)) {

      Parser_error_with_token_index(
          p,
          _STR("cannot refer to unexported field `%.*s` (type `%.*s`)",
               struct_field.len, struct_field.str, typ.name.len, typ.name.str),
          fname_tidx);
    };

    Parser_gen(p, string_add(dot, struct_field));

    Parser_next(p);

    return field.typ;
  };

  Option_Fn tmp245 = Table_find_method(
      &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ, field_name);
  if (!tmp245.ok) {
    string err = tmp245.error;

    Parser_error_with_token_index(
        p, _STR("could not find method `%.*s`", field_name.len, field_name.str),
        fname_tidx);

    v_exit(1);
  }
  Fn method = *(Fn *)tmp245.data;
  ;

  Parser_fn_call(p, method, method_ph, tos3(""), str_typ);

  if (string_eq(method.typ, tos3("array")) &&
      string_starts_with(typ.name, tos3("array_"))) {

    return typ.name;
  };

  if (string_eq(method.typ, tos3("void*")) &&
      string_starts_with(typ.name, tos3("array_"))) {

    return string_right(typ.name, 6);
  };

  if (string_ends_with(method.typ, tos3("*"))) {

    p->is_alloc = 1;
  };

  return method.typ;
}
IndexType main__get_index_type(string typ) {

  if (string_starts_with(typ, tos3("map_"))) {

    return main__IndexType_map;
  };

  if (string_eq(typ, tos3("string"))) {

    return main__IndexType_str;
  };

  if (string_starts_with(typ, tos3("array_")) ||
      string_eq(typ, tos3("array"))) {

    return main__IndexType_array;
  };

  if (string_eq(typ, tos3("byte*")) || string_eq(typ, tos3("byteptr")) ||
      string_contains(typ, tos3("*"))) {

    return main__IndexType_ptr;
  };

  if (string_at(typ, 0) == '[') {

    return main__IndexType_fixed_array;
  };

  return main__IndexType_noindex;
}
string Parser_index_expr(Parser *p, string typ_, int fn_ph) {

  string typ = typ_;

  Var v = p->expr_var;

  bool is_variadic_arg = string_starts_with(typ, tos3("..."));

  bool is_map = string_starts_with(typ, tos3("map_"));

  bool is_str = string_eq(typ, tos3("string"));

  bool is_arr0 = string_starts_with(typ, tos3("array_"));

  bool is_arr = is_arr0 || string_eq(typ, tos3("array"));

  bool is_ptr = string_eq(typ, tos3("byte*")) ||
                string_eq(typ, tos3("byteptr")) ||
                string_contains(typ, tos3("*"));

  bool is_indexer = p->tok == main__TokenKind_lsbr;

  bool close_bracket = 0;

  int index_error_tok_pos = p->token_idx;

  if (is_indexer) {

    bool is_fixed_arr = string_at(typ, 0) == '[';

    if (!is_str && !is_arr && !is_map && !is_ptr && !is_fixed_arr &&
        !is_variadic_arg) {

      Parser_error(p, _STR("Cant [] non-array/string/map. Got type \"%.*s\"",
                           typ.len, typ.str));
    };

    Parser_check(p, main__TokenKind_lsbr);

    if (is_str) {

      typ = tos3("byte");

      Parser_fgen(p, tos3("["));

      if (p->builtin_mod) {

        Parser_gen(p, tos3(".str["));

        close_bracket = 1;

      } else {

        Parser_gen(p, tos3(","));
      };
    };

    if (is_fixed_arr) {

      if (string_contains(typ, tos3("]["))) {

        int pos = string_index_after(typ, tos3("["), 1);

        typ = string_right(typ, pos);

      } else {

        typ = string_all_after(typ, tos3("]"));
      };

      Parser_gen(p, tos3("["));

      close_bracket = 1;

    } else if (is_ptr && !is_variadic_arg) {

      typ = string_replace(typ, tos3("*"), tos3(""));

      if (!is_arr) {

        Parser_gen(p, tos3("[/*ptr*/"));

        close_bracket = 1;
      };
    };

    if (is_arr) {

      if (is_arr0) {

        typ = string_right(typ, 6);
      };

      Parser_gen_array_at(p, typ, is_arr0, fn_ph);
    };

    if (is_map) {

      typ = string_replace(typ, tos3("map_"), tos3(""));

      if (string_eq(typ, tos3("map"))) {

        typ = tos3("void*");
      };

      Parser_gen(p, tos3(","));
    };

    if (is_arr) {

      int index_pos = p->cgen->cur_line.len;

      Type T = Table_find_type(&/* ? */ *p->table, Parser_expression(p));

      if (string_ne(T.parent, tos3("int")) &&
          string_ne(T.parent, tos3("u32"))) {

        Parser_check_types(p, T.name, tos3("int"));
      };

      if (v_string_int(
              string_replace(string_right(p->cgen->cur_line, index_pos),
                             tos3(" "), tos3(""))) < 0) {

        Parser_error(p, tos3("cannot access negative array index"));
      };

    } else {

      Type T = Table_find_type(&/* ? */ *p->table, Parser_expression(p));

      if (is_map && string_ne(T.parent, tos3("string"))) {

        Parser_check_types(p, T.name, tos3("string"));
      };
    };

    Parser_check(p, main__TokenKind_rsbr);

    if (close_bracket) {

      Parser_gen(p, _STR("]/*r%.*s %d*/", typ.len, typ.str, v.is_mut));
    };

    p->expr_var = v;
  };

  if (is_variadic_arg) {

    if (is_indexer) {

      string l = string_trim_space(p->cgen->cur_line);

      string index_val =
          string_trim_space(string_right(l, string_last_index(l, tos3(" "))));

      CGen_resetln(p->cgen, string_left(l, fn_ph));

      _PUSH(&p->table->varg_access,
            (/*typ = array_VargAccess   tmp_typ=VargAccess*/ (VargAccess){
                .fn_name = p->cur_fn.name,
                .tok_idx = index_error_tok_pos,
                .index = v_string_int(index_val)}),
            tmp268, VargAccess);

      CGen_set_placeholder(p->cgen, fn_ph,
                           _STR("%.*s->args[%.*s]", v.name.len, v.name.str,
                                index_val.len, index_val.str));

      return typ;
    };
  };

  if ((p->tok == main__TokenKind_assign && !p->is_sql) ||
      TokenKind_is_assign(p->tok)) {

    if (is_indexer && is_str && !p->builtin_mod) {

      Parser_error(p, tos3("strings are immutable"));
    };

    p->assigned_type = typ;

    p->expected_type = typ;

    int assign_pos = p->cgen->cur_line.len;

    bool is_cao = p->tok != main__TokenKind_assign;

    Parser_assign_statement(p, v, fn_ph, is_indexer && (is_map || is_arr));

    if (is_indexer && (is_map || is_arr)) {

      Parser_gen_array_set(p, typ, is_ptr, is_map, fn_ph, assign_pos, is_cao);
    };

    return typ;

  } else if ((is_map || is_arr || (is_str && !p->builtin_mod)) && is_indexer) {

    Parser_index_get(p, typ, fn_ph,
                     (IndexCfg){.is_arr = is_arr,
                                .is_map = is_map,
                                .is_ptr = is_ptr,
                                .is_str = is_str,
                                .is_arr0 = 0});
  };

  return typ;
}
string Parser_indot_expr(Parser *p) {

  int ph = CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = Parser_term(p);

  if (p->tok == main__TokenKind_dot) {

    while (p->tok == main__TokenKind_dot) {

      typ = Parser_dot(p, typ, ph);
    };
  };

  if (p->tok == main__TokenKind_key_in) {

    Parser_fgen(p, tos3(" "));

    Parser_check(p, main__TokenKind_key_in);

    if (p->tok == main__TokenKind_lsbr) {

      Parser_in_optimization(p, typ, ph);

      return tos3("bool");
    };

    Parser_fgen(p, tos3(" "));

    Parser_gen(p, tos3("), "));

    string arr_typ = Parser_expression(p);

    bool is_map = string_starts_with(arr_typ, tos3("map_"));

    if (!string_starts_with(arr_typ, tos3("array_")) && !is_map) {

      Parser_error(p, tos3("`in` requires an array/map"));
    };

    Type T = Table_find_type(&/* ? */ *p->table, arr_typ);

    if (!is_map && !Type_has_method(&/* ? */ T, tos3("contains"))) {

      Parser_error(
          p, _STR("%.*s has no method `contains`", arr_typ.len, arr_typ.str));
    };

    if (is_map) {

      CGen_set_placeholder(p->cgen, ph, tos3("_IN_MAP( ("));

    } else {

      CGen_set_placeholder(p->cgen, ph, _STR("_IN(%.*s, (", typ.len, typ.str));
    };

    Parser_gen(p, tos3(")"));

    return tos3("bool");
  };

  return typ;
}
string Parser_expression(Parser *p) {

  p->is_const_literal = 1;

  int ph = CGen_add_placeholder(&/* ? */ *p->cgen);

  string typ = Parser_indot_expr(p);

  bool is_str = string_eq(typ, tos3("string"));

  bool is_ustr = string_eq(typ, tos3("ustring"));

  if (p->tok == main__TokenKind_left_shift) {

    if (string_contains(typ, tos3("array_"))) {

      string tmp = Parser_get_tmp(p);

      string tmp_typ = string_right(typ, 6);

      Parser_check_space(p, main__TokenKind_left_shift);

      Parser_gen(p, tos3(", ("));

      if (!p->expr_var.is_mut && !p->pref->translated) {

        Parser_error(p, _STR("`%.*s` is immutable (can\'t <<)",
                             p->expr_var.name.len, p->expr_var.name.str));
      };

      if (p->expr_var.is_arg &&
          string_starts_with(p->expr_var.typ, tos3("array_"))) {

        Parser_error(
            p, string_add(
                   tos3("for now it's not possible to append an element to "),
                   _STR("a mutable array argument `%.*s`", p->expr_var.name.len,
                        p->expr_var.name.str)));
      };

      if (!p->expr_var.is_changed) {

        Parser_mark_var_changed(p, p->expr_var);
      };

      Parser_gen(p, _STR("/*typ = %.*s   tmp_typ=%.*s*/", typ.len, typ.str,
                         tmp_typ.len, tmp_typ.str));

      int ph_clone = CGen_add_placeholder(&/* ? */ *p->cgen);

      string expr_type = Parser_expression(p);

      if (p->pref->autofree && string_eq(typ, tos3("array_string")) &&
          string_eq(expr_type, tos3("string"))) {

        CGen_set_placeholder(p->cgen, ph_clone, tos3("string_clone("));

        Parser_gen(p, tos3(")"));
      };

      Parser_gen_array_push(p, ph, typ, expr_type, tmp, tmp_typ);

      return tos3("void");

    } else {

      Parser_next(p);

      Parser_gen(p, tos3(" << "));

      Parser_check_types(p, Parser_expression(p), typ);

      return tos3("int");
    };
  };

  if (p->tok == main__TokenKind_righ_shift) {

    Parser_next(p);

    Parser_gen(p, tos3(" >> "));

    Parser_check_types(p, Parser_expression(p), typ);

    return tos3("int");
  };

  while (p->tok == main__TokenKind_plus || p->tok == main__TokenKind_minus ||
         p->tok == main__TokenKind_pipe || p->tok == main__TokenKind_amp ||
         p->tok == main__TokenKind_xor) {

    TokenKind tok_op = p->tok;

    if (string_eq(typ, tos3("bool"))) {

      Parser_error(p,
                   _STR("operator %.*s not defined on bool ",
                        TokenKind_str(p->tok).len, TokenKind_str(p->tok).str));
    };

    bool is_num = string_eq(typ, tos3("void*")) ||
                  string_eq(typ, tos3("byte*")) || main__is_number_type(typ);

    Parser_check_space(p, p->tok);

    if (is_str && tok_op == main__TokenKind_plus && !p->is_js) {

      CGen_set_placeholder(p->cgen, ph, tos3("string_add("));

      Parser_gen(p, tos3(","));

    } else if (is_ustr && tok_op == main__TokenKind_plus) {

      CGen_set_placeholder(p->cgen, ph, tos3("ustring_add("));

      Parser_gen(p, tos3(","));

    } else if (is_num || p->is_js) {

      if (string_eq(typ, tos3("void*"))) {

        CGen_set_placeholder(p->cgen, ph, tos3("(byte*)"));
      };

      Parser_gen(p, TokenKind_str(tok_op));

    } else {

      if (p->pref->translated) {

        Parser_gen(p,
                   string_add(TokenKind_str(tok_op), tos3(" /*doom hack*/")));

      } else {

        Parser_gen(p, tos3(","));
      };
    };

    Parser_check_types(p, Parser_term(p), typ);

    if ((is_str || is_ustr) && tok_op == main__TokenKind_plus && !p->is_js) {

      Parser_gen(p, tos3(")"));
    };

    if (!p->pref->translated && !is_str && !is_ustr && !is_num) {

      Type T = Table_find_type(&/* ? */ *p->table, typ);

      if (tok_op == main__TokenKind_plus) {

        if (Type_has_method(&/* ? */ T, tos3("+"))) {

          CGen_set_placeholder(p->cgen, ph, string_add(typ, tos3("_plus(")));

          Parser_gen(p, tos3(")"));

        } else {

          Parser_error(
              p, _STR("operator + not defined on `%.*s`", typ.len, typ.str));
        };

      } else if (tok_op == main__TokenKind_minus) {

        if (Type_has_method(&/* ? */ T, tos3("-"))) {

          CGen_set_placeholder(p->cgen, ph,
                               _STR("%.*s_minus(", typ.len, typ.str));

          Parser_gen(p, tos3(")"));

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

  if (p->tok == main__TokenKind_mul && line_nr != p->scanner->line_nr) {

    return typ;
  };

  while (p->tok == main__TokenKind_mul || p->tok == main__TokenKind_div ||
         p->tok == main__TokenKind_mod) {

    TokenKind tok = p->tok;

    bool is_div = tok == main__TokenKind_div;

    bool is_mod = tok == main__TokenKind_mod;

    Parser_next(p);

    Parser_gen(p, TokenKind_str(tok));

    Parser_fgen(
        p, string_add(string_add(tos3(" "), TokenKind_str(tok)), tos3(" ")));

    if ((is_div || is_mod) && p->tok == main__TokenKind_number &&
        string_eq(p->lit, tos3("0"))) {

      Parser_error(p, tos3("division or modulo by zero"));
    };

    if (is_mod && (main__is_float_type(typ) || !main__is_number_type(typ))) {

      Parser_error(p, tos3("operator .mod requires integer types"));
    };

    Parser_check_types(p, Parser_unary(p), typ);
  };

  return typ;
}
string Parser_unary(Parser *p) {

  string typ = tos3("");

  TokenKind tok = p->tok;

  if (tok == main__TokenKind_not) { /* case */

    Parser_gen(p, tos3("!"));

    Parser_check(p, main__TokenKind_not);

    typ = Parser_indot_expr(p);

    if (string_ne(typ, tos3("bool"))) {

      Parser_error(p, _STR("operator ! requires bool type, not `%.*s`", typ.len,
                           typ.str));
    };

  } else if (tok == main__TokenKind_bit_not) { /* case */

    Parser_gen(p, tos3("~"));

    Parser_check(p, main__TokenKind_bit_not);

    typ = Parser_bool_expression(p);

  } else { // default:

    typ = Parser_factor(p);
  };

  return typ;
}
string Parser_factor(Parser *p) {

  string typ = tos3("");

  TokenKind tok = p->tok;

  if (tok == main__TokenKind_key_none) { /* case */

    if (!string_starts_with(p->expected_type, tos3("Option_"))) {

      Parser_error(p, _STR("need \"%.*s\" got none", p->expected_type.len,
                           p->expected_type.str));
    };

    Parser_gen(p, tos3("opt_none()"));

    Parser_check(p, main__TokenKind_key_none);

    return p->expected_type;

  } else if (tok == main__TokenKind_number) { /* case */

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
        !main__is_valid_int_const(p->lit, p->expected_type)) {

      Parser_error(p, _STR("constant `%.*s` overflows `%.*s`", p->lit.len,
                           p->lit.str, p->expected_type.len,
                           p->expected_type.str));
    };

    Parser_gen(p, p->lit);

    Parser_fgen(p, p->lit);

  } else if (tok == main__TokenKind_minus) { /* case */

    Parser_gen(p, tos3("-"));

    Parser_fgen(p, tos3("-"));

    Parser_next(p);

    return Parser_factor(p);

  } else if (tok == main__TokenKind_key_sizeof) { /* case */

    Parser_gen(p, tos3("sizeof("));

    Parser_fgen(p, tos3("sizeof("));

    Parser_next(p);

    Parser_check(p, main__TokenKind_lpar);

    string sizeof_typ = Parser_get_type(p);

    Parser_check(p, main__TokenKind_rpar);

    Parser_gen(p, _STR("%.*s)", sizeof_typ.len, sizeof_typ.str));

    Parser_fgen(p, _STR("%.*s)", sizeof_typ.len, sizeof_typ.str));

    return tos3("int");

  } else if (tok == main__TokenKind_amp || tok == main__TokenKind_dot ||
             tok == main__TokenKind_mul) { /* case */

    return Parser_name_expr(p);

  } else if (tok == main__TokenKind_name) { /* case */

    if (string_eq(p->lit, tos3("map")) &&
        Parser_peek(&/* ? */ *p) == main__TokenKind_lsbr) {

      return Parser_map_init(p);
    };

    if (string_eq(p->lit, tos3("json")) &&
        Parser_peek(&/* ? */ *p) == main__TokenKind_dot) {

      if (!(_IN(string, (tos3("json")), p->table->imports))) {

        Parser_error(p, tos3("undefined: `json`, use `import json`"));
      };

      FileImportTable_register_used_import(&/* ? */ p->import_table,
                                           tos3("json"));

      return Parser_js_decode(p);
    };

    typ = Parser_name_expr(p);

    return typ;

  } else if (tok == main__TokenKind_key_default) { /* case */

    Parser_next(p);

    Parser_next(p);

    string name = Parser_check_name(p);

    if (string_ne(name, tos3("T"))) {

      Parser_error(p, tos3("default needs T"));
    };

    Parser_gen(p, tos3("default(T)"));

    Parser_next(p);

    return tos3("T");

  } else if (tok == main__TokenKind_lpar) { /* case */

    Parser_gen(p, tos3("("));

    Parser_check(p, main__TokenKind_lpar);

    typ = Parser_bool_expression(p);

    if (!p->ptr_cast) {

      Parser_check(p, main__TokenKind_rpar);
    };

    p->ptr_cast = 0;

    Parser_gen(p, tos3(")"));

    return typ;

  } else if (tok == main__TokenKind_chartoken) { /* case */

    Parser_char_expr(p);

    typ = tos3("byte");

    return typ;

  } else if (tok == main__TokenKind_str) { /* case */

    Parser_string_expr(p);

    typ = tos3("string");

    return typ;

  } else if (tok == main__TokenKind_key_false) { /* case */

    typ = tos3("bool");

    Parser_gen(p, tos3("0"));

    Parser_fgen(p, tos3("false"));

  } else if (tok == main__TokenKind_key_true) { /* case */

    typ = tos3("bool");

    Parser_gen(p, tos3("1"));

    Parser_fgen(p, tos3("true"));

  } else if (tok == main__TokenKind_lsbr) { /* case */

    return Parser_array_init(p);

  } else if (tok == main__TokenKind_lcbr) { /* case */

    if (Parser_peek(&/* ? */ *p) == main__TokenKind_str) {

      return Parser_map_init(p);
    };

    return Parser_assoc(p);

  } else if (tok == main__TokenKind_key_if) { /* case */

    typ = Parser_if_st(p, 1, 0);

    return typ;

  } else if (tok == main__TokenKind_key_match) { /* case */

    typ = Parser_match_statement(p, 1);

    return typ;

  } else { // default:

    if (p->pref->is_verbose || p->pref->is_debug) {

      TokenKind next = Parser_peek(&/* ? */ *p);

      printf("prev=%.*s\n", TokenKind_str(p->prev_tok).len,
             TokenKind_str(p->prev_tok).str);

      printf("next=%.*s\n", TokenKind_str(next).len, TokenKind_str(next).str);
    };

    Parser_error(p, _STR("unexpected token: `%.*s`", TokenKind_str(p->tok).len,
                         TokenKind_str(p->tok).str));
  };

  Parser_next(p);

  return typ;
}
string Parser_assoc(Parser *p) {

  Parser_next(p);

  string name = Parser_check_name(p);

  Option_Var tmp307 = Parser_find_var(&/* ? */ *p, name);
  if (!tmp307.ok) {
    string err = tmp307.error;

    Parser_error(p, _STR("unknown variable `%.*s`", name.len, name.str));

    v_exit(1);
  }
  Var var = *(Var *)tmp307.data;
  ;

  Parser_check(p, main__TokenKind_pipe);

  Parser_gen(p, _STR("(%.*s){", var.typ.len, var.typ.str));

  array_string fields = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  while (p->tok != main__TokenKind_rcbr) {

    string field = Parser_check_name(p);

    _PUSH(&fields, (/*typ = array_string   tmp_typ=string*/ field), tmp310,
          string);

    Parser_gen(p, _STR(".%.*s = ", field.len, field.str));

    Parser_check(p, main__TokenKind_colon);

    Parser_bool_expression(p);

    Parser_gen(p, tos3(","));

    if (p->tok != main__TokenKind_rcbr) {

      Parser_check(p, main__TokenKind_comma);
    };
  };

  Type T = Table_find_type(&/* ? */ *p->table, var.typ);

  array_Var tmp312 = T.fields;
  for (int tmp313 = 0; tmp313 < tmp312.len; tmp313++) {
    Var ffield = ((Var *)tmp312.data)[tmp313];

    string f = ffield.name;

    if (_IN(string, (f), fields)) {

      continue;
    };

    Parser_gen(p, _STR(".%.*s = %.*s . %.*s,", f.len, f.str, name.len, name.str,
                       f.len, f.str));
  };

  Parser_check(p, main__TokenKind_rcbr);

  Parser_gen(p, tos3("}"));

  return var.typ;
}
void Parser_char_expr(Parser *p) {

  Parser_gen(p, _STR("\'%.*s\'", p->lit.len, p->lit.str));

  Parser_next(p);
}
string main__format_str(string _str) {

  string str = string_replace(_str, tos3("\""), tos3("\\\""));

#ifdef _WIN32

  str = string_replace(str, tos3("\r\n"), tos3("\\n"));

#endif
  ;

  str = string_replace(str, tos3("\n"), tos3("\\n"));

  return str;
}
void Parser_string_expr(Parser *p) {

  bool is_raw = p->tok == main__TokenKind_name && string_eq(p->lit, tos3("r"));

  if (is_raw) {

    Parser_next(p);
  };

  string str = p->lit;

  if (Parser_peek(&/* ? */ *p) != main__TokenKind_dollar || is_raw) {

    Parser_fgen(p, _STR("'%.*s'", str.len, str.str));

    string f = (is_raw) ? (main__cescaped_path(str)) : (main__format_str(str));

    if ((p->calling_c && Parser_peek(&/* ? */ *p) != main__TokenKind_dot) ||
        (p->pref->translated && string_eq(p->mod, tos3("main")))) {

      Parser_gen(p, _STR("\"%.*s\"", f.len, f.str));

    } else if (p->is_sql) {

      Parser_gen(p, _STR("'%.*s'", str.len, str.str));

    } else if (p->is_js) {

      Parser_gen(p, _STR("\"%.*s\"", f.len, f.str));

    } else {

      Parser_gen(p, _STR("tos3(\"%.*s\")", f.len, f.str));
    };

    Parser_next(p);

    return;
  };

#ifdef _VJS

  Parser_error(p, tos3("js backend does not support string formatting yet"));

#endif
  ;

  p->is_alloc = 1;

  string args = tos3("\"");

  string format = tos3("\"");

  Parser_fgen(p, tos3("\'"));

  bool complex_inter = 0;

  while (p->tok == main__TokenKind_str) {

    Parser_fgen(p, p->lit);

    p->lit = string_replace(p->lit, tos3("%"), tos3("%%"));

    format = string_add(format, main__format_str(p->lit));

    Parser_next(p);

    if (p->tok != main__TokenKind_dollar) {

      continue;
    };

    Parser_check(p, main__TokenKind_dollar);

    if (Parser_peek(&/* ? */ *p) != main__TokenKind_str) {

      Parser_fgen(p, tos3("{"));

      complex_inter = 1;
    };

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    string val = CGen_end_tmp(p->cgen);

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

    bool custom = p->tok == main__TokenKind_colon;

    if (custom) {

      string cformat = tos3("");

      Parser_next(p);

      if (p->tok == main__TokenKind_dot) {

        cformat = string_add(cformat, tos3("."));

        Parser_next(p);
      };

      if (p->tok == main__TokenKind_minus) {

        cformat = string_add(cformat, tos3("-"));

        Parser_next(p);
      };

      cformat = string_add(cformat, p->lit);

      Parser_next(p);

      string fspec = p->lit;

      cformat = string_add(cformat, fspec);

      if (string_eq(fspec, tos3("s"))) {

        if (string_ne(typ, tos3("string"))) {

          Parser_error(
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

      Parser_next(p);

    } else {

      string f = Parser_typ_to_fmt(p, typ, 0);

      if (string_eq(f, tos3(""))) {

        bool is_array = string_starts_with(typ, tos3("array_"));

        Type typ2 = Table_find_type(&/* ? */ *p->table, typ);

        bool has_str_method = Table_type_has_method(
            &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ2,
            tos3("str"));

        if (is_array || has_str_method) {

          if (is_array && !has_str_method) {

            Parser_gen_array_str(p, typ2);
          };

          args = string_add(string_all_before_last(args, val),
                            _STR("%.*s_str(%.*s).len, %.*s_str(%.*s).str",
                                 typ.len, typ.str, val.len, val.str, typ.len,
                                 typ.str, val.len, val.str));

          format = string_add(format, tos3("%.*s "));

        } else {

          Parser_error(
              p, _STR("unhandled sprintf format \"%.*s\" ", typ.len, typ.str));
        };
      };

      format = string_add(format, f);
    };
  };

  if (complex_inter) {

    Parser_fgen(p, tos3("}"));
  };

  Parser_fgen(p, tos3("\'"));

  if (p->cgen->nogen) {

    return;
  };

#ifndef _WIN32

  string cur_line = string_trim_space(p->cgen->cur_line);

  if (string_eq(cur_line, tos3("println (")) &&
      p->tok != main__TokenKind_plus) {

    CGen_resetln(p->cgen,
                 string_replace(cur_line, tos3("println ("), tos3("printf(")));

    Parser_gen(p,
               _STR("%.*s\\n%.*s", format.len, format.str, args.len, args.str));

    return;
  };

#endif
  ;

  if (p->tok == main__TokenKind_not) {

    Parser_check(p, main__TokenKind_not);

    Parser_gen(p, _STR("_STR_TMP(%.*s%.*s)", format.len, format.str, args.len,
                       args.str));

  } else {

    Parser_gen(
        p, _STR("_STR(%.*s%.*s)", format.len, format.str, args.len, args.str));
  };
}
string Parser_map_init(Parser *p) {

  string keys_gen = tos3("");

  string vals_gen = tos3("");

  string val_type = tos3("");

  if (p->tok == main__TokenKind_lcbr) {

    Parser_check(p, main__TokenKind_lcbr);

    int i = 0;

    while (1) {

      string key = p->lit;

      keys_gen =
          string_add(keys_gen, _STR("tos3(\"%.*s\"), ", key.len, key.str));

      Parser_check(p, main__TokenKind_str);

      Parser_check(p, main__TokenKind_colon);

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

      if (p->tok == main__TokenKind_rcbr) {

        Parser_check(p, main__TokenKind_rcbr);

        break;
      };

      if (p->tok == main__TokenKind_comma) {

        Parser_check(p, main__TokenKind_comma);
      };
    };

    Parser_gen(p,
               string_add(_STR("new_map_init(%d, sizeof(%.*s), ", i,
                               val_type.len, val_type.str),
                          _STR("(string[%d]){ %.*s }, (%.*s [%d]){ %.*s } )", i,
                               keys_gen.len, keys_gen.str, val_type.len,
                               val_type.str, i, vals_gen.len, vals_gen.str)));

    string typ = _STR("map_%.*s", val_type.len, val_type.str);

    Parser_register_map(p, typ);

    return typ;
  };

  Parser_next(p);

  Parser_check(p, main__TokenKind_lsbr);

  string key_type = Parser_check_name(p);

  if (string_ne(key_type, tos3("string"))) {

    Parser_error(p, tos3("only string key maps allowed for now"));
  };

  Parser_check(p, main__TokenKind_rsbr);

  val_type = Parser_get_type(p);

  string typ = _STR("map_%.*s", val_type.len, val_type.str);

  Parser_register_map(p, typ);

  Parser_gen(p, _STR("new_map(1, sizeof(%.*s))", val_type.len, val_type.str));

  if (p->tok == main__TokenKind_lcbr) {

    Parser_check(p, main__TokenKind_lcbr);

    Parser_check(p, main__TokenKind_rcbr);

    println(string_add(_STR("warning: %.*s:%d ", p->file_name.len,
                            p->file_name.str, p->scanner->line_nr),
                       tos3("initializaing maps no longer requires `{}`")));
  };

  return typ;
}
string Parser_array_init(Parser *p) {

  p->is_alloc = 1;

  Parser_check(p, main__TokenKind_lsbr);

  bool is_integer = p->tok == main__TokenKind_number;

  bool is_const_len = 0;

  if (p->tok == main__TokenKind_name && !p->inside_const) {

    string const_name = Parser_prepend_mod(&/* ? */ *p, p->lit);

    if (Table_known_const(&/* ? */ *p->table, const_name)) {

      Option_Var tmp345 = Table_find_const(&/* ? */ *p->table, const_name);
      if (!tmp345.ok) {
        string err = tmp345.error;

        v_exit(1);
      }
      Var c = *(Var *)tmp345.data;
      ;

      if (string_eq(c.typ, tos3("int")) &&
          Parser_peek(&/* ? */ *p) == main__TokenKind_rsbr) {

        is_integer = 1;

        is_const_len = 1;

      } else {

        Parser_error(p, _STR("bad fixed size array const `%.*s`", p->lit.len,
                             p->lit.str));
      };
    };
  };

  string lit = p->lit;

  string typ = tos3("");

  int new_arr_ph = CGen_add_placeholder(&/* ? */ *p->cgen);

  int i = 0;

  int pos = p->cgen->cur_line.len;

  while (p->tok != main__TokenKind_rsbr) {

    string val_typ = Parser_bool_expression(p);

    if (i == 0) {

      typ = val_typ;

      if (is_integer && p->tok == main__TokenKind_rsbr &&
          Parser_peek(&/* ? */ *p) == main__TokenKind_name &&
          Parser_cur_tok(&/* ? */ *p).line_nr ==
              Parser_peek_token(&/* ? */ *p).line_nr) {

        if (Parser_cur_tok(&/* ? */ *p).col +
                Parser_peek_token(&/* ? */ *p).lit.len ==
            Parser_peek_token(&/* ? */ *p).col) {

          Parser_check(p, main__TokenKind_rsbr);

          string array_elem_typ = Parser_get_type(p);

          if (!Table_known_type(&/* ? */ *p->table, array_elem_typ)) {

            Parser_error(p, _STR("bad type `%.*s`", array_elem_typ.len,
                                 array_elem_typ.str));
          };

          CGen_resetln(p->cgen, tos3(""));

          p->is_alloc = 0;

          if (is_const_len) {

            return _STR("[%.*s__%.*s]%.*s", p->mod.len, p->mod.str, lit.len,
                        lit.str, array_elem_typ.len, array_elem_typ.str);
          };

          return _STR("[%.*s]%.*s", lit.len, lit.str, array_elem_typ.len,
                      array_elem_typ.str);

        } else {

          Parser_check(p, main__TokenKind_rsbr);

          typ = Parser_get_type(p);

          Parser_error(p, _STR("no space allowed between [%.*s] and %.*s",
                               lit.len, lit.str, typ.len, typ.str));
        };
      };
    };

    if (string_ne(val_typ, typ)) {

      if (!Parser_check_types_no_throw(p, val_typ, typ)) {

        Parser_error(p, _STR("bad array element type `%.*s` instead of `%.*s`",
                             val_typ.len, val_typ.str, typ.len, typ.str));
      };
    };

    if (p->tok != main__TokenKind_rsbr && p->tok != main__TokenKind_semicolon) {

      Parser_gen(p, tos3(", "));

      Parser_check(p, main__TokenKind_comma);

      Parser_fspace(p);
    };

    i++;

    if (i == 1 && p->tok == main__TokenKind_semicolon) {

      Parser_warn(
          p,
          tos3(
              "`[0 ; len]` syntax was removed. Use `[0].repeat(len)` instead"));

      Parser_check_space(p, main__TokenKind_semicolon);

      string val = string_right(p->cgen->cur_line, pos);

      CGen_resetln(p->cgen, string_left(p->cgen->cur_line, pos));

      Parser_gen(p, _STR("array_repeat_old(& (%.*s[]){ %.*s }, ", typ.len,
                         typ.str, val.len, val.str));

      Parser_check_types(p, Parser_bool_expression(p), tos3("int"));

      Parser_gen(p, _STR(", sizeof(%.*s) )", typ.len, typ.str));

      Parser_check(p, main__TokenKind_rsbr);

      return _STR("array_%.*s", typ.len, typ.str);
    };
  };

  Parser_check(p, main__TokenKind_rsbr);

  if (p->tok != main__TokenKind_name && i == 0) {

    Parser_error(p, tos3("specify array type: `[]typ` instead of `[]`"));
  };

  if (p->tok == main__TokenKind_name && i == 0) {

    typ = Parser_get_type(p);
  };

  bool no_alloc = p->tok == main__TokenKind_not;

  if (no_alloc) {

    Parser_next(p);
  };

  bool is_fixed_size = p->tok == main__TokenKind_not;

  if (is_fixed_size) {

    Parser_next(p);

    Parser_gen(p, tos3(" }"));

    if (!Parser_first_pass(&/* ? */ *p)) {

      if (p->inside_const) {

        CGen_set_placeholder(p->cgen, new_arr_ph, tos3("{"));

      } else {

        CGen_set_placeholder(p->cgen, new_arr_ph,
                             _STR("(%.*s[]) {", typ.len, typ.str));
      };
    };

    return _STR("[%d]%.*s", i, typ.len, typ.str);
  };

  Parser_gen_array_init(p, typ, no_alloc, new_arr_ph, i);

  typ = _STR("array_%.*s", typ.len, typ.str);

  Parser_register_array(p, typ);

  return typ;
}
string Parser_struct_init(Parser *p, string typ) {

  p->is_struct_init = 1;

  Type t = Table_find_type(&/* ? */ *p->table, typ);

  if (Parser_gen_struct_init(p, typ, t)) {

    return typ;
  };

  strings__Builder_cut(&/* ? */ p->scanner->fmt_out, typ.len);

  bool ptr = string_contains(typ, tos3("*"));

  bool did_gen_something = 0;

  array_string inited_fields = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  TokenKind peek = Parser_peek(&/* ? */ *p);

  if (peek == main__TokenKind_colon || p->tok == main__TokenKind_rcbr) {

    while (p->tok != main__TokenKind_rcbr) {

      string field =
          (string_ne(typ, tos3("Option")))
              ? (Table_var_cgen_name(&/* ? */ *p->table, Parser_check_name(p)))
              : (Parser_check_name(p));

      if (!Parser_first_pass(&/* ? */ *p) &&
          !Type_has_field(&/* ? */ t, field)) {

        Parser_error(p, _STR("`%.*s` has no field `%.*s`", t.name.len,
                             t.name.str, field.len, field.str));
      };

      if (_IN(string, (field), inited_fields)) {

        Parser_error(p, _STR("already initialized field `%.*s` in `%.*s`",
                             field.len, field.str, t.name.len, t.name.str));
      };

      Option_Var tmp362 = Type_find_field(&/* ? */ t, field);
      if (!tmp362.ok) {
        string err = tmp362.error;

        Parser_error(p, _STR("no such field: \"%.*s\" in type %.*s", field.len,
                             field.str, typ.len, typ.str));

        break;
      }
      Var f = *(Var *)tmp362.data;
      ;

      _PUSH(&inited_fields, (/*typ = array_string   tmp_typ=string*/ field),
            tmp363, string);

      Parser_gen_struct_field_init(p, field);

      Parser_check(p, main__TokenKind_colon);

      Parser_fspace(p);

      Parser_check_types(p, Parser_bool_expression(p), f.typ);

      if (p->tok == main__TokenKind_comma) {

        Parser_next(p);
      };

      if (p->tok != main__TokenKind_rcbr) {

        Parser_gen(p, tos3(","));
      };

      Parser_fgenln(p, tos3(""));

      did_gen_something = 1;
    };

    if (t.fields.len != inited_fields.len && inited_fields.len > 0) {

      Parser_gen(p, tos3(","));
    };

    array_Var tmp364 = t.fields;
    for (int i = 0; i < tmp364.len; i++) {
      Var field = ((Var *)tmp364.data)[i];

      string sanitized_name =
          (string_ne(typ, tos3("Option")))
              ? (Table_var_cgen_name(&/* ? */ *p->table, field.name))
              : (field.name);

      if (_IN(string, (sanitized_name), inited_fields)) {

        continue;
      };

      string field_typ = field.typ;

      if (!p->builtin_mod && string_ends_with(field_typ, tos3("*")) &&
          string_contains(field_typ, tos3("Cfg"))) {

        Parser_error(p, _STR("pointer field `%.*s.%.*s` must be initialized",
                             typ.len, typ.str, field.name.len, field.name.str));
      };

      if (string_starts_with(field_typ, tos3("map_"))) {

        Parser_gen_struct_field_init(p, sanitized_name);

        Parser_gen_empty_map(p, string_right(field_typ, 4));

        _PUSH(&inited_fields,
              (/*typ = array_string   tmp_typ=string*/ sanitized_name), tmp367,
              string);

        if (i != t.fields.len - 1) {

          Parser_gen(p, tos3(","));
        };

        did_gen_something = 1;

        continue;
      };

      string def_val = main__type_default(field_typ);

      if (string_ne(def_val, tos3("")) && string_ne(def_val, tos3("{0}"))) {

        Parser_gen_struct_field_init(p, sanitized_name);

        Parser_gen(p, def_val);

        if (i != t.fields.len - 1) {

          Parser_gen(p, tos3(","));
        };

        did_gen_something = 1;
      };
    };

  } else {

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    if (T.fields.len == 0 && string_ne(T.parent, tos3(""))) {

      T = Table_find_type(&/* ? */ *p->table, T.parent);
    };

    array_Var tmp370 = T.fields;
    for (int i = 0; i < tmp370.len; i++) {
      Var ffield = ((Var *)tmp370.data)[i];

      string expr_typ = Parser_bool_expression(p);

      if (!Parser_check_types_no_throw(p, expr_typ, ffield.typ)) {

        Parser_error(
            p, _STR("field value #%d `%.*s` has type `%.*s`, got `%.*s` ",
                    i + 1, ffield.name.len, ffield.name.str, ffield.typ.len,
                    ffield.typ.str, expr_typ.len, expr_typ.str));
      };

      if (i < T.fields.len - 1) {

        if (p->tok != main__TokenKind_comma) {

          Parser_error(
              p, _STR("too few values in `%.*s` literal (%d instead of %d)",
                      typ.len, typ.str, i + 1, T.fields.len));
        };

        Parser_gen(p, tos3(","));

        Parser_next(p);
      };
    };

    if (p->tok == main__TokenKind_comma) {

      Parser_next(p);
    };

    if (p->tok != main__TokenKind_rcbr) {

      Parser_error(p,
                   _STR("too many fields initialized: `%.*s` has %d field(s)",
                        typ.len, typ.str, T.fields.len));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    Parser_gen(p, tos3("EMPTY_STRUCT_INITIALIZATION"));
  };

  Parser_gen(p, tos3("}"));

  if (ptr && !p->is_js) {

    Parser_gen(p, _STR(", sizeof(%.*s))", t.name.len, t.name.str));
  };

  Parser_check(p, main__TokenKind_rcbr);

  p->is_struct_init = 0;

  p->is_c_struct_init = 0;

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
_V_MulRet_string_V_string Parser_tmp_expr(Parser *p) {

  CGen_start_tmp(p->cgen);

  string typ = Parser_bool_expression(p);

  string val = CGen_end_tmp(p->cgen);

  return (_V_MulRet_string_V_string){.var_0 = typ, .var_1 = val};
}
string Parser_if_st(Parser *p, bool is_expr, int elif_depth) {

  if (is_expr) {

    p->inside_if_expr = 1;

    Parser_gen(p, tos3("("));

  } else {

    Parser_gen(p, tos3("if ("));

    Parser_fgen(p, tos3("if "));
  };

  Parser_next(p);

  if (p->tok == main__TokenKind_name &&
      Parser_peek(&/* ? */ *p) == main__TokenKind_decl_assign) {

    string option_tmp = Parser_get_tmp(p);

    string var_name = p->lit;

    Parser_next(p);

    Parser_check(p, main__TokenKind_decl_assign);

    _V_MulRet_string_V_string _V_mret_option_type_expr = Parser_tmp_expr(p);
    string option_type = _V_mret_option_type_expr.var_0;
    string expr = _V_mret_option_type_expr.var_1;

    string typ = string_right(option_type, 7);

    CGen_insert_before(p->cgen, _STR("%.*s %.*s = %.*s; ", option_type.len,
                                     option_type.str, option_tmp.len,
                                     option_tmp.str, expr.len, expr.str));

    Parser_check(p, main__TokenKind_lcbr);

    Parser_genln(p, string_add(option_tmp, tos3(".ok) {")));

    Parser_genln(p, _STR("%.*s %.*s = *(%.*s*) %.*s . data;", typ.len, typ.str,
                         var_name.len, var_name.str, typ.len, typ.str,
                         option_tmp.len, option_tmp.str));

    Parser_register_var(p, (Var){.name = var_name,
                                 .typ = typ,
                                 .is_mut = 0,
                                 .idx = 0,
                                 .is_arg = 0,
                                 .is_const = 0,
                                 .args = new_array(0, 1, sizeof(Var)),
                                 .attr = tos((byte *)"", 0),
                                 .is_alloc = 0,
                                 .is_returned = 0,
                                 .ptr = 0,
                                 .ref = 0,
                                 .parent_fn = tos((byte *)"", 0),
                                 .mod = tos((byte *)"", 0),
                                 .is_global = 0,
                                 .is_used = 0,
                                 .is_changed = 0,
                                 .scope_level = 0,
                                 .is_c = 0,
                                 .is_moved = 0,
                                 .line_nr = 0,
                                 .token_idx = 0});

    Parser_statements(p);

    return tos3("void");

  } else {

    Parser_check_types(p, Parser_bool_expression(p), tos3("bool"));
  };

  if (is_expr) {

    Parser_gen(p, tos3(") ? ("));

  } else {

    Parser_genln(p, tos3(") {"));
  };

  Parser_fgen(p, tos3(" "));

  Parser_check(p, main__TokenKind_lcbr);

  string typ = tos3("");

  if (p->tok == main__TokenKind_key_if && p->inside_if_expr) {

    typ = Parser_factor(p);

    Parser_next(p);

  } else {

    typ = Parser_statements(p);
  };

  bool if_returns = p->returns;

  p->returns = 0;

  if (p->tok == main__TokenKind_key_else) {

    Parser_fgenln(p, tos3(""));

    Parser_check(p, main__TokenKind_key_else);

    Parser_fspace(p);

    if (p->tok == main__TokenKind_key_if) {

      if (is_expr) {

        Parser_gen(p, tos3(") : ("));

        string nested = Parser_if_st(p, is_expr, elif_depth + 1);

        bool nested_returns = p->returns;

        p->returns = if_returns && nested_returns;

        return nested;

      } else {

        Parser_gen(p, tos3(" else "));

        string nested = Parser_if_st(p, is_expr, 0);

        bool nested_returns = p->returns;

        p->returns = if_returns && nested_returns;

        return nested;
      };
    };

    if (is_expr) {

      Parser_gen(p, tos3(") : ("));

    } else {

      Parser_genln(p, tos3(" else { "));
    };

    Parser_check(p, main__TokenKind_lcbr);

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

  if (Parser_fileis(&/* ? */ *p, tos3("test_test"))) {

    printf("if ret typ=\"%.*s\" line=%d\n", typ.len, typ.str,
           p->scanner->line_nr);
  };

  return typ;
}
void Parser_for_st(Parser *p) {

  Parser_check(p, main__TokenKind_key_for);

  Parser_fgen(p, tos3(" "));

  p->for_expr_cnt++;

  TokenKind next_tok = Parser_peek(&/* ? */ *p);

  Parser_open_scope(p);

  if (p->tok == main__TokenKind_lcbr) {

    Parser_gen(p, tos3("while (1) {"));

  } else if (p->tok == main__TokenKind_key_mut) {

    Parser_error(p, tos3("`mut` is not required in for loops"));

  } else if (next_tok == main__TokenKind_decl_assign ||
             next_tok == main__TokenKind_assign ||
             p->tok == main__TokenKind_semicolon) {

    Parser_genln(p, tos3("for ("));

    if (next_tok == main__TokenKind_decl_assign) {

      Parser_var_decl(p);

    } else if (p->tok != main__TokenKind_semicolon) {

      Parser_statement(p, 0);
    };

    Parser_check(p, main__TokenKind_semicolon);

    Parser_gen(p, tos3(" ; "));

    Parser_fgen(p, tos3(" "));

    if (p->tok != main__TokenKind_semicolon) {

      Parser_bool_expression(p);
    };

    Parser_check(p, main__TokenKind_semicolon);

    Parser_gen(p, tos3(" ; "));

    Parser_fgen(p, tos3(" "));

    if (p->tok != main__TokenKind_lcbr) {

      Parser_statement(p, 0);
    };

    Parser_genln(p, tos3(") { "));

  } else if (Parser_peek(&/* ? */ *p) == main__TokenKind_comma) {

    string i = Parser_check_name(p);

    Parser_check(p, main__TokenKind_comma);

    string val = Parser_check_name(p);

    if (string_eq(i, tos3("_")) && string_eq(val, tos3("_"))) {

      Parser_error(p, tos3("no new variables on the left side of `in`"));
    };

    Parser_fgen(p, tos3(" "));

    Parser_check(p, main__TokenKind_key_in);

    Parser_fgen(p, tos3(" "));

    string tmp = Parser_get_tmp(p);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    bool is_arr = string_starts_with(typ, tos3("array_"));

    bool is_map = string_starts_with(typ, tos3("map_"));

    bool is_str = string_eq(typ, tos3("string"));

    bool is_variadic_arg = string_starts_with(typ, tos3("..."));

    if (is_variadic_arg) {

      typ = string_right(typ, 3);
    };

    if (!is_arr && !is_str && !is_map && !is_variadic_arg) {

      Parser_error(p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    string expr = CGen_end_tmp(p->cgen);

    if (!is_variadic_arg) {

      if (p->is_js) {

        Parser_genln(
            p, _STR("var %.*s = %.*s;", tmp.len, tmp.str, expr.len, expr.str));

      } else {

        Parser_genln(p, _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len,
                             tmp.str, expr.len, expr.str));
      };
    };

    int pad = (is_arr) ? (6) : (4);

    string var_typ =
        (is_str) ? (tos3("byte"))
                 : ((is_variadic_arg) ? (typ) : (string_right(typ, pad)));

    string i_var_type = tos3("int");

    if (is_arr) {

      Parser_gen_for_header(p, i, tmp, var_typ, val);

    } else if (is_map) {

      i_var_type = tos3("string");

      Parser_gen_for_map_header(p, i, tmp, var_typ, val, typ);

    } else if (is_str) {

      i_var_type = tos3("byte");

      Parser_gen_for_str_header(p, i, tmp, var_typ, val);

    } else if (is_variadic_arg) {

      Parser_gen_for_varg_header(p, i, expr, typ, val);
    };

    if (string_ne(i, tos3("_"))) {

      Parser_register_var(p, (Var){.name = i,
                                   .typ = i_var_type,
                                   .is_mut = 1,
                                   .is_changed = 1,
                                   .idx = 0,
                                   .is_arg = 0,
                                   .is_const = 0,
                                   .args = new_array(0, 1, sizeof(Var)),
                                   .attr = tos((byte *)"", 0),
                                   .is_alloc = 0,
                                   .is_returned = 0,
                                   .ptr = 0,
                                   .ref = 0,
                                   .parent_fn = tos((byte *)"", 0),
                                   .mod = tos((byte *)"", 0),
                                   .is_global = 0,
                                   .is_used = 0,
                                   .scope_level = 0,
                                   .is_c = 0,
                                   .is_moved = 0,
                                   .line_nr = 0,
                                   .token_idx = 0});
    };

    if (string_ne(val, tos3("_"))) {

      Parser_register_var(p, (Var){.name = val,
                                   .typ = var_typ,
                                   .ptr = string_contains(typ, tos3("*")),
                                   .idx = 0,
                                   .is_arg = 0,
                                   .is_const = 0,
                                   .args = new_array(0, 1, sizeof(Var)),
                                   .attr = tos((byte *)"", 0),
                                   .is_mut = 0,
                                   .is_alloc = 0,
                                   .is_returned = 0,
                                   .ref = 0,
                                   .parent_fn = tos((byte *)"", 0),
                                   .mod = tos((byte *)"", 0),
                                   .is_global = 0,
                                   .is_used = 0,
                                   .is_changed = 0,
                                   .scope_level = 0,
                                   .is_c = 0,
                                   .is_moved = 0,
                                   .line_nr = 0,
                                   .token_idx = 0});
    };

  } else if (Parser_peek(&/* ? */ *p) == main__TokenKind_key_in) {

    string val = Parser_check_name(p);

    Parser_fgen(p, tos3(" "));

    Parser_check(p, main__TokenKind_key_in);

    Parser_fspace(p);

    string tmp = Parser_get_tmp(p);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    string expr = CGen_end_tmp(p->cgen);

    bool is_range = p->tok == main__TokenKind_dotdot;

    bool is_variadic_arg = string_starts_with(typ, tos3("..."));

    if (is_variadic_arg) {

      typ = string_right(typ, 3);
    };

    string range_end = tos3("");

    if (is_range) {

      Parser_check_types(p, typ, tos3("int"));

      Parser_check_space(p, main__TokenKind_dotdot);

      CGen_start_tmp(p->cgen);

      Parser_check_types(p, Parser_bool_expression(p), tos3("int"));

      range_end = CGen_end_tmp(p->cgen);
    };

    bool is_arr = string_contains(typ, tos3("array"));

    bool is_str = string_eq(typ, tos3("string"));

    if (!is_arr && !is_str && !is_range && !is_variadic_arg) {

      Parser_error(p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    if (!is_variadic_arg) {

      if (p->is_js) {

        Parser_genln(
            p, _STR("var %.*s = %.*s;", tmp.len, tmp.str, expr.len, expr.str));

      } else {

        Parser_genln(p, _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len,
                             tmp.str, expr.len, expr.str));
      };
    };

    string i = Parser_get_tmp(p);

    string var_type = typ;

    if (is_arr) {

      var_type = string_right(typ, 6);

      Parser_gen_for_header(p, i, tmp, var_type, val);

    } else if (is_str) {

      var_type = tos3("byte");

      Parser_gen_for_str_header(p, i, tmp, var_type, val);

    } else if (is_range) {

      var_type = tos3("int");

      Parser_gen_for_range_header(p, i, range_end, tmp, var_type, val);

    } else if (is_variadic_arg) {

      Parser_gen_for_varg_header(p, i, expr, typ, val);
    };

    if (string_ne(val, tos3("_"))) {

      Parser_register_var(p, (Var){.name = val,
                                   .typ = var_type,
                                   .ptr = string_contains(typ, tos3("*")),
                                   .is_changed = 1,
                                   .idx = 0,
                                   .is_arg = 0,
                                   .is_const = 0,
                                   .args = new_array(0, 1, sizeof(Var)),
                                   .attr = tos((byte *)"", 0),
                                   .is_mut = 0,
                                   .is_alloc = 0,
                                   .is_returned = 0,
                                   .ref = 0,
                                   .parent_fn = tos((byte *)"", 0),
                                   .mod = tos((byte *)"", 0),
                                   .is_global = 0,
                                   .is_used = 0,
                                   .scope_level = 0,
                                   .is_c = 0,
                                   .is_moved = 0,
                                   .line_nr = 0,
                                   .token_idx = 0});
    };

  } else {

    Parser_gen(p, tos3("while ("));

    Parser_check_types(p, Parser_bool_expression(p), tos3("bool"));

    Parser_genln(p, tos3(") {"));
  };

  Parser_fspace(p);

  Parser_check(p, main__TokenKind_lcbr);

  Parser_genln(p, tos3(""));

  Parser_statements(p);

  Parser_close_scope(p);

  p->for_expr_cnt--;

  p->returns = 0;
}
void Parser_switch_statement(Parser *p) {

  if (p->tok == main__TokenKind_key_switch) {

    Parser_check(p, main__TokenKind_key_switch);

  } else {

    Parser_check(p, main__TokenKind_key_match);
  };

  CGen_start_tmp(p->cgen);

  string typ = Parser_bool_expression(p);

  bool is_str = string_eq(typ, tos3("string"));

  string expr = CGen_end_tmp(p->cgen);

  Parser_check(p, main__TokenKind_lcbr);

  int i = 0;

  bool all_cases_return = 1;

  while (p->tok == main__TokenKind_key_case ||
         p->tok == main__TokenKind_key_default ||
         Parser_peek(&/* ? */ *p) == main__TokenKind_arrow ||
         p->tok == main__TokenKind_key_else) {

    p->returns = 0;

    if (p->tok == main__TokenKind_key_default ||
        p->tok == main__TokenKind_key_else) {

      Parser_genln(p, tos3("else  { // default:"));

      if (p->tok == main__TokenKind_key_default) {

        Parser_check(p, main__TokenKind_key_default);

        Parser_check(p, main__TokenKind_colon);

      } else {

        Parser_check(p, main__TokenKind_key_else);

        Parser_check(p, main__TokenKind_arrow);
      };

      Parser_statements(p);

      p->returns = all_cases_return && p->returns;

      return;
    };

    if (i > 0) {

      Parser_gen(p, tos3("else "));
    };

    Parser_gen(p, tos3("if ("));

    bool got_comma = 0;

    while (1) {

      if (got_comma) {

        if (is_str) {

          Parser_gen(p, tos3(")"));
        };

        Parser_gen(p, tos3(" || "));
      };

      if (string_eq(typ, tos3("string"))) {

        Parser_gen(p, _STR("string_eq(%.*s, ", expr.len, expr.str));

      } else {

        Parser_gen(p, _STR("%.*s == ", expr.len, expr.str));
      };

      if (p->tok == main__TokenKind_key_case ||
          p->tok == main__TokenKind_key_default) {

        Parser_check(p, p->tok);
      };

      Parser_bool_expression(p);

      if (p->tok != main__TokenKind_comma) {

        break;
      };

      Parser_check(p, main__TokenKind_comma);

      got_comma = 1;
    };

    if (p->tok == main__TokenKind_colon) {

      Parser_check(p, main__TokenKind_colon);

    } else {

      Parser_check(p, main__TokenKind_arrow);
    };

    if (is_str) {

      Parser_gen(p, tos3(")"));
    };

    Parser_gen(p, tos3(") {"));

    Parser_genln(p, tos3("/* case */"));

    Parser_statements(p);

    all_cases_return = all_cases_return && p->returns;

    i++;
  };

  p->returns = 0;
}
string Parser_match_statement(Parser *p, bool is_expr) {

  Parser_check(p, main__TokenKind_key_match);

  CGen_start_tmp(p->cgen);

  string typ = Parser_bool_expression(p);

  string expr = CGen_end_tmp(p->cgen);

  string tmp_var = Parser_get_tmp(p);

  CGen_insert_before(p->cgen,
                     _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp_var.len,
                          tmp_var.str, expr.len, expr.str));

  Parser_check(p, main__TokenKind_lcbr);

  int i = 0;

  bool all_cases_return = 1;

  string res_typ = tos3("");

  while (p->tok != main__TokenKind_rcbr) {

    if (p->tok == main__TokenKind_key_else) {

      Parser_check(p, main__TokenKind_key_else);

      Parser_check(p, main__TokenKind_arrow);

      if (i == 0) {

        if (is_expr) {

          bool got_brace = p->tok == main__TokenKind_lcbr;

          if (got_brace) {

            Parser_check(p, main__TokenKind_lcbr);
          };

          Parser_gen(p, tos3("( "));

          res_typ = Parser_bool_expression(p);

          Parser_gen(p, tos3(" )"));

          if (got_brace) {

            Parser_check(p, main__TokenKind_rcbr);
          };

          string tmp423 = res_typ;
          { Parser_check(p, main__TokenKind_rcbr); }
          return tmp423;
          ;

        } else {

          p->returns = 0;

          Parser_check(p, main__TokenKind_lcbr);

          Parser_genln(p, tos3("{ "));

          Parser_statements(p);

          p->returns = all_cases_return && p->returns;

          string tmp424 = tos3("");
          { Parser_check(p, main__TokenKind_rcbr); }
          return tmp424;
          ;
        };
      };

      if (is_expr) {

        Parser_gen(p, tos3(":("));

        bool got_brace = p->tok == main__TokenKind_lcbr;

        if (got_brace) {

          Parser_check(p, main__TokenKind_lcbr);
        };

        Parser_check_types(p, Parser_bool_expression(p), res_typ);

        if (got_brace) {

          Parser_check(p, main__TokenKind_rcbr);
        };

        Parser_gen(p, strings__repeat(')', i + 1));

        string tmp426 = res_typ;
        { Parser_check(p, main__TokenKind_rcbr); }
        return tmp426;
        ;

      } else {

        p->returns = 0;

        Parser_genln(p, tos3("else // default:"));

        Parser_check(p, main__TokenKind_lcbr);

        Parser_genln(p, tos3("{ "));

        Parser_statements(p);

        p->returns = all_cases_return && p->returns;

        string tmp427 = tos3("");
        { Parser_check(p, main__TokenKind_rcbr); }
        return tmp427;
        ;
      };
    };

    if (i > 0) {

      if (is_expr) {

        Parser_gen(p, tos3(": ("));

      } else {

        Parser_gen(p, tos3("else "));
      };

    } else if (is_expr) {

      Parser_gen(p, tos3("("));
    };

    if (is_expr) {

      Parser_gen(p, tos3("("));

    } else {

      Parser_gen(p, tos3("if ("));
    };

    bool got_comma = 0;

    while (1) {

      if (got_comma) {

        Parser_gen(p, tos3(") || ("));
      };

      if (string_eq(typ, tos3("string"))) {

        Parser_gen(p, _STR("string_eq(%.*s, ", tmp_var.len, tmp_var.str));

      } else {

        Parser_gen(p, _STR("(%.*s == ", tmp_var.len, tmp_var.str));
      };

      p->expected_type = typ;

      Parser_check_types(p, Parser_bool_expression(p), typ);

      p->expected_type = tos3("");

      if (p->tok != main__TokenKind_comma) {

        if (got_comma) {

          Parser_gen(p, tos3(") "));
        };

        break;
      };

      Parser_check(p, main__TokenKind_comma);

      got_comma = 1;
    };

    Parser_gen(p, tos3(") )"));

    Parser_check(p, main__TokenKind_arrow);

    if (is_expr) {

      Parser_gen(p, tos3("? ("));

      Parser_check(p, main__TokenKind_lcbr);

      if (i == 0) {

        res_typ = Parser_bool_expression(p);

      } else {

        Parser_check_types(p, Parser_bool_expression(p), res_typ);
      };

      Parser_check(p, main__TokenKind_rcbr);

      Parser_gen(p, tos3(")"));

    } else {

      p->returns = 0;

      Parser_check(p, main__TokenKind_lcbr);

      Parser_genln(p, tos3("{ "));

      Parser_statements(p);

      all_cases_return = all_cases_return && p->returns;
    };

    i++;
  };

  if (is_expr) {

    Parser_error(p, tos3("Match expession requires \"else\""));
  };

  p->returns = 0;

  string tmp429 = tos3("");
  { Parser_check(p, main__TokenKind_rcbr); }
  return tmp429;
  ;

  { Parser_check(p, main__TokenKind_rcbr); }
}
void Parser_assert_statement(Parser *p) {

  if (Parser_first_pass(&/* ? */ *p)) {

    return;
  };

  Parser_check(p, main__TokenKind_key_assert);

  Parser_fspace(p);

  string tmp = Parser_get_tmp(p);

  Parser_gen(p, _STR("bool %.*s = ", tmp.len, tmp.str));

  Parser_check_types(p, Parser_bool_expression(p), tos3("bool"));

  string filename = main__cescaped_path(p->file_path);

  Parser_genln(
      p,
      _STR(";\n\n\n\nif (!%.*s) {\n  println(tos2((byte *)\"\\x1B[31mFAILED: "
           "%.*s() in %.*s:%d\\x1B[0m\"));\n  g_test_fails++;\n  return;\n  // "
           "TODO\n  // Maybe print all vars in a test function if it fails?\n} "
           "else {\n  g_test_oks++;\n  //println(tos2((byte "
           "*)\"\\x1B[32mPASSED: %.*s()\\x1B[0m\"));\n}\n\n",
           tmp.len, tmp.str, p->cur_fn.name.len, p->cur_fn.name.str,
           filename.len, filename.str, p->scanner->line_nr, p->cur_fn.name.len,
           p->cur_fn.name.str));
}
void Parser_return_st(Parser *p) {

  Parser_check(p, main__TokenKind_key_return);

  Parser_fgen(p, tos3(" "));

  bool fn_returns = string_ne(p->cur_fn.typ, tos3("void"));

  if (fn_returns) {

    if (p->tok == main__TokenKind_rcbr) {

      Parser_error(p, _STR("`%.*s` needs to return `%.*s`", p->cur_fn.name.len,
                           p->cur_fn.name.str, p->cur_fn.typ.len,
                           p->cur_fn.typ.str));

    } else {

      int ph = CGen_add_placeholder(&/* ? */ *p->cgen);

      p->inside_return_expr = 1;

      bool is_none = p->tok == main__TokenKind_key_none;

      p->expected_type = p->cur_fn.typ;

      string expr_type = Parser_bool_expression(p);

      array_string types = new_array_from_c_array(
          0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

      array_string mr_values = new_array_from_c_array(
          1, 1, sizeof(string),
          EMPTY_ARRAY_OF_ELEMS(string, 1){
              string_trim_space(string_right(p->cgen->cur_line, ph))});

      _PUSH(&types, (/*typ = array_string   tmp_typ=string*/ expr_type), tmp438,
            string);

      while (p->tok == main__TokenKind_comma) {

        Parser_check(p, main__TokenKind_comma);

        CGen_start_tmp(p->cgen);

        _PUSH(
            &types,
            (/*typ = array_string   tmp_typ=string*/ Parser_bool_expression(p)),
            tmp439, string);

        _PUSH(&mr_values,
              (/*typ = array_string   tmp_typ=string*/ string_trim_space(
                  CGen_end_tmp(p->cgen))),
              tmp440, string);
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

        array_string tmp443 = mr_values;
        for (int ret_val_idx = 0; ret_val_idx < tmp443.len; ret_val_idx++) {
          string ret_val = ((string *)tmp443.data)[ret_val_idx];

          if (ret_val_idx > 0) {

            ret_fields = string_add(ret_fields, tos3(","));
          };

          ret_fields = string_add(ret_fields, _STR(".var_%d=%.*s", ret_val_idx,
                                                   ret_val.len, ret_val.str));
        };

        CGen_resetln(p->cgen,
                     _STR("(%.*s){%.*s}", p->cur_fn.typ.len, p->cur_fn.typ.str,
                          ret_fields.len, ret_fields.str));
      };

      p->inside_return_expr = 0;

      if (string_ends_with(p->cur_fn.typ, expr_type) && !is_none &&
          string_starts_with(p->cur_fn.typ, tos3("Option_"))) {

        string tmp = Parser_get_tmp(p);

        string ret = string_right(p->cgen->cur_line, ph);

        string typ = string_replace(expr_type, tos3("Option_"), tos3(""));

        CGen_resetln(p->cgen,
                     _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);", expr_type.len,
                          expr_type.str, tmp.len, tmp.str, expr_type.len,
                          expr_type.str, ret.len, ret.str));

        Parser_gen(p, _STR("return opt_ok(&%.*s, sizeof(%.*s))", tmp.len,
                           tmp.str, typ.len, typ.str));

      } else {

        string ret = string_right(p->cgen->cur_line, ph);

        string total_text = tos3("");

        array_string tmp449 = p->cur_fn.defer_text;
        for (int tmp450 = 0; tmp450 < tmp449.len; tmp450++) {
          string text = ((string *)tmp449.data)[tmp450];

          if (string_ne(text, tos3(""))) {

            total_text = string_add(text, total_text);
          };
        };

        if (string_eq(total_text, tos3("")) ||
            string_eq(expr_type, tos3("void*"))) {

          if (string_eq(expr_type,
                        _STR("%.*s*", p->cur_fn.typ.len, p->cur_fn.typ.str))) {

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

      Parser_check_types(p, expr_type, cur_fn_typ_chk);
    };

  } else {

    if (!p->is_vweb &&
        (p->tok == main__TokenKind_name || p->tok == main__TokenKind_number ||
         p->tok == main__TokenKind_str)) {

      Parser_error_with_token_index(
          p,
          _STR("function `%.*s` should not return a value", p->cur_fn.name.len,
               p->cur_fn.name.str),
          p->cur_fn.fn_name_token_idx);
    };

    if (string_eq(p->cur_fn.name, tos3("main"))) {

      Parser_gen(p, tos3("return 0"));

    } else {

      Parser_gen(p, tos3("return"));
    };
  };

  p->returns = 1;
}
string main__prepend_mod(string mod, string name) {

  return _STR("%.*s__%.*s", mod.len, mod.str, name.len, name.str);
}
string Parser_prepend_mod(Parser *p, string name) {

  return main__prepend_mod(p->mod, name);
}
void Parser_go_statement(Parser *p) {

  Parser_check(p, main__TokenKind_key_go);

  int gotoken_idx = Parser_cur_tok_index(&/* ? */ *p);

  if (Parser_peek(&/* ? */ *p) == main__TokenKind_dot) {

    string var_name = p->lit;

    Option_Var tmp454 = Parser_find_var(&/* ? */ *p, var_name);
    if (!tmp454.ok) {
      string err = tmp454.error;

      return;
    }
    Var v = *(Var *)tmp454.data;
    ;

    Parser_mark_var_used(p, v);

    gotoken_idx = Parser_cur_tok_index(&/* ? */ *p);

    Parser_next(p);

    Parser_check(p, main__TokenKind_dot);

    Type typ = Table_find_type(&/* ? */ *p->table, v.typ);

    Option_Fn tmp456 = Table_find_method(
        &/* ? */ *p->table, &/*112 EXP:"Type*" GOT:"Type" */ typ, p->lit);
    if (!tmp456.ok) {
      string err = tmp456.error;

      Parser_error_with_token_index(
          p, _STR("go method missing %.*s", var_name.len, var_name.str),
          gotoken_idx);

      return;
    }
    Fn method = *(Fn *)tmp456.data;
    ;

    Parser_async_fn_call(p, method, 0, var_name, v.typ);

  } else {

    string f_name = p->lit;

    Option_Fn tmp458 = Table_find_fn(&/* ? */ *p->table,
                                     Parser_prepend_mod(&/* ? */ *p, f_name));
    if (!tmp458.ok) {
      string err = tmp458.error;

      println(Table_debug_fns(&/* ? */ *p->table));

      Parser_error_with_token_index(
          p, _STR("can not find function %.*s", f_name.len, f_name.str),
          gotoken_idx);

      return;
    }
    Fn f = *(Fn *)tmp458.data;
    ;

    if (string_eq(f.name, tos3("println")) ||
        string_eq(f.name, tos3("print"))) {

      Parser_error_with_token_index(
          p, tos3("`go` cannot be used with `println`"), gotoken_idx);
    };

    Parser_async_fn_call(p, f, 0, tos3(""), tos3(""));
  };
}
string Parser_js_decode(Parser *p) {

  Parser_check(p, main__TokenKind_name);

  Parser_check(p, main__TokenKind_dot);

  string op = Parser_check_name(p);

  int op_token_idx = Parser_cur_tok_index(&/* ? */ *p);

  if (string_eq(op, tos3("decode"))) {

    Parser_check(p, main__TokenKind_lpar);

    string typ = Parser_get_type(p);

    Parser_check(p, main__TokenKind_comma);

    CGen_start_tmp(p->cgen);

    Parser_check_types(p, Parser_bool_expression(p), tos3("string"));

    string expr = CGen_end_tmp(p->cgen);

    Parser_check(p, main__TokenKind_rpar);

    string tmp = Parser_get_tmp(p);

    string cjson_tmp = Parser_get_tmp(p);

    string decl = _STR("%.*s %.*s; ", typ.len, typ.str, tmp.len, tmp.str);

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    array_Var tmp467 = T.fields;
    for (int tmp468 = 0; tmp468 < tmp467.len; tmp468++) {
      Var field = ((Var *)tmp467.data)[tmp468];

      string def_val = main__type_default(field.typ);

      if (string_ne(def_val, tos3(""))) {

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
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "typedef Option %.*s;", opt_type.len, opt_type.str)),
          tmp471, string);

    Table_register_type(p->table, opt_type);

    return opt_type;

  } else if (string_eq(op, tos3("encode"))) {

    Parser_check(p, main__TokenKind_lpar);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    Type T = Table_find_type(&/* ? */ *p->table, typ);

    Parser_gen_json_for_type(p, T);

    string expr = CGen_end_tmp(p->cgen);

    Parser_check(p, main__TokenKind_rpar);

    Parser_gen(p, _STR("json__json_print(json__jsencode_%.*s(%.*s))", typ.len,
                       typ.str, expr.len, expr.str));

    return tos3("string");

  } else {

    Parser_error_with_token_index(
        p, _STR("bad json op \"%.*s\"", op.len, op.str), op_token_idx);
  };

  return tos3("");
}
void Parser_attribute(Parser *p) {

  Parser_check(p, main__TokenKind_lsbr);

  p->attr = Parser_check_name(p);

  int attr_token_idx = Parser_cur_tok_index(&/* ? */ *p);

  if (p->tok == main__TokenKind_colon) {

    Parser_check(p, main__TokenKind_colon);

    p->attr = string_add(string_add(p->attr, tos3(":")), Parser_check_name(p));
  };

  Parser_check(p, main__TokenKind_rsbr);

  if (p->tok == main__TokenKind_func ||
      (p->tok == main__TokenKind_key_pub &&
       Parser_peek(&/* ? */ *p) == main__TokenKind_func)) {

    Parser_fn_decl(p);

    p->attr = tos3("");

    return;

  } else if (p->tok == main__TokenKind_key_struct) {

    Parser_struct_decl(p);

    p->attr = tos3("");

    return;
  };

  Parser_error_with_token_index(p, tos3("bad attribute usage"), attr_token_idx);
}
void Parser_defer_st(Parser *p) {

  Parser_check(p, main__TokenKind_key_defer);

  Parser_check(p, main__TokenKind_lcbr);

  int pos = p->cgen->lines.len;

  Parser_genln(p, tos3("{"));

  Parser_statements(p);

  *(string *)array_last(p->cur_fn.defer_text) = string_add(
      array_string_join(array_right(p->cgen->lines, pos), tos3("\n")),
      *(string *)array_last(p->cur_fn.defer_text));

  p->cgen->lines = array_left(p->cgen->lines, pos);

  CGen_resetln(p->cgen, tos3(""));
}
void Parser_check_and_register_used_imported_type(Parser *p, string typ_name) {

  int us_idx = string_index(typ_name, tos3("__"));

  if (us_idx != -1) {

    string arg_mod = string_left(typ_name, us_idx);

    if (FileImportTable_known_alias(&/* ? */ p->import_table, arg_mod)) {

      FileImportTable_register_used_import(&/* ? */ p->import_table, arg_mod);
    };
  };
}
void Parser_check_unused_imports(Parser *p) {

  if (string_eq(p->id, tos3("vgen"))) {

    return;
  };

  string output = tos3("");

  map_string tmp480 = p->import_table.imports;
  array_string keys_tmp480 = map_keys(&tmp480);
  for (int l = 0; l < keys_tmp480.len; l++) {
    string alias = ((string *)keys_tmp480.data)[l];
    string mod = {0};
    map_get(tmp480, alias, &mod);

    if (!FileImportTable_is_used_import(&/* ? */ p->import_table, alias)) {

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

  Parser_production_error_with_token_index(
      p,
      _STR("the following imports were never used: %.*s", output.len,
           output.str),
      0);
}
Type Parser_get_type2(Parser *p) {

  bool mul = 0;

  int nr_muls = 0;

  string typ = tos3("");

  TypeCategory cat = main__TypeCategory_struct_;

  if (p->tok == main__TokenKind_func) {

    Fn f = (Fn){.name = tos3("_"),
                .mod = p->mod,
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
                .defer_text = new_array(0, 1, sizeof(string)),
                .fn_name_token_idx = 0};

    Parser_next(p);

    int line_nr = p->scanner->line_nr;

    Parser_fn_args(p, &/*112 EXP:"Fn*" GOT:"Fn" */ f);

    if (p->scanner->line_nr == line_nr) {

      if (p->tok == main__TokenKind_name) {

        f.typ = Parser_get_type(p);

      } else {

        f.typ = tos3("void");
      };

    } else {

      f.typ = tos3("void");
    };

    Type fn_typ = (Type){.name = Fn_typ_str(&/* ? */ f),
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

  bool is_question = p->tok == main__TokenKind_question;

  if (is_question) {

    Parser_check(p, main__TokenKind_question);
  };

  if (p->tok == main__TokenKind_lsbr) {

    Parser_check(p, main__TokenKind_lsbr);

    if (p->tok == main__TokenKind_number) {

      typ = _STR("[%.*s]", p->lit.len, p->lit.str);

      Parser_next(p);

    } else {

      is_arr = 1;
    };

    Parser_check(p, main__TokenKind_rsbr);

    if (p->tok == main__TokenKind_lsbr) {

      Parser_next(p);

      if (p->tok == main__TokenKind_number) {

        typ = string_add(typ, _STR("[%.*s]", p->lit.len, p->lit.str));

        Parser_check(p, main__TokenKind_number);

      } else {

        is_arr2 = 1;
      };

      Parser_check(p, main__TokenKind_rsbr);
    };

    cat = main__TypeCategory_array;
  };

  if (!p->builtin_mod && p->tok == main__TokenKind_name &&
      string_eq(p->lit, tos3("map"))) {

    Parser_next(p);

    Parser_check(p, main__TokenKind_lsbr);

    string key_type = Parser_check_name(p);

    if (string_ne(key_type, tos3("string"))) {

      Parser_error(p, tos3("maps only support string keys for now"));
    };

    Parser_check(p, main__TokenKind_rsbr);

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

  while (p->tok == main__TokenKind_mul) {

    if (Parser_first_pass(&/* ? */ *p)) {

      Parser_warn(p, tos3("use `&Foo` instead of `*Foo`"));
    };

    mul = 1;

    nr_muls++;

    Parser_check(p, main__TokenKind_mul);
  };

  if (p->tok == main__TokenKind_amp) {

    mul = 1;

    nr_muls++;

    Parser_check(p, main__TokenKind_amp);
  };

  typ = string_add(typ, p->lit);

  if (!p->is_struct_init) {

    Parser_fgen(p, p->lit);
  };

  if (string_eq(p->lit, tos3("C")) &&
      Parser_peek(&/* ? */ *p) == main__TokenKind_dot) {

    Parser_next(p);

    Parser_check(p, main__TokenKind_dot);

    typ = p->lit;

  } else {

    if (Parser_peek(&/* ? */ *p) == main__TokenKind_dot) {

      if (!p->builtin_mod &&
          FileImportTable_known_alias(&/* ? */ p->import_table, typ)) {

        string mod =
            FileImportTable_resolve_alias(&/* ? */ p->import_table, typ);

        if (string_contains(mod, tos3("."))) {

          typ = string_replace(mod, tos3("."), tos3("_dot_"));
        };
      };

      Parser_next(p);

      Parser_check(p, main__TokenKind_dot);

      typ = string_add(typ, _STR("__%.*s", p->lit.len, p->lit.str));
    };

    Type t = Table_find_type(&/* ? */ *p->table, typ);

    if (string_eq(t.name, tos3("")) && !p->builtin_mod) {

      if (!string_contains(typ, tos3("array_")) &&
          string_ne(p->mod, tos3("main")) &&
          !string_contains(typ, tos3("__")) &&
          !string_starts_with(typ, tos3("["))) {

        typ = Parser_prepend_mod(&/* ? */ *p, typ);
      };

      t = Table_find_type(&/* ? */ *p->table, typ);

      if (string_eq(t.name, tos3("")) && !p->pref->translated &&
          !Parser_first_pass(&/* ? */ *p) &&
          !string_starts_with(typ, tos3("["))) {

        println(tos3("get_type() bad type"));

        Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
      };
    };
  };

  if (string_eq(typ, tos3("void"))) {

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

  if (is_question) {

    typ = _STR("Option_%.*s", typ.len, typ.str);

    Table_register_type_with_parent(p->table, typ, tos3("Option"));
  };

  if (string_last_index(typ, tos3("__")) > string_index(typ, tos3("__"))) {

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
string main__sql_params2params_gen(array_string sql_params,
                                   array_string sql_types, string qprefix) {

  string params_gen = tos3("");

  array_string tmp2 = sql_params;
  for (int i = 0; i < tmp2.len; i++) {
    string mparam = ((string *)tmp2.data)[i];

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

        main__verror(tos3("orm: only int and string variable types are "
                          "supported in queries"));
      };
    };
  };

  return params_gen;
}
string Parser_select_query(Parser *p, int fn_ph) {

  string qprefix = string_add(
      string_replace(Parser_get_tmp(p), tos3("tmp"), tos3("sql")), tos3("_"));

  p->sql_i = 0;

  p->sql_params = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  p->sql_types = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

  string q = tos3("select ");

  Parser_check(p, main__TokenKind_key_select);

  string n = Parser_check_name(p);

  if (string_eq(n, tos3("count"))) {

    q = string_add(q, tos3("count(*) from "));

    Parser_check_name(p);
  };

  string table_name = Parser_check_name(p);

  Type typ = Table_find_type(&/* ? */ *p->table, table_name);

  if (string_eq(typ.name, tos3(""))) {

    Parser_error(p,
                 _STR("unknown type `%.*s`", table_name.len, table_name.str));
  };

  array_Var fields = new_array_from_c_array(
      0, 0, sizeof(Var), EMPTY_ARRAY_OF_ELEMS(Var, 0){TCCSKIP(0)});

  array_Var tmp18 = typ.fields;
  for (int i = 0; i < tmp18.len; i++) {
    Var field = ((Var *)tmp18.data)[i];

    if (string_ne(field.typ, tos3("string")) &&
        string_ne(field.typ, tos3("int"))) {

      continue;
    };

    _PUSH(&fields, (/*typ = array_Var   tmp_typ=Var*/ field), tmp19, Var);
  };

  if (fields.len == 0) {

    Parser_error(p, _STR("V orm: select: empty fields in `%.*s`",
                         table_name.len, table_name.str));
  };

  if (string_ne((*(Var *)array_get(fields, 0)).name, tos3("id"))) {

    Parser_error(p, _STR("V orm: `id int` must be the first field in `%.*s`",
                         table_name.len, table_name.str));
  };

  if (string_eq(n, tos3("from"))) {

    array_Var tmp22 = fields;
    for (int i = 0; i < tmp22.len; i++) {
      Var field = ((Var *)tmp22.data)[i];

      q = string_add(q, field.name);

      if (i < fields.len - 1) {

        q = string_add(q, tos3(", "));
      };
    };

    q = string_add(q, tos3(" from "));
  };

  array_Var tmp23 = fields;
  for (int tmp24 = 0; tmp24 < tmp23.len; tmp24++) {
    Var field = ((Var *)tmp23.data)[tmp24];

    if (string_ne(field.typ, tos3("string")) &&
        string_ne(field.typ, tos3("int"))) {

      continue;
    };

    Parser_register_var(p, (Var){
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
                           });
  };

  q = string_add(q, table_name);

  if (p->tok == main__TokenKind_name && string_eq(p->lit, tos3("where"))) {

    Parser_next(p);

    CGen_start_tmp(p->cgen);

    p->is_sql = 1;

    Parser_bool_expression(p);

    p->is_sql = 0;

    q = string_add(q, string_add(tos3(" where "), CGen_end_tmp(p->cgen)));
  };

  bool query_one = 0;

  if (p->tok == main__TokenKind_name && string_eq(p->lit, tos3("limit"))) {

    Parser_next(p);

    CGen_start_tmp(p->cgen);

    p->is_sql = 1;

    Parser_bool_expression(p);

    p->is_sql = 0;

    string limit = CGen_end_tmp(p->cgen);

    q = string_add(q, string_add(tos3(" limit "), limit));

    if (string_eq(string_trim_space(limit), tos3("1"))) {

      query_one = 1;
    };
  };

  printf("sql query=\"%.*s\"\n", q.len, q.str);

  CGen_insert_before(
      p->cgen, _STR("// DEBUG_SQL prefix: %.*s | fn_ph: %d | query: \"%.*s\" ",
                    qprefix.len, qprefix.str, fn_ph, q.len, q.str));

  if (string_eq(n, tos3("count"))) {

    CGen_set_placeholder(p->cgen, fn_ph, tos3("pg__DB_q_int("));

    Parser_gen(p, _STR(", tos2(\"%.*s\"))", q.len, q.str));

  } else {

    string tmp = Parser_get_tmp(p);

    strings__Builder obj_gen = strings__new_builder(300);

    array_Var tmp29 = fields;
    for (int i = 0; i < tmp29.len; i++) {
      Var field = ((Var *)tmp29.data)[i];

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
          main__sql_params2params_gen(p->sql_params, p->sql_types, qprefix);

      CGen_insert_before(
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

      CGen_resetln(p->cgen, _STR("opt_%.*s%.*s", qprefix.len, qprefix.str,
                                 tmp.len, tmp.str));

    } else {

      q = string_add(q, tos3(" order by id"));

      string params_gen =
          main__sql_params2params_gen(p->sql_params, p->sql_types, qprefix);

      CGen_insert_before(
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

      CGen_resetln(p->cgen, _STR("%.*sarr_%.*s", qprefix.len, qprefix.str,
                                 tmp.len, tmp.str));
    };
  };

  if (string_eq(n, tos3("count"))) {

    return tos3("int");

  } else if (query_one) {

    string opt_type = _STR("Option_%.*s", table_name.len, table_name.str);

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR(
              "typedef Option %.*s;", opt_type.len, opt_type.str)),
          tmp34, string);

    Table_register_type(p->table, opt_type);

    return opt_type;

  } else {

    Parser_register_array(p,
                          _STR("array_%.*s", table_name.len, table_name.str));

    return _STR("array_%.*s", table_name.len, table_name.str);
  };
}
void Parser_insert_query(Parser *p, int fn_ph) {

  Parser_check_name(p);

  Parser_check(p, main__TokenKind_lpar);

  string var_name = Parser_check_name(p);

  Parser_check(p, main__TokenKind_rpar);

  Option_Var tmp36 = Parser_find_var(&/* ? */ *p, var_name);
  if (!tmp36.ok) {
    string err = tmp36.error;

    return;
  }
  Var var = *(Var *)tmp36.data;
  ;

  Type typ = Table_find_type(&/* ? */ *p->table, var.typ);

  array_Var fields = new_array_from_c_array(
      0, 0, sizeof(Var), EMPTY_ARRAY_OF_ELEMS(Var, 0){TCCSKIP(0)});

  array_Var tmp39 = typ.fields;
  for (int i = 0; i < tmp39.len; i++) {
    Var field = ((Var *)tmp39.data)[i];

    if (string_ne(field.typ, tos3("string")) &&
        string_ne(field.typ, tos3("int"))) {

      continue;
    };

    _PUSH(&fields, (/*typ = array_Var   tmp_typ=Var*/ field), tmp40, Var);
  };

  if (fields.len == 0) {

    Parser_error(p, _STR("V orm: insert: empty fields in `%.*s`", var.typ.len,
                         var.typ.str));
  };

  if (string_ne((*(Var *)array_get(fields, 0)).name, tos3("id"))) {

    Parser_error(p, _STR("V orm: `id int` must be the first field in `%.*s`",
                         var.typ.len, var.typ.str));
  };

  string table_name = var.typ;

  string sfields = tos3("");

  string params = tos3("");

  string vals = tos3("");

  int nr_vals = 0;

  array_Var tmp48 = fields;
  for (int i = 0; i < tmp48.len; i++) {
    Var field = ((Var *)tmp48.data)[i];

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

      Parser_error(p, _STR("V ORM: unsupported type `%.*s`", field.typ.len,
                           field.typ.str));
    };

    if (i < fields.len - 1) {

      sfields = string_add(sfields, tos3(", "));

      vals = string_add(vals, tos3(", "));
    };
  };

  CGen_insert_before(p->cgen,
                     string_add(_STR("char* params[%d];", nr_vals), params));

  CGen_set_placeholder(p->cgen, fn_ph, tos3("PQexecParams( "));

  Parser_genln(p, _STR(".conn, \"insert into %.*s (%.*s) values (%.*s)\", "
                       "%d,\n0, params, 0, 0, 0)",
                       table_name.len, table_name.str, sfields.len, sfields.str,
                       vals.len, vals.str, nr_vals));
}
bool Repl_checks(Repl *r) {

  bool in_string = 0;

  bool is_cut = 0;

  bool was_indent = r->indent > 0;

  for (int i = 0; i < r->line.len; i++) {

    if (string_at(r->line, i) == '\'' &&
        (i == 0 || string_at(r->line, i - 1) != '\\')) {

      in_string = !in_string;
    };

    if (string_at(r->line, i) == '{' && !in_string) {

      r->line = string_add(string_add(string_left(r->line, i + 1), tos3("\n")),
                           string_right(r->line, i + 1));

      is_cut = 1;

      i++;

      r->indent++;
    };

    if (string_at(r->line, i) == '}' && !in_string) {

      r->line = string_add(string_add(string_left(r->line, i), tos3("\n")),
                           string_right(r->line, i));

      is_cut = 1;

      i++;

      r->indent--;

      if (r->indent == 0) {

        r->in_func = 0;
      };
    };

    if (i + 2 < r->line.len && r->indent == 0 &&
        string_at(r->line, i + 1) == 'f' && string_at(r->line, i + 2) == 'n') {

      r->in_func = 1;
    };
  };

  return r->in_func || (was_indent && r->indent <= 0) || r->indent > 0 ||
         is_cut;
}
bool Repl_function_call(Repl *r, string line) {

  array_string tmp17 = r->functions_name;
  for (int tmp18 = 0; tmp18 < tmp17.len; tmp18++) {
    string function = ((string *)tmp17.data)[tmp18];

    if (string_starts_with(line, function)) {

      return 1;
    };
  };

  return 0;
}
void main__repl_help() {

  string version_hash = main__vhash();

  printf("\nV %.*s %.*s\n  help                   Displays this information.\n "
         " Ctrl-C, Ctrl-D, exit   Exits the REPL.\n  clear                  "
         "Clears the screen.\n\n",
         main__Version.len, main__Version.str, version_hash.len,
         version_hash.str);
}
array_string main__run_repl() {

  string version_hash = main__vhash();

  printf("V %.*s %.*s\n", main__Version.len, main__Version.str,
         version_hash.len, version_hash.str);

  println(tos3("Use Ctrl-C or `exit` to exit"));

  string file = tos3(".vrepl.v");

  string temp_file = tos3(".vrepl_temp.v");

  Repl r = (Repl){.indent = 0,
                  .in_func = 0,
                  .line = tos((byte *)"", 0),
                  .lines = new_array(0, 1, sizeof(string)),
                  .temp_lines = new_array(0, 1, sizeof(string)),
                  .functions_name = new_array(0, 1, sizeof(string)),
                  .functions = new_array(0, 1, sizeof(string))};

  string vexe = (*(string *)array_get(os__args, 0));

  while (1) {

    if (r.indent == 0) {

      print(tos3(">>> "));

    } else {

      print(tos3("... "));
    };

    r.line = os__get_raw_line();

    if (string_eq(string_trim_space(r.line), tos3("")) &&
        string_ends_with(r.line, tos3("\n"))) {

      continue;
    };

    r.line = string_trim_space(r.line);

    if (r.line.len == -1 || string_eq(r.line, tos3("")) ||
        string_eq(r.line, tos3("exit"))) {

      break;
    };

    if (string_eq(r.line, tos3("\n"))) {

      continue;
    };

    if (string_eq(r.line, tos3("clear"))) {

      term__erase_display(tos3("2"));

      continue;
    };

    if (string_eq(r.line, tos3("help"))) {

      main__repl_help();

      continue;
    };

    if (string_starts_with(r.line, tos3("fn"))) {

      r.in_func = 1;

      _PUSH(&r.functions_name,
            (/*typ = array_string   tmp_typ=string*/ string_trim_space(
                string_all_before(string_all_after(r.line, tos3("fn")),
                                  tos3("(")))),
            tmp27, string);
    };

    bool was_func = r.in_func;

    if (Repl_checks(&/* ? */ r)) {

      array_string tmp29 = string_split(r.line, tos3("\n"));
      for (int tmp30 = 0; tmp30 < tmp29.len; tmp30++) {
        string line = ((string *)tmp29.data)[tmp30];

        if (r.in_func || was_func) {

          _PUSH(&r.functions, (/*typ = array_string   tmp_typ=string*/ line),
                tmp31, string);

        } else {

          _PUSH(&r.temp_lines, (/*typ = array_string   tmp_typ=string*/ line),
                tmp32, string);
        };
      };

      if (r.indent > 0) {

        continue;
      };

      r.line = tos3("");
    };

    if (string_starts_with(r.line, tos3("print"))) {

      string source_code = string_add(
          string_add(string_add(array_string_join(r.functions, tos3("\n")),
                                array_string_join(r.lines, tos3("\n"))),
                     tos3("\n")),
          r.line);

      os__write_file(file, source_code);

      Option_os__Result tmp34 = os__exec(
          _STR("%.*s run %.*s -repl", vexe.len, vexe.str, file.len, file.str));
      if (!tmp34.ok) {
        string err = tmp34.error;

        main__verror(err);

        array_string tmp35 = new_array_from_c_array(
            0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});
        {

          os__rm(file);

          os__rm(temp_file);

          os__rm(string_left(file, file.len - 2));

          os__rm(string_left(temp_file, temp_file.len - 2));
        }
        return tmp35;
        ;
      }
      os__Result s = *(os__Result *)tmp34.data;
      ;

      array_string vals = string_split(s.output, tos3("\n"));

      for (int i = 0; i < vals.len; i++) {

        println((*(string *)array_get(vals, i)));
      };

    } else {

      string temp_line = r.line;

      bool temp_flag = 0;

      bool func_call = Repl_function_call(&/* ? */ r, r.line);

      if (!(string_contains(r.line, tos3(" ")) ||
            string_contains(r.line, tos3(":")) ||
            string_contains(r.line, tos3("=")) ||
            string_contains(r.line, tos3(",")) ||
            string_eq(r.line, tos3(""))) &&
          !func_call) {

        temp_line = _STR("println(%.*s)", r.line.len, r.line.str);

        temp_flag = 1;
      };

      string temp_source_code = string_add(
          string_add(
              string_add(
                  string_add(
                      string_add(array_string_join(r.functions, tos3("\n")),
                                 array_string_join(r.lines, tos3("\n"))),
                      tos3("\n")),
                  array_string_join(r.temp_lines, tos3("\n"))),
              tos3("\n")),
          temp_line);

      os__write_file(temp_file, temp_source_code);

      Option_os__Result tmp44 =
          os__exec(_STR("%.*s run %.*s -repl", vexe.len, vexe.str,
                        temp_file.len, temp_file.str));
      if (!tmp44.ok) {
        string err = tmp44.error;

        main__verror(err);

        array_string tmp45 = new_array_from_c_array(
            0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});
        {

          os__rm(file);

          os__rm(temp_file);

          os__rm(string_left(file, file.len - 2));

          os__rm(string_left(temp_file, temp_file.len - 2));
        }
        return tmp45;
        ;
      }
      os__Result s = *(os__Result *)tmp44.data;
      ;

      if (!func_call && s.exit_code == 0 && !temp_flag) {

        while (r.temp_lines.len > 0) {

          if (!string_starts_with((*(string *)array_get(r.temp_lines, 0)),
                                  tos3("print"))) {

            _PUSH(&r.lines,
                  (/*typ = array_string   tmp_typ=string*/ (
                      *(string *)array_get(r.temp_lines, 0))),
                  tmp48, string);
          };

          v_array_delete(&/* ? */ r.temp_lines, 0);
        };

        _PUSH(&r.lines, (/*typ = array_string   tmp_typ=string*/ r.line), tmp51,
              string);

      } else {

        while (r.temp_lines.len > 0) {

          v_array_delete(&/* ? */ r.temp_lines, 0);
        };
      };

      array_string vals = string_split(s.output, tos3("\n"));

      for (int i = 0; i < vals.len; i++) {

        println((*(string *)array_get(vals, i)));
      };
    };
  };

  array_string tmp56 = r.lines;
  {

    os__rm(file);

    os__rm(temp_file);

    os__rm(string_left(file, file.len - 2));

    os__rm(string_left(temp_file, temp_file.len - 2));
  }
  return tmp56;
  ;

  {

    os__rm(file);

    os__rm(temp_file);

    os__rm(string_left(file, file.len - 2));

    os__rm(string_left(temp_file, temp_file.len - 2));
  }
}
Scanner *main__new_scanner_file(string file_path) {

  if (!os__file_exists(file_path)) {

    main__verror(_STR("%.*s doesn't exist", file_path.len, file_path.str));
  };

  Option_string tmp1 = os__read_file(file_path);
  if (!tmp1.ok) {
    string err = tmp1.error;

    main__verror(
        _STR("scanner: failed to open %.*s", file_path.len, file_path.str));

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
                     vstrlen(c_text) - offset_from_begin);
    };
  };

  Scanner *s = main__new_scanner(raw_text);

  s->file_path = file_path;

  return s;
}
Scanner *main__new_scanner(string text) {

  return (Scanner *)memdup(
      &(Scanner){.text = text,
                 .fmt_out = strings__new_builder(1000),
                 .should_print_line_on_error = 1,
                 .should_print_errors_in_color = 1,
                 .should_print_relative_paths_on_error = 1,
                 .file_path = tos((byte *)"", 0),
                 .pos = 0,
                 .line_nr = 0,
                 .last_nl_pos = 0,
                 .inside_string = 0,
                 .inter_start = 0,
                 .inter_end = 0,
                 .debug = 0,
                 .line_comment = tos((byte *)"", 0),
                 .started = 0,
                 .fmt_indent = 0,
                 .fmt_line_empty = 0,
                 .fn_name = tos((byte *)"", 0),
                 .quote = 0,
                 .file_lines = new_array(0, 1, sizeof(string))},
      sizeof(Scanner));
}
ScanRes main__scan_res(TokenKind tok, string lit) {

  return (ScanRes){tok, lit};
}
string Scanner_ident_name(Scanner *s) {

  int start = s->pos;

  while (1) {

    s->pos++;

    if (s->pos >= s->text.len) {

      break;
    };

    byte c = string_at(s->text, s->pos);

    if (!main__is_name_char(c) && !byte_is_digit(c)) {

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

        Scanner_error(&/* ? */ *s, tos3("malformed octal constant"));
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

  if (Scanner_expect(&/* ? */ *s, tos3(".."), s->pos)) {

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

      Scanner_error(&/* ? */ *s, tos3("no `f` is needed for floats"));
    };
  };

  bool has_exponential_part = 0;

  if (Scanner_expect(&/* ? */ *s, tos3("e+"), s->pos) ||
      Scanner_expect(&/* ? */ *s, tos3("e-"), s->pos)) {

    int exp_start_pos = s->pos += 2;

    while (s->pos < s->text.len && byte_is_digit(string_at(s->text, s->pos))) {

      s->pos++;
    };

    if (exp_start_pos == s->pos) {

      Scanner_error(&/* ? */ *s, tos3("exponent has no digits"));
    };

    has_exponential_part = 1;
  };

  if (s->pos < s->text.len && string_at(s->text, s->pos) == '.') {

    if (has_exponential_part) {

      Scanner_error(&/* ? */ *s, tos3("exponential part should be integer"));

    } else {

      Scanner_error(&/* ? */ *s, tos3("too many decimal points in number"));
    };
  };

  string number = string_substr(s->text, start_pos, s->pos);

  s->pos--;

  return number;
}
string Scanner_ident_number(Scanner *s) {

  if (Scanner_expect(&/* ? */ *s, tos3("0x"), s->pos)) {

    return Scanner_ident_hex_number(s);
  };

  if (Scanner_expect(&/* ? */ *s, tos3("0."), s->pos) ||
      Scanner_expect(&/* ? */ *s, tos3("0e"), s->pos)) {

    return Scanner_ident_dec_number(s);
  };

  if (string_at(s->text, s->pos) == '0') {

    return Scanner_ident_oct_number(s);
  };

  return Scanner_ident_dec_number(s);
}
void Scanner_skip_whitespace(Scanner *s) {

  while (s->pos < s->text.len && byte_is_white(string_at(s->text, s->pos))) {

    if (main__is_nl(string_at(s->text, s->pos)) &&
        !Scanner_expect(&/* ? */ *s, tos3("\r\n"), s->pos - 1)) {

      Scanner_inc_line_number(s);
    };

    s->pos++;
  };
}
ScanRes Scanner_scan(Scanner *s) {

  if (string_ne(s->line_comment, tos3(""))) {
  };

  if (s->started) {

    s->pos++;
  };

  s->started = 1;

  if (s->pos >= s->text.len) {

    return main__scan_res(main__TokenKind_eof, tos3(""));
  };

  if (!s->inside_string) {

    Scanner_skip_whitespace(s);
  };

  if (s->inter_end) {

    if (string_at(s->text, s->pos) == s->quote) {

      s->inter_end = 0;

      return main__scan_res(main__TokenKind_str, tos3(""));
    };

    s->inter_end = 0;

    return main__scan_res(main__TokenKind_str, Scanner_ident_string(s));
  };

  Scanner_skip_whitespace(s);

  if (s->pos >= s->text.len) {

    return main__scan_res(main__TokenKind_eof, tos3(""));
  };

  byte c = string_at(s->text, s->pos);

  byte nextc = '\0';

  if (s->pos + 1 < s->text.len) {

    nextc = string_at(s->text, s->pos + 1);
  };

  if (main__is_name_char(c)) {

    string name = Scanner_ident_name(s);

    byte next_char =
        (s->pos + 1 < s->text.len) ? (string_at(s->text, s->pos + 1)) : ('\0');

    if (main__is_key(name)) {

      return main__scan_res(main__key_to_token(name), tos3(""));
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

    return main__scan_res(main__TokenKind_name, name);

  } else if (byte_is_digit(c) || (c == '.' && byte_is_digit(nextc))) {

    string num = Scanner_ident_number(s);

    return main__scan_res(main__TokenKind_number, num);
  };

  if (c == '+') { /* case */

    if (nextc == '+') {

      s->pos++;

      return main__scan_res(main__TokenKind_inc, tos3(""));

    } else if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_plus_assign, tos3(""));
    };

    return main__scan_res(main__TokenKind_plus, tos3(""));

  } else if (c == '-') { /* case */

    if (nextc == '-') {

      s->pos++;

      return main__scan_res(main__TokenKind_dec, tos3(""));

    } else if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_minus_assign, tos3(""));
    };

    return main__scan_res(main__TokenKind_minus, tos3(""));

  } else if (c == '*') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_mult_assign, tos3(""));
    };

    return main__scan_res(main__TokenKind_mul, tos3(""));

  } else if (c == '^') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_xor_assign, tos3(""));
    };

    return main__scan_res(main__TokenKind_xor, tos3(""));

  } else if (c == '%') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_mod_assign, tos3(""));
    };

    return main__scan_res(main__TokenKind_mod, tos3(""));

  } else if (c == '?') { /* case */

    return main__scan_res(main__TokenKind_question, tos3(""));

  } else if (c == main__single_quote || c == main__double_quote) { /* case */

    return main__scan_res(main__TokenKind_str, Scanner_ident_string(s));

  } else if (c == '`') { /* case */

    return main__scan_res(main__TokenKind_chartoken, Scanner_ident_char(s));

  } else if (c == '(') { /* case */

    return main__scan_res(main__TokenKind_lpar, tos3(""));

  } else if (c == ')') { /* case */

    return main__scan_res(main__TokenKind_rpar, tos3(""));

  } else if (c == '[') { /* case */

    return main__scan_res(main__TokenKind_lsbr, tos3(""));

  } else if (c == ']') { /* case */

    return main__scan_res(main__TokenKind_rsbr, tos3(""));

  } else if (c == '{') { /* case */

    if (s->inside_string) {

      return Scanner_scan(s);
    };

    return main__scan_res(main__TokenKind_lcbr, tos3(""));

  } else if (c == '$') { /* case */

    return main__scan_res(main__TokenKind_dollar, tos3(""));

  } else if (c == '}') { /* case */

    if (s->inside_string) {

      s->pos++;

      if (string_at(s->text, s->pos) == main__single_quote) {

        s->inside_string = 0;

        return main__scan_res(main__TokenKind_str, tos3(""));
      };

      return main__scan_res(main__TokenKind_str, Scanner_ident_string(s));

    } else {

      return main__scan_res(main__TokenKind_rcbr, tos3(""));
    };

  } else if (c == '&') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_and_assign, tos3(""));
    };

    if (nextc == '&') {

      s->pos++;

      return main__scan_res(main__TokenKind_and, tos3(""));
    };

    return main__scan_res(main__TokenKind_amp, tos3(""));

  } else if (c == '|') { /* case */

    if (nextc == '|') {

      s->pos++;

      return main__scan_res(main__TokenKind_logical_or, tos3(""));
    };

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_or_assign, tos3(""));
    };

    return main__scan_res(main__TokenKind_pipe, tos3(""));

  } else if (c == ',') { /* case */

    return main__scan_res(main__TokenKind_comma, tos3(""));

  } else if (c == '@') { /* case */

    s->pos++;

    string name = Scanner_ident_name(s);

    if (string_eq(name, tos3("FN"))) {

      return main__scan_res(main__TokenKind_str, s->fn_name);
    };

    if (string_eq(name, tos3("FILE"))) {

      return main__scan_res(main__TokenKind_str,
                            main__cescaped_path(os__realpath(s->file_path)));
    };

    if (string_eq(name, tos3("LINE"))) {

      return main__scan_res(main__TokenKind_str, int_str((s->line_nr + 1)));
    };

    if (string_eq(name, tos3("COLUMN"))) {

      return main__scan_res(main__TokenKind_str,
                            int_str((Scanner_current_column(&/* ? */ *s))));
    };

    if (string_eq(name, tos3("VHASH"))) {

      return main__scan_res(main__TokenKind_str, main__vhash());
    };

    if (!main__is_key(name)) {

      Scanner_error(
          &/* ? */ *s,
          tos3("@ must be used before keywords (e.g. `@type string`)"));
    };

    return main__scan_res(main__TokenKind_name, name);

  } else if (c == '\r') { /* case */

    if (nextc == '\n') {

      s->pos++;

      s->last_nl_pos = s->pos;

      return main__scan_res(main__TokenKind_nl, tos3(""));
    };

  } else if (c == '\n') { /* case */

    s->last_nl_pos = s->pos;

    return main__scan_res(main__TokenKind_nl, tos3(""));

  } else if (c == '.') { /* case */

    if (nextc == '.') {

      s->pos++;

      if (string_at(s->text, s->pos + 1) == '.') {

        s->pos++;

        return main__scan_res(main__TokenKind_ellipsis, tos3(""));
      };

      return main__scan_res(main__TokenKind_dotdot, tos3(""));
    };

    return main__scan_res(main__TokenKind_dot, tos3(""));

  } else if (c == '#') { /* case */

    int start = s->pos + 1;

    Scanner_ignore_line(s);

    if (nextc == '!') {

      s->line_comment =
          string_trim_space(string_substr(s->text, start + 1, s->pos));

      Scanner_fgenln(s, _STR("// shebang line \"%.*s\"", s->line_comment.len,
                             s->line_comment.str));

      return Scanner_scan(s);
    };

    string hash = string_substr(s->text, start, s->pos);

    return main__scan_res(main__TokenKind_hash, string_trim_space(hash));

  } else if (c == '>') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_ge, tos3(""));

    } else if (nextc == '>') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return main__scan_res(main__TokenKind_righ_shift_assign, tos3(""));
      };

      s->pos++;

      return main__scan_res(main__TokenKind_righ_shift, tos3(""));

    } else {

      return main__scan_res(main__TokenKind_gt, tos3(""));
    };

  } else if (c == 0xE2) { /* case */

    if (nextc == 0x89 && string_at(s->text, s->pos + 2) == 0xA0) {

      s->pos += 2;

      return main__scan_res(main__TokenKind_ne, tos3(""));

    } else if (nextc == 0x89 && string_at(s->text, s->pos + 2) == 0xBD) {

      s->pos += 2;

      return main__scan_res(main__TokenKind_le, tos3(""));

    } else if (nextc == 0xA9 && string_at(s->text, s->pos + 2) == 0xBE) {

      s->pos += 2;

      return main__scan_res(main__TokenKind_ge, tos3(""));
    };

  } else if (c == '<') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_le, tos3(""));

    } else if (nextc == '<') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return main__scan_res(main__TokenKind_left_shift_assign, tos3(""));
      };

      s->pos++;

      return main__scan_res(main__TokenKind_left_shift, tos3(""));

    } else {

      return main__scan_res(main__TokenKind_lt, tos3(""));
    };

  } else if (c == '=') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_eq, tos3(""));

    } else if (nextc == '>') {

      s->pos++;

      return main__scan_res(main__TokenKind_arrow, tos3(""));

    } else {

      return main__scan_res(main__TokenKind_assign, tos3(""));
    };

  } else if (c == ':') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_decl_assign, tos3(""));

    } else {

      return main__scan_res(main__TokenKind_colon, tos3(""));
    };

  } else if (c == ';') { /* case */

    return main__scan_res(main__TokenKind_semicolon, tos3(""));

  } else if (c == '!') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_ne, tos3(""));

    } else {

      return main__scan_res(main__TokenKind_not, tos3(""));
    };

  } else if (c == '~') { /* case */

    return main__scan_res(main__TokenKind_bit_not, tos3(""));

  } else if (c == '/') { /* case */

    if (nextc == '=') {

      s->pos++;

      return main__scan_res(main__TokenKind_div_assign, tos3(""));
    };

    if (nextc == '/') {

      int start = s->pos + 1;

      Scanner_ignore_line(s);

      s->line_comment = string_substr(s->text, start + 1, s->pos);

      s->line_comment = string_trim_space(s->line_comment);

      Scanner_fgenln(s, _STR("// %.*s \"%.*s\"", TokenKind_str(s->prev_tok).len,
                             TokenKind_str(s->prev_tok).str,
                             s->line_comment.len, s->line_comment.str));

      return Scanner_scan(s);
    };

    if (nextc == '*') {

      int start = s->pos;

      int nest_count = 1;

      while (nest_count > 0) {

        s->pos++;

        if (s->pos >= s->text.len) {

          s->line_nr--;

          Scanner_error(&/* ? */ *s, tos3("comment not terminated"));
        };

        if (string_at(s->text, s->pos) == '\n') {

          Scanner_inc_line_number(s);

          continue;
        };

        if (Scanner_expect(&/* ? */ *s, tos3("/*"), s->pos)) {

          nest_count++;

          continue;
        };

        if (Scanner_expect(&/* ? */ *s, tos3("*/"), s->pos)) {

          nest_count--;
        };
      };

      s->pos++;

      int end = s->pos + 1;

      string comm = string_substr(s->text, start, end);

      Scanner_fgenln(s, comm);

      return Scanner_scan(s);
    };

    return main__scan_res(main__TokenKind_div, tos3(""));
  };

#ifdef _WIN32

  if (c == '\0') {

    return main__scan_res(main__TokenKind_eof, tos3(""));
  };

#endif
  ;

  string msg =
      _STR("invalid character `%.*s`", byte_str(c).len, byte_str(c).str);

  if (c == '"') {

    msg = string_add(msg, tos3(", use \' to denote strings"));
  };

  Scanner_error(&/* ? */ *s, msg);

  return main__scan_res(main__TokenKind_eof, tos3(""));
}
int Scanner_current_column(Scanner *s) { return s->pos - s->last_nl_pos; }
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

  byte q = string_at(s->text, s->pos);

  if ((q == main__single_quote || q == main__double_quote) &&
      !s->inside_string) {

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

      Scanner_inc_line_number(s);
    };

    if (c == '0' && s->pos > 2 && string_at(s->text, s->pos - 1) == '\\') {

      Scanner_error(&/* ? */ *s, tos3("0 character in a string literal"));
    };

    if (c == '0' && s->pos > 5 &&
        Scanner_expect(&/* ? */ *s, tos3("\\x0"), s->pos - 3)) {

      Scanner_error(&/* ? */ *s, tos3("0 character in a string literal"));
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

    bool double_slash = Scanner_expect(&/* ? */ *s, tos3("\\\\"), s->pos - 2);

    if (string_at(s->text, s->pos) == '`' &&
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

  if (string_eq(c, tos3("\\`"))) {

    return tos3("`");
  };

  return (string_eq(c, tos3("\'"))) ? (string_add(tos3("\\"), c)) : (c);
}
bool Scanner_expect(Scanner *s, string want, int start_pos) {

  int end_pos = start_pos + want.len;

  if (start_pos < 0 || start_pos >= s->text.len) {

    return 0;
  };

  if (end_pos < 0 || end_pos > s->text.len) {

    return 0;
  };

  int tmp117 = start_pos;
  ;
  for (int tmp118 = tmp117; tmp118 < end_pos; tmp118++) {
    int pos = tmp118;

    if (string_at(s->text, pos) != string_at(want, pos - start_pos)) {

      return 0;
    };
  };

  return 1;
}
void Scanner_debug_tokens(Scanner *s) {

  s->pos = 0;

  s->debug = 1;

  string fname = string_all_after(s->file_path, os__PathSeparator);

  printf("\n===DEBUG TOKENS %.*s===\n", fname.len, fname.str);

  while (1) {

    ScanRes res = Scanner_scan(s);

    TokenKind tok = res.tok;

    string lit = res.lit;

    print(TokenKind_str(tok));

    if (string_ne(lit, tos3(""))) {

      printf(" `%.*s`\n", lit.len, lit.str);

    } else {

      println(tos3(""));
    };

    if (tok == main__TokenKind_eof) {

      println(tos3("============ END OF DEBUG TOKENS =================="));

      break;
    };
  };
}
void Scanner_ignore_line(Scanner *s) {

  Scanner_eat_to_end_of_line(s);

  Scanner_inc_line_number(s);
}
void Scanner_eat_to_end_of_line(Scanner *s) {

  while (s->pos < s->text.len && string_at(s->text, s->pos) != '\n') {

    s->pos++;
  };
}
void Scanner_inc_line_number(Scanner *s) {

  s->last_nl_pos = s->pos;

  s->line_nr++;
}
bool main__is_name_char(byte c) { return byte_is_letter(c) || c == '_'; }
bool main__is_nl(byte c) { return c == '\r' || c == '\n'; }
bool main__contains_capital(string s) {

  string tmp129 = s;
  array_byte bytes_tmp129 = string_bytes(tmp129);
  ;
  for (int tmp130 = 0; tmp130 < tmp129.len; tmp130++) {
    byte c = ((byte *)bytes_tmp129.data)[tmp130];

    if (c >= 'A' && c <= 'Z') {

      return 1;
    };
  };

  return 0;
}
bool main__good_type_name(string s) {

  if (s.len < 4) {

    return 1;
  };

  int tmp131 = 2;
  ;
  for (int tmp132 = tmp131; tmp132 < s.len; tmp132++) {
    int i = tmp132;

    if (byte_is_capital(string_at(s, i)) &&
        byte_is_capital(string_at(s, i - 1)) &&
        byte_is_capital(string_at(s, i - 2))) {

      return 0;
    };
  };

  return 1;
}
void Scanner_validate_var_name(Scanner *s, string name) {

  if (name.len > 11 && !string_contains(name, tos3("_"))) {

    Scanner_error(
        &/* ? */ *s,
        string_add(
            string_add(_STR("bad variable name `%.*s`\n", name.len, name.str),
                       tos3("looks like you have a multi-word name without "
                            "separating them with `_`")),
            tos3("\nfor example, use `registration_date` instead of "
                 "`registrationdate` ")));
  };
}
string Fn_str(Fn f) {

  Table t = (Table){.typesmap = new_map(1, sizeof(Type)),
                    .consts = new_array(0, 1, sizeof(Var)),
                    .fns = new_map(1, sizeof(Fn)),
                    .generic_fns = new_array(0, 1, sizeof(GenTable)),
                    .obf_ids = new_map(1, sizeof(int)),
                    .modules = new_array(0, 1, sizeof(string)),
                    .imports = new_array(0, 1, sizeof(string)),
                    .file_imports = new_map(1, sizeof(FileImportTable)),
                    .cflags = new_array(0, 1, sizeof(CFlag)),
                    .fn_cnt = 0,
                    .obfuscate = 0,
                    .varg_access = new_array(0, 1, sizeof(VargAccess))};

  string str_args =
      Fn_str_args(&/* ? */ f, &/*112 EXP:"Table*" GOT:"Table" */ t);

  return _STR("%.*s(%.*s) %.*s", f.name.len, f.name.str, str_args.len,
              str_args.str, f.typ.len, f.typ.str);
}
string Table_debug_fns(Table *t) {

  strings__Builder s = strings__new_builder(1000);

  map_Fn tmp4 = t->fns;
  array_string keys_tmp4 = map_keys(&tmp4);
  for (int l = 0; l < keys_tmp4.len; l++) {
    string _ = ((string *)keys_tmp4.data)[l];
    Fn f = {0};
    map_get(tmp4, _, &f);

    strings__Builder_writeln(&/* ? */ s, f.name);
  };

  return strings__Builder_str(s);
}
bool main__is_number_type(string typ) {

  return _IN(string, (typ), main__number_types);
}
bool main__is_float_type(string typ) {

  return _IN(string, (typ), main__float_types);
}
bool main__is_primitive_type(string typ) {

  return main__is_number_type(typ) || string_eq(typ, tos3("string"));
}
Table *main__new_table(bool obfuscate) {

  Table *t = (Table *)memdup(
      &(Table){.obfuscate = obfuscate,
               .typesmap = new_map(1, sizeof(Type)),
               .consts = new_array(0, 1, sizeof(Var)),
               .fns = new_map(1, sizeof(Fn)),
               .generic_fns = new_array(0, 1, sizeof(GenTable)),
               .obf_ids = new_map(1, sizeof(int)),
               .modules = new_array(0, 1, sizeof(string)),
               .imports = new_array(0, 1, sizeof(string)),
               .file_imports = new_map(1, sizeof(FileImportTable)),
               .cflags = new_array(0, 1, sizeof(CFlag)),
               .fn_cnt = 0,
               .varg_access = new_array(0, 1, sizeof(VargAccess))},
      sizeof(Table));

  Table_register_type(t, tos3("int"));

  Table_register_type(t, tos3("size_t"));

  Table_register_type_with_parent(t, tos3("i8"), tos3("int"));

  Table_register_type_with_parent(t, tos3("byte"), tos3("int"));

  Table_register_type_with_parent(t, tos3("char"), tos3("int"));

  Table_register_type_with_parent(t, tos3("i16"), tos3("int"));

  Table_register_type_with_parent(t, tos3("u16"), tos3("u32"));

  Table_register_type_with_parent(t, tos3("u32"), tos3("int"));

  Table_register_type_with_parent(t, tos3("i64"), tos3("int"));

  Table_register_type_with_parent(t, tos3("u64"), tos3("u32"));

  Table_register_type(t, tos3("byteptr"));

  Table_register_type(t, tos3("intptr"));

  Table_register_type(t, tos3("f32"));

  Table_register_type(t, tos3("f64"));

  Table_register_type(t, tos3("rune"));

  Table_register_type(t, tos3("bool"));

  Table_register_type(t, tos3("void"));

  Table_register_type(t, tos3("voidptr"));

  Table_register_type(t, tos3("T"));

  Table_register_type(t, tos3("va_list"));

  Table_register_const(t, tos3("stdin"), tos3("int"), tos3("main"));

  Table_register_const(t, tos3("stdout"), tos3("int"), tos3("main"));

  Table_register_const(t, tos3("stderr"), tos3("int"), tos3("main"));

  Table_register_const(t, tos3("errno"), tos3("int"), tos3("main"));

  Table_register_type_with_parent(t, tos3("map_string"), tos3("map"));

  Table_register_type_with_parent(t, tos3("map_int"), tos3("map"));

  return t;
}
string Table_var_cgen_name(Table *t, string name) {

  if (_IN(string, (name), main__CReserved)) {

    return _STR("v_%.*s", name.len, name.str);

  } else {

    return name;
  };
}
void Table_register_module(Table *t, string mod) {

  if (_IN(string, (mod), t->modules)) {

    return;
  };

  _PUSH(&t->modules, (/*typ = array_string   tmp_typ=string*/ mod), tmp6,
        string);
}
void Parser_register_array(Parser *p, string typ) {

  if (string_contains(typ, tos3("*"))) {

    printf("bad arr %.*s\n", typ.len, typ.str);

    return;
  };

  if (!Table_known_type(&/* ? */ *p->table, typ)) {

    Parser_register_type_with_parent(p, typ, tos3("array"));

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR("typedef array %.*s;",
                                                        typ.len, typ.str)),
          tmp7, string);
  };
}
void Parser_register_map(Parser *p, string typ) {

  if (string_contains(typ, tos3("*"))) {

    printf("bad map %.*s\n", typ.len, typ.str);

    return;
  };

  if (!Table_known_type(&/* ? */ *p->table, typ)) {

    Parser_register_type_with_parent(p, typ, tos3("map"));

    _PUSH(&p->cgen->typedefs,
          (/*typ = array_string   tmp_typ=string*/ _STR("typedef map %.*s;",
                                                        typ.len, typ.str)),
          tmp8, string);
  };
}
bool Table_known_mod(Table *table, string mod) {

  return _IN(string, (mod), table->modules);
}
void Table_register_const(Table *t, string name, string typ, string mod) {

  _PUSH(&t->consts,
        (/*typ = array_Var   tmp_typ=Var*/ (Var){
            .name = name,
            .typ = typ,
            .is_const = 1,
            .mod = mod,
            .idx = -1,
            .is_arg = 0,
            .args = new_array(0, 1, sizeof(Var)),
            .attr = tos((byte *)"", 0),
            .is_mut = 0,
            .is_alloc = 0,
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .parent_fn = tos((byte *)"", 0),
            .is_global = 0,
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
            .line_nr = 0,
            .token_idx = 0}),
        tmp9, Var);
}
void Parser_register_global(Parser *p, string name, string typ) {

  _PUSH(&p->table->consts,
        (/*typ = array_Var   tmp_typ=Var*/ (Var){
            .name = name,
            .typ = typ,
            .is_const = 1,
            .is_global = 1,
            .mod = p->mod,
            .is_mut = 1,
            .idx = -1,
            .is_arg = 0,
            .args = new_array(0, 1, sizeof(Var)),
            .attr = tos((byte *)"", 0),
            .is_alloc = 0,
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .parent_fn = tos((byte *)"", 0),
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
            .line_nr = 0,
            .token_idx = 0}),
        tmp10, Var);
}
void Table_register_fn(Table *t, Fn new_fn) {

  map_set(&t->fns, new_fn.name, &(Fn[]){new_fn});
}
bool Table_known_type(Table *table, string typ_) {

  string typ = typ_;

  if (string_starts_with(typ, tos3("...")) && typ.len > 3) {

    typ = string_right(typ, 3);
  };

  if (string_ends_with(typ, tos3("*")) && !string_contains(typ, tos3(" "))) {

    typ = string_left(typ, typ.len - 1);
  };

  Type tmp12 = {0};
  bool tmp13 = map_get(/*table.v : 349*/ table->typesmap, typ, &tmp12);

  Type t = tmp12;

  return t.name.len > 0 && !t.is_placeholder;
}
bool Table_known_type_fast(Table *table, Type *t) {

  return string_ne(t->name, tos3("")) && !t->is_placeholder;
}
Option_Fn Table_find_fn(Table *t, string name) {

  Fn tmp15 = {0};
  bool tmp16 = map_get(/*table.v : 358*/ t->fns, name, &tmp15);

  Fn f = tmp15;

  if (f.name.str != 0) {

    Fn tmp18 = OPTION_CAST(Fn)(f);
    return opt_ok(&tmp18, sizeof(Fn));
  };

  return opt_none();
}
bool Table_known_fn(Table *t, string name) {

  Option_Fn tmp19 = Table_find_fn(&/* ? */ *t, name);
  if (!tmp19.ok) {
    string err = tmp19.error;

    return 0;
  };

  return 1;
}
bool Table_known_const(Table *t, string name) {

  Option_Var tmp20 = Table_find_const(&/* ? */ *t, name);
  if (!tmp20.ok) {
    string err = tmp20.error;

    return 0;
  };

  return 1;
}
void Table_register_type(Table *t, string typ) {

  if (typ.len == 0) {

    return;
  };

  if (_IN_MAP((typ), t->typesmap)) {

    return;
  };

  map_set(&t->typesmap, typ,
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

  map_set(&t->typesmap, typ,
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

  map_set(&t->typesmap, typ.name, &(Type[]){typ});
}
void Table_rewrite_type(Table *t, Type typ) {

  if (typ.name.len == 0) {

    return;
  };

  map_set(&t->typesmap, typ.name, &(Type[]){typ});
}
void Table_add_field(Table *table, string type_name, string field_name,
                     string field_type, bool is_mut, string attr,
                     AccessMod access_mod) {

  if (string_eq(type_name, tos3(""))) {

    print_backtrace();

    main__verror(tos3("add_field: empty type"));
  };

  Type tmp22 = {0};
  bool tmp23 = map_get(/*table.v : 424*/ table->typesmap, type_name, &tmp22);

  Type t = tmp22;

  _PUSH(&t.fields,
        (/*typ = array_Var   tmp_typ=Var*/ (Var){
            .name = field_name,
            .typ = field_type,
            .is_mut = is_mut,
            .attr = attr,
            .parent_fn = type_name,
            .access_mod = access_mod,
            .idx = 0,
            .is_arg = 0,
            .is_const = 0,
            .args = new_array(0, 1, sizeof(Var)),
            .is_alloc = 0,
            .is_returned = 0,
            .ptr = 0,
            .ref = 0,
            .mod = tos((byte *)"", 0),
            .is_global = 0,
            .is_used = 0,
            .is_changed = 0,
            .scope_level = 0,
            .is_c = 0,
            .is_moved = 0,
            .line_nr = 0,
            .token_idx = 0}),
        tmp25, Var);

  map_set(&table->typesmap, type_name, &(Type[]){t});
}
bool Type_has_field(Type *t, string name) {

  Option_Var tmp26 = Type_find_field(&/* ? */ *t, name);
  if (!tmp26.ok) {
    string err = tmp26.error;

    return 0;
  };

  return 1;
}
bool Type_has_enum_val(Type *t, string name) {

  return _IN(string, (name), t->enum_vals);
}
Option_Var Type_find_field(Type *t, string name) {

  array_Var tmp27 = t->fields;
  for (int tmp28 = 0; tmp28 < tmp27.len; tmp28++) {
    Var field = ((Var *)tmp27.data)[tmp28];

    if (string_eq(field.name, name)) {

      Var tmp29 = OPTION_CAST(Var)(field);
      return opt_ok(&tmp29, sizeof(Var));
    };
  };

  return opt_none();
}
bool Table_type_has_field(Table *table, Type *typ, string name) {

  Option_Var tmp30 = Table_find_field(&/* ? */ *table, typ, name);
  if (!tmp30.ok) {
    string err = tmp30.error;

    return 0;
  };

  return 1;
}
Option_Var Table_find_field(Table *table, Type *typ, string name) {

  array_Var tmp31 = typ->fields;
  for (int tmp32 = 0; tmp32 < tmp31.len; tmp32++) {
    Var field = ((Var *)tmp31.data)[tmp32];

    if (string_eq(field.name, name)) {

      Var tmp33 = OPTION_CAST(Var)(field);
      return opt_ok(&tmp33, sizeof(Var));
    };
  };

  if (string_ne(typ->parent, tos3(""))) {

    Type parent = Table_find_type(&/* ? */ *table, typ->parent);

    array_Var tmp35 = parent.fields;
    for (int tmp36 = 0; tmp36 < tmp35.len; tmp36++) {
      Var field = ((Var *)tmp35.data)[tmp36];

      if (string_eq(field.name, name)) {

        Var tmp37 = OPTION_CAST(Var)(field);
        return opt_ok(&tmp37, sizeof(Var));
      };
    };
  };

  return opt_none();
}
void Parser_add_method(Parser *p, string type_name, Fn f) {

  if (!Parser_first_pass(&/* ? */ *p) && string_ne(f.name, tos3("str"))) {

    return;
  };

  if (string_eq(type_name, tos3(""))) {

    print_backtrace();

    main__verror(tos3("add_method: empty type"));
  };

  Type tmp38 = {0};
  bool tmp39 = map_get(/*table.v : 485*/ p->table->typesmap, type_name, &tmp38);

  Type t = tmp38;

  if (string_ne(f.name, tos3("str")) && _IN(Fn, (f), t.methods)) {

    Parser_error(p, _STR("redefinition of method `%.*s.%.*s`", type_name.len,
                         type_name.str, f.name.len, f.name.str));
  };

  _PUSH(&t.methods, (/*typ = array_Fn   tmp_typ=Fn*/ f), tmp41, Fn);

  map_set(&p->table->typesmap, type_name, &(Type[]){t});
}
bool Type_has_method(Type *t, string name) {

  Option_Fn tmp42 = Type_find_method(&/* ? */ *t, name);
  if (!tmp42.ok) {
    string err = tmp42.error;

    return 0;
  };

  return 1;
}
bool Table_type_has_method(Table *table, Type *typ, string name) {

  Option_Fn tmp43 = Table_find_method(&/* ? */ *table, typ, name);
  if (!tmp43.ok) {
    string err = tmp43.error;

    return 0;
  };

  return 1;
}
Option_Fn Table_find_method(Table *table, Type *typ, string name) {

  Type tmp44 = {0};
  bool tmp45 = map_get(/*table.v : 504*/ table->typesmap, typ->name, &tmp44);

  Type t = tmp44;

  array_Fn tmp47 = t.methods;
  for (int tmp48 = 0; tmp48 < tmp47.len; tmp48++) {
    Fn method = ((Fn *)tmp47.data)[tmp48];

    if (string_eq(method.name, name)) {

      Fn tmp49 = OPTION_CAST(Fn)(method);
      return opt_ok(&tmp49, sizeof(Fn));
    };
  };

  if (string_ne(typ->parent, tos3(""))) {

    Type parent = Table_find_type(&/* ? */ *table, typ->parent);

    array_Fn tmp51 = parent.methods;
    for (int tmp52 = 0; tmp52 < tmp51.len; tmp52++) {
      Fn method = ((Fn *)tmp51.data)[tmp52];

      if (string_eq(method.name, name)) {

        Fn tmp53 = OPTION_CAST(Fn)(method);
        return opt_ok(&tmp53, sizeof(Fn));
      };
    };

    return opt_none();
  };

  return opt_none();
}
Option_Fn Type_find_method(Type *t, string name) {

  array_Fn tmp54 = t->methods;
  for (int tmp55 = 0; tmp55 < tmp54.len; tmp55++) {
    Fn method = ((Fn *)tmp54.data)[tmp55];

    if (string_eq(method.name, name)) {

      Fn tmp56 = OPTION_CAST(Fn)(method);
      return opt_ok(&tmp56, sizeof(Fn));
    };
  };

  return opt_none();
}
Type Parser_find_type(Parser *p, string name) {

  Type typ = Table_find_type(&/* ? */ *p->table, name);

  if (string_eq(typ.name, tos3(""))) {

    return Table_find_type(&/* ? */ *p->table,
                           Parser_prepend_mod(&/* ? */ *p, name));
  };

  return typ;
}
Type Table_find_type(Table *t, string name_) {

  string name = name_;

  if (string_ends_with(name, tos3("*")) && !string_contains(name, tos3(" "))) {

    name = string_left(name, name.len - 1);
  };

  if (!(_IN_MAP((name), t->typesmap))) {

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

  Type tmp59 = {0};
  bool tmp60 = map_get(/*table.v : 561*/ t->typesmap, name, &tmp59);

  return tmp59;
}
bool Parser_check_types2(Parser *p, string got_, string expected_, bool throw) {

  string got = got_;

  string expected = expected_;

  if (p->pref->translated) {

    return 1;
  };

  if (string_starts_with(expected, tos3("..."))) {

    expected = string_right(expected, 3);
  };

  if (string_starts_with(got, tos3("..."))) {

    got = string_right(got, 3);
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

  if (main__is_number_type(got) && main__is_number_type(expected) &&
      p->is_const_literal) {

    return 1;
  };

  expected = string_replace(expected, tos3("*"), tos3(""));

  got = string_replace(got, tos3("*"), tos3(""));

  if (string_ne(got, expected)) {

    if (string_ends_with(expected, tos3("er"))) {

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

  return Parser_check_types2(p, got, expected, 1);
}
bool Parser_check_types_no_throw(Parser *p, string got, string expected) {

  return Parser_check_types2(p, got, expected, 0);
}
void Parser_check_types_with_token_index(Parser *p, string got, string expected,
                                         int var_token_idx) {

  if (!Parser_check_types2(p, got, expected, 0)) {

    Parser_error_with_token_index(p,
                                  _STR("expected type `%.*s`, but got `%.*s`",
                                       expected.len, expected.str, got.len,
                                       got.str),
                                  var_token_idx);
  };
}
bool Parser_satisfies_interface(Parser *p, string interface_name, string _typ,
                                bool throw) {

  Type int_typ = Table_find_type(&/* ? */ *p->table, interface_name);

  Type typ = Table_find_type(&/* ? */ *p->table, _typ);

  array_Fn tmp65 = int_typ.methods;
  for (int tmp66 = 0; tmp66 < tmp65.len; tmp66++) {
    Fn method = ((Fn *)tmp65.data)[tmp66];

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
bool Table_is_interface(Table *table, string name) {

  if (!(_IN_MAP((name), table->typesmap))) {

    return 0;
  };

  Type tmp67 = {0};
  bool tmp68 = map_get(/*table.v : 717*/ table->typesmap, name, &tmp67);

  Type t = tmp67;

  return t.cat == main__TypeCategory_interface_;
}
bool Table_main_exists(Table *t) {

  map_Fn tmp70 = t->fns;
  array_string keys_tmp70 = map_keys(&tmp70);
  for (int l = 0; l < keys_tmp70.len; l++) {
    string _ = ((string *)keys_tmp70.data)[l];
    Fn f = {0};
    map_get(tmp70, _, &f);

    if (string_eq(f.name, tos3("main__main"))) {

      return 1;
    };
  };

  return 0;
}
bool Table_has_at_least_one_test_fn(Table *t) {

  map_Fn tmp71 = t->fns;
  array_string keys_tmp71 = map_keys(&tmp71);
  for (int l = 0; l < keys_tmp71.len; l++) {
    string _ = ((string *)keys_tmp71.data)[l];
    Fn f = {0};
    map_get(tmp71, _, &f);

    if (string_starts_with(f.name, tos3("main__test_"))) {

      return 1;
    };
  };

  return 0;
}
Option_Var Table_find_const(Table *t, string name) {

  array_Var tmp72 = t->consts;
  for (int tmp73 = 0; tmp73 < tmp72.len; tmp73++) {
    Var c = ((Var *)tmp72.data)[tmp73];

    if (string_eq(c.name, name)) {

      Var tmp74 = OPTION_CAST(Var)(c);
      return opt_ok(&tmp74, sizeof(Var));
    };
  };

  return opt_none();
}
string Table_cgen_name_type_pair(Table *table, string name, string typ) {

  if (typ.len > 0 && string_at(typ, 0) == '[') {

    string tmp = string_all_after(typ, tos3("]"));

    string size = string_all_before(typ, tos3("]"));

    return _STR("%.*s %.*s  %.*s ]", tmp.len, tmp.str, name.len, name.str,
                size.len, size.str);

  } else if (string_starts_with(typ, tos3("fn ("))) {

    Type T = Table_find_type(&/* ? */ *table, typ);

    if (string_eq(T.name, tos3(""))) {

      println(tos3("this should never happen"));

      v_exit(1);
    };

    string str_args = Fn_str_args(&/* ? */ T.func, table);

    return _STR("%.*s (*%.*s)( %.*s /*FFF*/ )", T.func.typ.len, T.func.typ.str,
                name.len, name.str, str_args.len, str_args.str);

  } else if (string_eq(typ, tos3("tm"))) {

    return _STR("struct /*TM*/ tm %.*s", name.len, name.str);
  };

  return _STR("%.*s %.*s", typ.len, typ.str, name.len, name.str);
}
bool main__is_valid_int_const(string val, string typ) {

  int x = v_string_int(val);

  if (string_eq(typ, tos3("byte"))) { /* case */

    return 0 <= x && x <= math__MaxU8;

  } else if (string_eq(typ, tos3("u16"))) { /* case */

    return 0 <= x && x <= math__MaxU16;

  } else if (string_eq(typ, tos3("i8"))) { /* case */

    return math__MinI8 <= x && x <= math__MaxI8;

  } else if (string_eq(typ, tos3("i16"))) { /* case */

    return math__MinI16 <= x && x <= math__MaxI16;

  } else if (string_eq(typ, tos3("int"))) { /* case */

    return math__MinI32 <= x && x <= math__MaxI32;
  };

  return 1;
}
void Table_register_generic_fn(Table *t, string fn_name) {

  _PUSH(&t->generic_fns,
        (/*typ = array_GenTable   tmp_typ=GenTable*/ (GenTable){
            fn_name, new_array_from_c_array(
                         0, 0, sizeof(string),
                         EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)})}),
        tmp82, GenTable);
}
array_string Table_fn_gen_types(Table *t, string fn_name) {

  array_GenTable tmp83 = t->generic_fns;
  for (int _ = 0; _ < tmp83.len; _++) {
    GenTable f = ((GenTable *)tmp83.data)[_];

    if (string_eq(f.fn_name, fn_name)) {

      return f.types;
    };
  };

  main__verror(_STR("function %.*s not found", fn_name.len, fn_name.str));

  return new_array_from_c_array(0, 0, sizeof(string),
                                EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});
}
void Table_register_generic_fn_type(Table *t, string fn_name, string typ) {

  array_GenTable tmp84 = t->generic_fns;
  for (int i = 0; i < tmp84.len; i++) {
    GenTable f = ((GenTable *)tmp84.data)[i];

    if (string_eq(f.fn_name, fn_name)) {

      _PUSH(&(*(GenTable *)array_get(t->generic_fns, i)).types,
            (/*typ = array_string   tmp_typ=string*/ typ), tmp87, string);

      return;
    };
  };
}
string Parser_typ_to_fmt(Parser *p, string typ, int level) {

  Type t = Table_find_type(&/* ? */ *p->table, typ);

  if (t.cat == main__TypeCategory_enum_) {

    return tos3("%d");
  };

  if (string_eq(typ, tos3("string"))) { /* case */

    return tos3("%.*s");

  } else if (string_eq(typ, tos3("ustring"))) { /* case */

    return tos3("%.*s");

  } else if (string_eq(typ, tos3("byte")) || string_eq(typ, tos3("bool")) ||
             string_eq(typ, tos3("int")) || string_eq(typ, tos3("char")) ||
             string_eq(typ, tos3("byte")) || string_eq(typ, tos3("i16")) ||
             string_eq(typ, tos3("i8"))) { /* case */

    return tos3("%d");

  } else if (string_eq(typ, tos3("u16")) ||
             string_eq(typ, tos3("u32"))) { /* case */

    return tos3("%u");

  } else if (string_eq(typ, tos3("f64")) ||
             string_eq(typ, tos3("f32"))) { /* case */

    return tos3("%f");

  } else if (string_eq(typ, tos3("i64"))) { /* case */

    return tos3("%lld");

  } else if (string_eq(typ, tos3("u64"))) { /* case */

    return tos3("%llu");

  } else if (string_eq(typ, tos3("byte*")) ||
             string_eq(typ, tos3("byteptr"))) { /* case */

    return tos3("%s");

  } else if (string_eq(typ, tos3("void"))) { /* case */

    Parser_error(p, tos3("cannot interpolate this value"));

  } else { // default:

    if (string_ends_with(typ, tos3("*"))) {

      return tos3("%p");
    };
  };

  if (string_ne(t.parent, tos3("")) && level == 0) {

    return Parser_typ_to_fmt(p, t.parent, level + 1);
  };

  return tos3("");
}
bool main__is_compile_time_const(string s_) {

  string s = string_trim_space(s_);

  if (string_eq(s, tos3(""))) {

    return 0;
  };

  if (string_contains(s, tos3("\'"))) {

    return 1;
  };

  string tmp90 = s;
  array_byte bytes_tmp90 = string_bytes(tmp90);
  ;
  for (int tmp91 = 0; tmp91 < tmp90.len; tmp91++) {
    byte c = ((byte *)bytes_tmp90.data)[tmp91];

    if (!((c >= '0' && c <= '9') || c == '.')) {

      return 0;
    };
  };

  return 1;
}
string Table_qualify_module(Table *table, string mod, string file_path) {

  array_string tmp92 = table->imports;
  for (int tmp93 = 0; tmp93 < tmp92.len; tmp93++) {
    string m = ((string *)tmp92.data)[tmp93];

    if (string_contains(m, tos3(".")) && string_contains(m, mod)) {

      array_string m_parts = string_split(m, tos3("."));

      string m_path = array_string_join(m_parts, os__PathSeparator);

      if (string_eq(mod, (*(string *)array_get(m_parts, m_parts.len - 1))) &&
          string_contains(file_path, m_path)) {

        return m;
      };
    };
  };

  return mod;
}
FileImportTable Table_get_file_import_table(Table *table, string id) {

  if (_IN_MAP((id), table->file_imports)) {

    FileImportTable tmp98 = {0};
    bool tmp99 = map_get(/*table.v : 883*/ table->file_imports, id, &tmp98);

    return tmp98;
  };

  return main__new_file_import_table(id);
}
FileImportTable main__new_file_import_table(string file_path) {

  return (FileImportTable){.file_path = file_path,
                           .imports = new_map(1, sizeof(string)),
                           .module_name = tos((byte *)"", 0),
                           .used_imports = new_array(0, 1, sizeof(string)),
                           .import_tok_idx = new_map(1, sizeof(int))};
}
bool FileImportTable_known_import(FileImportTable *fit, string mod) {

  return _IN_MAP((mod), fit->imports) ||
         FileImportTable_is_aliased(&/* ? */ *fit, mod);
}
void FileImportTable_register_import(FileImportTable *fit, string mod,
                                     int tok_idx) {

  FileImportTable_register_alias(fit, mod, mod, tok_idx);
}
void FileImportTable_register_alias(FileImportTable *fit, string alias,
                                    string mod, int tok_idx) {

  string tmp100 = tos((byte *)"", 0);
  bool tmp101 = map_get(/*table.v : 905*/ fit->imports, alias, &tmp100);

  if (!tmp101)
    tmp100 = tos((byte *)"", 0);

  if (_IN_MAP((alias), fit->imports) && string_ne(tmp100, mod)) {

    main__verror(_STR("cannot import %.*s as %.*s: import name %.*s already in "
                      "use in \"%.*s\"",
                      mod.len, mod.str, alias.len, alias.str, alias.len,
                      alias.str, fit->file_path.len, fit->file_path.str));
  };

  if (string_contains(mod, tos3(".internal."))) {

    array_string mod_parts = string_split(mod, tos3("."));

    array_string internal_mod_parts = new_array_from_c_array(
        0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});

    array_string tmp104 = mod_parts;
    for (int tmp105 = 0; tmp105 < tmp104.len; tmp105++) {
      string part = ((string *)tmp104.data)[tmp105];

      if (string_eq(part, tos3("internal"))) {

        break;
      };

      _PUSH(&internal_mod_parts, (/*typ = array_string   tmp_typ=string*/ part),
            tmp106, string);
    };

    string internal_parent = array_string_join(internal_mod_parts, tos3("."));

    if (!string_starts_with(fit->module_name, internal_parent)) {

      main__verror(_STR("module %.*s can only be imported internally by libs",
                        mod.len, mod.str));
    };
  };

  map_set(&fit->imports, alias, &(string[]){mod});

  map_set(&fit->import_tok_idx, mod, &(int[]){tok_idx});
}
int FileImportTable_get_import_tok_idx(FileImportTable *fit, string mod) {

  int tmp108 = 0;
  bool tmp109 = map_get(/*table.v : 926*/ fit->import_tok_idx, mod, &tmp108);

  return tmp108;
}
bool FileImportTable_known_alias(FileImportTable *fit, string alias) {

  return _IN_MAP((alias), fit->imports);
}
bool FileImportTable_is_aliased(FileImportTable *fit, string mod) {

  map_string tmp110 = fit->imports;
  array_string keys_tmp110 = map_keys(&tmp110);
  for (int l = 0; l < keys_tmp110.len; l++) {
    string _ = ((string *)keys_tmp110.data)[l];
    string val = {0};
    map_get(tmp110, _, &val);

    if (string_eq(val, mod)) {

      return 1;
    };
  };

  return 0;
}
string FileImportTable_resolve_alias(FileImportTable *fit, string alias) {

  string tmp111 = tos((byte *)"", 0);
  bool tmp112 = map_get(/*table.v : 943*/ fit->imports, alias, &tmp111);

  if (!tmp112)
    tmp111 = tos((byte *)"", 0);

  return tmp111;
}
void FileImportTable_register_used_import(FileImportTable *fit, string alias) {

  if (!(_IN(string, (alias), fit->used_imports))) {

    _PUSH(&fit->used_imports, (/*typ = array_string   tmp_typ=string*/ alias),
          tmp113, string);
  };
}
bool FileImportTable_is_used_import(FileImportTable *fit, string alias) {

  return _IN(string, (alias), fit->used_imports);
}
bool Type_contains_field_type(Type *t, string typ) {

  if (!byte_is_capital(string_at(t->name, 0))) {

    return 0;
  };

  array_Var tmp116 = t->fields;
  for (int tmp117 = 0; tmp117 < tmp116.len; tmp117++) {
    Var field = ((Var *)tmp116.data)[tmp117];

    if (string_eq(field.typ, typ)) {

      return 1;
    };
  };

  return 0;
}
string Parser_identify_typo(Parser *p, string name, FileImportTable *fit) {

  if (name.len < 2) {

    return tos3("");
  };

  f32 min_match = 0.50;

  string name_orig = string_replace(string_replace(name, tos3("__"), tos3(".")),
                                    tos3("_dot_"), tos3("."));

  string output = tos3("");

  string n = Table_find_misspelled_fn(&/* ? */ *p->table, name, fit, min_match);

  if (string_ne(n, tos3(""))) {

    output = string_add(output, _STR("\n  * function: `%.*s`", n.len, n.str));
  };

  n = Parser_find_misspelled_local_var(&/* ? */ *p, name_orig, min_match);

  if (string_ne(n, tos3(""))) {

    output = string_add(output, _STR("\n  * variable: `%.*s`", n.len, n.str));
  };

  n = Table_find_misspelled_imported_mod(&/* ? */ *p->table, name_orig, fit,
                                         min_match);

  if (string_ne(n, tos3(""))) {

    output = string_add(output, _STR("\n  * module: `%.*s`", n.len, n.str));
  };

  return output;
}
string Table_find_misspelled_fn(Table *table, string name, FileImportTable *fit,
                                f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_fn = tos3("");

  string n1 = (string_starts_with(name, tos3("main__")))
                  ? (string_right(name, 6))
                  : (name);

  map_Fn tmp125 = table->fns;
  array_string keys_tmp125 = map_keys(&tmp125);
  for (int l = 0; l < keys_tmp125.len; l++) {
    string _ = ((string *)keys_tmp125.data)[l];
    Fn f = {0};
    map_get(tmp125, _, &f);

    if (n1.len - f.name.len > 2 || f.name.len - n1.len > 2) {

      continue;
    };

    if (!(string_eq(f.mod, tos3("")) || string_eq(f.mod, tos3("main")) ||
          string_eq(f.mod, tos3("builtin")))) {

      bool mod_imported = 0;

      map_string tmp127 = fit->imports;
      array_string keys_tmp127 = map_keys(&tmp127);
      for (int l = 0; l < keys_tmp127.len; l++) {
        string _ = ((string *)keys_tmp127.data)[l];
        string m = {0};
        map_get(tmp127, _, &m);

        if (string_eq(f.mod, m)) {

          mod_imported = 1;

          break;
        };
      };

      if (!mod_imported) {

        continue;
      };
    };

    f32 p = strings__dice_coefficient(n1, f.name);

    if (f32_gt(p, closest)) {

      closest = p;

      closest_fn = f.name;
    };
  };

  return (f32_ge(closest, min_match)) ? (closest_fn) : (tos3(""));
}
string Table_find_misspelled_imported_mod(Table *table, string name,
                                          FileImportTable *fit, f32 min_match) {

  f32 closest = ((f32)(0));

  string closest_mod = tos3("");

  string n1 = (string_starts_with(name, tos3("main.")))
                  ? (string_right(name, 5))
                  : (name);

  map_string tmp132 = fit->imports;
  array_string keys_tmp132 = map_keys(&tmp132);
  for (int l = 0; l < keys_tmp132.len; l++) {
    string alias = ((string *)keys_tmp132.data)[l];
    string mod = {0};
    map_get(tmp132, alias, &mod);

    if ((n1.len - alias.len > 2 || alias.len - n1.len > 2)) {

      continue;
    };

    string mod_alias =
        (string_eq(alias, mod))
            ? (alias)
            : (_STR("%.*s (%.*s)", alias.len, alias.str, mod.len, mod.str));

    f32 p = strings__dice_coefficient(n1, alias);

    if (f32_gt(p, closest)) {

      closest = p;

      closest_mod = _STR("%.*s", mod_alias.len, mod_alias.str);
    };
  };

  return (f32_ge(closest, min_match)) ? (closest_mod) : (tos3(""));
}
map_int main__build_keys() {

  map_int res = new_map(1, sizeof(int));

  for (int t = ((int)(main__TokenKind_keyword_beg)) + 1;
       t < ((int)(main__TokenKind_keyword_end)); t++) {

    string key = (*(string *)array_get(main__TokenStr, t));

    map_set(&res, key, &(int[]){((int)(t))});
  };

  return res;
}
array_string main__build_token_str() {

  array_string s = array_repeat(
      new_array_from_c_array(1, 1, sizeof(string),
                             EMPTY_ARRAY_OF_ELEMS(string, 1){tos3("")}),
      main__NrTokens);

  array_set(&/*q*/ s, main__TokenKind_keyword_beg, &(string[]){tos3("")});

  array_set(&/*q*/ s, main__TokenKind_keyword_end, &(string[]){tos3("")});

  array_set(&/*q*/ s, main__TokenKind_eof, &(string[]){tos3("eof")});

  array_set(&/*q*/ s, main__TokenKind_name, &(string[]){tos3("name")});

  array_set(&/*q*/ s, main__TokenKind_number, &(string[]){tos3("number")});

  array_set(&/*q*/ s, main__TokenKind_str, &(string[]){tos3("STR")});

  array_set(&/*q*/ s, main__TokenKind_chartoken, &(string[]){tos3("char")});

  array_set(&/*q*/ s, main__TokenKind_plus, &(string[]){tos3("+")});

  array_set(&/*q*/ s, main__TokenKind_minus, &(string[]){tos3("-")});

  array_set(&/*q*/ s, main__TokenKind_mul, &(string[]){tos3("*")});

  array_set(&/*q*/ s, main__TokenKind_div, &(string[]){tos3("/")});

  array_set(&/*q*/ s, main__TokenKind_mod, &(string[]){tos3("%")});

  array_set(&/*q*/ s, main__TokenKind_xor, &(string[]){tos3("^")});

  array_set(&/*q*/ s, main__TokenKind_bit_not, &(string[]){tos3("~")});

  array_set(&/*q*/ s, main__TokenKind_pipe, &(string[]){tos3("|")});

  array_set(&/*q*/ s, main__TokenKind_hash, &(string[]){tos3("#")});

  array_set(&/*q*/ s, main__TokenKind_amp, &(string[]){tos3("&")});

  array_set(&/*q*/ s, main__TokenKind_inc, &(string[]){tos3("++")});

  array_set(&/*q*/ s, main__TokenKind_dec, &(string[]){tos3("--")});

  array_set(&/*q*/ s, main__TokenKind_and, &(string[]){tos3("&&")});

  array_set(&/*q*/ s, main__TokenKind_logical_or, &(string[]){tos3("||")});

  array_set(&/*q*/ s, main__TokenKind_not, &(string[]){tos3("!")});

  array_set(&/*q*/ s, main__TokenKind_dot, &(string[]){tos3(".")});

  array_set(&/*q*/ s, main__TokenKind_dotdot, &(string[]){tos3("..")});

  array_set(&/*q*/ s, main__TokenKind_ellipsis, &(string[]){tos3("...")});

  array_set(&/*q*/ s, main__TokenKind_comma, &(string[]){tos3(",")});

  array_set(&/*q*/ s, main__TokenKind_semicolon, &(string[]){tos3(";")});

  array_set(&/*q*/ s, main__TokenKind_colon, &(string[]){tos3(":")});

  array_set(&/*q*/ s, main__TokenKind_arrow, &(string[]){tos3("=>")});

  array_set(&/*q*/ s, main__TokenKind_assign, &(string[]){tos3("=")});

  array_set(&/*q*/ s, main__TokenKind_decl_assign, &(string[]){tos3(":=")});

  array_set(&/*q*/ s, main__TokenKind_plus_assign, &(string[]){tos3("+=")});

  array_set(&/*q*/ s, main__TokenKind_minus_assign, &(string[]){tos3("-=")});

  array_set(&/*q*/ s, main__TokenKind_mult_assign, &(string[]){tos3("*=")});

  array_set(&/*q*/ s, main__TokenKind_div_assign, &(string[]){tos3("/=")});

  array_set(&/*q*/ s, main__TokenKind_xor_assign, &(string[]){tos3("^=")});

  array_set(&/*q*/ s, main__TokenKind_mod_assign, &(string[]){tos3("%=")});

  array_set(&/*q*/ s, main__TokenKind_or_assign, &(string[]){tos3("|=")});

  array_set(&/*q*/ s, main__TokenKind_and_assign, &(string[]){tos3("&=")});

  array_set(&/*q*/ s, main__TokenKind_righ_shift_assign,
            &(string[]){tos3(">>=")});

  array_set(&/*q*/ s, main__TokenKind_left_shift_assign,
            &(string[]){tos3("<<=")});

  array_set(&/*q*/ s, main__TokenKind_lcbr, &(string[]){tos3("{")});

  array_set(&/*q*/ s, main__TokenKind_rcbr, &(string[]){tos3("}")});

  array_set(&/*q*/ s, main__TokenKind_lpar, &(string[]){tos3("(")});

  array_set(&/*q*/ s, main__TokenKind_rpar, &(string[]){tos3(")")});

  array_set(&/*q*/ s, main__TokenKind_lsbr, &(string[]){tos3("[")});

  array_set(&/*q*/ s, main__TokenKind_rsbr, &(string[]){tos3("]")});

  array_set(&/*q*/ s, main__TokenKind_eq, &(string[]){tos3("==")});

  array_set(&/*q*/ s, main__TokenKind_ne, &(string[]){tos3("!=")});

  array_set(&/*q*/ s, main__TokenKind_gt, &(string[]){tos3(">")});

  array_set(&/*q*/ s, main__TokenKind_lt, &(string[]){tos3("<")});

  array_set(&/*q*/ s, main__TokenKind_ge, &(string[]){tos3(">=")});

  array_set(&/*q*/ s, main__TokenKind_le, &(string[]){tos3("<=")});

  array_set(&/*q*/ s, main__TokenKind_question, &(string[]){tos3("?")});

  array_set(&/*q*/ s, main__TokenKind_left_shift, &(string[]){tos3("<<")});

  array_set(&/*q*/ s, main__TokenKind_righ_shift, &(string[]){tos3(">>")});

  array_set(&/*q*/ s, main__TokenKind_nl, &(string[]){tos3("NLL")});

  array_set(&/*q*/ s, main__TokenKind_dollar, &(string[]){tos3("$")});

  array_set(&/*q*/ s, main__TokenKind_key_assert, &(string[]){tos3("assert")});

  array_set(&/*q*/ s, main__TokenKind_key_struct, &(string[]){tos3("struct")});

  array_set(&/*q*/ s, main__TokenKind_key_if, &(string[]){tos3("if")});

  array_set(&/*q*/ s, main__TokenKind_key_else, &(string[]){tos3("else")});

  array_set(&/*q*/ s, main__TokenKind_key_return, &(string[]){tos3("return")});

  array_set(&/*q*/ s, main__TokenKind_key_module, &(string[]){tos3("module")});

  array_set(&/*q*/ s, main__TokenKind_key_sizeof, &(string[]){tos3("sizeof")});

  array_set(&/*q*/ s, main__TokenKind_key_go, &(string[]){tos3("go")});

  array_set(&/*q*/ s, main__TokenKind_key_goto, &(string[]){tos3("goto")});

  array_set(&/*q*/ s, main__TokenKind_key_const, &(string[]){tos3("const")});

  array_set(&/*q*/ s, main__TokenKind_key_mut, &(string[]){tos3("mut")});

  array_set(&/*q*/ s, main__TokenKind_key_type, &(string[]){tos3("type")});

  array_set(&/*q*/ s, main__TokenKind_key_for, &(string[]){tos3("for")});

  array_set(&/*q*/ s, main__TokenKind_key_switch, &(string[]){tos3("switch")});

  array_set(&/*q*/ s, main__TokenKind_key_case, &(string[]){tos3("case")});

  array_set(&/*q*/ s, main__TokenKind_func, &(string[]){tos3("fn")});

  array_set(&/*q*/ s, main__TokenKind_key_true, &(string[]){tos3("true")});

  array_set(&/*q*/ s, main__TokenKind_key_false, &(string[]){tos3("false")});

  array_set(&/*q*/ s, main__TokenKind_key_continue,
            &(string[]){tos3("continue")});

  array_set(&/*q*/ s, main__TokenKind_key_break, &(string[]){tos3("break")});

  array_set(&/*q*/ s, main__TokenKind_key_import, &(string[]){tos3("import")});

  array_set(&/*q*/ s, main__TokenKind_key_embed, &(string[]){tos3("embed")});

  array_set(&/*q*/ s, main__TokenKind_key_default,
            &(string[]){tos3("default")});

  array_set(&/*q*/ s, main__TokenKind_key_enum, &(string[]){tos3("enum")});

  array_set(&/*q*/ s, main__TokenKind_key_interface,
            &(string[]){tos3("interface")});

  array_set(&/*q*/ s, main__TokenKind_key_pub, &(string[]){tos3("pub")});

  array_set(&/*q*/ s, main__TokenKind_key_import_const,
            &(string[]){tos3("import_const")});

  array_set(&/*q*/ s, main__TokenKind_key_in, &(string[]){tos3("in")});

  array_set(&/*q*/ s, main__TokenKind_key_atomic, &(string[]){tos3("atomic")});

  array_set(&/*q*/ s, main__TokenKind_key_orelse, &(string[]){tos3("or")});

  array_set(&/*q*/ s, main__TokenKind_key_global,
            &(string[]){tos3("__global")});

  array_set(&/*q*/ s, main__TokenKind_key_union, &(string[]){tos3("union")});

  array_set(&/*q*/ s, main__TokenKind_key_static, &(string[]){tos3("static")});

  array_set(&/*q*/ s, main__TokenKind_key_as, &(string[]){tos3("as")});

  array_set(&/*q*/ s, main__TokenKind_key_defer, &(string[]){tos3("defer")});

  array_set(&/*q*/ s, main__TokenKind_key_match, &(string[]){tos3("match")});

  array_set(&/*q*/ s, main__TokenKind_key_select, &(string[]){tos3("select")});

  array_set(&/*q*/ s, main__TokenKind_key_none, &(string[]){tos3("none")});

  return s;
}
TokenKind main__key_to_token(string key) {

  int tmp7 = 0;
  bool tmp8 = map_get(/*token.v : 237*/ main__KEYWORDS, key, &tmp7);

  TokenKind a = ((TokenKind)(tmp7));

  return a;
}
bool main__is_key(string key) { return ((int)(main__key_to_token(key))) > 0; }
string TokenKind_str(TokenKind t) {

  return (*(string *)array_get(main__TokenStr, ((int)(t))));
}
bool TokenKind_is_decl(TokenKind t) {

  return t == main__TokenKind_key_enum || t == main__TokenKind_key_interface ||
         t == main__TokenKind_func || t == main__TokenKind_key_struct ||
         t == main__TokenKind_key_type || t == main__TokenKind_key_const ||
         t == main__TokenKind_key_import_const ||
         t == main__TokenKind_key_pub || t == main__TokenKind_eof;
}
bool TokenKind_is_assign(TokenKind t) {

  return _IN(TokenKind, (t), main__AssignTokens);
}
bool array_TokenKind_contains(array_TokenKind t, TokenKind val) {

  array_TokenKind tmp12 = t;
  for (int tmp13 = 0; tmp13 < tmp12.len; tmp13++) {
    TokenKind tt = ((TokenKind *)tmp12.data)[tmp13];

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
void Parser_fspace(Parser *p) { Parser_fgen(p, tos3(" ")); }
void Parser_fgenln(Parser *p, string s) { Scanner_fgenln(p->scanner, s); }
void Parser_fmt_inc(Parser *p) { p->scanner->fmt_indent++; }
void Parser_fmt_dec(Parser *p) { p->scanner->fmt_indent--; }
TestSession main__new_test_sesion(string vargs) {

  return (TestSession){
      .vexe = os__executable(),
      .vargs = vargs,
      .files = new_array(0, 1, sizeof(string)),
      .failed = 0,
  };
}
void main__test_v() {

  array_string args = os__args;

  if (string_eq(*(string *)array_last(args), tos3("test"))) {

    println(tos3("Usage:"));

    println(tos3("   A)"));

    println(
        tos3("      v test v  : run all v tests and build all the examples"));

    println(tos3("   B)"));

    println(
        tos3("      v test folder/ : run all v tests in the given folder."));

    println(
        tos3("      v -stats test folder/ : the same, but print more stats."));

    println(tos3("   C)"));

    println(tos3(
        "      v test file_test.v : run test functions in a given test file."));

    println(tos3(
        "      v -stats test file_test.v : as above, but with more stats."));

    println(tos3("   NB: you can also give many and mixed folder/ file_test.v "
                 "arguments after test."));

    println(tos3(""));

    return;
  };

  string args_string = array_string_join(array_right(args, 1), tos3(" "));

  string args_before = string_all_before(args_string, tos3("test "));

  string args_after = string_all_after(args_string, tos3("test "));

  if (string_eq(args_after, tos3("v"))) {

    main__v_test_v(args_before);

    return;
  };

  TestSession ts = main__new_test_sesion(args_before);

  array_string tmp6 = string_split(args_after, tos3(" "));
  for (int tmp7 = 0; tmp7 < tmp6.len; tmp7++) {
    string targ = ((string *)tmp6.data)[tmp7];

    if (os__file_exists(targ) && string_ends_with(targ, tos3("_test.v"))) {

      _PUSH(&ts.files, (/*typ = array_string   tmp_typ=string*/ targ), tmp8,
            string);

      continue;
    };

    if (os__dir_exists(targ)) {

      _PUSH_MANY(
          &ts.files,
          (/*typ = array_string   tmp_typ=string*/ os__walk_ext(
              string_trim_right(targ, os__PathSeparator), tos3("_test.v"))),
          tmp9, array_string);

      continue;
    };

    printf("Unrecognized test file %.*s .\n", targ.len, targ.str);
  };

  println(tos3("Testing..."));

  TestSession_test(&/* ? */ ts);

  println(tos3("---------------------------------------------------------------"
               "-------------"));

  println(benchmark__Benchmark_total_message(&/* ? */ ts.benchmark,
                                             tos3("running V _test.v files")));

  if (ts.failed) {

    v_exit(1);
  };
}
void TestSession_test(TestSession *ts) {

  string ok = term__ok_message(tos3("OK"));

  string fail = term__fail_message(tos3("FAIL"));

  bool cmd_needs_quoting = (string_eq(os__user_os(), tos3("windows")));

  bool show_stats =
      _IN(string, (tos3("-stats")), string_split(ts->vargs, tos3(" ")));

  ts->benchmark = benchmark__new_benchmark();

  array_string tmp14 = ts->files;
  for (int tmp15 = 0; tmp15 < tmp14.len; tmp15++) {
    string dot_relative_file = ((string *)tmp14.data)[tmp15];

    string relative_file =
        string_replace(dot_relative_file, tos3("./"), tos3(""));

    string file = os__realpath(relative_file);

    string tmpc_filepath = string_replace(file, tos3(".v"), tos3(".tmp.c"));

    string cmd = _STR("\"%.*s\" %.*s \"%.*s\"", ts->vexe.len, ts->vexe.str,
                      ts->vargs.len, ts->vargs.str, file.len, file.str);

    if (cmd_needs_quoting) {

      cmd = _STR("\"%.*s\"", cmd.len, cmd.str);
    };

    benchmark__Benchmark_step(&/* ? */ ts->benchmark);

    if (show_stats) {

      println(tos3("-------------------------------------------------"));

      int status = os__system(cmd);

      if (status == 0) {

        benchmark__Benchmark_ok(&/* ? */ ts->benchmark);

      } else {

        benchmark__Benchmark_fail(&/* ? */ ts->benchmark);

        ts->failed = 1;

        continue;
      };

    } else {

      Option_os__Result tmp21 = os__exec(cmd);
      if (!tmp21.ok) {
        string err = tmp21.error;

        benchmark__Benchmark_fail(&/* ? */ ts->benchmark);

        ts->failed = 1;

        println(benchmark__Benchmark_step_message(
            &/* ? */ ts->benchmark,
            _STR("%.*s %.*s", relative_file.len, relative_file.str, fail.len,
                 fail.str)));

        continue;
      }
      os__Result r = *(os__Result *)tmp21.data;
      ;

      if (r.exit_code != 0) {

        benchmark__Benchmark_fail(&/* ? */ ts->benchmark);

        ts->failed = 1;

        println(benchmark__Benchmark_step_message(
            &/* ? */ ts->benchmark,
            _STR("%.*s %.*s\n`%.*s`\n (\n%.*s\n)", relative_file.len,
                 relative_file.str, fail.len, fail.str, file.len, file.str,
                 r.output.len, r.output.str)));

      } else {

        benchmark__Benchmark_ok(&/* ? */ ts->benchmark);

        println(benchmark__Benchmark_step_message(
            &/* ? */ ts->benchmark, _STR("%.*s %.*s", relative_file.len,
                                         relative_file.str, ok.len, ok.str)));
      };
    };

    os__rm(tmpc_filepath);
  };

  benchmark__Benchmark_stop(&/* ? */ ts->benchmark);
}
bool main__stable_example(string example, int index, array_string arr) {

  return !string_contains(example, tos3("vweb"));
}
void main__v_test_v(string args_before_test) {

  string vexe = os__executable();

  string parent_dir = os__dir(vexe);

  os__chdir(parent_dir);

  if (!os__dir_exists(string_add(parent_dir, tos3("/vlib")))) {

    println(tos3("vlib/ is missing, it must be next to the V executable"));

    v_exit(1);
  };

  if (!os__dir_exists(string_add(parent_dir, tos3("/compiler")))) {

    println(tos3("compiler/ is missing, it must be next to the V executable"));

    v_exit(1);
  };

#ifdef __APPLE__

  os__system(_STR("%.*s -o v.c compiler", vexe.len, vexe.str));

  if (os__system(tos3("cc -Werror v.c")) != 0) {

    println(tos3("cc failed to build v.c without warnings"));

    v_exit(1);
  };

  println(tos3("v.c can be compiled without warnings. This is good :)"));

#endif
  ;

  println(tos3("Testing..."));

  TestSession ts = main__new_test_sesion(args_before_test);

  _PUSH_MANY(&ts.files,
             (/*typ = array_string   tmp_typ=string*/ os__walk_ext(
                 parent_dir, tos3("_test.v"))),
             tmp25, array_string);

  TestSession_test(&/* ? */ ts);

  println(benchmark__Benchmark_total_message(&/* ? */ ts.benchmark,
                                             tos3("running V tests")));

  println(tos3("\nBuilding examples..."));

  TestSession es = main__new_test_sesion(args_before_test);

  _PUSH_MANY(
      &es.files,
      (/*typ = array_string   tmp_typ=string*/ array_string_filter(
          os__walk_ext(string_add(parent_dir, tos3("/examples")), tos3(".v")),
          main__stable_example)),
      tmp27, array_string);

  TestSession_test(&/* ? */ es);

  println(benchmark__Benchmark_total_message(&/* ? */ es.benchmark,
                                             tos3("building examples")));

  main__test_vget();

  if (ts.failed || es.failed) {

    v_exit(1);
  };
}
void main__test_vget() {}

////////////////// Reset the file/line numbers //////////
#line 29332 "/tmp/gen_vc/v.c.tmp.c"

void init_consts() {
  g_str_buf = malloc(1000);

  builtin_init();
  builtin__min_cap = 2 << 10;
  builtin__max_cap = 2 << 20;
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
  os__args = new_array_from_c_array(
      0, 0, sizeof(string), EMPTY_ARRAY_OF_ELEMS(string, 0){TCCSKIP(0)});
  os__PathSeparator = tos3("/");
  math__Log2E = 1.0 / math__Ln2;
  math__Log10E = 1.0 / math__Ln10;
  math__MinI8 = -128;
  math__MinI16 = -32768;
  math__MinI32 = -2147483648;
  time__MonthDays = new_array_from_c_array(
      12, 12, sizeof(int),
      EMPTY_ARRAY_OF_ELEMS(int, 12){31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
                                    31});
  time__absoluteZeroYear = ((i64)(-292277022399));
  time__secondsPerHour = 60 * time__secondsPerMinute;
  time__secondsPerDay = 24 * time__secondsPerHour;
  time__secondsPerWeek = 7 * time__secondsPerDay;
  time__daysPer400Years = 365 * 400 + 97;
  time__daysPer100Years = 365 * 100 + 24;
  time__daysPer4Years = 365 * 4 + 1;
  time__daysBefore = new_array_from_c_array(
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
  time__Months = tos3("JanFebMarAprMayJunJulAugSepOctNovDec");
  time__Days = tos3("MonTueWedThuFriSatSun");
  main__CommonCHeaders = tos3(
      "\n\n#include <stdio.h>  // TODO remove all these includes, define all "
      "function signatures and types manually\n#include <stdlib.h>\n#include "
      "<signal.h>\n#include <stdarg.h> // for va_list\n#include <inttypes.h>  "
      "// int64_t etc\n#include <string.h> // memcpy\n\n#ifndef "
      "_WIN32\n#include <ctype.h>\n#include <locale.h> // tolower\n#include "
      "<sys/time.h>\n#include <unistd.h> // sleep	\n#endif\n\n\n#ifdef "
      "__APPLE__\n#include <libproc.h> // proc_pidpath\n#include <execinfo.h> "
      "// backtrace and backtrace_symbols_fd\n#endif\n\n#ifdef "
      "__linux__\n#ifndef __BIONIC__\n#include <execinfo.h> // backtrace and "
      "backtrace_symbols_fd\n#endif\n#pragma weak backtrace\n#pragma weak "
      "backtrace_symbols_fd\n#endif\n\n\n#ifdef __linux__\n#include "
      "<sys/types.h>\n#include <sys/wait.h> // os__wait uses wait on "
      "nix\n#endif\n\n#ifdef __FreeBSD__\n#include <sys/types.h>\n#include "
      "<sys/wait.h> // os__wait uses wait on nix\n#endif\n\n#ifdef "
      "__DragonFly__\n#include <sys/types.h>\n#include <sys/wait.h> // "
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
      "OPTION_CAST(x)\n#endif\n\nvoid pthread_mutex_lock(HANDLE *m) {\n	"
      "WaitForSingleObject(*m, INFINITE);\n}\n\nvoid "
      "pthread_mutex_unlock(HANDLE *m) {\n	"
      "ReleaseMutex(*m);\n}\n#else\n#include "
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
      "load_so(byteptr);\nvoid reload_so();\nvoid init_consts();\n");
  main__js_headers = tos3(
      "\n\nvar array_string = function() {}\nvar array_byte = function() "
      "{}\nvar array_int = function() {}\nvar byte = function() {}\nvar double "
      "= function() {}\nvar int = function() {}\nvar f64 = function() {}\nvar "
      "f32 = function() {}\nvar i64 = function() {}\nvar i32 = function() "
      "{}\nvar i16 = function() {}\nvar u64 = function() {}\nvar u32 = "
      "function() {}\nvar u16 = function() {}\nvar i8 = function() {}\nvar u8 "
      "= function() {}\nvar bool = function() {}\nvar rune = function() "
      "{}\nvar map_string = function() {}\nvar map_int = function() "
      "{}\n\nfunction init_consts() {\n	\n}	\n\n");
  main__dot_ptr = tos3("->");
  main__Version = tos3("0.1.21");
  main__supported_platforms = new_array_from_c_array(
      11, 11, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 11){
          tos3("windows"), tos3("mac"), tos3("linux"), tos3("freebsd"),
          tos3("openbsd"), tos3("netbsd"), tos3("dragonfly"), tos3("msvc"),
          tos3("android"), tos3("js"), tos3("solaris")});
  main__v_modules_path = string_add(os__home_dir(), tos3(".vmodules"));
  main__HKEY_LOCAL_MACHINE = ((RegKey)(0x80000002));
  main__KEY_QUERY_VALUE = (0x0001);
  main__KEY_WOW64_32KEY = (0x0200);
  main__KEY_ENUMERATE_SUB_KEYS = (0x0008);
  main__EmptyFn = (Fn){.name = tos((byte *)"", 0),
                       .mod = tos((byte *)"", 0),
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
                       .defer_text = new_array(0, 1, sizeof(string)),
                       .fn_name_token_idx = 0};
  main__MainFn = (Fn){.name = tos3("main"),
                      .mod = tos((byte *)"", 0),
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
                      .defer_text = new_array(0, 1, sizeof(string)),
                      .fn_name_token_idx = 0};
  main__and_or_error =
      string_add(tos3("use `()` to make the boolean expression clear\n"),
                 tos3("for example: `(a && b) || c` instead of `a && b || c`"));
  main__CReserved = new_array_from_c_array(
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
  main__number_types = new_array_from_c_array(
      11, 11, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 11){tos3("number"), tos3("int"), tos3("i8"),
                                       tos3("i16"), tos3("u16"), tos3("u32"),
                                       tos3("byte"), tos3("i64"), tos3("u64"),
                                       tos3("f32"), tos3("f64")});
  main__float_types = new_array_from_c_array(
      2, 2, sizeof(string),
      EMPTY_ARRAY_OF_ELEMS(string, 2){tos3("f32"), tos3("f64")});
  main__TokenStr = main__build_token_str();
  main__KEYWORDS = main__build_keys();
  main__AssignTokens = new_array_from_c_array(
      11, 11, sizeof(TokenKind),
      EMPTY_ARRAY_OF_ELEMS(TokenKind, 11){
          main__TokenKind_assign, main__TokenKind_plus_assign,
          main__TokenKind_minus_assign, main__TokenKind_mult_assign,
          main__TokenKind_div_assign, main__TokenKind_xor_assign,
          main__TokenKind_mod_assign, main__TokenKind_or_assign,
          main__TokenKind_and_assign, main__TokenKind_righ_shift_assign,
          main__TokenKind_left_shift_assign});
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
  init_consts();
  os__args = os__init_os_args(argc, (byteptr *)argv);

  main__main();

  return 0;
}
