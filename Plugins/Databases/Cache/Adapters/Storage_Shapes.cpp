#include "Storage_Faces.h"
#include "Storage_Point.h"
#include "Storage_Shapes.h"

ISC_NSP_BEGIN

wchar_t Storage_Shapes::__srv_cl_name[] = L"Storage.Shapes";

// Properties

void Storage_Shapes::setFace(const d_ref<Storage_Faces>& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Face";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref<Storage_Faces> Storage_Shapes::getFace() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Face";

   d_ref<Storage_Faces> __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

void Storage_Shapes::setShape(const d_ref< d_obj_vector<Storage_Point> >& val)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Shape";

   __args_mgr.set_next(&val);
   Critical_section cs(__db->get_cs_handle());
   __db->set_property(this, get_cl_name(), __prop_name, __args_mgr);
}

d_ref< d_obj_vector<Storage_Point> > Storage_Shapes::getShape() const
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __prop_name[] = L"Shape";

   d_ref< d_obj_vector<Storage_Point> > __res;
   __args_mgr.set_next_as_res(&__res);
   Critical_section cs(__db->get_cs_handle());
   __db->get_property(this, get_cl_name(), __prop_name, __args_mgr);
   return __res;
}

// Methods

d_string Storage_Shapes::_ClassName(Database* __db, const d_bool& fullname)
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

void Storage_Shapes::_ComposeOid(Database* __db, const d_string& id)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%ComposeOid";

   __args_mgr.set_next(&id);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
}

d_status Storage_Shapes::_Delete(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Delete";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Shapes::_Delete(Database* __db, const d_binary& oid)
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

d_status Storage_Shapes::_Delete(Database* __db, const d_binary& oid, const d_int& concurrency)
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

d_status Storage_Shapes::_DeleteExtent(Database* __db, const d_int& concurrency, d_string& deletecount, d_string& instancecount)
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

d_bool Storage_Shapes::_Exists(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%Exists";

   d_bool __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_bool Storage_Shapes::_Exists(Database* __db, const d_binary& oid)
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

d_int Storage_Shapes::_IsA(Database* __db, const d_string& isclass)
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

d_status Storage_Shapes::_KillExtent(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%KillExtent";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Shapes::_SaveIndices(Database* __db)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"%SaveIndices";

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Shapes::_SaveIndices(Database* __db, const d_string& pStartId)
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

d_status Storage_Shapes::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId)
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

d_status Storage_Shapes::_SaveIndices(Database* __db, const d_string& pStartId, const d_string& pEndId, const d_bool& lockExtent)
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

d_binary Storage_Shapes::FaceGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Shapes::FaceGetObject(const d_int& force)
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

d_string Storage_Shapes::FaceGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"FaceGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Shapes::FaceGetObjectId(const d_int& force)
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

d_status Storage_Shapes::FaceIsValid(Database* __db, const d_string& value)
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

d_status Storage_Shapes::FaceSetObject(const d_binary& newvalue)
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

d_status Storage_Shapes::FaceSetObjectId(const d_string& newid)
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

d_status Storage_Shapes::IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2)
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

d_status Storage_Shapes::IDKEYDelete(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency)
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

d_bool Storage_Shapes::IDKEYExists(Database* __db, const d_string& K1, const d_string& K2)
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

d_bool Storage_Shapes::IDKEYExists(Database* __db, const d_string& K1, const d_string& K2, d_string& id)
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

d_ref<Storage_Shapes> Storage_Shapes::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);

   d_ref<Storage_Shapes> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Shapes> Storage_Shapes::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&concurrency);

   d_ref<Storage_Shapes> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_ref<Storage_Shapes> Storage_Shapes::IDKEYOpen(Database* __db, const d_string& K1, const d_string& K2, const d_int& concurrency, d_status& sc)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"IDKEYOpen";

   __args_mgr.set_next(&K1);
   __args_mgr.set_next(&K2);
   __args_mgr.set_next(&concurrency);
   __args_mgr.set_next(&sc);

   d_ref<Storage_Shapes> __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Shapes::ShapeGetObject()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapeGetObject";

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_binary Storage_Shapes::ShapeGetObject(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapeGetObject";

   __args_mgr.set_next(&force);

   d_binary __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Shapes::ShapeGetObjectId()
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapeGetObjectId";

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_string Storage_Shapes::ShapeGetObjectId(const d_int& force)
{
   GEN_DECLARE_ARGS_AND_DB();
   wchar_t __mtd_name[] = L"ShapeGetObjectId";

   __args_mgr.set_next(&force);

   d_string __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(get_ref(), __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

d_status Storage_Shapes::ShapeIsValid(Database* __db, const d_string& value)
{
   GEN_DECLARE_ARGS();
   wchar_t __mtd_name[] = L"ShapeIsValid";

   __args_mgr.set_next(&value);

   d_status __res;
   __args_mgr.set_next_as_res(&__res);

   Critical_section cs(__db->get_cs_handle());
   __db->run_method(-1, __srv_cl_name, __mtd_name, __args_mgr);
   return __res;
}

ISC_NSP_END
