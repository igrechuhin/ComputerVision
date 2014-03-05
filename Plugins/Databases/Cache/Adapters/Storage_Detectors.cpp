#include "Storage_Detectors.h"
#include "Storage_FaceRect.h"
#include "Storage_Faces.h"

ISC_NSP_BEGIN

wchar_t Storage_Detectors::__srv_cl_name[] = L"Storage.Detectors";

// Properties

void Storage_Detectors::setFace(const d_ref<Storage_Faces>& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Face";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref<Storage_Faces> Storage_Detectors::getFace() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Face";

   d_ref<Storage_Faces> __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Detectors::setRect(const d_ref<Storage_FaceRect>& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Rect";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref<Storage_FaceRect> Storage_Detectors::getRect() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Rect";

   d_ref<Storage_FaceRect> __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Detectors::setType(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Type";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_Detectors::getType() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Type";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

// Methods

d_string Storage_Detectors::_ClassName(Database* __db, const d_bool& fullname)
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

void Storage_Detectors::_ComposeOid(Database* __db, const d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%ComposeOid";

   __args_mgr.set_next(&id);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
}

d_status Storage_Detectors::_Delete(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::_Delete(Database* __db, const d_binary& oid)
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

d_status Storage_Detectors::_Delete(Database* __db, const d_binary& oid, const d_int& concurrency)
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

d_status Storage_Detectors::_DeleteExtent(Database* __db, const d_int& concurrency, d_string& deletecount, d_string& instancecount)
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

d_bool Storage_Detectors::_Exists(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Exists";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Detectors::_Exists(Database* __db, const d_binary& oid)
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

d_int Storage_Detectors::_IsA(Database* __db, const d_string& isclass)
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

d_status Storage_Detectors::_KillExtent(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%KillExtent";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::_SaveIndices(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::_SaveIndices(Database* __db, const d_string& pStartId)
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

d_status Storage_Detectors::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId)
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

d_status Storage_Detectors::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId, const d_bool& lockExtent)
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

d_binary Storage_Detectors::FaceGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Detectors::FaceGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Detectors::FaceGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Detectors::FaceGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::FaceIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"FaceIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::FaceSetObject(const d_binary& newvalue)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceSetObject";

   __args_mgr.set_next(&newvalue);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::FaceSetObjectId(const d_string& newid)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceSetObjectId";

   __args_mgr.set_next(&newid);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2)
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

d_status Storage_Detectors::IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency)
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

d_bool Storage_Detectors::IDKEYExists(Database* __db, const d_string& K1, const d_string& K2)
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

d_bool Storage_Detectors::IDKEYExists(Database* __db, const d_string& K1, const d_string& K2, d_string& id)
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

d_ref<Storage_Detectors> Storage_Detectors::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);

   d_ref<Storage_Detectors> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Detectors> Storage_Detectors::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&concurrency);

   d_ref<Storage_Detectors> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Detectors> Storage_Detectors::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency, d_status& sc)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&concurrency);
   __args_mgr.set_next(&sc);

   d_ref<Storage_Detectors> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Detectors::RectGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"RectGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Detectors::RectGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"RectGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Detectors::RectGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"RectGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Detectors::RectGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"RectGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::RectIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"RectIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::RectSetObject(const d_binary& newvalue)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"RectSetObject";

   __args_mgr.set_next(&newvalue);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::RectSetObjectId(const d_string& newid)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"RectSetObjectId";

   __args_mgr.set_next(&newid);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_Detectors::TypeDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"TypeDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Detectors::TypeIndexExists(Database* __db, const d_int& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"TypeIndexExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Detectors::TypeIndexExists(Database* __db, const d_int& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"TypeIndexExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Detectors::TypeIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"TypeIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Detectors::TypeLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"TypeLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

ISC_NSP_END
