

#include "table.h"

class PythonTable : public Table
{
private:

    Array<const char *> type_name,
                        array_name;

    virtual TypeId Type(int min, int max)
    {
        if (min >= SCHAR_MIN && max <= SCHAR_MAX)
            return I8;
        if (min >= 0 && max <= USHRT_MAX)
            return U16;
        if (min >= SHRT_MIN && max <= SHRT_MAX)
            return I16;
        return I32;
    }

    TextBuffer des_buffer; // deserialize buffer
    UnbufferedTextFile prs_buffer;
    UnbufferedBinaryFile data_buffer;

    void PrintHeader(const char *, const char *, const char * = "");
    void PrintTrailer();
    void PrintTrailerAndVariable(const char *, const char *);
    void PrintIntsSubrange(int, int, Array<int> &);
    void Print(IntArrayInfo &);
    void PrintNames(void);
 
  
    void non_terminal_action(void);
    void non_terminal_no_goto_default_action(void);
    void terminal_action(void);
    void terminal_shift_default_action(void);
    void init_file(FILE **, const char *);
    void init_parser_files(void);
    void exit_parser_files(void);
  
    void print_symbols(void);
    void print_exports(void);
    void print_definition(const char *, const char *, int);
    void print_definition(const char *, const char *, bool);
    void print_definitions(void);
    void print_externs(void);
    void print_source_tables(void);
 

public:

    PythonTable(Control *control_, Pda *pda_) : Table(control_, pda_),
                                              prs_buffer(&sysprs),
                                              data_buffer(&sysdat)
    {
        type_name.Resize(num_type_ids);
        array_name.Resize(num_name_ids);

        type_name[B] = type_name[I8] = "int";
        type_name[I16] = "int";
        type_name[U8] = type_name[U16] = "int";
        type_name[I32] = "int";

        array_name[NULLABLES] = "isNullable";
        array_name[PROSTHESES_INDEX] = "prosthesesIndex";
        array_name[KEYWORDS] = "isKeyword";
        array_name[BASE_CHECK] = "baseCheck";
        array_name[BASE_ACTION] = "baseAction";
        array_name[TERM_CHECK] = "termCheck";
        array_name[TERM_ACTION] = "termAction";
        array_name[DEFAULT_GOTO] = "defaultGoto";
        array_name[DEFAULT_REDUCE] = "defaultReduce";
        array_name[SHIFT_STATE] = "shiftState";
        array_name[SHIFT_CHECK] = "shiftCheck";
        array_name[DEFAULT_SHIFT] = "defaultShift";
        array_name[ACTION_SYMBOLS_BASE] = "asb";
        array_name[ACTION_SYMBOLS_RANGE] = "asr";
        array_name[NACTION_SYMBOLS_BASE] = "nasb";
        array_name[NACTION_SYMBOLS_RANGE] = "nasr";
        array_name[TERMINAL_INDEX] = "terminalIndex";
        array_name[NONTERMINAL_INDEX] = "nonterminalIndex";
        array_name[SCOPE_PREFIX] = "scopePrefix";
        array_name[SCOPE_SUFFIX] = "scopeSuffix";
        array_name[SCOPE_LHS_SYMBOL] = "scopeLhs";
        array_name[SCOPE_LOOK_AHEAD] = "scopeLa";
        array_name[SCOPE_STATE_SET] = "scopeStateSet";
        array_name[SCOPE_RIGHT_SIDE] = "scopeRhs";
        array_name[SCOPE_STATE] = "scopeState";
        array_name[IN_SYMB] = "inSymb";
        array_name[NAME_START] = "!?";
    }

    virtual ~PythonTable() {}

    virtual void PrintTables(void);
};


