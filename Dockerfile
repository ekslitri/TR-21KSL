FROM alpine:latest
WORKDIR /home/ekslitriHttpserver
COPY ./main .
RUN apk add libstdc++
RUN apk add libc6-compat
ENTRYPOINT ["./main"]