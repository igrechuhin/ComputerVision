#ifndef __Storage_Detectors
#define __Storage_Detectors

#include <cppbind.h>

ISC_NSP_BEGIN

class Persistent_t;
class Storage_Detectors;
class Storage_FaceRect;
class Storage_Faces;

class Storage_Detectors : public Persistent_t {
   friend class d_ref<Storage_Detectors>;

protected:
   Storage_Detectors() {}

private:
   static wchar_t __srv_cl_name[18];

   Storage_Detectors(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_Detectors() {}

   static d_ref<Storage_Detectors> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_Detectors> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_Detectors>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_Detectors), &obj, &num_refs))
         return d_ref<Storage_Detectors>(dynamic_cast<Storage_Detectors*>(obj), num_refs);
      else
         return d_ref<Storage_Detectors>(new Storage_Detectors(db, oref, cl_name));
   }

   static d_ref<Storage_Detectors> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_Detectors> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_Detectors> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setFace(const d_ref<Storage_Faces>& val);
   virtual d_ref<Storage_Faces> getFace() const;

   virtual void setRect(const d_ref<Storage_FaceRect>& val);
   virtual d_ref<Storage_FaceRect> getRect() const;

   virtual void setType(const d_int& val);
   virtual d_int getType() const;

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

   static d_ref<Storage_Detectors> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2);
   static d_ref<Storage_Detectors> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency);
   static d_ref<Storage_Detectors> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency, d_status& sc);

   virtual d_binary RectGetObject();
   virtual d_binary RectGetObject(const d_int& force);

   virtual d_string RectGetObjectId();
   virtual d_string RectGetObjectId(const d_int& force);

   static d_status RectIsValid(Database* __db, const d_string& value);

   virtual d_status RectSetObject(const d_binary& newvalue);

   virtual d_status RectSetObjectId(const d_string& newid);

   static d_int TypeDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool TypeIndexExists(Database* __db, const d_int& K1);
   static d_bool TypeIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status TypeIsValid(Database* __db, const d_string& _val);

   static d_string TypeLogicalToDisplay(Database* __db, const d_int& _val);

   // Queries

   static void get_Extent(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Detectors_Extent }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }
};

ISC_NSP_END

#endif
