#include "registro.h"
#include <cstring>
#include <arpa/inet.h>

static void write_u32(std::vector<char>& out, uint32_t v) {
    uint32_t be = htonl(v);
    const char* p = reinterpret_cast<const char*>(&be);
    out.insert(out.end(), p, p+4);
}
static void write_i64(std::vector<char>& out, int64_t v) {
    for (int i=0;i<8;i++) out.push_back((v >> (i*8)) & 0xFF);
}
static uint32_t read_u32(const char* p) {
    uint32_t be;
    memcpy(&be, p, 4);
    return ntohl(be);
}
static int64_t read_i64(const char* p) {
    int64_t v = 0;
    for (int i=0;i<8;i++) v |= (uint64_t)(uint8_t)p[i] << (i*8);
    return v;
}

std::vector<char> Registro::serializar() const {
    std::vector<char> out;
    write_u32(out, 0);
    write_i64(out, id);
    write_u32(out, (uint32_t)titulo.size());
    out.insert(out.end(), titulo.begin(), titulo.end());
    write_u32(out, (uint32_t)ano);
    write_u32(out, (uint32_t)autores.size());
    out.insert(out.end(), autores.begin(), autores.end());
    write_u32(out, (uint32_t)citacoes);
    write_u32(out, (uint32_t)atualizacao.size());
    out.insert(out.end(), atualizacao.begin(), atualizacao.end());
    write_u32(out, (uint32_t)snippet.size());
    out.insert(out.end(), snippet.begin(), snippet.end());
    uint32_t total = (uint32_t)(out.size() - 4);
    uint32_t be = htonl(total);
    memcpy(out.data(), &be, 4);
    return out;
}

Registro Registro::desserializar_from_buffer(const char* buf, size_t size) {
    Registro r;
    if (size < 4) return r;
    uint32_t total = read_u32(buf); 
    const char* p = buf + 4;
    size_t remaining = size - 4;
    if (remaining < 8) return r;
    r.id = read_i64(p); p += 8; remaining -= 8;
    if (remaining < 4) return r;
    uint32_t len = read_u32(p); p += 4; remaining -= 4;
    if (remaining < len) len = (uint32_t)remaining;
    r.titulo.assign(p, p+len); p += len; remaining -= len;
    if (remaining < 4) return r;
    r.ano = (int)read_u32(p); p += 4; remaining -= 4;
    if (remaining < 4) return r;
    len = read_u32(p); p += 4; remaining -= 4;
    if (remaining < len) len = (uint32_t)remaining;
    r.autores.assign(p, p+len); p += len; remaining -= len;
    if (remaining < 4) return r;
    r.citacoes = (int)read_u32(p); p += 4; remaining -= 4;
    if (remaining < 4) return r;
    len = read_u32(p); p += 4; remaining -= 4;
    if (remaining < len) len = (uint32_t)remaining;
    r.atualizacao.assign(p, p+len); p += len; remaining -= len;
    if (remaining < 4) return r;
    len = read_u32(p); p += 4; remaining -= 4;
    if (remaining < len) len = (uint32_t)remaining;
    r.snippet.assign(p, p+len);
    return r;
}
