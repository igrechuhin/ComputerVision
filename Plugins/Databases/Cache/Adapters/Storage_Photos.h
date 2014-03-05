#ifndef __Storage_Photos
#define __Storage_Photos

#include <cppbind.h>

ISC_NSP_BEGIN

class Persistent_t;
class Storage_Faces;
class Storage_Photos;

class Storage_Photos : public Persistent_t {
   friend class d_ref<Storage_Photos>;

protected:
   Storage_Photos() {}

private:
   static wchar_t __srv_cl_name[15];

   Storage_Photos(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_Photos() {}

   static d_ref<Storage_Photos> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_Photos> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_Photos>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_Photos), &obj, &num_refs))
         return d_ref<Storage_Photos>(dynamic_cast<Storage_Photos*>(obj), num_refs);
      else
         return d_ref<Storage_Photos>(new Storage_Photos(db, oref, cl_name));
   }

   static d_ref<Storage_Photos> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_Photos> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_Photos> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setCRC(const d_int& val);
   virtual d_int getCRC() const;

   virtual void setColorDepth(const d_int& val);
   virtual d_int getColorDepth() const;

   virtual void setFaces(const d_ref< d_relationship<Storage_Faces> >& val);
   virtual d_ref< d_relationship<Storage_Faces> > getFaces() const;

   virtual void setFacesCount(const d_int& val);
   virtual d_int getFacesCount() const;

   virtual void setHeight(const d_int& val);
   virtual d_int getHeight() const;

   virtual void setImage(const d_ref<d_file_bin_stream>& val);
   virtual d_ref<d_file_bin_stream> getImage() const;

   virtual void setMiddleBrightness(const d_int& val);
   virtual d_int getMiddleBrightness() const;

   virtual void setWidth(const d_int& val);
   virtual d_int getWidth() const;

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

   static d_int CRCDisplayToLogical(Database* __db, const d_string& _val);

   static d_status CRCIndexDelete(Database* __db, const d_int& K1);
   static d_status CRCIndexDelete(Database* __db, const d_int& K1, const d_int& concurrency);

   static d_bool CRCIndexExists(Database* __db, const d_int& K1);
   static d_bool CRCIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_ref<Storage_Photos> CRCIndexOpen(Database* __db, const d_int& K1);
   static d_ref<Storage_Photos> CRCIndexOpen(Database* __db, const d_int& K1, const d_int& concurrency);
   static d_ref<Storage_Photos> CRCIndexOpen(Database* __db, const d_int& K1, const d_int& concurrency, d_status& sc);

   static d_status CRCIsValid(Database* __db, const d_string& _val);

   static d_string CRCLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int ColorDepthDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool ColorDepthIndexExists(Database* __db, const d_int& K1);
   static d_bool ColorDepthIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status ColorDepthIsValid(Database* __db, const d_string& _val);

   static d_string ColorDepthLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int FacesCountDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool FacesCountIndexExists(Database* __db, const d_int& K1);
   static d_bool FacesCountIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status FacesCountIsValid(Database* __db, const d_string& _val);

   static d_string FacesCountLogicalToDisplay(Database* __db, const d_int& _val);

   virtual d_binary FacesGetObject();
   virtual d_binary FacesGetObject(const d_int& force);

   virtual d_string FacesGetObjectId();
   virtual d_string FacesGetObjectId(const d_int& force);

   static d_status FacesIsValid(Database* __db, const d_string& value);

   static d_int HeightDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool HeightIndexExists(Database* __db, const d_int& K1);
   static d_bool HeightIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status HeightIsValid(Database* __db, const d_string& _val);

   static d_string HeightLogicalToDisplay(Database* __db, const d_int& _val);

   static d_status IDKEYDelete(Database* __db, const d_string& K1);
   static d_status IDKEYDelete(Database* __db, const d_string& K1, const d_int& concurrency);

   static d_bool IDKEYExists(Database* __db, const d_string& K1);
   static d_bool IDKEYExists(Database* __db, const d_string& K1, d_string& id);

   static d_ref<Storage_Photos> IDKEYOpen(Database* __db, const d_string& K1);
   static d_ref<Storage_Photos> IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency);
   static d_ref<Storage_Photos> IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency, d_status& sc);

   virtual d_string ImageGetObjectId();
   virtual d_string ImageGetObjectId(const d_int& force);

   static d_status ImageIsValid(Database* __db, const d_string& value);

   virtual d_status ImageSet(const d_string& newvalue);

   virtual d_status ImageSetObject(const d_binary& newvalue);

   virtual d_status ImageSetObjectId(const d_string& newid);

   static d_int MiddleBrightnessDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool MiddleBrightnessIndexExists(Database* __db, const d_int& K1);
   static d_bool MiddleBrightnessIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status MiddleBrightnessIsValid(Database* __db, const d_string& _val);

   static d_string MiddleBrightnessLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int WidthDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool WidthIndexExists(Database* __db, const d_int& K1);
   static d_bool WidthIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status WidthIsValid(Database* __db, const d_string& _val);

   static d_string WidthLogicalToDisplay(Database* __db, const d_int& _val);

   // Queries

   static void get_All(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Photos_All }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_ByWidthHeightCRC(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Photos_ByWidthHeightCRC(?, ?, ?) }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_Extent(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Photos_Extent }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_Filtered(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Photos_Filtered(?, ?, ?, ?, ?, ?, ?, ?, ?, ?) }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }
};

ISC_NSP_END

#endif
