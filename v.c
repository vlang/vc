
#include <inttypes.h> // int64_t etc
#include <signal.h>
#include <stdarg.h> // for va_list
#include <stdio.h> // TODO remove all these includes, define all function signatures and types manually
#include <stdlib.h>

#define STRUCT_DEFAULT_VALUE                                                   \
  {}
#define EMPTY_STRUCT_DECLARATION
#define EMPTY_STRUCT_INIT
#define OPTION_CAST(x) (x)

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <direct.h> // _wgetcwd
#include <fcntl.h>  // _O_U8TEXT
#include <io.h>     // _waccess
#include <shellapi.h>
#include <windows.h>
//#include <WinSock2.h>
#ifdef _MSC_VER
// On MSVC these are the same (as long as /volatile:ms is passed)
#define _Atomic volatile

// MSVC can't parse some things properly
#undef STRUCT_DEFAULT_VALUE
#define STRUCT_DEFAULT_VALUE                                                   \
  { 0 }
#undef EMPTY_STRUCT_DECLARATION
#define EMPTY_STRUCT_DECLARATION void *____dummy_variable;
#undef EMPTY_STRUCT_INIT
#define EMPTY_STRUCT_INIT 0
#define OPTION_CAST(x)
#endif

void pthread_mutex_lock(HANDLE *m) { WaitForSingleObject(*m, INFINITE); }

void pthread_mutex_unlock(HANDLE *m) { ReleaseMutex(*m); }
#else
#include <pthread.h>
#endif

//================================== TYPEDEFS ================================*/

typedef unsigned char byte;
typedef unsigned int uint;
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
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
typedef array array_uint;
typedef array array_float;
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
#define ALLOC_INIT(type, ...)                                                  \
  (type *)memdup((type[]){__VA_ARGS__}, sizeof(type))

//================================== GLOBALS =================================*/
// int V_ZERO = 0;
byteptr g_str_buf;
int load_so(byteptr);
void reload_so();
void init_consts();
int g_test_ok = 1;
/*================================== FNS =================================*/
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <signal.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
typedef struct array array;
typedef array array_int;
typedef array array_string;
typedef array array_byte;
typedef struct string string;
typedef struct ustring ustring;
typedef struct map map;
typedef struct Node Node;
typedef struct Option Option;
typedef struct os__File os__File;
typedef struct os__FileInfo os__FileInfo;
typedef Option Option_string;
typedef array array_ustring;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef struct os__filetime os__filetime;
typedef struct os__win32finddata os__win32finddata;
typedef struct strings__Builder strings__Builder;
typedef struct time__Time time__Time;
typedef Option Option_int;
typedef struct CGen CGen;
typedef struct Fn Fn;
typedef array array_Var;
typedef int BuildMode;
typedef int OS;
typedef int Pass;
typedef struct V V;
typedef struct Preferences Preferences;
typedef struct ModDepGraphNode ModDepGraphNode;
typedef struct ModDepGraph ModDepGraph;
typedef array array_ModDepGraphNode;
typedef struct DepSet DepSet;
typedef array array_FileImportTable;
typedef struct Var Var;
typedef struct Parser Parser;
typedef struct Scanner Scanner;
typedef struct ScanRes ScanRes;
typedef struct Table Table;
typedef array array_Type;
typedef map map_Fn;
typedef struct FileImportTable FileImportTable;
typedef int AccessMod;
typedef struct Type Type;
typedef array array_Fn;
typedef int Token;
typedef array array_Token;
typedef Option Option_string;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_int;
typedef int BuildMode;
typedef int OS;
typedef int Pass;
typedef map map_ModDepGraphNode;
typedef map map_DepSet;
typedef int AccessMod;
typedef int Token;
struct array {
  void *data;
  int len;
  int cap;
  int element_size;
};
struct string {
  int hash_cache;
  byte *str;
  int len;
};
struct ustring {
  string s;
  array_int runes;
  int len;
};
struct map {
  int element_size;
  Node *root;
  array_string _keys;
  int key_i;
  int size;
};
struct Node {
  Node *left;
  Node *right;
  string key;
  void *val;
};
struct Option {
  byte data[255];
  string error;
  bool ok;
};
struct os__File {
  FILE *cfile;
};
struct os__FileInfo {
  string name;
  int size;
};
struct os__filetime {
  u32 dwLowDateTime;
  u32 dwHighDateTime;
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
struct CGen {
  os__File out;
  string out_path;
  array_string typedefs;
  array_string type_aliases;
  array_string includes;
  array_string types;
  array_string thread_args;
  array_string thread_fns;
  array_string consts;
  array_string fns;
  array_string so_fns;
  array_string consts_init;
  array_string lines;
  bool is_user;
  Pass run;
  bool nogen;
  string tmp_line;
  string cur_line;
  string prev_line;
  bool is_tmp;
  string fn_main;
  string stash;
};
struct Fn {
  string name;
  string pkg;
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
  string defer_text;
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
  bool is_play;
  bool is_repl;
  bool is_run;
  bool show_c_cmd;
  bool sanitize;
  bool is_debug;
  bool no_auto_free;
  string cflags;
};
struct ModDepGraphNode {
  string name;
  array_string deps;
  string last_cycle;
};
struct ModDepGraph {
  bool acyclic;
  array_ModDepGraphNode nodes;
};
struct DepSet {
  array_string items;
};
struct Var {
  string typ;
  string name;
  bool is_arg;
  bool is_const;
  bool is_import_const;
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
  int scope_level;
};
struct Parser {
  string file_path;
  string file_name;
  Scanner *scanner;
  int token_idx;
  Token tok;
  Token prev_tok;
  Token prev_tok2;
  string lit;
  CGen *cgen;
  Table *table;
  FileImportTable *import_table;
  Pass run;
  OS os;
  string mod;
  bool inside_const;
  Var expr_var;
  string assigned_type;
  string expected_type;
  int tmp_cnt;
  bool is_script;
  Preferences *pref;
  bool builtin_pkg;
  array_string vh_lines;
  bool inside_if_expr;
  bool is_struct_init;
  int if_expr_cnt;
  int for_expr_cnt;
  bool ptr_cast;
  bool calling_c;
  Fn *cur_fn;
  bool returns;
  string vroot;
  bool is_c_struct_init;
  bool can_chash;
  string attr;
  bool v_script;
  string var_decl_name;
  bool building_v;
  bool is_alloc;
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
};
struct ScanRes {
  Token tok;
  string lit;
};
struct Table {
  array_Type types;
  array_Var consts;
  map_Fn fns;
  map_int obf_ids;
  array_string packages;
  array_string imports;
  array_string flags;
  _Atomic int fn_cnt;
  bool obfuscate;
};
struct FileImportTable {
  string module_name;
  string file_path;
  map_string imports;
};
struct Type {
  string mod;
  string name;
  array_Var fields;
  array_Fn methods;
  string parent;
  Fn func;
  bool is_c;
  bool is_interface;
  bool is_enum;
  array_string enum_vals;
  bool is_placeholder;
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
string array_int_str(array_int a);
void v_array_free(array a);
string array_string_str(array_string a);
string array_byte_hex(array_byte b);
string tos(byte *s, int len);
string tos_clone(byte *s);
string tos2(byte *s);
string string_clone(string a);
string string_replace(string s, string rep, string with);
int string_int(string s);
i32 string_i32(string s);
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
int string_last_index(string s, string p);
int string_index_after(string s, string p, int start);
bool string_contains(string s, string p);
bool string_starts_with(string s, string p);
bool string_ends_with(string s, string p);
string string_to_lower(string s);
string string_to_upper(string s);
string string_find_between(string s, string start, string end);
bool array_string_contains(array_string ar, string val);
bool array_int_contains(array_int ar, int val);
bool is_space(byte c);
bool byte_is_space(byte c);
string string_trim_space(string s);
string string_trim(string s, byte c);
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
string ustring_substr(ustring u, int start, int end);
string ustring_left(ustring u, int pos);
string ustring_right(ustring u, int pos);
byte string_at(string s, int idx);
string ustring_at(ustring u, int idx);
void v_ustring_free(ustring u);
int abs(int a);
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
void print_backtrace();
void v_panic(string s);
void println(string s);
void eprintln(string s);
void v_print(string s);
byte *v_malloc(int n);
byte *v_calloc(int n);
void v_free(void *ptr);
void *memdup(void *src, int sz);
string double_str(double d);
string f64_str(f64 d);
string f32_str(f32 d);
string ptr_str(void *ptr);
string int_str(int nn);
string u8_str(u8 nn);
string i64_str(i64 nn);
string bool_str(bool b);
string int_hex(int n);
string i64_hex(i64 n);
bool array_byte_contains(array_byte a, byte val);
string rune_str(rune c);
string byte_str(byte c);
int utf8_char_len(byte b);
string utf32_to_str(u32 code);
string utf32_to_str_no_malloc(u32 code, void *buf);
int string_utf32_code(string _rune);
u16 *string_to_wide(string _str);
string string_from_wide(u16 *_wstr);
string string_from_wide2(u16 *_wstr, int len);
map new_map(int cap, int elm_size);
Node *new_node(string key, void *val, int element_size);
void map_insert(map *m, Node *n, string key, void *val);
bool Node_find(Node *n, string key, void *out, int element_size);
bool Node_find2(Node *n, string key, int element_size);
void map__set(map *m, string key, void *val);
void map_preorder_keys(map *m, Node *node);
array_string map_keys(map *m);
bool map_get(map m, string key, void *out);
bool map_exists(map m, string key);
bool map__exists(map m, string key);
void v_map_print(map m);
void v_map_free(map m);
string map_string_str(map_string m);
Option opt_ok(void *data, int size);
Option v_error(string s);
void os__todo_remove();
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
int os__system(string cmd);
FILE *os__popen(string path);
string os__exec(string cmd);
string os__getenv(string key);
int os__setenv(string name, string value, bool overwrite);
int os__unsetenv(string name);
bool os__file_exists(string path);
bool os__dir_exists(string path);
void os__mkdir(string path);
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
array_string os__ls(string path);
void os__signal(int signum, void *handler);
int os__fork();
int os__wait();
int os__file_last_mod_unix(string path);
void os__log(string s);
void os__flush_stdout();
void os__print_backtrace();
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
array_int math__digits(int n, int base);
f64 math__erf(f64 a);
f64 math__erfc(f64 a);
f64 math__exp2(f64 a);
int math__recursive_product(int n, int *current_number_ptr);
i64 math__factorial(int n);
f64 math__floor(f64 a);
f64 math__fmod(f64 a, f64 b);
f64 math__gamma(f64 a);
i64 math__gcd(i64 a, i64 b);
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
strings__Builder strings__new_builder(int initial_size);
void strings__Builder_write(strings__Builder *b, string s);
void strings__Builder_writeln(strings__Builder *b, string s);
string strings__Builder_str(strings__Builder b);
void strings__Builder_cut(strings__Builder b, int n);
void strings__Builder_free(strings__Builder *b);
string strings__repeat(byte c, int n);
void rand__seed(int s);
int rand__next(int max);
time__Time time__now();
time__Time time__random();
time__Time time__unix(int u);
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
CGen *new_cgen(string out_name_c);
void CGen_genln(CGen *g, string s);
void CGen_gen(CGen *g, string s);
void CGen_resetln(CGen *g, string s);
void CGen_save(CGen *g);
void CGen_start_tmp(CGen *g);
string CGen_end_tmp(CGen *g);
int CGen_add_placeholder(CGen *g);
void CGen_set_placeholder(CGen *g, int pos, string val);
int CGen_add_placeholder2(CGen *g);
void CGen_set_placeholder2(CGen *g, int pos, string val);
void CGen_insert_before(CGen *g, string val);
void CGen_register_thread_fn(CGen *g, string wrapper_name, string wrapper_text,
                             string struct_text);
string V_prof_counters(V *c);
string Parser_print_prof_counters(Parser *p);
void Parser_gen_type(Parser *p, string s);
void Parser_gen_typedef(Parser *p, string s);
void Parser_gen_type_alias(Parser *p, string s);
void CGen_add_to_main(CGen *g, string s);
void build_thirdparty_obj_file(string flag);
Var Fn_find_var(Fn *f, string name);
void Fn_open_scope(Fn *f);
void Fn_mark_var_used(Fn *f, Var v);
bool Fn_known_var(Fn *f, string name);
void Fn_register_var(Fn *f, Var v);
void Fn_clear_vars(Fn *f);
bool Parser_is_sig(Parser *p);
Fn *new_fn(string pkg, bool is_public);
void Parser_fn_decl(Parser *p);
void Parser_check_unused_variables(Parser *p);
void Parser_async_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                          string receiver_type);
void Parser_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                    string receiver_type);
void Parser_fn_args(Parser *p, Fn *f);
Fn *Parser_fn_call_args(Parser *p, Fn *f);
bool contains_capital(string s);
string Fn_typ_str(Fn f);
string Fn_str_args(Fn *f, Table *table);
void Parser_gen_json_for_type(Parser *p, Type typ);
bool is_js_prim(string typ);
string Parser_decode_array(Parser *p, string typ);
string js_enc_name(string typ);
string js_dec_name(string typ);
string Parser_encode_array(Parser *p, string typ);
string modules_path();
void V_compile(V *v);
void V_cc_windows_cross(V *c);
void V_cc(V *v);
array_string V_v_files_from_dir(V *v, string dir);
void V_add_user_v_files(V *v);
string get_arg(string joined_args, string arg, string def);
string V_module_path(V *v, string pkg);
void V_log(V *v, string s);
V *new_v(array_string args);
array_string run_repl();
array_string env_vflags_and_os_args();
void DepSet_add(DepSet *dset, string item);
DepSet DepSet_diff(DepSet *dset, DepSet otherset);
int DepSet_size(DepSet *dset);
ModDepGraph *new_mod_dep_graph();
void ModDepGraph_from_import_tables(ModDepGraph *graph,
                                    array_FileImportTable import_tables);
void ModDepGraph_add(ModDepGraph *graph, string mod, array_string deps);
ModDepGraph *ModDepGraph_resolve(ModDepGraph *graph);
array_string ModDepGraph_imports(ModDepGraph *graph);
void ModDepGraph_last_node(ModDepGraph *graph);
void ModDepGraph_display(ModDepGraph *graph);
void cc_msvc(V *v);
void build_thirdparty_obj_file_with_msvc(string flag);
Parser V_new_parser(V *c, string path, Pass run);
void Parser_next(Parser *p);
void Parser_log(Parser *p, string s);
void Parser_parse(Parser *p);
void Parser_imports(Parser *p);
void Parser_register_import(Parser *p);
void Parser_const_decl(Parser *p);
void Parser_type_decl(Parser *p);
Fn *Parser_interface_method(Parser *p, string field_name, string receiver);
void Parser_struct_decl(Parser *p);
void Parser_enum_decl(Parser *p, string _enum_name);
string Parser_check_name(Parser *p);
string Parser_check_string(Parser *p);
string Parser_strtok(Parser *p);
void Parser_check_space(Parser *p, Token expected);
void Parser_check(Parser *p, Token expected);
void Parser_error(Parser *p, string s);
bool Parser_first_run(Parser *p);
string Parser_get_type(Parser *p);
void Parser_print_tok(Parser *p);
string Parser_statements(Parser *p);
string Parser_statements_no_rcbr(Parser *p);
void Parser_close_scope(Parser *p);
void Parser_genln(Parser *p, string s);
void Parser_gen(Parser *p, string s);
void Parser_vh_genln(Parser *p, string s);
void Parser_fmt_inc(Parser *p);
void Parser_fmt_dec(Parser *p);
string Parser_statement(Parser *p, bool add_semi);
void Parser_assign_statement(Parser *p, Var v, int ph, bool is_map);
void Parser_var_decl(Parser *p);
string Parser_bool_expression(Parser *p);
string Parser_bterm(Parser *p);
string Parser_name_expr(Parser *p);
string Parser_var_expr(Parser *p, Var v);
bool Parser_fileis(Parser *p, string s);
string Parser_dot(Parser *p, string str_typ, int method_ph);
string Parser_index_expr(Parser *p, string typ, int fn_ph);
string Parser_expression(Parser *p);
string Parser_term(Parser *p);
string Parser_unary(Parser *p);
string Parser_factor(Parser *p);
string Parser_assoc(Parser *p);
void Parser_char_expr(Parser *p);
string Parser_typ_to_fmt(Parser *p, string typ, int level);
string format_str(string str);
void Parser_string_expr(Parser *p);
string Parser_map_init(Parser *p);
string Parser_array_init(Parser *p);
void Parser_register_array(Parser *p, string typ);
void Parser_register_map(Parser *p, string typ);
string Parser_struct_init(Parser *p, bool is_c_struct_init);
string Parser_cast(Parser *p, string typ);
string Parser_get_tmp(Parser *p);
int Parser_get_tmp_counter(Parser *p);
string os_name_to_ifdef(string name);
void Parser_comp_time(Parser *p);
void Parser_chash(Parser *p);
string Parser_if_st(Parser *p, bool is_expr, int elif_depth);
void Parser_for_st(Parser *p);
void Parser_switch_statement(Parser *p);
void Parser_assert_statement(Parser *p);
void Parser_return_st(Parser *p);
string prepend_pkg(string pkg, string name);
string Parser_prepend_pkg(Parser *p, string name);
void Parser_go_statement(Parser *p);
void Parser_register_var(Parser *p, Var v);
string Parser_js_decode(Parser *p);
bool is_compile_time_const(string s);
void Parser_attribute(Parser *p);
void Parser_defer_st(Parser *p);
void Scanner_fgen(Scanner *scanner, string s);
void Scanner_fgenln(Scanner *scanner, string s);
void Parser_fgen(Parser *p, string s);
void Parser_fspace(Parser *p);
void Parser_fgenln(Parser *p, string s);
Token Parser_peek(Parser *p);
void Parser_create_type_string(Parser *p, Type T, string name);
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
void Scanner_error(Scanner *s, string msg);
string Scanner_ident_string(Scanner *s);
string Scanner_ident_char(Scanner *s);
Token Scanner_peek(Scanner *s);
bool Scanner_expect(Scanner *s, string want, int start_pos);
void Scanner_debug_tokens(Scanner *s);
bool is_name_char(byte c);
bool is_nl(byte c);
int Scanner_get_opening_bracket(Scanner *s);
void Scanner_create_type_string(Scanner *s, Type T, string name);
string Type_str(Type t);
string Fn_str(Fn f);
bool is_number_type(string typ);
bool is_float_type(string typ);
bool is_primitive_type(string typ);
Table *new_table(bool obfuscate);
string Table_var_cgen_name(Table *t, string name);
void Table_register_package(Table *t, string pkg);
bool Table_known_pkg(Table *table, string pkg);
void Table_register_const(Table *t, string name, string typ, string mod,
                          bool is_imported);
void Parser_register_global(Parser *p, string name, string typ);
void Table_register_fn(Table *t, Fn new_fn);
bool Table_known_type(Table *table, string typ);
Fn Table_find_fn(Table *t, string name);
bool Table_known_fn(Table *t, string name);
bool Table_known_const(Table *t, string name);
void Table_register_type(Table *t, string typ);
void Parser_register_type_with_parent(Parser *p, string strtyp, string parent);
void Table_register_type_with_parent(Table *t, string typ, string parent);
void Table_register_type2(Table *t, Type typ);
void Type_add_field(Type *t, string name, string typ, bool is_mut, string attr,
                    AccessMod access_mod);
bool Type_has_field(Type *t, string name);
bool Type_has_enum_val(Type *t, string name);
Var Type_find_field(Type *t, string name);
bool Table_type_has_field(Table *table, Type *typ, string name);
Var Table_find_field(Table *table, Type *typ, string name);
void Type_add_method(Type *t, Fn f);
bool Type_has_method(Type *t, string name);
bool Table_type_has_method(Table *table, Type *typ, string name);
Fn Table_find_method(Table *table, Type *typ, string name);
Fn Type_find_method(Type *t, string name);
Type *Parser_find_type(Parser *p, string name);
Type *Table_find_type(Table *t, string name);
bool Parser__check_types(Parser *p, string got, string expected, bool throw);
bool Parser_check_types(Parser *p, string got, string expected);
bool Parser_check_types_no_throw(Parser *p, string got, string expected);
bool Parser_satisfies_interface(Parser *p, string interface_name, string _typ,
                                bool throw);
string type_default(string typ);
bool Table_is_interface(Table *t, string name);
bool Table_main_exists(Table *t);
Var Table_find_const(Table *t, string name);
string Table_cgen_name(Table *table, Fn *f);
string Table_cgen_name_type_pair(Table *table, string name, string typ);
bool is_valid_int_const(string val, string typ);
string Table_qualify_module(Table *table, string mod, string file_path);
FileImportTable *new_file_import_table(string file_path);
bool FileImportTable_known_import(FileImportTable *fit, string mod);
void FileImportTable_register_import(FileImportTable *fit, string mod);
void FileImportTable_register_alias(FileImportTable *fit, string alias,
                                    string mod);
bool FileImportTable_known_alias(FileImportTable *fit, string alias);
bool FileImportTable_is_aliased(FileImportTable *fit, string mod);
string FileImportTable_resolve_alias(FileImportTable *fit, string alias);
map_int build_keys();
array_string build_token_str();
Token key_to_token(string key);
bool is_key(string key);
string Token_str(Token t);
bool Token_is_decl(Token t);
bool Token_is_assign(Token t);
bool array_Token_contains(array_Token t, Token val);
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
string time__Months;
string time__Days;
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
Fn *main__EmptyFn;
Fn *main__MainFn;
#define main__MaxModuleDepth 4
#define main__AccessMod_private 0
#define main__AccessMod_private_mut 1
#define main__AccessMod_public 2
#define main__AccessMod_public_mut 3
#define main__AccessMod_public_mut_mut 4
array_string main__CReserved;
array_string main__NUMBER_TYPES;
array_string main__FLOAT_TYPES;
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
#define main__Token_key_sizeof 84
#define main__Token_key_struct 85
#define main__Token_key_switch 86
#define main__Token_key_true 87
#define main__Token_key_type 88
#define main__Token_key_orelse 89
#define main__Token_key_union 90
#define main__Token_key_pub 91
#define main__Token_key_static 92
#define main__Token_keyword_end 93
#define main__NrTokens 140
array_string main__TokenStr;
map_int main__KEYWORDS;
array_Token main__AssignTokens;

array new_array(int mylen, int cap, int elm_size) {

  array arr = (array){.len = mylen,
                      .cap = cap,
                      .element_size = elm_size,
                      .data = v_malloc(cap * elm_size)};

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

    v_panic(tos2("array.insert: index larger than length"));

    return;
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

    v_panic(tos2("array.first: empty array"));
  };

  return (byte *)a.data + 0;
}
void *array_last(array a) {

  if (a.len == 0) {

    v_panic(tos2("array.last: empty array"));
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
string array_int_str(array_int a) {

  string res = tos2("[");

  for (int i = 0; i < a.len; i++) {

    int val = (*(int *)array__get(a, i));

    res = string_add(res, _STR("%d", val));

    if (i < a.len - 1) {

      res = string_add(res, tos2(", "));
    };
  };

  res = string_add(res, tos2("]"));

  return res;
}
void v_array_free(array a) { free(a.data); }
string array_string_str(array_string a) {

  string res = tos2("[");

  for (int i = 0; i < a.len; i++) {

    string val = (*(string *)array__get(a, i));

    res = string_add(res, _STR("\"%.*s\"", val.len, val.str));

    if (i < a.len - 1) {

      res = string_add(res, tos2(", "));
    };
  };

  res = string_add(res, tos2("]"));

  return res;
}
string array_byte_hex(array_byte b) {

  byte *hex = v_malloc(b.len * 2 + 1);

  byte *ptr = &/*vvar*/ hex[/*ptr*/ 0] /*rbyte 1*/;

  for (int i = 0; i < b.len; i++) {

    ptr += sprintf(ptr, "%02X", (*(byte *)array__get(b, i)));
  };

  return (tos2(hex));
}
void todo() {}
string tos(byte *s, int len) {

  if (isnil(s)) {

    v_panic(tos2("tos(): nil string"));
  };

  return (string){
      .str = s,
      .len = len,
      .hash_cache = 0,
  };
}
string tos_clone(byte *s) {

  if (isnil(s)) {

    v_panic(tos2("tos: nil string"));

    return (string){.hash_cache = 0, .str = 0, .len = 0};
  };

  int len = strlen(s);

  string res = tos(s, len);

  return string_clone(res);
}
string tos2(byte *s) {

  if (isnil(s)) {

    v_panic(tos2("tos2: nil string"));

    return (string){.hash_cache = 0, .str = 0, .len = 0};
  };

  int len = strlen(s);

  string res = tos(s, len);

  return res;
}
string string_clone(string a) {

  string b = (string){
      .len = a.len,
      .str = v_malloc(a.len + 1),
      .hash_cache = 0,
  };

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

  array_int idxs =
      new_array_from_c_array(0, 0, sizeof(int), (int[]){EMPTY_STRUCT_INIT});

  {}

  string rem = s;

  int rstart = 0;

  while (1) {

    int i = string_index(rem, rep);

    if (i < 0) {

      break;
    };

    _PUSH(&idxs, (rstart + i), tmp11, int);

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
}
int string_int(string s) { return atoi(s.str); }
i32 string_i32(string s) { return atol(s.str); }
i64 string_i64(string s) { return atoll(s.str); }
f32 string_f32(string s) { return atof(s.str); }
f64 string_f64(string s) { return atof(s.str); }
u32 string_u32(string s) { return strtoul(s.str, 0, 0); }
u64 string_u64(string s) { return strtoull(s.str, 0, 0); }
bool string_eq(string s, string a) {

  if (isnil(s.str)) {

    v_panic(tos2("string.eq(): nil string"));
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

  string res = (string){
      .len = new_len,
      .str = v_malloc(new_len + 1),
      .hash_cache = 0,
  };

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

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

  if (delim.len == 0) {

    _PUSH(&res, (s), tmp30, string);

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

        _PUSH(&res, (string_trim_space(val)), tmp37, string);
      };

      start = i;
    };

    i++;
  };

  return res;
}
array_string string_split_single(string s, byte delim) {

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

  if (((int)(delim)) == 0) {

    _PUSH(&res, (s), tmp39, string);

    return res;
  };

  int i = 0;

  int start = 0;

  while (i < s.len) {

    bool a = s.str[i] /*rbyte 0*/ == delim;

    bool b = i == s.len - 1;

    if (a || b) {

      if (i == s.len - 1) {

        i++;
      };

      string val = string_substr(s, start, i);

      if (val.len > 0) {

        _PUSH(&res, (string_trim_space(val)), tmp45, string);
      };

      start = i + 1;
    };

    i++;
  };

  return res;
}
array_string string_split_into_lines(string s) {

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

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

      _PUSH(&res, (line), tmp51, string);

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

    return tos2("");
  };

  return string_substr(s, n, s.len);
}
string string_substr(string s, int start, int end) {

  if (start >= s.len) {

    return tos2("");
  };

  int len = end - start;

  string res = (string){
      .len = len,
      .str = v_malloc(len + 1),
      .hash_cache = 0,
  };

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

  int tmp55 = 0;

  array_int prefix = array_repeat(&tmp55, p.len, sizeof(int));

  int j = 0;

  for (int i = 1; i < p.len; i++) {

    while (p.str[j] /*rbyte 0*/ != p.str[i] /*rbyte 0*/ && j > 0) {

      j = (*(int *)array__get(prefix, j - 1));
    };

    if (p.str[j] /*rbyte 0*/ == p.str[i] /*rbyte 0*/) {

      j++;
    };

    int tmp61 = j;

    array_set(&/*q*/ prefix, i, &tmp61);
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

  byte *b = v_malloc(s.len);

  for (int i = 0; i < s.len; i++) {

    b[/*ptr*/ i] /*rbyte 1*/ = tolower(s.str[/*ptr*/ i] /*rbyte 0*/);
  };

  return tos(b, s.len);
}
string string_to_upper(string s) {

  byte *b = v_malloc(s.len);

  for (int i = 0; i < s.len; i++) {

    b[/*ptr*/ i] /*rbyte 1*/ = toupper(s.str[/*ptr*/ i] /*rbyte 0*/);
  };

  return tos(b, s.len);
}
string string_find_between(string s, string start, string end) {

  int start_pos = string_index(s, start);

  if (start_pos == -1) {

    return tos2("");
  };

  string val = string_right(s, start_pos + start.len);

  int end_pos = string_index(val, end);

  if (end_pos == -1) {

    return val;
  };

  return string_left(val, end_pos);
}
bool array_string_contains(array_string ar, string val) {

  array_string tmp81 = ar;
  ;
  for (int tmp82 = 0; tmp82 < tmp81.len; tmp82++) {
    string s = ((string *)tmp81.data)[tmp82];

    if (string_eq(s, val)) {

      return 1;
    };
  };

  return 0;
}
bool array_int_contains(array_int ar, int val) {

  array_int tmp83 = ar;
  ;
  for (int i = 0; i < tmp83.len; i++) {
    int s = ((int *)tmp83.data)[i];

    if (s == val) {

      return 1;
    };
  };

  return 0;
}
bool is_space(byte c) { return isspace(c); }
bool byte_is_space(byte c) { return is_space(c); }
string string_trim_space(string s) {

  if (string_eq(s, tos2(""))) {

    return tos2("");
  };

  int i = 0;

  while (i < s.len && is_space(s.str[i] /*rbyte 0*/)) {

    i++;
  };

  int end = s.len - 1;

  while (end >= 0 && is_space(s.str[end] /*rbyte 0*/)) {

    end--;
  };

  string res = string_substr(s, i, end + 1);

  return res;
}
string string_trim(string s, byte c) {

  if (string_eq(s, tos2(""))) {

    return tos2("");
  };

  int i = 0;

  while (i < s.len && c == s.str[i] /*rbyte 0*/) {

    i++;
  };

  string res = string_right(s, i);

  int end = res.len - 1;

  while (end >= 0 && c == res.str[end] /*rbyte 1*/) {

    end--;
  };

  res = string_left(res, end + 1);

  return res;
}
string string_trim_left(string s, string cutset) {

  int start = string_index(s, cutset);

  if (start != 0) {

    return s;
  };

  while (start < s.len - 1 &&
         s.str[start] /*rbyte 0*/ == cutset.str[0] /*rbyte 0*/) {

    start++;
  };

  return string_right(s, start);
}
string string_trim_right(string s, string cutset) {

  int pos = string_last_index(s, cutset);

  if (pos == -1) {

    return s;
  };

  return string_left(s, pos);
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

  return compare_strings(&/*11 EXP:"string*" GOT:"string" */ aa,
                         &/*11 EXP:"string*" GOT:"string" */ bb);
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

    _PUSH(&res.runes, (i), tmp97, int);

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

    int tmp102 = i;

    array_set(&/*q*/ res.runes, j, &tmp102);

    j++;

    i += char_len - 1;

    res.len++;
  };

  return res;
}
string ustring_substr(ustring u, int start, int end) {

  start = (*(int *)array__get(u.runes, start));

  if (end >= u.runes.len) {

    end = u.s.len;

  } else {

    end = (*(int *)array__get(u.runes, end));
  };

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
int abs(int a) {

  if (a >= 0) {

    return a;
  };

  return -a;
}
bool byte_is_digit(byte c) { return c >= '0' && c <= '9'; }
bool byte_is_hex_digit(byte c) {

  return byte_is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
bool byte_is_oct_digit(byte c) { return c >= '0' && c <= '7'; }
bool byte_is_letter(byte c) {

  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
void v_string_free(string s) { free(s.str); }
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

    return tos2("");
  };

  int len = 0;

  array_string tmp111 = a;
  ;
  for (int i = 0; i < tmp111.len; i++) {
    string val = ((string *)tmp111.data)[i];

    len += val.len + del.len;
  };

  len -= del.len;

  string res = tos2("");

  res.len = len;

  res.str = v_malloc(res.len + 1);

  int idx = 0;

  array_string tmp114 = a;
  ;
  for (int i = 0; i < tmp114.len; i++) {
    string val = ((string *)tmp114.data)[i];

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

  return array_string_join(s, tos2("\n"));
}
string string_reverse(string s) {

  string res = (string){
      .len = s.len,
      .str = v_malloc(s.len),
      .hash_cache = 0,
  };

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

  int h = s.hash_cache;

  if (h == 0 && s.len > 0) {

    string tmp123 = s;
    ;
    for (int tmp124 = 0; tmp124 < tmp123.len; tmp124++) {
      byte c = ((byte *)tmp123.str)[tmp124];

      h = h * 31 + ((int)(c));
    };
  };

  return h;
}
array_byte string_bytes(string s) {

  if (s.len == 0) {

    return new_array_from_c_array(0, 0, sizeof(byte),
                                  (byte[]){EMPTY_STRUCT_INIT});
  };

  byte tmp125 = ((byte)(0));

  array_byte buf = array_repeat(&tmp125, s.len, sizeof(byte));

  memcpy(buf.data, s.str, s.len);

  return buf;
}
void v_exit(int code) { exit(code); }
bool isnil(void *v) { return v == 0; }
void on_panic(int (*f)(int /*FFF*/)) {}
void print_backtrace() {

  return;

#ifdef __APPLE__

  voidptr buffer[100] = STRUCT_DEFAULT_VALUE;

  void *nr_ptrs = backtrace(buffer, 100);

  backtrace_symbols_fd(buffer, nr_ptrs, 1);

#endif
  ;
}
void v_panic(string s) {

  printf("V panic: %.*s\n", s.len, s.str);

  print_backtrace();

  exit(1);
}
void println(string s) {

  if (isnil(s.str)) {

    v_panic(tos2("println(NIL)"));
  };

#ifdef _WIN32

  _putws(string_to_wide(s));

  ;

#else

  printf("%.*s\n", s.len, s.str);

#endif
  ;
}
void eprintln(string s) {

  if (isnil(s.str)) {

    v_panic(tos2("eprintln(NIL)"));
  };

#ifdef __APPLE__

  fprintf(stderr, "%.*s\n", s.len, s.str);

  ;

#else

  println(s);

#endif
  ;
}
void v_print(string s) {

#ifdef _WIN32

  wprintf(string_to_wide(s));

  ;

#else

  printf("%.*s", s.len, s.str);

#endif
  ;
}
byte *v_malloc(int n) {

  if (n < 0) {

    v_panic(tos2("malloc(<0)"));
  };

  byte *ptr = malloc(n);

  if (isnil(ptr)) {

    v_panic(_STR("malloc(%d) failed", n));
  };

  return ptr;
}
byte *v_calloc(int n) {

  if (n < 0) {

    v_panic(tos2("calloc(<0)"));
  };

  return calloc(n, 1);
}
void v_free(void *ptr) { free(ptr); }
void *memdup(void *src, int sz) {

  byte *mem = v_malloc(sz);

  return memcpy(mem, src, sz);
}
string double_str(double d) {

  byte *buf = v_malloc(sizeof(double) * 5 + 1);

  sprintf(buf, "%f", d);

  return tos(buf, strlen(buf));
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
string int_str(int nn) {

  int n = nn;

  if (n == 0) {

    return tos2("0");
  };

  int max = 16;

  byte *buf = v_malloc(max);

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
string u8_str(u8 nn) {

  u8 n = nn;

  if (n == ((u8)(0))) {

    return tos2("0");
  };

  int max = 5;

  byte *buf = v_malloc(max);

  int len = 0;

  bool is_neg = 0;

  if (n < ((u8)(0))) {

    n = -n;

    is_neg = 1;
  };

  while (n > ((u8)(0))) {

    u8 d = n % ((u8)(10));

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = d + ((u8)('0'));

    len++;

    n = n / ((u8)(10));
  };

  if (is_neg) {

    buf[/*ptr*/ max - len - 1] /*rbyte 1*/ = '-';

    len++;
  };

  return tos(buf + max - len, len);
}
string i64_str(i64 nn) {

  i64 n = nn;

  if (n == ((i64)(0))) {

    return tos2("0");
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
string bool_str(bool b) {

  if (b) {

    return tos2("true");
  };

  return tos2("false");
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

  array_byte tmp29 = a;
  ;
  for (int tmp30 = 0; tmp30 < tmp29.len; tmp30++) {
    byte aa = ((byte *)tmp29.data)[tmp30];

    if (aa == val) {

      return 1;
    };
  };

  return 0;
}
string rune_str(rune c) {

  int fst_byte = ((int)(c)) >> 8 * 3 & 0xff;

  int len = utf8_char_len(fst_byte);

  string str = (string){
      .len = len,
      .str = v_malloc(len + 1),
      .hash_cache = 0,
  };

  for (int i = 0; i < len; i++) {

    str.str[/*ptr*/ i] /*rbyte 1*/ = ((int)(c)) >> 8 * (3 - i) & 0xff;
  };

  str.str[len] /*rbyte 1*/ = '\0';

  return str;
}
string byte_str(byte c) {

  string str = (string){
      .len = 1,
      .str = v_malloc(2),
      .hash_cache = 0,
  };

  str.str[/*ptr*/ 0] /*rbyte 1*/ = c;

  str.str[/*ptr*/ 1] /*rbyte 1*/ = '\0';

  return str;
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

  return tos2("");
}
string utf32_to_str_no_malloc(u32 code, void *buf) {

  int icode = ((int)(code));

  byteptr buffer = ((byteptr)(buf));

  if (icode <= 127) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = icode;

    return tos(&/*11 EXP:"byte*" GOT:"byteptr" */ buffer, 1);
  };

  if ((icode <= 2047)) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = 192 | (icode >> 6);

    buffer[/*ptr*/ 1] /*rbyteptr 1*/ = 128 | (icode & 63);

    return tos(&/*11 EXP:"byte*" GOT:"byteptr" */ buffer, 2);
  };

  if ((icode <= 65535)) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = 224 | (icode >> 12);

    buffer[/*ptr*/ 1] /*rbyteptr 1*/ = 128 | ((icode >> 6) & 63);

    buffer[/*ptr*/ 2] /*rbyteptr 1*/ = 128 | (icode & 63);

    return tos(&/*11 EXP:"byte*" GOT:"byteptr" */ buffer, 3);
  };

  if ((icode <= 1114111)) {

    buffer[/*ptr*/ 0] /*rbyteptr 1*/ = 240 | (icode >> 18);

    buffer[/*ptr*/ 1] /*rbyteptr 1*/ = 128 | ((icode >> 12) & 63);

    buffer[/*ptr*/ 2] /*rbyteptr 1*/ = 128 | ((icode >> 6) & 63);

    buffer[/*ptr*/ 3] /*rbyteptr 1*/ = 128 | (icode & 63);

    return tos(&/*11 EXP:"byte*" GOT:"byteptr" */ buffer, 4);
  };

  return tos2("");
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

  ;

#else

  return 0;

#endif
  ;
}
string string_from_wide(u16 *_wstr) {

#ifdef _WIN32

  int wstr_len = ((int)(wcslen(_wstr)));

  return string_from_wide2(_wstr, wstr_len);

  ;

#else

  return tos2("");

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

  ;

#else

  return tos2("");

#endif
  ;
}
map new_map(int cap, int elm_size) {

  map res = (map){.element_size = elm_size,
                  .root = 0,
                  ._keys = new_array(0, 1, sizeof(string)),
                  .key_i = 0,
                  .size = 0};

  return res;
}
Node *new_node(string key, void *val, int element_size) {

  Node *new_e = ALLOC_INIT(
      Node, {.key = key, .val = v_malloc(element_size), .left = 0, .right = 0});

  memcpy(new_e->val, val, element_size);

  return new_e;
}
void map_insert(map *m, Node *n, string key, void *val) {

  if (string_eq(n->key, key)) {

    memcpy(n->val, val, m->element_size);

    return;
  };

  if (string_gt(n->key, key)) {

    if (isnil(n->left)) {

      n->left = new_node(key, val, m->element_size);

      m->size++;

    } else {

      map_insert(m, n->left, key, val);
    };

    return;
  };

  if (isnil(n->right)) {

    n->right = new_node(key, val, m->element_size);

    m->size++;

  } else {

    map_insert(m, n->right, key, val);
  };
}
bool Node_find(Node *n, string key, void *out, int element_size) {

  if (string_eq(n->key, key)) {

    memcpy(out, n->val, element_size);

    return 1;

  } else if (string_gt(n->key, key)) {

    if (isnil(n->left)) {

      return 0;

    } else {

      return Node_find(&/* ? */ *n->left, key, out, element_size);
    };

  } else {

    if (isnil(n->right)) {

      return 0;

    } else {

      return Node_find(&/* ? */ *n->right, key, out, element_size);
    };
  };

  return 0;
}
bool Node_find2(Node *n, string key, int element_size) {

  if (string_eq(n->key, key)) {

    return 1;

  } else if (string_gt(n->key, key)) {

    if (isnil(n->left)) {

      return 0;

    } else {

      return Node_find2(&/* ? */ *n->left, key, element_size);
    };

  } else {

    if (isnil(n->right)) {

      return 0;

    } else {

      return Node_find2(&/* ? */ *n->right, key, element_size);
    };
  };

  return 0;
}
void map__set(map *m, string key, void *val) {

  if (isnil(m->root)) {

    m->root = new_node(key, val, m->element_size);

    m->size++;

    return;
  };

  map_insert(m, m->root, key, val);
}
void map_preorder_keys(map *m, Node *node) {

  string tmp3 = node->key;

  array_set(&/*q*/ m->_keys, m->key_i, &tmp3);

  m->key_i++;

  if (!isnil(node->left)) {

    map_preorder_keys(m, node->left);
  };

  if (!isnil(node->right)) {

    map_preorder_keys(m, node->right);
  };
}
array_string map_keys(map *m) {

  string tmp4 = tos2("");

  m->_keys = array_repeat(&tmp4, m->size, sizeof(string));

  m->key_i = 0;

  if (isnil(m->root)) {

    return m->_keys;
  };

  map_preorder_keys(m, m->root);

  return m->_keys;
}
bool map_get(map m, string key, void *out) {

  if (isnil(m.root)) {

    return 0;
  };

  return Node_find(&/* ? */ *m.root, key, out, m.element_size);
}
bool map_exists(map m, string key) {

  v_panic(tos2("map.exists(key) was removed from the language. Use `key in "
               "map` instead."));

  return 0;
}
bool map__exists(map m, string key) {

  return !isnil(m.root) && Node_find2(&/* ? */ *m.root, key, m.element_size);
}
void v_map_print(map m) {

  println(tos2("<<<<<<<<"));

  println(tos2(">>>>>>>>>>"));
}
void v_map_free(map m) {}
string map_string_str(map_string m) {

  if (m.size == 0) {

    return tos2("{}");
  };

  string s = tos2("{\n");

  s = string_add(s, tos2("}"));

  return s;
}
Option opt_ok(void *data, int size) {

  if (size > 255) {

    v_panic(_STR("option size too big: %d (max is 255)", size));
  };

  Option res = (Option){
      .ok = 1,
      .error = tos("", 0),
  };

  memcpy(res.data, data, size);

  return res;
}
Option v_error(string s) { return (Option){.error = s, .ok = 0}; }
void os__todo_remove() {}
array_string os__init_os_args(int argc, byteptr *argv) {

  array_string args = new_array_from_c_array(0, 0, sizeof(string),
                                             (string[]){EMPTY_STRUCT_INIT});

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

  ;

#else

  for (int i = 0; i < argc; i++) {

    _PUSH(&args, ((tos2(argv[/*ptr*/ i] /*rbyteptr 0*/))), tmp7, string);
  };

#endif
  ;

  return args;
}
array_string os__parse_windows_cmd_line(byte *cmd) {

  string s = (tos2(cmd));

  return string_split(s, tos2(" "));
}
Option_string os__read_file(string path) {

  string mode = tos2("rb");

  struct /*c struct init*/

      FILE *fp = ALLOC_INIT(FILE, {EMPTY_STRUCT_INIT});

#ifdef _WIN32

  fp = _wfopen(string_to_wide(path), string_to_wide(mode));

  ;

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

  string tmp14 = OPTION_CAST(string)((tos(str, fsize)));
  return opt_ok(&tmp14, sizeof(string));
}
int os__file_size(string path) {

  struct /*c struct init*/

      stat s = (struct stat){.st_size = 0, .st_mode = 0, .st_mtime = 0};

#ifdef _WIN32

  _wstat(string_to_wide(path), &/*vvar*/ s);

  ;

#else

  stat(path.str, &/*vvar*/ s);

#endif
  ;

  return s.st_size;
}
void os__mv(string old, string new) {

#ifdef _WIN32

  _wrename(string_to_wide(old), string_to_wide(new));

  ;

#else

  rename(old.str, new.str);

#endif
  ;
}
array_string os__read_lines(string path) {

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

  byte buf[1000] = STRUCT_DEFAULT_VALUE;

  string mode = tos2("rb");

  struct /*c struct init*/

      FILE *fp = ALLOC_INIT(FILE, {EMPTY_STRUCT_INIT});

#ifdef _WIN32

  fp = _wfopen(string_to_wide(path), string_to_wide(mode));

  ;

#else

  byte *cpath = path.str;

  fp = fopen(cpath, mode.str);

#endif
  ;

  if (isnil(fp)) {

    return res;
  };

  while (fgets(buf, 1000, fp) != 0) {

    string val = tos2("");

    buf[strlen(buf) - 1] /*rbyte 1*/ = '\0';

#ifdef _WIN32

    if (buf[strlen(buf) - 2] /*rbyte 1*/ == 13) {

      buf[strlen(buf) - 2] /*rbyte 1*/ = '\0';
    };

#endif
    ;

    _PUSH(&res, (tos_clone(buf)), tmp22, string);
  };

  fclose(fp);

  return res;
}
array_ustring os__read_ulines(string path) {

  array_string lines = os__read_lines(path);

  array_ustring ulines = new_array_from_c_array(0, 0, sizeof(ustring),
                                                (ustring[]){EMPTY_STRUCT_INIT});

  array_string tmp25 = lines;
  ;
  for (int tmp26 = 0; tmp26 < tmp25.len; tmp26++) {
    string myline = ((string *)tmp25.data)[tmp26];

    _PUSH(&ulines, (string_ustring(myline)), tmp27, ustring);
  };

  return ulines;
}
Option_os__File os__open(string path) {

  os__File file = (struct os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(path);

  string mode = tos2("rb");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

  ;

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(cpath, "rb")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(_STR("failed to open file \"%.*s\"", path.len, path.str));
  };

  os__File tmp32 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp32, sizeof(os__File));
}
Option_os__File os__create(string path) {

  os__File file = (os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(string_replace(path, tos2("/"), tos2("\\")));

  string mode = tos2("wb");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

  ;

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(cpath, "wb")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(_STR("failed to create file \"%.*s\"", path.len, path.str));
  };

  os__File tmp37 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp37, sizeof(os__File));
}
Option_os__File os__open_append(string path) {

  os__File file = (os__File){.cfile = 0};

#ifdef _WIN32

  u16 *wpath = string_to_wide(string_replace(path, tos2("/"), tos2("\\")));

  string mode = tos2("ab");

  file = (os__File){.cfile = _wfopen(wpath, string_to_wide(mode))};

  ;

#else

  byte *cpath = path.str;

  file = (os__File){.cfile = fopen(cpath, "ab")};

#endif
  ;

  if (isnil(file.cfile)) {

    return v_error(
        _STR("failed to create(append) file \"%.*s\"", path.len, path.str));
  };

  os__File tmp42 = OPTION_CAST(os__File)(file);
  return opt_ok(&tmp42, sizeof(os__File));
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
int os__system(string cmd) {

  int ret = ((int)(0));

#ifdef _WIN32

  ret = _wsystem(string_to_wide(cmd));

  ;

#else

  ret = system(cmd.str);

#endif
  ;

  if (ret == -1) {

    os__print_c_errno();
  };

  return ret;
}
FILE *os__popen(string path) {

#ifdef _WIN32

  string mode = tos2("rb");

  u16 *wpath = string_to_wide(path);

  return _wpopen(wpath, string_to_wide(mode));

  ;

#else

  byte *cpath = path.str;

  return popen(cpath, "r");

#endif
  ;
}
string os__exec(string cmd) {

  cmd = _STR("%.*s 2>&1", cmd.len, cmd.str);

  FILE *f = os__popen(cmd);

  if (isnil(f)) {

    printf("popen %.*s failed\n", cmd.len, cmd.str);

    return tos2("");
  };

  byte buf[1000] = STRUCT_DEFAULT_VALUE;

  string res = tos2("");

  while (fgets(buf, 1000, f) != 0) {

    res = string_add(res, tos(buf, strlen(buf)));
  };

  return string_trim_space(res);
}
string os__getenv(string key) {

#ifdef _WIN32

  void *s = _wgetenv(string_to_wide(key));

  if (isnil(s)) {

    return tos2("");
  };

  return string_from_wide(s);

  ;

#else

  byte *s = getenv(key.str);

  if (isnil(s)) {

    return tos2("");
  };

  return (tos2(s));

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

  ;

#else

  return setenv(name.str, value.str, overwrite);

#endif
  ;
}
int os__unsetenv(string name) {

#ifdef _WIN32

  string format = _STR("%.*s=", name.len, name.str);

  return _putenv(format.str);

  ;

#else

  return unsetenv(name.str);

#endif
  ;
}
bool os__file_exists(string path) {

#ifdef _WIN32

  path = string_replace(path, tos2("/"), tos2("\\"));

  return _waccess(string_to_wide(path), 0) != -1;

  ;

#else

  return access(path.str, 0) != -1;

#endif
  ;
}
bool os__dir_exists(string path) {

#ifdef _WIN32

  path = string_replace(path, tos2("/"), tos2("\\"));

  int attr = ((int)(GetFileAttributes(string_to_wide(path))));

  if (attr == INVALID_FILE_ATTRIBUTES) {

    return 0;
  };

  if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0) {

    return 1;
  };

  return 0;

  ;

#else

  void *dir = opendir(path.str);

  bool res = !isnil(dir);

  if (res) {

    closedir(dir);
  };

  return res;

#endif
  ;
}
void os__mkdir(string path) {

#ifdef _WIN32

  path = string_replace(path, tos2("/"), tos2("\\"));

  if (string_last_index(path, tos2("\\")) != -1) {

    os__mkdir(string_all_before_last(path, tos2("\\")));
  };

  CreateDirectory(string_to_wide(path), 0);

  ;

#else

  mkdir(path.str, 511);

#endif
  ;
}
void os__rm(string path) {

#ifdef _WIN32

  _wremove(string_to_wide(path));

  ;

#else

  remove(path.str);

#endif
  ;
}
void os__rmdir(string path) {

#ifndef _WIN32

  rmdir(path.str);

  ;

#else

  RemoveDirectory(string_to_wide(path));

#endif
  ;
}
void os__print_c_errno() {}
string os__ext(string path) {

  int pos = string_last_index(path, tos2("."));

  if (pos == -1) {

    return tos2("");
  };

  return string_right(path, pos);
}
string os__dir(string path) {

  int pos = -1;

#ifdef _WIN32

  pos = string_last_index(path, tos2("\\"));

  ;

#else

  pos = string_last_index(path, os__PathSeparator);

#endif
  ;

  if (pos == -1) {

    return tos2(".");
  };

  return string_left(path, pos);
}
string os__path_sans_ext(string path) {

  int pos = string_last_index(path, tos2("."));

  if (pos == -1) {

    return path;
  };

  return string_left(path, pos);
}
string os__basedir(string path) {

  int pos = string_last_index(path, tos2("/"));

  if (pos == -1) {

    return path;
  };

  return string_left(path, pos + 1);
}
string os__filename(string path) { return string_all_after(path, tos2("/")); }
string os__get_line() {

  string str = os__get_raw_line();

  if (string_at(str, str.len - 1) == '\n') {

    return string_substr(str, 0, str.len - 1);
  };

  return str;
}
string os__get_raw_line() {

#ifdef _WIN32

  int max = 512;

  u16 *buf = ((u16 *)(v_malloc(max * 2)));

  void *h_input = GetStdHandle(os__STD_INPUT_HANDLE);

  if (h_input == os__INVALID_HANDLE_VALUE) {

    v_panic(tos2("get_raw_line() error getting input handle."));
  };

  int nr_chars = 0;

  ReadConsole(h_input, buf, max, &/*vvar*/ nr_chars, 0);

  if (nr_chars == 0) {

    return tos2("");
  };

  return string_from_wide2(buf, nr_chars);

  ;

#else

  u64 max = ((u64)(256));

  byte *buf = v_malloc(((int)(max)));

  int nr_chars = getline(&/*vvar*/ buf, &/*vvar*/ max, stdin);

  if (nr_chars == 0) {

    return tos2("");
  };

  return (tos(buf, nr_chars));

#endif
  ;
}
array_string os__get_lines() {

  string line = tos2("");

  array_string inputstr = new_array_from_c_array(0, 0, sizeof(string),
                                                 (string[]){EMPTY_STRUCT_INIT});

  while (1) {

    line = os__get_line();

    if ((line.len <= 0)) {

      break;
    };

    line = string_trim_space(line);

    _PUSH(&inputstr, (line), tmp73, string);
  };

  return inputstr;
}
string os__get_lines_joined() {

  string line = tos2("");

  string inputstr = tos2("");

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

  return tos2("linux");

#endif
  ;

#ifdef __APPLE__

  return tos2("mac");

#endif
  ;

#ifdef _WIN32

  return tos2("windows");

#endif
  ;

#ifdef __FreeBSD__

  return tos2("freebsd");

#endif
  ;

#ifdef __OpenBSD__

  return tos2("openbsd");

#endif
  ;

#ifdef __NetBSD__

  return tos2("netbsd");

#endif
  ;

#ifdef __DragonFly__

  return tos2("dragonfly");

#endif
  ;

#ifdef _MSC_VER

  return tos2("windows");

#endif
  ;

  return tos2("unknown");
}
string os__home_dir() {

  string home = os__getenv(tos2("HOME"));

#ifdef _WIN32

  home = os__getenv(tos2("HOMEDRIVE"));

  if (home.len == 0) {

    home = os__getenv(tos2("SYSTEMDRIVE"));
  };

  string homepath = os__getenv(tos2("HOMEPATH"));

  if (homepath.len == 0) {

    homepath = string_add(tos2("\\Users\\"), os__getenv(tos2("USERNAME")));
  };

  home = string_add(home, homepath);

#endif
  ;

  home = string_add(home, tos2("/"));

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

      sigaction sa =
          (struct sigaction){.sa_mask = 0, .sa_sigaction = 0, .sa_flags = 0};

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

    v_panic(tos2("error reading /proc/self/exe to get exe path"));
  };

  return (tos(result, count));

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

    println(tos2("os.executable() failed"));

    return tos2(".");
  };

  return (tos2(result));

#endif
  ;

#ifdef __FreeBSD__

  byte *result = v_malloc(os__MAX_PATH);

  int mib[4] = (int[]){1, 14, 12, -1};

  int size = os__MAX_PATH;

  sysctl(mib, 4, result, &/*vvar*/ size, 0, 0);

  return (tos2(result));

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

    v_panic(tos2("error reading /proc/curproc/exe to get exe path"));
  };

  return (tos(result, count));

#endif
  ;

#ifdef __DragonFly__

  byte *result = v_malloc(os__MAX_PATH);

  int count = ((int)(readlink("/proc/curproc/file", result, os__MAX_PATH)));

  if (count < 0) {

    v_panic(tos2("error reading /proc/curproc/file to get exe path"));
  };

  return (tos(result, count));

#endif
  ;

  return tos2(".");
}
bool os__is_dir(string path) {

#ifdef _WIN32

  return os__dir_exists(path);

  ;

#else

  struct /*c struct init*/

      stat statbuf = (struct stat){.st_size = 0, .st_mode = 0, .st_mtime = 0};

  byte *cstr = path.str;

  if (stat(cstr, &/*vvar*/ statbuf) != 0) {

    return 0;
  };

  return statbuf.st_mode & S_IFMT == S_IFDIR;

#endif
  ;
}
void os__chdir(string path) {

#ifdef _WIN32

  _wchdir(string_to_wide(path));

  ;

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

    return tos2("");
  };

  return string_from_wide(buf);

  ;

#else

  byte *buf = v_malloc(512);

  if (getcwd(buf, 512) == 0) {

    return tos2("");
  };

  return (tos2(buf));

#endif
  ;
}
array_string os__ls(string path) {

#ifdef _WIN32

  os__win32finddata find_file_data = (os__win32finddata){.dwFileAttributes = 0,
                                                         .nFileSizeHigh = 0,
                                                         .nFileSizeLow = 0,
                                                         .dwReserved0 = 0,
                                                         .dwReserved1 = 0,
                                                         .dwFileType = 0,
                                                         .dwCreatorType = 0,
                                                         .wFinderFlags = 0};

  array_string dir_files = new_array_from_c_array(
      0, 0, sizeof(string), (string[]){EMPTY_STRUCT_INIT});

  if (!os__dir_exists(path)) {

    printf("ls() couldnt open dir \"%.*s\" (does not exist).\n", path.len,
           path.str);

    return dir_files;
  };

  string path_files = _STR("%.*s\\*", path.len, path.str);

  void *h_find_files =
      FindFirstFile(string_to_wide(path_files), &/*vvar*/ find_file_data);

  string first_filename = string_from_wide(((u16 *)(find_file_data.cFileName)));

  if (string_ne(first_filename, tos2(".")) &&
      string_ne(first_filename, tos2(".."))) {

    _PUSH(&dir_files, (first_filename), tmp107, string);
  };

  while (FindNextFile(h_find_files, &/*vvar*/ find_file_data)) {

    string filename = string_from_wide(((u16 *)(find_file_data.cFileName)));

    if (string_ne(filename, tos2(".")) && string_ne(filename, tos2(".."))) {

      _PUSH(&dir_files, (string_clone(filename)), tmp109, string);
    };
  };

  FindClose(h_find_files);

  return dir_files;

  ;

#else

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

  void *dir = opendir(path.str);

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

    string name = tos_clone(ent->d_name);

    if (string_ne(name, tos2(".")) && string_ne(name, tos2("..")) &&
        string_ne(name, tos2(""))) {

      _PUSH(&res, (name), tmp114, string);
    };
  };

  closedir(dir);

  return res;

#endif
  ;
}
void os__signal(int signum, void *handler) { signal(signum, handler); }
int os__fork() {

#ifndef _WIN32

  void *pid = fork();

  return pid;

#endif
  ;
}
int os__wait() {

#ifndef _WIN32

  void *pid = wait(0);

  return pid;

#endif
  ;
}
int os__file_last_mod_unix(string path) {

  struct /*c struct init*/

      stat attr = (struct stat){.st_size = 0, .st_mode = 0, .st_mtime = 0};

  stat(path.str, &/*vvar*/ attr);

  return attr.st_mtime;
}
void os__log(string s) {}
void os__flush_stdout() { fflush(stdout); }
void os__print_backtrace() {}
string os__get_error_msg(int code) {

  void *_ptr_text = strerror(code);

  if (_ptr_text == 0) {

    return tos2("");
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
array_int math__digits(int n, int base) {

  int sign = 1;

  if (n < 0) {

    sign = -1;

    n = -n;
  };

  array_int res =
      new_array_from_c_array(0, 0, sizeof(int), (int[]){EMPTY_STRUCT_INIT});

  while (n != 0) {

    _PUSH(&res, ((n % base) * sign), tmp3, int);

    n /= base;
  };

  return res;
}
f64 math__erf(f64 a) { return erf(a); }
f64 math__erfc(f64 a) { return erfc(a); }
f64 math__exp2(f64 a) { return exp2(a); }
int math__recursive_product(int n, int *current_number_ptr) {

  int m = n / 2;

  if ((m == 0)) {

    return *current_number_ptr += 2;
  };

  if ((n == 2)) {

    return (*current_number_ptr += 2) * (*current_number_ptr += 2);
  };

  return math__recursive_product(
             (n - m), &/*11 EXP:"int*" GOT:"int" */ *current_number_ptr) *
         math__recursive_product(
             m, &/*11 EXP:"int*" GOT:"int" */ *current_number_ptr);
}
i64 math__factorial(int n) {

  if (n < 0) {

    v_panic(tos2("factorial: Cannot find factorial of negative number"));
  };

  if (n < 2) {

    return ((i64)(1));
  };

  int r = 1;

  int p = 1;

  int current_number = 1;

  int h = 0;

  int shift = 0;

  int high = 1;

  int len = high;

  int log2n = ((int)(math__floor(math__log2(n))));

  for (; h != n;) {

    shift += h;

    h = n >> log2n;

    log2n -= 1;

    len = high;

    high = (h - 1) | 1;

    len = (high - len) / 2;

    if ((len > 0)) {

      p *= math__recursive_product(len, &/*vvar*/ current_number);

      r *= p;
    };
  };

  return ((i64)((r << shift)));
}
f64 math__floor(f64 a) { return floor(a); }
f64 math__fmod(f64 a, f64 b) { return fmod(a, b); }
f64 math__gamma(f64 a) { return tgamma(a); }
i64 math__gcd(i64 a, i64 b) {

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

  return tos(b.buf.data, b.len);
}
void strings__Builder_cut(strings__Builder b, int n) { b.len -= n; }
void strings__Builder_free(strings__Builder *b) { v_free(b->buf.data); }
string strings__repeat(byte c, int n) {

  if (n <= 0) {

    return tos2("");
  };

  byte *arr = v_malloc(n + 1);

  for (int i = 0; i < n; i++) {

    arr[/*ptr*/ i] /*rbyte 1*/ = c;
  };

  arr[/*ptr*/ n] /*rbyte 1*/ = '\0';

  return (tos(arr, n));
}
void rand__seed(int s) { srand(s); }
int rand__next(int max) { return rand() % max; }
void time__remove_me_when_c_bug_is_fixed() {}
time__Time time__now() {

  void *t = time(0);

  struct /*c struct init*/

      tm *now = 0;

  now = localtime(&/*vvar*/ t);

  return time__convert_ctime(*now);
}
time__Time time__random() {

  return (struct time__Time){.year = rand__next(2) + 201,
                             .month = rand__next(12) + 1,
                             .day = rand__next(30) + 1,
                             .hour = rand__next(24),
                             .minute = rand__next(60),
                             .second = rand__next(60),
                             .uni = 0};
}
time__Time time__unix(int u) {

  struct /*c struct init*/

      tm *t = 0;

  t = localtime(&/*vvar*/ u);

  return time__convert_ctime(*t);
}
time__Time time__convert_ctime(struct /*TM*/ tm t) {

  return (struct time__Time){.year = t.tm_year + 1900,
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

  string am = tos2("am");

  int hour = t.hour;

  if (t.hour > 11) {

    am = tos2("pm");
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

  int pos = string_index(s, tos2(" "));

  if (pos <= 0) {

    println(tos2("bad time format"));

    return time__now();
  };

  string symd = string_left(s, pos);

  array_string ymd = string_split(symd, tos2("-"));

  if (ymd.len != 3) {

    println(tos2("bad time format"));

    return time__now();
  };

  string shms = string_right(s, pos);

  array_string hms = string_split(shms, tos2(":"));

  string hour = (*(string *)array__get(hms, 0));

  string minute = (*(string *)array__get(hms, 1));

  string second = (*(string *)array__get(hms, 2));

  return time__new_time(
      (time__Time){.year = string_int((*(string *)array__get(ymd, 0))),
                   .month = string_int((*(string *)array__get(ymd, 1))),
                   .day = string_int((*(string *)array__get(ymd, 2))),
                   .hour = string_int(hour),
                   .minute = string_int(minute),
                   .second = string_int(second),
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
  }

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

    return tos2("now");
  };

  if (secs < 60) {

    return tos2("1m");
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

    return tos2("");
  };

  return time__Time_md(t);
}
int time__day_of_week(int y, int m, int d) { return 0; }
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

  ;

#else

  struct /*c struct init*/

      timeval ts = (struct timeval){.tv_sec = 0, .tv_usec = 0};

  gettimeofday(&/*vvar*/ ts, 0);

  return ts.tv_sec * 1000 + (ts.tv_usec / 1000);

#endif
  ;
}
void time__sleep(int seconds) {

#ifdef _WIN32

  _sleep(seconds * 1000);

  ;

#else

  sleep(seconds);

#endif
  ;
}
void time__usleep(int n) {

#ifdef _WIN32

  ;

#else

  usleep(n);

#endif
  ;
}
void time__sleep_ms(int n) {

#ifdef _WIN32

  Sleep(n);

  ;

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

  int tmp39 = OPTION_CAST(int)(res);
  return opt_ok(&tmp39, sizeof(int));
}
CGen *new_cgen(string out_name_c) {

  string path = _STR(".%.*s", out_name_c.len, out_name_c.str);

  Option_os__File tmp2 = os__create(path);
  if (!tmp2.ok) {
    string err = tmp2.error;

    printf("failed to create %.*s\n", path.len, path.str);

    return ALLOC_INIT(CGen, {.out_path = tos("", 0),
                             .typedefs = new_array(0, 1, sizeof(string)),
                             .type_aliases = new_array(0, 1, sizeof(string)),
                             .includes = new_array(0, 1, sizeof(string)),
                             .types = new_array(0, 1, sizeof(string)),
                             .thread_args = new_array(0, 1, sizeof(string)),
                             .thread_fns = new_array(0, 1, sizeof(string)),
                             .consts = new_array(0, 1, sizeof(string)),
                             .fns = new_array(0, 1, sizeof(string)),
                             .so_fns = new_array(0, 1, sizeof(string)),
                             .consts_init = new_array(0, 1, sizeof(string)),
                             .lines = new_array(0, 1, sizeof(string)),
                             .is_user = 0,
                             .nogen = 0,
                             .tmp_line = tos("", 0),
                             .cur_line = tos("", 0),
                             .prev_line = tos("", 0),
                             .is_tmp = 0,
                             .fn_main = tos("", 0),
                             .stash = tos("", 0)});
  }
  os__File out = *(os__File *)tmp2.data;
  ;

  CGen *gen = ALLOC_INIT(CGen, {.out_path = path,
                                .out = out,
                                .lines = _make(0, 1000, sizeof(string)),
                                .typedefs = new_array(0, 1, sizeof(string)),
                                .type_aliases = new_array(0, 1, sizeof(string)),
                                .includes = new_array(0, 1, sizeof(string)),
                                .types = new_array(0, 1, sizeof(string)),
                                .thread_args = new_array(0, 1, sizeof(string)),
                                .thread_fns = new_array(0, 1, sizeof(string)),
                                .consts = new_array(0, 1, sizeof(string)),
                                .fns = new_array(0, 1, sizeof(string)),
                                .so_fns = new_array(0, 1, sizeof(string)),
                                .consts_init = new_array(0, 1, sizeof(string)),
                                .is_user = 0,
                                .nogen = 0,
                                .tmp_line = tos("", 0),
                                .cur_line = tos("", 0),
                                .prev_line = tos("", 0),
                                .is_tmp = 0,
                                .fn_main = tos("", 0),
                                .stash = tos("", 0)});

  return gen;
}
void CGen_genln(CGen *g, string s) {

  if (g->nogen || g->run != main__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    g->tmp_line =
        _STR("%.*s %.*s\n", g->tmp_line.len, g->tmp_line.str, s.len, s.str);

    return;
  };

  g->cur_line =
      _STR("%.*s %.*s", g->cur_line.len, g->cur_line.str, s.len, s.str);

  if (string_ne(g->cur_line, tos2(""))) {

    _PUSH(&g->lines, (g->cur_line), tmp4, string);

    g->prev_line = g->cur_line;

    g->cur_line = tos2("");
  };
}
void CGen_gen(CGen *g, string s) {

  if (g->nogen || g->run != main__Pass_main) {

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

  if (g->nogen || g->run != main__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    g->tmp_line = s;

  } else {

    g->cur_line = s;
  };
}
void CGen_save(CGen *g) {

  string s = array_string_join(g->lines, tos2("\n"));

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

  g->tmp_line = tos2("");

  g->is_tmp = 1;
}
string CGen_end_tmp(CGen *g) {

  g->is_tmp = 0;

  string res = g->tmp_line;

  g->tmp_line = tos2("");

  return res;
}
int CGen_add_placeholder(CGen *g) {

  if (g->is_tmp) {

    return g->tmp_line.len;
  };

  return g->cur_line.len;
}
void CGen_set_placeholder(CGen *g, int pos, string val) {

  if (g->nogen || g->run != main__Pass_main) {

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
int CGen_add_placeholder2(CGen *g) {

  if (g->is_tmp) {

    println(tos2("tmp in addp2"));

    v_exit(1);
  };

  _PUSH(&g->lines, (tos2("")), tmp11, string);

  return g->lines.len - 1;
}
void CGen_set_placeholder2(CGen *g, int pos, string val) {

  if (g->nogen || g->run != main__Pass_main) {

    return;
  };

  if (g->is_tmp) {

    println(tos2("tmp in setp2"));

    v_exit(1);
  };

  string tmp12 = val;

  array_set(&/*q*/ g->lines, pos, &tmp12);
}
void CGen_insert_before(CGen *g, string val) {

  string prev = (*(string *)array__get(g->lines, g->lines.len - 1));

  string tmp16 = _STR("%.*s \n %.*s \n", prev.len, prev.str, val.len, val.str);

  array_set(&/*q*/ g->lines, g->lines.len - 1, &tmp16);
}
void CGen_register_thread_fn(CGen *g, string wrapper_name, string wrapper_text,
                             string struct_text) {

  array_string tmp17 = g->thread_args;
  ;
  for (int tmp18 = 0; tmp18 < tmp17.len; tmp18++) {
    string arg = ((string *)tmp17.data)[tmp18];

    if (string_contains(arg, wrapper_name)) {

      return;
    };
  };

  _PUSH(&g->thread_args, (struct_text), tmp19, string);

  _PUSH(&g->thread_args, (wrapper_text), tmp20, string);
}
string V_prof_counters(V *c) {

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

  array_Type tmp22 = c->table->types;
  ;
  for (int tmp23 = 0; tmp23 < tmp22.len; tmp23++) {
    Type typ = ((Type *)tmp22.data)[tmp23];

    array_Fn tmp24 = typ.methods;
    ;
    for (int tmp25 = 0; tmp25 < tmp24.len; tmp25++) {
      Fn f = ((Fn *)tmp24.data)[tmp25];

      _PUSH(
          &res,
          (_STR("double %.*s_time;",
                Table_cgen_name(c->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f).len,
                Table_cgen_name(c->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f).str)),
          tmp26, string);
    };
  };

  return array_string_join(res, tos2(";\n"));
}
string Parser_print_prof_counters(Parser *p) {

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

  array_Type tmp28 = p->table->types;
  ;
  for (int tmp29 = 0; tmp29 < tmp28.len; tmp29++) {
    Type typ = ((Type *)tmp28.data)[tmp29];

    array_Fn tmp30 = typ.methods;
    ;
    for (int tmp31 = 0; tmp31 < tmp30.len; tmp31++) {
      Fn f = ((Fn *)tmp30.data)[tmp31];

      string counter =
          _STR("%.*s_time",
               Table_cgen_name(p->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f).len,
               Table_cgen_name(p->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f).str);

      _PUSH(&res,
            (_STR("if (%.*s) printf(\"%%%%f : %.*s \\n\", %.*s);", counter.len,
                  counter.str,
                  Table_cgen_name(p->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f).len,
                  Table_cgen_name(p->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f).str,
                  counter.len, counter.str)),
            tmp33, string);
    };
  };

  return array_string_join(res, tos2(";\n"));
}
void Parser_gen_type(Parser *p, string s) {

  if (!Parser_first_run(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->types, (s), tmp34, string);
}
void Parser_gen_typedef(Parser *p, string s) {

  if (!Parser_first_run(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->typedefs, (s), tmp35, string);
}
void Parser_gen_type_alias(Parser *p, string s) {

  if (!Parser_first_run(&/* ? */ *p)) {

    return;
  };

  _PUSH(&p->cgen->type_aliases, (s), tmp36, string);
}
void CGen_add_to_main(CGen *g, string s) {

  println(tos2("add to main"));

  g->fn_main = string_add(g->fn_main, s);
}
void build_thirdparty_obj_file(string flag) {

  string obj_path = string_all_after(flag, tos2(" "));

  if (os__file_exists(obj_path)) {

    return;
  };

  printf("%.*s not found, building it...\n", obj_path.len, obj_path.str);

  string parent =
      string_trim_space(string_all_before_last(obj_path, tos2("/")));

  array_string files = os__ls(parent);

  string cfiles = tos2("");

  array_string tmp41 = files;
  ;
  for (int tmp42 = 0; tmp42 < tmp41.len; tmp42++) {
    string file = ((string *)tmp41.data)[tmp42];

    if (string_ends_with(file, tos2(".c"))) {

      cfiles = string_add(
          cfiles, string_add(string_add(string_add(parent, tos2("/")), file),
                             tos2(" ")));
    };
  };

  string cc = (string_eq(os__user_os(), tos2("windows"))) ? (tos2("gcc"))
                                                          : (tos2("cc"));

  string res =
      os__exec(_STR("%.*s -fPIC -c -o %.*s %.*s", cc.len, cc.str, obj_path.len,
                    obj_path.str, cfiles.len, cfiles.str));

  println(res);
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

  return (Var){.typ = tos("", 0),
               .name = tos("", 0),
               .is_arg = 0,
               .is_const = 0,
               .is_import_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos("", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos("", 0),
               .mod = tos("", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .scope_level = 0};
}
void Fn_open_scope(Fn *f) { f->scope_level++; }
void Fn_mark_var_used(Fn *f, Var v) {

  array_Var tmp7 = f->local_vars;
  ;
  for (int i = 0; i < tmp7.len; i++) {
    Var vv = ((Var *)tmp7.data)[i];

    if (string_eq(vv.name, v.name)) {

      Var *ptr = &/*vvar*/ (*(Var *)array__get(f->local_vars, i));

      ptr->is_used = 1;
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
      .is_import_const = v.is_import_const,
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
  };

  if (f->var_idx >= f->local_vars.len) {

    _PUSH(&f->local_vars, (new_var), tmp13, Var);

  } else {

    Var tmp14 = new_var;

    array_set(&/*q*/ f->local_vars, f->var_idx, &tmp14);
  };

  f->var_idx++;
}
void Fn_clear_vars(Fn *f) {

  f->var_idx = 0;

  f->local_vars =
      new_array_from_c_array(0, 0, sizeof(Var), (Var[]){EMPTY_STRUCT_INIT});
}
bool Parser_is_sig(Parser *p) {

  return (p->pref->build_mode == main__BuildMode_default_mode ||
          p->pref->build_mode == main__BuildMode_build) &&
         (string_contains(p->file_path, main__ModPath));
}
Fn *new_fn(string pkg, bool is_public) {

  Var tmp15 = (Var){.typ = tos("", 0),
                    .name = tos("", 0),
                    .is_arg = 0,
                    .is_const = 0,
                    .is_import_const = 0,
                    .args = new_array(0, 1, sizeof(Var)),
                    .attr = tos("", 0),
                    .is_mut = 0,
                    .is_alloc = 0,
                    .ptr = 0,
                    .ref = 0,
                    .parent_fn = tos("", 0),
                    .mod = tos("", 0),
                    .line_nr = 0,
                    .is_global = 0,
                    .is_used = 0,
                    .scope_level = 0};

  Fn *f = ALLOC_INIT(
      Fn, {.pkg = pkg,
           .local_vars = array_repeat(&tmp15, main__MaxLocalVars, sizeof(Var)),
           .is_public = is_public,
           .name = tos("", 0),
           .var_idx = 0,
           .args = new_array(0, 1, sizeof(Var)),
           .is_interface = 0,
           .scope_level = 0,
           .typ = tos("", 0),
           .is_c = 0,
           .receiver_typ = tos("", 0),
           .is_method = 0,
           .returns_error = 0,
           .is_decl = 0,
           .defer_text = tos("", 0)});

  return f;
}
void Parser_fn_decl(Parser *p) {

  Parser_fgen(p, tos2("fn "));

  /*
  {

  Parser_fgenln( p , tos2("\n") ) ;

  }
  */

  bool is_pub = p->tok == main__Token_key_pub;

  bool is_live =
      string_eq(p->attr, tos2("live")) && !p->pref->is_so && p->pref->is_live;

  if (string_eq(p->attr, tos2("live")) && Parser_first_run(&/* ? */ *p) &&
      !p->pref->is_live && !p->pref->is_so) {

    println(tos2(
        "INFO: run `v -live program.v` if you want to use [live] functions"));
  };

  if (is_pub) {

    Parser_next(p);
  };

  p->returns = 0;

  Parser_next(p);

  Fn *f = new_fn(p->mod, is_pub);

  string receiver_typ = tos2("");

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

    Type *T = Table_find_type(&/* ? */ *p->table, receiver_typ);

    if (T->is_interface) {

      Parser_error(p,
                   _STR("invalid receiver type `%.*s` (`%.*s` is an interface)",
                        receiver_typ.len, receiver_typ.str, receiver_typ.len,
                        receiver_typ.str));
    };

    if (!Parser_first_run(&/* ? */ *p) && !p->builtin_pkg &&
        string_ne(T->mod, p->mod)) {

      printf("T.mod=%.*s\n", T->mod.len, T->mod.str);

      printf("p.mod=%.*s\n", p->mod.len, p->mod.str);

      Parser_error(p, _STR("cannot define new methods on non-local type `%.*s`",
                           receiver_typ.len, receiver_typ.str));
    };

    if (!p->builtin_pkg && string_contains(receiver_typ, tos2("*"))) {

      string t = string_replace(receiver_typ, tos2("*"), tos2(""));

      Parser_error(p, _STR("use `(%.*s mut %.*s)` instead of `(%.*s *%.*s)`",
                           receiver_name.len, receiver_name.str, t.len, t.str,
                           receiver_name.len, receiver_name.str, t.len, t.str));
    };

    f->receiver_typ = receiver_typ;

    if (is_mut || is_amp) {

      receiver_typ = string_add(receiver_typ, tos2("*"));
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
                         .is_import_const = 0,
                         .args = new_array(0, 1, sizeof(Var)),
                         .attr = tos("", 0),
                         .is_alloc = 0,
                         .parent_fn = tos("", 0),
                         .mod = tos("", 0),
                         .is_global = 0,
                         .is_used = 0,
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

  bool is_c = string_eq(f->name, tos2("C")) && p->tok == main__Token_dot;

  bool is_sig = Parser_is_sig(p);

  if (is_c) {

    Parser_check(p, main__Token_dot);

    f->name = Parser_check_name(p);

    f->is_c = 1;

  } else if (!p->pref->translated &&
             !string_contains(p->file_path, tos2("view.v"))) {

    if (contains_capital(f->name)) {

      Parser_error(p, tos2("function names cannot contain uppercase letters, "
                           "use snake_case instead"));
    };

    if (string_contains(f->name, tos2("__"))) {

      Parser_error(p, tos2("function names cannot contain double underscores, "
                           "use single underscores instead"));
    };
  };

  bool has_receiver = receiver_typ.len > 0;

  if (string_ne(receiver_typ, tos2(""))) {
  };

  if (!is_c && !p->builtin_pkg && string_ne(p->mod, tos2("main")) &&
      receiver_typ.len == 0) {

    f->name = Parser_prepend_pkg(&/* ? */ *p, f->name);
  };

  if (Parser_first_run(&/* ? */ *p) &&
      Table_known_fn(&/* ? */ *p->table, f->name) && receiver_typ.len == 0) {

    Fn existing_fn = Table_find_fn(&/* ? */ *p->table, f->name);

    if (!existing_fn.is_decl) {

      Parser_error(p, _STR("redefinition of `%.*s`", f->name.len, f->name.str));
    };
  };

  bool is_generic = 0;

  if (p->tok == main__Token_lt) {

    Parser_next(p);

    string gen_type = Parser_check_name(p);

    if (string_ne(gen_type, tos2("T"))) {

      Parser_error(p, tos2("only `T` is allowed as a generic type for now"));
    };

    Parser_check(p, main__Token_gt);

    is_generic = 1;
  };

  Parser_fn_args(p, f);

  if (p->tok == main__Token_not) {

    Parser_next(p);

    f->returns_error = 1;
  };

  string typ = tos2("void");

  if (p->tok == main__Token_name || p->tok == main__Token_mul ||
      p->tok == main__Token_amp || p->tok == main__Token_lsbr ||
      p->tok == main__Token_question) {

    Parser_fgen(p, tos2(" "));

    typ = Parser_get_type(p);
  };

  bool is_fn_header = !is_c && !is_sig &&
                      (p->pref->translated || p->pref->is_test) &&
                      p->tok != main__Token_lcbr;

  if (is_fn_header) {

    f->is_decl = 1;
  };

  if (!is_c && !is_sig && !is_fn_header) {

    Parser_fgen(p, tos2(" "));

    Parser_check(p, main__Token_lcbr);
  };

  if (string_starts_with(typ, tos2("Option_"))) {

    _PUSH(&p->cgen->typedefs, (_STR("typedef Option %.*s;", typ.len, typ.str)),
          tmp36, string);
  };

  f->typ = typ;

  string str_args = Fn_str_args(&/* ? */ *f, p->table);

  if (string_eq(f->name, tos2("main")) && !has_receiver) {

    if (string_ne(str_args, tos2("")) || string_ne(typ, tos2("void"))) {

      Parser_error(p,
                   tos2("fn main must have no arguments and no return values"));
    };

    typ = tos2("int");

    str_args = tos2("int argc, char** argv");
  };

  string dll_export_linkage = tos2("");

  if (p->os == main__OS_msvc && string_eq(p->attr, tos2("live")) &&
      p->pref->is_so) {

    dll_export_linkage = tos2("__declspec(dllexport) ");
  };

  string fn_name_cgen = Table_cgen_name(p->table, f);

  bool skip_main_in_test = string_eq(f->name, tos2("main")) && p->pref->is_test;

  if (!is_c && !is_live && !is_sig && !is_fn_header && !skip_main_in_test) {

    if (p->pref->obfuscate) {

      Parser_genln(p, _STR("; // %.*s", f->name.len, f->name.str));
    };

    Parser_genln(p, _STR("%.*s%.*s %.*s(%.*s) {", dll_export_linkage.len,
                         dll_export_linkage.str, typ.len, typ.str,
                         fn_name_cgen.len, fn_name_cgen.str, str_args.len,
                         str_args.str));
  };

  if (is_fn_header) {

    Parser_genln(p, _STR("%.*s %.*s(%.*s);", typ.len, typ.str, fn_name_cgen.len,
                         fn_name_cgen.str, str_args.len, str_args.str));

    Parser_fgenln(p, tos2(""));
  };

  if (is_c) {

    Parser_fgenln(p, tos2("\n"));
  };

  p->cur_fn = f;

  if (string_ne(receiver_typ, tos2(""))) {

    Type *receiver_t = Table_find_type(&/* ? */ *p->table, receiver_typ);

    if (Parser_first_run(&/* ? */ *p) &&
        string_eq(receiver_t->name, tos2(""))) {

      Table_register_type2(
          p->table,
          (Type){
              .name = string_replace(receiver_typ, tos2("*"), tos2("")),
              .mod = p->mod,
              .is_placeholder = 1,
              .fields = new_array(0, 1, sizeof(Var)),
              .methods = new_array(0, 1, sizeof(Fn)),
              .parent = tos("", 0),
              .is_c = 0,
              .is_interface = 0,
              .is_enum = 0,
              .enum_vals = new_array(0, 1, sizeof(string)),
          });
    };

    Type_add_method(receiver_t, *f);

  } else {

    Table_register_fn(p->table, *f);
  };

  if (is_sig || Parser_first_run(&/* ? */ *p) || is_live || is_fn_header ||
      skip_main_in_test) {

    if (!is_sig && !is_fn_header) {

      int opened_scopes = 0;

      int closed_scopes = 0;

      while (1) {

        if (p->tok == main__Token_lcbr) {

          opened_scopes++;
        };

        if (p->tok == main__Token_rcbr) {

          closed_scopes++;
        };

        Parser_next(p);

        if (Token_is_decl(p->tok) && !(p->prev_tok == main__Token_dot &&
                                       p->tok == main__Token_key_type)) {

          break;
        };

        if (closed_scopes > opened_scopes && p->prev_tok == main__Token_rcbr) {

          if (p->tok == main__Token_lsbr) {

            break;
          };
        };
      };
    };

    if (is_live && Parser_first_run(&/* ? */ *p) &&
        string_eq(p->mod, tos2("main"))) {

      _PUSH(&p->cgen->so_fns, (fn_name_cgen), tmp44, string);

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

    if (!is_c && string_ne(f->name, tos2("main")) &&
        Parser_first_run(&/* ? */ *p)) {

      if (string_eq(f->name, tos2("darwin__nsstring")) &&
          p->pref->build_mode == main__BuildMode_default_mode) {

        return;
      };

      _PUSH(&p->cgen->fns, (string_add(fn_decl, tos2(";"))), tmp46, string);
    };

    return;
  };

  if (string_eq(p->attr, tos2("live")) && p->pref->is_so) {

    Parser_genln(p, tos2("pthread_mutex_lock(&live_fn_mutex);"));
  };

  if (string_eq(f->name, tos2("main")) || string_eq(f->name, tos2("WinMain"))) {

    Parser_genln(p, tos2("init_consts();"));

    if (array_string_contains(p->table->imports, tos2("os"))) {

      if (string_eq(f->name, tos2("main"))) {

        Parser_genln(p, tos2("os__args = os__init_os_args(argc, argv);"));

      } else if (string_eq(f->name, tos2("WinMain"))) {

        Parser_genln(p,
                     tos2("os__args = os__parse_windows_cmd_line(pCmdLine);"));
      };
    };

    if (p->pref->is_live) {

      string file_base = string_replace(p->file_path, tos2(".v"), tos2(""));

      if (p->os != main__OS_windows && p->os != main__OS_msvc) {

        string so_name = string_add(file_base, tos2(".so"));

        Parser_genln(p, _STR(" \nload_so(\"%.*s\"); \npthread_t "
                             "_thread_so;\npthread_create(&_thread_so , NULL, "
                             "&reload_so, NULL); ",
                             so_name.len, so_name.str));

      } else {

        string so_name =
            string_add(file_base, (p->os == main__OS_msvc) ? (tos2(".dll"))
                                                           : (tos2(".so")));

        Parser_genln(p, _STR("\nlive_fn_mutex = CreateMutexA(0, 0, "
                             "0);\nload_so(\"%.*s\");\nunsigned long "
                             "_thread_so;\n_thread_so = CreateThread(0, 0, "
                             "(LPTHREAD_START_ROUTINE)&reload_so, 0, 0, "
                             "0);\n				",
                             so_name.len, so_name.str));
      };
    };

    if (p->pref->is_test &&
        !string_contains(p->scanner->file_path, tos2("/volt"))) {

      Parser_error(p, tos2("tests cannot have function `main`"));
    };
  };

  if (is_c || is_sig || is_fn_header) {

    return;
  };

  if (p->pref->is_prof && string_ne(f->name, tos2("main")) &&
      string_ne(f->name, tos2("time__ticks"))) {

    Parser_genln(p, _STR("double _PROF_START = time__ticks();//%.*s",
                         f->name.len, f->name.str));

    string cgen_name = Table_cgen_name(p->table, f);

    f->defer_text = _STR("  %.*s_time += time__ticks() - _PROF_START;",
                         cgen_name.len, cgen_name.str);
  };

  Parser_statements_no_rcbr(p);

  if (p->pref->is_prof && string_eq(f->name, tos2("main"))) {

    Parser_genln(p, Parser_print_prof_counters(p));
  };

  Parser_genln(p, f->defer_text);

  if (string_ne(typ, tos2("void")) && !p->returns &&
      string_ne(f->name, tos2("main")) && string_ne(f->name, tos2("WinMain"))) {

    Parser_error(p, _STR("%.*s must return \"%.*s\"", f->name.len, f->name.str,
                         typ.len, typ.str));
  };

  if (string_eq(p->attr, tos2("live")) && p->pref->is_so) {

    Parser_genln(p, tos2("pthread_mutex_unlock(&live_fn_mutex);"));
  };

  if (string_eq(p->mod, tos2("main"))) {
  };

  if (p->cur_fn->scope_level > 2) {
  };

  if (string_ne(p->mod, tos2("main"))) {

    Parser_genln(p, tos2("}"));

    return;
  };

  Parser_check_unused_variables(p);

  p->cur_fn = main__EmptyFn;

  Parser_genln(p, tos2("}"));

  { Parser_fgenln(p, tos2("\n")); }
}
void Parser_check_unused_variables(Parser *p) {

  array_Var tmp51 = p->cur_fn->local_vars;
  ;
  for (int tmp52 = 0; tmp52 < tmp51.len; tmp52++) {
    Var var = ((Var *)tmp51.data)[tmp52];

    if (string_eq(var.name, tos2(""))) {

      break;
    };

    if (!var.is_used && !p->pref->is_repl && !var.is_arg &&
        !p->pref->translated && string_ne(var.name, tos2("_"))) {

      p->scanner->line_nr = var.line_nr - 1;

      Parser_error(
          p, _STR("`%.*s` declared and not used", var.name.len, var.name.str));
    };
  };
}
void Parser_async_fn_call(Parser *p, Fn f, int method_ph, string receiver_var,
                          string receiver_type) {

  string thread_name = tos2("");

  string fn_name = f.name;

  if (f.is_method) {

    receiver_type = string_replace(receiver_type, tos2("*"), tos2(""));

    fn_name = _STR("%.*s_%.*s", receiver_type.len, receiver_type.str,
                   f.name.len, f.name.str);
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

  string str_args = tos2("");

  bool did_gen_something = 0;

  array_Var tmp60 = f.args;
  ;
  for (int i = 0; i < tmp60.len; i++) {
    Var arg = ((Var *)tmp60.data)[i];

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

        str_args = string_add(str_args, tos2(","));
      };

      continue;
    };

    Parser_genln(p, _STR("%.*s -> %.*s =  ", tmp_struct.len, tmp_struct.str,
                         arg.name.len, arg.name.str));

    Parser_expression(p);

    Parser_genln(p, tos2(";"));

    if (i < f.args.len - 1) {

      Parser_check(p, main__Token_comma);

      str_args = string_add(str_args, tos2(","));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    arg_struct = string_add(arg_struct, tos2("EMPTY_STRUCT_DECLARATION"));
  };

  arg_struct = string_add(
      arg_struct, _STR("} %.*s ;", arg_struct_name.len, arg_struct_name.str));

  fn_name = Table_cgen_name(p->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f);

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

  string parg = tos2("NULL");

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
      string_ne(f.pkg, p->mod)) {

    Parser_error(p, _STR("function `%.*s` is private", f.name.len, f.name.str));
  };

  p->calling_c = f.is_c;

  if (f.is_c && !p->builtin_pkg) {

    if (string_eq(f.name, tos2("free"))) {

      Parser_error(p, tos2("use `free()` instead of `C.free()`"));

    } else if (string_eq(f.name, tos2("malloc"))) {

      Parser_error(p, tos2("use `malloc()` instead of `C.malloc()`"));
    };
  };

  string cgen_name = Table_cgen_name(p->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f);

  if (!f.is_method) {

    Parser_gen(p, cgen_name);

    Parser_gen(p, tos2("("));

  } else {

    string method_call = _STR("%.*s(", cgen_name.len, cgen_name.str);

    Var receiver = *(Var *)array_first(f.args);

    if (receiver.is_mut && !p->expr_var.is_mut) {

      printf("%.*s  recv=%.*s recv_mut=%d\n", method_call.len, method_call.str,
             receiver.name.len, receiver.name.str, receiver.is_mut);

      Parser_error(p, _STR("`%.*s` is immutable", p->expr_var.name.len,
                           p->expr_var.name.str));
    };

    if (receiver.ref ||
        (receiver.is_mut && !string_contains(receiver_type, tos2("*")))) {

      method_call = string_add(method_call, tos2("& /* ? */"));
    };

    if (!receiver.is_mut && string_contains(receiver_type, tos2("*"))) {

      method_call = string_add(method_call, tos2("*"));
    };

    string cast = tos2("");

    if (string_eq(f.typ, tos2("void*"))) {

      cast = string_all_after(receiver_type, tos2("_"));

      cast = _STR("*(%.*s*) ", cast.len, cast.str);
    };

    CGen_set_placeholder(p->cgen, method_ph,
                         _STR("%.*s %.*s", cast.len, cast.str, method_call.len,
                              method_call.str));
  };

  Parser_next(p);

  Parser_fn_call_args(p, &/*11 EXP:"Fn*" GOT:"Fn" */ f);

  Parser_gen(p, tos2(")"));

  p->calling_c = 0;
}
void Parser_fn_args(Parser *p, Fn *f) {

  Parser_check(p, main__Token_lpar);

  /*
  {

  Parser_check( p , main__Token_rpar ) ;

  }
  */

  if (f->is_interface) {

    Var int_arg = (Var){.typ = f->receiver_typ,
                        .name = tos("", 0),
                        .is_arg = 0,
                        .is_const = 0,
                        .is_import_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos("", 0),
                        .is_mut = 0,
                        .is_alloc = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos("", 0),
                        .mod = tos("", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .scope_level = 0};

    _PUSH(&f->args, (int_arg), tmp71, Var);
  };

  bool types_only = p->tok == main__Token_mul ||
                    (Parser_peek(p) == main__Token_comma &&
                     Table_known_type(&/* ? */ *p->table, p->lit)) ||
                    Parser_peek(p) == main__Token_rpar;

  if (types_only) {

    while (p->tok != main__Token_rpar) {

      string typ = Parser_get_type(p);

      Var v = (Var){.typ = typ,
                    .is_arg = 1,
                    .line_nr = p->scanner->line_nr,
                    .name = tos("", 0),
                    .is_const = 0,
                    .is_import_const = 0,
                    .args = new_array(0, 1, sizeof(Var)),
                    .attr = tos("", 0),
                    .is_mut = 0,
                    .is_alloc = 0,
                    .ptr = 0,
                    .ref = 0,
                    .parent_fn = tos("", 0),
                    .mod = tos("", 0),
                    .is_global = 0,
                    .is_used = 0,
                    .scope_level = 0};

      _PUSH(&f->args, (v), tmp75, Var);

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

      _PUSH(&names, (Parser_check_name(p)), tmp77, string);
    };

    Parser_fspace(p);

    bool is_mut = p->tok == main__Token_key_mut;

    if (is_mut) {

      Parser_next(p);
    };

    string typ = Parser_get_type(p);

    if (is_mut && is_primitive_type(typ)) {

      Parser_error(p, string_add(tos2("mutable arguments are only allowed for "
                                      "arrays, maps, and structs."),
                                 tos2("\nreturn values instead: `foo(n mut "
                                      "int)` => `foo(n int) int`")));
    };

    array_string tmp80 = names;
    ;
    for (int tmp81 = 0; tmp81 < tmp80.len; tmp81++) {
      string name = ((string *)tmp80.data)[tmp81];

      if (!Parser_first_run(&/* ? */ *p) &&
          !Table_known_type(&/* ? */ *p->table, typ)) {

        Parser_error(p, _STR("fn_args: unknown type %.*s", typ.len, typ.str));
      };

      if (is_mut) {

        typ = string_add(typ, tos2("*"));
      };

      Var v = (Var){.name = name,
                    .typ = typ,
                    .is_arg = 1,
                    .is_mut = is_mut,
                    .ptr = is_mut,
                    .line_nr = p->scanner->line_nr,
                    .is_const = 0,
                    .is_import_const = 0,
                    .args = new_array(0, 1, sizeof(Var)),
                    .attr = tos("", 0),
                    .is_alloc = 0,
                    .ref = 0,
                    .parent_fn = tos("", 0),
                    .mod = tos("", 0),
                    .is_global = 0,
                    .is_used = 0,
                    .scope_level = 0};

      Fn_register_var(f, v);

      _PUSH(&f->args, (v), tmp83, Var);
    };

    if (p->tok == main__Token_comma) {

      Parser_next(p);
    };

    if (p->tok == main__Token_dotdot) {

      _PUSH(&f->args,
            ((Var){.name = tos2(".."),
                   .typ = tos("", 0),
                   .is_arg = 0,
                   .is_const = 0,
                   .is_import_const = 0,
                   .args = new_array(0, 1, sizeof(Var)),
                   .attr = tos("", 0),
                   .is_mut = 0,
                   .is_alloc = 0,
                   .ptr = 0,
                   .ref = 0,
                   .parent_fn = tos("", 0),
                   .mod = tos("", 0),
                   .line_nr = 0,
                   .is_global = 0,
                   .is_used = 0,
                   .scope_level = 0}),
            tmp84, Var);

      Parser_next(p);
    };
  };

  { Parser_check(p, main__Token_rpar); }
}
Fn *Parser_fn_call_args(Parser *p, Fn *f) {

  Parser_check(p, main__Token_lpar);

  if (f->is_c) {

    while (p->tok != main__Token_rpar) {

      Parser_bool_expression(p);

      if (p->tok == main__Token_comma) {

        Parser_gen(p, tos2(", "));

        Parser_check(p, main__Token_comma);
      };
    };

    Parser_check(p, main__Token_rpar);

    return f;
  };

  array_Var tmp85 = f->args;
  ;
  for (int i = 0; i < tmp85.len; i++) {
    Var arg = ((Var *)tmp85.data)[i];

    if (i == 0 && f->is_method) {

      if (f->args.len > 1) {

        Parser_gen(p, tos2(","));
      };

      continue;
    };

    if (i == f->args.len - 1 && string_eq(arg.name, tos2(".."))) {

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

      if (p->tok != main__Token_key_mut) {

        Parser_error(p, _STR("`%.*s` is a key_mut argument, you need to "
                             "provide `mut`: `%.*s(...mut a...)`",
                             arg.name.len, arg.name.str, f->name.len,
                             f->name.str));
      };

      if (Parser_peek(p) != main__Token_name) {

        Parser_error(
            p, _STR("`%.*s` is a key_mut argument, you need to provide a "
                    "variable to modify: `%.*s(... mut a...)`",
                    arg.name.len, arg.name.str, f->name.len, f->name.str));
      };

      Parser_check(p, main__Token_key_mut);
    };

    p->expected_type = arg.typ;

    string typ = Parser_bool_expression(p);

    if (i == 0 && string_eq(f->name, tos2("println")) &&
        string_ne(typ, tos2("string")) && string_ne(typ, tos2("void"))) {

      Type *T = Table_find_type(&/* ? */ *p->table, typ);

      string fmt = Parser_typ_to_fmt(p, typ, 0);

      if (string_ne(fmt, tos2(""))) {

        CGen_resetln(p->cgen,
                     string_replace(
                         p->cgen->cur_line, tos2("println ("),
                         string_add(string_add(tos2("/*opt*/printf (\""), fmt),
                                    tos2("\\n\", "))));

        continue;
      };

      if (string_ends_with(typ, tos2("*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2("ptr_str("));

        Parser_gen(p, tos2(")"));

        continue;
      };

      if (!Type_has_method(&/* ? */ *T, tos2("str"))) {

        string error_msg =
            (_STR("`%.*s` needs to have method `str() string` to be printable",
                  typ.len, typ.str));

        if (T->fields.len > 0) {

          int index = p->cgen->cur_line.len - 1;

          while (index > 0 && string_at(p->cgen->cur_line, index) != ' ') {

            index--;
          };

          string name = string_right(p->cgen->cur_line, index + 1);

          if (string_eq(name, tos2("}"))) {

            Parser_error(p, error_msg);
          };

          CGen_resetln(p->cgen, string_left(p->cgen->cur_line, index));

          Parser_create_type_string(p, *T, name);

          string_replace(p->cgen->cur_line, typ, tos2(""));

          Parser_next(p);

          return Parser_fn_call_args(p, f);
        };

        Parser_error(p, error_msg);
      };

      CGen_set_placeholder(p->cgen, ph, _STR("%.*s_str(", typ.len, typ.str));

      Parser_gen(p, tos2(")"));

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

      if (string_contains(got, tos2("*")) &&
          !string_contains(expected, tos2("*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2("*"));
      };

      if (!string_contains(got, tos2("*")) &&
          string_contains(expected, tos2("*")) &&
          string_ne(got, tos2("voidptr"))) {

        if (!(string_eq(expected, tos2("void*")) &&
              string_eq(got, tos2("int"))) &&
            !(string_eq(expected, tos2("byte*")) &&
              string_contains(got, tos2("]byte"))) &&
            !(string_eq(expected, tos2("byte*")) &&
              string_eq(got, tos2("string")))) {

          CGen_set_placeholder(p->cgen, ph,
                               _STR("& /*11 EXP:\"%.*s\" GOT:\"%.*s\" */",
                                    expected.len, expected.str, got.len,
                                    got.str));
        };
      };
    };

    if (is_interface) {

      if (!string_contains(got, tos2("*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2("&"));
      };

      Type *interface_type = Table_find_type(&/* ? */ *p->table, arg.typ);

      array_Fn tmp101 = interface_type->methods;
      ;
      for (int tmp102 = 0; tmp102 < tmp101.len; tmp102++) {
        Fn method = ((Fn *)tmp101.data)[tmp102];

        Parser_gen(p, _STR(", %.*s_%.*s ", typ.len, typ.str, method.name.len,
                           method.name.str));
      };
    };

    if (i < f->args.len - 1) {

      bool is_vararg =
          i == f->args.len - 2 &&
          string_eq((*(Var *)array__get(f->args, i + 1)).name, tos2(".."));

      if (p->tok != main__Token_comma && !is_vararg) {

        Parser_error(p, _STR("wrong number of arguments for %d,%.*s fn `%.*s`: "
                             "expected %d, but got less",
                             i, arg.name.len, arg.name.str, f->name.len,
                             f->name.str, f->args.len));
      };

      if (p->tok == main__Token_comma) {

        Parser_fgen(p, tos2(", "));
      };

      if (!is_vararg) {

        Parser_next(p);

        Parser_gen(p, tos2(","));
      };
    };
  };

  if (f->args.len > 0) {

    Var last_arg = *(Var *)array_last(f->args);

    if (string_eq(last_arg.name, tos2(".."))) {

      while (p->tok != main__Token_rpar) {

        if (p->tok == main__Token_comma) {

          Parser_gen(p, tos2(","));

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
string Fn_typ_str(Fn f) {

  strings__Builder sb = strings__new_builder(50);

  strings__Builder_write(&/* ? */ sb, tos2("fn ("));

  array_Var tmp112 = f.args;
  ;
  for (int i = 0; i < tmp112.len; i++) {
    Var arg = ((Var *)tmp112.data)[i];

    strings__Builder_write(&/* ? */ sb, arg.typ);

    if (i < f.args.len - 1) {

      strings__Builder_write(&/* ? */ sb, tos2(","));
    };
  };

  strings__Builder_write(&/* ? */ sb, tos2(")"));

  if (string_ne(f.typ, tos2("void"))) {

    strings__Builder_write(&/* ? */ sb, _STR(" %.*s", f.typ.len, f.typ.str));
  };

  return strings__Builder_str(sb);
}
string Fn_str_args(Fn *f, Table *table) {

  string s = tos2("");

  array_Var tmp114 = f->args;
  ;
  for (int i = 0; i < tmp114.len; i++) {
    Var arg = ((Var *)tmp114.data)[i];

    if (Table_is_interface(&/* ? */ *table, arg.typ)) {

      s = string_add(s, _STR(" void* %.*s", arg.name.len, arg.name.str));

      Type *interface_type = Table_find_type(&/* ? */ *table, arg.typ);

      array_Fn tmp116 = interface_type->methods;
      ;
      for (int tmp117 = 0; tmp117 < tmp116.len; tmp117++) {
        Fn method = ((Fn *)tmp116.data)[tmp117];

        s = string_add(s, _STR(", %.*s (*%.*s_%.*s)(void*) ", method.typ.len,
                               method.typ.str, arg.typ.len, arg.typ.str,
                               method.name.len, method.name.str));
      };

    } else if (string_eq(arg.name, tos2(".."))) {

      s = string_add(s, tos2("..."));

    } else {

      s = string_add(
          s, Table_cgen_name_type_pair(&/* ? */ *table, arg.name, arg.typ));
    };

    if (i < f->args.len - 1) {

      s = string_add(s, tos2(", "));
    };
  };

  return s;
}
void Parser_gen_json_for_type(Parser *p, Type typ) {

  string dec = tos2("");

  string enc = tos2("");

  string t = typ.name;

  if (string_eq(t, tos2("int")) || string_eq(t, tos2("string")) ||
      string_eq(t, tos2("bool"))) {

    return;
  };

  if (Parser_first_run(&/* ? */ *p)) {

    return;
  };

  Fn dec_fn = (Fn){.pkg = p->mod,
                   .typ = _STR("Option_%.*s", typ.name.len, typ.name.str),
                   .name = js_dec_name(t),
                   .local_vars = new_array(0, 1, sizeof(Var)),
                   .var_idx = 0,
                   .args = new_array(0, 1, sizeof(Var)),
                   .is_interface = 0,
                   .scope_level = 0,
                   .is_c = 0,
                   .receiver_typ = tos("", 0),
                   .is_public = 0,
                   .is_method = 0,
                   .returns_error = 0,
                   .is_decl = 0,
                   .defer_text = tos("", 0)};

  if (Table_known_fn(&/* ? */ *p->table, dec_fn.name)) {

    return;
  };

  Var arg = (Var){.typ = tos2("cJSON*"),
                  .name = tos("", 0),
                  .is_arg = 0,
                  .is_const = 0,
                  .is_import_const = 0,
                  .args = new_array(0, 1, sizeof(Var)),
                  .attr = tos("", 0),
                  .is_mut = 0,
                  .is_alloc = 0,
                  .ptr = 0,
                  .ref = 0,
                  .parent_fn = tos("", 0),
                  .mod = tos("", 0),
                  .line_nr = 0,
                  .is_global = 0,
                  .is_used = 0,
                  .scope_level = 0};

  _PUSH(&dec_fn.args, (arg), tmp6, Var);

  Table_register_fn(p->table, dec_fn);

  Fn enc_fn = (Fn){.pkg = p->mod,
                   .typ = tos2("cJSON*"),
                   .name = js_enc_name(t),
                   .local_vars = new_array(0, 1, sizeof(Var)),
                   .var_idx = 0,
                   .args = new_array(0, 1, sizeof(Var)),
                   .is_interface = 0,
                   .scope_level = 0,
                   .is_c = 0,
                   .receiver_typ = tos("", 0),
                   .is_public = 0,
                   .is_method = 0,
                   .returns_error = 0,
                   .is_decl = 0,
                   .defer_text = tos("", 0)};

  Var enc_arg = (Var){.typ = t,
                      .name = tos("", 0),
                      .is_arg = 0,
                      .is_const = 0,
                      .is_import_const = 0,
                      .args = new_array(0, 1, sizeof(Var)),
                      .attr = tos("", 0),
                      .is_mut = 0,
                      .is_alloc = 0,
                      .ptr = 0,
                      .ref = 0,
                      .parent_fn = tos("", 0),
                      .mod = tos("", 0),
                      .line_nr = 0,
                      .is_global = 0,
                      .is_used = 0,
                      .scope_level = 0};

  _PUSH(&enc_fn.args, (enc_arg), tmp9, Var);

  Table_register_fn(p->table, enc_fn);

  dec = string_add(
      dec,
      _STR(
          "\n//%.*s %.*s(cJSON* root) {  \nOption %.*s(cJSON* root, %.*s* res) "
          "{  \n//  %.*s res; \n  if (!root) {\n    const char *error_ptr = "
          "cJSON_GetErrorPtr();\n    if (error_ptr != NULL)	{\n      "
          "fprintf(stderr, \"Error in decode() for %.*s error_ptr=: "
          "%%%%s\\n\", error_ptr);\n//      printf(\"\\nbad js=%%%%s\\n\", "
          "js.str); \n      return v_error(tos2(error_ptr));\n    }\n  }\n",
          t.len, t.str, dec_fn.name.len, dec_fn.name.str, dec_fn.name.len,
          dec_fn.name.str, t.len, t.str, t.len, t.str, t.len, t.str));

  enc =
      string_add(enc, _STR("\ncJSON* %.*s(%.*s val) {  \ncJSON *o = "
                           "cJSON_CreateObject();\nstring res = tos2(\"\"); \n",
                           enc_fn.name.len, enc_fn.name.str, t.len, t.str));

  if (string_starts_with(t, tos2("array_"))) {

    dec = string_add(dec, Parser_decode_array(p, t));

    enc = string_add(enc, Parser_encode_array(&/* ? */ *p, t));
  };

  array_Var tmp10 = typ.fields;
  ;
  for (int tmp11 = 0; tmp11 < tmp10.len; tmp11++) {
    Var field = ((Var *)tmp10.data)[tmp11];

    if (string_eq(field.attr, tos2("skip"))) {

      continue;
    };

    Type *field_type = Table_find_type(&/* ? */ *p->table, field.typ);

    Parser_gen_json_for_type(p, *field_type);

    string name = field.name;

    string _typ = string_replace(field.typ, tos2("*"), tos2(""));

    string enc_name = js_enc_name(_typ);

    string dec_name = js_dec_name(_typ);

    if (is_js_prim(_typ)) {

      dec = string_add(
          dec, _STR(" /*prim*/ res->%.*s = %.*s(js_get(root, \"%.*s\"))",
                    name.len, name.str, dec_name.len, dec_name.str,
                    field.name.len, field.name.str));

    } else {

      dec = string_add(
          dec, _STR(" /*!!*/ %.*s(js_get(root, \"%.*s\"), & (res->%.*s))",
                    dec_name.len, dec_name.str, field.name.len, field.name.str,
                    name.len, name.str));
    };

    dec = string_add(dec, tos2(";\n"));

    enc = string_add(
        enc, _STR("  cJSON_AddItemToObject(o,  \"%.*s\", %.*s(val.%.*s)); \n",
                  name.len, name.str, enc_name.len, enc_name.str, name.len,
                  name.str));
  };

  _PUSH(&p->cgen->fns,
        (_STR("%.*s return opt_ok(res, sizeof(*res)); \n}", dec.len, dec.str)),
        tmp17, string);

  _PUSH(&p->cgen->fns,
        (_STR("/*enc start*/ %.*s return o;}", enc.len, enc.str)), tmp18,
        string);
}
bool is_js_prim(string typ) {

  return string_eq(typ, tos2("int")) || string_eq(typ, tos2("string")) ||
         string_eq(typ, tos2("bool")) || string_eq(typ, tos2("f32")) ||
         string_eq(typ, tos2("f64")) || string_eq(typ, tos2("i8")) ||
         string_eq(typ, tos2("i16")) || string_eq(typ, tos2("i32")) ||
         string_eq(typ, tos2("i64"));
}
string Parser_decode_array(Parser *p, string typ) {

  typ = string_replace(typ, tos2("array_"), tos2(""));

  Type *t = Table_find_type(&/* ? */ *p->table, typ);

  string fn_name = js_dec_name(typ);

  Parser_gen_json_for_type(p, *t);

  string s = tos2("");

  if (is_js_prim(typ)) {

    s = _STR("%.*s val= %.*s(jsval); ", typ.len, typ.str, fn_name.len,
             fn_name.str);

  } else {

    s = _STR("  %.*s val; %.*s(jsval, &val); ", typ.len, typ.str, fn_name.len,
             fn_name.str);
  };

  return _STR("\n*res = new_array(0, 0, sizeof(%.*s));\nconst cJSON *jsval = "
              "NULL;\ncJSON_ArrayForEach(jsval, root)\n{\n%.*s \n  "
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
string Parser_encode_array(Parser *p, string typ) {

  typ = string_replace(typ, tos2("array_"), tos2(""));

  string fn_name = js_enc_name(typ);

  return _STR(
      "\no = cJSON_CreateArray();\nfor (int i = 0; i < val.len; i++){\n  "
      "cJSON_AddItemToArray(o, %.*s(  ((%.*s*)val.data)[i]  ));\n} \n",
      fn_name.len, fn_name.str, typ.len, typ.str);
}
string modules_path() {

  return string_add(os__home_dir(), tos2("/.vmodules/"));
}
int main(int argc, char **argv) {
  init_consts();
  os__args = os__init_os_args(argc, argv);

  array_string args = env_vflags_and_os_args();

  if (_IN(string, tos2("-v"), args) || _IN(string, tos2("--version"), args) ||
      _IN(string, tos2("version"), args)) {

    printf("V %.*s\n", main__Version.len, main__Version.str);

    return 0;
  };

  if (_IN(string, tos2("-h"), args) || _IN(string, tos2("--help"), args) ||
      _IN(string, tos2("help"), args)) {

    println(main__HelpText);

    return 0;
  };

  if (_IN(string, tos2("translate"), args)) {

    println(tos2("Translating C to V will be available in V 0.3"));

    return 0;
  };

  if (_IN(string, tos2("fmt"), args)) {

    string file = *(string *)array_last(args);

    if (!os__file_exists(file)) {

      printf("\"%.*s\" does not exist\n", file.len, file.str);

      v_exit(1);
    };

    if (!string_ends_with(file, tos2(".v"))) {

      println(tos2("v fmt can only be used on .v files"));

      v_exit(1);
    };

    println(tos2("vfmt is temporarily disabled"));

    return 0;
  };

  if (_IN(string, tos2("get"), args)) {

    if (!os__file_exists(main__ModPath)) {

      os__mkdir(main__ModPath);
    };
  };

  if (args.len < 2 ||
      (args.len == 2 &&
       string_eq((*(string *)array__get(args, 1)), tos2("-")))) {

    run_repl();

    return 0;
  };

  V *v = new_v(args);

  if (v->pref->is_verbose) {

    println(array_string_str(args));
  };

  if (_IN(string, tos2("doc"), args)) {

    v_exit(0);
  };

  V_compile(v);
}
void V_compile(V *v) {

  CGen *cgen = v->cgen;

  CGen_genln(cgen, tos2("// Generated by V"));

  V_add_user_v_files(v);

  if (v->pref->is_verbose) {

    println(tos2("all .v files:"));

    println(array_string_str(v->files));
  };

  array_string tmp7 = v->files;
  ;
  for (int tmp8 = 0; tmp8 < tmp7.len; tmp8++) {
    string file = ((string *)tmp7.data)[tmp8];

    Parser p = V_new_parser(v, file, main__Pass_decl);

    Parser_parse(&/* ? */ p);
  };

  cgen->run = main__Pass_main;

  if (v->pref->is_play) {

    CGen_genln(cgen, tos2("#define VPLAY (1) "));
  };

  CGen_genln(
      cgen,
      tos2(
          "   \n#include <stdio.h>  // TODO remove all these includes, define "
          "all function signatures and types manually \n#include "
          "<stdlib.h>\n#include <signal.h>\n#include <stdarg.h> // for va_list "
          "\n#include <inttypes.h>  // int64_t etc \n\n#define "
          "STRUCT_DEFAULT_VALUE {}\n#define EMPTY_STRUCT_DECLARATION\n#define "
          "EMPTY_STRUCT_INIT\n#define OPTION_CAST(x) (x)\n\n#ifdef "
          "_WIN32\n#define WIN32_LEAN_AND_MEAN\n#include <windows.h>\n#include "
          "<shellapi.h>\n#include <io.h> // _waccess\n#include <fcntl.h> // "
          "_O_U8TEXT\n#include <direct.h> // _wgetcwd\n//#include "
          "<WinSock2.h>\n#ifdef _MSC_VER\n// On MSVC these are the same (as "
          "long as /volatile:ms is passed)\n#define _Atomic volatile\n\n// "
          "MSVC can\'t parse some things properly\n#undef "
          "STRUCT_DEFAULT_VALUE\n#define STRUCT_DEFAULT_VALUE {0}\n#undef "
          "EMPTY_STRUCT_DECLARATION\n#define EMPTY_STRUCT_DECLARATION void "
          "*____dummy_variable;\n#undef EMPTY_STRUCT_INIT\n#define "
          "EMPTY_STRUCT_INIT 0\n#define OPTION_CAST(x)\n#endif\n\nvoid "
          "pthread_mutex_lock(HANDLE *m) {\n	WaitForSingleObject(*m, "
          "INFINITE);\n}\n\nvoid pthread_mutex_unlock(HANDLE *m) {\n	"
          "ReleaseMutex(*m);\n}\n#else\n#include <pthread.h> \n#endif "
          "\n\n//================================== TYPEDEFS "
          "================================*/ \n\ntypedef unsigned char "
          "byte;\ntypedef unsigned int uint;\ntypedef int64_t i64;\ntypedef "
          "int32_t i32;\ntypedef int16_t i16;\ntypedef int8_t i8;\ntypedef "
          "uint64_t u64;\ntypedef uint32_t u32;\ntypedef uint16_t "
          "u16;\ntypedef uint8_t u8;\ntypedef uint32_t rune;\ntypedef float "
          "f32;\ntypedef double f64; \ntypedef unsigned char* "
          "byteptr;\ntypedef int* intptr;\ntypedef void* voidptr;\ntypedef "
          "struct array array;\ntypedef struct map map;\ntypedef array "
          "array_string; \ntypedef array array_int; \ntypedef array "
          "array_byte; \ntypedef array array_uint; \ntypedef array "
          "array_float; \ntypedef array array_f32; \ntypedef array array_f64; "
          "\ntypedef map map_int; \ntypedef map map_string; \n#ifndef "
          "bool\n	typedef int bool;\n	#define true 1\n	"
          "#define false 0\n#endif\n\n//============================== HELPER "
          "C MACROS =============================*/ \n\n#define _PUSH(arr, "
          "val, tmp, tmp_typ) {tmp_typ tmp = (val); array__push(arr, "
          "&tmp);}\n#define _PUSH_MANY(arr, val, tmp, tmp_typ) {tmp_typ tmp = "
          "(val); array__push_many(arr, tmp.data, tmp.len);}\n#define _IN(typ, "
          "val, arr) array_##typ##_contains(arr, val) \n#define _IN_MAP(val, "
          "m) map__exists(m, val) \n#define ALLOC_INIT(type, ...) (type "
          "*)memdup((type[]){ __VA_ARGS__ }, sizeof(type)) "
          "\n\n//================================== GLOBALS "
          "=================================*/   \n//int V_ZERO = 0; \nbyteptr "
          "g_str_buf; \nint load_so(byteptr);\nvoid reload_so();\nvoid "
          "init_consts();"));

  if (v->os != main__OS_windows && v->os != main__OS_msvc) {

    if (v->pref->is_so) {

      CGen_genln(cgen, tos2("pthread_mutex_t live_fn_mutex;"));
    };

    if (v->pref->is_live) {

      CGen_genln(
          cgen,
          tos2("pthread_mutex_t live_fn_mutex = PTHREAD_MUTEX_INITIALIZER;"));
    };

  } else {

    if (v->pref->is_so) {

      CGen_genln(cgen, tos2("HANDLE live_fn_mutex;"));
    };

    if (v->pref->is_live) {

      CGen_genln(cgen, tos2("HANDLE live_fn_mutex = 0;"));
    };
  };

  bool imports_json = array_string_contains(v->table->imports, tos2("json"));

  if (v->os == main__OS_mac &&
      ((v->pref->build_mode == main__BuildMode_embed_vlib &&
        array_string_contains(v->table->imports, tos2("ui"))) ||
       (v->pref->build_mode == main__BuildMode_build &&
        string_contains(v->dir, tos2("/ui"))))) {

    CGen_genln(cgen, tos2("id defaultFont = 0; // main.v"));
  };

  if (imports_json && v->pref->build_mode == main__BuildMode_embed_vlib ||
      (v->pref->build_mode == main__BuildMode_build &&
       string_contains(v->out_name, tos2("json.o")))) {
  };

  if (v->pref->build_mode == main__BuildMode_default_mode) {

    if (imports_json) {

      CGen_genln(cgen, tos2("#include \"cJSON.h\""));
    };
  };

  if (v->pref->build_mode == main__BuildMode_embed_vlib ||
      v->pref->build_mode == main__BuildMode_default_mode) {

    CGen_genln(cgen, tos2("int g_test_ok = 1; "));

    if (array_string_contains(v->table->imports, tos2("json"))) {

      CGen_genln(cgen,
                 tos2(" \n#define js_get(object, key) "
                      "cJSON_GetObjectItemCaseSensitive((object), (key))\n"));
    };
  };

  if (array_string_contains(os__args, tos2("-debug_alloc"))) {

    CGen_genln(cgen, tos2("#define DEBUG_ALLOC 1"));
  };

  CGen_genln(cgen, tos2("/*================================== FNS "
                        "=================================*/"));

  CGen_genln(cgen, tos2("this line will be replaced with definitions"));

  int defs_pos = cgen->lines.len - 1;

  array_string tmp12 = v->files;
  ;
  for (int tmp13 = 0; tmp13 < tmp12.len; tmp13++) {
    string file = ((string *)tmp12.data)[tmp13];

    Parser p = V_new_parser(v, file, main__Pass_main);

    Parser_parse(&/* ? */ p);

    if (!v->pref->nofmt && !string_contains(file, tos2("/vlib/"))) {
    };
  };

  V_log(&/* ? */ *v, tos2("Done parsing."));

  strings__Builder d = strings__new_builder(10000);

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->includes));

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->typedefs));

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->types));

  strings__Builder_writeln(&/* ? */ d,
                           tos2("\nstring _STR(const char*, ...);\n"));

  strings__Builder_writeln(&/* ? */ d,
                           tos2("\nstring _STR_TMP(const char*, ...);\n"));

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->fns));

  strings__Builder_writeln(&/* ? */ d, array_string_join_lines(cgen->consts));

  strings__Builder_writeln(&/* ? */ d,
                           array_string_join_lines(cgen->thread_args));

  if (v->pref->is_prof) {

    strings__Builder_writeln(&/* ? */ d, tos2("; // Prof counters:"));

    strings__Builder_writeln(&/* ? */ d, V_prof_counters(v));
  };

  string dd = strings__Builder_str(d);

  array_set(&/* ? */ cgen->lines, defs_pos,
            &/*11 EXP:"void*" GOT:"string" */ dd);

  if (v->pref->build_mode == main__BuildMode_default_mode ||
      v->pref->build_mode == main__BuildMode_embed_vlib) {

    CGen_genln(cgen, _STR("void init_consts() { g_str_buf=malloc(1000); %.*s }",
                          array_string_join_lines(cgen->consts_init).len,
                          array_string_join_lines(cgen->consts_init).str));

    CGen_genln(
        cgen,
        tos2(
            "\nstring _STR(const char *fmt, ...) {\n	va_list "
            "argptr;\n	va_start(argptr, fmt);\n	size_t len = "
            "vsnprintf(0, 0, fmt, argptr) + 1;  \n	"
            "va_end(argptr);\n	byte* buf = malloc(len);  \n	"
            "va_start(argptr, fmt);\n	vsprintf(buf, fmt, argptr);\n	"
            "va_end(argptr);\n#ifdef DEBUG_ALLOC \n	puts(\"_STR:\"); "
            "\n	puts(buf); \n#endif \n	return tos2(buf);\n}\n\nstring "
            "_STR_TMP(const char *fmt, ...) {\n	va_list argptr;\n	"
            "va_start(argptr, fmt);\n	size_t len = vsnprintf(0, 0, fmt, "
            "argptr) + 1;  \n	va_end(argptr);\n	va_start(argptr, "
            "fmt);\n	vsprintf(g_str_buf, fmt, argptr);\n	"
            "va_end(argptr);\n#ifdef DEBUG_ALLOC \n	//puts(\"_STR_TMP:\"); "
            "\n	//puts(g_str_buf); \n#endif \n	return "
            "tos2(g_str_buf);\n}\n\n"));
  };

  if (v->pref->build_mode != main__BuildMode_build) {

    if (!Table_main_exists(&/* ? */ *v->table) && !v->pref->is_test) {

      if (v->pref->is_script) {

        CGen_genln(
            cgen,
            _STR("int main() { \n#ifdef _WIN32\n _setmode(_fileno(stdout), "
                 "_O_U8TEXT); \n#endif\n init_consts(); %.*s; return 0; }",
                 cgen->fn_main.len, cgen->fn_main.str));

      } else {

        println(
            tos2("panic: function `main` is undeclared in the main module"));

        v_exit(1);
      };

    } else if (v->pref->is_test) {

      CGen_genln(
          cgen, tos2("int main() { \n#ifdef _WIN32\n _setmode(_fileno(stdout), "
                     "_O_U8TEXT); \n#endif\n init_consts();"));

      map_Fn tmp17 = v->table->fns;
      array_string keys_tmp17 = map_keys(&tmp17);
      for (int l = 0; l < keys_tmp17.len; l++) {
        string key = ((string *)keys_tmp17.data)[l];
        Fn f = {0};
        map_get(tmp17, key, &f);

        if (string_starts_with(f.name, tos2("test_"))) {

          CGen_genln(cgen, _STR("%.*s();", f.name.len, f.name.str));
        };
      };

      CGen_genln(cgen, tos2("return g_test_ok == 0; }"));
    };
  };

  if (v->pref->is_live) {

    string file = v->dir;

    string file_base = string_replace(v->dir, tos2(".v"), tos2(""));

    string so_name = string_add(file_base, tos2(".so"));

    string vexe = (*(string *)array__get(os__args, 0));

    if (string_eq(os__user_os(), tos2("windows"))) {

      vexe = string_replace(vexe, tos2("\\"), tos2("\\\\"));
    };

    string msvc = tos2("");

    if (v->os == main__OS_msvc) {

      msvc = tos2("-os msvc");
    };

    string debug = tos2("");

    if (v->pref->is_debug) {

      debug = tos2("-debug");
    };

    os__system(_STR("%.*s %.*s %.*s -o %.*s -shared %.*s", vexe.len, vexe.str,
                    msvc.len, msvc.str, debug.len, debug.str, file_base.len,
                    file_base.str, file.len, file.str));

    CGen_genln(
        cgen, tos2("\n\nvoid lfnmutex_print(char *s){\n	if(0){\n	"
                   "	fflush(stderr);\n		fprintf(stderr,\">> "
                   "live_fn_mutex: %p | %s\\n\", &live_fn_mutex, s);\n	"
                   "	fflush(stderr);\n	}\n}\n"));

    if (v->os != main__OS_windows && v->os != main__OS_msvc) {

      CGen_genln(
          cgen,
          tos2(
              "\n#include <dlfcn.h>\nvoid* live_lib=0;\nint load_so(byteptr "
              "path) {\n	char cpath[1024];\n	"
              "sprintf(cpath,\"./%s\", path);\n	//printf(\"load_so %s\\n\", "
              "cpath); \n	if (live_lib) dlclose(live_lib);\n	"
              "live_lib = dlopen(cpath, RTLD_LAZY);\n	if (!live_lib) "
              "{\n		puts(\"open failed\"); \n		"
              "exit(1); \n		return 0;\n	}\n"));

      array_string tmp26 = cgen->so_fns;
      ;
      for (int tmp27 = 0; tmp27 < tmp26.len; tmp27++) {
        string so_fn = ((string *)tmp26.data)[tmp27];

        CGen_genln(cgen, _STR("%.*s = dlsym(live_lib, \"%.*s\");  ", so_fn.len,
                              so_fn.str, so_fn.len, so_fn.str));
      };

    } else {

      CGen_genln(
          cgen,
          tos2("\nvoid* live_lib=0;\nint load_so(byteptr path) {\n	char "
               "cpath[1024];\n	sprintf(cpath, \"./%s\", path);\n	if "
               "(live_lib) FreeLibrary(live_lib);\n	live_lib = "
               "LoadLibraryA(cpath);\n	if (!live_lib) {\n		"
               "puts(\"open failed\");\n		exit(1);\n	"
               "	return 0;\n	}\n"));

      array_string tmp28 = cgen->so_fns;
      ;
      for (int tmp29 = 0; tmp29 < tmp28.len; tmp29++) {
        string so_fn = ((string *)tmp28.data)[tmp29];

        CGen_genln(cgen,
                   _STR("%.*s = (void *)GetProcAddress(live_lib, \"%.*s\");  ",
                        so_fn.len, so_fn.str, so_fn.len, so_fn.str));
      };
    };

    CGen_genln(
        cgen,
        _STR("return 1; \n}\n\nint _live_reloads = 0;\nvoid reload_so() "
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
             "			continue;        \n			}\n    "
             "  \n			lfnmutex_print(\"reload_so "
             "locking...\");\n			"
             "pthread_mutex_lock(&live_fn_mutex);\n			"
             "lfnmutex_print(\"reload_so locked\");\n        \n		"
             "	live_lib = 0; // hack: force skipping dlclose/1, the code may "
             "be still used...\n			"
             "load_so(new_so_name);\n			#ifndef "
             "_WIN32\n			unlink(new_so_name); // removing the "
             ".so file from the filesystem after dlopen-ing it is safe, since "
             "it will still be mapped in memory.\n			"
             "#else\n			_unlink(new_so_name);\n		"
             "	#endif\n			//if(0 == rename(new_so_name, "
             "\"%.*s\")){\n			//	load_so(\"%.*s\"); "
             "\n			//}\n\n			"
             "lfnmutex_print(\"reload_so unlocking...\");  \n		"
             "	pthread_mutex_unlock(&live_fn_mutex);  \n		"
             "	lfnmutex_print(\"reload_so unlocked\");\n\n		"
             "}\n		time__sleep_ms(100); \n	}\n}\n",
             file.len, file.str, file.len, file.str, file_base.len,
             file_base.str, vexe.len, vexe.str, msvc.len, msvc.str, file.len,
             file.str, file.len, file.str, so_name.len, so_name.str,
             so_name.len, so_name.str));
  };

  if (v->pref->is_so) {

    CGen_genln(cgen, tos2(" int load_so(byteptr path) { return 0; }"));
  };

  CGen_save(cgen);

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos2("flags="));

    println(array_string_str(v->table->flags));
  };

  V_cc(v);

  if (v->pref->is_test || v->pref->is_run) {

    if (1 || v->pref->is_verbose) {

      printf("============ running %.*s ============\n", v->out_name.len,
             v->out_name.str);
    };

    string cmd = (string_starts_with(v->out_name, tos2("/")))
                     ? (v->out_name)
                     : (string_add(tos2("./"), v->out_name));

#ifdef _WIN32

    cmd = v->out_name;

    cmd = string_replace(cmd, tos2("/"), tos2("\\"));

#endif
    ;

    if (os__args.len > 3) {

      cmd = string_add(
          cmd, string_add(tos2(" "), array_string_join(array_right(os__args, 3),
                                                       tos2(" "))));
    };

    int ret = os__system(cmd);

    if (ret != 0) {

      if (!v->pref->is_test) {

        string s = os__exec(cmd);

        println(s);

        println(tos2("failed to run the compiled program"));
      };

      v_exit(1);
    };
  };
}
void V_cc_windows_cross(V *c) {

  if (!string_ends_with(c->out_name, tos2(".exe"))) {

    c->out_name = string_add(c->out_name, tos2(".exe"));
  };

  string args = _STR("-o %.*s -w -L. ", c->out_name.len, c->out_name.str);

  array_string tmp34 = c->table->flags;
  ;
  for (int tmp35 = 0; tmp35 < tmp34.len; tmp35++) {
    string flag = ((string *)tmp34.data)[tmp35];

    if (!string_starts_with(flag, tos2("-l"))) {

      args = string_add(args, flag);

      args = string_add(args, tos2(" "));
    };
  };

  string libs = tos2("");

  if (c->pref->build_mode == main__BuildMode_default_mode) {

    libs =
        _STR("\"%.*s/vlib/builtin.o\"", main__ModPath.len, main__ModPath.str);

    if (!os__file_exists(libs)) {

      println(tos2("`builtin.o` not found"));

      v_exit(1);
    };

    array_string tmp37 = c->table->imports;
    ;
    for (int tmp38 = 0; tmp38 < tmp37.len; tmp38++) {
      string imp = ((string *)tmp37.data)[tmp38];

      libs = string_add(libs, _STR(" \"%.*s/vlib/%.*s.o\"", main__ModPath.len,
                                   main__ModPath.str, imp.len, imp.str));
    };
  };

  args = string_add(args, _STR(" %.*s ", c->out_name_c.len, c->out_name_c.str));

  array_string tmp39 = c->table->flags;
  ;
  for (int tmp40 = 0; tmp40 < tmp39.len; tmp40++) {
    string flag = ((string *)tmp39.data)[tmp40];

    if (string_starts_with(flag, tos2("-l"))) {

      args = string_add(args, flag);

      args = string_add(args, tos2(" "));
    };
  };

  println(tos2("Cross compiling for Windows..."));

  string winroot = _STR("%.*s/winroot", main__ModPath.len, main__ModPath.str);

  if (!os__dir_exists(winroot)) {

    string winroot_url = tos2(
        "https://github.com/vlang/v/releases/download/v0.1.10/winroot.zip");

    printf("\"%.*s\" not found. Download it from %.*s and save in %.*s\n",
           winroot.len, winroot.str, winroot_url.len, winroot_url.str,
           main__ModPath.len, main__ModPath.str);

    v_exit(1);
  };

  string obj_name = c->out_name;

  obj_name = string_replace(obj_name, tos2(".exe"), tos2(""));

  obj_name = string_replace(obj_name, tos2(".o.o"), tos2(".o"));

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

    println(tos2("Cross compilation for Windows failed. Make sure you have "
                 "clang installed."));

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

      println(tos2("Cross compilation for Windows failed. Make sure you have "
                   "lld linker installed."));

      v_exit(1);
    };
  };

  println(tos2("Done!"));
}
void V_cc(V *v) {

  if (v->os == main__OS_windows) {

#ifndef _WIN32

    V_cc_windows_cross(&/* ? */ *v);

    return;

#endif
    ;
  };

#ifdef _WIN32

  if (v->os == main__OS_msvc) {

    cc_msvc(v);

    return;
  };

#endif
  ;

  bool linux_host = string_eq(os__user_os(), tos2("linux"));

  V_log(&/* ? */ *v, _STR("cc() isprod=%d outname=%.*s", v->pref->is_prod,
                          v->out_name.len, v->out_name.str));

  array_string a = new_array_from_c_array(
      2, 2, sizeof(string), (string[]){v->pref->cflags, tos2("-w")});

  string flags = array_string_join(v->table->flags, tos2(" "));

  if (v->pref->is_so) {

    _PUSH(&a, (tos2("-shared -fPIC ")), tmp50, string);

    v->out_name = string_add(v->out_name, tos2(".so"));
  };

  if (v->pref->is_prod) {

    _PUSH(&a, (tos2("-O2")), tmp51, string);

  } else {

    _PUSH(&a, (tos2("-g")), tmp52, string);
  };

  if (v->pref->is_live || v->pref->is_so) {

    if ((v->os == main__OS_linux || string_eq(os__user_os(), tos2("linux")))) {

      _PUSH(&a, (tos2("-rdynamic")), tmp53, string);
    };

    if ((v->os == main__OS_mac || string_eq(os__user_os(), tos2("mac")))) {

      _PUSH(&a, (tos2("-flat_namespace")), tmp54, string);
    };
  };

  string libs = tos2("");

  if (v->pref->build_mode == main__BuildMode_build) {

    _PUSH(&a, (tos2("-c")), tmp56, string);

  } else if (v->pref->build_mode == main__BuildMode_embed_vlib) {

  } else if (v->pref->build_mode == main__BuildMode_default_mode) {

    libs =
        _STR("\"%.*s/vlib/builtin.o\"", main__ModPath.len, main__ModPath.str);

    if (!os__file_exists(libs)) {

      println(tos2("`builtin.o` not found"));

      v_exit(1);
    };

    array_string tmp57 = v->table->imports;
    ;
    for (int tmp58 = 0; tmp58 < tmp57.len; tmp58++) {
      string imp = ((string *)tmp57.data)[tmp58];

      if (string_eq(imp, tos2("webview"))) {

        continue;
      };

      libs = string_add(libs, _STR(" \"%.*s/vlib/%.*s.o\"", main__ModPath.len,
                                   main__ModPath.str, imp.len, imp.str));
    };
  };

  if (v->pref->sanitize) {

    _PUSH(&a, (tos2("-fsanitize=leak")), tmp59, string);
  };

  string sysroot = tos2("/Users/alex/tmp/lld/linuxroot/");

  if (v->os == main__OS_linux && !linux_host) {

    _PUSH(&a,
          (_STR("-c --sysroot=%.*s -target x86_64-linux-gnu", sysroot.len,
                sysroot.str)),
          tmp61, string);

    if (!string_ends_with(v->out_name, tos2(".o"))) {

      v->out_name = string_add(v->out_name, tos2(".o"));
    };
  };

  _PUSH(&a, (_STR("-o %.*s", v->out_name.len, v->out_name.str)), tmp62, string);

  _PUSH(&a, (_STR("\".%.*s\"", v->out_name_c.len, v->out_name_c.str)), tmp63,
        string);

  if (v->os == main__OS_mac) {

    _PUSH(&a, (tos2("-mmacosx-version-min=10.7")), tmp64, string);
  };

  _PUSH(&a, (flags), tmp65, string);

  _PUSH(&a, (libs), tmp66, string);

  if (v->os == main__OS_mac) {

    _PUSH(&a, (tos2("-x objective-c")), tmp67, string);
  };

  if (v->pref->build_mode != main__BuildMode_build &&
      (v->os == main__OS_linux || v->os == main__OS_freebsd ||
       v->os == main__OS_openbsd || v->os == main__OS_netbsd ||
       v->os == main__OS_dragonfly)) {

    _PUSH(&a, (tos2("-lm -lpthread ")), tmp68, string);

    if (v->os == main__OS_linux) {

      _PUSH(&a, (tos2(" -ldl ")), tmp69, string);
    };
  };

  if (v->os == main__OS_windows) {

    _PUSH(&a, (tos2("-DUNICODE -D_UNICODE")), tmp70, string);
  };

  string args = array_string_join(a, tos2(" "));

  string cmd = _STR("cc %.*s", args.len, args.str);

#ifdef _WIN32

  cmd = _STR("gcc %.*s", args.len, args.str);

#endif
  ;

  if (string_ends_with(v->out_name, tos2(".c"))) {

    os__mv(_STR(".%.*s", v->out_name_c.len, v->out_name_c.str), v->out_name);

    v_exit(0);
  };

  i64 ticks = time__ticks();

  string res = os__exec(cmd);

  i64 diff = time__ticks() - ticks;

  if (v->pref->show_c_cmd || v->pref->is_verbose) {

    println(tos2("\n=========="));

    println(cmd);

    printf("cc took %lld ms\n", diff);

    println(tos2("=========\n"));
  };

  if (string_contains(res, tos2("error: "))) {

    println(res);

    v_panic(tos2("clang error"));
  };

  if (v->os == main__OS_linux && !linux_host &&
      v->pref->build_mode != main__BuildMode_build) {

    v->out_name = string_replace(v->out_name, tos2(".o"), tos2(""));

    string obj_file = string_add(v->out_name, tos2(".o"));

    printf("linux obj_file=%.*s out_name=%.*s\n", obj_file.len, obj_file.str,
           v->out_name.len, v->out_name.str);

    string ress = os__exec(string_add(
        string_add(
            string_add(
                string_add(
                    string_add(
                        string_add(
                            string_add(
                                string_add(_STR("/usr/local/Cellar/llvm/8.0.0/"
                                                "bin/ld.lld --sysroot=%.*s ",
                                                sysroot.len, sysroot.str),
                                           _STR("-v -o %.*s ", v->out_name.len,
                                                v->out_name.str)),
                                tos2("-m elf_x86_64 -dynamic-linker "
                                     "/lib64/ld-linux-x86-64.so.2 ")),
                            tos2("/usr/lib/x86_64-linux-gnu/crt1.o ")),
                        _STR("%.*s/lib/x86_64-linux-gnu/libm-2.28.a ",
                             sysroot.len, sysroot.str)),
                    tos2("/usr/lib/x86_64-linux-gnu/crti.o ")),
                obj_file),
            tos2(" /usr/lib/x86_64-linux-gnu/libc.so ")),
        tos2("/usr/lib/x86_64-linux-gnu/crtn.o")));

    println(ress);

    if (string_contains(ress, tos2("error:"))) {

      v_exit(1);
    };

    printf("linux cross compilation done. resulting binary: \"%.*s\"\n",
           v->out_name.len, v->out_name.str);
  };

  if (!v->pref->is_debug && string_ne(v->out_name_c, tos2("v.c")) &&
      string_ne(v->out_name_c, tos2("v_macos.c"))) {

    os__rm(_STR(".%.*s", v->out_name_c.len, v->out_name_c.str));
  };
}
array_string V_v_files_from_dir(V *v, string dir) {

  array_string res = new_array_from_c_array(0, 0, sizeof(string),
                                            (string[]){EMPTY_STRUCT_INIT});

  if (!os__file_exists(dir)) {

    v_panic(_STR("%.*s doesn\'t exist", dir.len, dir.str));

  } else if (!os__dir_exists(dir)) {

    v_panic(_STR("%.*s isn\'t a directory", dir.len, dir.str));
  };

  array_string files = os__ls(dir);

  if (v->pref->is_verbose) {

    printf("v_files_from_dir (\"%.*s\")\n", dir.len, dir.str);
  };

  array_string_sort(&/* ? */ files);

  array_string tmp80 = files;
  ;
  for (int tmp81 = 0; tmp81 < tmp80.len; tmp81++) {
    string file = ((string *)tmp80.data)[tmp81];

    if (!string_ends_with(file, tos2(".v")) &&
        !string_ends_with(file, tos2(".vh"))) {

      continue;
    };

    if (string_ends_with(file, tos2("_test.v"))) {

      continue;
    };

    if (string_ends_with(file, tos2("_win.v")) &&
        (v->os != main__OS_windows && v->os != main__OS_msvc)) {

      continue;
    };

    if (string_ends_with(file, tos2("_lin.v")) && v->os != main__OS_linux) {

      continue;
    };

    if (string_ends_with(file, tos2("_mac.v")) && v->os != main__OS_mac) {

      continue;
    };

    if (string_ends_with(file, tos2("_nix.v")) &&
        (v->os == main__OS_windows || v->os == main__OS_msvc)) {

      continue;
    };

    _PUSH(&res, (_STR("%.*s/%.*s", dir.len, dir.str, file.len, file.str)),
          tmp82, string);
  };

  return res;
}
void V_add_user_v_files(V *v) {

  string dir = v->dir;

  V_log(&/* ? */ *v, _STR("add_v_files(%.*s)", dir.len, dir.str));

  array_string user_files = new_array_from_c_array(
      0, 0, sizeof(string), (string[]){EMPTY_STRUCT_INIT});

  bool is_test_with_imports = string_ends_with(dir, tos2("_test.v")) &&
                              (string_contains(dir, tos2("/volt")) ||
                               string_contains(dir, tos2("/c2volt")));

  if (is_test_with_imports) {

    _PUSH(&user_files, (dir), tmp86, string);

    int pos = string_last_index(dir, tos2("/"));

    dir = string_add(string_left(dir, pos), tos2("/"));
  };

  if (string_ends_with(dir, tos2(".v"))) {

    _PUSH(&user_files, (dir), tmp88, string);

    dir = string_all_before(dir, tos2("/"));

  } else {

    array_string files = V_v_files_from_dir(&/* ? */ *v, dir);

    array_string tmp90 = files;
    ;
    for (int tmp91 = 0; tmp91 < tmp90.len; tmp91++) {
      string file = ((string *)tmp90.data)[tmp91];

      _PUSH(&user_files, (file), tmp92, string);
    };
  };

  if (user_files.len == 0) {

    println(tos2("No input .v files"));

    v_exit(1);
  };

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos2("user_files:"));

    println(array_string_str(user_files));
  };

  array_FileImportTable file_imports = new_array_from_c_array(
      0, 0, sizeof(FileImportTable), (FileImportTable[]){EMPTY_STRUCT_INIT});

  array_string tmp94 = user_files;
  ;
  for (int tmp95 = 0; tmp95 < tmp94.len; tmp95++) {
    string file = ((string *)tmp94.data)[tmp95];

    Parser p = V_new_parser(v, file, main__Pass_imports);

    Parser_parse(&/* ? */ p);

    _PUSH(&file_imports, (*p.import_table), tmp97, FileImportTable);
  };

  if (v->pref->build_mode == main__BuildMode_default_mode) {

    for (int i = 0; i < v->table->imports.len; i++) {

      string pkg = V_module_path(&/* ? */ *v,
                                 (*(string *)array__get(v->table->imports, i)));

      array_string vfiles = V_v_files_from_dir(
          &/* ? */ *v, _STR("%.*s/vlib/%.*s", main__ModPath.len,
                            main__ModPath.str, pkg.len, pkg.str));

      array_string tmp103 = vfiles;
      ;
      for (int tmp104 = 0; tmp104 < tmp103.len; tmp104++) {
        string file = ((string *)tmp103.data)[tmp104];

        Parser p = V_new_parser(v, file, main__Pass_imports);

        Parser_parse(&/* ? */ p);

        _PUSH(&file_imports, (*p.import_table), tmp106, FileImportTable);
      };
    };

  } else {

    for (int i = 0; i < v->table->imports.len; i++) {

      string pkg = V_module_path(&/* ? */ *v,
                                 (*(string *)array__get(v->table->imports, i)));

      string idir = os__getwd();

      string import_path =
          _STR("%.*s/%.*s", idir.len, idir.str, pkg.len, pkg.str);

      if (!os__file_exists(import_path)) {

        import_path = _STR("%.*s/vlib/%.*s", v->lang_dir.len, v->lang_dir.str,
                           pkg.len, pkg.str);
      };

      array_string vfiles = V_v_files_from_dir(&/* ? */ *v, import_path);

      array_string tmp114 = vfiles;
      ;
      for (int tmp115 = 0; tmp115 < tmp114.len; tmp115++) {
        string file = ((string *)tmp114.data)[tmp115];

        Parser p = V_new_parser(v, file, main__Pass_imports);

        Parser_parse(&/* ? */ p);

        _PUSH(&file_imports, (*p.import_table), tmp117, FileImportTable);
      };
    };
  };

  if (v->pref->is_verbose) {

    V_log(&/* ? */ *v, tos2("imports:"));

    println(array_string_str(v->table->imports));
  };

  ModDepGraph *dep_graph = new_mod_dep_graph();

  ModDepGraph_from_import_tables(dep_graph, file_imports);

  ModDepGraph *deps_resolved = ModDepGraph_resolve(&/* ? */ *dep_graph);

  if (!deps_resolved->acyclic) {

    ModDepGraph_display(&/* ? */ *deps_resolved);

    v_panic(tos2("Import cycle detected."));
  };

  array_string tmp120 = ModDepGraph_imports(&/* ? */ *deps_resolved);
  ;
  for (int tmp121 = 0; tmp121 < tmp120.len; tmp121++) {
    string mod = ((string *)tmp120.data)[tmp121];

    string mod_p = V_module_path(&/* ? */ *v, mod);

    string idir = os__getwd();

    string module_path =
        _STR("%.*s/%.*s", idir.len, idir.str, mod_p.len, mod_p.str);

    if (v->pref->build_mode == main__BuildMode_default_mode ||
        v->pref->build_mode == main__BuildMode_build) {

      module_path = _STR("%.*s/vlib/%.*s", main__ModPath.len, main__ModPath.str,
                         mod_p.len, mod_p.str);
    };

    if (!os__file_exists(module_path)) {

      module_path = _STR("%.*s/vlib/%.*s", v->lang_dir.len, v->lang_dir.str,
                         mod_p.len, mod_p.str);
    };

    array_string vfiles = V_v_files_from_dir(&/* ? */ *v, module_path);

    array_string tmp126 = vfiles;
    ;
    for (int tmp127 = 0; tmp127 < tmp126.len; tmp127++) {
      string file = ((string *)tmp126.data)[tmp127];

      if (!_IN(string, file, v->files)) {

        _PUSH(&v->files, (file), tmp128, string);
      };
    };
  };

  array_FileImportTable tmp129 = file_imports;
  ;
  for (int tmp130 = 0; tmp130 < tmp129.len; tmp130++) {
    FileImportTable fit = ((FileImportTable *)tmp129.data)[tmp130];

    if (!_IN(string, fit.file_path, v->files)) {

      _PUSH(&v->files, (fit.file_path), tmp131, string);
    };
  };
}
string get_arg(string joined_args, string arg, string def) {

  string key = _STR("-%.*s ", arg.len, arg.str);

  int pos = string_index(joined_args, key);

  if (pos == -1) {

    return def;
  };

  pos += key.len;

  int space = string_index_after(joined_args, tos2(" "), pos);

  if (space == -1) {

    space = joined_args.len;
  };

  string res = string_substr(joined_args, pos, space);

  return res;
}
string V_module_path(V *v, string pkg) {

  if (string_contains(pkg, tos2("."))) {

    return string_replace(pkg, tos2("."), tos2("/"));
  };

  return pkg;
}
void V_log(V *v, string s) {

  if (!v->pref->is_verbose) {

    return;
  };

  println(s);
}
V *new_v(array_string args) {

  string dir = *(string *)array_last(args);

  if (array_string_contains(args, tos2("run"))) {

    dir = (*(string *)array__get(args, 2));
  };

  if (args.len < 2) {

    dir = tos2("");
  };

  string joined_args = array_string_join(args, tos2(" "));

  string target_os = get_arg(joined_args, tos2("os"), tos2(""));

  string out_name = get_arg(joined_args, tos2("o"), tos2("a.out"));

  BuildMode build_mode = main__BuildMode_default_mode;

  if (array_string_contains(args, tos2("-lib"))) {

    build_mode = main__BuildMode_build;

    string base = string_all_after(dir, tos2("/"));

    printf("Building module %.*s...\n", base.len, base.str);

    out_name = string_add(base, tos2(".o"));

  } else if (!array_string_contains(args, tos2("-embed_vlib"))) {

    build_mode = main__BuildMode_embed_vlib;
  };

  bool is_test = string_ends_with(dir, tos2("_test.v"));

  bool is_script = string_ends_with(dir, tos2(".v"));

  if (is_script && !os__file_exists(dir)) {

    printf("`%.*s` does not exist\n", dir.len, dir.str);

    v_exit(1);
  };

  if (string_eq(out_name, tos2("a.out")) && string_ends_with(dir, tos2(".v"))) {

    out_name = string_left(dir, dir.len - 2);
  };

  if (string_eq(dir, tos2(".")) && string_eq(out_name, tos2("a.out"))) {

    string base = string_all_after(os__getwd(), tos2("/"));

    out_name = string_trim_space(base);
  };

  OS _os = main__OS_mac;

  if (string_eq(target_os, tos2(""))) {

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

    if (string_eq(target_os, tos2("linux"))) { /* case */

      _os = main__OS_linux;

    } else if (string_eq(target_os, tos2("windows"))) { /* case */

      _os = main__OS_windows;

    } else if (string_eq(target_os, tos2("mac"))) { /* case */

      _os = main__OS_mac;

    } else if (string_eq(target_os, tos2("freebsd"))) { /* case */

      _os = main__OS_freebsd;

    } else if (string_eq(target_os, tos2("openbsd"))) { /* case */

      _os = main__OS_openbsd;

    } else if (string_eq(target_os, tos2("netbsd"))) { /* case */

      _os = main__OS_netbsd;

    } else if (string_eq(target_os, tos2("dragonfly"))) { /* case */

      _os = main__OS_dragonfly;

    } else if (string_eq(target_os, tos2("msvc"))) { /* case */

      _os = main__OS_msvc;
    };
  };

  array_string builtins = new_array_from_c_array(7, 7, sizeof(string),
                                                 (string[]){
                                                     tos2("array.v"),
                                                     tos2("string.v"),
                                                     tos2("builtin.v"),
                                                     tos2("int.v"),
                                                     tos2("utf8.v"),
                                                     tos2("map.v"),
                                                     tos2("option.v"),
                                                 });

  string vroot = os__dir(os__executable());

  if (os__dir_exists(vroot) &&
      os__dir_exists(string_add(vroot, tos2("/vlib/builtin")))) {

  } else {

    println(tos2("vlib not found. It should be next to the V executable. "));

    println(tos2("Go to https://vlang.io to install V."));

    v_exit(1);
  };

  string out_name_c =
      string_add(string_all_after(out_name, tos2("/")), tos2(".c"));

  array_string files = new_array_from_c_array(0, 0, sizeof(string),
                                              (string[]){EMPTY_STRUCT_INIT});

  if (!string_contains(out_name, tos2("builtin.o"))) {

    array_string tmp152 = builtins;
    ;
    for (int tmp153 = 0; tmp153 < tmp152.len; tmp153++) {
      string builtin = ((string *)tmp152.data)[tmp153];

      string f = _STR("%.*s/vlib/builtin/%.*s", vroot.len, vroot.str,
                      builtin.len, builtin.str);

      if (build_mode == main__BuildMode_default_mode ||
          build_mode == main__BuildMode_build) {
      };

      _PUSH(&files, (f), tmp155, string);
    };
  };

  string cflags = tos2("");

  array_string tmp157 = args;
  ;
  for (int ci = 0; ci < tmp157.len; ci++) {
    string cv = ((string *)tmp157.data)[ci];

    if (string_eq(cv, tos2("-cflags"))) {

      cflags = string_add(
          cflags, string_add((*(string *)array__get(args, ci + 1)), tos2(" ")));
    };
  };

  bool obfuscate = array_string_contains(args, tos2("-obf"));

  Preferences *pref = ALLOC_INIT(
      Preferences,
      {
          .is_test = is_test,
          .is_script = is_script,
          .is_so = array_string_contains(args, tos2("-shared")),
          .is_play = array_string_contains(args, tos2("play")),
          .is_prod = array_string_contains(args, tos2("-prod")),
          .is_verbose = array_string_contains(args, tos2("-verbose")),
          .is_debug = array_string_contains(args, tos2("-debug")),
          .obfuscate = obfuscate,
          .is_prof = array_string_contains(args, tos2("-prof")),
          .is_live = array_string_contains(args, tos2("-live")),
          .sanitize = array_string_contains(args, tos2("-sanitize")),
          .nofmt = array_string_contains(args, tos2("-nofmt")),
          .show_c_cmd = array_string_contains(args, tos2("-show_c_cmd")),
          .translated = array_string_contains(args, tos2("translated")),
          .is_run = array_string_contains(args, tos2("run")),
          .is_repl = array_string_contains(args, tos2("-repl")),
          .build_mode = build_mode,
          .cflags = cflags,
          .no_auto_free = 0,
      });

  if (pref->is_so) {

    out_name_c = string_add(string_all_after(out_name, tos2("/")),
                            tos2("_shared_lib.c"));
  };

  return ALLOC_INIT(V, {
                           .os = _os,
                           .out_name = out_name,
                           .files = files,
                           .dir = dir,
                           .lang_dir = vroot,
                           .table = new_table(obfuscate),
                           .out_name = out_name,
                           .out_name_c = out_name_c,
                           .cgen = new_cgen(out_name_c),
                           .vroot = vroot,
                           .pref = pref,
                       });
}
array_string run_repl() {

  printf("V %.*s\n", main__Version.len, main__Version.str);

  println(tos2("Use Ctrl-C or `exit` to exit"));

  string file = tos2(".vrepl.v");

  string temp_file = tos2(".vrepl_temp.v");

  /*
  {

  os__rm ( file ) ;

  os__rm ( temp_file ) ;

  }
  */

  array_string lines = new_array_from_c_array(0, 0, sizeof(string),
                                              (string[]){EMPTY_STRUCT_INIT});

  string vexe = (*(string *)array__get(os__args, 0));

  while (1) {

    v_print(tos2(">>> "));

    string line = os__get_raw_line();

    if (string_eq(string_trim_space(line), tos2("")) &&
        string_ends_with(line, tos2("\n"))) {

      continue;
    };

    line = string_trim_space(line);

    if (string_eq(line, tos2("")) || string_eq(line, tos2("exit"))) {

      break;
    };

    if (string_starts_with(line, tos2("print"))) {

      string source_code = string_add(
          string_add(array_string_join(lines, tos2("\n")), tos2("\n")), line);

      os__write_file(file, source_code);

      string s = os__exec(
          _STR("%.*s run %.*s -repl", vexe.len, vexe.str, file.len, file.str));

      array_string vals = string_split(s, tos2("\n"));

      if (string_contains(s, tos2("panic: "))) {

        if (!string_contains(s, tos2("declared and not used"))) {

          for (int i = 1; i < vals.len; i++) {

            println((*(string *)array__get(vals, i)));
          };

        } else {

          println(s);
        };

      } else {

        for (int i = 0; i < vals.len - 1; i++) {

          println((*(string *)array__get(vals, i)));
        };
      };

    } else {

      string temp_line = line;

      bool temp_flag = 0;

      if (!(string_contains(line, tos2(" ")) ||
            string_contains(line, tos2(":")) ||
            string_contains(line, tos2("=")) ||
            string_contains(line, tos2(",")))) {

        temp_line = _STR("println(%.*s)", line.len, line.str);

        temp_flag = 1;
      };

      string temp_source_code = string_add(
          string_add(array_string_join(lines, tos2("\n")), tos2("\n")),
          temp_line);

      os__write_file(temp_file, temp_source_code);

      string s = os__exec(_STR("%.*s run %.*s -repl", vexe.len, vexe.str,
                               temp_file.len, temp_file.str));

      if (string_contains(s, tos2("panic: "))) {

        if (!string_contains(s, tos2("declared and not used"))) {

          array_string vals = string_split(s, tos2("\n"));

          for (int i = 1; i < vals.len; i++) {

            println((*(string *)array__get(vals, i)));
          };

        } else {

          _PUSH(&lines, (line), tmp186, string);
        };

      } else {

        _PUSH(&lines, (line), tmp187, string);

        array_string vals = string_split(s, tos2("\n"));

        for (int i = 0; i < vals.len - 1; i++) {

          println((*(string *)array__get(vals, i)));
        };
      };
    };
  };

  array_string tmp192 = lines;
  {

    os__rm(file);

    os__rm(temp_file);
  }
  return tmp192;
  ;

  {

    os__rm(file);

    os__rm(temp_file);
  }
}
array_string env_vflags_and_os_args() {

  array_string args = new_array_from_c_array(0, 0, sizeof(string),
                                             (string[]){EMPTY_STRUCT_INIT});

  string vflags = os__getenv(tos2("VFLAGS"));

  if (string_ne(tos2(""), vflags)) {

    _PUSH(&args, ((*(string *)array__get(os__args, 0))), tmp195, string);

    _PUSH_MANY(&args, (string_split(vflags, tos2(" "))), tmp198, array_string);

    if (os__args.len > 1) {

      _PUSH_MANY(&args, (array_right(os__args, 1)), tmp199, array_string);
    };

  } else {

    _PUSH_MANY(&args, (os__args), tmp200, array_string);
  };

  return args;
}
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
ModDepGraph *new_mod_dep_graph() {

  return ALLOC_INIT(
      ModDepGraph,
      {.acyclic = 1, .nodes = new_array(0, 1, sizeof(ModDepGraphNode))});
}
void ModDepGraph_from_import_tables(ModDepGraph *graph,
                                    array_FileImportTable import_tables) {

  array_FileImportTable tmp6 = import_tables;
  ;
  for (int tmp7 = 0; tmp7 < tmp6.len; tmp7++) {
    FileImportTable fit = ((FileImportTable *)tmp6.data)[tmp7];

    array_string deps = new_array_from_c_array(0, 0, sizeof(string),
                                               (string[]){EMPTY_STRUCT_INIT});

    map_string tmp9 = fit.imports;
    array_string keys_tmp9 = map_keys(&tmp9);
    for (int l = 0; l < keys_tmp9.len; l++) {
      string _ = ((string *)keys_tmp9.data)[l];
      string m = {0};
      map_get(tmp9, _, &m);

      _PUSH(&deps, (m), tmp10, string);
    };

    ModDepGraph_add(graph, fit.module_name, deps);
  };
}
void ModDepGraph_add(ModDepGraph *graph, string mod, array_string deps) {

  _PUSH(
      &graph->nodes,
      ((ModDepGraphNode){.name = mod, .deps = deps, .last_cycle = tos("", 0)}),
      tmp11, ModDepGraphNode);
}
ModDepGraph *ModDepGraph_resolve(ModDepGraph *graph) {

  map_ModDepGraphNode node_names = new_map(1, sizeof(ModDepGraphNode));

  map_DepSet node_deps = new_map(1, sizeof(DepSet));

  array_ModDepGraphNode tmp14 = graph->nodes;
  ;
  for (int _ = 0; _ < tmp14.len; _++) {
    ModDepGraphNode node = ((ModDepGraphNode *)tmp14.data)[_];

    ModDepGraphNode tmp15 = node;

    map__set(&node_names, node.name, &tmp15);

    DepSet dep_set = (DepSet){.items = new_array(0, 1, sizeof(string))};

    array_string tmp17 = node.deps;
    ;
    for (int _ = 0; _ < tmp17.len; _++) {
      string dep = ((string *)tmp17.data)[_];

      DepSet_add(&/* ? */ dep_set, dep);
    };

    DepSet tmp18 = dep_set;

    map__set(&node_deps, node.name, &tmp18);
  };

  ModDepGraph *resolved = new_mod_dep_graph();

  while (node_deps.size != 0) {

    DepSet ready_set = (DepSet){.items = new_array(0, 1, sizeof(string))};

    map_DepSet tmp21 = node_deps;
    array_string keys_tmp21 = map_keys(&tmp21);
    for (int l = 0; l < keys_tmp21.len; l++) {
      string name = ((string *)keys_tmp21.data)[l];
      DepSet deps = {0};
      map_get(tmp21, name, &deps);

      if (DepSet_size(&/* ? */ deps) == 0) {

        DepSet_add(&/* ? */ ready_set, name);
      };
    };

    if (DepSet_size(&/* ? */ ready_set) == 0) {

      ModDepGraph *g = new_mod_dep_graph();

      g->acyclic = 0;

      array_string ndk = map_keys(&/* ? */ node_deps);

      map_DepSet tmp24 = node_deps;
      array_string keys_tmp24 = map_keys(&tmp24);
      for (int l = 0; l < keys_tmp24.len; l++) {
        string name = ((string *)keys_tmp24.data)[l];
        DepSet _ = {0};
        map_get(tmp24, name, &_);

        ModDepGraphNode tmp25 = {0};
        bool tmp26 = map_get(node_names, name, &tmp25);

        ModDepGraphNode node = tmp25;

        if (string_eq(name, (*(string *)array__get(ndk, node_deps.size - 1)))) {

          DepSet tmp30 = {0};
          bool tmp31 = map_get(node_deps, name, &tmp30);

          DepSet tmp32 = {0};
          bool tmp33 = map_get(node_deps, name, &tmp32);

          node.last_cycle =
              (*(string *)array__get(tmp30.items, tmp32.items.len - 1));
        };

        _PUSH(&g->nodes, (node), tmp36, ModDepGraphNode);
      };

      return g;
    };

    DepSet_size(&/* ? */ ready_set) > 0;

    {

      map_DepSet new_set = new_map(1, sizeof(DepSet));

      array_string tmp38 = ready_set.items;
      ;
      for (int tmp39 = 0; tmp39 < tmp38.len; tmp39++) {
        string name = ((string *)tmp38.data)[tmp39];

        ModDepGraphNode tmp41 = {0};
        bool tmp42 = map_get(node_names, name, &tmp41);

        _PUSH(&resolved->nodes, (tmp41), tmp40, ModDepGraphNode);
      };

      map_DepSet tmp43 = node_deps;
      array_string keys_tmp43 = map_keys(&tmp43);
      for (int l = 0; l < keys_tmp43.len; l++) {
        string k = ((string *)keys_tmp43.data)[l];
        DepSet d = {0};
        map_get(tmp43, k, &d);

        if (!_IN(string, k, ready_set.items)) {

          DepSet tmp44 = d;

          map__set(&new_set, k, &tmp44);
        };
      };

      node_deps = new_set;
    }

    map_DepSet tmp45 = node_deps;
    array_string keys_tmp45 = map_keys(&tmp45);
    for (int l = 0; l < keys_tmp45.len; l++) {
      string name = ((string *)keys_tmp45.data)[l];
      DepSet deps = {0};
      map_get(tmp45, name, &deps);

      DepSet tmp46 = DepSet_diff(&/* ? */ deps, ready_set);

      map__set(&node_deps, name, &tmp46);
    };
  };

  return resolved;
}
array_string ModDepGraph_imports(ModDepGraph *graph) {

  array_string mods = new_array_from_c_array(0, 0, sizeof(string),
                                             (string[]){EMPTY_STRUCT_INIT});

  array_ModDepGraphNode tmp48 = graph->nodes;
  ;
  for (int tmp49 = 0; tmp49 < tmp48.len; tmp49++) {
    ModDepGraphNode node = ((ModDepGraphNode *)tmp48.data)[tmp49];

    if (string_eq(node.name, tos2("main"))) {

      continue;
    };

    _PUSH(&mods, (node.name), tmp50, string);
  };

  return mods;
}
void ModDepGraph_last_node(ModDepGraph *graph) {

  return;

  (*(ModDepGraphNode *)array__get(graph->nodes, graph->nodes.len - 1));
}
void ModDepGraph_display(ModDepGraph *graph) {

  for (int i = 0; i < graph->nodes.len; i++) {

    ModDepGraphNode node = (*(ModDepGraphNode *)array__get(graph->nodes, i));

    array_string tmp57 = node.deps;
    ;
    for (int tmp58 = 0; tmp58 < tmp57.len; tmp58++) {
      string dep = ((string *)tmp57.data)[tmp58];

      string out = _STR(" * %.*s -> %.*s", node.name.len, node.name.str,
                        dep.len, dep.str);

      if (!graph->acyclic && i == graph->nodes.len - 1 &&
          string_eq(dep, node.last_cycle)) {

        out = string_add(out, tos2(" <-- last cycle"));
      };

      println(out);
    };
  };
}
void cc_msvc(V *v) {}
void build_thirdparty_obj_file_with_msvc(string flag) {}
Parser V_new_parser(V *c, string path, Pass run) {

  V_log(&/* ? */ *c, _STR("new_parser(\"%.*s\")", path.len, path.str));

  c->cgen->run = run;

  Parser p =
      (Parser){.file_path = path,
               .file_name = string_all_after(path, tos2("/")),
               .scanner = new_scanner(path),
               .table = c->table,
               .import_table = new_file_import_table(path),
               .cur_fn = main__EmptyFn,
               .cgen = c->cgen,
               .is_script = (c->pref->is_script && string_eq(path, c->dir)),
               .pref = c->pref,
               .os = c->os,
               .run = run,
               .vroot = c->vroot,
               .building_v = !c->pref->is_repl &&
                             (string_contains(path, tos2("compiler/")) ||
                              string_contains(path, tos2("v/vlib"))),
               .token_idx = 0,
               .lit = tos("", 0),
               .mod = tos("", 0),
               .inside_const = 0,
               .assigned_type = tos("", 0),
               .expected_type = tos("", 0),
               .tmp_cnt = 0,
               .builtin_pkg = 0,
               .vh_lines = new_array(0, 1, sizeof(string)),
               .inside_if_expr = 0,
               .is_struct_init = 0,
               .if_expr_cnt = 0,
               .for_expr_cnt = 0,
               .ptr_cast = 0,
               .calling_c = 0,
               .returns = 0,
               .is_c_struct_init = 0,
               .can_chash = 0,
               .attr = tos("", 0),
               .v_script = 0,
               .var_decl_name = tos("", 0),
               .is_alloc = 0};

  Parser_next(&/* ? */ p);

  return p;
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
void Parser_parse(Parser *p) {

  Parser_log(&/* ? */ *p, _STR("\nparse() run=%d file=%.*s tok=%.*s", p->run,
                               p->file_name.len, p->file_name.str,
                               Parser_strtok(&/* ? */ *p).len,
                               Parser_strtok(&/* ? */ *p).str));

  if (p->is_script || p->pref->is_test) {

    p->mod = tos2("main");

    if (p->tok == main__Token_key_module) {

      Parser_next(p);

      Parser_fgen(p, tos2("module "));

      p->mod = Parser_check_name(p);
    };

  } else {

    Parser_check(p, main__Token_key_module);

    Parser_fspace(p);

    p->mod = Parser_check_name(p);
  };

  Parser_fgenln(p, tos2("\n"));

  p->builtin_pkg = string_eq(p->mod, tos2("builtin"));

  p->can_chash =
      string_eq(p->mod, tos2("ft")) || string_eq(p->mod, tos2("http")) ||
      string_eq(p->mod, tos2("glfw")) || string_eq(p->mod, tos2("ui"));

  string fq_mod =
      Table_qualify_module(&/* ? */ *p->table, p->mod, p->file_path);

  p->import_table->module_name = fq_mod;

  Table_register_package(p->table, fq_mod);

  p->mod = string_replace(fq_mod, tos2("."), tos2("_dot_"));

  if (p->run == main__Pass_imports) {

    while (p->tok == main__Token_key_import &&
           Parser_peek(p) != main__Token_key_const) {

      Parser_imports(p);
    };

    if (array_string_contains(p->table->imports, tos2("builtin"))) {

      Parser_error(p, tos2("module `builtin` cannot be imported"));
    };

    return;
  };

  while (1) {

    if ((p->tok == main__Token_key_import)) { /* case */

      if (Parser_peek(p) == main__Token_key_const) {

        Parser_const_decl(p);

      } else {

        Parser_imports(p);

        if (p->tok != main__Token_key_import) {

          Parser_fgenln(p, tos2(""));
        };
      };

    } else if ((p->tok == main__Token_key_enum)) { /* case */

      Parser_next(p);

      if (p->tok == main__Token_name) {

        Parser_fgen(p, tos2("enum "));

        string name = Parser_check_name(p);

        Parser_fgen(p, tos2(" "));

        Parser_enum_decl(p, name);

      } else if (p->pref->translated) {

        Parser_enum_decl(p, tos2("int"));

      } else {

        Parser_check(p, main__Token_name);
      };

    } else if ((p->tok == main__Token_key_pub)) { /* case */

      if (Parser_peek(p) == main__Token_func) {

        Parser_fn_decl(p);

      } else if (Parser_peek(p) == main__Token_key_struct) {

        Parser_error(p, tos2("structs can\'t be declared public *yet*"));

      } else {

        Parser_error(p, tos2("wrong pub keyword usage"));
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

      if (!p->pref->translated && !p->pref->is_live && !p->builtin_pkg &&
          !p->building_v) {

        Parser_error(p, tos2("__global is only allowed in translated code"));
      };

      Parser_next(p);

      string name = Parser_check_name(p);

      string typ = Parser_get_type(p);

      Parser_register_global(p, name, typ);

      string g = Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ);

      if (p->tok == main__Token_assign) {

        Parser_next(p);

        g = string_add(g, tos2(" = "));

        CGen_start_tmp(p->cgen);

        Parser_bool_expression(p);

        g = string_add(g, CGen_end_tmp(p->cgen));
      };

      g = string_add(g, tos2("; // global"));

      _PUSH(&p->cgen->consts, (g), tmp8, string);

    } else if ((p->tok == main__Token_eof)) { /* case */

      Parser_log(&/* ? */ *p, tos2("end of parse()"));

      if (p->is_script && !p->pref->is_test) {

        p->cur_fn = main__MainFn;

        Parser_check_unused_variables(p);
      };

      if (0 && !Parser_first_run(&/* ? */ *p) &&
          Parser_fileis(&/* ? */ *p, tos2("main.v"))) {

        Option_os__File tmp9 = os__create(tos2("/var/tmp/fmt.v"));
        if (!tmp9.ok) {
          string err = tmp9.error;

          v_panic(tos2("failed to create fmt.v"));

          return;
        }
        os__File out = *(os__File *)tmp9.data;
        ;

        os__File_writeln(out, strings__Builder_str(p->scanner->fmt_out));

        os__File_close(out);
      };

      return;

    } else { // default:

      if (p->is_script && !p->pref->is_test) {

        if (Parser_first_run(&/* ? */ *p)) {

          if (string_eq(p->cur_fn->name, tos2(""))) {

            p->cur_fn = main__MainFn;
          };

          return;
        };

        if (string_eq(p->cur_fn->name, tos2(""))) {

          p->cur_fn = main__MainFn;

          if (p->pref->is_repl) {

            Fn_clear_vars(p->cur_fn);
          };
        };

        int start = p->cgen->lines.len;

        Parser_statement(p, 1);

        if (string_ne((*(string *)array__get(p->cgen->lines, start - 1)),
                      tos2("")) &&
            string_ne(p->cgen->fn_main, tos2(""))) {

          start--;
        };

        Parser_genln(p, tos2(""));

        int end = p->cgen->lines.len;

        array_string lines = array_slice(p->cgen->lines, start, end);

        p->cgen->fn_main =
            string_add(p->cgen->fn_main, array_string_join(lines, tos2("\n")));

        CGen_resetln(p->cgen, tos2(""));

        for (int i = start; i < end; i++) {

          string tmp16 = tos2("");

          array_set(&/*q*/ p->cgen->lines, i, &tmp16);
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

      Parser_register_import(p);
    };

    Parser_check(p, main__Token_rpar);

    return;
  };

  Parser_register_import(p);
}
void Parser_register_import(Parser *p) {

  if (p->tok != main__Token_name) {

    Parser_error(p, tos2("bad import format"));
  };

  string pkg = string_trim_space(p->lit);

  string mod_alias = pkg;

  int depth = 1;

  Parser_next(p);

  while (p->tok == main__Token_dot) {

    Parser_check(p, main__Token_dot);

    string submodule = Parser_check_name(p);

    mod_alias = submodule;

    pkg = string_add(pkg, string_add(tos2("."), submodule));

    depth++;

    if (depth > main__MaxModuleDepth) {

      Parser_error(p, _STR("module depth of %d exceeded: %.*s",
                           main__MaxModuleDepth, pkg.len, pkg.str));
    };
  };

  if (p->tok == main__Token_key_as && Parser_peek(p) == main__Token_name) {

    Parser_check(p, main__Token_key_as);

    mod_alias = Parser_check_name(p);
  };

  FileImportTable_register_alias(p->import_table, mod_alias, pkg);

  if (array_string_contains(p->table->imports, pkg)) {

    return;
  };

  Parser_log(&/* ? */ *p, _STR("adding import %.*s", pkg.len, pkg.str));

  _PUSH(&p->table->imports, (pkg), tmp21, string);

  Table_register_package(p->table, pkg);

  Parser_fgenln(p, string_add(tos2(" "), pkg));
}
void Parser_const_decl(Parser *p) {

  bool is_import = p->tok == main__Token_key_import;

  p->inside_const = 1;

  if (is_import) {

    Parser_next(p);
  };

  Parser_check(p, main__Token_key_const);

  Parser_fspace(p);

  Parser_check(p, main__Token_lpar);

  Parser_fgenln(p, tos2(""));

  Parser_fmt_inc(p);

  while (p->tok == main__Token_name) {

    string name = Parser_check_name(p);

    if (p->pref->is_play &&
        !(string_at(name, 0) >= 'A' && string_at(name, 0) <= 'Z')) {

      Parser_error(p, tos2("const name must be capitalized"));
    };

    if (!is_import) {

      name = Parser_prepend_pkg(&/* ? */ *p, name);
    };

    string typ = tos2("int");

    if (!is_import) {

      Parser_check_space(p, main__Token_assign);

      typ = Parser_expression(p);
    };

    if (Parser_first_run(&/* ? */ *p) && !is_import &&
        Table_known_const(&/* ? */ *p->table, name)) {

      Parser_error(p, _STR("redefinition of `%.*s`", name.len, name.str));
    };

    Table_register_const(p->table, name, typ, p->mod, is_import);

    if (p->run == main__Pass_main && !is_import) {

      if (is_compile_time_const(p->cgen->cur_line)) {

        _PUSH(&p->cgen->consts,
              (_STR("#define %.*s %.*s", name.len, name.str,
                    p->cgen->cur_line.len, p->cgen->cur_line.str)),
              tmp29, string);

        CGen_resetln(p->cgen, tos2(""));

        Parser_fgenln(p, tos2(""));

        continue;
      };

      if (string_starts_with(typ, tos2("["))) {

        _PUSH(&p->cgen->consts,
              (string_add(
                  Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ),
                  _STR(" = %.*s;", p->cgen->cur_line.len,
                       p->cgen->cur_line.str))),
              tmp30, string);

      } else {

        _PUSH(&p->cgen->consts,
              (string_add(
                  Table_cgen_name_type_pair(&/* ? */ *p->table, name, typ),
                  tos2(";"))),
              tmp31, string);

        _PUSH(&p->cgen->consts_init,
              (_STR("%.*s = %.*s;", name.len, name.str, p->cgen->cur_line.len,
                    p->cgen->cur_line.str)),
              tmp32, string);
      };

      CGen_resetln(p->cgen, tos2(""));
    };

    Parser_fgenln(p, tos2(""));
  };

  Parser_fmt_dec(p);

  Parser_check(p, main__Token_rpar);

  Parser_fgenln(p, tos2("\n"));

  p->inside_const = 0;
}
void Parser_type_decl(Parser *p) {

  Parser_check(p, main__Token_key_type);

  string name = Parser_check_name(p);

  string parent = Parser_get_type(p);

  string nt_pair = Table_cgen_name_type_pair(&/* ? */ *p->table, name, parent);

  string _struct = (!string_contains(parent, tos2("[")) &&
                    !string_starts_with(parent, tos2("fn ")) &&
                    !Table_known_type(&/* ? */ *p->table, parent))
                       ? (tos2("struct"))
                       : (tos2(""));

  Parser_gen_typedef(
      p, _STR("typedef %.*s %.*s; // type alias name=\"%.*s\" parent=\"%.*s\"",
              _struct.len, _struct.str, nt_pair.len, nt_pair.str, name.len,
              name.str, parent.len, parent.str));

  Parser_register_type_with_parent(p, name, parent);
}
Fn *Parser_interface_method(Parser *p, string field_name, string receiver) {

  Fn *method = ALLOC_INIT(Fn, {.name = field_name,
                               .is_interface = 1,
                               .is_method = 1,
                               .receiver_typ = receiver,
                               .pkg = tos("", 0),
                               .local_vars = new_array(0, 1, sizeof(Var)),
                               .var_idx = 0,
                               .args = new_array(0, 1, sizeof(Var)),
                               .scope_level = 0,
                               .typ = tos("", 0),
                               .is_c = 0,
                               .is_public = 0,
                               .returns_error = 0,
                               .is_decl = 0,
                               .defer_text = tos("", 0)});

  Parser_log(&/* ? */ *p, _STR("is interface. field=%.*s run=%d",
                               field_name.len, field_name.str, p->run));

  Parser_fn_args(p, method);

  if (Scanner_has_gone_over_line_end(*p->scanner)) {

    method->typ = tos2("void");

  } else {

    method->typ = Parser_get_type(p);

    Parser_fspace(p);

    Parser_fgenln(p, tos2(""));
  };

  return method;
}
void Parser_struct_decl(Parser *p) {

  string objc_parent = tos2("");

  bool is_objc = 0;

  if (p->tok == main__Token_lsbr) {

    Parser_check(p, main__Token_lsbr);

    is_objc = p->tok == main__Token_key_interface;

    Parser_next(p);

    if (is_objc) {

      Parser_check(p, main__Token_colon);

      objc_parent = Parser_check_name(p);
    };

    Parser_check(p, main__Token_rsbr);
  };

  bool is_interface = p->tok == main__Token_key_interface;

  bool is_union = p->tok == main__Token_key_union;

  bool is_struct = p->tok == main__Token_key_struct;

  Parser_fgen(p, string_add(Token_str(p->tok), tos2(" ")));

  Parser_next(p);

  string name = Parser_check_name(p);

  if (string_contains(name, tos2("_")) && !p->pref->translated) {

    Parser_error(p, tos2("type names cannot contain `_`"));
  };

  if (is_interface && !string_ends_with(name, tos2("er"))) {

    Parser_error(p, tos2("interface names temporarily have to end with `er` "
                         "(e.g. `Speaker`, `Reader`)"));
  };

  bool is_c = string_eq(name, tos2("C")) && p->tok == main__Token_dot;

  if (is_c) {

    Parser_check(p, main__Token_dot);

    name = Parser_check_name(p);
  };

  if (!is_c && !p->builtin_pkg && string_ne(p->mod, tos2("main"))) {

    name = Parser_prepend_pkg(&/* ? */ *p, name);
  };

  if (p->run == main__Pass_decl && Table_known_type(&/* ? */ *p->table, name)) {

    Parser_error(p, _STR("`%.*s` redeclared", name.len, name.str));
  };

  if (is_objc) {

    Parser_gen_type(p, _STR("@interface %.*s : %.*s { @public", name.len,
                            name.str, objc_parent.len, objc_parent.str));

  } else {

    if (!is_c) {

      string kind = (is_union) ? (tos2("union")) : (tos2("struct"));

      Parser_gen_typedef(p, _STR("typedef %.*s %.*s %.*s;", kind.len, kind.str,
                                 name.len, name.str, name.len, name.str));

      Parser_gen_type(
          p, _STR("%.*s %.*s {", kind.len, kind.str, name.len, name.str));
    };
  };

  if (!is_c && p->tok == main__Token_key_struct) {

    Parser_error(p, _STR("use `struct %.*s {` instead of `type %.*s struct {`",
                         name.len, name.str, name.len, name.str));
  };

  Type *typ = Table_find_type(&/* ? */ *p->table, name);

  bool is_ph = 0;

  if (typ->is_placeholder) {

    is_ph = 1;

    typ->name = name;

    typ->mod = p->mod;

    typ->is_c = is_c;

    typ->is_placeholder = 0;

  } else {

    typ = ALLOC_INIT(Type, {.name = name,
                            .mod = p->mod,
                            .is_c = is_c,
                            .is_interface = is_interface,
                            .fields = new_array(0, 1, sizeof(Var)),
                            .methods = new_array(0, 1, sizeof(Fn)),
                            .parent = tos("", 0),
                            .is_enum = 0,
                            .enum_vals = new_array(0, 1, sizeof(string)),
                            .is_placeholder = 0});
  };

  if (is_c && is_struct && p->tok != main__Token_lcbr) {

    Table_register_type2(p->table, *typ);

    return;
  };

  Parser_fgen(p, tos2(" "));

  Parser_check(p, main__Token_lcbr);

  bool is_pub = 0;

  bool is_mut = 0;

  array_string names = new_array_from_c_array(0, 0, sizeof(string),
                                              (string[]){EMPTY_STRUCT_INIT});

  bool did_gen_something = 0;

  while (p->tok != main__Token_rcbr) {

    if (p->tok == main__Token_key_pub) {

      if (is_pub) {

        Parser_error(p, tos2("structs can only have one `pub:`, all public "
                             "fields have to be grouped"));
      };

      is_pub = 1;

      Parser_fmt_dec(p);

      Parser_check(p, main__Token_key_pub);

      if (p->tok != main__Token_key_mut) {

        Parser_check(p, main__Token_colon);
      };

      Parser_fmt_inc(p);

      Parser_fgenln(p, tos2(""));
    };

    if (p->tok == main__Token_key_mut) {

      if (is_mut) {

        Parser_error(p, tos2("structs can only have one `mut:`, all private "
                             "key_mut fields have to be grouped"));
      };

      is_mut = 1;

      Parser_fmt_dec(p);

      Parser_check(p, main__Token_key_mut);

      if (p->tok != main__Token_key_mut) {

        Parser_check(p, main__Token_colon);
      };

      Parser_fmt_inc(p);

      Parser_fgenln(p, tos2(""));
    };

    string field_name = Parser_check_name(p);

    if (_IN(string, field_name, names)) {

      Parser_error(
          p, _STR("duplicate field `%.*s`", field_name.len, field_name.str));
    };

    _PUSH(&names, (field_name), tmp53, string);

    if (is_interface) {

      Type_add_method(typ, *Parser_interface_method(p, field_name, name));

      continue;
    };

    AccessMod access_mod =
        (is_pub) ? (main__AccessMod_public) : (main__AccessMod_private);

    Parser_fgen(p, tos2(" "));

    string field_type = Parser_get_type(p);

    bool is_atomic = p->tok == main__Token_key_atomic;

    if (is_atomic) {

      Parser_next(p);

      Parser_gen_type(p, tos2("_Atomic "));
    };

    if (!is_c) {

      Parser_gen_type(
          p, string_add(Table_cgen_name_type_pair(&/* ? */ *p->table,
                                                  field_name, field_type),
                        tos2(";")));
    };

    string attr = tos2("");

    if (p->tok == main__Token_lsbr) {

      Parser_next(p);

      attr = Parser_check_name(p);

      Parser_check(p, main__Token_rsbr);
    };

    did_gen_something = 1;

    Type_add_field(typ, field_name, field_type, is_mut, attr, access_mod);

    Parser_fgenln(p, tos2(""));
  };

  if (!is_ph && Parser_first_run(&/* ? */ *p)) {

    Table_register_type2(p->table, *typ);
  };

  Parser_check(p, main__Token_rcbr);

  if (!is_c) {

    if (!did_gen_something) {

      Parser_gen_type(p, tos2("EMPTY_STRUCT_DECLARATION };"));

      Parser_fgenln(p, tos2(""));

    } else {

      Parser_gen_type(p, tos2("}; "));
    };
  };

  if (is_objc) {

    Parser_gen_type(p, tos2("@end"));
  };

  Parser_fgenln(p, tos2("\n"));
}
void Parser_enum_decl(Parser *p, string _enum_name) {

  string enum_name = _enum_name;

  if (!p->builtin_pkg && string_ne(p->mod, tos2("main"))) {

    enum_name = Parser_prepend_pkg(&/* ? */ *p, enum_name);
  };

  if (string_ne(enum_name, tos2("int"))) {

    _PUSH(&p->cgen->typedefs,
          (_STR("typedef int %.*s;", enum_name.len, enum_name.str)), tmp59,
          string);
  };

  Parser_check(p, main__Token_lcbr);

  int val = 0;

  array_string fields = new_array_from_c_array(0, 0, sizeof(string),
                                               (string[]){EMPTY_STRUCT_INIT});

  while (p->tok == main__Token_name) {

    string field = Parser_check_name(p);

    _PUSH(&fields, (field), tmp63, string);

    Parser_fgenln(p, tos2(""));

    string name = _STR("%.*s__%.*s_%.*s", p->mod.len, p->mod.str, enum_name.len,
                       enum_name.str, field.len, field.str);

    if (p->run == main__Pass_main) {

      _PUSH(&p->cgen->consts,
            (_STR("#define %.*s %d", name.len, name.str, val)), tmp65, string);
    };

    if (p->tok == main__Token_comma) {

      Parser_next(p);
    };

    Table_register_const(p->table, name, enum_name, p->mod, 0);

    val++;
  };

  Table_register_type2(
      p->table, *ALLOC_INIT(Type, {.name = enum_name,
                                   .mod = p->mod,
                                   .parent = tos2("int"),
                                   .is_enum = 1,
                                   .enum_vals = fields,
                                   .fields = new_array(0, 1, sizeof(Var)),
                                   .methods = new_array(0, 1, sizeof(Fn)),
                                   .is_c = 0,
                                   .is_interface = 0,
                                   .is_placeholder = 0}));

  Parser_check(p, main__Token_rcbr);

  Parser_fgenln(p, tos2("\n"));
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

  if (string_eq(res, tos2(""))) {

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

    println(tos2("check()"));

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
      string_at(p->scanner->text, p->scanner->pos + 1) != '}') {

    Parser_fgenln(p, tos2(""));

    Parser_fmt_inc(p);
  };

  Parser_next(p);

  if (string_ne(p->scanner->line_comment, tos2(""))) {
  };
}
void Parser_error(Parser *p, string s) {

  if (0) {
  };

  if (p->pref->is_verbose) {

    printf("pass=%d fn=`%.*s`\n", p->run, p->cur_fn->name.len,
           p->cur_fn->name.str);
  };

  CGen_save(p->cgen);

  string cur_path = os__getwd();

  if (!p->pref->is_repl && (string_contains(p->file_path, tos2("v/compiler")) ||
                            string_contains(cur_path, tos2("v/compiler")))) {

    println(tos2("\n========================="));

    println(tos2("It looks like you are building V. It is being frequently "
                 "updated every day."));

    println(tos2("If you didn\'t modify the compiler\'s code, most likely "
                 "there was a change that "));

    println(tos2("lead to this error."));

    println(tos2("\nRun `git pull && make`, that will most likely fix it."));

    println(tos2("\nIf this doesn\'t help, please create a GitHub issue."));

    println(tos2("=========================\n"));
  };

  Scanner_error(&/* ? */ *p->scanner,
                string_replace(string_replace(string_replace(s, tos2("array_"),
                                                             tos2("[]")),
                                              tos2("__"), tos2(".")),
                               tos2("Option_"), tos2("?")));
}
bool Parser_first_run(Parser *p) { return p->run == main__Pass_decl; }
string Parser_get_type(Parser *p) {

  bool debug = Parser_fileis(&/* ? */ *p, tos2("fn_test")) && 0;

  bool mul = 0;

  int nr_muls = 0;

  string typ = tos2("");

  if (p->tok == main__Token_func) {

    if (debug) {

      printf("\nget_type() .key_goT FN TYP line=%d\n", p->scanner->line_nr);
    };

    Fn f = (Fn){.name = tos2("_"),
                .pkg = p->mod,
                .local_vars = new_array(0, 1, sizeof(Var)),
                .var_idx = 0,
                .args = new_array(0, 1, sizeof(Var)),
                .is_interface = 0,
                .scope_level = 0,
                .typ = tos("", 0),
                .is_c = 0,
                .receiver_typ = tos("", 0),
                .is_public = 0,
                .is_method = 0,
                .returns_error = 0,
                .is_decl = 0,
                .defer_text = tos("", 0)};

    Parser_next(p);

    int line_nr = p->scanner->line_nr;

    Parser_fn_args(p, &/*11 EXP:"Fn*" GOT:"Fn" */ f);

    if (p->scanner->line_nr == line_nr) {

      if (debug) {

        println(tos2("same line getting type"));
      };

      if (p->tok == main__Token_name) {

        f.typ = Parser_get_type(p);

      } else {

        f.typ = tos2("void");
      };

    } else {

      f.typ = tos2("void");
    };

    Type fn_typ = (Type){.name = Fn_typ_str(f),
                         .mod = p->mod,
                         .func = f,
                         .fields = new_array(0, 1, sizeof(Var)),
                         .methods = new_array(0, 1, sizeof(Fn)),
                         .parent = tos("", 0),
                         .is_c = 0,
                         .is_interface = 0,
                         .is_enum = 0,
                         .enum_vals = new_array(0, 1, sizeof(string)),
                         .is_placeholder = 0};

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

  if (!p->builtin_pkg && p->tok == main__Token_name &&
      string_eq(p->lit, tos2("map"))) {

    Parser_next(p);

    Parser_check(p, main__Token_lsbr);

    string key_type = Parser_check_name(p);

    if (string_ne(key_type, tos2("string"))) {

      Parser_error(p, tos2("maps only support string keys for now"));
    };

    Parser_check(p, main__Token_rsbr);

    string val_type = Parser_check_name(p);

    typ = _STR("map_%.*s", val_type.len, val_type.str);

    Parser_register_map(p, typ);

    return typ;
  };

  while (p->tok == main__Token_mul) {

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

  if (string_eq(p->lit, tos2("C")) && Parser_peek(p) == main__Token_dot) {

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    typ = p->lit;

  } else {

    if (Parser_peek(p) == main__Token_dot) {

      Parser_next(p);

      Parser_check(p, main__Token_dot);

      typ = string_add(typ, _STR("__%.*s", p->lit.len, p->lit.str));
    };

    Type *t = Table_find_type(&/* ? */ *p->table, typ);

    if (string_eq(t->name, tos2("")) && !p->builtin_pkg) {

      if (!string_contains(typ, tos2("array_")) &&
          string_ne(p->mod, tos2("main")) &&
          !string_contains(typ, tos2("__")) &&
          !string_starts_with(typ, tos2("["))) {

        typ = Parser_prepend_pkg(&/* ? */ *p, typ);
      };

      t = Table_find_type(&/* ? */ *p->table, typ);

      if (string_eq(t->name, tos2("")) && !p->pref->translated &&
          !Parser_first_run(&/* ? */ *p) &&
          !string_starts_with(typ, tos2("["))) {

        println(tos2("get_type() bad type"));

        Parser_error(p, _STR("unknown type `%.*s`", typ.len, typ.str));
      };
    };
  };

  if (string_eq(typ, tos2("void"))) {

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

    Table_register_type_with_parent(p->table, typ, tos2("Option"));

    if (p->tok == main__Token_question) {

      Parser_next(p);
    };
  };

  if (string_eq(typ, tos2("byteptr"))) {

    return tos2("byte*");
  };

  if (string_eq(typ, tos2("voidptr"))) {

    return tos2("void*");
  };

  if (string_last_index(typ, tos2("__")) > string_index(typ, tos2("__"))) {

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

  Parser_log(&/* ? */ *p, tos2("statements()"));

  string typ = Parser_statements_no_rcbr(p);

  if (!p->inside_if_expr) {

    Parser_genln(p, tos2("}"));
  };

  return typ;
}
string Parser_statements_no_rcbr(Parser *p) {

  Fn_open_scope(p->cur_fn);

  if (!p->inside_if_expr) {

    Parser_genln(p, tos2(""));
  };

  int i = 0;

  string last_st_typ = tos2("");

  while (p->tok != main__Token_rcbr && p->tok != main__Token_eof &&
         p->tok != main__Token_key_case && p->tok != main__Token_key_default &&
         Parser_peek(p) != main__Token_arrow) {

    last_st_typ = Parser_statement(p, 1);

    if (!p->inside_if_expr) {

      Parser_genln(p, tos2(""));

      Parser_fgenln(p, tos2(""));
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

    if (!p->building_v && !v.is_mut && v.is_alloc) {

      if (string_starts_with(v.typ, tos2("array_"))) {

        Parser_genln(p, _STR("v_array_free(%.*s); // close_scope free",
                             v.name.len, v.name.str));

      } else {

        Parser_genln(
            p, _STR("free(%.*s); // close_scope free", v.name.len, v.name.str));
      };
    };
  };

  p->cur_fn->var_idx = i + 1;

  p->cur_fn->scope_level--;
}
void Parser_genln(Parser *p, string s) { CGen_genln(p->cgen, s); }
void Parser_gen(Parser *p, string s) { CGen_gen(p->cgen, s); }
void Parser_vh_genln(Parser *p, string s) {

  _PUSH(&p->vh_lines, (s), tmp94, string);
}
void Parser_fmt_inc(Parser *p) { p->scanner->fmt_indent++; }
void Parser_fmt_dec(Parser *p) { p->scanner->fmt_indent--; }
string Parser_statement(Parser *p, bool add_semi) {

  p->cgen->is_tmp = 0;

  Token tok = p->tok;

  string q = tos2("");

  if ((tok == main__Token_name)) { /* case */

    Token next = Parser_peek(p);

    if (p->pref->is_verbose) {

      println(Token_str(next));
    };

    if (Parser_peek(p) == main__Token_colon) {

      Parser_fmt_dec(p);

      string label = Parser_check_name(p);

      Parser_fmt_inc(p);

      Parser_genln(p, string_add(label, tos2(":")));

      Parser_check(p, main__Token_colon);

      return tos2("");

    } else if (Parser_peek(p) == main__Token_decl_assign) {

      Parser_log(&/* ? */ *p, tos2("var decl"));

      Parser_var_decl(p);

    } else if (string_eq(p->lit, tos2("jsdecode"))) {

      Parser_js_decode(p);

    } else {

      q = Parser_bool_expression(p);
    };

  } else if ((tok == main__Token_key_goto)) { /* case */

    Parser_check(p, main__Token_key_goto);

    Parser_fgen(p, tos2(" "));

    string label = Parser_check_name(p);

    Parser_genln(p, _STR("goto %.*s;", label.len, label.str));

    return tos2("");

  } else if ((tok == main__Token_key_defer)) { /* case */

    Parser_defer_st(p);

    return tos2("");

  } else if ((tok == main__Token_hash)) { /* case */

    Parser_chash(p);

    return tos2("");

  } else if ((tok == main__Token_dollar)) { /* case */

    Parser_comp_time(p);

  } else if ((tok == main__Token_key_if)) { /* case */

    Parser_if_st(p, 0, 0);

  } else if ((tok == main__Token_key_for)) { /* case */

    Parser_for_st(p);

  } else if ((tok == main__Token_key_switch) ||
             (tok == main__Token_key_match)) { /* case */

    Parser_switch_statement(p);

  } else if ((tok == main__Token_key_mut) ||
             (tok == main__Token_key_static)) { /* case */

    Parser_var_decl(p);

  } else if ((tok == main__Token_key_return)) { /* case */

    Parser_return_st(p);

  } else if ((tok == main__Token_lcbr)) { /* case */

    Parser_check(p, main__Token_lcbr);

    Parser_genln(p, tos2("{"));

    Parser_statements(p);

    return tos2("");

  } else if ((tok == main__Token_key_continue)) { /* case */

    if (p->for_expr_cnt == 0) {

      Parser_error(p, tos2("`continue` statement outside `for`"));
    };

    Parser_genln(p, tos2("continue"));

    Parser_check(p, main__Token_key_continue);

  } else if ((tok == main__Token_key_break)) { /* case */

    if (p->for_expr_cnt == 0) {

      Parser_error(p, tos2("`break` statement outside `for`"));
    };

    Parser_genln(p, tos2("break"));

    Parser_check(p, main__Token_key_break);

  } else if ((tok == main__Token_key_go)) { /* case */

    Parser_go_statement(p);

  } else if ((tok == main__Token_key_assert)) { /* case */

    Parser_assert_statement(p);

  } else { // default:

    string typ = Parser_expression(p);

    if (p->inside_if_expr) {

    } else {

      Parser_genln(p, tos2("; "));
    };

    return typ;
  };

  if (p->inside_if_expr && p->tok != main__Token_rcbr) {

    Parser_gen(p, tos2(", "));
  };

  if (add_semi && !p->inside_if_expr) {

    Parser_genln(p, tos2(";"));
  };

  return q;
}
void Parser_assign_statement(Parser *p, Var v, int ph, bool is_map) {

  Parser_log(&/* ? */ *p,
             _STR("assign_statement() name=%.*s tok=", v.name.len, v.name.str));

  Token tok = p->tok;

  if (!v.is_mut && !v.is_arg && !p->pref->translated && !v.is_global) {

    Parser_error(p, _STR("`%.*s` is immutable", v.name.len, v.name.str));
  };

  bool is_str = string_eq(v.typ, tos2("string"));

  if ((tok == main__Token_assign)) { /* case */

    if (!is_map) {

      Parser_gen(p, tos2(" = "));
    };

  } else if ((tok == main__Token_plus_assign)) { /* case */

    if (is_str) {

      Parser_gen(p, _STR("= string_add(%.*s, ", v.name.len, v.name.str));

    } else {

      Parser_gen(p, tos2(" += "));
    };

  } else { // default:

    Parser_gen(p,
               string_add(string_add(tos2(" "), Token_str(p->tok)), tos2(" ")));
  };

  Parser_fspace(p);

  Parser_fgen(p, Token_str(tok));

  Parser_fspace(p);

  Parser_next(p);

  int pos = p->cgen->cur_line.len;

  string expr_type = Parser_bool_expression(p);

  if (string_starts_with(p->assigned_type, tos2("Option_")) &&
      string_eq(expr_type,
                string_right(p->assigned_type, tos2("Option_").len))) {

    println(tos2("allowing option asss"));

    string expr = string_right(p->cgen->cur_line, pos);

    string left = string_left(p->cgen->cur_line, pos);

    CGen_resetln(p->cgen, string_add(left, _STR("opt_ok(%.*s, sizeof(%.*s))",
                                                expr.len, expr.str,
                                                expr_type.len, expr_type.str)));

  } else if (!p->builtin_pkg &&
             !Parser_check_types_no_throw(p, expr_type, p->assigned_type)) {

    p->scanner->line_nr--;

    Parser_error(p, _STR("cannot use type `%.*s` as type `%.*s` in assignment",
                         expr_type.len, expr_type.str, p->assigned_type.len,
                         p->assigned_type.str));
  };

  if (is_str && tok == main__Token_plus_assign) {

    Parser_gen(p, tos2(")"));
  };

  p->assigned_type = tos2("");

  if (!v.is_used) {

    Fn_mark_var_used(&/* ? */ *p->cur_fn, v);
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

  if (!p->builtin_pkg && Fn_known_var(&/* ? */ *p->cur_fn, name)) {

    Var v = Fn_find_var(&/* ? */ *p->cur_fn, name);

    Parser_error(p, _STR("redefinition of `%.*s`", name.len, name.str));
  };

  if (name.len > 1 && contains_capital(name)) {

    Parser_error(p, tos2("variable names cannot contain uppercase letters, use "
                         "snake_case instead"));
  };

  Parser_check_space(p, main__Token_decl_assign);

  int pos = CGen_add_placeholder(p->cgen);

  string typ = Parser_bool_expression(p);

  bool or_else = p->tok == main__Token_key_orelse;

  string tmp = Parser_get_tmp(p);

  if (or_else) {

    CGen_set_placeholder(
        p->cgen, pos, _STR("%.*s %.*s = ", typ.len, typ.str, tmp.len, tmp.str));

    Parser_gen(p, tos2(";"));

    typ = string_replace(typ, tos2("Option_"), tos2(""));

    Parser_next(p);

    Parser_check(p, main__Token_lcbr);

    Parser_genln(p, _STR("if (!%.*s .ok) {", tmp.len, tmp.str));

    Parser_register_var(p, (Var){.name = tos2("err"),
                                 .typ = tos2("string"),
                                 .is_mut = 0,
                                 .is_used = 1,
                                 .is_arg = 0,
                                 .is_const = 0,
                                 .is_import_const = 0,
                                 .args = new_array(0, 1, sizeof(Var)),
                                 .attr = tos("", 0),
                                 .is_alloc = 0,
                                 .ptr = 0,
                                 .ref = 0,
                                 .parent_fn = tos("", 0),
                                 .mod = tos("", 0),
                                 .line_nr = 0,
                                 .is_global = 0,
                                 .scope_level = 0});

    Parser_genln(p, _STR("string err = %.*s . error;", tmp.len, tmp.str));

    Parser_statements(p);

    Parser_genln(p,
                 _STR("%.*s %.*s = *(%.*s*) %.*s . data;", typ.len, typ.str,
                      name.len, name.str, typ.len, typ.str, tmp.len, tmp.str));

    if (!p->returns && p->prev_tok2 != main__Token_key_continue &&
        p->prev_tok2 != main__Token_key_break) {

      Parser_error(p, tos2("`or` block must return/continue/break/panic"));
    };
  };

  Parser_register_var(p, (Var){.name = name,
                               .typ = typ,
                               .is_mut = is_mut,
                               .is_alloc = p->is_alloc,
                               .is_arg = 0,
                               .is_const = 0,
                               .is_import_const = 0,
                               .args = new_array(0, 1, sizeof(Var)),
                               .attr = tos("", 0),
                               .ptr = 0,
                               .ref = 0,
                               .parent_fn = tos("", 0),
                               .mod = tos("", 0),
                               .line_nr = 0,
                               .is_global = 0,
                               .is_used = 0,
                               .scope_level = 0});

  string cgen_typ = typ;

  if (!or_else) {

    string gen_name = Table_var_cgen_name(p->table, name);

    string nt_gen = string_add(
        Table_cgen_name_type_pair(&/* ? */ *p->table, gen_name, cgen_typ),
        tos2("="));

    if (is_static) {

      nt_gen = _STR("static %.*s", nt_gen.len, nt_gen.str);
    };

    CGen_set_placeholder(p->cgen, pos, nt_gen);
  };

  p->var_decl_name = tos2("");
}
string Parser_bool_expression(Parser *p) {

  Token tok = p->tok;

  string typ = Parser_bterm(p);

  while (p->tok == main__Token_and || p->tok == main__Token_logical_or) {

    Parser_gen(p, _STR(" %.*s ", Token_str(p->tok).len, Token_str(p->tok).str));

    Parser_check_space(p, p->tok);

    Parser_check_types(p, Parser_bterm(p), typ);
  };

  if (string_eq(typ, tos2(""))) {

    println(tos2("curline:"));

    println(p->cgen->cur_line);

    println(Token_str(tok));

    Parser_error(p, tos2("expr() returns empty type"));
  };

  return typ;
}
string Parser_bterm(Parser *p) {

  int ph = CGen_add_placeholder(p->cgen);

  string typ = Parser_expression(p);

  p->expected_type = typ;

  bool is_str = string_eq(typ, tos2("string"));

  Token tok = p->tok;

  if (tok == main__Token_eq || tok == main__Token_gt || tok == main__Token_lt ||
      tok == main__Token_le || tok == main__Token_ge || tok == main__Token_ne) {

    Parser_fgen(p,
                _STR(" %.*s ", Token_str(p->tok).len, Token_str(p->tok).str));

    if (is_str) {

      Parser_gen(p, tos2(","));

    } else {

      Parser_gen(p, Token_str(tok));
    };

    Parser_next(p);

    Parser_check_types(p, Parser_expression(p), typ);

    typ = tos2("bool");

    if (is_str) {

      Parser_gen(p, tos2(")"));

      if ((tok == main__Token_eq)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2("string_eq("));

      } else if ((tok == main__Token_ne)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2("string_ne("));

      } else if ((tok == main__Token_le)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2("string_le("));

      } else if ((tok == main__Token_ge)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2("string_ge("));

      } else if ((tok == main__Token_gt)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2("string_gt("));

      } else if ((tok == main__Token_lt)) { /* case */

        CGen_set_placeholder(p->cgen, ph, tos2("string_lt("));
      };
    };
  };

  return typ;
}
string Parser_name_expr(Parser *p) {

  Parser_log(&/* ? */ *p, _STR("\nname expr() pass=%d tok=%.*s %.*s", p->run,
                               Token_str(p->tok).len, Token_str(p->tok).str,
                               p->lit.len, p->lit.str));

  int hack_pos = p->scanner->pos;

  Token hack_tok = p->tok;

  string hack_lit = p->lit;

  int ph = CGen_add_placeholder(p->cgen);

  bool ptr = p->tok == main__Token_amp;

  bool deref = p->tok == main__Token_mul;

  if (ptr || deref) {

    Parser_next(p);
  };

  if (deref) {

    if (p->pref->is_play && !p->builtin_pkg) {

      Parser_error(p, tos2("dereferencing is temporarily disabled on the "
                           "playground, will be fixed soon"));
    };
  };

  string name = p->lit;

  Parser_fgen(p, name);

  string orig_name = name;

  bool is_c = string_eq(name, tos2("C")) && Parser_peek(p) == main__Token_dot;

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

    Type *T = Parser_find_type(&/* ? */ *p, p->expected_type);

    if (T->is_enum) {

      Parser_check(p, main__Token_dot);

      string val = Parser_check_name(p);

      if (!Type_has_enum_val(&/* ? */ *T, val)) {

        Parser_error(p, _STR("enum `%.*s` does not have value `%.*s`",
                             T->name.len, T->name.str, val.len, val.str));
      };

      Parser_gen(
          p, string_add(string_add(string_add(string_add(T->mod, tos2("__")),
                                              p->expected_type),
                                   tos2("_")),
                        val));
    };

    return p->expected_type;
  };

  if (((string_eq(name, p->mod) && Table_known_pkg(&/* ? */ *p->table, name)) ||
       FileImportTable_known_alias(&/* ? */ *p->import_table, name)) &&
      !Fn_known_var(&/* ? */ *p->cur_fn, name) && !is_c) {

    string pkg = name;

    if (string_ne(name, p->mod) &&
        FileImportTable_known_alias(&/* ? */ *p->import_table, name)) {

      pkg = string_replace(
          FileImportTable_resolve_alias(&/* ? */ *p->import_table, name),
          tos2("."), tos2("_dot_"));
    };

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    name = p->lit;

    Parser_fgen(p, name);

    name = prepend_pkg(pkg, name);

  } else if (!Table_known_type(&/* ? */ *p->table, name) &&
             !Fn_known_var(&/* ? */ *p->cur_fn, name) &&
             !Table_known_fn(&/* ? */ *p->table, name) &&
             !Table_known_const(&/* ? */ *p->table, name) && !is_c) {

    name = Parser_prepend_pkg(&/* ? */ *p, name);
  };

  Var v = Fn_find_var(&/* ? */ *p->cur_fn, name);

  if (string_eq(name, string_add(tos2("main__"), p->var_decl_name))) {

    v.name = p->var_decl_name;

    v.typ = tos2("voidptr");

    v.is_mut = 1;
  };

  if (v.name.len != 0) {

    if (ptr) {

      Parser_gen(p, tos2("& /*vvar*/ "));

    } else if (deref) {

      Parser_gen(p, tos2("*"));
    };

    string typ = Parser_var_expr(p, v);

    if (deref) {

      if (!string_contains(typ, tos2("*")) &&
          !string_ends_with(typ, tos2("ptr"))) {

        printf("name=\"%.*s\", t=%.*s\n", name.len, name.str, v.typ.len,
               v.typ.str);

        Parser_error(p, _STR("dereferencing requires a pointer, but got `%.*s`",
                             typ.len, typ.str));
      };

      typ = string_replace(typ, tos2("ptr"), tos2(""));

      typ = string_replace(typ, tos2("*"), tos2(""));

    } else if (ptr) {

      typ = string_add(typ, tos2("*"));
    };

    return typ;
  };

  if (Table_known_type(&/* ? */ *p->table, name)) {

    if (!is_c && (Parser_peek(p) == main__Token_lpar ||
                  (deref && Parser_peek(p) == main__Token_rpar))) {

      if (deref) {

        name = string_add(name, tos2("*"));

      } else if (ptr) {

        name = string_add(name, tos2("*"));
      };

      Parser_gen(p, tos2("("));

      string typ = Parser_cast(p, name);

      Parser_gen(p, tos2(")"));

      while (p->tok == main__Token_dot) {

        typ = Parser_dot(p, typ, ph);
      };

      return typ;

    } else if (Parser_peek(p) == main__Token_dot) {

      Type *enum_type = Table_find_type(&/* ? */ *p->table, name);

      if (!enum_type->is_enum) {

        Parser_error(p, _STR("`%.*s` is not an enum", name.len, name.str));
      };

      Parser_next(p);

      Parser_check(p, main__Token_dot);

      string val = p->lit;

      Parser_gen(p, string_add(string_add(string_add(string_add(enum_type->mod,
                                                                tos2("__")),
                                                     enum_type->name),
                                          tos2("_")),
                               val));

      Parser_next(p);

      return enum_type->name;

    } else if (Parser_peek(p) == main__Token_lcbr) {

      p->scanner->pos = hack_pos;

      p->tok = hack_tok;

      p->lit = hack_lit;

      if (is_c_struct_init) {

        p->is_c_struct_init = 1;

        CGen_insert_before(p->cgen, tos2("struct /*c struct init*/"));
      };

      return Parser_struct_init(p, is_c_struct_init);
    };
  };

  if (is_c) {

    Fn f = (Fn){.name = name,
                .is_c = 1,
                .pkg = tos("", 0),
                .local_vars = new_array(0, 1, sizeof(Var)),
                .var_idx = 0,
                .args = new_array(0, 1, sizeof(Var)),
                .is_interface = 0,
                .scope_level = 0,
                .typ = tos("", 0),
                .receiver_typ = tos("", 0),
                .is_public = 0,
                .is_method = 0,
                .returns_error = 0,
                .is_decl = 0,
                .defer_text = tos("", 0)};

    Parser_fn_call(p, f, 0, tos2(""), tos2(""));

    Fn cfn = Table_find_fn(&/* ? */ *p->table, name);

    if (string_eq(cfn.name, tos2(""))) {

      return tos2("void*");
    };

    return cfn.typ;
  };

  Var c = Table_find_const(&/* ? */ *p->table, name);

  if (string_ne(c.name, tos2("")) && ptr && !c.is_global) {

    Parser_error(p, _STR("cannot take the address of constant `%.*s`",
                         c.name.len, c.name.str));
  };

  if (c.name.len != 0) {

    if (ptr) {

      Parser_gen(p, tos2("& /*const*/ "));
    };

    Parser_log(&/* ? */ *p, tos2("calling var expr"));

    string typ = Parser_var_expr(p, c);

    if (ptr) {

      typ = string_add(typ, tos2("*"));
    };

    return typ;
  };

  Fn f = Table_find_fn(&/* ? */ *p->table, name);

  if (string_eq(f.name, tos2(""))) {

    if (!Parser_first_run(&/* ? */ *p)) {

      if (p->v_script) {

        name = string_replace(name, tos2("main__"), tos2("os__"));

        f = Table_find_fn(&/* ? */ *p->table, name);
      };

      if (string_eq(f.name, tos2(""))) {

        if (Table_known_pkg(&/* ? */ *p->table, orig_name) ||
            FileImportTable_known_alias(&/* ? */ *p->import_table, orig_name)) {

          name = string_replace(string_replace(name, tos2("__"), tos2(".")),
                                tos2("_dot_"), tos2("."));

          Parser_error(p, _STR("undefined: `%.*s`", name.len, name.str));

        } else {

          Parser_error(p,
                       _STR("undefined: `%.*s`", orig_name.len, orig_name.str));
        };
      };

    } else {

      Parser_next(p);

      return tos2("void");
    };
  };

  if (Parser_peek(p) != main__Token_lpar) {

    Parser_gen(p, Table_cgen_name(p->table, &/*11 EXP:"Fn*" GOT:"Fn" */ f));

    Parser_next(p);

    return tos2("void*");
  };

  if (string_eq(f.typ, tos2("void")) && !p->inside_if_expr) {
  };

  Parser_log(&/* ? */ *p, tos2("calling function"));

  Parser_fn_call(p, f, 0, tos2(""), tos2(""));

  if (p->tok == main__Token_dot) {

    string typ = tos2("");

    while (p->tok == main__Token_dot) {

      typ = Parser_dot(p, f.typ, ph);
    };

    return typ;
  };

  Parser_log(&/* ? */ *p, tos2("end of name_expr"));

  return f.typ;
}
string Parser_var_expr(Parser *p, Var v) {

  Parser_log(&/* ? */ *p, _STR("\nvar_expr() v.name=\"%.*s\" v.typ=\"%.*s\"",
                               v.name.len, v.name.str, v.typ.len, v.typ.str));

  Fn_mark_var_used(&/* ? */ *p->cur_fn, v);

  int fn_ph = CGen_add_placeholder(p->cgen);

  p->expr_var = v;

  Parser_gen(p, Table_var_cgen_name(p->table, v.name));

  Parser_next(p);

  string typ = v.typ;

  if (string_starts_with(typ, tos2("fn "))) {

    Type *T = Table_find_type(&/* ? */ *p->table, typ);

    Parser_gen(p, tos2("("));

    Parser_fn_call_args(p, &/*11 EXP:"Fn*" GOT:"Fn" */ T->func);

    Parser_gen(p, tos2(")"));

    typ = T->func.typ;
  };

  if (p->tok == main__Token_lsbr) {

    typ = Parser_index_expr(p, typ, fn_ph);
  };

  while (p->tok == main__Token_dot) {

    typ = Parser_dot(p, typ, fn_ph);

    Parser_log(&/* ? */ *p, _STR("typ after dot=%.*s", typ.len, typ.str));

    if (p->tok == main__Token_lsbr) {
    };
  };

  if (p->tok == main__Token_inc || p->tok == main__Token_dec) {

    if (!v.is_mut && !v.is_arg && !p->pref->translated) {

      Parser_error(p, _STR("`%.*s` is immutable", v.name.len, v.name.str));
    };

    if (string_ne(typ, tos2("int"))) {

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

      return tos2("void");
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

  string field_name = p->lit;

  Parser_fgen(p, field_name);

  Parser_log(&/* ? */ *p, _STR("dot() field_name=%.*s typ=%.*s", field_name.len,
                               field_name.str, str_typ.len, str_typ.str));

  Type *typ = Parser_find_type(&/* ? */ *p, str_typ);

  if (typ->name.len == 0) {

    Parser_error(
        p, _STR("dot(): cannot find type `%.*s`", str_typ.len, str_typ.str));
  };

  bool has_field = Table_type_has_field(&/* ? */ *p->table, typ, field_name);

  bool has_method = Table_type_has_method(&/* ? */ *p->table, typ, field_name);

  if (!typ->is_c && !has_field && !has_method &&
      !Parser_first_run(&/* ? */ *p)) {

    if (string_starts_with(typ->name, tos2("Option_"))) {

      string opt_type = string_right(typ->name, 7);

      Parser_error(
          p, _STR("unhandled option type: %.*s?", opt_type.len, opt_type.str));
    };

    println(tos2("error in dot():"));

    println(tos2("fields:"));

    array_Var tmp156 = typ->fields;
    ;
    for (int tmp157 = 0; tmp157 < tmp156.len; tmp157++) {
      Var field = ((Var *)tmp156.data)[tmp157];

      println(field.name);
    };

    println(tos2("methods:"));

    array_Fn tmp158 = typ->methods;
    ;
    for (int tmp159 = 0; tmp159 < tmp158.len; tmp159++) {
      Fn field = ((Fn *)tmp158.data)[tmp159];

      println(field.name);
    };

    printf("str_typ==\"%.*s\"\n", str_typ.len, str_typ.str);

    Parser_error(p, _STR("type `%.*s`  has no field or method `%.*s`",
                         typ->name.len, typ->name.str, field_name.len,
                         field_name.str));
  };

  string dot = tos2(".");

  if (string_contains(str_typ, tos2("*"))) {

    dot = tos2("->");
  };

  if (has_field) {

    Var field = Table_find_field(&/* ? */ *p->table, typ, field_name);

    Token next = Parser_peek(p);

    bool modifying = Token_is_assign(next) || next == main__Token_inc ||
                     next == main__Token_dec;

    bool is_vi = Parser_fileis(&/* ? */ *p, tos2("vi"));

    if (!p->builtin_pkg && !p->pref->translated && modifying && !field.is_mut &&
        !is_vi) {

      Parser_error(p, _STR("cannot modify immutable field `%.*s` (type `%.*s`)",
                           field_name.len, field_name.str, typ->name.len,
                           typ->name.str));
    };

    if (!p->builtin_pkg && string_ne(p->mod, typ->mod)) {
    };

    if (field.access_mod == main__AccessMod_private && !p->builtin_pkg &&
        !p->pref->translated && string_ne(p->mod, typ->mod)) {

      Parser_error(p,
                   _STR("cannot refer to unexported field `%.*s` (type `%.*s`)",
                        field_name.len, field_name.str, typ->name.len,
                        typ->name.str));
    };

    if (field.access_mod == main__AccessMod_public && !p->builtin_pkg &&
        string_ne(p->mod, typ->mod)) {

      if (!field.is_mut && !p->pref->translated && modifying) {

        Parser_error(
            p,
            _STR("cannot modify public immutable field `%.*s` (type `%.*s`)",
                 field_name.len, field_name.str, typ->name.len, typ->name.str));
      };
    };

    Parser_gen(p, string_add(dot, field_name));

    Parser_next(p);

    return field.typ;
  };

  Fn method = Table_find_method(&/* ? */ *p->table, typ, field_name);

  Parser_fn_call(p, method, method_ph, tos2(""), str_typ);

  if (string_eq(method.typ, tos2("array")) &&
      string_starts_with(typ->name, tos2("array_"))) {

    return typ->name;
  };

  if (string_eq(method.typ, tos2("void*")) &&
      string_starts_with(typ->name, tos2("array_"))) {

    return string_right(typ->name, 6);
  };

  return method.typ;
}
string Parser_index_expr(Parser *p, string typ, int fn_ph) {

  Var v = p->expr_var;

  bool is_map = string_starts_with(typ, tos2("map_"));

  bool is_str = string_eq(typ, tos2("string"));

  bool is_arr0 = string_starts_with(typ, tos2("array_"));

  bool is_arr = is_arr0 || string_eq(typ, tos2("array"));

  bool is_ptr = string_eq(typ, tos2("byte*")) ||
                string_eq(typ, tos2("byteptr")) ||
                string_contains(typ, tos2("*"));

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

      typ = tos2("byte");

      Parser_fgen(p, tos2("["));

      if (p->builtin_pkg) {

        Parser_gen(p, tos2(".str["));

        close_bracket = 1;

      } else {

        Parser_gen(p, tos2(","));
      };
    };

    if (is_fixed_arr) {

      if (string_contains(typ, tos2("]["))) {

        int pos = string_index_after(typ, tos2("["), 1);

        typ = string_right(typ, pos);

      } else {

        typ = string_all_after(typ, tos2("]"));
      };

      Parser_gen(p, tos2("["));

      close_bracket = 1;

    } else if (is_ptr) {

      typ = string_replace(typ, tos2("*"), tos2(""));

      if (!is_arr) {

        Parser_gen(p, tos2("[/*ptr*/"));

        close_bracket = 1;
      };
    };

    if (is_arr) {

      if (is_arr0) {

        if (Parser_fileis(&/* ? */ *p, tos2("int_test"))) {

          printf("\nRRRR0 %.*s\n", typ.len, typ.str);
        };

        typ = string_right(typ, 6);

        if (Parser_fileis(&/* ? */ *p, tos2("int_test"))) {

          printf("RRRR %.*s\n", typ.len, typ.str);
        };
      };

      if (string_eq(typ, tos2("array"))) {

        typ = tos2("void*");
      };

      if (p->pref->translated && !p->builtin_pkg) {

        CGen_set_placeholder(p->cgen, fn_ph,
                             _STR("((%.*s*)(", typ.len, typ.str));

        Parser_gen(p, tos2(".data))["));

      } else {

        Parser_gen(p, tos2(","));
      };
    };

    if (is_map) {

      typ = string_replace(typ, tos2("map_"), tos2(""));

      if (string_eq(typ, tos2("map"))) {

        typ = tos2("void*");
      };

      Parser_gen(p, tos2(","));
    };

    if (is_arr) {

      Type *T = Table_find_type(&/* ? */ *p->table, Parser_expression(p));

      if (string_ne(T->parent, tos2("int"))) {

        Parser_check_types(p, T->name, tos2("int"));
      };

    } else {

      Parser_expression(p);
    };

    Parser_check(p, main__Token_rsbr);

    if (close_bracket) {

      Parser_gen(p, _STR("]/*r%.*s %d*/", typ.len, typ.str, v.is_mut));
    };
  };

  if (p->tok == main__Token_assign || p->tok == main__Token_plus_assign ||
      p->tok == main__Token_minus_assign || p->tok == main__Token_mult_assign ||
      p->tok == main__Token_div_assign || p->tok == main__Token_xor_assign ||
      p->tok == main__Token_mod_assign || p->tok == main__Token_or_assign ||
      p->tok == main__Token_and_assign ||
      p->tok == main__Token_righ_shift_assign ||
      p->tok == main__Token_left_shift_assign) {

    if (is_indexer && is_str && !p->builtin_pkg) {

      Parser_error(p, tos2("strings are immutable"));
    };

    int assign_pos = p->cgen->cur_line.len;

    p->assigned_type = typ;

    p->expected_type = typ;

    Parser_assign_statement(p, v, fn_ph, is_indexer && (is_map || is_arr));

    if (is_indexer && (is_map || is_arr)) {

      string tmp = Parser_get_tmp(p);

      string tmp_val = string_right(p->cgen->cur_line, assign_pos);

      CGen_resetln(p->cgen, string_left(p->cgen->cur_line, assign_pos));

      if (is_map) {

        CGen_set_placeholder(p->cgen, fn_ph, tos2("map__set(&"));

      } else {

        if (is_ptr) {

          CGen_set_placeholder(p->cgen, fn_ph, tos2("array_set("));

        } else {

          CGen_set_placeholder(p->cgen, fn_ph, tos2("array_set(&/*q*/"));
        };
      };

      Parser_gen(p, _STR(", & %.*s)", tmp.len, tmp.str));

      CGen_insert_before(p->cgen,
                         _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len,
                              tmp.str, tmp_val.len, tmp_val.str));
    };

    return typ;

    return tos2("void");

  } else if ((is_map || is_arr || (is_str && !p->builtin_pkg)) && is_indexer) {

    string index_expr = string_right(p->cgen->cur_line, fn_ph);

    CGen_resetln(p->cgen, string_left(p->cgen->cur_line, fn_ph));

    string tmp = Parser_get_tmp(p);

    string tmp_ok = Parser_get_tmp(p);

    if (is_map) {

      Parser_gen(p, _STR("%.*s", tmp.len, tmp.str));

      string def = type_default(typ);

      if (string_eq(def, tos2("STRUCT_DEFAULT_VALUE"))) {

        def = tos2("{0}");
      };

      CGen_insert_before(
          p->cgen,
          _STR("%.*s %.*s = %.*s; bool %.*s = map_get(%.*s, & %.*s);", typ.len,
               typ.str, tmp.len, tmp.str, def.len, def.str, tmp_ok.len,
               tmp_ok.str, index_expr.len, index_expr.str, tmp.len, tmp.str));

    } else if (is_arr) {

      if (p->pref->translated && !p->builtin_pkg) {

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

    } else if (is_str && !p->builtin_pkg) {

      Parser_gen(p, _STR("string_at(%.*s)", index_expr.len, index_expr.str));
    };

    if (is_map && string_eq(typ, tos2("string"))) {

      CGen_insert_before(p->cgen,
                         _STR("if (!%.*s) %.*s = tos(\"\", 0);", tmp_ok.len,
                              tmp_ok.str, tmp.len, tmp.str));
    };
  };

  return typ;
}
string Parser_expression(Parser *p) {

  if (string_contains(p->scanner->file_path, tos2("test_test"))) {

    printf("expression() pass=%d tok=\n", p->run);

    Parser_print_tok(&/* ? */ *p);
  };

  p->cgen;

  (tos2("/* expr start*/"));

  int ph = CGen_add_placeholder(p->cgen);

  string typ = Parser_term(p);

  bool is_str = string_eq(typ, tos2("string"));

  if (p->tok == main__Token_left_shift) {

    if (string_contains(typ, tos2("array_"))) {

      string tmp = Parser_get_tmp(p);

      string tmp_typ = string_right(typ, 6);

      Parser_check_space(p, main__Token_left_shift);

      Parser_gen(p, tos2(", ("));

      if (!p->expr_var.is_mut && !p->pref->translated) {

        Parser_error(p, _STR("`%.*s` is immutable (can\'t <<)",
                             p->expr_var.name.len, p->expr_var.name.str));
      };

      string expr_type = Parser_expression(p);

      bool push_array = string_eq(typ, expr_type);

      if (push_array) {

        CGen_set_placeholder(p->cgen, ph, tos2("_PUSH_MANY(&"));

        Parser_gen(p,
                   _STR("), %.*s, %.*s)", tmp.len, tmp.str, typ.len, typ.str));

      } else {

        Parser_check_types(p, expr_type, tmp_typ);

        string push_call = (string_contains(typ, tos2("*")))
                               ? (tos2("_PUSH("))
                               : (tos2("_PUSH(&"));

        CGen_set_placeholder(p->cgen, ph, push_call);

        Parser_gen(p, _STR("), %.*s, %.*s)", tmp.len, tmp.str, tmp_typ.len,
                           tmp_typ.str));
      };

      return tos2("void");

    } else {

      Parser_next(p);

      Parser_gen(p, tos2(" << "));

      Parser_check_types(p, Parser_expression(p), typ);

      return tos2("int");
    };
  };

  if (p->tok == main__Token_key_in) {

    Parser_fgen(p, tos2(" "));

    Parser_check(p, main__Token_key_in);

    Parser_fgen(p, tos2(" "));

    Parser_gen(p, tos2(", "));

    string arr_typ = Parser_expression(p);

    bool is_map = string_starts_with(arr_typ, tos2("map_"));

    if (!string_starts_with(arr_typ, tos2("array_")) && !is_map) {

      Parser_error(p, tos2("`in` requires an array/map"));
    };

    Type *T = Table_find_type(&/* ? */ *p->table, arr_typ);

    if (!is_map && !Type_has_method(&/* ? */ *T, tos2("contains"))) {

      Parser_error(
          p, _STR("%.*s has no method `contains`", arr_typ.len, arr_typ.str));
    };

    if (is_map) {

      CGen_set_placeholder(p->cgen, ph, tos2("_IN_MAP( "));

    } else {

      CGen_set_placeholder(p->cgen, ph, _STR("_IN(%.*s, ", typ.len, typ.str));
    };

    Parser_gen(p, tos2(")"));

    return tos2("bool");
  };

  if (p->tok == main__Token_righ_shift) {

    Parser_next(p);

    Parser_gen(p, tos2(" >> "));

    Parser_check_types(p, Parser_expression(p), typ);

    return tos2("int");
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

    bool is_num = string_eq(typ, tos2("void*")) ||
                  string_eq(typ, tos2("byte*")) || is_number_type(typ);

    Parser_check_space(p, p->tok);

    if (is_str && tok_op == main__Token_plus) {

      CGen_set_placeholder(p->cgen, ph, tos2("string_add("));

      Parser_gen(p, tos2(","));

    } else if (is_num) {

      if (string_eq(typ, tos2("void*"))) {

        CGen_set_placeholder(p->cgen, ph, tos2("(byte*)"));
      };

      Parser_gen(p, Token_str(tok_op));

    } else {

      if (p->pref->translated) {

        Parser_gen(p, string_add(Token_str(tok_op), tos2(" /*doom hack*/")));

      } else {

        Parser_gen(p, tos2(","));
      };
    };

    Parser_check_types(p, Parser_term(p), typ);

    if (is_str && tok_op == main__Token_plus) {

      Parser_gen(p, tos2(")"));
    };

    if (!p->pref->translated && !is_str && !is_num) {

      Type *T = Table_find_type(&/* ? */ *p->table, typ);

      if (tok_op == main__Token_plus) {

        if (Type_has_method(&/* ? */ *T, tos2("+"))) {

          CGen_set_placeholder(p->cgen, ph, string_add(typ, tos2("_plus(")));

          Parser_gen(p, tos2(")"));

        } else {

          Parser_error(
              p, _STR("operator + not defined on `%.*s`", typ.len, typ.str));
        };

      } else if (tok_op == main__Token_minus) {

        if (Type_has_method(&/* ? */ *T, tos2("-"))) {

          CGen_set_placeholder(p->cgen, ph,
                               _STR("%.*s_minus(", typ.len, typ.str));

          Parser_gen(p, tos2(")"));

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

    Parser_fgen(p,
                string_add(string_add(tos2(" "), Token_str(tok)), tos2(" ")));

    if (is_div && p->tok == main__Token_number &&
        string_eq(p->lit, tos2("0"))) {

      Parser_error(p, tos2("division by zero"));
    };

    if (is_mod && (is_float_type(typ) || !is_number_type(typ))) {

      Parser_error(p, tos2("operator .mod requires integer types"));
    };

    Parser_check_types(p, Parser_unary(p), typ);
  };

  return typ;
}
string Parser_unary(Parser *p) {

  string typ = tos2("");

  Token tok = p->tok;

  if ((tok == main__Token_not)) { /* case */

    Parser_gen(p, tos2("!"));

    Parser_check(p, main__Token_not);

    typ = tos2("bool");

    Parser_bool_expression(p);

  } else if ((tok == main__Token_bit_not)) { /* case */

    Parser_gen(p, tos2("~"));

    Parser_check(p, main__Token_bit_not);

    typ = Parser_bool_expression(p);

  } else { // default:

    typ = Parser_factor(p);
  };

  return typ;
}
string Parser_factor(Parser *p) {

  string typ = tos2("");

  Token tok = p->tok;

  if ((tok == main__Token_number)) { /* case */

    typ = tos2("int");

    if ((string_contains(p->lit, tos2(".")) ||
         (string_contains(p->lit, tos2("e")) ||
          string_contains(p->lit, tos2("E")))) &&
        !(string_at(p->lit, 0) == '0' &&
          (string_at(p->lit, 1) == 'x' || string_at(p->lit, 1) == 'X'))) {

      typ = tos2("f32");

    } else {

      u64 v_u64 = string_u64(p->lit);

      if (((u64)(((u32)(v_u64)))) < v_u64) {

        typ = tos2("u64");
      };
    };

    if (string_ne(p->expected_type, tos2("")) &&
        !is_valid_int_const(p->lit, p->expected_type)) {

      Parser_error(p, _STR("constant `%.*s` overflows `%.*s`", p->lit.len,
                           p->lit.str, p->expected_type.len,
                           p->expected_type.str));
    };

    Parser_gen(p, p->lit);

    Parser_fgen(p, p->lit);

  } else if ((tok == main__Token_minus)) { /* case */

    Parser_gen(p, tos2("-"));

    Parser_fgen(p, tos2("-"));

    Parser_next(p);

    return Parser_factor(p);

  } else if ((tok == main__Token_key_sizeof)) { /* case */

    Parser_gen(p, tos2("sizeof("));

    Parser_fgen(p, tos2("sizeof("));

    Parser_next(p);

    Parser_check(p, main__Token_lpar);

    string sizeof_typ = Parser_get_type(p);

    if (string_ends_with(sizeof_typ, tos2("*"))) {

      sizeof_typ =
          string_add(tos2("*"), string_left(sizeof_typ, sizeof_typ.len - 1));
    };

    Parser_check(p, main__Token_rpar);

    Parser_gen(p, _STR("%.*s)", sizeof_typ.len, sizeof_typ.str));

    Parser_fgen(p, _STR("%.*s)", sizeof_typ.len, sizeof_typ.str));

    return tos2("int");

  } else if ((tok == main__Token_amp) || (tok == main__Token_dot) ||
             (tok == main__Token_mul)) { /* case */

    return Parser_name_expr(p);

  } else if ((tok == main__Token_name)) { /* case */

    if (string_eq(p->lit, tos2("map")) && Parser_peek(p) == main__Token_lsbr) {

      return Parser_map_init(p);
    };

    if (string_eq(p->lit, tos2("json")) && Parser_peek(p) == main__Token_dot) {

      return Parser_js_decode(p);
    };

    typ = Parser_name_expr(p);

    return typ;

  } else if ((tok == main__Token_key_default)) { /* case */

    Parser_next(p);

    Parser_next(p);

    string name = Parser_check_name(p);

    if (string_ne(name, tos2("T"))) {

      Parser_error(p, tos2("default needs T"));
    };

    Parser_gen(p, tos2("default(T)"));

    Parser_next(p);

    return tos2("T");

  } else if ((tok == main__Token_lpar)) { /* case */

    Parser_gen(p, tos2("("));

    Parser_check(p, main__Token_lpar);

    typ = Parser_bool_expression(p);

    if (!p->ptr_cast) {

      Parser_check(p, main__Token_rpar);
    };

    p->ptr_cast = 0;

    Parser_gen(p, tos2(")"));

    return typ;

  } else if ((tok == main__Token_chartoken)) { /* case */

    Parser_char_expr(p);

    typ = tos2("byte");

    return typ;

  } else if ((tok == main__Token_str)) { /* case */

    Parser_string_expr(p);

    typ = tos2("string");

    return typ;

  } else if ((tok == main__Token_key_false)) { /* case */

    typ = tos2("bool");

    Parser_gen(p, tos2("0"));

    Parser_fgen(p, tos2("false"));

  } else if ((tok == main__Token_key_true)) { /* case */

    typ = tos2("bool");

    Parser_gen(p, tos2("1"));

    Parser_fgen(p, tos2("true"));

  } else if ((tok == main__Token_lsbr)) { /* case */

    return Parser_array_init(p);

  } else if ((tok == main__Token_lcbr)) { /* case */

    return Parser_assoc(p);

  } else if ((tok == main__Token_key_if)) { /* case */

    typ = Parser_if_st(p, 1, 0);

    return typ;

  } else { // default:

    Token next = Parser_peek(p);

    printf("PREV=%.*s\n", Token_str(p->prev_tok).len,
           Token_str(p->prev_tok).str);

    printf(".neXT=%.*s\n", Token_str(next).len, Token_str(next).str);

    Parser_error(p, _STR("unexpected token: `%.*s`", Token_str(p->tok).len,
                         Token_str(p->tok).str));
  };

  Parser_next(p);

  return typ;
}
string Parser_assoc(Parser *p) {

  Parser_next(p);

  string name = Parser_check_name(p);

  if (!Fn_known_var(&/* ? */ *p->cur_fn, name)) {

    Parser_error(p, _STR("unknown variable `%.*s`", name.len, name.str));
  };

  Var var = Fn_find_var(&/* ? */ *p->cur_fn, name);

  Parser_check(p, main__Token_pipe);

  Parser_gen(p, _STR("(%.*s){", var.typ.len, var.typ.str));

  array_string fields = new_array_from_c_array(0, 0, sizeof(string),
                                               (string[]){EMPTY_STRUCT_INIT});

  while (p->tok != main__Token_rcbr) {

    string field = Parser_check_name(p);

    _PUSH(&fields, (field), tmp223, string);

    Parser_gen(p, _STR(".%.*s = ", field.len, field.str));

    Parser_check(p, main__Token_colon);

    Parser_bool_expression(p);

    Parser_gen(p, tos2(","));

    if (p->tok != main__Token_rcbr) {

      Parser_check(p, main__Token_comma);
    };
  };

  Type *T = Table_find_type(&/* ? */ *p->table, var.typ);

  array_Var tmp225 = T->fields;
  ;
  for (int tmp226 = 0; tmp226 < tmp225.len; tmp226++) {
    Var ffield = ((Var *)tmp225.data)[tmp226];

    string f = ffield.name;

    if (_IN(string, f, fields)) {

      continue;
    };

    Parser_gen(p, _STR(".%.*s = %.*s . %.*s,", f.len, f.str, name.len, name.str,
                       f.len, f.str));
  };

  Parser_check(p, main__Token_rcbr);

  Parser_gen(p, tos2("}"));

  return var.typ;
}
void Parser_char_expr(Parser *p) {

  Parser_gen(p, _STR("\'%.*s\'", p->lit.len, p->lit.str));

  Parser_next(p);
}
string Parser_typ_to_fmt(Parser *p, string typ, int level) {

  Type *t = Table_find_type(&/* ? */ *p->table, typ);

  if (t->is_enum) {

    return tos2("%d");
  };

  if (string_eq(typ, tos2("string"))) { /* case */

    return tos2("%.*s");

  } else if (string_eq(typ, tos2("ustring"))) { /* case */

    return tos2("%.*s");

  } else if (string_eq(typ, tos2("byte")) || string_eq(typ, tos2("int")) ||
             string_eq(typ, tos2("char")) || string_eq(typ, tos2("byte")) ||
             string_eq(typ, tos2("bool")) || string_eq(typ, tos2("u32")) ||
             string_eq(typ, tos2("i32")) || string_eq(typ, tos2("i16")) ||
             string_eq(typ, tos2("u16")) || string_eq(typ, tos2("i8")) ||
             string_eq(typ, tos2("u8"))) { /* case */

    return tos2("%d");

  } else if (string_eq(typ, tos2("f64")) ||
             string_eq(typ, tos2("f32"))) { /* case */

    return tos2("%f");

  } else if (string_eq(typ, tos2("i64")) ||
             string_eq(typ, tos2("u64"))) { /* case */

    return tos2("%lld");

  } else if (string_eq(typ, tos2("byte*")) ||
             string_eq(typ, tos2("byteptr"))) { /* case */

    return tos2("%s");

  } else if (string_eq(typ, tos2("void"))) { /* case */

    Parser_error(p, tos2("cannot interpolate this value"));

  } else { // default:

    if (string_ends_with(typ, tos2("*"))) {

      return tos2("%p");
    };
  };

  if (string_ne(t->parent, tos2("")) && level == 0) {

    return Parser_typ_to_fmt(p, t->parent, level + 1);
  };

  return tos2("");
}
string format_str(string str) {

  str = string_replace(str, tos2("\""), tos2("\\\""));

#ifdef _WIN32

  str = string_replace(str, tos2("\r\n"), tos2("\\n"));

#endif
  ;

  str = string_replace(str, tos2("\n"), tos2("\\n"));

  return str;
}
void Parser_string_expr(Parser *p) {

  string str = p->lit;

  if (Parser_peek(p) != main__Token_dollar) {

    Parser_fgen(p, _STR("\'%.*s\'", str.len, str.str));

    string f = format_str(str);

    if (p->calling_c ||
        (p->pref->translated && string_eq(p->mod, tos2("main")))) {

      Parser_gen(p, _STR("\"%.*s\"", f.len, f.str));

    } else {

      Parser_gen(p, _STR("tos2(\"%.*s\")", f.len, f.str));
    };

    Parser_next(p);

    return;
  };

  string args = tos2("\"");

  string format = tos2("\"");

  Parser_fgen(p, tos2("\'"));

  bool complex_inter = 0;

  while (p->tok == main__Token_str) {

    Parser_fgen(p, p->lit);

    p->lit = string_replace(p->lit, tos2("%"), tos2("%%"));

    format = string_add(format, format_str(p->lit));

    Parser_next(p);

    if (p->tok != main__Token_dollar) {

      continue;
    };

    Parser_check(p, main__Token_dollar);

    if (Parser_peek(p) != main__Token_str) {

      Parser_fgen(p, tos2("{"));

      complex_inter = 1;
    };

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    string val = CGen_end_tmp(p->cgen);

    val = string_trim_space(val);

    args = string_add(args, _STR(", %.*s", val.len, val.str));

    if (string_eq(typ, tos2("string"))) {

      args = string_add(args, _STR(".len, %.*s.str", val.len, val.str));
    };

    if (string_eq(typ, tos2("ustring"))) {

      args = string_add(args, _STR(".len, %.*s.s.str", val.len, val.str));
    };

    bool custom = p->tok == main__Token_colon;

    if (custom) {

      format = string_add(format, tos2("%"));

      Parser_next(p);

      if (p->tok == main__Token_dot) {

        format = string_add(format, tos2("."));

        Parser_next(p);
      };

      format = string_add(format, p->lit);

      Parser_next(p);

      format = string_add(format, p->lit);

      Parser_next(p);

    } else {

      string f = Parser_typ_to_fmt(p, typ, 0);

      if (string_eq(f, tos2(""))) {

        Parser_error(
            p, _STR("unhandled sprintf format \"%.*s\" ", typ.len, typ.str));
      };

      format = string_add(format, f);
    };
  };

  if (complex_inter) {

    Parser_fgen(p, tos2("}"));
  };

  Parser_fgen(p, tos2("\'"));

  if (p->cgen->nogen) {

    return;
  };

  string cur_line = string_trim_space(p->cgen->cur_line);

  if (string_contains(cur_line, tos2("println (")) &&
      p->tok != main__Token_plus &&
      !string_contains(cur_line, tos2("string_add")) &&
      !string_contains(cur_line, tos2("eprintln"))) {

    CGen_resetln(p->cgen,
                 string_replace(cur_line, tos2("println ("), tos2("printf(")));

    Parser_gen(p,
               _STR("%.*s\\n%.*s", format.len, format.str, args.len, args.str));

    return;
  };

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

  Parser_next(p);

  Parser_check(p, main__Token_lsbr);

  string key_type = Parser_check_name(p);

  if (string_ne(key_type, tos2("string"))) {

    Parser_error(p, tos2("only string key maps allowed for now"));
  };

  Parser_check(p, main__Token_rsbr);

  string val_type = Parser_check_name(p);

  if (!Table_known_type(&/* ? */ *p->table, val_type)) {

    Parser_error(
        p, _STR("map init unknown type \"%.*s\"", val_type.len, val_type.str));
  };

  string typ = _STR("map_%.*s", val_type.len, val_type.str);

  Parser_register_map(p, typ);

  Parser_gen(p, _STR("new_map(1, sizeof(%.*s))", val_type.len, val_type.str));

  Parser_check(p, main__Token_lcbr);

  Parser_check(p, main__Token_rcbr);

  return typ;
}
string Parser_array_init(Parser *p) {

  p->is_alloc = 1;

  Parser_check(p, main__Token_lsbr);

  bool is_integer = p->tok == main__Token_number;

  string lit = p->lit;

  string typ = tos2("");

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

          string name = Parser_check_name(p);

          if (Table_known_type(&/* ? */ *p->table, name)) {

            CGen_resetln(p->cgen, tos2(""));

            Parser_gen(p, tos2("STRUCT_DEFAULT_VALUE"));

            return _STR("[%.*s]%.*s", lit.len, lit.str, name.len, name.str);

          } else {

            Parser_error(p, _STR("bad type `%.*s`", name.len, name.str));
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

      Parser_gen(p, tos2(", "));

      Parser_check(p, main__Token_comma);

      Parser_fspace(p);
    };

    i++;

    if (i == 1 && p->tok == main__Token_semicolon) {

      Parser_check_space(p, main__Token_semicolon);

      string val = string_right(p->cgen->cur_line, pos);

      CGen_resetln(p->cgen, string_left(p->cgen->cur_line, pos));

      if (0 && string_eq(string_trim_space(val), tos2("0"))) {

        Parser_gen(p, tos2("array_repeat( & V_ZERO, "));

      } else {

        string tmp = Parser_get_tmp(p);

        CGen_insert_before(p->cgen, _STR("%.*s %.*s = %.*s;", typ.len, typ.str,
                                         tmp.len, tmp.str, val.len, val.str));

        Parser_gen(p, _STR("array_repeat(&%.*s, ", tmp.len, tmp.str));
      };

      Parser_check_types(p, Parser_bool_expression(p), tos2("int"));

      Parser_gen(p, _STR(", sizeof(%.*s) )", typ.len, typ.str));

      Parser_check(p, main__Token_rsbr);

      return _STR("array_%.*s", typ.len, typ.str);
    };
  };

  Parser_check(p, main__Token_rsbr);

  if (p->tok != main__Token_name && i == 0) {

    Parser_error(p, tos2("specify array type: `[]typ` instead of `[]`"));
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

    Parser_gen(p, tos2(" }"));

    if (!Parser_first_run(&/* ? */ *p)) {

      if (p->inside_const) {

        CGen_set_placeholder(p->cgen, new_arr_ph, tos2("{ "));

      } else {

        CGen_set_placeholder(p->cgen, new_arr_ph,
                             _STR("(%.*s[]) { ", typ.len, typ.str));
      };
    };

    return _STR("[%d]%.*s", i, typ.len, typ.str);
  };

  string new_arr = tos2("new_array_from_c_array");

  if (no_alloc) {

    new_arr = string_add(new_arr, tos2("_no_alloc"));
  };

  Parser_gen(p, tos2(" })"));

  if (!Parser_first_run(&/* ? */ *p)) {

    if (i == 0) {

      CGen_set_placeholder(
          p->cgen, new_arr_ph,
          _STR("%.*s(%d, %d, sizeof(%.*s), (%.*s[]) {EMPTY_STRUCT_INIT ",
               new_arr.len, new_arr.str, i, i, typ.len, typ.str, typ.len,
               typ.str));

    } else {

      CGen_set_placeholder(p->cgen, new_arr_ph,
                           _STR("%.*s(%d, %d, sizeof(%.*s), (%.*s[]) { ",
                                new_arr.len, new_arr.str, i, i, typ.len,
                                typ.str, typ.len, typ.str));
    };
  };

  typ = _STR("array_%.*s", typ.len, typ.str);

  Parser_register_array(p, typ);

  return typ;
}
void Parser_register_array(Parser *p, string typ) {

  if (string_contains(typ, tos2("*"))) {

    printf("bad arr %.*s\n", typ.len, typ.str);

    return;
  };

  if (!Table_known_type(&/* ? */ *p->table, typ)) {

    Parser_register_type_with_parent(p, typ, tos2("array"));

    _PUSH(&p->cgen->typedefs, (_STR("typedef array %.*s;", typ.len, typ.str)),
          tmp258, string);
  };
}
void Parser_register_map(Parser *p, string typ) {

  if (string_contains(typ, tos2("*"))) {

    printf("bad map %.*s\n", typ.len, typ.str);

    return;
  };

  if (!Table_known_type(&/* ? */ *p->table, typ)) {

    Parser_register_type_with_parent(p, typ, tos2("map"));

    _PUSH(&p->cgen->typedefs, (_STR("typedef map %.*s;", typ.len, typ.str)),
          tmp259, string);
  };
}
string Parser_struct_init(Parser *p, bool is_c_struct_init) {

  p->is_struct_init = 1;

  string typ = Parser_get_type(p);

  strings__Builder_cut(p->scanner->fmt_out, typ.len);

  bool ptr = string_contains(typ, tos2("*"));

  if (string_eq(typ, tos2("tm"))) {

    string tmp262 = tos2("");

    array_set(&/*q*/ p->cgen->lines, p->cgen->lines.len - 1, &tmp262);

    string tmp263 = tos2("");

    array_set(&/*q*/ p->cgen->lines, p->cgen->lines.len - 2, &tmp263);
  };

  Parser_check(p, main__Token_lcbr);

  if (!ptr) {

    if (p->is_c_struct_init) {

      Parser_gen(p, _STR("(struct %.*s) {", typ.len, typ.str));

      p->is_c_struct_init = 0;

    } else {

      Parser_gen(p, _STR("(%.*s) {", typ.len, typ.str));
    };

  } else {

    if (p->tok == main__Token_not) {

      Parser_next(p);

      Parser_gen(p, tos2("0"));

      Parser_check(p, main__Token_rcbr);

      return typ;
    };

    string no_star = string_replace(typ, tos2("*"), tos2(""));

    Parser_gen(p, _STR("ALLOC_INIT(%.*s, {", no_star.len, no_star.str));
  };

  bool did_gen_something = 0;

  array_string inited_fields = new_array_from_c_array(
      0, 0, sizeof(string), (string[]){EMPTY_STRUCT_INIT});

  Token peek = Parser_peek(p);

  if (peek == main__Token_colon || p->tok == main__Token_rcbr) {

    Type *t = Table_find_type(&/* ? */ *p->table, typ);

    while (p->tok != main__Token_rcbr) {

      string field = Parser_check_name(p);

      if (!Type_has_field(&/* ? */ *t, field)) {

        Parser_error(p, _STR("`%.*s` has no field `%.*s`", t->name.len,
                             t->name.str, field.len, field.str));
      };

      Var f = Type_find_field(&/* ? */ *t, field);

      _PUSH(&inited_fields, (field), tmp271, string);

      Parser_gen(p, _STR(".%.*s = ", field.len, field.str));

      Parser_check(p, main__Token_colon);

      Parser_fspace(p);

      Parser_check_types(p, Parser_bool_expression(p), f.typ);

      if (p->tok == main__Token_comma) {

        Parser_next(p);
      };

      if (p->tok != main__Token_rcbr) {

        Parser_gen(p, tos2(","));
      };

      Parser_fgenln(p, tos2(""));

      did_gen_something = 1;
    };

    if (t->fields.len != inited_fields.len && inited_fields.len > 0) {

      Parser_gen(p, tos2(","));
    };

    array_Var tmp272 = t->fields;
    ;
    for (int i = 0; i < tmp272.len; i++) {
      Var field = ((Var *)tmp272.data)[i];

      if (array_string_contains(inited_fields, field.name)) {

        continue;
      };

      string field_typ = field.typ;

      if (!p->builtin_pkg && string_ends_with(field_typ, tos2("*")) &&
          string_contains(field_typ, tos2("Cfg"))) {

        Parser_error(p, _STR("pointer field `%.*s.%.*s` must be initialized",
                             typ.len, typ.str, field.name.len, field.name.str));
      };

      string def_val = type_default(field_typ);

      if (string_ne(def_val, tos2("")) &&
          string_ne(def_val, tos2("STRUCT_DEFAULT_VALUE"))) {

        Parser_gen(p, _STR(".%.*s = %.*s", field.name.len, field.name.str,
                           def_val.len, def_val.str));

        if (i != t->fields.len - 1) {

          Parser_gen(p, tos2(","));
        };
      };

      did_gen_something = 1;
    };

  } else {

    Type *T = Table_find_type(&/* ? */ *p->table, typ);

    if (T->fields.len == 0 && string_ne(T->parent, tos2(""))) {

      T = Table_find_type(&/* ? */ *p->table, T->parent);
    };

    array_Var tmp276 = T->fields;
    ;
    for (int i = 0; i < tmp276.len; i++) {
      Var ffield = ((Var *)tmp276.data)[i];

      string expr_typ = Parser_bool_expression(p);

      if (!Parser_check_types_no_throw(p, expr_typ, ffield.typ)) {

        Parser_error(
            p, _STR("field value #%d `%.*s` has type `%.*s`, got `%.*s` ",
                    i + 1, ffield.name.len, ffield.name.str, ffield.typ.len,
                    ffield.typ.str, expr_typ.len, expr_typ.str));
      };

      if (i < T->fields.len - 1) {

        if (p->tok != main__Token_comma) {

          Parser_error(
              p, _STR("too few values in `%.*s` literal (%d instead of %d)",
                      typ.len, typ.str, i + 1, T->fields.len));
        };

        Parser_gen(p, tos2(","));

        Parser_next(p);
      };
    };

    if (p->tok == main__Token_comma) {

      Parser_next(p);
    };

    if (p->tok != main__Token_rcbr) {

      Parser_error(p,
                   _STR("too many fields initialized: `%.*s` has %d field(s)",
                        typ.len, typ.str, T->fields.len));
    };

    did_gen_something = 1;
  };

  if (!did_gen_something) {

    Parser_gen(p, tos2("EMPTY_STRUCT_INIT"));
  };

  Parser_gen(p, tos2("}"));

  if (ptr) {

    Parser_gen(p, tos2(")"));
  };

  Parser_check(p, main__Token_rcbr);

  p->is_struct_init = 0;

  return typ;
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

  p->expected_type = tos2("");

  bool is_byteptr = string_eq(expr_typ, tos2("byte*")) ||
                    string_eq(expr_typ, tos2("byteptr"));

  bool is_bytearr = string_eq(expr_typ, tos2("array_byte"));

  if (string_eq(typ, tos2("string"))) {

    if (is_byteptr || is_bytearr) {

      if (p->tok == main__Token_comma) {

        Parser_check(p, main__Token_comma);

        CGen_set_placeholder(p->cgen, pos, tos2("tos("));

        if (is_bytearr) {

          Parser_gen(p, tos2(".data"));
        };

        Parser_gen(p, tos2(", "));

        Parser_check_types(p, Parser_expression(p), tos2("int"));

      } else {

        if (is_bytearr) {

          Parser_gen(p, tos2(".data"));
        };

        CGen_set_placeholder(p->cgen, pos, tos2("tos2("));
      };

    } else if (string_eq(expr_typ, tos2("int"))) {

      Parser_error(
          p, _STR("cannot cast `%.*s` to `%.*s`, use `str()` method instead",
                  expr_typ.len, expr_typ.str, typ.len, typ.str));

    } else {

      Parser_error(p, _STR("cannot cast `%.*s` to `%.*s`", expr_typ.len,
                           expr_typ.str, typ.len, typ.str));
    };

  } else {

    CGen_set_placeholder(p->cgen, pos, _STR("(%.*s)(", typ.len, typ.str));
  };

  Parser_check(p, main__Token_rpar);

  Parser_gen(p, tos2(")"));

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
string os_name_to_ifdef(string name) {

  if (string_eq(name, tos2("windows"))) { /* case */

    return tos2("_WIN32");

  } else if (string_eq(name, tos2("mac"))) { /* case */

    return tos2("__APPLE__");

  } else if (string_eq(name, tos2("linux"))) { /* case */

    return tos2("__linux__");

  } else if (string_eq(name, tos2("freebsd"))) { /* case */

    return tos2("__FreeBSD__");

  } else if (string_eq(name, tos2("openbsd"))) { /* case */

    return tos2("__OpenBSD__");

  } else if (string_eq(name, tos2("netbsd"))) { /* case */

    return tos2("__NetBSD__");

  } else if (string_eq(name, tos2("dragonfly"))) { /* case */

    return tos2("__DragonFly__");

  } else if (string_eq(name, tos2("msvc"))) { /* case */

    return tos2("_MSC_VER");
  };

  v_panic(_STR("bad os ifdef name \"%.*s\"", name.len, name.str));

  return tos2("");
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

        Parser_genln(p, tos2("#endif"));
      };

    } else {

      println(tos2("Supported platforms:"));

      println(array_string_str(main__SupportedPlatforms));

      Parser_error(p, _STR("unknown platform `%.*s`", name.len, name.str));
    };

  } else if (p->tok == main__Token_key_for) {

    Parser_next(p);

    string name = Parser_check_name(p);

    if (string_ne(name, tos2("field"))) {

      Parser_error(p, tos2("for field only"));
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

  } else if (p->tok == main__Token_key_else) {

    Parser_next(p);

    Parser_check(p, main__Token_lcbr);

    Parser_genln(p, tos2("#else"));

    Parser_statements_no_rcbr(p);

    Parser_genln(p, tos2("#endif"));

  } else {

    Parser_error(p, tos2("bad comptime expr"));
  };
}
void Parser_chash(Parser *p) {

  string hash = string_trim_space(p->lit);

  Parser_next(p);

  bool is_sig = Parser_is_sig(p);

  if (is_sig) {
  };

  if (string_starts_with(hash, tos2("flag "))) {

    string flag = string_right(hash, 5);

    if (string_contains(hash, tos2("linux")) && p->os != main__OS_linux) {

      return;

    } else if (string_contains(hash, tos2("darwin")) && p->os != main__OS_mac) {

      return;

    } else if (string_contains(hash, tos2("windows")) &&
               (p->os != main__OS_windows && p->os != main__OS_msvc)) {

      return;
    };

    if (string_contains(flag, tos2("linux")) ||
        string_contains(flag, tos2("darwin")) ||
        string_contains(flag, tos2("windows"))) {

      int pos = string_index(flag, tos2(" "));

      flag = string_right(flag, pos);
    };

    bool has_vroot = string_contains(flag, tos2("@VROOT"));

    flag = string_replace(string_trim_space(flag), tos2("@VROOT"), p->vroot);

    if (array_string_contains(p->table->flags, flag)) {

      return;
    };

    Parser_log(&/* ? */ *p, _STR("adding flag \"%.*s\"", flag.len, flag.str));

    if (has_vroot && string_contains(flag, tos2(".o"))) {

      if (p->os == main__OS_msvc) {

        build_thirdparty_obj_file_with_msvc(flag);

      } else {

        build_thirdparty_obj_file(flag);
      };
    };

    _PUSH(&p->table->flags, (flag), tmp293, string);

    return;
  };

  if (string_starts_with(hash, tos2("include"))) {

    if (Parser_first_run(&/* ? */ *p) && !is_sig) {

      _PUSH(&p->cgen->includes, (_STR("#%.*s", hash.len, hash.str)), tmp294,
            string);

      return;
    };

  } else if (string_starts_with(hash, tos2("typedef"))) {

    if (Parser_first_run(&/* ? */ *p)) {

      _PUSH(&p->cgen->typedefs, (_STR("%.*s", hash.len, hash.str)), tmp295,
            string);
    };

  } else if (string_contains(hash, tos2("embed"))) {

    int pos = string_index(hash, tos2("embed")) + 5;

    string file = string_right(hash, pos);

    if (p->pref->build_mode != main__BuildMode_default_mode) {

      Parser_genln(p, _STR("#include %.*s", file.len, file.str));
    };

  } else if (string_contains(hash, tos2("define"))) {

    _PUSH(&p->cgen->includes, (_STR("#%.*s", hash.len, hash.str)), tmp298,
          string);

  } else if (string_eq(hash, tos2("v"))) {

    println(tos2("v script"));

  } else {

    if (!p->can_chash) {

      Parser_error(
          p, tos2("bad token `#` (embedding C code is no longer supported)"));
    };

    Parser_genln(p, hash);
  };
}
string Parser_if_st(Parser *p, bool is_expr, int elif_depth) {

  if (is_expr) {

    if (Parser_fileis(&/* ? */ *p, tos2("if_expr"))) {

      println(tos2("IF EXPR"));
    };

    p->inside_if_expr = 1;

    Parser_gen(p, tos2("("));

  } else {

    Parser_gen(p, tos2("if ("));

    Parser_fgen(p, tos2("if "));
  };

  Parser_next(p);

  Parser_check_types(p, Parser_bool_expression(p), tos2("bool"));

  if (is_expr) {

    Parser_gen(p, tos2(") ? ("));

  } else {

    Parser_genln(p, tos2(") {"));
  };

  Parser_fgen(p, tos2(" "));

  Parser_check(p, main__Token_lcbr);

  string typ = tos2("");

  if (p->tok == main__Token_key_if && p->inside_if_expr) {

    typ = Parser_factor(p);

    Parser_next(p);

  } else {

    typ = Parser_statements(p);
  };

  if (p->tok == main__Token_key_else) {

    Parser_fgenln(p, tos2(""));

    Parser_check(p, main__Token_key_else);

    Parser_fspace(p);

    if (p->tok == main__Token_key_if) {

      if (is_expr) {

        Parser_gen(p, tos2(") : ("));

        return Parser_if_st(p, is_expr, elif_depth + 1);

      } else {

        Parser_gen(p, tos2(" else "));

        return Parser_if_st(p, is_expr, 0);
      };
    };

    if (is_expr) {

      Parser_gen(p, tos2(") : ("));

    } else {

      Parser_genln(p, tos2(" else { "));
    };

    Parser_check(p, main__Token_lcbr);

    typ = Parser_statements(p);

    p->inside_if_expr = 0;

    if (is_expr) {

      Parser_gen(p, strings__repeat(')', elif_depth + 1));
    };

    return typ;
  };

  p->inside_if_expr = 0;

  if (Parser_fileis(&/* ? */ *p, tos2("test_test"))) {

    printf("if ret typ=\"%.*s\" line=%d\n", typ.len, typ.str,
           p->scanner->line_nr);
  };

  return typ;
}
void Parser_for_st(Parser *p) {

  Parser_check(p, main__Token_key_for);

  Parser_fgen(p, tos2(" "));

  p->for_expr_cnt++;

  Token next_tok = Parser_peek(p);

  Fn_open_scope(p->cur_fn);

  if (p->tok == main__Token_lcbr) {

    Parser_gen(p, tos2("while (1) {"));

  } else if (p->tok == main__Token_key_mut) {

    Parser_error(p, tos2("`mut` is not required in for loops"));

  } else if (next_tok == main__Token_decl_assign ||
             next_tok == main__Token_assign ||
             p->tok == main__Token_semicolon) {

    Parser_genln(p, tos2("for ("));

    if (next_tok == main__Token_decl_assign) {

      Parser_var_decl(p);

    } else if (p->tok != main__Token_semicolon) {

      Parser_statement(p, 0);
    };

    Parser_check(p, main__Token_semicolon);

    Parser_gen(p, tos2(" ; "));

    Parser_fgen(p, tos2(" "));

    if (p->tok != main__Token_semicolon) {

      Parser_bool_expression(p);
    };

    Parser_check(p, main__Token_semicolon);

    Parser_gen(p, tos2(" ; "));

    Parser_fgen(p, tos2(" "));

    if (p->tok != main__Token_lcbr) {

      Parser_statement(p, 0);
    };

    Parser_genln(p, tos2(") { "));

  } else if (Parser_peek(p) == main__Token_comma) {

    string i = Parser_check_name(p);

    Parser_check(p, main__Token_comma);

    string val = Parser_check_name(p);

    Parser_fgen(p, tos2(" "));

    Parser_check(p, main__Token_key_in);

    Parser_fgen(p, tos2(" "));

    string tmp = Parser_get_tmp(p);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    bool is_arr = string_starts_with(typ, tos2("array_"));

    bool is_map = string_starts_with(typ, tos2("map_"));

    bool is_str = string_eq(typ, tos2("string"));

    if (!is_arr && !is_str && !is_map) {

      Parser_error(p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    string expr = CGen_end_tmp(p->cgen);

    Parser_genln(p, _STR("%.*s %.*s = %.*s ;", typ.len, typ.str, tmp.len,
                         tmp.str, expr.len, expr.str));

    int pad = (is_arr) ? (6) : (4);

    string var_typ = string_right(typ, pad);

    Var val_var = (Var){.name = val,
                        .typ = var_typ,
                        .ptr = string_contains(typ, tos2("*")),
                        .is_arg = 0,
                        .is_const = 0,
                        .is_import_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos("", 0),
                        .is_mut = 0,
                        .is_alloc = 0,
                        .ref = 0,
                        .parent_fn = tos("", 0),
                        .mod = tos("", 0),
                        .line_nr = 0,
                        .is_global = 0,
                        .is_used = 0,
                        .scope_level = 0};

    Parser_register_var(p, val_var);

    if (is_arr || is_str) {

      Var i_var = (Var){.name = i,
                        .typ = tos2("int"),
                        .is_mut = 1,
                        .is_arg = 0,
                        .is_const = 0,
                        .is_import_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos("", 0),
                        .is_alloc = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos("", 0),
                        .mod = tos("", 0),
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
                        .typ = tos2("string"),
                        .is_mut = 1,
                        .is_arg = 0,
                        .is_const = 0,
                        .is_import_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos("", 0),
                        .is_alloc = 0,
                        .ptr = 0,
                        .ref = 0,
                        .parent_fn = tos("", 0),
                        .mod = tos("", 0),
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

      if (string_eq(def, tos2("STRUCT_DEFAULT_VALUE"))) {

        def = tos2("{0}");
      };

      Parser_genln(p, _STR("%.*s %.*s = %.*s; map_get(%.*s, %.*s, & %.*s);",
                           var_typ.len, var_typ.str, val.len, val.str, def.len,
                           def.str, tmp.len, tmp.str, i.len, i.str, val.len,
                           val.str));
    };

  } else if (Parser_peek(p) == main__Token_key_in) {

    string val = Parser_check_name(p);

    Parser_fgen(p, tos2(" "));

    Parser_check(p, main__Token_key_in);

    Parser_fspace(p);

    string tmp = Parser_get_tmp(p);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    string expr = CGen_end_tmp(p->cgen);

    bool is_range = p->tok == main__Token_dotdot;

    string range_end = tos2("");

    if (is_range) {

      Parser_check_types(p, typ, tos2("int"));

      Parser_check_space(p, main__Token_dotdot);

      CGen_start_tmp(p->cgen);

      Parser_check_types(p, Parser_bool_expression(p), tos2("int"));

      range_end = CGen_end_tmp(p->cgen);
    };

    bool is_arr = string_contains(typ, tos2("array"));

    bool is_str = string_eq(typ, tos2("string"));

    if (!is_arr && !is_str && !is_range) {

      Parser_error(p, _STR("cannot range over type `%.*s`", typ.len, typ.str));
    };

    Parser_genln(p, _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len,
                         tmp.str, expr.len, expr.str));

    string var_type = tos2("");

    if (is_arr) {

      var_type = string_right(typ, 6);

    } else if (is_str) {

      var_type = tos2("byte");

    } else if (is_range) {

      var_type = tos2("int");
    };

    Var val_var = (Var){.name = val,
                        .typ = var_type,
                        .ptr = string_contains(typ, tos2("*")),
                        .is_arg = 0,
                        .is_const = 0,
                        .is_import_const = 0,
                        .args = new_array(0, 1, sizeof(Var)),
                        .attr = tos("", 0),
                        .is_mut = 0,
                        .is_alloc = 0,
                        .ref = 0,
                        .parent_fn = tos("", 0),
                        .mod = tos("", 0),
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

    Parser_gen(p, tos2("while ("));

    Parser_check_types(p, Parser_bool_expression(p), tos2("bool"));

    Parser_genln(p, tos2(") {"));
  };

  Parser_fspace(p);

  Parser_check(p, main__Token_lcbr);

  Parser_genln(p, tos2(""));

  Parser_statements(p);

  Parser_close_scope(p);

  p->for_expr_cnt--;
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

  while (p->tok == main__Token_key_case || p->tok == main__Token_key_default ||
         Parser_peek(p) == main__Token_arrow ||
         p->tok == main__Token_key_else) {

    if (p->tok == main__Token_key_default || p->tok == main__Token_key_else) {

      Parser_genln(p, tos2("else  { // default:"));

      if (p->tok == main__Token_key_default) {

        Parser_check(p, main__Token_key_default);

        Parser_check(p, main__Token_colon);

      } else {

        Parser_check(p, main__Token_key_else);

        Parser_check(p, main__Token_arrow);
      };

      Parser_statements(p);

      break;
    };

    if (i > 0) {

      Parser_gen(p, tos2("else "));
    };

    Parser_gen(p, tos2("if ("));

    bool got_comma = 0;

    while (1) {

      if (got_comma) {

        Parser_gen(p, tos2(") ||  "));
      };

      if (string_eq(typ, tos2("string"))) {

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

    Parser_gen(p, tos2(")) {"));

    Parser_genln(p, tos2("/* case */"));

    Parser_statements(p);

    i++;
  };
}
void Parser_assert_statement(Parser *p) {

  if (Parser_first_run(&/* ? */ *p)) {

    return;
  };

  Parser_check(p, main__Token_key_assert);

  Parser_fspace(p);

  string tmp = Parser_get_tmp(p);

  Parser_gen(p, _STR("bool %.*s = ", tmp.len, tmp.str));

  Parser_check_types(p, Parser_bool_expression(p), tos2("bool"));

  string filename = p->file_path;

  Parser_genln(
      p,
      _STR(";\n \nif (!%.*s) { \n  puts(\"\\x1B[31mFAILED: %.*s() in "
           "%.*s:%d\\x1B[0m\");  \ng_test_ok = 0 ; \n	// TODO\n	// "
           "Maybe print all vars in a test function if it fails? \n} \nelse { "
           "\n  //puts(\"\\x1B[32mPASSED: %.*s()\\x1B[0m\");\n}",
           tmp.len, tmp.str, p->cur_fn->name.len, p->cur_fn->name.str,
           filename.len, filename.str, p->scanner->line_nr, p->cur_fn->name.len,
           p->cur_fn->name.str));
}
void Parser_return_st(Parser *p) {

  Parser_check(p, main__Token_key_return);

  Parser_fgen(p, tos2(" "));

  bool fn_returns = string_ne(p->cur_fn->typ, tos2("void"));

  if (fn_returns) {

    if (p->tok == main__Token_rcbr) {

      Parser_error(p, _STR("`%.*s` needs to return `%.*s`", p->cur_fn->name.len,
                           p->cur_fn->name.str, p->cur_fn->typ.len,
                           p->cur_fn->typ.str));

    } else {

      int ph = CGen_add_placeholder(p->cgen);

      string expr_type = Parser_bool_expression(p);

      if (string_ends_with(p->cur_fn->typ, expr_type) &&
          string_starts_with(p->cur_fn->typ, tos2("Option_"))) {

        string tmp = Parser_get_tmp(p);

        string ret = string_right(p->cgen->cur_line, ph);

        p->cgen->cur_line =
            _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);", expr_type.len,
                 expr_type.str, tmp.len, tmp.str, expr_type.len, expr_type.str,
                 ret.len, ret.str);

        CGen_resetln(p->cgen,
                     _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);", expr_type.len,
                          expr_type.str, tmp.len, tmp.str, expr_type.len,
                          expr_type.str, ret.len, ret.str));

        Parser_gen(p, _STR("return opt_ok(&%.*s, sizeof(%.*s))", tmp.len,
                           tmp.str, expr_type.len, expr_type.str));

      } else {

        string ret = string_right(p->cgen->cur_line, ph);

        p->cgen;

        (p->cur_fn->defer_text);

        if (string_eq(p->cur_fn->defer_text, tos2("")) ||
            string_eq(expr_type, tos2("void*"))) {

          CGen_resetln(p->cgen, _STR("return %.*s", ret.len, ret.str));

        } else {

          string tmp = Parser_get_tmp(p);

          CGen_resetln(p->cgen,
                       _STR("%.*s %.*s = %.*s;", expr_type.len, expr_type.str,
                            tmp.len, tmp.str, ret.len, ret.str));

          Parser_genln(p, p->cur_fn->defer_text);

          Parser_genln(p, _STR("return %.*s;", tmp.len, tmp.str));
        };
      };

      Parser_check_types(p, expr_type, p->cur_fn->typ);
    };

  } else {

    if (0 && p->tok == main__Token_name || p->tok == main__Token_number) {

      Parser_error(p, _STR("function `%.*s` does not return a value",
                           p->cur_fn->name.len, p->cur_fn->name.str));
    };

    if (string_eq(p->cur_fn->name, tos2("main"))) {

      Parser_gen(p, tos2("return 0"));

    } else {

      Parser_gen(p, tos2("return"));
    };
  };

  p->returns = 1;
}
string prepend_pkg(string pkg, string name) {

  return _STR("%.*s__%.*s", pkg.len, pkg.str, name.len, name.str);
}
string Parser_prepend_pkg(Parser *p, string name) {

  return prepend_pkg(p->mod, name);
}
void Parser_go_statement(Parser *p) {

  Parser_check(p, main__Token_key_go);

  if (Parser_peek(p) == main__Token_dot) {

    string var_name = p->lit;

    Var v = Fn_find_var(&/* ? */ *p->cur_fn, var_name);

    Fn_mark_var_used(&/* ? */ *p->cur_fn, v);

    Parser_next(p);

    Parser_check(p, main__Token_dot);

    Type *typ = Table_find_type(&/* ? */ *p->table, v.typ);

    Fn method = Table_find_method(&/* ? */ *p->table, typ, p->lit);

    Parser_async_fn_call(p, method, 0, var_name, v.typ);

  } else {

    Fn f = Table_find_fn(&/* ? */ *p->table, p->lit);

    if (string_eq(f.name, tos2("println"))) {

      Parser_error(p, tos2("`go` cannot be used with `println`"));
    };

    Parser_async_fn_call(p, f, 0, tos2(""), tos2(""));
  };
}
void Parser_register_var(Parser *p, Var v) {

  if (v.line_nr == 0) {

    v.line_nr = p->scanner->line_nr;
  };

  Fn_register_var(p->cur_fn, v);
}
string Parser_js_decode(Parser *p) {

  Parser_check(p, main__Token_name);

  Parser_check(p, main__Token_dot);

  string op = Parser_check_name(p);

  if (string_eq(op, tos2("decode"))) {

    Parser_check(p, main__Token_lpar);

    string typ = Parser_get_type(p);

    Parser_check(p, main__Token_comma);

    CGen_start_tmp(p->cgen);

    Parser_check_types(p, Parser_bool_expression(p), tos2("string"));

    string expr = CGen_end_tmp(p->cgen);

    Parser_check(p, main__Token_rpar);

    string tmp = Parser_get_tmp(p);

    string cjson_tmp = Parser_get_tmp(p);

    string decl = _STR("%.*s %.*s; ", typ.len, typ.str, tmp.len, tmp.str);

    Type *T = Table_find_type(&/* ? */ *p->table, typ);

    array_Var tmp351 = T->fields;
    ;
    for (int tmp352 = 0; tmp352 < tmp351.len; tmp352++) {
      Var field = ((Var *)tmp351.data)[tmp352];

      string def_val = type_default(field.typ);

      if (string_ne(def_val, tos2(""))) {

        decl = string_add(decl, _STR("%.*s . %.*s = %.*s;\n", tmp.len, tmp.str,
                                     field.name.len, field.name.str,
                                     def_val.len, def_val.str));
      };
    };

    Parser_gen_json_for_type(p, *T);

    decl = string_add(decl,
                      _STR("cJSON* %.*s = json__json_parse(%.*s);",
                           cjson_tmp.len, cjson_tmp.str, expr.len, expr.str));

    CGen_insert_before(p->cgen, decl);

    Parser_gen(p, _STR("json__jsdecode_%.*s(%.*s, &%.*s); cJSON_Delete(%.*s);",
                       typ.len, typ.str, cjson_tmp.len, cjson_tmp.str, tmp.len,
                       tmp.str, cjson_tmp.len, cjson_tmp.str));

    string opt_type = _STR("Option_%.*s", typ.len, typ.str);

    _PUSH(&p->cgen->typedefs,
          (_STR("typedef Option %.*s;", opt_type.len, opt_type.str)), tmp355,
          string);

    Table_register_type(p->table, opt_type);

    return opt_type;

  } else if (string_eq(op, tos2("encode"))) {

    Parser_check(p, main__Token_lpar);

    CGen_start_tmp(p->cgen);

    string typ = Parser_bool_expression(p);

    Type *T = Table_find_type(&/* ? */ *p->table, typ);

    Parser_gen_json_for_type(p, *T);

    string expr = CGen_end_tmp(p->cgen);

    Parser_check(p, main__Token_rpar);

    Parser_gen(p, _STR("json__json_print(json__jsencode_%.*s(%.*s))", typ.len,
                       typ.str, expr.len, expr.str));

    return tos2("string");

  } else {

    Parser_error(p, _STR("bad json op \"%.*s\"", op.len, op.str));
  };

  return tos2("");
}
bool is_compile_time_const(string s) {

  s = string_trim_space(s);

  if (string_eq(s, tos2(""))) {

    return 0;
  };

  if (string_contains(s, tos2("\'"))) {

    return 1;
  };

  string tmp359 = s;
  ;
  for (int tmp360 = 0; tmp360 < tmp359.len; tmp360++) {
    byte c = ((byte *)tmp359.str)[tmp360];

    if (!((c >= '0' && c <= '9') || c == '.')) {

      return 0;
    };
  };

  return 1;
}
void Parser_attribute(Parser *p) {

  Parser_check(p, main__Token_lsbr);

  p->attr = Parser_check_name(p);

  Parser_check(p, main__Token_rsbr);

  if (p->tok == main__Token_func) {

    Parser_fn_decl(p);

    p->attr = tos2("");

    return;

  } else if (p->tok == main__Token_key_struct) {

    Parser_struct_decl(p);

    p->attr = tos2("");

    return;
  };

  Parser_error(p, tos2("bad attribute usage"));
}
void Parser_defer_st(Parser *p) {

  Parser_check(p, main__Token_key_defer);

  Parser_genln(p, tos2("/*"));

  int pos = p->cgen->lines.len;

  Parser_check(p, main__Token_lcbr);

  Parser_genln(p, tos2("{"));

  Parser_statements(p);

  p->cur_fn->defer_text = string_add(
      array_string_join(array_right(p->cgen->lines, pos), tos2("\n")),
      p->cur_fn->defer_text);

  Parser_genln(p, tos2("*/"));
}
void Scanner_fgen(Scanner *scanner, string s) {

  if (scanner->fmt_line_empty) {

    s = string_add(strings__repeat('\t', scanner->fmt_indent), s);
  };

  strings__Builder_write(&/* ? */ scanner->fmt_out, s);

  scanner->fmt_line_empty = 0;
}
void Scanner_fgenln(Scanner *scanner, string s) {

  if (scanner->fmt_line_empty) {

    s = string_add(strings__repeat('\t', scanner->fmt_indent), s);
  };

  strings__Builder_writeln(&/* ? */ scanner->fmt_out, s);

  scanner->fmt_line_empty = 1;
}
void Parser_fgen(Parser *p, string s) { Scanner_fgen(p->scanner, s); }
void Parser_fspace(Parser *p) { Parser_fgen(p, tos2(" ")); }
void Parser_fgenln(Parser *p, string s) { Scanner_fgenln(p->scanner, s); }
Token Parser_peek(Parser *p) {

  while (1) {

    Token tok = Scanner_peek(p->scanner);

    if (tok != main__Token_nl) {

      return tok;
    };
  };
}
void Parser_create_type_string(Parser *p, Type T, string name) {

  Scanner_create_type_string(p->scanner, T, name);
}
Scanner *new_scanner(string file_path) {

  if (!os__file_exists(file_path)) {

    v_panic(_STR("\"%.*s\" doesn\'t exist", file_path.len, file_path.str));
  };

  Option_string tmp1 = os__read_file(file_path);
  if (!tmp1.ok) {
    string err = tmp1.error;

    v_panic(
        _STR("scanner: failed to open \"%.*s\"", file_path.len, file_path.str));

    return ALLOC_INIT(Scanner, {
                                   .file_path = tos("", 0),
                                   .text = tos("", 0),
                                   .pos = 0,
                                   .line_nr = 0,
                                   .inside_string = 0,
                                   .dollar_start = 0,
                                   .dollar_end = 0,
                                   .debug = 0,
                                   .line_comment = tos("", 0),
                                   .started = 0,
                                   .fmt_indent = 0,
                                   .fmt_line_empty = 0,
                               });
  }
  string raw_text = *(string *)tmp1.data;
  ;

  if (raw_text.len >= 3) {

    byte *c_text = raw_text.str;

    if (c_text[/*ptr*/ 0] /*rbyte 0*/ == 0xEF &&
        c_text[/*ptr*/ 1] /*rbyte 0*/ == 0xBB &&
        c_text[/*ptr*/ 2] /*rbyte 0*/ == 0xBF) {

      int offset_from_begin = 3;

      raw_text = tos(&/*11 EXP:"byte*" GOT:"byte" */ c_text
                         [/*ptr*/ offset_from_begin] /*rbyte 0*/,
                     strlen(c_text) - offset_from_begin);
    };
  };

  string text = raw_text;

  Scanner *scanner =
      ALLOC_INIT(Scanner, {
                              .file_path = file_path,
                              .text = text,
                              .fmt_out = strings__new_builder(1000),
                              .pos = 0,
                              .line_nr = 0,
                              .inside_string = 0,
                              .dollar_start = 0,
                              .dollar_end = 0,
                              .debug = 0,
                              .line_comment = tos("", 0),
                              .started = 0,
                              .fmt_indent = 0,
                              .fmt_line_empty = 0,
                          });

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

        Scanner_error(&/* ? */ *s, tos2("malformed octal constant"));
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

  while (byte_is_digit(string_at(s->text, s->pos))) {

    s->pos++;
  };

  if (Scanner_expect(s, tos2(".."), s->pos)) {

    string number = string_substr(s->text, start_pos, s->pos);

    s->pos--;

    return number;
  };

  if (string_at(s->text, s->pos) == '.') {

    s->pos++;

    while (byte_is_digit(string_at(s->text, s->pos))) {

      s->pos++;
    };
  };

  bool has_exponential_part = 0;

  if (Scanner_expect(s, tos2("e+"), s->pos) ||
      Scanner_expect(s, tos2("e-"), s->pos)) {

    int exp_start_pos = s->pos += 2;

    while (byte_is_digit(string_at(s->text, s->pos))) {

      s->pos++;
    };

    if (exp_start_pos == s->pos) {

      Scanner_error(&/* ? */ *s, tos2("exponent has no digits"));
    };

    has_exponential_part = 1;
  };

  if (string_at(s->text, s->pos) == '.') {

    if (has_exponential_part) {

      Scanner_error(&/* ? */ *s, tos2("exponential part should be integer"));

    } else {

      Scanner_error(&/* ? */ *s, tos2("too many decimal points in number"));
    };
  };

  string number = string_substr(s->text, start_pos, s->pos);

  s->pos--;

  return number;
}
string Scanner_ident_number(Scanner *s) {

  if (Scanner_expect(s, tos2("0x"), s->pos)) {

    return Scanner_ident_hex_number(s);
  };

  if (Scanner_expect(s, tos2("0."), s->pos) ||
      Scanner_expect(s, tos2("0e"), s->pos)) {

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
        !Scanner_expect(s, tos2("\r\n"), s->pos - 1)) {

      s->line_nr++;
    };

    s->pos++;
  };
}
ScanRes Scanner_scan(Scanner *s) {

  if (string_ne(s->line_comment, tos2(""))) {
  };

  if (s->started) {

    s->pos++;
  };

  s->started = 1;

  if (s->pos >= s->text.len) {

    return scan_res(main__Token_eof, tos2(""));
  };

  if (!s->inside_string) {

    Scanner_skip_whitespace(s);
  };

  if (s->dollar_end) {

    if (string_at(s->text, s->pos) == '\'') {

      s->dollar_end = 0;

      return scan_res(main__Token_str, tos2(""));
    };

    s->dollar_end = 0;

    return scan_res(main__Token_str, Scanner_ident_string(s));
  };

  Scanner_skip_whitespace(s);

  if (s->pos >= s->text.len) {

    return scan_res(main__Token_eof, tos2(""));
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

      return scan_res(key_to_token(name), tos2(""));
    };

    if (s->inside_string) {

      if (next_char == '\'') {

        s->pos++;

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

  } else if (byte_is_digit(c) || c == '.' && byte_is_digit(nextc)) {

    string num = Scanner_ident_number(s);

    return scan_res(main__Token_number, num);
  };

  if ((c == '+')) { /* case */

    if (nextc == '+') {

      s->pos++;

      return scan_res(main__Token_inc, tos2(""));

    } else if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_plus_assign, tos2(""));
    };

    return scan_res(main__Token_plus, tos2(""));

  } else if ((c == '-')) { /* case */

    if (nextc == '-') {

      s->pos++;

      return scan_res(main__Token_dec, tos2(""));

    } else if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_minus_assign, tos2(""));
    };

    return scan_res(main__Token_minus, tos2(""));

  } else if ((c == '*')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_mult_assign, tos2(""));
    };

    return scan_res(main__Token_mul, tos2(""));

  } else if ((c == '^')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_xor_assign, tos2(""));
    };

    return scan_res(main__Token_xor, tos2(""));

  } else if ((c == '%')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_mod_assign, tos2(""));
    };

    return scan_res(main__Token_mod, tos2(""));

  } else if ((c == '?')) { /* case */

    return scan_res(main__Token_question, tos2(""));

  } else if ((c == '\'')) { /* case */

    return scan_res(main__Token_str, Scanner_ident_string(s));

  } else if ((c == '\`')) { /* case */

    return scan_res(main__Token_chartoken, Scanner_ident_char(s));

  } else if ((c == '(')) { /* case */

    return scan_res(main__Token_lpar, tos2(""));

  } else if ((c == ')')) { /* case */

    return scan_res(main__Token_rpar, tos2(""));

  } else if ((c == '[')) { /* case */

    return scan_res(main__Token_lsbr, tos2(""));

  } else if ((c == ']')) { /* case */

    return scan_res(main__Token_rsbr, tos2(""));

  } else if ((c == '{')) { /* case */

    if (s->inside_string) {

      return Scanner_scan(s);
    };

    return scan_res(main__Token_lcbr, tos2(""));

  } else if ((c == '$')) { /* case */

    return scan_res(main__Token_dollar, tos2(""));

  } else if ((c == '}')) { /* case */

    if (s->inside_string) {

      s->pos++;

      if (string_at(s->text, s->pos) == '\'') {

        s->inside_string = 0;

        return scan_res(main__Token_str, tos2(""));
      };

      return scan_res(main__Token_str, Scanner_ident_string(s));

    } else {

      return scan_res(main__Token_rcbr, tos2(""));
    };

  } else if ((c == '&')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_and_assign, tos2(""));
    };

    if (nextc == '&') {

      s->pos++;

      return scan_res(main__Token_and, tos2(""));
    };

    return scan_res(main__Token_amp, tos2(""));

  } else if ((c == '|')) { /* case */

    if (nextc == '|') {

      s->pos++;

      return scan_res(main__Token_logical_or, tos2(""));
    };

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_or_assign, tos2(""));
    };

    return scan_res(main__Token_pipe, tos2(""));

  } else if ((c == ',')) { /* case */

    return scan_res(main__Token_comma, tos2(""));

  } else if ((c == '@')) { /* case */

    s->pos++;

    string name = Scanner_ident_name(s);

    if (!is_key(name)) {

      Scanner_error(
          &/* ? */ *s,
          tos2("@ must be used before keywords (e.g. `@type string`)"));
    };

    return scan_res(main__Token_name, name);

  } else if ((c == '\r')) { /* case */

    if (nextc == '\n') {

      s->pos++;

      return scan_res(main__Token_nl, tos2(""));
    };

  } else if ((c == '\n')) { /* case */

    return scan_res(main__Token_nl, tos2(""));

  } else if ((c == '.')) { /* case */

    if (nextc == '.') {

      s->pos++;

      return scan_res(main__Token_dotdot, tos2(""));
    };

    return scan_res(main__Token_dot, tos2(""));

  } else if ((c == '#')) { /* case */

    int start = s->pos + 1;

    while (s->pos < s->text.len && string_at(s->text, s->pos) != '\n') {

      s->pos++;
    };

    s->line_nr++;

    string hash = string_substr(s->text, start, s->pos);

    return scan_res(main__Token_hash, string_trim_space(hash));

  } else if ((c == '>')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_ge, tos2(""));

    } else if (nextc == '>') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return scan_res(main__Token_righ_shift_assign, tos2(""));
      };

      s->pos++;

      return scan_res(main__Token_righ_shift, tos2(""));

    } else {

      return scan_res(main__Token_gt, tos2(""));
    };

  } else if ((c == '<')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_le, tos2(""));

    } else if (nextc == '<') {

      if (s->pos + 2 < s->text.len && string_at(s->text, s->pos + 2) == '=') {

        s->pos += 2;

        return scan_res(main__Token_left_shift_assign, tos2(""));
      };

      s->pos++;

      return scan_res(main__Token_left_shift, tos2(""));

    } else {

      return scan_res(main__Token_lt, tos2(""));
    };

  } else if ((c == '=')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_eq, tos2(""));

    } else if (nextc == '>') {

      s->pos++;

      return scan_res(main__Token_arrow, tos2(""));

    } else {

      return scan_res(main__Token_assign, tos2(""));
    };

  } else if ((c == ':')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_decl_assign, tos2(""));

    } else {

      return scan_res(main__Token_colon, tos2(""));
    };

  } else if ((c == ';')) { /* case */

    return scan_res(main__Token_semicolon, tos2(""));

  } else if ((c == '!')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_ne, tos2(""));

    } else {

      return scan_res(main__Token_not, tos2(""));
    };

  } else if ((c == '~')) { /* case */

    return scan_res(main__Token_bit_not, tos2(""));

  } else if ((c == '/')) { /* case */

    if (nextc == '=') {

      s->pos++;

      return scan_res(main__Token_div_assign, tos2(""));
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

          Scanner_error(&/* ? */ *s, tos2("comment not terminated"));
        };

        if (string_at(s->text, s->pos) == '\n') {

          s->line_nr++;

          continue;
        };

        if (Scanner_expect(s, tos2("/*"), s->pos)) {

          nest_count++;

          continue;
        };

        if (Scanner_expect(s, tos2("*/"), s->pos)) {

          nest_count--;
        };
      };

      s->pos++;

      int end = s->pos + 1;

      string comm = string_substr(s->text, start, end);

      Scanner_fgenln(s, comm);

      return Scanner_scan(s);
    };

    return scan_res(main__Token_div, tos2(""));
  };

#ifdef _WIN32

  if (c == '\0') {

    return scan_res(main__Token_eof, tos2(""));
  };

#endif
  ;

  string msg =
      _STR("invalid character `%.*s`", byte_str(c).len, byte_str(c).str);

  if (c == '"') {

    msg = string_add(msg, tos2(", use \' to denote strings"));
  };

  Scanner_error(&/* ? */ *s, msg);

  return scan_res(main__Token_eof, tos2(""));
}
void Scanner_error(Scanner *s, string msg) {

  string file = string_all_after(s->file_path, tos2("/"));

  printf("panic: %.*s:%d\n", file.len, file.str, s->line_nr + 1);

  println(msg);

  v_exit(1);
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

      Scanner_error(&/* ? */ *s, tos2("0 character in a string literal"));
    };

    if (c == '0' && s->pos > 5 && Scanner_expect(s, tos2("\\x0"), s->pos - 3)) {

      Scanner_error(&/* ? */ *s, tos2("0 character in a string literal"));
    };

    if (c == '{' && prevc == '$') {

      s->inside_string = 1;

      s->pos -= 2;

      break;
    };

    if ((byte_is_letter(c) || c == '_') && prevc == '$') {

      s->inside_string = 1;

      s->dollar_start = 1;

      s->pos -= 2;

      break;
    };
  };

  string lit = tos2("");

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

    bool double_slash = Scanner_expect(s, tos2("\\\\"), s->pos - 2);

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

  int tmp120 = start_pos;
  ;
  for (int tmp121 = tmp120; tmp121 < end_pos; tmp121++) {
    int pos = tmp121;

    if (string_at(s->text, pos) != string_at(want, pos - start_pos)) {

      return 0;
    };
  };

  return 1;
}
void Scanner_debug_tokens(Scanner *s) {

  s->pos = 0;

  s->debug = 1;

  string fname = string_all_after(s->file_path, tos2("/"));

  printf("\n===DEBUG TOKENS %.*s===\n", fname.len, fname.str);

  while (1) {

    ScanRes res = Scanner_scan(s);

    Token tok = res.tok;

    string lit = res.lit;

    v_print(Token_str(tok));

    if (string_ne(lit, tos2(""))) {

      printf(" `%.*s`\n", lit.len, lit.str);

    } else {

      println(tos2(""));
    };

    if (tok == main__Token_eof) {

      println(tos2("============ END OF DEBUG TOKENS =================="));

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

  string newtext = tos2("\'{ ");

  int start = Scanner_get_opening_bracket(s) + 1;

  int end = s->pos;

  array_Var tmp150 = T.fields;
  ;
  for (int i = 0; i < tmp150.len; i++) {
    Var field = ((Var *)tmp150.data)[i];

    if (i != 0) {

      newtext = string_add(newtext, tos2(", "));
    };

    newtext = string_add(
        newtext, string_add(_STR("%.*s: ", field.name.len, field.name.str),
                            _STR("$%.*s.%.*s", name.len, name.str,
                                 field.name.len, field.name.str)));
  };

  newtext = string_add(newtext, tos2(" }\'"));

  s->text = string_add(string_add(string_substr(s->text, 0, start), newtext),
                       string_substr(s->text, end, s->text.len));

  s->pos = start - 2;

  s->line_nr = line;

  s->inside_string = inside_string;
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

    s = string_add(s, tos2("\n"));
  };

  if (t.methods.len > 0) {

    array_Fn tmp4 = t.methods;
    ;
    for (int tmp5 = 0; tmp5 < tmp4.len; tmp5++) {
      Fn method = ((Fn *)tmp4.data)[tmp5];

      s = string_add(
          s, _STR("\n    %.*s", Fn_str(method).len, Fn_str(method).str));
    };

    s = string_add(s, tos2("\n"));
  };

  s = string_add(s, tos2("}\n"));

  return s;
}
string Fn_str(Fn f) {

  Table t = (Table){.types = new_array(0, 1, sizeof(Type)),
                    .consts = new_array(0, 1, sizeof(Var)),
                    .packages = new_array(0, 1, sizeof(string)),
                    .imports = new_array(0, 1, sizeof(string)),
                    .flags = new_array(0, 1, sizeof(string)),
                    .fn_cnt = 0,
                    .obfuscate = 0};

  string str_args =
      Fn_str_args(&/* ? */ f, &/*11 EXP:"Table*" GOT:"Table" */ t);

  return _STR("%.*s(%.*s) %.*s", f.name.len, f.name.str, str_args.len,
              str_args.str, f.typ.len, f.typ.str);
}
bool is_number_type(string typ) {

  return array_string_contains(main__NUMBER_TYPES, typ);
}
bool is_float_type(string typ) {

  return array_string_contains(main__FLOAT_TYPES, typ);
}
bool is_primitive_type(string typ) {

  return is_number_type(typ) || string_eq(typ, tos2("string"));
}
Table *new_table(bool obfuscate) {

  Table *t = ALLOC_INIT(Table, {
                                   .obf_ids = new_map(1, sizeof(int)),
                                   .fns = new_map(1, sizeof(Fn)),
                                   .obfuscate = obfuscate,
                                   .types = new_array(0, 1, sizeof(Type)),
                                   .consts = new_array(0, 1, sizeof(Var)),
                                   .packages = new_array(0, 1, sizeof(string)),
                                   .imports = new_array(0, 1, sizeof(string)),
                                   .flags = new_array(0, 1, sizeof(string)),
                                   .fn_cnt = 0,
                               });

  Table_register_type(t, tos2("int"));

  Table_register_type(t, tos2("size_t"));

  Table_register_type_with_parent(t, tos2("i8"), tos2("int"));

  Table_register_type_with_parent(t, tos2("u8"), tos2("int"));

  Table_register_type_with_parent(t, tos2("i16"), tos2("int"));

  Table_register_type_with_parent(t, tos2("u16"), tos2("int"));

  Table_register_type_with_parent(t, tos2("i32"), tos2("int"));

  Table_register_type_with_parent(t, tos2("u32"), tos2("int"));

  Table_register_type_with_parent(t, tos2("byte"), tos2("int"));

  Table_register_type_with_parent(t, tos2("i64"), tos2("int"));

  Table_register_type_with_parent(t, tos2("u64"), tos2("int"));

  Table_register_type(t, tos2("byteptr"));

  Table_register_type(t, tos2("intptr"));

  Table_register_type(t, tos2("f32"));

  Table_register_type(t, tos2("f64"));

  Table_register_type(t, tos2("rune"));

  Table_register_type(t, tos2("bool"));

  Table_register_type(t, tos2("void"));

  Table_register_type(t, tos2("voidptr"));

  Table_register_type(t, tos2("va_list"));

  Table_register_const(t, tos2("stdin"), tos2("int"), tos2("main"), 0);

  Table_register_const(t, tos2("stdout"), tos2("int"), tos2("main"), 0);

  Table_register_const(t, tos2("stderr"), tos2("int"), tos2("main"), 0);

  Table_register_const(t, tos2("errno"), tos2("int"), tos2("main"), 0);

  Table_register_type_with_parent(t, tos2("map_string"), tos2("map"));

  Table_register_type_with_parent(t, tos2("map_int"), tos2("map"));

  return t;
}
string Table_var_cgen_name(Table *t, string name) {

  if (array_string_contains(main__CReserved, name)) {

    return _STR("v_%.*s", name.len, name.str);

  } else {

    return name;
  };
}
void Table_register_package(Table *t, string pkg) {

  if (array_string_contains(t->packages, pkg)) {

    return;
  };

  _PUSH(&t->packages, (pkg), tmp9, string);
}
bool Table_known_pkg(Table *table, string pkg) {

  return _IN(string, pkg, table->packages);
}
void Table_register_const(Table *t, string name, string typ, string mod,
                          bool is_imported) {

  _PUSH(&t->consts,
        ((Var){.name = name,
               .typ = typ,
               .is_const = 1,
               .is_import_const = is_imported,
               .mod = mod,
               .is_arg = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos("", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos("", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .scope_level = 0}),
        tmp10, Var);
}
void Parser_register_global(Parser *p, string name, string typ) {

  _PUSH(&p->table->consts,
        ((Var){.name = name,
               .typ = typ,
               .is_const = 1,
               .is_global = 1,
               .mod = p->mod,
               .is_arg = 0,
               .is_import_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos("", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos("", 0),
               .line_nr = 0,
               .is_used = 0,
               .scope_level = 0}),
        tmp11, Var);
}
void Table_register_fn(Table *t, Fn new_fn) {

  Fn tmp12 = new_fn;

  map__set(&t->fns, new_fn.name, &tmp12);
}
bool Table_known_type(Table *table, string typ) {

  if (string_ends_with(typ, tos2("*")) && !string_contains(typ, tos2(" "))) {

    typ = string_left(typ, typ.len - 1);
  };

  array_Type tmp13 = table->types;
  ;
  for (int tmp14 = 0; tmp14 < tmp13.len; tmp14++) {
    Type t = ((Type *)tmp13.data)[tmp14];

    if (string_eq(t.name, typ) && !t.is_placeholder) {

      return 1;
    };
  };

  return 0;
}
Fn Table_find_fn(Table *t, string name) {

  Fn tmp15 = {0};
  bool tmp16 = map_get(t->fns, name, &tmp15);

  Fn f = tmp15;

  if (!isnil(f.name.str)) {

    return f;
  };

  return (Fn){.name = tos("", 0),
              .pkg = tos("", 0),
              .local_vars = new_array(0, 1, sizeof(Var)),
              .var_idx = 0,
              .args = new_array(0, 1, sizeof(Var)),
              .is_interface = 0,
              .scope_level = 0,
              .typ = tos("", 0),
              .is_c = 0,
              .receiver_typ = tos("", 0),
              .is_public = 0,
              .is_method = 0,
              .returns_error = 0,
              .is_decl = 0,
              .defer_text = tos("", 0)};
}
bool Table_known_fn(Table *t, string name) {

  Fn f = Table_find_fn(&/* ? */ *t, name);

  return string_ne(f.name, tos2(""));
}
bool Table_known_const(Table *t, string name) {

  Var v = Table_find_const(&/* ? */ *t, name);

  return v.name.len > 0;
}
void Table_register_type(Table *t, string typ) {

  if (typ.len == 0) {

    return;
  };

  array_Type tmp20 = t->types;
  ;
  for (int tmp21 = 0; tmp21 < tmp20.len; tmp21++) {
    Type typ2 = ((Type *)tmp20.data)[tmp21];

    if (string_eq(typ2.name, typ)) {

      return;
    };
  };

  _PUSH(&t->types,
        ((Type){.name = typ,
                .mod = tos("", 0),
                .fields = new_array(0, 1, sizeof(Var)),
                .methods = new_array(0, 1, sizeof(Fn)),
                .parent = tos("", 0),
                .is_c = 0,
                .is_interface = 0,
                .is_enum = 0,
                .enum_vals = new_array(0, 1, sizeof(string)),
                .is_placeholder = 0}),
        tmp22, Type);
}
void Parser_register_type_with_parent(Parser *p, string strtyp, string parent) {

  Type typ = (Type){.name = strtyp,
                    .parent = parent,
                    .mod = p->mod,
                    .fields = new_array(0, 1, sizeof(Var)),
                    .methods = new_array(0, 1, sizeof(Fn)),
                    .is_c = 0,
                    .is_interface = 0,
                    .is_enum = 0,
                    .enum_vals = new_array(0, 1, sizeof(string)),
                    .is_placeholder = 0};

  Table_register_type2(p->table, typ);
}
void Table_register_type_with_parent(Table *t, string typ, string parent) {

  if (typ.len == 0) {

    return;
  };

  array_Type tmp24 = t->types;
  ;
  for (int tmp25 = 0; tmp25 < tmp24.len; tmp25++) {
    Type typ2 = ((Type *)tmp24.data)[tmp25];

    if (string_eq(typ2.name, typ)) {

      return;
    };
  };

  _PUSH(&t->types,
        ((Type){.name = typ,
                .parent = parent,
                .mod = tos("", 0),
                .fields = new_array(0, 1, sizeof(Var)),
                .methods = new_array(0, 1, sizeof(Fn)),
                .is_c = 0,
                .is_interface = 0,
                .is_enum = 0,
                .enum_vals = new_array(0, 1, sizeof(string)),
                .is_placeholder = 0}),
        tmp26, Type);
}
void Table_register_type2(Table *t, Type typ) {

  if (typ.name.len == 0) {

    return;
  };

  array_Type tmp27 = t->types;
  ;
  for (int tmp28 = 0; tmp28 < tmp27.len; tmp28++) {
    Type typ2 = ((Type *)tmp27.data)[tmp28];

    if (string_eq(typ2.name, typ.name)) {

      return;
    };
  };

  _PUSH(&t->types, (typ), tmp29, Type);
}
void Type_add_field(Type *t, string name, string typ, bool is_mut, string attr,
                    AccessMod access_mod) {

  Var v = (Var){.name = name,
                .typ = typ,
                .is_mut = is_mut,
                .attr = attr,
                .access_mod = access_mod,
                .is_arg = 0,
                .is_const = 0,
                .is_import_const = 0,
                .args = new_array(0, 1, sizeof(Var)),
                .is_alloc = 0,
                .ptr = 0,
                .ref = 0,
                .parent_fn = tos("", 0),
                .mod = tos("", 0),
                .line_nr = 0,
                .is_global = 0,
                .is_used = 0,
                .scope_level = 0};

  _PUSH(&t->fields, (v), tmp31, Var);
}
bool Type_has_field(Type *t, string name) {

  Var field = Type_find_field(&/* ? */ *t, name);

  return (string_ne(field.name, tos2("")));
}
bool Type_has_enum_val(Type *t, string name) {

  return _IN(string, name, t->enum_vals);
}
Var Type_find_field(Type *t, string name) {

  array_Var tmp33 = t->fields;
  ;
  for (int tmp34 = 0; tmp34 < tmp33.len; tmp34++) {
    Var field = ((Var *)tmp33.data)[tmp34];

    if (string_eq(field.name, name)) {

      return field;
    };
  };

  return (Var){.typ = tos("", 0),
               .name = tos("", 0),
               .is_arg = 0,
               .is_const = 0,
               .is_import_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos("", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos("", 0),
               .mod = tos("", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .scope_level = 0};
}
bool Table_type_has_field(Table *table, Type *typ, string name) {

  Var field = Table_find_field(&/* ? */ *table, typ, name);

  return (string_ne(field.name, tos2("")));
}
Var Table_find_field(Table *table, Type *typ, string name) {

  Var field = Type_find_field(&/* ? */ *typ, name);

  if (field.name.len == 0 && typ->parent.len > 0) {

    Type *parent = Table_find_type(&/* ? */ *table, typ->parent);

    return Type_find_field(&/* ? */ *parent, name);
  };

  return field;
}
void Type_add_method(Type *t, Fn f) { _PUSH(&t->methods, (f), tmp38, Fn); }
bool Type_has_method(Type *t, string name) {

  Fn method = Type_find_method(&/* ? */ *t, name);

  return (string_ne(method.name, tos2("")));
}
bool Table_type_has_method(Table *table, Type *typ, string name) {

  Fn method = Table_find_method(&/* ? */ *table, typ, name);

  return (string_ne(method.name, tos2("")));
}
Fn Table_find_method(Table *table, Type *typ, string name) {

  Fn method = Type_find_method(&/* ? */ *typ, name);

  if (method.name.len == 0 && typ->parent.len > 0) {

    Type *parent = Table_find_type(&/* ? */ *table, typ->parent);

    return Type_find_method(&/* ? */ *parent, name);
  };

  return method;
}
Fn Type_find_method(Type *t, string name) {

  array_Fn tmp43 = t->methods;
  ;
  for (int tmp44 = 0; tmp44 < tmp43.len; tmp44++) {
    Fn method = ((Fn *)tmp43.data)[tmp44];

    if (string_eq(method.name, name)) {

      return method;
    };
  };

  return (Fn){.name = tos("", 0),
              .pkg = tos("", 0),
              .local_vars = new_array(0, 1, sizeof(Var)),
              .var_idx = 0,
              .args = new_array(0, 1, sizeof(Var)),
              .is_interface = 0,
              .scope_level = 0,
              .typ = tos("", 0),
              .is_c = 0,
              .receiver_typ = tos("", 0),
              .is_public = 0,
              .is_method = 0,
              .returns_error = 0,
              .is_decl = 0,
              .defer_text = tos("", 0)};
}
Type *Parser_find_type(Parser *p, string name) {

  Type *typ = Table_find_type(&/* ? */ *p->table, name);

  if (typ->name.len == 0) {

    return Table_find_type(&/* ? */ *p->table,
                           Parser_prepend_pkg(&/* ? */ *p, name));
  };

  return typ;
}
Type *Table_find_type(Table *t, string name) {

  if (string_ends_with(name, tos2("*")) && !string_contains(name, tos2(" "))) {

    name = string_left(name, name.len - 1);
  };

  array_Type tmp46 = t->types;
  ;
  for (int i = 0; i < tmp46.len; i++) {
    Type typ = ((Type *)tmp46.data)[i];

    if (string_eq(typ.name, name)) {

      return &/*vvar*/ (*(Type *)array__get(t->types, i));
    };
  };

  return ALLOC_INIT(Type, {.mod = tos("", 0),
                           .name = tos("", 0),
                           .fields = new_array(0, 1, sizeof(Var)),
                           .methods = new_array(0, 1, sizeof(Fn)),
                           .parent = tos("", 0),
                           .is_c = 0,
                           .is_interface = 0,
                           .is_enum = 0,
                           .enum_vals = new_array(0, 1, sizeof(string)),
                           .is_placeholder = 0});
}
bool Parser__check_types(Parser *p, string got, string expected, bool throw) {

  Parser_log(&/* ? */ *p, _STR("check types got=\"%.*s\" exp=\"%.*s\"  ",
                               got.len, got.str, expected.len, expected.str));

  if (p->pref->translated) {

    return 1;
  };

  if (string_eq(got, tos2("int")) && string_eq(expected, tos2("f32"))) {

    return 1;
  };

  if (string_eq(got, tos2("int")) && string_eq(expected, tos2("f64"))) {

    return 1;
  };

  if (string_eq(got, tos2("f64")) && string_eq(expected, tos2("f32"))) {

    return 1;
  };

  if (string_eq(got, tos2("f32")) && string_eq(expected, tos2("f64"))) {

    return 1;
  };

  if (string_eq(got, tos2("int")) && string_eq(expected, tos2("i64"))) {

    return 1;
  };

  if (string_eq(got, tos2("void*")) &&
      string_starts_with(expected, tos2("fn "))) {

    return 1;
  };

  if (string_starts_with(got, tos2("[")) &&
      string_eq(expected, tos2("byte*"))) {

    return 1;
  };

  if (string_eq(got, tos2("void*")) || string_eq(expected, tos2("void*"))) {

    if (p->pref->is_play) {

      return 0;
    };

    return 1;
  };

  if (string_eq(got, tos2("int")) && string_eq(expected, tos2("byte"))) {

    return 1;
  };

  if (string_eq(got, tos2("byteptr")) && string_eq(expected, tos2("byte*"))) {

    return 1;
  };

  if (string_eq(got, tos2("byte*")) && string_eq(expected, tos2("byteptr"))) {

    return 1;
  };

  if (string_eq(got, tos2("int")) && string_eq(expected, tos2("byte*"))) {

    return 1;
  };

  if (string_eq(got, tos2("int")) && string_eq(expected, tos2("byteptr"))) {

    return 1;
  };

  if (string_eq(got, tos2("Option")) &&
      string_starts_with(expected, tos2("Option_"))) {

    return 1;
  };

  if (string_eq(got, tos2("array")) &&
      string_starts_with(expected, tos2("array_"))) {

    return 1;
  };

  if (string_starts_with(expected, tos2("Option_")) &&
      string_ends_with(expected, got)) {

    return 1;
  };

  if (!p->pref->is_play) {

    if (string_ends_with(expected, tos2("*")) && string_eq(got, tos2("int"))) {

      return 1;
    };

    if (string_eq(expected, tos2("void*")) && string_eq(got, tos2("int"))) {

      return 1;
    };
  };

  expected = string_replace(expected, tos2("*"), tos2(""));

  got = string_replace(got, tos2("*"), tos2(""));

  if (string_ne(got, expected)) {

    if (string_ends_with(expected, tos2("er"))) {

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

  return Parser__check_types(p, got, expected, 1);
}
bool Parser_check_types_no_throw(Parser *p, string got, string expected) {

  return Parser__check_types(p, got, expected, 0);
}
bool Parser_satisfies_interface(Parser *p, string interface_name, string _typ,
                                bool throw) {

  Type *int_typ = Table_find_type(&/* ? */ *p->table, interface_name);

  Type *typ = Table_find_type(&/* ? */ *p->table, _typ);

  array_Fn tmp51 = int_typ->methods;
  ;
  for (int tmp52 = 0; tmp52 < tmp51.len; tmp52++) {
    Fn method = ((Fn *)tmp51.data)[tmp52];

    if (!Type_has_method(&/* ? */ *typ, method.name)) {

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

  if (string_starts_with(typ, tos2("array_"))) {

    typ = string_right(typ, 6);

    return _STR("new_array(0, 1, sizeof(%.*s))", typ.len, typ.str);
  };

  if (string_ends_with(typ, tos2("*"))) {

    return tos2("0");
  };

  if (string_contains(typ, tos2("__"))) {

    return tos2("STRUCT_DEFAULT_VALUE");
  };

  if (string_eq(typ, tos2("bool"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("string"))) { /* case */

    return tos2("tos(\"\", 0)");

  } else if (string_eq(typ, tos2("i8"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("i16"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("i32"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("i64"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("u8"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("u16"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("u32"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("u64"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("byte"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("int"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("rune"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("f32"))) { /* case */

    return tos2("0.0");

  } else if (string_eq(typ, tos2("f64"))) { /* case */

    return tos2("0.0");

  } else if (string_eq(typ, tos2("byteptr"))) { /* case */

    return tos2("0");

  } else if (string_eq(typ, tos2("voidptr"))) { /* case */

    return tos2("0");
  };

  return tos2("STRUCT_DEFAULT_VALUE");
}
bool Table_is_interface(Table *t, string name) {

  array_Type tmp53 = t->types;
  ;
  for (int tmp54 = 0; tmp54 < tmp53.len; tmp54++) {
    Type typ = ((Type *)tmp53.data)[tmp54];

    if (typ.is_interface && string_eq(typ.name, name)) {

      return 1;
    };
  };

  return 0;
}
bool Table_main_exists(Table *t) {

  map_Fn tmp55 = t->fns;
  array_string keys_tmp55 = map_keys(&tmp55);
  for (int l = 0; l < keys_tmp55.len; l++) {
    string _ = ((string *)keys_tmp55.data)[l];
    Fn f = {0};
    map_get(tmp55, _, &f);

    if (string_eq(f.name, tos2("main"))) {

      return 1;
    };
  };

  return 0;
}
Var Table_find_const(Table *t, string name) {

  array_Var tmp56 = t->consts;
  ;
  for (int tmp57 = 0; tmp57 < tmp56.len; tmp57++) {
    Var c = ((Var *)tmp56.data)[tmp57];

    if (string_eq(c.name, name)) {

      return c;
    };
  };

  return (Var){.typ = tos("", 0),
               .name = tos("", 0),
               .is_arg = 0,
               .is_const = 0,
               .is_import_const = 0,
               .args = new_array(0, 1, sizeof(Var)),
               .attr = tos("", 0),
               .is_mut = 0,
               .is_alloc = 0,
               .ptr = 0,
               .ref = 0,
               .parent_fn = tos("", 0),
               .mod = tos("", 0),
               .line_nr = 0,
               .is_global = 0,
               .is_used = 0,
               .scope_level = 0};
}
string Table_cgen_name(Table *table, Fn *f) {

  string name = f->name;

  if (f->is_method) {

    name = _STR("%.*s_%.*s", f->receiver_typ.len, f->receiver_typ.str,
                f->name.len, f->name.str);

    name = string_replace(name, tos2(" "), tos2(""));

    name = string_replace(name, tos2("*"), tos2(""));

    name = string_replace(name, tos2("+"), tos2("plus"));

    name = string_replace(name, tos2("-"), tos2("minus"));
  };

  if (string_eq(f->pkg, tos2("builtin")) &&
      array_string_contains(main__CReserved, f->name)) {

    return _STR("v_%.*s", name.len, name.str);
  };

  if (table->obfuscate && string_ne(f->name, tos2("main")) &&
      string_ne(f->name, tos2("WinMain")) &&
      string_ne(f->pkg, tos2("builtin")) && !f->is_c &&
      string_ne(f->pkg, tos2("darwin")) && string_ne(f->pkg, tos2("os")) &&
      !string_contains(f->name, tos2("window_proc")) &&
      string_ne(f->name, tos2("gg__vec2")) &&
      string_ne(f->name, tos2("build_token_str")) &&
      string_ne(f->name, tos2("build_keys")) &&
      string_ne(f->pkg, tos2("json")) &&
      !string_ends_with(name, tos2("_str")) &&
      !string_contains(name, tos2("contains"))) {

    int tmp59 = 0;
    bool tmp60 = map_get(table->obf_ids, name, &tmp59);

    int idx = tmp59;

    if (idx == 0) {

      table->fn_cnt++;

      int tmp62 = table->fn_cnt;

      map__set(&table->obf_ids, name, &tmp62);

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

    string tmp = string_all_after(typ, tos2("]"));

    string size = string_all_before(typ, tos2("]"));

    return _STR("%.*s %.*s  %.*s ]", tmp.len, tmp.str, name.len, name.str,
                size.len, size.str);

  } else if (string_starts_with(typ, tos2("fn ("))) {

    Type *T = Table_find_type(&/* ? */ *table, typ);

    if (string_eq(T->name, tos2(""))) {

      println(tos2("this should never happen"));

      v_exit(1);
    };

    string str_args = Fn_str_args(&/* ? */ T->func, table);

    return _STR("%.*s (*%.*s)( %.*s /*FFF*/ )", T->func.typ.len,
                T->func.typ.str, name.len, name.str, str_args.len,
                str_args.str);

  } else if (string_eq(typ, tos2("tm"))) {

    return _STR("struct /*TM*/ tm %.*s", name.len, name.str);
  };

  return _STR("%.*s %.*s", typ.len, typ.str, name.len, name.str);
}
bool is_valid_int_const(string val, string typ) {

  int x = string_int(val);

  if (string_eq(typ, tos2("byte")) || string_eq(typ, tos2("u8"))) { /* case */

    return 0 <= x && x <= math__MaxU8;

  } else if (string_eq(typ, tos2("u16"))) { /* case */

    return 0 <= x && x <= math__MaxU16;

  } else if (string_eq(typ, tos2("i8"))) { /* case */

    return math__MinI8 <= x && x <= math__MaxI8;

  } else if (string_eq(typ, tos2("i16"))) { /* case */

    return math__MinI16 <= x && x <= math__MaxI16;

  } else if (string_eq(typ, tos2("int")) ||
             string_eq(typ, tos2("i32"))) { /* case */

    return math__MinI32 <= x && x <= math__MaxI32;
  };

  return 1;
}
string Table_qualify_module(Table *table, string mod, string file_path) {

  array_string tmp71 = table->imports;
  ;
  for (int tmp72 = 0; tmp72 < tmp71.len; tmp72++) {
    string m = ((string *)tmp71.data)[tmp72];

    if (string_contains(m, tos2(".")) && string_contains(m, mod)) {

      array_string m_parts = string_split(m, tos2("."));

      string m_path = array_string_join(m_parts, tos2("/"));

      if (string_eq(mod, (*(string *)array__get(m_parts, m_parts.len - 1))) &&
          string_contains(file_path, m_path)) {

        return m;
      };
    };
  };

  return mod;
}
FileImportTable *new_file_import_table(string file_path) {

  FileImportTable *t =
      ALLOC_INIT(FileImportTable, {
                                      .file_path = file_path,
                                      .imports = new_map(1, sizeof(string)),
                                      .module_name = tos("", 0),
                                  });

  return t;
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

    v_panic(_STR("cannot import %.*s as %.*s: import name %.*s already in use "
                 "in \"%.*s\".",
                 mod.len, mod.str, alias.len, alias.str, alias.len, alias.str,
                 fit->file_path.len, fit->file_path.str));

    return;
  };

  string tmp78 = mod;

  map__set(&fit->imports, alias, &tmp78);
}
bool FileImportTable_known_alias(FileImportTable *fit, string alias) {

  return _IN_MAP(alias, fit->imports);
}
bool FileImportTable_is_aliased(FileImportTable *fit, string mod) {

  map_string tmp79 = fit->imports;
  array_string keys_tmp79 = map_keys(&tmp79);
  for (int l = 0; l < keys_tmp79.len; l++) {
    string _ = ((string *)keys_tmp79.data)[l];
    string val = {0};
    map_get(tmp79, _, &val);

    if (string_eq(val, mod)) {

      return 1;
    };
  };

  return 0;
}
string FileImportTable_resolve_alias(FileImportTable *fit, string alias) {

  string tmp80 = tos("", 0);
  bool tmp81 = map_get(fit->imports, alias, &tmp80);

  if (!tmp81)
    tmp80 = tos("", 0);

  return tmp80;
}
map_int build_keys() {

  map_int res = new_map(1, sizeof(int));

  for (int t = ((int)(main__Token_keyword_beg)) + 1;
       t < ((int)(main__Token_keyword_end)); t++) {

    string key = (*(string *)array__get(main__TokenStr, t));

    int tmp6 = ((int)(t));

    map__set(&res, key, &tmp6);
  };

  return res;
}
array_string build_token_str() {

  string tmp7 = tos2("");

  array_string s = array_repeat(&tmp7, main__NrTokens, sizeof(string));

  string tmp9 = tos2("");

  array_set(&/*q*/ s, main__Token_keyword_beg, &tmp9);

  string tmp10 = tos2("");

  array_set(&/*q*/ s, main__Token_keyword_end, &tmp10);

  string tmp11 = tos2(".eof");

  array_set(&/*q*/ s, main__Token_eof, &tmp11);

  string tmp12 = tos2(".name");

  array_set(&/*q*/ s, main__Token_name, &tmp12);

  string tmp13 = tos2(".number");

  array_set(&/*q*/ s, main__Token_number, &tmp13);

  string tmp14 = tos2("STR");

  array_set(&/*q*/ s, main__Token_str, &tmp14);

  string tmp15 = tos2(".chartoken");

  array_set(&/*q*/ s, main__Token_chartoken, &tmp15);

  string tmp16 = tos2("+");

  array_set(&/*q*/ s, main__Token_plus, &tmp16);

  string tmp17 = tos2("-");

  array_set(&/*q*/ s, main__Token_minus, &tmp17);

  string tmp18 = tos2("*");

  array_set(&/*q*/ s, main__Token_mul, &tmp18);

  string tmp19 = tos2("/");

  array_set(&/*q*/ s, main__Token_div, &tmp19);

  string tmp20 = tos2("%");

  array_set(&/*q*/ s, main__Token_mod, &tmp20);

  string tmp21 = tos2("^");

  array_set(&/*q*/ s, main__Token_xor, &tmp21);

  string tmp22 = tos2("~");

  array_set(&/*q*/ s, main__Token_bit_not, &tmp22);

  string tmp23 = tos2("|");

  array_set(&/*q*/ s, main__Token_pipe, &tmp23);

  string tmp24 = tos2("#");

  array_set(&/*q*/ s, main__Token_hash, &tmp24);

  string tmp25 = tos2("&");

  array_set(&/*q*/ s, main__Token_amp, &tmp25);

  string tmp26 = tos2("++");

  array_set(&/*q*/ s, main__Token_inc, &tmp26);

  string tmp27 = tos2("--");

  array_set(&/*q*/ s, main__Token_dec, &tmp27);

  string tmp28 = tos2("&&");

  array_set(&/*q*/ s, main__Token_and, &tmp28);

  string tmp29 = tos2("||");

  array_set(&/*q*/ s, main__Token_logical_or, &tmp29);

  string tmp30 = tos2("!");

  array_set(&/*q*/ s, main__Token_not, &tmp30);

  string tmp31 = tos2(".");

  array_set(&/*q*/ s, main__Token_dot, &tmp31);

  string tmp32 = tos2("..");

  array_set(&/*q*/ s, main__Token_dotdot, &tmp32);

  string tmp33 = tos2(",");

  array_set(&/*q*/ s, main__Token_comma, &tmp33);

  string tmp34 = tos2(";");

  array_set(&/*q*/ s, main__Token_semicolon, &tmp34);

  string tmp35 = tos2(":");

  array_set(&/*q*/ s, main__Token_colon, &tmp35);

  string tmp36 = tos2("=>");

  array_set(&/*q*/ s, main__Token_arrow, &tmp36);

  string tmp37 = tos2("=");

  array_set(&/*q*/ s, main__Token_assign, &tmp37);

  string tmp38 = tos2(":=");

  array_set(&/*q*/ s, main__Token_decl_assign, &tmp38);

  string tmp39 = tos2("+=");

  array_set(&/*q*/ s, main__Token_plus_assign, &tmp39);

  string tmp40 = tos2("-=");

  array_set(&/*q*/ s, main__Token_minus_assign, &tmp40);

  string tmp41 = tos2("*=");

  array_set(&/*q*/ s, main__Token_mult_assign, &tmp41);

  string tmp42 = tos2("/=");

  array_set(&/*q*/ s, main__Token_div_assign, &tmp42);

  string tmp43 = tos2("^=");

  array_set(&/*q*/ s, main__Token_xor_assign, &tmp43);

  string tmp44 = tos2("%=");

  array_set(&/*q*/ s, main__Token_mod_assign, &tmp44);

  string tmp45 = tos2("|=");

  array_set(&/*q*/ s, main__Token_or_assign, &tmp45);

  string tmp46 = tos2("&=");

  array_set(&/*q*/ s, main__Token_and_assign, &tmp46);

  string tmp47 = tos2(">>=");

  array_set(&/*q*/ s, main__Token_righ_shift_assign, &tmp47);

  string tmp48 = tos2("<<=");

  array_set(&/*q*/ s, main__Token_left_shift_assign, &tmp48);

  string tmp49 = tos2("{");

  array_set(&/*q*/ s, main__Token_lcbr, &tmp49);

  string tmp50 = tos2("}");

  array_set(&/*q*/ s, main__Token_rcbr, &tmp50);

  string tmp51 = tos2("(");

  array_set(&/*q*/ s, main__Token_lpar, &tmp51);

  string tmp52 = tos2(")");

  array_set(&/*q*/ s, main__Token_rpar, &tmp52);

  string tmp53 = tos2("[");

  array_set(&/*q*/ s, main__Token_lsbr, &tmp53);

  string tmp54 = tos2("]");

  array_set(&/*q*/ s, main__Token_rsbr, &tmp54);

  string tmp55 = tos2("==");

  array_set(&/*q*/ s, main__Token_eq, &tmp55);

  string tmp56 = tos2("!=");

  array_set(&/*q*/ s, main__Token_ne, &tmp56);

  string tmp57 = tos2(">");

  array_set(&/*q*/ s, main__Token_gt, &tmp57);

  string tmp58 = tos2("<");

  array_set(&/*q*/ s, main__Token_lt, &tmp58);

  string tmp59 = tos2(">=");

  array_set(&/*q*/ s, main__Token_ge, &tmp59);

  string tmp60 = tos2("<=");

  array_set(&/*q*/ s, main__Token_le, &tmp60);

  string tmp61 = tos2("?");

  array_set(&/*q*/ s, main__Token_question, &tmp61);

  string tmp62 = tos2("<<");

  array_set(&/*q*/ s, main__Token_left_shift, &tmp62);

  string tmp63 = tos2(">>");

  array_set(&/*q*/ s, main__Token_righ_shift, &tmp63);

  string tmp64 = tos2("NLL");

  array_set(&/*q*/ s, main__Token_nl, &tmp64);

  string tmp65 = tos2("$");

  array_set(&/*q*/ s, main__Token_dollar, &tmp65);

  string tmp66 = tos2("assert");

  array_set(&/*q*/ s, main__Token_key_assert, &tmp66);

  string tmp67 = tos2("struct");

  array_set(&/*q*/ s, main__Token_key_struct, &tmp67);

  string tmp68 = tos2("if");

  array_set(&/*q*/ s, main__Token_key_if, &tmp68);

  string tmp69 = tos2("else");

  array_set(&/*q*/ s, main__Token_key_else, &tmp69);

  string tmp70 = tos2("return");

  array_set(&/*q*/ s, main__Token_key_return, &tmp70);

  string tmp71 = tos2("module");

  array_set(&/*q*/ s, main__Token_key_module, &tmp71);

  string tmp72 = tos2("sizeof");

  array_set(&/*q*/ s, main__Token_key_sizeof, &tmp72);

  string tmp73 = tos2("go");

  array_set(&/*q*/ s, main__Token_key_go, &tmp73);

  string tmp74 = tos2("goto");

  array_set(&/*q*/ s, main__Token_key_goto, &tmp74);

  string tmp75 = tos2("const");

  array_set(&/*q*/ s, main__Token_key_const, &tmp75);

  string tmp76 = tos2("mut");

  array_set(&/*q*/ s, main__Token_key_mut, &tmp76);

  string tmp77 = tos2("type");

  array_set(&/*q*/ s, main__Token_key_type, &tmp77);

  string tmp78 = tos2("for");

  array_set(&/*q*/ s, main__Token_key_for, &tmp78);

  string tmp79 = tos2("switch");

  array_set(&/*q*/ s, main__Token_key_switch, &tmp79);

  string tmp80 = tos2("case");

  array_set(&/*q*/ s, main__Token_key_case, &tmp80);

  string tmp81 = tos2("fn");

  array_set(&/*q*/ s, main__Token_func, &tmp81);

  string tmp82 = tos2("true");

  array_set(&/*q*/ s, main__Token_key_true, &tmp82);

  string tmp83 = tos2("false");

  array_set(&/*q*/ s, main__Token_key_false, &tmp83);

  string tmp84 = tos2("continue");

  array_set(&/*q*/ s, main__Token_key_continue, &tmp84);

  string tmp85 = tos2("break");

  array_set(&/*q*/ s, main__Token_key_break, &tmp85);

  string tmp86 = tos2("import");

  array_set(&/*q*/ s, main__Token_key_import, &tmp86);

  string tmp87 = tos2("embed");

  array_set(&/*q*/ s, main__Token_key_embed, &tmp87);

  string tmp88 = tos2("default");

  array_set(&/*q*/ s, main__Token_key_default, &tmp88);

  string tmp89 = tos2("enum");

  array_set(&/*q*/ s, main__Token_key_enum, &tmp89);

  string tmp90 = tos2("interface");

  array_set(&/*q*/ s, main__Token_key_interface, &tmp90);

  string tmp91 = tos2("pub");

  array_set(&/*q*/ s, main__Token_key_pub, &tmp91);

  string tmp92 = tos2("import_const");

  array_set(&/*q*/ s, main__Token_key_import_const, &tmp92);

  string tmp93 = tos2("in");

  array_set(&/*q*/ s, main__Token_key_in, &tmp93);

  string tmp94 = tos2("atomic");

  array_set(&/*q*/ s, main__Token_key_atomic, &tmp94);

  string tmp95 = tos2("or");

  array_set(&/*q*/ s, main__Token_key_orelse, &tmp95);

  string tmp96 = tos2("__global");

  array_set(&/*q*/ s, main__Token_key_global, &tmp96);

  string tmp97 = tos2("union");

  array_set(&/*q*/ s, main__Token_key_union, &tmp97);

  string tmp98 = tos2("static");

  array_set(&/*q*/ s, main__Token_key_static, &tmp98);

  string tmp99 = tos2("as");

  array_set(&/*q*/ s, main__Token_key_as, &tmp99);

  string tmp100 = tos2("defer");

  array_set(&/*q*/ s, main__Token_key_defer, &tmp100);

  string tmp101 = tos2("match");

  array_set(&/*q*/ s, main__Token_key_match, &tmp101);

  return s;
}
Token key_to_token(string key) {

  int tmp102 = 0;
  bool tmp103 = map_get(main__KEYWORDS, key, &tmp102);

  Token a = ((Token)(tmp102));

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

  array_Token tmp107 = t;
  ;
  for (int tmp108 = 0; tmp108 < tmp107.len; tmp108++) {
    Token tt = ((Token *)tmp107.data)[tmp108];

    if (tt == val) {

      return 1;
    };
  };

  return 0;
}
void init_consts() {
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
  os__args = new_array_from_c_array(0, 0, sizeof(string),
                                    (string[]){EMPTY_STRUCT_INIT});
  os__PathSeparator = tos2("/");
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
  time__Months = tos2("JanFebMarAprMayJunJulAugSepOctNovDec");
  time__Days = tos2("MonTueWedThuFriSatSun");
  main__Version = tos2("0.1.16");
  main__SupportedPlatforms = new_array_from_c_array(
      8, 8, sizeof(string),
      (string[]){tos2("windows"), tos2("mac"), tos2("linux"), tos2("freebsd"),
                 tos2("openbsd"), tos2("netbsd"), tos2("dragonfly"),
                 tos2("msvc")});
  main__ModPath = modules_path();
  main__HelpText = tos2(
      "\nUsage: v [options] [file | directory]\n\nOptions:\n  -                "
      " Read from stdin (Default; Interactive mode if in a tty)\n  -h, help    "
      "      Display this information.\n  -v, version       Display compiler "
      "version.\n  -lib              Generate object file.\n  -prod            "
      " Build an optimized executable.\n  -o <file>         Place output into "
      "<file>.\n  -obf              Obfuscate the resulting binary.\n  "
      "-show_c_cmd       Print the full C compilation command and how much "
      "time it took. \n  -debug            Leave a C file for debugging in "
      ".program.c. \n  -live             Enable hot code reloading (required "
      "by functions marked with [live]). \n  fmt               Run vfmt to "
      "format the source code. \n  run               Build and execute a V "
      "program. You can add arguments after the file name.\n\n\nFiles:\n  "
      "<file>_test.v     Test file.\n");
  main__EmptyFn = ALLOC_INIT(Fn, {.name = tos("", 0),
                                  .pkg = tos("", 0),
                                  .local_vars = new_array(0, 1, sizeof(Var)),
                                  .var_idx = 0,
                                  .args = new_array(0, 1, sizeof(Var)),
                                  .is_interface = 0,
                                  .scope_level = 0,
                                  .typ = tos("", 0),
                                  .is_c = 0,
                                  .receiver_typ = tos("", 0),
                                  .is_public = 0,
                                  .is_method = 0,
                                  .returns_error = 0,
                                  .is_decl = 0,
                                  .defer_text = tos("", 0)});
  main__MainFn = ALLOC_INIT(Fn, {.name = tos2("main"),
                                 .pkg = tos("", 0),
                                 .local_vars = new_array(0, 1, sizeof(Var)),
                                 .var_idx = 0,
                                 .args = new_array(0, 1, sizeof(Var)),
                                 .is_interface = 0,
                                 .scope_level = 0,
                                 .typ = tos("", 0),
                                 .is_c = 0,
                                 .receiver_typ = tos("", 0),
                                 .is_public = 0,
                                 .is_method = 0,
                                 .returns_error = 0,
                                 .is_decl = 0,
                                 .defer_text = tos("", 0)});
  main__CReserved = new_array_from_c_array(
      10, 10, sizeof(string),
      (string[]){tos2("exit"), tos2("unix"), tos2("print"), tos2("error"),
                 tos2("malloc"), tos2("calloc"), tos2("char"), tos2("free"),
                 tos2("panic"), tos2("register")});
  main__NUMBER_TYPES = new_array_from_c_array(
      13, 13, sizeof(string),
      (string[]){tos2("number"), tos2("int"), tos2("i8"), tos2("u8"),
                 tos2("i16"), tos2("u16"), tos2("i32"), tos2("u32"),
                 tos2("byte"), tos2("i64"), tos2("u64"), tos2("f32"),
                 tos2("f64")});
  main__FLOAT_TYPES = new_array_from_c_array(
      2, 2, sizeof(string), (string[]){tos2("f32"), tos2("f64")});
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
  vsprintf(buf, fmt, argptr);
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
  size_t len = vsnprintf(0, 0, fmt, argptr) + 1;
  va_end(argptr);
  va_start(argptr, fmt);
  vsprintf(g_str_buf, fmt, argptr);
  va_end(argptr);
#ifdef DEBUG_ALLOC
  // puts("_STR_TMP:");
  // puts(g_str_buf);
#endif
  return tos2(g_str_buf);
}
