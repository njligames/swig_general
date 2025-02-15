/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package api.internals.evr;

public class Math {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Math(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Math obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        evrJNI.delete_Math(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Math() {
    this(evrJNI.new_Math(), true);
  }

  public double add(double a, double b) {
    return evrJNI.Math_add(swigCPtr, this, a, b);
  }

}
