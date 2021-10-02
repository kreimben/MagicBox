import Foundation
import Wayland

@main
class Main {
    static func main() {
        print("Hello, This will be MagicBox!")

        let display = wl_start_display()
    }
}