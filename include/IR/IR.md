Code

    extern func print(string: String): Void

    func main() {
        var a = 10

        print(a)
    }

IR

    @[extern("C")]
    func print(string: String): Void

    func main(): Void {
        #0 var a: I32
        set #0 10

        call print(#0)
    }

Code

    std.gs

    extern func println(string: String): Void

    extern func to_string(number: I32): String

    main.gs

    import std

    func main() {
        for i in 0..10 {
            println(to_string(i))
        }
    }

IR

    @[extern("C")]
    func println(string: String): Void

    @[extern("C")]
    func to_string(number: I32): String

    func main(): Void {
        bb0:
            #0 var i: I32
            set #0, 0
        bb1:
            cmp #0, 10
            je bb3
        bb2:
            #1 var tmp0: String
            call to_string(#0), #1
            call println(#1)
        bb3:
            return
    }
