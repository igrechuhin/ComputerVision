#ifndef __Storage_FaceRect
#define __Storage_FaceRect

#include <cppbind.h>

ISC_NSP_BEGIN

class Registered_t;
class Storage_FaceRect;

class Storage_FaceRect : public Registered_t {
   friend class d_ref<Storage_FaceRect>;

protected:
   Storage_FaceRect() {}

private:
   static wchar_t __srv_cl_name[17];

   Storage_FaceRect(Database* db, int oref, const wchar_t* cl_name)
   { init(db, oref, cl_name); }

public:
   virtual ~Storage_FaceRect() {}

   static d_ref<Storage_FaceRect> openref(t_istream& in, Database* db)
   {
      int oref; cl_name_t tname;
      abs_d_ref::get_oref_n_name(in, &oref, tname);
      return openref(db, oref, tname);
   }

   static d_ref<Storage_FaceRect> openref(Database* db, int oref, const_name_t cl_name)
   {
      if (oref == 0)
         return d_ref<Storage_FaceRect>();

      Obj_t *obj; int *num_refs;
      if (db->get_proxies_info()->get_proxy_info(oref, typeid(Storage_FaceRect), &obj, &num_refs))
         return d_ref<Storage_FaceRect>(dynamic_cast<Storage_FaceRect*>(obj), num_refs);
      else
         return d_ref<Storage_FaceRect>(new Storage_FaceRect(db, oref, cl_name));
   }

   static d_ref<Storage_FaceRect> create_new(Database* db, const_str_t init_val = 0, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->make_obj(__srv_cl_name, init_val, err), db);
   }

   static d_ref<Storage_FaceRect> openid(Database* db, const const_str_t ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->openid_obj(__srv_cl_name, ident, concurrency, timeout, err), db);
   }

   static d_ref<Storage_FaceRect> open(Database* db, const d_binary& ident, int concurrency = -1, int timeout = -1, Db_err* err = 0)
   {
      Critical_section cs(db->get_cs_handle());
      return openref(db->open_obj(ident, concurrency, timeout, err), db);
   }

   // Properties

   virtual void setHeight(const d_int& val);
   virtual d_int getHeight() const;

   virtual void setLeft(const d_int& val);
   virtual d_int getLeft() const;

   virtual void setLeftX(const d_int& val);
   virtual d_int getLeftX() const;

   virtual void setLeftY(const d_int& val);
   virtual d_int getLeftY() const;

   virtual void setRight(const d_int& val);
   virtual d_int getRight() const;

   virtual void setRightX(const d_int& val);
   virtual d_int getRightX() const;

   virtual void setRightY(const d_int& val);
   virtual d_int getRightY() const;

   virtual void setWidth(const d_int& val);
   virtual d_int getWidth() const;

   virtual void setX(const d_int& val);
   virtual d_int getX() const;

   virtual void setY(const d_int& val);
   virtual d_int getY() const;

   // Methods

   static d_string _ClassName(Database* __db, const d_bool& fullname);

   static d_status _Delete(Database* __db);
   static d_status _Delete(Database* __db, const d_binary& oid);
   static d_status _Delete(Database* __db, const d_binary& oid, const d_int& concurrency);

   static d_int _IsA(Database* __db, const d_string& isclass);

   static d_int HeightDisplayToLogical(Database* __db, const d_string& _val);

   static d_status HeightIsValid(Database* __db, const d_string& _val);

   static d_string HeightLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int LeftDisplayToLogical(Database* __db, const d_string& _val);

   static d_status LeftIsValid(Database* __db, const d_string& _val);

   static d_string LeftLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int LeftXDisplayToLogical(Database* __db, const d_string& _val);

   static d_status LeftXIsValid(Database* __db, const d_string& _val);

   static d_string LeftXLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int LeftYDisplayToLogical(Database* __db, const d_string& _val);

   static d_status LeftYIsValid(Database* __db, const d_string& _val);

   static d_string LeftYLogicalToDisplay(Database* __db, const d_int& _val);

   static d_string LogicalToOdbc(Database* __db);
   static d_string LogicalToOdbc(Database* __db, const d_string& val);

   static d_string OdbcToLogical(Database* __db);
   static d_string OdbcToLogical(Database* __db, const d_string& val);

   static d_int RightDisplayToLogical(Database* __db, const d_string& _val);

   static d_status RightIsValid(Database* __db, const d_string& _val);

   static d_string RightLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int RightXDisplayToLogical(Database* __db, const d_string& _val);

   static d_status RightXIsValid(Database* __db, const d_string& _val);

   static d_string RightXLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int RightYDisplayToLogical(Database* __db, const d_string& _val);

   static d_status RightYIsValid(Database* __db, const d_string& _val);

   static d_string RightYLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int WidthDisplayToLogical(Database* __db, const d_string& _val);

   static d_status WidthIsValid(Database* __db, const d_string& _val);

   static d_string WidthLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int XDisplayToLogical(Database* __db, const d_string& _val);

   static d_status XIsValid(Database* __db, const d_string& _val);

   static d_string XLogicalToDisplay(Database* __db, const d_int& _val);

   static d_int YDisplayToLogical(Database* __db, const d_string& _val);

   static d_status YIsValid(Database* __db, const d_string& _val);

   static d_string YLogicalToDisplay(Database* __db, const d_int& _val);

   // Queries
};

ISC_NSP_END

#endif
