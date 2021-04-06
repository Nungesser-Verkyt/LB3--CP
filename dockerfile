FROM alpine

COPY ./nee-LB3.cpp .

RUN apk update 
RUN apk add build-base musl-dev libc-dev gdb

RUN g++ nee-LB3.cpp -static
CMD ./a.out

