#include "stdafx.h"
#include "Element.h"
#include "ElementManager.h"
#include "Modeler1View.h"
#include "MainFrm.h"
#include "XMLData.h"
#include "SQLiteTools.h"

//
// SQLiteTools
//

SQLiteTools::SQLiteTools()
{
}

SQLiteTools::~SQLiteTools()
{
}

bool SQLiteTools::CreateDatabase(std::string filename)
{
    bool bOk = true;

    try
    {
        SQLite::Database db;
        db.SetDatabaseName(filename);

        if (!db.Open())
            return false;

        db.SetBusyTimeout(100000);

        string sql = "CREATE TABLE Diagram (DiagramPK INTEGER PRIMARY KEY, "
            "LastUpdate DATETIME ,"
            "FileName VARCHAR(64), "
            "Json TEXT"
            ");";

        int rows = 0;
        if (!db.ExecuteSQL(sql, rows))
            return false;

#ifdef OLD
        sql = "CREATE TABLE Study (StudyPK INTEGER PRIMARY KEY,"
            "LastUpdate DATETIME,"
            "PatientFK INTEGER,"
            "UID CHAR(64), "
            "Date DATETIME, "
            "StudyID VARCHAR(16), "
            "AccessionNumber VARCHAR(64), "
            "Description VARCHAR(64)"
            ");";

        rows = 0;
        if (!db.ExecuteSQL(sql, rows))
            return false;

        sql = "CREATE TABLE Series (SeriesPK INTEGER PRIMARY KEY,"
            "LastUpdate DATETIME,"
            "StudyFK INTEGER,"
            "UID CHAR(64),"
            "Number INTEGER,"
            "Modality CHAR(16),"
            "Date DATETIME,"
            "Description VARCHAR(64)"
            ");";

        rows = 0;
        if (!db.ExecuteSQL(sql, rows))
            return false;

        sql = "CREATE TABLE Instance (InstancePK INTEGER PRIMARY KEY,"
            "LastUpdate DATETIME,"
            "SeriesFK INTEGER,"
            "Type INTEGER, "
            "UID CHAR(64), "
            "SOPClassUID CHAR(64), "
            "Date DATETIME, "
            "Number INTEGER, "
            "SourceFile VARCHAR(265), "
            "TransferSyntaxUID CHAR(64)"
            ");";

        rows = 0;
        if (!db.ExecuteSQL(sql, rows))
            return false;

        sql = "CREATE TABLE Equipment (EquipmentPK INTEGER PRIMARY KEY,"
            "LastUpdate DATETIME,"
            "SeriesFK INTEGER,"
            "ManufacturerName VARCHAR(64), "
            "ModelName VARCHAR(64),"
            "InstitutionName VARCHAR(64), "
            "DepartmentName VARCHAR(64),"
            "StationName VARCHAR(64)"
            ");";

        rows = 0;
        if (!db.ExecuteSQL(sql, rows))
            return false;

        sql = "CREATE TABLE Image (ImagePK INTEGER PRIMARY KEY,"
            "LastUpdate DATETIME,"
            "InstanceFK INTEGER,"
            "Comments TEXT,"
            "NbFrames INTEGER, "
            "NbRows INTEGER,"
            "NbColumns INTEGER,"
            "NbBits INTEGER"
            ");";

        rows = 0;
        if (!db.ExecuteSQL(sql, rows))
            return false;

        sql = "CREATE TABLE PresentationState (PresentationStatePK INTEGER PRIMARY KEY,"
            "LastUpdate DATETIME,"
            "InstanceFK INTEGER,"
            "Key TEXT,"
            "Value TEXT"
            ");";

        rows = 0;
        if (!db.ExecuteSQL(sql, rows))
            return false;
#endif

        db.SetBusyTimeout(100000);
        db.CreateAdminUser();
        db.Close();
    }
    catch (SQLite::DatabaseException ex)
    {
        string err = ex.ToString();
        wstring werr(err.begin(), err.end());
        AfxMessageBox(werr.c_str());
        return false;
    }
    return bOk;
}

bool SQLiteTools::IndexFiles(std::string path, std::string database)
{
    //DIR* dir = opendir(path.c_str());
    //dirent* dr;
    //bool bOk = true;
    //while ((dr = readdir(dir)) != NULL)
    //{
    //    string filename = dr->d_name;
    //    if (filename == "." || filename == "..")
    //        continue;
    //    if (strstr(filename.c_str(), ".dcm") == NULL)
    //        continue;

    //    printf("DCM File found: %s\n", filename.c_str());
    //    bOk &= AddFileToDatabase(path + filename, database);
    //}
    //closedir(dir);

    //return bOk;
    return true;
}

bool SQLiteTools::AddFileToDatabase(std::string filename, std::string database)
{
    return true;
}

bool SQLiteTools::InsertJson(CModeler1View* pView)
{
    return true;
}



//
// SQLiteQueryString
//

SQLiteQueryString::SQLiteQueryString()
{
}

SQLiteQueryString::~SQLiteQueryString()
{
}

std::string SQLiteQueryString::GetSQLQuery(const SQLiteQueryString::Enum& item)
{
    string sql = "";

    switch (item)
    {
    case Insert_Equipment:
        sql = "INSERT INTO Equipment VALUES (NULL, datetime('now'), ?, ?, ?, ?, ?, ?);";
        break;

    case Select_Equipment:
        sql = "SELECT e.LastUpdate, e.ManufacturerName, e.ModelName, e.InstitutionName, e.DepartmentName, e.StationName "
            "FROM Patient p, Study s, Series se, Equipment e "
            "WHERE p.PatientPK = s.PatientFK "
            "AND s.StudyPK = se.StudyFK "
            "AND se.SeriesPK = e.SeriesFK "
            "AND p.PatientPK =%ld;";
        break;

    case Insert_Image:
        sql = "INSERT INTO Image VALUES (NULL, datetime('now'), ?, ?, ?, ?, ?, ?);";
        break;

    case Insert_PresentationState:
        sql = "INSERT INTO PresentationState VALUES (NULL, datetime('now'), ?, ?, ?);";
        break;

    case Insert_Instance:
        sql = "INSERT INTO Instance VALUES (NULL, datetime('now'), ?, ?, ?, ?, ?, ?, ?, ?);";
        break;

    case Select_Instance:
        sql = "SELECT i.LastUpdate, i.Type, i.UID, i.SOPClassUID, i.Date, i.Number, i.SourceFile, i.TransferSyntaxUID "
            "FROM Patient p, Study s, Series se, Instance i "
            "WHERE p.PatientPK = s.PatientFK "
            "AND s.StudyPK = se.StudyFK "
            "AND se.SeriesPK = i.SeriesFK "
            "AND p.PatientPK = %ld;";
        break;

    case SelectSOPClass_Instance:
        sql = "SELECT i.SOPClassUID "
            "FROM Patient p, Study st, Series se, Instance i "
            "WHERE p.PatientPK = st.PatientFK "
            "AND st.StudyPK = se.StudyFK "
            "AND i.SeriesFK = se.SeriesPK "
            "AND p.PatientPK = %ld;";
        break;

    case Insert_Series:
        sql = "INSERT INTO Series VALUES (NULL, datetime('now'), ?, ?, ?, ?, ?, ?);";
        break;

    case Select_Series:
        sql = "SELECT se.LastUpdate, se.UID, se.Number, se.Modality, se.Date, se.Description "
            "FROM Patient p, Study s, Series se "
            "WHERE p.PatientPK = s.PatientFK "
            "AND s.StudyPK = se.StudyFK "
            "AND p.PatientPK =%ld;";
        break;

    case Insert_Study:
        sql = "INSERT INTO Study VALUES (NULL, datetime('now'), ?, ?, ?, ?, ?, ?);";
        break;

    case Select_Study:
        sql = "SELECT s.LastUpdate, s.UID, s.Date, s.StudyID, s.AccessionNumber, s.Description "
            "FROM Patient p, Study s "
            "WHERE p.PatientPK = s.PatientFK "
            "AND p.PatientPK = %ld;";
        break;

    case SelectCountByStudyID_Study:
        sql = "SELECT COUNT(*) "
            "FROM Patient p, Study s "
            "WHERE p.PatientPK = s.PatientFK "
            "AND s.StudyID LIKE '%s%%';";
        break;

    case SelectPatientPKByStudyID_Study:
        sql = "SELECT p.PatientPK "
            "FROM Patient p, Study s "
            "WHERE p.PatientPK = s.PatientFK "
            "AND s.StudyID LIKE '%s%%';";
        break;

    case Insert_Patient:
        sql = "INSERT INTO Patient VALUES (NULL, datetime('now'), ?, ?, ?, ?, ?, ?);";
        break;

    case Select_Patient:
        sql = "SELECT LastUpdate, PatientID, LastName, FirstName, Sex, BirthDate, SSN "
            "FROM Patient "
            "WHERE PatientPK = %ld;";
        break;

    case SelectCount_Patient:
        sql = "SELECT count(*) "
            "FROM Patient;";
        break;

    case SelectCountByLastName_Patient:
        sql = "SELECT count(*) "
            "FROM Patient "
            "WHERE LastName LIKE '%s%%';";
        break;

    case SelectPatientPKByLastName_Patient:
        sql = "SELECT PatientPK "
            "FROM Patient "
            "WHERE LastName LIKE '%s%%';";
        break;

    case SelectCountByFirstNameAndLastName_Patient:
        sql = "SELECT count(*) "
            "FROM Patient "
            "WHERE FirstName LIKE '%s%%' "
            "AND LastName LIKE '%s%%';";
        break;

    case SelectPatientPKByFirstNameAndLastName_Patient:
        sql = "SELECT PatientPK "
            "FROM Patient "
            "WHERE FirstName LIKE '%s%%' "
            "AND LastName LIKE '%s%%';";
        break;

    case SelectCountByPatientID_Patient:
        sql = "SELECT COUNT(*) "
            "FROM Patient "
            "WHERE PatientID LIKE '%s%%';";
        break;

    case SelectPatientPKByPatientID_Patient:
        sql = "SELECT PatientPK "
            "FROM Patient "
            "WHERE PatientID LIKE '%s%%';";
        break;

    case SelectCountByBirthDate_Patient:
        sql = "SELECT COUNT(*) "
            "FROM Patient "
            "WHERE BirthDate LIKE '%s%%';";
        break;

    case SelectPatientPKByBirthDate_Patient:
        sql = "SELECT PatientPK "
            "FROM Patient "
            "WHERE BirthDate LIKE '%s%%';";
        break;

    case SelectPatientPK_Patient:
        sql = "SELECT PatientPK FROM Patient;";
        break;

    case Insert_Diagram:
        sql = "INSERT INTO Diagram VALUES (NULL, datetime('now'), ?, ?);";
        break;

    case Update_Diagram:
        sql = "UPDATE Diagram SET Json=? WHERE DiagramPK=?;";
        break;
    }

    return sql;
}

//
// SQLiteDiagramEntity
//

SQLiteDiagramEntity::SQLiteDiagramEntity(SQLite::Database* pDatabase)
{
    m_pDatabase = pDatabase;
}

SQLiteDiagramEntity::~SQLiteDiagramEntity()
{
}

bool SQLiteDiagramEntity::InsertOrUpdate(int& id)
{
    string sql;

    if (id == 0)
    {
        // Insert
        sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::Insert_Diagram);

        SQLite::PreparedStmt stmt = m_pDatabase->CreatePreparedStmt(sql);
        stmt.SetStringParameter(1, this->FileName);
        stmt.SetStringParameter(2, this->Json);
        //stmt.SetNullParameter(6);

        int rows;
        if (!stmt.Execute(rows))
            return false;

        stmt.Close();

        id = m_pDatabase->GetLastRowID();
    }
    else
    {
        // Update
        sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::Update_Diagram);

        SQLite::PreparedStmt stmt = m_pDatabase->CreatePreparedStmt(sql);
        stmt.SetStringParameter(1, this->Json);
        stmt.SetIntegerParameter(2, id);
        //stmt.SetNullParameter(6);

        int rows;
        if (!stmt.Execute(rows))
            return false;

        stmt.Close();
    }

    return true;
}

bool SQLiteDiagramEntity::Select(long PatientPK)
{
    /*
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::Select_Patient);
    sprintf(szSql, sql.c_str(), PatientPK);

    SQLite::Query query;
    if (!m_pDatabase->ExecuteQuery(szSql, query))
        return false;

    this->LastUpdate = query.GetStringValue(0);
    this->PatientID = query.GetStringValue(1);
    this->FamilyName = query.GetStringValue(2);
    this->GivenName = query.GetStringValue(3);
    this->PatientSex = query.GetStringValue(4);
    this->PatientBirthDateTime = query.GetStringValue(5);
    */
    return true;
}

bool SQLiteDiagramEntity::SelectCount(int& count)
{
    /*
    //
    // Retrieve count(*)
    //
    string sql;
    sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectCount_Patient);

    //
    // Get the number of returned rows
    //
    count = m_pDatabase->ExecuteScalar(sql);
    */
    return true;
}

#ifdef OLD
bool SQLiteDiagramEntity::SelectCountByLastName(std::string LastName, int& count)
{
    //
    // Retrieve count(*)
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectCountByLastName_Patient);
    sprintf(szSql, sql.c_str(), LastName.c_str());

    //
    // Get the number of returned rows
    //
    count = m_db.ExecuteScalar(szSql);

    return true;
}

bool SQLiteDiagramEntity::SelectPatientPKByLastName(std::string LastName)
{
    //
    // Retrieve PatientPK from name
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectPatientPKByLastName_Patient);
    sprintf(szSql, sql.c_str(), LastName.c_str());

    SQLite::Query query;
    if (!m_db.ExecuteQuery(szSql, query))
        return false;

    this->PatientPK = 0;
    this->PatientPK = query.GetIntValue(0);

    return true;
}

bool SQLiteDiagramEntity::SelectCountByFirstNameAndLastName(std::string FirstName, std::string LastName, int& count)
{
    //
    // Retrieve count(*)
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectCountByFirstNameAndLastName_Patient);
    sprintf(szSql, sql.c_str(), FirstName.c_str(), LastName.c_str());

    //
    // Get the number of returned rows
    //
    count = m_db.ExecuteScalar(szSql);

    return true;
}

bool SQLiteDiagramEntity::SelectPatientPKByFirstNameAndLastName(std::string FirstName, std::string LastName)
{
    //
    // Retrieve PatientPK from fname and lname
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectPatientPKByFirstNameAndLastName_Patient);
    sprintf(szSql, sql.c_str(), FirstName.c_str(), LastName.c_str());

    SQLite::Query query;
    if (!m_db.ExecuteQuery(szSql, query))
        return false;

    this->PatientPK = 0;
    this->PatientPK = query.GetIntValue(0);

    return true;
}

bool SQLiteDiagramEntity::SelectCountByPatientID(std::string PatientID, int& count)
{
    //
    // Retrieve count(*)
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectCountByPatientID_Patient);
    sprintf(szSql, sql.c_str(), PatientID.c_str());

    //
    // Get the number of returned rows
    //
    count = m_db.ExecuteScalar(szSql);

    return true;
}

bool SQLiteDiagramEntity::SelectPatientPKByPatientID(std::string PatientID)
{
    //
    // Retrieve PatientPK from PatientID
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectPatientPKByPatientID_Patient);
    sprintf(szSql, sql.c_str(), PatientID.c_str());

    SQLite::Query query;
    if (!m_db.ExecuteQuery(szSql, query))
        return false;

    this->PatientPK = 0;
    this->PatientPK = query.GetIntValue(0);

    return true;
}

bool SQLiteDiagramEntity::SelectCountByBirthDate(std::string BirthDate, int& count)
{
    //
    // Retrieve count(*)
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectCountByBirthDate_Patient);
    sprintf(szSql, sql.c_str(), BirthDate.c_str());


    //
    // Get the number of returned rows
    //
    count = m_db.ExecuteScalar(szSql);

    return true;
}

bool SQLiteDiagramEntity::SelectPatientPKByBirthDate(std::string BirthDate)
{
    //
    // Retrieve PatientPK from BirthDate
    //
    char szSql[512];
    string sql = SQLiteQueryString::GetSQLQuery(SQLiteQueryString::SelectPatientPKByBirthDate_Patient);
    sprintf(szSql, sql.c_str(), BirthDate.c_str());

    SQLite::Query query;
    if (!m_db.ExecuteQuery(szSql, query))
        return false;

    this->PatientPK = 0;
    this->PatientPK = query.GetIntValue(0);

    return true;
}

#endif