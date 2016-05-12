// Copyright 2014 The CRAVE developers. All rights reserved.

#include "../../crave/experimental/SequenceItem.hpp"

namespace crave
{
  crv_sequence_item::crv_sequence_item() : gen_(), built_(false), cloned_(false) {}

  crv_sequence_item::crv_sequence_item(crv_sequence_item const & other) : crv_object(other), gen_(), built_(false), cloned_(true) {}

  std::string crv_sequence_item::obj_kind() const { return "crv_sequence_item"; }

  bool crv_sequence_item::randomize() {
    assert(!cloned_ && "cloned crv_sequence_item cannot be randomized");
    if (!built_) {
      gen_ = std::make_shared<Generator>();
      recursive_build(*gen_);
      built_ = true;
    }
    return gen_->nextCov();
  }
  
  void crv_sequence_item::goal(crv_covergroup& group) {
    for (auto e : group.bound_var_expr_list()) (*gen_)(e);
    for (auto e : group.uncovered_as_list()) gen_->cover(e);
  }
    
  void crv_sequence_item::request_rebuild() {
    built_ = false;
    gen_.reset();
    crv_object::request_rebuild();
  }
}
