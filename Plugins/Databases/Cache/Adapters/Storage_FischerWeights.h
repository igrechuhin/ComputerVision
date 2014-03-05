#ifndef __Storage_FischerWeights
#define __Storage_FischerWeights

#include <cppbind.h>

ISC_NSP_BEGIN

class Persistent_t;
class Storage_Faces;
class Storage_FischerWeights;

class Storage_FischerWeights : public Persistent_t {
   friend class d_ref<Storage_FischerWeights>;

protected:
   Storage_FischerWeights() {}

private:
   static wchar_t __srv_cl_name[23];

   Storage_FischerWeights(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_FischerWeights() {}

   static d_ref<Storage_FischerWeights> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_FischerWeights> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_FischerWeights>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_FischerWeights), &obj, &num_refs))
         return d_ref<Storage_FischerWeights>(dynamic_cast<Storage_FischerWeights*>(obj), num_refs);
      else
         return d_ref<Storage_FischerWeights>(new Storage_FischerWeights(db, oref, cl_name));
   }

   static d_ref<Storage_FischerWeights> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_FischerWeights> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_FischerWeights> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setFace(const d_ref<Storage_Faces>& val);
   virtual d_ref<Storage_Faces> getFace() const;

   virtual void setIndex(const d_int& val);
   virtual d_int getIndex() const;

   virtual void setWeights(const d_ref< d_prim_vector<d_double> >& val);
   virtual d_ref< d_prim_vector<d_double> > getWeights() const;

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

   virtual d_binary FaceGetObject();
   virtual d_binary FaceGetObject(const d_int& force);

   virtual d_string FaceGetObjectId();
   virtual d_string FaceGetObjectId(const d_int& force);

   static d_status FaceIsValid(Database* __db, const d_string& value);

   virtual d_status FaceSetObject(const d_binary& newvalue);

   virtual d_status FaceSetObjectId(const d_string& newid);

   static d_status IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2);
   static d_status IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency);

   static d_bool IDKEYExists(Database* __db, const d_string& K1, const d_string& K2);
   static d_bool IDKEYExists(Database* __db, const d_string& K1, const d_string& K2, d_string& id);

   static d_ref<Storage_FischerWeights> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2);
   static d_ref<Storage_FischerWeights> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency);
   static d_ref<Storage_FischerWeights> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency, d_status& sc);

   static d_int IndexDisplayToLogical(Database* __db, const d_string& _val);

   static d_status IndexIsValid(Database* __db, const d_string& _val);

   static d_string IndexLogicalToDisplay(Database* __db, const d_int& _val);

   static d_double WeightsDisplayToLogical(Database* __db, const d_string& _val);

   virtual d_binary WeightsGetObject();
   virtual d_binary WeightsGetObject(const d_int& force);

   virtual d_string WeightsGetObjectId();
   virtual d_string WeightsGetObjectId(const d_int& force);

   static d_status WeightsIsValid(Database* __db, const d_string& _val);

   static d_string WeightsLogicalToDisplay(Database* __db, const d_double& _val);

   // Queries

   static void get_ByIndex(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.FischerWeights_ByIndex(?) }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_Extent(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.FischerWeights_Extent }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }
};

ISC_NSP_END

#endif
