#include "Storage_Point.h"

ISC_NSP_BEGIN

wchar_t Storage_Point::__srv_cl_name[] = L"Storage.Point";

// Properties

void Storage_Point::setX(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"X";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_Point::getX() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"X";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Point::setY(const d_int& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Y";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_int Storage_Point::getY() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Y";

   d_int __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

// Methods

d_string Storage_Point::_ClassName(Database* __db, const d_bool& fullname)
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

d_status Storage_Point::_Delete(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Point::_Delete(Database* __db, const d_binary& oid)
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

d_status Storage_Point::_Delete(Database* __db, const d_binary& oid, const d_int& concurrency)
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

d_int Storage_Point::_IsA(Database* __db, const d_string& isclass)
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

d_string Storage_Point::LogicalToOdbc(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"LogicalToOdbc";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Point::LogicalToOdbc(Database* __db, const d_string& val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"LogicalToOdbc";

   __args_mgr.set_next(&val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Point::OdbcToLogical(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"OdbcToLogical";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Point::OdbcToLogical(Database* __db, const d_string& val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"OdbcToLogical";

   __args_mgr.set_next(&val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_Point::XDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"XDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Point::XIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"XIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Point::XLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"XLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_int Storage_Point::YDisplayToLogical(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"YDisplayToLogical";

   __args_mgr.set_next(&_val);

   d_int __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Point::YIsValid(Database* __db, const d_string& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"YIsValid";

   __args_mgr.set_next(&_val);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Point::YLogicalToDisplay(Database* __db, const d_int& _val)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"YLogicalToDisplay";

   __args_mgr.set_next(&_val);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

ISC_NSP_END
