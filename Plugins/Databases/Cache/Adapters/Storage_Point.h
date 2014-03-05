#ifndef __Storage_Point
#define __Storage_Point

#include <cppbind.h>

ISC_NSP_BEGIN

class Registered_t;
class Storage_Point;

class Storage_Point : public Registered_t {
   friend class d_ref<Storage_Point>;

protected:
   Storage_Point() {}

private:
   static wchar_t __srv_cl_name[14];

   Storage_Point(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_Point() {}

   static d_ref<Storage_Point> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_Point> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_Point>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_Point), &obj, &num_refs))
         return d_ref<Storage_Point>(dynamic_cast<Storage_Point*>(obj), num_refs);
      else
         return d_ref<Storage_Point>(new Storage_Point(db, oref, cl_name));
   }

   static d_ref<Storage_Point> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_Point> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_Point> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setX(const d_int& val);
   virtual d_int getX() const;

   virtual void setY(const d_int& val);
   virtual d_int getY() const;

   // Methods

   static d_string _ClassName(Database* __db, const d_bool& fullname);

   static d_status _Delete(Database* __db);
   static d_status _Delete(Database* __db, const d_binary& oid);
   static d_status _Delete(Database* __db, const d_binary& oid, const d_int& concurrency);

   static d_int _IsA(Database* __db, const d_string& isclass);

   static d_string LogicalToOdbc(Database* __db);
   static d_string LogicalToOdbc(Database* __db, const d_string& val);

   static d_string OdbcToLogical(Database* __db);
   static d_string OdbcToLogical(Database* __db, const d_string& val);

   static d_int XDisplayToLogical(Database* __db, const d_string& _val);

   static d_status XIsValid(Database* __db, const d_string& _val);

   static d_string XLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int YDisplayToLogical(Database* __db, const d_string& _val);

   static d_status YIsValid(Database* __db, const d_string& _val);

   static d_string YLogicalToDisplay(Database* __db, const d_int& _val);

   // Queries
};

ISC_NSP_END

#endif
