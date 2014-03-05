#ifndef __Storage_Info
#define __Storage_Info

#include <cppbind.h>

ISC_NSP_BEGIN

class Persistent_t;
class Storage_Info;

class Storage_Info : public Persistent_t {
   friend class d_ref<Storage_Info>;

protected:
   Storage_Info() {}

private:
   static wchar_t __srv_cl_name[13];

   Storage_Info(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_Info() {}

   static d_ref<Storage_Info> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_Info> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_Info>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_Info), &obj, &num_refs))
         return d_ref<Storage_Info>(dynamic_cast<Storage_Info*>(obj), num_refs);
      else
         return d_ref<Storage_Info>(new Storage_Info(db, oref, cl_name));
   }

   static d_ref<Storage_Info> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_Info> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_Info> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setFischerIndex(const d_int& val);
   virtual d_int getFischerIndex() const;

   virtual void setNeedFischerUpdate(const d_bool& val);
   virtual d_bool getNeedFischerUpdate() const;

   virtual void setNeedModelUpdate(const d_bool& val);
   virtual d_bool getNeedModelUpdate() const;

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

   static d_int FischerIndexDisplayToLogical(Database* __db, const d_string& _val);

   static d_status FischerIndexIsValid(Database* __db, const d_string& _val);

   static d_string FischerIndexLogicalToDisplay(Database* __db, const d_int& _val);

   static d_status IDKEYDelete(Database* __db, const d_string& K1);
   static d_status IDKEYDelete(Database* __db, const d_string& K1, const d_int& concurrency);

   static d_bool IDKEYExists(Database* __db, const d_string& K1);
   static d_bool IDKEYExists(Database* __db, const d_string& K1, d_string& id);

   static d_ref<Storage_Info> IDKEYOpen(Database* __db, const d_string& K1);
   static d_ref<Storage_Info> IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency);
   static d_ref<Storage_Info> IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency, d_status& sc);

   static d_bool NeedFischerUpdateDisplayToLogical(Database* __db, const d_string& _val);

   static d_status NeedFischerUpdateIsValid(Database* __db);
   static d_status NeedFischerUpdateIsValid(Database* __db, const d_string& _val);

   static d_string NeedFischerUpdateLogicalToDisplay(Database* __db, const d_bool& _val);

   static d_bool NeedModelUpdateDisplayToLogical(Database* __db, const d_string& _val);

   static d_status NeedModelUpdateIsValid(Database* __db);
   static d_status NeedModelUpdateIsValid(Database* __db, const d_string& _val);

   static d_string NeedModelUpdateLogicalToDisplay(Database* __db, const d_bool& _val);

   // Queries

   static void get_Extent(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Info_Extent }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_IDs(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Info_IDs }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }
};

ISC_NSP_END

#endif
