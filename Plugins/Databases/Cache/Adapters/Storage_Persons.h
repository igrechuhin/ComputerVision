#ifndef __Storage_Persons
#define __Storage_Persons

#include <cppbind.h>

ISC_NSP_BEGIN

class Persistent_t;
class Storage_Faces;
class Storage_Persons;

class Storage_Persons : public Persistent_t {
   friend class d_ref<Storage_Persons>;

protected:
   Storage_Persons() {}

private:
   static wchar_t __srv_cl_name[16];

   Storage_Persons(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_Persons() {}

   static d_ref<Storage_Persons> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_Persons> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_Persons>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_Persons), &obj, &num_refs))
         return d_ref<Storage_Persons>(dynamic_cast<Storage_Persons*>(obj), num_refs);
      else
         return d_ref<Storage_Persons>(new Storage_Persons(db, oref, cl_name));
   }

   static d_ref<Storage_Persons> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_Persons> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_Persons> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setFaces(const d_ref< d_relationship<Storage_Faces> >& val);
   virtual d_ref< d_relationship<Storage_Faces> > getFaces() const;

   virtual void setGender(const d_bool& val);
   virtual d_bool getGender() const;

   // Methods

   static d_string _ClassName(Database* __db, const d_bool& fullname);

   static void _ComposeOid(Database* __db, const d_string& id);

   static d_status _Delete(Database* __db);
   static d_status _Delete(Database* __db, const d_binary& oid);
   static d_status _Delete(Database* __db, const d_binary& oid, const d_int& concurrency);

   static d_status _DeleteExtent(Database* __db, const d_int& concurrency, d_string& deletecount, d_string& instancecount);

   static d_bool _Exists(Database* __db);
   static d_bool _Exists(Database* __db, const d_binary& oid);

   static d_int _IsA(Database* __db, const d_string& isclass);

   static d_status _KillExtent(Database* __db);

   static d_status _SaveIndices(Database* __db);
   static d_status _SaveIndices(Database* __db, const d_string& pStartId);
   static d_status _SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId);
   static d_status _SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId, const d_bool& lockExtent);

   virtual d_binary FacesGetObject();
   virtual d_binary FacesGetObject(const d_int& force);

   virtual d_string FacesGetObjectId();
   virtual d_string FacesGetObjectId(const d_int& force);

   static d_status FacesIsValid(Database* __db, const d_string& value);

   static d_bool GenderDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool GenderIndexExists(Database* __db, const d_bool& K1);
   static d_bool GenderIndexExists(Database* __db, const d_bool& K1, d_string& id);

   static d_status GenderIsValid(Database* __db);
   static d_status GenderIsValid(Database* __db, const d_string& _val);

   static d_string GenderLogicalToDisplay(Database* __db, const d_bool& _val);

   static d_status IDKEYDelete(Database* __db, const d_string& K1);
   static d_status IDKEYDelete(Database* __db, const d_string& K1, const d_int& concurrency);

   static d_bool IDKEYExists(Database* __db, const d_string& K1);
   static d_bool IDKEYExists(Database* __db, const d_string& K1, d_string& id);

   static d_ref<Storage_Persons> IDKEYOpen(Database* __db, const d_string& K1);
   static d_ref<Storage_Persons> IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency);
   static d_ref<Storage_Persons> IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency, d_status& sc);

   // Queries

   static void get_Extent(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Persons_Extent }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_Filtered(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Persons_Filtered(?) }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_IDs(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Persons_IDs }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }
};

ISC_NSP_END

#endif
