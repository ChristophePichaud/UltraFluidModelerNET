#pragma once

class CModeler1View;

class SQLiteQueryString
{
protected:

public:
    enum Enum
    {
        Insert_Equipment,
        Select_Equipment,
        Insert_Image,
        Insert_PresentationState,
        Insert_Instance,
        Select_Instance,
        SelectSOPClass_Instance,
        Insert_Series,
        Select_Series,
        Insert_Study,
        Select_Study,
        SelectCountByStudyID_Study,
        SelectPatientPKByStudyID_Study,
        Insert_Patient,
        Select_Patient,
        SelectCount_Patient,
        SelectCountByLastName_Patient,
        SelectPatientPKByLastName_Patient,
        SelectCountByFirstNameAndLastName_Patient,
        SelectPatientPKByFirstNameAndLastName_Patient,
        SelectCountByPatientID_Patient,
        SelectPatientPKByPatientID_Patient,
        SelectCountByBirthDate_Patient,
        SelectPatientPKByBirthDate_Patient,
        SelectPatientPK_Patient,

        Insert_Diagram,
        Update_Diagram,
        None
    };

public:
    SQLiteQueryString();
    virtual ~SQLiteQueryString();

    static std::string GetSQLQuery(const SQLiteQueryString::Enum& item);

public:
};

class SQLiteTools
{
public:
    SQLiteTools();
    virtual~SQLiteTools();

public:
    bool CreateDatabase(std::string filename);
    bool IndexFiles(std::string path, std::string database);
    bool AddFileToDatabase(std::string filename, std::string database);

    bool InsertJson(CModeler1View* pView);
};

class SQLiteDiagramEntity
{
public:
    SQLiteDiagramEntity(SQLite::Database* pDatabase);
    virtual ~SQLiteDiagramEntity();

public:
    long DiagramPK;
    std::string LastUpdate;
    std::string FileName;
    std::string Json;

protected:
    SQLite::Database* m_pDatabase;

public:
    bool InsertOrUpdate(int& id);
    bool Select(long PatientPK);
    bool SelectCount(int& count);
};
