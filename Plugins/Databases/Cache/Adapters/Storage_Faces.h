#ifndef __Storage_Faces
#define __Storage_Faces

#include <cppbind.h>

ISC_NSP_BEGIN

class Persistent_t;
class Storage_Detectors;
class Storage_Faces;
class Storage_FischerWeights;
class Storage_Persons;
class Storage_Photos;
class Storage_Shapes;

class Storage_Faces : public Persistent_t {
   friend class d_ref<Storage_Faces>;

protected:
   Storage_Faces() {}

private:
   static wchar_t __srv_cl_name[14];

   Storage_Faces(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_Faces() {}

   static d_ref<Storage_Faces> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_Faces> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_Faces>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_Faces), &obj, &num_refs))
         return d_ref<Storage_Faces>(dynamic_cast<Storage_Faces*>(obj), num_refs);
      else
         return d_ref<Storage_Faces>(new Storage_Faces(db, oref, cl_name));
   }

   static d_ref<Storage_Faces> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_Faces> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_Faces> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setAge(const d_int& val);
   virtual d_int getAge() const;

   virtual void setBeard(const d_bool& val);
   virtual d_bool getBeard() const;

   virtual void setBetweenEyesDistance(const d_int& val);
   virtual d_int getBetweenEyesDistance() const;

   virtual void setClosedEyebrow(const d_bool& val);
   virtual d_bool getClosedEyebrow() const;

   virtual void setClosedForehead(const d_bool& val);
   virtual d_bool getClosedForehead() const;

   virtual void setDetectors(const d_ref< d_relationship<Storage_Detectors> >& val);
   virtual d_ref< d_relationship<Storage_Detectors> > getDetectors() const;

   virtual void setFischerWeights(const d_ref< d_relationship<Storage_FischerWeights> >& val);
   virtual d_ref< d_relationship<Storage_FischerWeights> > getFischerWeights() const;

   virtual void setGlasses(const d_bool& val);
   virtual d_bool getGlasses() const;

   virtual void setMoustache(const d_bool& val);
   virtual d_bool getMoustache() const;

   virtual void setOrientation(const d_int& val);
   virtual d_int getOrientation() const;

   virtual void setPerson(const d_ref<Storage_Persons>& val);
   virtual d_ref<Storage_Persons> getPerson() const;

   virtual void setPhoto(const d_ref<Storage_Photos>& val);
   virtual d_ref<Storage_Photos> getPhoto() const;

   virtual void setShapes(const d_ref< d_relationship<Storage_Shapes> >& val);
   virtual d_ref< d_relationship<Storage_Shapes> > getShapes() const;

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

   static d_int AgeDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool AgeIndexExists(Database* __db, const d_int& K1);
   static d_bool AgeIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status AgeIsValid(Database* __db, const d_string& _val);

   static d_string AgeLogicalToDisplay(Database* __db, const d_int& _val);

   static d_bool BeardDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool BeardIndexExists(Database* __db, const d_bool& K1);
   static d_bool BeardIndexExists(Database* __db, const d_bool& K1, d_string& id);

   static d_status BeardIsValid(Database* __db);
   static d_status BeardIsValid(Database* __db, const d_string& _val);

   static d_string BeardLogicalToDisplay(Database* __db, const d_bool& _val);

   static d_int BetweenEyesDistanceDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool BetweenEyesDistanceIndexExists(Database* __db, const d_int& K1);
   static d_bool BetweenEyesDistanceIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status BetweenEyesDistanceIsValid(Database* __db, const d_string& _val);

   static d_string BetweenEyesDistanceLogicalToDisplay(Database* __db, const d_int& _val);

   static d_bool ClosedEyebrowDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool ClosedEyebrowIndexExists(Database* __db, const d_bool& K1);
   static d_bool ClosedEyebrowIndexExists(Database* __db, const d_bool& K1, d_string& id);

   static d_status ClosedEyebrowIsValid(Database* __db);
   static d_status ClosedEyebrowIsValid(Database* __db, const d_string& _val);

   static d_string ClosedEyebrowLogicalToDisplay(Database* __db, const d_bool& _val);

   static d_bool ClosedForeheadDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool ClosedForeheadIndexExists(Database* __db, const d_bool& K1);
   static d_bool ClosedForeheadIndexExists(Database* __db, const d_bool& K1, d_string& id);

   static d_status ClosedForeheadIsValid(Database* __db);
   static d_status ClosedForeheadIsValid(Database* __db, const d_string& _val);

   static d_string ClosedForeheadLogicalToDisplay(Database* __db, const d_bool& _val);

   virtual d_binary DetectorsGetObject();
   virtual d_binary DetectorsGetObject(const d_int& force);

   virtual d_string DetectorsGetObjectId();
   virtual d_string DetectorsGetObjectId(const d_int& force);

   static d_status DetectorsIsValid(Database* __db, const d_string& value);

   virtual d_binary FischerWeightsGetObject();
   virtual d_binary FischerWeightsGetObject(const d_int& force);

   virtual d_string FischerWeightsGetObjectId();
   virtual d_string FischerWeightsGetObjectId(const d_int& force);

   static d_status FischerWeightsIsValid(Database* __db, const d_string& value);

   static d_bool GlassesDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool GlassesIndexExists(Database* __db, const d_bool& K1);
   static d_bool GlassesIndexExists(Database* __db, const d_bool& K1, d_string& id);

   static d_status GlassesIsValid(Database* __db);
   static d_status GlassesIsValid(Database* __db, const d_string& _val);

   static d_string GlassesLogicalToDisplay(Database* __db, const d_bool& _val);

   static d_status IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2);
   static d_status IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency);

   static d_bool IDKEYExists(Database* __db, const d_string& K1, const d_string& K2);
   static d_bool IDKEYExists(Database* __db, const d_string& K1, const d_string& K2, d_string& id);

   static d_ref<Storage_Faces> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2);
   static d_ref<Storage_Faces> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency);
   static d_ref<Storage_Faces> IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency, d_status& sc);

   static d_bool MoustacheDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool MoustacheIndexExists(Database* __db, const d_bool& K1);
   static d_bool MoustacheIndexExists(Database* __db, const d_bool& K1, d_string& id);

   static d_status MoustacheIsValid(Database* __db);
   static d_status MoustacheIsValid(Database* __db, const d_string& _val);

   static d_string MoustacheLogicalToDisplay(Database* __db, const d_bool& _val);

   static d_int OrientationDisplayToLogical(Database* __db, const d_string& _val);

   static d_bool OrientationIndexExists(Database* __db, const d_int& K1);
   static d_bool OrientationIndexExists(Database* __db, const d_int& K1, d_string& id);

   static d_status OrientationIsValid(Database* __db, const d_string& _val);

   static d_string OrientationLogicalToDisplay(Database* __db, const d_int& _val);

   virtual d_binary PersonGetObject();
   virtual d_binary PersonGetObject(const d_int& force);

   virtual d_string PersonGetObjectId();
   virtual d_string PersonGetObjectId(const d_int& force);

   static d_status PersonIsValid(Database* __db, const d_string& value);

   virtual d_status PersonSetObject(const d_binary& newvalue);

   virtual d_status PersonSetObjectId(const d_string& newid);

   virtual d_binary PhotoGetObject();
   virtual d_binary PhotoGetObject(const d_int& force);

   virtual d_string PhotoGetObjectId();
   virtual d_string PhotoGetObjectId(const d_int& force);

   static d_status PhotoIsValid(Database* __db, const d_string& value);

   virtual d_status PhotoSetObject(const d_binary& newvalue);

   virtual d_status PhotoSetObjectId(const d_string& newid);

   virtual d_binary ShapesGetObject();
   virtual d_binary ShapesGetObject(const d_int& force);

   virtual d_string ShapesGetObjectId();
   virtual d_string ShapesGetObjectId(const d_int& force);

   static d_status ShapesIsValid(Database* __db, const d_string& value);

   // Queries

   static void get_All(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Faces_All }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_Extent(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Faces_Extent }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }

   static void get_Filtered(d_query& query)
   {
      Critical_section cs(Critical_section_handle::get_cs_handle());
      wchar_t stored_proc_call[] = L"{ call Storage.Faces_Filtered(?, ?, ?, ?, ?, ?, ?, ?, ?, ?) }";
      query.prepare(stored_proc_call);
      query.set_stored_proc(true);
   }
};

ISC_NSP_END

#endif
