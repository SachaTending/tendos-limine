// Used for creating GDT segment descriptors in 64-bit integer form.

#include <tty.h>
#include <stdint.h>
#include <gdt.h>

void setGdt(limit, base);

void setGdt2(gp);

extern gdt_flush();

// struct gdt_desc gdt[32];

static struct gdt_desc gdt[] = {
    {0},

    {
        .limit       = 0xffff,
        .base_low    = 0x0000,
        .base_mid    = 0x00,
        .access      = 0b10011010,
        .granularity = 0b00000000,
        .base_hi     = 0x00
    },

    {
        .limit       = 0xffff,
        .base_low    = 0x0000,
        .base_mid    = 0x00,
        .access      = 0b10010010,
        .granularity = 0b00000000,
        .base_hi     = 0x00
    },

    {
        .limit       = 0xffff,
        .base_low    = 0x0000,
        .base_mid    = 0x00,
        .access      = 0b10011010,
        .granularity = 0b11001111,
        .base_hi     = 0x00
    },

    {
        .limit       = 0xffff,
        .base_low    = 0x0000,
        .base_mid    = 0x00,
        .access      = 0b10010010,
        .granularity = 0b11001111,
        .base_hi     = 0x00
    },

    {
        .limit       = 0x0000,
        .base_low    = 0x0000,
        .base_mid    = 0x00,
        .access      = 0b10011010,
        .granularity = 0b00100000,
        .base_hi     = 0x00
    },

    {
        .limit       = 0x0000,
        .base_low    = 0x0000,
        .base_mid    = 0x00,
        .access      = 0b10010010,
        .granularity = 0b00000000,
        .base_hi     = 0x00
    }
};

struct gdt_ptr gp;

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_mid = (base >> 16) & 0xFF;
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
    gdt[num].base_hi = 0x00;
}

void
create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;

    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24

    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;

    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0

    printf("0x%x \n", descriptor);
}

int
test2(void)
{
    //create_descriptor(0, 0, 0);
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = &gdt;


    /* Our NULL descriptor */
    //gdt_set_gate(0, 0, 0, 0, 0);

    //gdt_set_gate(1, 0, 0x00009a000000ffff, 0x9A, 0xCF);
    //gdt_set_gate(2, 0, 0x000093000000ffff, 0x92, 0xCF);

    //gdt_set_gate(3, 0, 0x00cf9a000000ffff, 0x9A, 0xCF);
    //gdt_set_gate(4, 0, 0x00cf93000000ffff, 0x92, 0xCF);

    //gdt_set_gate(4, 0, 0x00af9b000000ffff, 0x9A, 0xCF);
    //gdt_set_gate(5, 0, 0x00af93000000ffff, 0x92, 0xCF);
    
    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    //gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    //gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_flush();
    //create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    //create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    //create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    //create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

    return 0;
}