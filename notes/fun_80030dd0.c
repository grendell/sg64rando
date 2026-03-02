void FUN_80030dd0(uint param_1)

{
  uint uVar1;
  
  if ((param_1 & 0xff00) == 0) {
    *(undefined1 *)((param_1 & 0xff) + 0x800ec3d0) = 0xff;
  }
  else if ((param_1 & 0xff00) == 0x4000) {
    *(undefined1 *)((param_1 & 0xff) + 0x800ec3d0) = 0;
  }
  else if ((param_1 & 0x8000) == 0) {
    *(byte *)((param_1 & 0xff) + 0x800ec3d0) =
         (byte)((param_1 & 0xff00) >> 8) | *(byte *)((param_1 & 0xff) + 0x800ec3d0);
  }
  else {
    *(byte *)((param_1 & 0xff) + 0x800ec3d0) =
         *(byte *)((param_1 & 0xff) + 0x800ec3d0) & (byte)(0xff00 - (param_1 & 0x7f00) >> 8);
  }
  uVar1 = 0;
  if (DAT_800ebb6e != 0) {
    do {
      if ((uint)(byte)(&DAT_800ec350)[uVar1] == (param_1 & 0xff)) break;
      uVar1 = uVar1 + 1;
    } while ((int)uVar1 < (int)(uint)DAT_800ebb6e);
  }
  if (*(char *)((param_1 & 0xff) + 0x800ec3d0) == '\0') {
    if (uVar1 != DAT_800ebb6e) {
      if ((int)uVar1 < (int)(uint)DAT_800ebb6e) {
        do {
          (&DAT_800ec350)[uVar1] = *(undefined1 *)(uVar1 + 0x800ec351);
          uVar1 = uVar1 + 1;
        } while ((int)uVar1 < (int)(uint)DAT_800ebb6e);
      }
      DAT_800ebb6e = DAT_800ebb6e - 1;
    }
  }
  else if (uVar1 == DAT_800ebb6e) {
    for (; 0 < (int)uVar1; uVar1 = uVar1 - 1) {
      (&DAT_800ec350)[uVar1] = *(undefined1 *)(uVar1 + 0x800ec34f);
    }
    DAT_800ebb6e = DAT_800ebb6e + 1;
    DAT_800ec350 = (char)param_1;
  }
  return;
}