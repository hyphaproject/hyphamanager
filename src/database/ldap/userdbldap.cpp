#include <QtCore/QMutex>
#include "../../settings/databasesettings.h"

#include "userdbldap.h"
#include <QDebug>
#include <QtCore/QList>
#include <QtCore/QString>

UserDBLDAP::UserDBLDAP(UserDatabaseSettings *settings, QObject *parent) : UserDatabase(settings, parent)
{
    ld = NULL;
}

UserDBLDAP::~UserDBLDAP()
{
    if(ld)
        ldap_unbind_ext(ld, NULL, NULL);
}

bool UserDBLDAP::connect()
{
    int version = LDAP_VERSION3;
    int res;

    UserDatabaseSettings *dbs = settings;
    QString url("ldap://"+dbs->getHost()+":389");
    QString ldapbinddn(""+dbs->getUser()+","+dbs->getDatabase());
    res = ldap_initialize(&ld, url.toStdString().c_str());
    if (res != LDAP_SUCCESS)
    {
        qDebug("wrong init");
        ld = NULL;
        return false;
    }
    res = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, (void *)&version);
    if (res != LDAP_SUCCESS)
    {
        qDebug("failed set option v3");
        ldap_unbind_ext(ld, NULL, NULL);
        ld = NULL;
        return false;
    }

    char* authpass = strdup(dbs->getPassword().toStdString().c_str());
    struct berval passwd;
    passwd.bv_val = authpass;
    passwd.bv_len = dbs->getPassword().toStdString().length();
    res = ldap_sasl_bind_s(ld, ldapbinddn.toStdString().c_str(), LDAP_SASL_SIMPLE, &passwd, NULL, NULL, NULL);
    if (res != LDAP_SUCCESS)
    {
        qDebug("failed to bind to ");
        qDebug(ldapbinddn.toStdString().c_str());
        free(authpass);
        ldap_unbind_ext(ld, NULL, NULL);
        ld = NULL;
        return false;
    }
    free(authpass);

    return true;
}

QList<QString> UserDBLDAP::getUsers(){
    QList<QString> users;
    if(ld){
        UserDatabaseSettings *dbs = settings;
        QString filter("objectClass=person");
        char *attrs[] = { strdup(dbs->getAttributeUsername().toStdString().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().toStdString().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.toStdString().c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                 e = ldap_next_entry( ld, e ), i++ )
            {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    users.append(QString::fromStdString(username));
                    if (bvals) ber_memfree(bvals);
                }
            }
        }
    }



    return users;
}

QString UserDBLDAP::getFirstname(QString username)
{
    if(ld){
        UserDatabaseSettings *dbs = settings;
        QString filter("(&(objectClass=person)("+dbs->getAttributeUsername()+"="+username+"))");
        char *attrs[] = { strdup(dbs->getAttributeFirstname().toStdString().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().toStdString().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.toStdString().c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                 e = ldap_next_entry( ld, e ), i++ )
            {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return QString::fromStdString(username);
                }
            }
        }
    }

    return QString();
}

QString UserDBLDAP::getLastname(QString username)
{
    if(ld){
        UserDatabaseSettings *dbs = settings;
        QString filter("(&(objectClass=person)("+dbs->getAttributeUsername()+"="+username+"))");
        char *attrs[] = { strdup(dbs->getAttributeLastname().toStdString().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().toStdString().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.toStdString().c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                 e = ldap_next_entry( ld, e ), i++ )
            {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return QString::fromStdString(username);
                }
            }
        }
    }

    return QString();
}

QString UserDBLDAP::getMail(QString username)
{
    if(ld){
        UserDatabaseSettings *dbs = settings;
        QString filter("(&(objectClass=person)("+dbs->getAttributeUsername()+"="+username+"))");
        char *attrs[] = { strdup(dbs->getAttributeMail().toStdString().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().toStdString().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.toStdString().c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                 e = ldap_next_entry( ld, e ), i++ )
            {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return QString::fromStdString(username);
                }
            }
        }
    }

    return QString();
}

QList<QString> UserDBLDAP::getDevices(QString username)
{
    QList<QString> users;
    if(ld){
        UserDatabaseSettings *dbs = settings;
        QString filter("(&(objectClass=person)("+dbs->getAttributeUsername()+"="+username+"))");

        char *attrs[] = { strdup(dbs->getAttributeDevices().toStdString().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().toStdString().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.toStdString().c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                 e = ldap_next_entry( ld, e ), i++ )
            {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    users.append(QString::fromStdString(username));
                    if (bvals) ber_memfree(bvals);
                }
            }
        }
    }



    return users;
}

QString UserDBLDAP::getOwnerOfDevice(QString device)
{
    if(ld){
        UserDatabaseSettings *dbs = settings;
        QString filter("(&(objectClass=person)(registeredAddress="+device+"))");
        char *attrs[] = { strdup(dbs->getAttributeUsername().toStdString().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().toStdString().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.toStdString().c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                 e = ldap_next_entry( ld, e ), i++ )
            {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return QString::fromStdString(username);
                }
            }
        }
    }
    return QString();
}

bool UserDBLDAP::createUser(QString username, QString firstname, QString lastname, QString mail)
{
    return false;
}

bool UserDBLDAP::updateUser(QString username, QString firstname, QString lastname, QString mail, QString devices)
{
    return false;
}
