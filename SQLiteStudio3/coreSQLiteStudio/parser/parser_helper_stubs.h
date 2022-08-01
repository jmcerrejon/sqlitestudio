#ifndef PARSER_HELPER_STUBS_H
#define PARSER_HELPER_STUBS_H

#include "parsercontext.h"
#include "ast/sqlitebegintrans.h"
#include "ast/sqlitecreatetable.h"
#include "ast/sqliteconflictalgo.h"
#include "ast/sqliteselect.h"
#include "ast/sqliteindexedcolumn.h"
#include "ast/sqliteforeignkey.h"
#include "ast/sqliteorderby.h"
#include "ast/sqlitewindowdefinition.h"
#include "ast/sqlitewith.h"

#include <QString>
#include <QList>

/** @file
 *
 * This file contains only structures and functions
 * that are helpful in parsers generated by lemon,
 * because lemon uses C unions, therefore only primitive
 * types can be used as data type.
 * (see %type declarations in *.y files).
 */

/**
 * @brief Stores 'dbnm' grammar rule.
 */
struct ParserFullName
{
    QString name1 = QString();
    QString name2 = QString();
};

/**
 * @brief Stores <tt>EXPLAIN</tt> and <tt>QUERY PLAN</tt> grammar rules.
 */
struct ParserStubExplain
{
    ParserStubExplain(bool explain, bool queryPlan);

    bool explain;
    bool queryPlan;
};

/**
 * @brief Stores "<tt>OR</tt> conflict" grammar rules.
 */
struct ParserStubInsertOrReplace
{
    explicit ParserStubInsertOrReplace(bool replace);
    ParserStubInsertOrReplace(bool replace, SqliteConflictAlgo orConflict);

    bool replace;
    SqliteConflictAlgo orConflict;
};

/**
 * @brief Stores grammar rules for <tt>BEGIN/END/COMMIT/ROLLBACK</tt> additional parameters.
 */
struct ParserStubTransDetails
{
    QString name = QString();
    SqliteBeginTrans::Type type = SqliteBeginTrans::Type::null;
    bool transactionKw = false;
    bool toKw = false;
    SqliteConflictAlgo onConflict = SqliteConflictAlgo::null;
};

struct ParserStubCreateTableOption
{
    enum Type
    {
        WITHOUT_ROWID,
        STRICT
    };

    ParserStubCreateTableOption(Type type);

    Type type;
};

ParserStubCreateTableOption* parserStubFindCreateTableOption(const QList<ParserStubCreateTableOption*>& options, ParserStubCreateTableOption::Type type);

typedef QList<SqliteCreateTable::Column*> ParserCreateTableColumnList;
typedef QList<SqliteCreateTable::Constraint*> ParserCreateTableConstraintList;
typedef QList<SqliteCreateTable::Column::Constraint*> ParserCreateTableColumnConstraintList;
typedef QList<SqliteForeignKey::Condition*> ParserFkConditionList;
typedef QList<SqliteExpr*> ParserExprList;
typedef QList<SqliteWith::CommonTableExpression*> ParserCteList;
typedef QList<SqliteSelect::Core::ResultColumn*> ParserResultColumnList;
typedef QList<SqliteSelect::Core::JoinSourceOther*> ParserOtherSourceList;
typedef QList<SqliteOrderBy*> ParserOrderByList;
typedef QList<SqliteQuery*> ParserQueryList;
typedef QPair<QVariant,SqliteExpr*> ParserSetValue;
typedef QList<ParserSetValue> ParserSetValueList;
typedef QList<SqliteIndexedColumn*> ParserIndexedColumnList;
typedef QList<ParserExprList> ParserExprNestedList;
typedef QList<SqliteWindowDefinition*> ParserWindowDefList;
typedef QList<ParserStubCreateTableOption*> ParserCreateTableOptionList;

/**
 * @brief Stores parameters for defferable foreign keys.
 */
struct ParserDeferSubClause
{
    ParserDeferSubClause(SqliteDeferrable deferrable, SqliteInitially initially);

    SqliteInitially initially;
    SqliteDeferrable deferrable;
};

/**
 * @brief Stores "<tt>AS</tt> aliasName" grammar rule.
 */
struct ParserStubAlias
{
    ParserStubAlias(const QString& name, bool asKw);

    QString name = QString();
    bool asKw = false;
};

/**
 * @brief Stores <tt>NOT INDEXED/INDEXED BY</tt> grammar rules.
 */
struct ParserIndexedBy
{
    explicit ParserIndexedBy(const QString& name);
    explicit ParserIndexedBy(bool indexedBy);

    bool notIndexedKw = false;
    QString indexedBy = QString();
};

class ParserTermOrLiteral
{
    public:
        explicit ParserTermOrLiteral(const QString& name);
        explicit ParserTermOrLiteral(const QVariant& literal);

        QString toName() const;
        QVariant toLiteral() const;
        bool isName() const;
        bool isLiteral() const;

    private:
        QVariant value;
        bool nameMode = false;
};

#endif // PARSER_HELPER_STUBS_H
