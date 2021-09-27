// swift-tools-version:5.4
import PackageDescription

let package = Package(
        name: "WaylandClient",
        products: [
            .library(name: "WaylandClient", targets: ["WaylandClient"]),
        ],
        dependencies: [
          .library("wayland-client")
        ],
        targets: [
            .target(name: "WaylandClient", dependencies: [
                .product(name: "WaylandClient", package: "WaylandClient"),
            ]),
        ]
)
