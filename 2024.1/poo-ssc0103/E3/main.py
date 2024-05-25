#!/usr/bin/env python3

class BinaryTree:
    def __init__(self):
        self.root = None
        self.tree = {}

    def insert(self, value):
        if self.root is None:
            self.root = {"value": value, "left": None, "right": None}
            self.tree[value] = (None, None)
        else:
            self._insert_recursive(self.root, value)

    def _insert_recursive(self, node, value):
        if value < node["value"]:
            if node["left"] is None:
                node["left"] = {"value": value, "left": None, "right": None}
                self.tree[node["value"]] = (value, self.tree[node["value"]][1])
                self.tree[value] = (None, None)
            else:
                self._insert_recursive(node["left"], value)
        elif value > node["value"]:
            if node["right"] is None:
                node["right"] = {"value": value, "left": None, "right": None}
                self.tree[node["value"]] = (self.tree[node["value"]][0], value)
                self.tree[value] = (None, None)
            else:
                self._insert_recursive(node["right"], value)

    def inorder(self):
        inorder_list = self._inorder_recursive(self.root)
        return " " + "  ".join(inorder_list)

    def _inorder_recursive(self, node):
        if node is None:
            return []
        return (
            self._inorder_recursive(node["left"])
            + [node["value"]]
            + self._inorder_recursive(node["right"]))

    def __str__(self):
        if self.root is None:
            return "Empty tree"
        s = "digraph {\n"
        for k, v in self.tree.items():
            left, right = v
            if left is not None:
                s += f"{k} -> {left}\n"
            if right is not None:
                s += f"{k} -> {right}\n"
        return s + "}\n"


def process_commands(commands):
    tree = BinaryTree()
    for command in commands:
        action, value = command.split()
        if action == "i":
            tree.insert(value)
    return tree


import sys


def main():
    commands = sys.stdin.read().strip().split("\n")
    tree = process_commands(commands)

    print(tree.inorder())
    print(tree)


if __name__ == "__main__":
    main()
