extern func to_string(value: I32): String

extern func println(text: String): Void

func hello() {
    if 1 < 45 {
        println("Hi")
    }

    println("Hello, World!")
}
