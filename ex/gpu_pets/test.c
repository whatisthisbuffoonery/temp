#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK(call) do { \
    cl_int e = (call); \
    if (e != CL_SUCCESS) { \
        fprintf(stderr, "%s failed: %d\n", #call, e); \
        exit(1); \
    } \
} while (0)

int main(void)
{
    cl_platform_id platform;
    cl_device_id device;
    cl_int err;
    char name[256];
    size_t count = 1024;
    float output[1024];

    /* This code is compiled for, and executed on, the GPU. */
    const char *source =
        "__kernel void test(__global float *out) {"
        "    size_t i = get_global_id(0);"
        "    out[i] = (float)i * 2.0f + 1.0f;"
        "}";

    /* Select a GPU explicitly. No CPU fallback. */
    CHECK(clGetPlatformIDs(1, &platform, NULL));
    CHECK(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU,
        1, &device, NULL));
    CHECK(clGetDeviceInfo(device, CL_DEVICE_NAME,
        sizeof(name), name, NULL));
    printf("Selected GPU: %s\n", name);

    cl_context context = clCreateContext(
        NULL, 1, &device, NULL, NULL, &err);
    CHECK(err);

    cl_command_queue queue = clCreateCommandQueue(
        context, device, 0, &err);
    CHECK(err);

    /* Compile the kernel. */
    cl_program program = clCreateProgramWithSource(
        context, 1, &source, NULL, &err);
    CHECK(err);

    err = clBuildProgram(program, 1, &device,
        "-cl-std=CL1.2", NULL, NULL);
    if (err != CL_SUCCESS)
    {
        char log[16384] = {0};

        clGetProgramBuildInfo(program, device,
            CL_PROGRAM_BUILD_LOG, sizeof(log) - 1, log, NULL);
        fprintf(stderr, "Build log: %s\n", log);
        CHECK(err);
    }

    cl_kernel kernel = clCreateKernel(program, "test", &err);
    CHECK(err);

    /* Allocate output storage accessible to the GPU. */
    cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
        sizeof(output), NULL, &err);
    CHECK(err);

    CHECK(clSetKernelArg(kernel, 0, sizeof(buffer), &buffer));

    /* Launch 1,024 work items, each computing one output. */
    CHECK(clEnqueueNDRangeKernel(queue, kernel,
        1, NULL, &count, NULL, 0, NULL, NULL));

    /* Blocking read: wait until the results reach the CPU. */
    CHECK(clEnqueueReadBuffer(queue, buffer, CL_TRUE,
        0, sizeof(output), output, 0, NULL, NULL));

    for (size_t i = 0; i < count; ++i)
    {
        if (output[i] != (float)i * 2.0f + 1.0f)
        {
            fprintf(stderr, "FAIL at %zu: got %f\n", i, output[i]);
            return 1;
        }
    }

    printf("PASS: all 1024 GPU results match CPU expectations.\n");
    printf("First: %.0f; last: %.0f\n", output[0], output[1023]);

    CHECK(clReleaseMemObject(buffer));
    CHECK(clReleaseKernel(kernel));
    CHECK(clReleaseProgram(program));
    CHECK(clReleaseCommandQueue(queue));
    CHECK(clReleaseContext(context));
    return 0;
}
