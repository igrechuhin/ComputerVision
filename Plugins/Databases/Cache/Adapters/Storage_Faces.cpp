#include "Storage_Detectors.h"
#include "Storage_Faces.h"
#include "Storage_FischerWeights.h"
#include "Storage_Persons.h"
#include "Storage_Photos.h"
#include "Storage_Shapes.h"

ISC_NSP_BEGIN

wchar_t Storage_Faces::__srv_cl_name[] = L"Storage.Faces";

// Properties

void Storage_Faces::setAge(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Age";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_Faces::getAge() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Age";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setBeard(const d_bool& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Beard";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_bool Storage_Faces::getBeard() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Beard";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setBetweenEyesDistance(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"BetweenEyesDistance";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_Faces::getBetweenEyesDistance() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"BetweenEyesDistance";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setClosedEyebrow(const d_bool& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"ClosedEyebrow";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_bool Storage_Faces::getClosedEyebrow() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"ClosedEyebrow";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setClosedForehead(const d_bool& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"ClosedForehead";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_bool Storage_Faces::getClosedForehead() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"ClosedForehead";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setDetectors(const d_ref< d_relationship<Storage_Detectors> >& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Detectors";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref< d_relationship<Storage_Detectors> > Storage_Faces::getDetectors() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Detectors";

   d_ref< d_relationship<Storage_Detectors> > __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setFischerWeights(const d_ref< d_relationship<Storage_FischerWeights> >& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"FischerWeights";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref< d_relationship<Storage_FischerWeights> > Storage_Faces::getFischerWeights() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"FischerWeights";

   d_ref< d_relationship<Storage_FischerWeights> > __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setGlasses(const d_bool& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Glasses";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_bool Storage_Faces::getGlasses() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Glasses";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setMoustache(const d_bool& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Moustache";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_bool Storage_Faces::getMoustache() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Moustache";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setOrientation(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Orientation";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_Faces::getOrientation() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Orientation";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setPerson(const d_ref<Storage_Persons>& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Person";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref<Storage_Persons> Storage_Faces::getPerson() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Person";

   d_ref<Storage_Persons> __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setPhoto(const d_ref<Storage_Photos>& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Photo";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref<Storage_Photos> Storage_Faces::getPhoto() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Photo";

   d_ref<Storage_Photos> __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Faces::setShapes(const d_ref< d_relationship<Storage_Shapes> >& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Shapes";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref< d_relationship<Storage_Shapes> > Storage_Faces::getShapes() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Shapes";

   d_ref< d_relationship<Storage_Shapes> > __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

// Methods

d_string Storage_Faces::_ClassName(Database* __db, const d_bool& fullname)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%ClassName";

   __args_mgr.set_next(&fullname);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

void Storage_Faces::_ComposeOid(Database* __db, const d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%ComposeOid";

   __args_mgr.set_next(&id);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
}

d_status Storage_Faces::_Delete(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_Delete(Database* __db, const d_binary& oid)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   __args_mgr.set_next(&oid);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_Delete(Database* __db, const d_binary& oid, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   __args_mgr.set_next(&oid);
   __args_mgr.set_next(&concurrency);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_DeleteExtent(Database* __db, const d_int& concurrency, d_string& deletecount, d_string& instancecount)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%DeleteExtent";

   __args_mgr.set_next(&concurrency);
   __args_mgr.set_next(&deletecount);
   __args_mgr.set_next(&instancecount);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::_Exists(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Exists";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::_Exists(Database* __db, const d_binary& oid)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Exists";

   __args_mgr.set_next(&oid);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_Faces::_IsA(Database* __db, const d_string& isclass)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%IsA";

   __args_mgr.set_next(&isclass);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_KillExtent(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%KillExtent";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_SaveIndices(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_SaveIndices(Database* __db, const d_string& pStartId)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   __args_mgr.set_next(&pStartId);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   __args_mgr.set_next(&pStartId);
   __args_mgr.set_next(&pEndId);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId, const d_bool& lockExtent)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   __args_mgr.set_next(&pStartId);
   __args_mgr.set_next(&pEndId);
   __args_mgr.set_next(&lockExtent);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_Faces::AgeDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"AgeDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::AgeIndexExists(Database* __db, const d_int& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"AgeIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::AgeIndexExists(Database* __db, const d_int& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"AgeIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::AgeIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"AgeIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::AgeLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"AgeLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::BeardDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BeardDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::BeardIndexExists(Database* __db, const d_bool& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BeardIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::BeardIndexExists(Database* __db, const d_bool& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BeardIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::BeardIsValid(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BeardIsValid";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::BeardIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BeardIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::BeardLogicalToDisplay(Database* __db, const d_bool& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BeardLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_Faces::BetweenEyesDistanceDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BetweenEyesDistanceDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::BetweenEyesDistanceIndexExists(Database* __db, const d_int& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BetweenEyesDistanceIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::BetweenEyesDistanceIndexExists(Database* __db, const d_int& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BetweenEyesDistanceIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::BetweenEyesDistanceIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BetweenEyesDistanceIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::BetweenEyesDistanceLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"BetweenEyesDistanceLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::ClosedEyebrowDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedEyebrowDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::ClosedEyebrowIndexExists(Database* __db, const d_bool& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedEyebrowIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::ClosedEyebrowIndexExists(Database* __db, const d_bool& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedEyebrowIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::ClosedEyebrowIsValid(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedEyebrowIsValid";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::ClosedEyebrowIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedEyebrowIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::ClosedEyebrowLogicalToDisplay(Database* __db, const d_bool& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedEyebrowLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::ClosedForeheadDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedForeheadDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::ClosedForeheadIndexExists(Database* __db, const d_bool& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedForeheadIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::ClosedForeheadIndexExists(Database* __db, const d_bool& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedForeheadIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::ClosedForeheadIsValid(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedForeheadIsValid";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::ClosedForeheadIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedForeheadIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::ClosedForeheadLogicalToDisplay(Database* __db, const d_bool& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ClosedForeheadLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::DetectorsGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"DetectorsGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::DetectorsGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"DetectorsGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::DetectorsGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"DetectorsGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::DetectorsGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"DetectorsGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::DetectorsIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"DetectorsIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::FischerWeightsGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FischerWeightsGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::FischerWeightsGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FischerWeightsGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::FischerWeightsGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FischerWeightsGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::FischerWeightsGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FischerWeightsGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::FischerWeightsIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"FischerWeightsIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::GlassesDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"GlassesDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::GlassesIndexExists(Database* __db, const d_bool& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"GlassesIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::GlassesIndexExists(Database* __db, const d_bool& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"GlassesIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::GlassesIsValid(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"GlassesIsValid";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::GlassesIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"GlassesIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::GlassesLogicalToDisplay(Database* __db, const d_bool& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"GlassesLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYDelete";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYDelete";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&concurrency);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::IDKEYExists(Database* __db, const d_string& K1, const d_string& K2)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::IDKEYExists(Database* __db, const d_string& K1, const d_string& K2, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Faces> Storage_Faces::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);

   d_ref<Storage_Faces> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Faces> Storage_Faces::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&concurrency);

   d_ref<Storage_Faces> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Faces> Storage_Faces::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency, d_status& sc)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&concurrency);
   __args_mgr.set_next(&sc);

   d_ref<Storage_Faces> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::MoustacheDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"MoustacheDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::MoustacheIndexExists(Database* __db, const d_bool& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"MoustacheIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::MoustacheIndexExists(Database* __db, const d_bool& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"MoustacheIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::MoustacheIsValid(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"MoustacheIsValid";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::MoustacheIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"MoustacheIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::MoustacheLogicalToDisplay(Database* __db, const d_bool& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"MoustacheLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_Faces::OrientationDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"OrientationDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::OrientationIndexExists(Database* __db, const d_int& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"OrientationIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Faces::OrientationIndexExists(Database* __db, const d_int& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"OrientationIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::OrientationIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"OrientationIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::OrientationLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"OrientationLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::PersonGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PersonGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::PersonGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PersonGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::PersonGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PersonGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::PersonGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PersonGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::PersonIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"PersonIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::PersonSetObject(const d_binary& newvalue)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PersonSetObject";

   __args_mgr.set_next(&newvalue);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::PersonSetObjectId(const d_string& newid)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PersonSetObjectId";

   __args_mgr.set_next(&newid);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::PhotoGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PhotoGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::PhotoGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PhotoGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::PhotoGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PhotoGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::PhotoGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PhotoGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::PhotoIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"PhotoIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::PhotoSetObject(const d_binary& newvalue)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PhotoSetObject";

   __args_mgr.set_next(&newvalue);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::PhotoSetObjectId(const d_string& newid)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"PhotoSetObjectId";

   __args_mgr.set_next(&newid);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::ShapesGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapesGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Faces::ShapesGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapesGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::ShapesGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapesGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Faces::ShapesGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapesGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Faces::ShapesIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ShapesIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

ISC_NSP_END
