#include "Storage_FischerFaces.h"

ISC_NSP_BEGIN

wchar_t Storage_FischerFaces::__srv_cl_name[] = L"Storage.FischerFaces";

// Properties

void Storage_FischerFaces::setIndex(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Index";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_FischerFaces::getIndex() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Index";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_FischerFaces::setWopt(const d_ref< d_prim_vector<d_double> >& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Wopt";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref< d_prim_vector<d_double> > Storage_FischerFaces::getWopt() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Wopt";

   d_ref< d_prim_vector<d_double> > __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

// Methods

d_string Storage_FischerFaces::_ClassName(Database* __db, const d_bool& fullname)
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

void Storage_FischerFaces::_ComposeOid(Database* __db, const d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%ComposeOid";

   __args_mgr.set_next(&id);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
}

d_status Storage_FischerFaces::_Delete(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_FischerFaces::_Delete(Database* __db, const d_binary& oid)
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

d_status Storage_FischerFaces::_Delete(Database* __db, const d_binary& oid, const d_int& concurrency)
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

d_status Storage_FischerFaces::_DeleteExtent(Database* __db, const d_int& concurrency, d_string& deletecount, d_string& instancecount)
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

d_bool Storage_FischerFaces::_Exists(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Exists";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_FischerFaces::_Exists(Database* __db, const d_binary& oid)
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

d_int Storage_FischerFaces::_IsA(Database* __db, const d_string& isclass)
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

d_status Storage_FischerFaces::_KillExtent(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%KillExtent";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_FischerFaces::_SaveIndices(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_FischerFaces::_SaveIndices(Database* __db, const d_string& pStartId)
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

d_status Storage_FischerFaces::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId)
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

d_status Storage_FischerFaces::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId, const d_bool& lockExtent)
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

d_status Storage_FischerFaces::IDKEYDelete(Database* __db, const d_string& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYDelete";

   __args_mgr.set_next(&K1);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_FischerFaces::IDKEYDelete(Database* __db, const d_string& K1, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYDelete";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&concurrency);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_FischerFaces::IDKEYExists(Database* __db, const d_string& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYExists";

   __args_mgr.set_next(&K1);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_FischerFaces::IDKEYExists(Database* __db, const d_string& K1, d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYExists";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&id);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_FischerFaces> Storage_FischerFaces::IDKEYOpen(Database* __db, const d_string& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);

   d_ref<Storage_FischerFaces> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_FischerFaces> Storage_FischerFaces::IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&concurrency);

   d_ref<Storage_FischerFaces> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_FischerFaces> Storage_FischerFaces::IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency, d_status& sc)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&concurrency);
   __args_mgr.set_next(&sc);

   d_ref<Storage_FischerFaces> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_FischerFaces::IndexDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IndexDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_FischerFaces::IndexIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IndexIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_FischerFaces::IndexLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IndexLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_double Storage_FischerFaces::WoptDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"WoptDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_double __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_FischerFaces::WoptGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"WoptGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_FischerFaces::WoptGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"WoptGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_FischerFaces::WoptGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"WoptGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_FischerFaces::WoptGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"WoptGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_FischerFaces::WoptIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"WoptIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_FischerFaces::WoptLogicalToDisplay(Database* __db, const d_double& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"WoptLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

ISC_NSP_END
