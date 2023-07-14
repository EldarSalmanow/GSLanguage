extern func println(text: String): Void

func hello() {
    println("Hello, World!")
}

class Person {
    func Person(n: String, a: I32) {
        self.name = n
        self.age = a
    }

    func getName() {
        return self.name
    }

    func getAge() {
        return self.age
    }

    name: String
    age: I32
}

func main() {
    var p: Person = Person("", 1);
    p.getName()
    p.getAge()

    match x {
        1 -> {
            println("Hi!")
            println("Hi!")
        }
        2 -> println("Who!")
    }

    if 1 < 2 {
        for i in 0..10 {
            println("Hello, World!")
        }
    } else if 3 < 4 {
        println("Hello!")
    } else {
        println("World!")
    }

    hello()
}

module IO {

    extern func PrintLn(string: String): Void

}

module Std {

    ![builtin]
    class String

    ![builtin]
    class I32

}

import Std::IO

enum NodeKind {
    IntLit,
    BinExpr
}

class Node {
    abstract func kind(): NodeKind
}

class IntLit from Node {
    var num: I32

    override func kind(): NodeKind {
        return NodeKind::IntLit
    }
}

enum BinOp {
    Add,
    Sub
}

class BinExpr from Node {
    var lhs: Node
    var rhs: Node
    var op: BinOp

    override func kind(): NodeKind {
        return NodeKind::BinExpr
    }
}

func main() {
    var ns: [Node, 2] = [IntLit { 1 }, BinExpr { IntLit { 2 }, IntLit { 3 }, BinOp::Add }]

    var x: I32 = 10

    IO::PrintLn("Hello!")

    match x {
        1 -> print("Hi!")
        _ -> print("Not hi!")
    }
}
