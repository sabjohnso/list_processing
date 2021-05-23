#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Tape.hpp>

namespace ListProcessing::Dynamic::Details {

  /**
   * @brief A class template describing homogeneous dynamic trees.
   */
  template<typename T, size_type N>
  class Tree;

  /**
   * @brief Reference specialization fo the Tree class template
   */
  template<typename T>
  class Tree<T, 1> {
  public:
    using value_type       = T;
    using const_reference  = value_type const&;
    using rvalue_reference = value_type&&;

    Tree()
      : branch()
      , context(nil<ContextElement>)
      , tainted(false) {}

  private:
    struct Branch {

      using branch_pointer = shared_ptr<Branch>;
      using node_type      = variant<value_type, branch_pointer>;
      using data_type      = Tape<node_type>;

      Branch()
        : data(empty_tape<node_type>) {}

      Branch(data_type data)
        : data(data) {}

      data_type data;
    }; // end of struct Branch

    struct ContextElement {
      Branch branch;
      bool   tainted;

    }; // end of struct ContextElement

    using Context = List<ContextElement>;

    Tree(Branch branch, Context context, bool tainted)
      : branch(branch)
      , context(context)
      , tainted(tainted) {}

    //
    // ... class data
    //
    Branch  branch;
    Context context;
    bool    tainted;

    /**
     * @brief Return true if the focus of the current branch is at it's final
     * position
     */
    friend bool
    isAtBack(Tree xs) {
      return isAtBack(xs.branch.data);
    }

    /**
     * @brief Return true if the focus of the currrent node is at the initial
     * position
     */
    friend bool
    isAtFront(Tree xs) {
      return isAtFront(xs.branch.data);
    }

    /**
     * @brief Return true if the current focus of the current node is an empty
     * branch and false if it is a branch containing data.
     *
     * @details It is an error to call this function if the focus of the current
     * node is not a branch
     */
    friend bool
    isBranchEmpty(Tree xs) {
      return isEmpty(xs.branch.data);
    }

    /**
     * @brief isLeaf Return true if the focus of the current node is a leaf and
     * false if it is a branch.
     *
     * @details It is an error to call this function if the current node is
     * empty
     */
    friend bool
    isLeaf(Tree xs) {
      return holds_alternative<value_type>(read(xs.branch.data));
    }

    /**
     * @brief Return true if the focus of the current node is a branch and
     * false if it is a leaf.
     *
     * @details It is an error to call this function if the current node is
     * empty.
     */
    friend bool
    isBranch(Tree xs) {
      return holds_alternative<shared_ptr<Branch>>(read(xs.branch.data));
    }

    /**
     * @brief Return true if the tree does not have any data or structure beyond
     * the current node
     */
    friend bool
    isEmpty(Tree xs) {
      return isEmpty(xs.branch.data) && isNull(xs.context);
    }

    /**
     * @brief Insert a new value at the focus of the open node
     */
    friend Tree
    insert(Tree xs, const_reference x) {
      return Tree(Branch(insert(x, xs.branch.data)), xs.context, true);
    }

    /**
     * @brief Remove the branch or value that is the focus of the current node
     */
    friend Tree
    remove(Tree xs) {
      return Tree(Branch(remove(xs.branch.data)), xs.context, true);
    }

    /**
     * @brief Replace the value that is the focus of the current node with
     * the input value
     */
    friend Tree
    write(Tree xs, const_reference x) {
      return insert(remove(xs), x);
    }

    /**
     * @brief Return the value that is the focus of the open node
     */
    friend value_type
    read(Tree xs) {
      return get<value_type>(read(xs.branch.data));
    }

    /**
     * @brief Insert a new branch at the focus of the current node
     */
    friend Tree
    insertBranch(Tree xs) {
      return Tree(
        Branch(insert(
          typename Branch::node_type(make_shared<Branch>()), xs.branch.data)),
        xs.context,
        true);
    }

    /**
     * @brief Insert a branch into the into the focus of the open node
     */
    static Tree
    insertExistingBranch(Tree xs, Branch branch) {
      return Tree(
        Branch(insert(
          xs.branch.data,
          typename Branch::node_type(make_shared<Branch>(branch)))),
        xs.context,
        true);
    }

    /**
     * @brief Open the branch that is the focus of the currently open node
     */
    friend Tree
    open(Tree xs) {
      return Tree(
        *(get<shared_ptr<Branch>>(read(xs.branch.data))),
        cons(ContextElement{ xs.branch, xs.tainted }, xs.context),
        false);
    }

    /**
     * @brief Close the current node of the tree
     */
    friend Tree
    close(Tree xs) {
      return xs.tainted ? insertExistingBranch(
                            Tree(
                              head(xs.context).branch,
                              tail(xs.context),
                              ghead(xs.context).tainted),
                            xs.branch)
                        : Tree(
                            head(xs.context).branch,
                            tail(xs.context),
                            head(xs.context).tainted);
    }
  }; // end of class Tree

  template<typename T>
  inline const Tree<T, 1> empty_tree{};

} // end of namespace ListProcessing::Dynamic::Details
