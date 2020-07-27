#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Tape.hpp>

namespace ListProcessing::Dynamic::Details
{

  /**
   * @brief A class template describing homogeneous dynamic trees.
   */
  template<typename T, size_type N>
  class Tree;

  /**
   * @brief Reference specialization fo the Tree class template
   */
  template<typename T>
  class Tree<T,1>
  {
  public:
    using value_type = T;
    using const_reference = value_type const&;
    using rvalue_reference = value_type&&;

    Tree()
      : branch()
      , context(nil<ContextElement>)
      , tainted(false)
    {}

  private:
    struct Branch
    {

      using branch_pointer = shared_ptr<Branch>;
      using node_type = variant<value_type, branch_pointer>;
      using data_type = Tape<node_type>;


      Branch()
        : data(empty_tape<node_type>)
      {}

      Branch(data_type data)
        : data(data)
      {}

      data_type data;
    }; // end of struct Branch


    struct ContextElement
    {
      Branch branch;
      bool tainted;

    };
    using Context = List<ContextElement>;

    Tree(Branch branch, Context context, bool tainted)
      : branch(branch)
      , context(context)
      , tainted(tainted)
    {}

    Branch branch;
    Context context;
    bool tainted;

    friend bool
    isAtBack(Tree xs){
      return isAtBack(xs.branch.data);
    }

    friend bool
    isAtFront(Tree xs){
      return isAtFront(xs.branch.data);
    }

    friend bool
    isBranchEmpty(Tree xs)
    {
      return isEmpty(xs.branch.data);
    }

    friend bool
    isLeaf(Tree xs)
    {
      return holds_alternative<value_type>(read(xs.branch.data));
    }


    friend bool
    isBranch(Tree xs)
    {
      return holds_alternative<shared_ptr<Branch>>(read(xs.branch.data));
    }

    friend bool
    isEmpty(Tree xs)
    {
      return isEmpty(xs.branch.data) && isNull(xs.context);
    }



    friend Tree
    insert(Tree xs, const_reference x)
    {
      return Tree(Branch(insert(xs.branch.data, x)), xs.context, true);
    }

    friend Tree
    remove(Tree xs)
    {
      return Tree(Branch(remove(xs.branch.data)), xs.context, true);
    }

    friend value_type
    read(Tree xs)
    {
      return get<value_type>(read(xs.branch.data));
    }

    friend Tree
    insertBranch(Tree xs)
    {
      return Tree(Branch(insert(xs.branch.data, typename Branch::node_type(make_shared<Branch>()))),
                  xs.context, true);
    }

    static Tree
    insertExistingBranch(Tree xs, Branch branch)
    {
      return Tree(Branch(insert(xs.branch.data, typename Branch::node_type(make_shared<Branch>(branch)))),
                  xs.context, true);
    }

    friend Tree
    open(Tree xs)
    {
      return Tree(*(get<shared_ptr<Branch>>(read(xs.branch.data))),
                  cons(ContextElement{xs.branch, xs.tainted},
                       xs.context),
                  false);
    }

    friend Tree
    close(Tree xs)
    {
      return xs.tainted
        ? insertExistingBranch(
          Tree(head(xs.context).branch,
               tail(xs.context),
               ghead(xs.context).tainted),
          xs.branch)
        : Tree(head(xs.context).branch,
               tail(xs.context),
               head(xs.context).tainted);
    }


  }; // end of class Tree



  template<typename T>
  inline const Tree<T,1> empty_tree{};

} // end of namespace ListProcessing::Dynamic::Details
