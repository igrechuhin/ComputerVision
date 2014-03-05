#include "Storage_Info.h"

ISC_NSP_BEGIN

wchar_t Storage_Info::__srv_cl_name[] = L"Storage.Info";

// Properties

void Storage_Info::setFischerIndex(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"FischerIndex";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_Info::getFischerIndex() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"FischerIndex";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Info::setNeedFischerUpdate(const d_bool& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"NeedFischerUpdate";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_bool Storage_Info::getNeedFischerUpdate() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"NeedFischerUpdate";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Info::setNeedModelUpdate(const d_bool& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"NeedModelUpdate";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_bool Storage_Info::getNeedModelUpdate() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"NeedModelUpdate";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

// Methods

d_string Storage_Info::_ClassName(Database* __db, const d_bool& fullname)
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

void Storage_Info::_ComposeOid(Database* __db, const d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%ComposeOid";

   __args_mgr.set_next(&id);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
}

d_status Storage_Info::_Delete(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::_Delete(Database* __db, const d_binary& oid)
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

d_status Storage_Info::_Delete(Database* __db, const d_binary& oid, const d_int& concurrency)
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

d_status Storage_Info::_DeleteExtent(Database* __db, const d_int& concurrency, d_string& deletecount, d_string& instancecount)
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

d_bool Storage_Info::_Exists(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Exists";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Info::_Exists(Database* __db, const d_binary& oid)
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

d_int Storage_Info::_IsA(Database* __db, const d_string& isclass)
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

d_status Storage_Info::_KillExtent(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%KillExtent";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::_SaveIndices(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::_SaveIndices(Database* __db, const d_string& pStartId)
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

d_status Storage_Info::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId)
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

d_status Storage_Info::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId, const d_bool& lockExtent)
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

d_int Storage_Info::FischerIndexDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"FischerIndexDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::FischerIndexIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"FischerIndexIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Info::FischerIndexLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"FischerIndexLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::IDKEYDelete(Database* __db, const d_string& K1)
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

d_status Storage_Info::IDKEYDelete(Database* __db, const d_string& K1, const d_int& concurrency)
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

d_bool Storage_Info::IDKEYExists(Database* __db, const d_string& K1)
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

d_bool Storage_Info::IDKEYExists(Database* __db, const d_string& K1, d_string& id)
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

d_ref<Storage_Info> Storage_Info::IDKEYOpen(Database* __db, const d_string& K1)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);

   d_ref<Storage_Info> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Info> Storage_Info::IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&concurrency);

   d_ref<Storage_Info> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Info> Storage_Info::IDKEYOpen(Database* __db, const d_string& K1, const d_int& concurrency, d_status& sc)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&concurrency);
   __args_mgr.set_next(&sc);

   d_ref<Storage_Info> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Info::NeedFischerUpdateDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedFischerUpdateDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::NeedFischerUpdateIsValid(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedFischerUpdateIsValid";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::NeedFischerUpdateIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedFischerUpdateIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Info::NeedFischerUpdateLogicalToDisplay(Database* __db, const d_bool& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedFischerUpdateLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Info::NeedModelUpdateDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedModelUpdateDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::NeedModelUpdateIsValid(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedModelUpdateIsValid";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Info::NeedModelUpdateIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedModelUpdateIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Info::NeedModelUpdateLogicalToDisplay(Database* __db, const d_bool& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"NeedModelUpdateLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

ISC_NSP_END
