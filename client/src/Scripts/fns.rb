
def convert2new gid
  return 0 if gid == 0

  gid -= 1
  y = gid/16
  x = gid%16

  while y >= 42
    y -= 42
    x += 16
  end

  y*64 + x + 1
end

def convert2old gid
  return 0 if gid == 0

  gid -= 1
  y = gid/64
  x = gid%64

  while x >= 16
    x -= 16
    y += 42
  end

  y*16 + x + 1
end

