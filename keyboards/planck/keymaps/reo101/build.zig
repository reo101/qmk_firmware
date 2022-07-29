const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const target = std.zig.CrossTarget{ .cpu_arch = .arm, .os_tag = .freestanding, .abi = .eabi };
    const mode = std.builtin.Mode.ReleaseSmall;

    // const obj = b.addSharedLibrary("keymap", "keymap.zig", b.version(0, 0, 1));
    const keymap = b.addObject("keymap", "keymap.zig");
    keymap.setTarget(target);
    keymap.setBuildMode(mode);

    // keymap.addIncludeDir("/usr/include");
    // keymap.addIncludeDir("/data/data/com.termux/files/usr/include");
    // keymap.linkLibC();
    keymap.addIncludeDir("../../../../quantum");
    keymap.addIncludeDir("../../../../platforms");
    keymap.addIncludeDir("../../../../keyboards/planck/rev6");
    keymap.addIncludeDir("../../../../keyboards/keebio/iris");
    keymap.addIncludeDir("../../../../tmk_core/protocol");
    keymap.addIncludeDir("../../../../quantum/audio");
    keymap.addIncludeDir("../../../../quantum/logging");
    keymap.addIncludeDir("../../../../quantum/sequencer");

    // lib.linkLibC();

    // _ = obj.installRaw("keymap.o", std.build.InstallRawStep.CreateOptions{
    //    .dest_dir = .{.custom = (".")},
    // });

    const keymap_step = b.step("keymap", "Build the keymap");
    // b.installArtifact(lib);
    keymap_step.dependOn(&keymap.step);

    const keymap_tests = b.addTest("keymap.zig");
    keymap_tests.setTarget(target);
    keymap_tests.setBuildMode(mode);

    keymap_tests.addIncludeDir("/data/data/com.termux/files/usr/include");
    // keymap_tests.linkLibC();
    keymap_tests.addIncludeDir("../../../../quantum");
    keymap_tests.addIncludeDir("../../../../platforms");
    keymap_tests.addIncludeDir("../../../../keyboards/planck/rev6");
    keymap_tests.addIncludeDir("../../../../keyboards/keebio/iris");
    keymap_tests.addIncludeDir("../../../../tmk_core/protocol");
    keymap_tests.addIncludeDir("../../../../quantum/audio");
    keymap_tests.addIncludeDir("../../../../quantum/logging");
    keymap_tests.addIncludeDir("../../../../quantum/sequencer");

    const keymap_tests_step = b.step("test", "Test keymap");
    keymap_tests_step.dependOn(&keymap_tests.step);

    // obj.createObject;
    //
    // std.debug.print("{s}", .{obj.getOutputSource()});
    //
    // const obj_cmd = obj.run();
    //
    // const obj_step = b.step("object", "Build the object");
    // obj_step.dependOn(&obj_cmd.step);
}
